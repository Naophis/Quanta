/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
/* Intrinsic functions of MCU */
#include <machine.h>

#define FLASH_BLOCKS_DECLARE

#include "iodefine.h"
#include "flash3.h"

#define true 1
#define false 0

/******************************************************************************
 Macro definitions
 ******************************************************************************/
#define BSP_ICLK_HZ 10000000
#define BSP_DATA_FLASH_SIZE_BYTES 8
/* Define read mode macro */
#define READ_MODE               0
/* Define ROM PE mode macro */
#define ROM_PE_MODE             1
/* Define data flash PE mode macro */
#define FLD_PE_MODE             2
/* The number of ICLK ticks needed for 35us delay are calculated below */
#define WAIT_TRESW              (35*(BSP_ICLK_HZ/1000000))
/* The number of ICLK ticks needed for 10us delay are calculated below */
#define WAIT_T10USEC            (10*(BSP_ICLK_HZ/1000000))
/* The number of loops to wait for FENTRYR timeout. */
#define FLASH_FENTRYR_TIMEOUT   (4)

/******************************************************************************
 Typedef definitions
 ******************************************************************************/
/* These typedefs are used for guaranteeing correct accesses to memory. When
 working with the FCU sometimes byte or word accesses are required. */
typedef __evenaccess                                       volatile uint8_t * FCU_BYTE_PTR;
typedef __evenaccess                                       volatile uint16_t * FCU_WORD_PTR;
typedef __evenaccess                                       volatile uint32_t * FCU_LONG_PTR;

/* These flash states are used internal for locking purposes. */
typedef enum {
	FLASH_READY, FLASH_ERASING, FLASH_WRITING, FLASH_BLANKCHECK, FLASH_LOCK_BIT
} flash_states_t;

/******************************************************************************
 Exported global variables
 ******************************************************************************/

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/
/* Signals whether FCU firmware has been transferred to the FCU RAM
 0 : No, 1 : Yes */
static uint8_t g_fcu_transfer_complete = 0;
/* Valid values are 'READ_MODE','ROM_PE_MODE' or 'FLD_PE_MODE' */
static uint8_t g_current_mode;
/* Stores whether the peripheral clock notification command has
 been executed */
static uint8_t g_fcu_pclk_command = 0;
/* States for flash operations */
static flash_states_t g_flash_state;

#ifndef FLASH_API_RX_CFG_IGNORE_LOCK_BITS
/* Determines whether lock bit protection is used when programming/erasing */
static uint8_t g_lock_bit_protection = true;
#endif

/* Flash intialisation function prototype */
static uint8_t flash_init(void);
/* Enter PE mode function prototype */
static uint8_t enter_pe_mode(uint32_t flash_addr);
/* Exit PE mode function prototype */
static void exit_pe_mode(uint32_t flash_addr);
/* ROM write function prototype */
static uint8_t rom_write(uint32_t address, uint32_t data, uint32_t size);
/* Data flash write function prototype */
static uint8_t data_flash_write(uint32_t address, uint32_t data, uint32_t size);
/* Data flash status clear function prototype */
static void data_flash_status_clear(void);
/* Notify peripheral clock function prototype */
static uint8_t notify_peripheral_clock(FCU_BYTE_PTR flash_addr);
/* FCU reset function prototype */
static void flash_reset(void);
/* Used to grab flash state */
static uint8_t flash_grab_state(flash_states_t new_state);
/* Used to release flash state */
static void flash_release_state(void);
/* Used to issue an erase command to the FCU */
static uint8_t flash_erase_command(FCU_BYTE_PTR const erase_addr);
/* Used to get largest programming size that can be used. */
static uint32_t flash_get_program_size(uint32_t bytes, uint32_t flash_addr);

/******************************************************************************
 * Function Name: flash_init
 * Description  : Initializes the FCU peripheral block.
 *                NOTE: This function does not have to execute from in RAM.
 * Arguments    : none
 * Return Value : FLASH_SUCCESS -
 *                    Operation Successful
 *                FLASH_FAILURE -
 *                    Operation Failed
 ******************************************************************************/
static uint8_t flash_init(void) {
	volatile int32_t wait_cnt;
	FLASH.FAEINT.BIT.CFAEIE = 0;
	FLASH.FAEINT.BIT.CMDLKIE = 0;
	FLASH.FAEINT.BIT.DFAEIE = 0;
	FLASH.FAEINT.BIT.ECRCTIE = 0;
	IPR(FCU, FIFERR)= 0;
	IEN(FCU, FIFERR)= 0;
	IPR(FCU, FRDYI)= 0;
	IEN(FCU, FRDYI)= 0;
	if (FLASH.FENTRYR.WORD != 0x0000) {
		FLASH.FENTRYR.WORD = 0xAA00;
		wait_cnt = FLASH_FENTRYR_TIMEOUT;
		while (0x0000 != FLASH.FENTRYR.WORD) {
			if (wait_cnt-- <= 0) {
				return FLASH_FAILURE;
			}
		}
	}
	g_fcu_transfer_complete = 1;
	return FLASH_SUCCESS;
}
/******************************************************************************
 End of function  flash_init
 ******************************************************************************/

/******************************************************************************
 * Function Name: R_FlashGetVersion
 * Description  : Returns the current version of this module. The version number
 *                is encoded where the top 2 bytes are the major version number
 *                and the bottom 2 bytes are the minor version number. For
 *                example, Version 4.25 would be returned as 0x00040019.
 * Arguments    : none
 * Return Value : Version of this module.
 ******************************************************************************/
#pragma inline(R_FlashGetVersion)
uint32_t R_FlashGetVersion(void) {
	return ((((uint32_t) RX_FLASH_API_VERSION_MAJOR) << 16)
			| ((uint32_t) RX_FLASH_API_VERSION_MINOR));
}
/******************************************************************************
 End of function  R_FlashGetVersion
 ******************************************************************************/

/******************************************************************************
 * Function Name: data_flash_status_clear
 * Description  : Clear the status of the Data Flash operation.
 *                NOTE: This function does not have to execute from in RAM.
 * Arguments    : none
 * Return Value : none
 ******************************************************************************/
static void data_flash_status_clear(void) {
	FCU_BYTE_PTR ptrb;
	ptrb = (FCU_BYTE_PTR) (DF_ADDRESS);
	if (FLASH.FSTATR.BIT.ILGLERR == 1) {
		if (FLASH.FASTAT.BYTE != 0x10) {
			FLASH.FASTAT.BYTE = 0x10;
		}
	}
	*ptrb = 0x50;
}
/******************************************************************************
 End of function  data_flash_status_clear
 ******************************************************************************/

/******************************************************************************
 * Function Name: data_flash_write
 * Description  : Write either bytes to Data Flash area.
 *                NOTE: This function does not have to execute from in RAM.
 * Arguments    : address -
 *                    The address (in the Data Flash programming area)
 *                    to write the data to
 *                data -
 *                    The address of the data to write
 *                size -
 *                    The size of the data to write. Must be set to
 *                    either DF_PROGRAM_SIZE_LARGE or DF_PROGRAM_SIZE_SMALL.
 * Return Value : FLASH_SUCCESS -
 *                    Operation Successful
 *                FLASH_FAILURE -
 *                    Operation Failed
 ******************************************************************************/
static uint8_t data_flash_write(uint32_t address, uint32_t data, uint32_t size) {
	volatile int32_t wait_cnt;
	volatile uint32_t n = 0;
	FLASH.FSADDR.BIT.FSADDR = address;
	if (DF_PROGRAM_SIZE_SMALL == size) {
		*(FCU_BYTE_PTR) DF_ADDRESS = 0xE8;
		*(FCU_BYTE_PTR) DF_ADDRESS = 0x02;
		//2byteずつ読み込む。256byteなら128回ループする
		while (n++ < (size >> 1)) {
			const uint8_t* p = (const uint8_t*) (data);
			*(FCU_WORD_PTR) DF_ADDRESS = ((uint16_t) (p[1]) << 8)
					| (uint16_t) (p[0]);
			while (FLASH.FSTATR.BIT.DBFULL != 0)
				;
			data += 2;
		}
		*(FCU_BYTE_PTR) (DF_ADDRESS) = 0xD0;
		wait_cnt = WAIT_MAX_DF_WRITE;
		while (FLASH.FSTATR.BIT.FRDY == 0) {
			wait_cnt--;
			if (wait_cnt == 0) {
				flash_reset();
				return FLASH_FAILURE;
			}
		}
		if ((FLASH.FSTATR.BIT.ILGLERR == 1) || (FLASH.FSTATR.BIT.PRGERR == 1)) {
			return FLASH_FAILURE;
		}
	} else {
		return FLASH_FAILURE;
	}
	return FLASH_SUCCESS;
}

/******************************************************************************
 * Function Name: R_FlashDataAreaBlankCheck
 * Description  : Performs a blank check on a specified data flash block
 *                NOTE1: This function does not have to execute from in RAM. It
 *                       must be in RAM though if FLASH_API_RX_CFG_ROM_BGO is
 *                       enabled and this function is called during a ROM P/E
 *                       operation.
 *                NOTE2: RX610 & RX62x support block and 8 byte checks
 *                       RX630/631/63N support block and 2 byte checks
 * Arguments    : address -
 *                    The address to check if is blank.
 *                    If the parameter 'size'=='BLANK_CHECK_8_BYTE',
 *                    this should be set to an 8-byte address boundary.
 *                    If the parameter 'size'=='BLANK_CHECK_ENTIRE_BLOCK',
 *                    this should be set to a defined Data Block Number
 *                    ('BLOCK_DB0', 'BLOCK_DB1', etc...) or an address
 *                    in the data flash block.  Either option will work.
 *                    If the parameter 'size'=='BLANK_CHECK_2_BYTE',
 *                    this should be set to a 2 byte address boundary.
 *                size -
 *                    This specifies if you are checking an 8-byte location,
 *                    2-byte location, or an entire block. You must set this
 *                    to either 'BLANK_CHECK_8_BYTE', 'BLANK_CHECK_2_BYTE',
 *                    or 'BLANK_CHECK_ENTIRE_BLOCK'.
 * Return Value : FLASH_BLANK -
 *                    (2 or 8 Byte check or non-BGO) Blank
 *                    (Entire Block & BGO) Blank check operation started
 *                FLASH_NOT_BLANK -
 *                    Not Blank
 *                FLASH_FAILURE -
 *                    Operation Failed
 *                FLASH_BUSY -
 *                    Another flash operation is in progress
 *                FLASH_ERROR_ADDRESS -
 *                    Invalid address
 *                FLASH_ERROR_BYTES -
 *                    Incorrect 'size' was submitted
 ******************************************************************************/
uint8_t R_FlashDataAreaBlankCheck(uint32_t address, uint8_t size) {
	return 0;
}
/******************************************************************************
 End of function  R_FlashDataAreaBlankCheck
 ******************************************************************************/

/******************************************************************************
 * Function Name: R_FlashDataAreaAccess
 * Description  : This function is used to allow read and program permissions
 *                to the Data Flash areas.
 *                NOTE1: This function does not have to execute from in RAM. It
 *                       must be in RAM though if FLASH_API_RX_CFG_ROM_BGO is
 *                       enabled and this function is called during a ROM P/E
 *                       operation.
 * Arguments    : read_en_mask -
 *                    Bitmasked value. Bits 0-3 represents each Data
 *                    Blocks 0-3 (respectively).
 *                    '0'=no Read access.
 *                    '1'=Allows Read by CPU
 *                write_en_mask -
 *                    Bitmasked value. Bits 0-3 represents each Data
 *                    Blocks 0-3 (respectively).
 *                    '0'=no Erase/Write access.
 *                    '1'=Allows Erase/Write by FCU
 * Return Value : none
 ******************************************************************************/
void R_FlashDataAreaAccess(uint16_t read_en_mask, uint16_t write_en_mask) {
//	/* Used for making sure select bits are not set. */
//	uint16_t temp_mask = 0x00FF;
//
//	/* Set Read access for the Data Flash blocks DB0-DB7 */
//	FLASH.DFLRE.WORD = (uint16_t) (0x2D00 | (read_en_mask & temp_mask));
//
//	/* Set Erase/Program access for the Data Flash blocks DB0-DB7 */
//	FLASH.DFLWE.WORD = (uint16_t) (0x1E00 | (write_en_mask & temp_mask));

}
/******************************************************************************
 End of function  R_FlashDataAreaAccess
 ******************************************************************************/

/******************************************************************************
 * Function Name: R_FlashGetStatus
 * Description  : Returns the current state of the flash
 *                NOTE1: This function does not have to execute from in RAM. It
 *                       must be in RAM though if FLASH_API_RX_CFG_ROM_BGO is
 *                       enabled and this function is called during a ROM P/E
 *                       operation.
 * Arguments    : none
 * Return Value : FLASH_SUCCESS -
 *                    Flash is ready to use
 *                FLASH_BUSY -
 *                    Flash is busy with another operation
 ******************************************************************************/
uint8_t R_FlashGetStatus(void) {
	/* Return flash status */
	if (g_flash_state == FLASH_READY) {
		return FLASH_SUCCESS;
	} else {
		return FLASH_BUSY;
	}
}
/******************************************************************************
 End of function  R_FlashGetStatus
 ******************************************************************************/

/******************************************************************************
 * Function Name: flash_grab_state
 * Description  : Attempt to grab the flash state to perform an operation
 *                NOTE1: This function does not have to execute from in RAM. It
 *                       must be in RAM though if FLASH_API_RX_CFG_ROM_BGO is
 *                       enabled and this function is called during a ROM P/E
 *                       operation.
 * Arguments    : new_state -
 *                    Which state to attempt to transition to
 * Return Value : FLASH_SUCCESS -
 *                    State was grabbed
 *                FLASH_BUSY -
 *                    Flash is busy with another operation
 ******************************************************************************/
static uint8_t flash_grab_state(flash_states_t new_state) {
	return FLASH_SUCCESS;
}
/******************************************************************************
 End of function  flash_grab_state
 ******************************************************************************/

/******************************************************************************
 * Function Name: flash_release_state
 * Description  : Release state so another flash operation can take place
 *                NOTE1: This function does not have to execute from in RAM. It
 *                       must be in RAM though if FLASH_API_RX_CFG_ROM_BGO is
 *                       enabled and this function is called during a ROM P/E
 *                       operation.
 * Arguments    : none
 * Return Value : none
 ******************************************************************************/
static void flash_release_state(void) {
//	/* Set current FCU mode to READ */
//	g_current_mode = READ_MODE;
//	/* Done with programming */
//	g_flash_state = FLASH_READY;
//
//	/* Release hold on lock */
//	R_BSP_HardwareUnlock(BSP_LOCK_FLASH);
}
/******************************************************************************
 End of function  flash_release_state
 ******************************************************************************/

/******************************************************************************
 * Function Name: R_FlashSetLockBitProtection
 * Description  : Enables or disables lock bit protection.
 *                NOTE1: This function does not have to execute from in RAM. It
 *                       must be in RAM though if FLASH_API_RX_CFG_ROM_BGO is
 *                       enabled and this function is called during a ROM P/E
 *                       operation.
 * Arguments    : lock_bit -
 *                    Boolean, whether to enable or disable lock bit
 *                    protection (true = enabled, false = disabled)
 * Return Value : FLASH_SUCCESS -
 *                    Operation Successful
 *                FLASH_BUSY -
 *                    Another flash operation is in progress
 ******************************************************************************/
uint8_t R_FlashSetLockBitProtection(uint32_t lock_bit) {
	/* Attempt to grab state */;
	if (flash_grab_state(FLASH_LOCK_BIT) != FLASH_SUCCESS) {
		/* Another operation is already in progress */
		return FLASH_BUSY;
	}

	/* Enable or disable? */
	g_lock_bit_protection = lock_bit;

	/* Release state */
	flash_release_state();

	/* Return success */
	return FLASH_SUCCESS;
}
/******************************************************************************
 End of function  R_FlashSetLockBitProtection
 ******************************************************************************/

/******************************************************************************
 * Function Name: rom_write
 * Description  : Write bytes to ROM Area Flash.
 *                NOTE: This function MUST execute from in RAM.
 * Arguments    : address -
 *                    ROM address of where to write to
 *                data -
 *                    Pointer to the data to write
 *                size -
 *                    The size of the data to write. Must be set to
 *                    either a supported write size of the MCU.
 * Return Value : FLASH_SUCCESS -
 *                    Operation Successful
 *                FLASH_FAILURE -
 *                    Operation Failed
 ******************************************************************************/
static uint8_t rom_write(uint32_t address, uint32_t data, uint32_t size) {
	/* If ROM programming is not enabled then do not compile this code as it is
	 not needed. */

	/* If ROM programming is not enabled then this function will always just
	 return FLASH_SUCCESS. This is okay because this function will never
	 actually be called. The API write function will return an error when
	 a ROM address is entered for programming. */

	/* Return FLASH_SUCCESS, operation successful */
	return FLASH_SUCCESS;
}
/******************************************************************************
 End of function  rom_write
 ******************************************************************************/

/******************************************************************************
 * Function Name: enter_pe_mode
 * Description  : Puts the FCU into program/erase mode.
 *                NOTE: This function MUST execute from in RAM for 'ROM Area'
 *                programming, but if you are ONLY doing Data Flash programming,
 *                this function can reside and execute in Flash.
 * Arguments    : flash_addr -
 *                    The programming/erasure address
 *                bytes -
 *                    The number of bytes you are writing (if you are writing).
 * Return Value : FLASH_SUCCESS -
 *                    Operation Successful
 *                FLASH_FAILURE -
 *                    Operation Failed
 ******************************************************************************/
static uint8_t enter_pe_mode(uint32_t flash_addr) {
	/* Used for timeout on FENTRYR write/read. */
	volatile int32_t wait_cnt;

	/* If FCU firmware has already been transferred to FCU RAM,
	 no need to do it again */
	if (!g_fcu_transfer_complete) {
		/* Initialise the FCU, and store operation resilt in result variable */
		/* Check if FCU initialisation was successful */
		if (flash_init() != FLASH_SUCCESS) {
			/* FCU initialisiation failed - return operation failure */
			return FLASH_FAILURE;
		}
	}

	/* FENTRYR must be 0x0000 before bit FENTRY0 or FENTRYD can be set to 1 */
	FLASH.FENTRYR.WORD = 0xAA00;

	/* Initialize timeout for FENTRYR being written. */
	wait_cnt = FLASH_FENTRYR_TIMEOUT;

	/* Read FENTRYR to ensure it has been set to 0. Note that the top byte
	 of the FENTRYR register is not retained and is read as 0x00. */
	while (0x0000 != FLASH.FENTRYR.WORD) {
		/* Wait until FENTRYR is 0 unless timeout occurs. */
		if (wait_cnt-- <= 0) {
			/* This should not happen. FENTRYR getting written to 0 should
			 only take 2-4 PCLK cycles. */
			return FLASH_FAILURE;
		}
	}

	/* Check if FCU mode is set to ROM PE */
	if (g_current_mode == ROM_PE_MODE) {
		/* Disable the FRDYI interrupt */
		FLASH.FRDYIE.BIT.FRDYIE = 0;

		/* Check which area of flash this address is in */
		if (flash_addr >= ROM_AREA_0) {
			/* Area 0 */
			/* Enter ROM PE mode for ROM Area 0 */
			FLASH.FENTRYR.WORD = 0xAA01;
		} else if ((flash_addr < ROM_AREA_0) && (flash_addr >= ROM_AREA_1)) {
			/* Area 1 */
			/* Enter ROM PE mode for ROM Area 1 */
			FLASH.FENTRYR.WORD = 0xAA02;
		} else if ((flash_addr < ROM_AREA_1) && (flash_addr >= ROM_AREA_2)) {
			/* Area 2 */
			/* Enter ROM PE mode for ROM Area 2 */
			FLASH.FENTRYR.WORD = 0xAA04;
		} else {
			/* Area 3 */
			/* Enter ROM PE mode for ROM Area 3 */
			FLASH.FENTRYR.WORD = 0xAA08;
		}

	}
	/* Check if FCU mode is set to data flash PE */
	else if (g_current_mode == FLD_PE_MODE) {
		/* Disable the FRDYI interrupt */
		FLASH.FRDYIE.BIT.FRDYIE = 0;

		/* Set FENTRYD bit(Bit 7) and FKEY (B8-15 = 0xAA) */
		FLASH.FENTRYR.WORD = 0xAA80;

		/*  First clear the FCU's status before doing Data Flash programming.
		 This is to clear out any previous errors that may have occured.
		 For example, if you attempt to read the Data Flash area
		 before you make it readable using R_FlashDataAreaAccess(). */
		data_flash_status_clear();

	}
	/* Catch-all for invalid FCU mode */
	else {
		/* Invalid value of 'g_current_mode' */
		return FLASH_FAILURE;
	}

	/* Enable Write/Erase of ROM/Data Flash */
	FLASH.FWEPROR.BYTE = 0x01;

	/* Check for FCU error */
	if ((FLASH.FSTATR.BIT.ILGLERR == 1) || (FLASH.FSTATR.BIT.ERSERR == 1)
			|| (FLASH.FSTATR.BIT.PRGERR == 1)
			|| (FLASH.FSTATR.BIT.FCUERR == 1)) {
		/* Return FLASH_FAILURE, operation failure */
		return FLASH_FAILURE;
	}

	/* Check to see if peripheral clock notification command is needed */
	if (g_fcu_pclk_command == 0) {
		/* Disable FCU interrupts, so interrupt will not trigger after
		 peripheral clock notification command */
		FLASH.FRDYIE.BIT.FRDYIE = 0;

		/* Inform FCU of flash clock speed, check if operation is succesful */
		if (notify_peripheral_clock((FCU_BYTE_PTR) flash_addr) != 0) {
			/* Return FLASH_FAILURE, operation failure */
			return FLASH_FAILURE;
		}

		/* No need to notify FCU of clock supplied to flash again */
		g_fcu_pclk_command = 1;
	}

	/* Return FLASH_SUCCESS, operation successful */
	return FLASH_SUCCESS;
}
/******************************************************************************
 End of function enter_pe_mode
 ******************************************************************************/

/******************************************************************************
 * Function Name: exit_pe_mode
 * Description  : Takes the FCU out of program/erase mode.
 *                NOTE: This function MUST execute from in RAM for 'ROM Area'
 *                programming, but if you are ONLY doing Data Flash
 *                programming, this function can reside and execute in Flash.
 * Arguments    : flash_addr -
 *                    The programming/erasure address
 * Return Value : none
 ******************************************************************************/
static void exit_pe_mode(uint32_t flash_addr) {
	/* Declare wait timer count variable */
	volatile int32_t wait_cnt;
	/* Declare address pointer */
	FCU_BYTE_PTR p_addr;

	/* Cast flash address so that it can be used as pointer and will be
	 accessed correctly. */
	p_addr = (FCU_BYTE_PTR) flash_addr;

	/* Set wait timer count duration */
	wait_cnt = WAIT_MAX_ERASE;

	/* Iterate while loop whilst FCU operation is in progress */
	while (FLASH.FSTATR.BIT.FRDY == 0) {
		/* Decrement wait timer count variable */
		wait_cnt--;

		/* Check if wait timer count value has reached zero */
		if (wait_cnt == 0) {
			/* Timeout duration has elapsed, assuming operation failure and
			 resetting the FCU */
			flash_reset();

			/* Break from the while loop prematurely */
			break;
		}
	}

	/* Check FSTATR and execute a status register clear command if needed */
	if ((FLASH.FSTATR.BIT.ILGLERR == 1) || (FLASH.FSTATR.BIT.ERSERR == 1)
			|| (FLASH.FSTATR.BIT.PRGERR == 1)) {

		/* Clear ILGLERR */
		if (FLASH.FSTATR.BIT.ILGLERR == 1) {
			/* FASTAT must be set to 0x10 before the status clear command
			 can be successfully issued  */
			if (FLASH.FASTAT.BYTE != 0x10) {
				/* Set the FASTAT register to 0x10 so that a status clear
				 command can be issued */
				FLASH.FASTAT.BYTE = 0x10;
			}
		}

		/* Send status clear command to FCU */
		*p_addr = 0x50;
	}

	/* Enter ROM Read mode */
	FLASH.FENTRYR.WORD = 0xAA00;

	/* Initialize timeout for FENTRYR being written. */
	wait_cnt = FLASH_FENTRYR_TIMEOUT;

	/* Read FENTRYR to ensure it has been set to 0. Note that the top byte
	 of the FENTRYR register is not retained and is read as 0x00. */
	while (0x0000 != FLASH.FENTRYR.WORD) {
		/* Wait until FENTRYR is 0 unless timeout occurs. */
		if (wait_cnt-- <= 0) {
			/* This should not happen. FENTRYR getting written to 0 should
			 only take 2-4 PCLK cycles. Could add a call to FlashError()
			 here if user wants to process this. */
			break;
		}
	}

	/* Disable the FRDYI interrupt */
	FLASH.FRDYIE.BIT.FRDYIE = 0;

	/* Flash write/erase disabled */
	FLASH.FWEPROR.BYTE = 0x02;

}
/******************************************************************************
 End of function  exit_pe_mode
 ******************************************************************************/

/******************************************************************************
 * Function Name: R_FlashErase
 * Description  : Erases an entire flash block.
 *                NOTE: This function MUST execute from in RAM for 'ROM Area'
 *                programming, but if you are ONLY doing Data Flash programming,
 *                this function can reside and execute in Flash.
 * Arguments    : block -
 *                    The block number to erase (BLOCK_0, BLOCK_1, etc...)
 * Return Value : FLASH_SUCCESS -
 *                    Operation Successful
 *                FLASH_FAILURE -
 *                    Operation Failed
 *                FLASH_BUSY -
 *                    Another flash operation is in progress
 ******************************************************************************/
uint8_t R_FlashErase(uint32_t block) {
	/* Declare address pointer */
	uint32_t p_addr;
	/* Declare erase operation result container variable */
	uint8_t result = FLASH_SUCCESS;

	/* Attempt to grab state */
	if (flash_grab_state(FLASH_ERASING) != FLASH_SUCCESS) {
		/* Another operation is already in progress */
		return FLASH_BUSY;
	}

	/* Erase Command Address */
	p_addr = g_flash_BlockAddresses[block];

	/* Do we want to erase a Data Flash block or ROM block? */
	if (block >= BLOCK_DB0) {
		/* Set current FCU mode to data flash PE */
		g_current_mode = FLD_PE_MODE;
	} else {
		/* Set current FCU mode to ROM PE */
		g_current_mode = ROM_PE_MODE;
	}

	/* Enter ROM PE mode, check if operation successful */
	if (enter_pe_mode(p_addr) != FLASH_SUCCESS) {
		/* Make sure part is in ROM read mode. */
		exit_pe_mode(p_addr);

		/* Release state */
		flash_release_state();

		/* Return FLASH_FAILURE, operation failure */
		return FLASH_FAILURE;
	}
	/* Only disable lock bit protection if user has specified to
	 do so earlier */
	if (g_lock_bit_protection == false) {
		/* Cancel the ROM Protect feature */
		FLASH.FPROTR.WORD = 0x5501;
	}

	/* NOTE:
	 Some RX MCUs (e.g. RX63N) actually has 1024 x 32 byte blocks instead of
	 the 16 x 2Kbyte blocks defined in port file. These are grouped
	 into 16 blocks to make it easier for the user to delete larger sections
	 of the data flash at once. The user can still delete individual blocks
	 but they will need to use the new flash erase function that takes
	 addresses instead of blocks. For reference, the 2KB blocks defined
	 are called 'fake' blocks. */
	if ( FLD_PE_MODE == g_current_mode) {

		/* Calculate how many bytes to erase */
		int32_t bytes_to_erase = (int32_t) (g_flash_BlockAddresses[BLOCK_DB1]
				- g_flash_BlockAddresses[BLOCK_DB0]);

		/* Erase real data flash blocks until the 'fake' block is erased .*/
		while (0 < bytes_to_erase) {

			/* Send FCU command to erase block */
			result = flash_erase_command((FCU_BYTE_PTR) p_addr);

			/* Advance pointer to next block */
			p_addr += DF_ERASE_BLOCK_SIZE;

			/* Subtract off bytes erased */
			bytes_to_erase -= DF_ERASE_BLOCK_SIZE;
		}
	} else {
		/* This is a ROM block erase */
		/* Send FCU command to erase block */
		result = flash_erase_command((FCU_BYTE_PTR) p_addr);
	}

	/* Leave Program/Erase Mode */
	exit_pe_mode(p_addr);

	/* Release state */
	flash_release_state();

	/* Return erase result */
	return result;
}
/******************************************************************************
 End of function  R_FlashErase
 ******************************************************************************/

#if defined(DF_GROUPED_BLOCKS)
/******************************************************************************
 * Function Name: R_FlashEraseRange
 * Description  : Erases blocks starting at an address and stopping when the
 *                number of bytes to erase has been reached.
 *                NOTE: This function is currently only for data flash blocks
 *                on RX MCUs.
 *                NOTE: This function MUST execute from in RAM for 'ROM Area'
 *                programming, but if you are ONLY doing Data Flash programming,
 *                this function can reside and execute in Flash.
 * Arguments    : start_addr -
 *                    The address of where to start erasing. Must be on
 *                    erase boundary.
 *                bytes -
 *                    The numbers of bytes to erase. Must be multiple of
 *                    erase size.
 * Return Value : FLASH_SUCCESS -
 *                    Operation Successful
 *                FLASH_FAILURE -
 *                    Operation Failed
 *                FLASH_ERROR_ALIGNED -
 *                    Flash address was not on correct boundary
 *                FLASH_BUSY -
 *                    Another flash operation is in progress
 *                FLASH_ERROR_BYTES -
 *                    Number of bytes did not match erase size
 *                FLASH_ERROR_ADDRESS -
 *                    Invalid address, this is only for DF
 ******************************************************************************/
uint8_t R_FlashEraseRange(uint32_t start_addr, uint32_t bytes) {
	uint8_t result = FLASH_SUCCESS;
	start_addr &= 0x00FFFFFF;
	if (start_addr >= DF_ADDRESS
			&& start_addr < (DF_ADDRESS + BSP_DATA_FLASH_SIZE_BYTES)) {
		if (bytes & (DF_ERASE_BLOCK_SIZE - 1)) {
			return FLASH_ERROR_BYTES;
		}
		if (start_addr & (DF_ERASE_BLOCK_SIZE - 1)) {
			return FLASH_ERROR_ALIGNED;
		}
	} else {
		return FLASH_ERROR_ADDRESS;
	}
	if (flash_grab_state(FLASH_ERASING) != FLASH_SUCCESS) {
		return FLASH_BUSY;
	}
	g_current_mode = FLD_PE_MODE;
	if (enter_pe_mode(start_addr) != FLASH_SUCCESS) {
		exit_pe_mode(start_addr);
		flash_release_state();
		return FLASH_FAILURE;
	}
	while (0 < bytes) {
		result = flash_erase_command((FCU_BYTE_PTR) start_addr);
		start_addr += DF_ERASE_BLOCK_SIZE;
		bytes -= DF_ERASE_BLOCK_SIZE;
	}
	exit_pe_mode(start_addr);
	flash_release_state();
	return result;
}
/******************************************************************************
 End of function  R_FlashEraseRange
 ******************************************************************************/
#endif /* defined(DF_GROUPED_BLOCKS) */

/******************************************************************************
 * Function Name: flash_erase_command
 * Description  : Issues the FCU command to erase a flash block
 *                NOTE: This function MUST execute from in RAM for 'ROM Area'
 *                programming, but if you are ONLY doing Data Flash programming,
 *                this function can reside and execute in Flash.
 * Arguments    : erase_addr -
 *                    An address in the block to be erased
 * Return Value : FLASH_SUCCESS -
 *                    Operation Successful
 *                FLASH_FAILURE -
 *                    Operation Failed
 ******************************************************************************/
static uint8_t flash_erase_command(FCU_BYTE_PTR const erase_addr) {
	volatile int32_t wait_cnt;
	uint8_t result = FLASH_SUCCESS;
	*erase_addr = 0x20;
	*erase_addr = 0xD0;
	wait_cnt = WAIT_MAX_ERASE / 1;	//良くない
	while (FLASH.FSTATR.BIT.FRDY == 0) {
		wait_cnt--;
		if (wait_cnt == 0) {
			flash_reset();
			return FLASH_FAILURE;
		}
	}
	if ((FLASH.FSTATR.BIT.ILGLERR == 1) || (FLASH.FSTATR.BIT.ERSERR == 1)) {
		result = FLASH_FAILURE;
	}
	return result;
}
/******************************************************************************
 End of function  flash_erase_command
 ******************************************************************************/

/******************************************************************************
 * Function Name: R_FlashWrite
 * Description  : Writes bytes into flash.
 *                NOTE: This function MUST execute from in RAM for 'ROM Area'
 *                programming, but if you are ONLY doing Data Flash programming,
 *                this function can reside and execute in Flash.
 * Arguments    : flash_addr -
 *                    Flash address location to write to. This address
 *                    must be on a program boundary (e.g. RX62N has
 *                    256-byte ROM writes and 8-byte DF writes).
 *                buffer_addr -
 *                    Address location of data buffer to write into flash.
 *                bytes -
 *                    The number of bytes to write. You must always pass a
 *                    multiple of the programming size (e.g. RX62N has
 *                    256-byte ROM writes and 8-byte DF writes).
 * Return Value : FLASH_SUCCESS -
 *                    Operation Successful
 *                FLASH_FAILURE -
 *                    Operation Failed
 *                FLASH_ERROR_ALIGNED -
 *                    Flash address was not on correct boundary
 *                FLASH_ERROR_BYTES -
 *                    Number of bytes did not match programming size of ROM or DF
 *                FLASH_ERROR_ADDRESS -
 *                    Invalid address
 *                FLASH_ERROR_BOUNDARY -
 *                    (ROM) Cannot write across flash areas.
 *                FLASH_BUSY -
 *                    Flash is busy with another operation
 ******************************************************************************/
uint8_t R_FlashWrite(uint32_t flash_addr, uint32_t buffer_addr, uint16_t bytes) {
	uint8_t result = FLASH_SUCCESS;
	uint32_t num_byte_to_write;
	flash_addr &= 0x00FFFFFF;

	if (flash_grab_state(FLASH_WRITING) != FLASH_SUCCESS) {
		return FLASH_BUSY;
	}
	g_current_mode = FLD_PE_MODE;
	if (enter_pe_mode(flash_addr) != FLASH_SUCCESS) {
		exit_pe_mode(flash_addr);
		flash_release_state();
		return FLASH_FAILURE2;
	}
	if (g_lock_bit_protection == false) {
		FLASH.FPROTR.WORD = 0x5501;
	}
	while (bytes) {
		num_byte_to_write = flash_get_program_size((uint32_t) bytes,
				flash_addr);
		if (g_current_mode == FLD_PE_MODE) {
			result = data_flash_write(flash_addr, buffer_addr,
					num_byte_to_write);
		} else {
			result = rom_write(flash_addr, buffer_addr, num_byte_to_write);
		}
		if (result != FLASH_SUCCESS) {
			break;
		}
		flash_addr += num_byte_to_write;
		buffer_addr += num_byte_to_write;
		bytes -= num_byte_to_write;
	}

	exit_pe_mode(flash_addr);
	flash_release_state();
	return result;
}
static uint8_t notify_peripheral_clock(FCU_BYTE_PTR flash_addr) {
	return FLASH_SUCCESS;
}
static void flash_reset(void) {
}
static uint32_t flash_get_program_size(uint32_t bytes, uint32_t flash_addr) {
	uint32_t num_byte_to_write = 0;
	if (g_current_mode == FLD_PE_MODE) {
		num_byte_to_write = DF_PROGRAM_SIZE_SMALL;
	} else {
		/* Set the next data transfer size to be smallest supported write. */
		num_byte_to_write = ROM_PROGRAM_SIZE;
	}
	return num_byte_to_write;
}

#ifndef  FLASH_API_RX_CFG_IGNORE_LOCK_BITS
uint8_t R_FlashProgramLockBit(uint32_t block) {
	/* Declare address pointer */
	FCU_BYTE_PTR p_addr;

	/* Declare operation result container variable */
	uint8_t result = FLASH_SUCCESS;

	/* Declare timer wait count variable */
	volatile int32_t wait_cnt;

	/* Attempt to grab state */
	if (flash_grab_state(FLASH_LOCK_BIT) != FLASH_SUCCESS) {
		/* Another operation is already in progress */
		return FLASH_BUSY;
	}

	/* Flash Command Address */
	p_addr = (FCU_BYTE_PTR) (g_flash_BlockAddresses[block]);

	/* Set FCU to ROM PE mode */
	g_current_mode = ROM_PE_MODE;

	/* Enter ROM PE mode, check if operation successful */
	if (enter_pe_mode((uint32_t) p_addr) != FLASH_SUCCESS) {
		/* Make sure part is in ROM read mode. */
		exit_pe_mode((uint32_t) p_addr);

		/* Release state */
		flash_release_state();

		/* Return FLASH_FAILURE, operation failure */
		return FLASH_FAILURE;
	}

	/* Send the FCU Command */
	*p_addr = 0x77;
	*p_addr = 0xD0;

	/* Set timeout wait counter value */
	wait_cnt = WAIT_MAX_ROM_WRITE;

	/* Wait until FCU operation finishes, or a timeout occurs */
	while (FLASH.FSTATR.BIT.FRDY == 0) {
		/* Decrement the wait counter */
		wait_cnt--;

		/* Check if the wait counter has reached zero */
		if (wait_cnt == 0) {
			/* Maximum timeout duration for writing to ROM has elapsed -
			 assume operation failure and reset the FCU */
			flash_reset();

			/* Return FLASH_FAILURE, operation failure */
			result = FLASH_FAILURE;
		}
	}

	/* Check for illegal command or programming errors */
	if ((FLASH.FSTATR.BIT.ILGLERR == 1) || (FLASH.FSTATR.BIT.PRGERR == 1)) {
		/* Return FLASH_FAILURE, operation failure */
		result = FLASH_FAILURE;
	}

	/* Leave Program/Erase Mode */
	exit_pe_mode((uint32_t) p_addr);

	/* Release state */
	flash_release_state();

	/* Return result of lock bit programming */
	return result;
}
/******************************************************************************
 End of function  R_FlashProgramLockBit
 ******************************************************************************/

/******************************************************************************
 * Function Name: R_FlashReadLockBit
 * Description  : Reads and returns the lock bit status for a ROM block
 *                NOTE: This function MUST execute from RAM
 * Arguments    : block -
 *                    Which ROM erasure block to read the lock bit of
 * Return Value : FLASH_LOCK_BIT_SET -
 *                    Lock bit was set
 *                FLASH_LOCK_BIT_NOT_SET -
 *                    Lock bit was not set
 *                FLASH_FAILURE -
 *                    Operation Failed
 *                FLASH_BUSY -
 *                    Another flash operation is in progress
 ******************************************************************************/
uint8_t R_FlashReadLockBit(uint32_t block) {
	/* Declare address pointer */
	FCU_BYTE_PTR p_addr;

	/* Declare operation result container variable */
	uint8_t result = FLASH_SUCCESS;

	/* Holds outcome of lock-bit read */
	uint8_t lock_bit;

	/* Attempt to grab state */;
	if (flash_grab_state(FLASH_LOCK_BIT) != FLASH_SUCCESS) {
		/* Another operation is already in progress */
		return FLASH_BUSY;
	}

	/* Flash Command Address */
	p_addr = (FCU_BYTE_PTR) (g_flash_BlockAddresses[block]);

	/* Set FCU to ROM PE mode */
	g_current_mode = ROM_PE_MODE;

	/* Enter ROM PE mode, check if operation successful */
	if (enter_pe_mode((uint32_t) p_addr) != FLASH_SUCCESS) {
		/* Make sure part is in ROM read mode. */
		exit_pe_mode((uint32_t) p_addr);

		/* Release state */
		flash_release_state();

		/* Return FLASH_FAILURE, operation failure */
		return FLASH_FAILURE;
	}

	/* Switch to ROM Lock-Bit Read Mode */
	*p_addr = 0x71;

	/* Check for illegal command */
	if (FLASH.FSTATR.BIT.ILGLERR == 1) {
		/* Return FLASH_FAILURE, operation failure */
		result = FLASH_FAILURE;
	} else {
		/* Read lock bit value */
		lock_bit = *p_addr;

		/* Set return value */
		if (lock_bit != 0x00) {
			/* Lock bit is not set */
			result = FLASH_LOCK_BIT_NOT_SET;
		} else {
			/* Lock bit is set */
			result = FLASH_LOCK_BIT_SET;
		}
	}

	/* Leave Program/Erase Mode */
	exit_pe_mode((uint32_t) p_addr);

	/* Release state */
	flash_release_state();

	/* Return result of lock bit programming */
	return result;
}
/******************************************************************************
 End of function  R_FlashReadLockBit
 ******************************************************************************/
#endif /* FLASH_API_RX_CFG_IGNORE_LOCK_BITS */

