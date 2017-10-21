///*
// * Flash.h
// *
// *  Created on: 2017/08/14
// *      Author: Naoto
// */
//
//#ifndef FLASH_H_
//#define FLASH_H_
//
///**** Function Return Values ****/
///* Operation was successful */
//#define FLASH_SUCCESS           (0x00)
//#define FLASH_BLANK             (0x00)
//#define FLASH_ERROR_ALIGNED     (0x01)
//#define FLASH_NOT_BLANK         (0x01)
//#define FLASH_ERROR_BYTES       (0x02)
//#define FLASH_ERROR_ADDRESS     (0x03)
//#define FLASH_ERROR_BOUNDARY    (0x04)
//#define FLASH_BUSY              (0x05)
//#define FLASH_FAILURE           (0x06)
//#define FLASH_LOCK_BIT_SET      (0x07)
//#define FLASH_LOCK_BIT_NOT_SET  (0x08)
//#define BLANK_CHECK_ENTIRE_BLOCK     1
//
//#define READ_MODE               0
//#define ROM_PE_MODE             1
//#define FLD_PE_MODE             2
///* These flash states are used internal for locking purposes. */
//typedef enum {
//	FLASH_READY, FLASH_ERASING, FLASH_WRITING, FLASH_BLANKCHECK, FLASH_LOCK_BIT
//} flash_states_t;
//
//static uint8_t g_fcu_transfer_complete = 0;
//static uint8_t g_fcu_pclk_command = 0;
//static flash_states_t g_flash_state;
//static uint8_t g_current_mode;
//const uint32_t g_flash_BlockAddresses[16] = {
///* Caution. ID CODE(FFFFFFA0-FFFFFFAF) is excluded. */
//0x00100000, /* DB00 */
//0x00100800, /* DB01 */
//0x00101000, /* DB02 */
//0x00101800, /* DB03 */
//0x00102000, /* DB04 */
//0x00102800, /* DB05 */
//0x00103000, /* DB06 */
//0x00103800, /* DB07 */
//0x00104000, /* DB08 */
//0x00104800, /* DB09 */
//0x00105000, /* DB10 */
//0x00105800, /* DB11 */
//0x00106000, /* DB12 */
//0x00106800, /* DB13 */
//0x00107000, /* DB14 */
//0x00107800 /* DB15 */
//};
//#define DF_PROGRAM_SIZE_SMALL 2
//typedef __evenaccess                volatile uint32_t * FCU_BYTE_PTR;
//typedef __evenaccess                volatile uint16_t * FCU_WORD_PTR;
//typedef __evenaccess                volatile uint32_t * FCU_LONG_PTR;
//
//#define DF_ADDRESS              0x00100000
//#define DF_MASK                 0xFFFFF800
//#define DF_ERASE_BLOCK_SIZE     0x00000020
//#define DF_BLOCK_SIZE_LARGE     0x00000800
//#define DF_NUM_BLOCKS           16
//#define FLASH_CLOCK_HZ 240000000
//#define BSP_ICLK_HZ 60000000
//#define WAIT_MAX_DF_WRITE \
//        ((int32_t)(2000 * (50.0/(FLASH_CLOCK_HZ/1000000)))*(BSP_ICLK_HZ/1000000))
//
///* Flash intialisation function prototype */
//static uint8_t flash_init(void);
///* Enter PE mode function prototype */
//static uint8_t enter_pe_mode(uint32_t flash_addr);
///* Exit PE mode function prototype */
//static void exit_pe_mode(uint32_t flash_addr);
///* ROM write function prototype */
//static uint8_t rom_write(uint32_t address, uint32_t data, uint32_t size);
///* Data flash write function prototype */
//static uint8_t data_flash_write(uint32_t address, uint32_t data, uint32_t size);
///* Data flash status clear function prototype */
//static void data_flash_status_clear(void);
///* Notify peripheral clock function prototype */
//static uint8_t notify_peripheral_clock(FCU_BYTE_PTR flash_addr);
///* FCU reset function prototype */
//static void flash_reset(void);
///* Used to release flash state */
//static void flash_release_state(void);
///* Used to issue an erase command to the FCU */
//static uint8_t flash_erase_command(FCU_BYTE_PTR const erase_addr);
///* Used to get largest programming size that can be used. */
//static uint32_t flash_get_program_size(uint32_t bytes, uint32_t flash_addr);
//
//static uint8_t flash_init(void) {
//	volatile int32_t wait_cnt;
//
//	/* Disable FCU interrupts in FCU block */
//	FLASH.FAEINT.BIT.CFAEIE = 0;
//	FLASH.FAEINT.BIT.CMDLKIE = 0;
//	FLASH.FAEINT.BIT.DFAEIE = 0;
//	FLASH.FAEINT.BIT.ECRCTIE = 0;
//
//	IPR(FCU, FIFERR) = 0;
//	IEN(FCU, FIFERR) = 0;
//	IPR(FCU, FRDYI) = 0;
//	IEN(FCU, FRDYI) = 0;
//	if (FLASH.FENTRYR.WORD != 0x0000) {
//		FLASH.FENTRYR.WORD = 0xAA00;
//		wait_cnt = WAIT_MAX_DF_WRITE / 10000;
//		while (0x0000 != FLASH.FENTRYR.WORD) {
//			if (wait_cnt-- <= 0) {
//				return FLASH_FAILURE;
//			}
//		}
//	}
//
//	/* FCU firmware transfer complete, set the flag to 1 */
//	g_fcu_transfer_complete = 1;
//
//	/* Return no errors */
//	return FLASH_SUCCESS;
//}
//static void flash_release_state(void) {
//	g_current_mode = READ_MODE;
//	g_flash_state = FLASH_READY;
//}
///**
// * go to data flash memory P/E mode
// */
//void startPEMode() {
//	FLASH.FENTRYR.WORD = 0xAA08;
//}
//static uint8_t enter_pe_mode(uint32_t flash_addr) {
//	startPEMode();
//	return 0;
//}
//char isPEMode() {
//	return FLASH.FENTRYR.WORD == 0xAA08;
//}
///**
// * end to data flash memory P/E mode
// */
//void endPEMode() {
//	FLASH.FENTRYR.WORD = 0xAA00;
//}
//
//#define ERASE_1 0x20
//#define ERASE_2 0x20
//static uint8_t flash_erase_command(FCU_BYTE_PTR const erase_addr) {
//	volatile int32_t wait_cnt;
//	uint8_t result = FLASH_SUCCESS;
//
//	*erase_addr = 0x20;
//	*erase_addr = 0xD0;
//	wait_cnt = WAIT_MAX_DF_WRITE / 10000;	//良くない
//	while (FLASH.FSTATR.BIT.FRDY == 0) {
//		wait_cnt--;
//		if (wait_cnt == 0) {
//			flash_reset();
//			return FLASH_FAILURE;
//		}
//	}
//	if ((FLASH.FSTATR.BIT.ILGLERR == 1) || (FLASH.FSTATR.BIT.ERSERR == 1)) {
//		result = FLASH_FAILURE;
//	}
//	return result;
//}
//uint8_t R_FlashEraseRange(uint32_t start_addr, uint32_t bytes) {
//	uint8_t result = FLASH_SUCCESS;
//	start_addr &= 0x00FFFFFF;
//	g_current_mode = FLD_PE_MODE;
//	if (enter_pe_mode(start_addr) != FLASH_SUCCESS) {
//		exit_pe_mode(start_addr);
//		flash_release_state();
//		return FLASH_FAILURE;
//	}
//	while (0 < bytes) {
//		result = flash_erase_command((FCU_BYTE_PTR) start_addr);
//		start_addr += DF_ERASE_BLOCK_SIZE;
//		bytes -= DF_ERASE_BLOCK_SIZE;
//	}
//	exit_pe_mode(start_addr);
//	flash_release_state();
//	return result;
//}
//
//char blockErase(FCU_BYTE_PTR const erase_addr) {
//	volatile int32_t wait_cnt = 10000;
//	FLASH.FCPSR.BIT.ESUSPMD = 1; //erase優先
//	FLASH.FSADDR.BIT.FSADDR = erase_addr;
//	*erase_addr = 0x20;
//	*erase_addr = 0xD0;
//
//	while (FLASH.FSTATR.BIT.FRDY == 0) {
//		wait_cnt--;
//		if (wait_cnt == 0) {
//			flash_reset();
//			return FLASH_FAILURE;
//		}
//	}
//
//	if ((FLASH.FSTATR.BIT.ILGLERR == 1) || (FLASH.FSTATR.BIT.ERSERR == 1)) {
//		return FLASH_FAILURE;
//	}
//	return FLASH_SUCCESS;
//
//}
//
//void initFcu() {
//	FLASH.FCMDR.BIT.PCMDR;
//}
//
//char erase() {
//	startPEMode();
//	char res = blockErase(g_flash_BlockAddresses[0]);
//	endPEMode();
//	return res;
//}
//
//void protectOff() {
//	FLASH.FPROTR.WORD = 0x5501;
//}
//
//static void exit_pe_mode(uint32_t flash_addr) {
//	endPEMode();
//}
//static uint8_t data_flash_write(uint32_t address, uint32_t data, uint32_t size) {
//	volatile int32_t wait_cnt;
//	volatile uint32_t n = 0;
//	if (DF_PROGRAM_SIZE_SMALL == size) {
//		size = (uint8_t) (size >> 1);
//		*(FCU_BYTE_PTR) DF_ADDRESS = 0xE8;
//		*(FCU_BYTE_PTR) DF_ADDRESS = size;
//		while (n++ < size) {
//			*(FCU_WORD_PTR) address = *(uint16_t *) data;
//			data += 2;
//		}
//		*(FCU_BYTE_PTR) (DF_ADDRESS) = 0xD0;
//		wait_cnt = WAIT_MAX_DF_WRITE / 10000;
////		myprintf("wait_cnt=%d\r\n", WAIT_MAX_DF_WRITE);
//		while (FLASH.FSTATR.BIT.FRDY == 0) {
//			wait_cnt--;
//			if (wait_cnt == 0) {
//				flash_reset();
////				myprintf("timeout\r\n");
//				return FLASH_FAILURE;
//			}
//		}
//		if ((FLASH.FSTATR.BIT.ILGLERR == 1) || (FLASH.FSTATR.BIT.PRGERR == 1)) {
////			myprintf("illegal\r\n");
//			return FLASH_FAILURE;
//		}
//	} else {
//		return FLASH_FAILURE;
//	}
//	return FLASH_SUCCESS;
//}
//char write(uint32_t flash_addr, uint32_t buffer_addr, uint16_t bytes) {
//	uint8_t result = FLASH_SUCCESS;
//	uint32_t num_byte_to_write;
//	protectOff();
//	startPEMode();
//	FLASH.FSADDR.BIT.FSADDR = flash_addr;
//	myprintf("byteSize= %d\r\n", bytes);
//	g_current_mode = FLD_PE_MODE;
//	while (bytes) {
//		num_byte_to_write = flash_get_program_size((uint32_t) bytes,
//				flash_addr);
//		if (g_current_mode == FLD_PE_MODE) {
//			result = data_flash_write(flash_addr, buffer_addr,
//					num_byte_to_write);
//		}
//		if (result != FLASH_SUCCESS) {
//			break;
//		}
//
//		flash_addr += num_byte_to_write;
//		buffer_addr += num_byte_to_write;
//		bytes -= num_byte_to_write;
//	}
//	endPEMode();
//	return result;
//}
//static void flash_reset(void) {
//	flash_release_state();
//	FLASH.FENTRYR.WORD = 0xAA00;
//	FLASH.FWEPROR.BYTE = 0x02;
//}
//static uint32_t flash_get_program_size(uint32_t bytes, uint32_t flash_addr) {
//	return DF_PROGRAM_SIZE_SMALL;
//}
//
//#endif /* FLASH_H_ */
