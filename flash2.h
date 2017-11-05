///*
// * flash2.h
// *
// *  Created on: 2017/08/17
// *      Author: Naoto
// */
//
//#ifndef FLASH2_H_
//#define FLASH2_H_
//
//#define PROGRAM_SIZE 1024
//void initFcu() {
//	R_FlashDataAreaAccess(0xffff, 0xffff);
//}
//char trans_farm_;
//char start();
//void readMap(uint32_t flash_addr) {
//	initFcu();
//	uint32_t address;
//	address = flash_addr;
//	myprintf("\r\n");
//	for (int i = 0; i < 16; i++) {
//		for (int j = 0; j < 16; j++) {
//			map[i][j] = *(unsigned char *) (address + 16 * i + j);
////			myprintf("%2x,", (char) (wall[i][j]));
//			cmt_wait(1);
//		}
////		myprintf("\r\n");
//	}
//	printMap();
//}
//int wait_FRDY(int t) {
//	int cn = 0;
//	while (FLASH.FSTATR.BIT.FRDY == 0) {
//		cmt_wait(1); //1us　wait
//		cn++;
//		if (cn == t)
//			return 1;
//	}
//	return 0;
//}
//char saveFcu(uint32_t flash_addr) {
//	start();
//	unsigned char wall[16][16];
//	for (int i = 0; i < 16; i++) {
//		for (int j = 0; j < 16; j++) {
//			wall[i][j] = map[i][j];
//		}
//	}
////	char res = R_FLASH_Erase(flash_addr, 1);
////	uint8_t ret2 = R_FlashWrite(flash_addr, (uint32_t) wall, sizeof(wall));
////	if (FLASH_SUCCESS == ret2) {
////		return true;
////	} else {
////		myprintf("error code = %d\r\n", ret2);
////	}
//
//	return false;
//}
///**
// * ブロック単位で削除
// * @param brock
// * @return
// */
//char R_FLASH_EraseFlashBrock(uint8_t brock) {
////	FLASH.FRESETR.BIT.FRESET = 1;
//	if (FLASH.FASTAT.BYTE != 0x10) {
//		FLASH.FASTAT.BYTE = 0x10;
////		FLASH.FRESETR.BIT.FRESET = 1;
//	}
////	R_FLASH_EraseFlashAddr(flash_block_address_t[brock]);
//	uint8_t ret = R_FlashR_FLASH_Erase(brock);
//	return ret;
//}
//void R_FLASH_EraseAllFlashBlock() {
////	for (int i = FLASH_DF_BLOCK_0; i <= BLOCK_DB15; i++) {
////		R_FLASH_EraseFlashBrock(i);
////	}
//}
//
//char writeMap(uint32_t flash_addr) {
//	unsigned char wall[16][16] = { { 14, 6, 6, 5, 14, 7, 12, 6, 5, 12, 6, 4, 6,
//			6, 6, 5 },
//			{ 12, 5, 15, 10, 6, 6, 3, 15, 8, 1, 15, 11, 14, 7, 12, 1 }, { 9, 10,
//					6, 6, 6, 4, 4, 6, 3, 8, 4, 6, 6, 6, 3, 9 }, { 9, 12, 6, 6,
//					4, 1, 9, 12, 7, 9, 10, 4, 6, 6, 5, 9 }, { 9, 10, 6, 4, 3, 9,
//					9, 11, 15, 9, 15, 10, 4, 6, 3, 9 }, { 9, 13, 12, 2, 6, 3,
//					10, 6, 6, 2, 6, 6, 2, 5, 13, 9 }, { 9, 11, 9, 12, 5, 12, 4,
//					7, 14, 4, 5, 12, 5, 9, 11, 9 }, { 10, 5, 9, 9, 9, 9, 9, 12,
//					5, 9, 9, 9, 9, 9, 12, 3 }, { 15, 9, 8, 3, 9, 9, 11, 8, 3,
//					11, 9, 9, 10, 1, 9, 15 }, { 12, 1, 9, 15, 8, 3, 13, 9, 15,
//					13, 10, 1, 15, 11, 10, 5 }, { 9, 9, 9, 12, 3, 13, 9, 8, 5,
//					9, 13, 10, 4, 6, 4, 1 }, { 9, 10, 2, 2, 5, 11, 11, 9, 9, 11,
//					11, 12, 3, 15, 9, 9 }, { 8, 7, 12, 5, 9, 12, 5, 9, 9, 13,
//					13, 9, 12, 5, 10, 1 }, { 9, 15, 9, 9, 9, 9, 9, 8, 1, 8, 1,
//					9, 9, 9, 15, 9 }, { 8, 6, 1, 10, 3, 9, 9, 9, 9, 9, 9, 10, 3,
//					8, 6, 1 }, { 10, 6, 2, 6, 6, 3, 10, 3, 10, 3, 10, 6, 6, 2,
//					6, 3 } };
//	for (int i = 0; i < 16; i++) {
//		for (int j = 0; j < 16; j++) {
//			map[i][j] = wall[i][j];
//		}
//	}
//	return saveFcu(flash_addr);
//}
//
//char writeMap2(uint32_t flash_addr) {
//	unsigned char wall[16][16] = { { 14, 6, 6, 6, 6, 6, 6, 4, 4, 4, 6, 4, 4, 4,
//			6, 5 }, { 13, 12, 5, 12, 5, 12, 5, 9, 9, 10, 5, 9, 9, 10, 5, 9 }, {
//			8, 3, 10, 3, 10, 3, 10, 2, 3, 14, 2, 0, 2, 6, 0, 1 }, { 9, 12, 6, 5,
//			13, 12, 6, 4, 6, 4, 5, 10, 5, 12, 3, 9 }, { 8, 1, 12, 2, 0, 3, 12,
//			3, 12, 1, 8, 5, 10, 0, 6, 1 }, { 11, 11, 10, 6, 2, 7, 10, 4, 3, 11,
//			11, 8, 5, 10, 5, 9 }, { 12, 4, 7, 12, 4, 7, 12, 3, 14, 6, 6, 1, 9,
//			14, 0, 1 }, { 9, 10, 5, 9, 10, 5, 9, 12, 5, 12, 6, 3, 9, 12, 3, 9 },
//			{ 8, 5, 10, 1, 12, 0, 3, 8, 3, 10, 6, 5, 9, 8, 6, 1 }, { 11, 8, 7,
//					11, 11, 11, 12, 2, 5, 12, 6, 3, 9, 10, 5, 9 }, { 12, 3, 13,
//					12, 6, 4, 2, 4, 3, 10, 6, 5, 9, 14, 0, 1 }, { 8, 7, 8, 1,
//					12, 3, 12, 2, 5, 12, 6, 3, 9, 12, 3, 9 }, { 9, 12, 1, 8, 2,
//					4, 2, 6, 3, 8, 4, 7, 9, 10, 4, 1 }, { 8, 1, 8, 2, 4, 3, 12,
//					6, 5, 11, 10, 5, 9, 12, 1, 9 }, { 9, 8, 2, 4, 3, 12, 2, 4,
//					3, 13, 12, 3, 8, 1, 8, 3 }, { 10, 2, 6, 2, 6, 3, 14, 2, 6,
//					2, 2, 7, 11, 10, 2, 7 } };
//	for (int i = 0; i < 16; i++) {
//		for (int j = 0; j < 16; j++) {
//			map[i][j] = wall[i][j];
//		}
//	}
//	return saveFcu(flash_addr);
//}
//
////char saveFcuBlock(uint8_t brock) {
////	return saveFcu(g_flash_BlockAddresses[brock]);
////}
//void readMaze(long db) {
//	initFcu();
//
//	while (FLASH.FSTATR.BIT.FRDY == 0)
//		;
//	if (FLASH.FASTAT.BIT.CMDLK == 1) {
//		myprintf("command lock\r\n");
//	}
//	FLASH.FENTRYR.WORD = 0xAA00;
//	trans_farm_ = false;
//	uint32_t address = db;
//	for (char i = 0; i < MAZE_SIZE; i++) {
//		for (char j = 0; j < MAZE_SIZE; j++) {
//			map[i][j] = *(unsigned char *) (address + 16 * i + j);
////			myprintf("%2x", map[i][j]);
//		}
////		myprintf("\r\n");
//	}
//	printMap();
//}
//void readMaze2() {
////	initFcu();
////	uint32_t address = g_flash_BlockAddresses[BLOCK_DB1];
////	for (int i = 0; i < MAZE_SIZE; i++) {
////		for (int j = 0; j < MAZE_SIZE; j++) {
////			map[i][j] = *(unsigned char *) (address + 16 * i + j);
////		}
////	}
////	printMap();
//}
//
//void resetMap() {
//	uint32_t flash_addr = FLASH_DF_BLOCK_0;
//	R_FLASH_EraseFlashBrock(FLASH_DF_BLOCK_0, 4);
//	for (int i = 0; i < MAZE_SIZE; i++) {
//		for (int j = 0; j < MAZE_SIZE; j++) {
//			map[i][j] = 0;
//		}
//	}
////	uint8_t ret2 = R_FlashWrite(flash_addr, (uint32_t) map, sizeof(map));
////	if (FLASH_SUCCESS == ret2) {
////		oneUp(100);
////	} else {
////		coin(100);
////	}
//}
//
//char printBrankCheck() {
//	uint8_t ch;
//	char b = false;
////	for (int i = BLOCK_DB0; i <= BLOCK_DB15; i++) {
////		ch = R_FlashDataAreaBlankCheck(g_flash_BlockAddresses[i],
////				BLANK_CHECK_2_BYTE);
////		if (ch != 0) {
////			b = true;
////		}
////	}
//	return !b;
//}
//void resetFull() {
////	uint32_t flash_addr = g_flash_BlockAddresses[BLOCK_DB0];
////	printBrankCheck();
////	R_FLASH_EraseAllFlashBlock();
////	for (int i = 0; i < MAZE_SIZE; i++) {
////		for (int j = 0; j < MAZE_SIZE; j++) {
////			map[i][j] = 0;
////		}
////	}
////	uint8_t ret2 = R_FlashWrite(flash_addr, (uint32_t) map, sizeof(map));
////	if (FLASH_SUCCESS == ret2) {
////		oneUp(100);
////	} else {
////		coin(100);
////	}
//}
//char encorderOperation();
//
//#define STR(var) #var
//
//static const uint32_t data_flash_block = 64;     // データ・フラッシュのブロックサイズ
//static const uint32_t data_flash_size = 65536;  // データ・フラッシュの容量
//static const uint32_t data_flash_bank = 1024;   // データ・フラッシュのバンク数
//const uint32_t addrList[16] = { 0x00100000, 0x00100800, 0x00101000, 0x00101800,
//		0x00102000, 0x00102800, 0x00103000, 0x00103800, 0x00104000, 0x00104800,
//		0x00105000, 0x00105800, 0x00106000, 0x00106800, 0x00107000, 0x00107800 };
//
//enum error {
//	NONE, ADDRESS, TIMEOUT, LOCK, ILGLERR, PRGERR
//};
//enum mode {
//	RD, PE
//};
//typedef __evenaccess                                                                                     volatile uint8_t * FCU_BYTE_PTR;
//typedef __evenaccess                                                                                     volatile uint16_t * FCU_WORD_PTR;
//typedef __evenaccess                                                                                     volatile uint32_t * FCU_LONG_PTR;
//
//#define FACI_CMD_AREA  0x007E0000   ///< byte 書き込み
//#define FACI_CMD_AREA16  0x007E0000   ///< word(16) 書き込み
//#define F_FCLK 60000000
//enum mode mode_;
//enum error error_;
//
//void statusClear() {
//	myprintf("status clear\r\n");
//	if (FLASH.FSTATR.BIT.ILGLERR == 1) {
//		if (FLASH.FASTAT.BYTE != 0x10) {
//			FLASH.FASTAT.BYTE = 0x10;
//		}
//	}
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0x50;
//	trans_farm_ = false;
//}
//// 強制終了コマンド
//char turn_break_() {
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0xB3;
//	uint32_t cnt = 4800;
//	if (F_FCLK < 20000000)
//		cnt = 4800;
//	while (FLASH.FSTATR.BIT.FRDY == 0) {
//		--cnt;
//		if (cnt == 0)
//			break;
//	}
//	if (cnt == 0) {
//		myprintf("FACI 'turn_break_' timeout\r\n");
//		return false;
//	}
//
//	if (FLASH.FASTAT.BIT.CMDLK == 0) {
//		return true;
//	} else {
//		myprintf("FACI 'turn_break_' fail\r\n");
//		return false;
//	}
//}
//
//void turn_rd_() {
//	uint32_t n = 5;
//	while (FLASH.FSTATR.BIT.FRDY == 0) {
//		--n;
//		if (n == 0)
//			break;
//	}
//	if (n == 0 || FLASH.FASTAT.BIT.CMDLK != 0) {
//		turn_break_();
//	}
//
//	FLASH.FENTRYR.WORD = 0xAA00;
//
//	if (FLASH.FENTRYR.WORD != 0x0000) {
//		myprintf("FACI 'turn_rd_' fail\r\n");
//	}
//	mode_ = RD;
//}
//
//void turn_pe_() {
//	FLASH.FENTRYR.WORD = 0xAA80;
//	if (FLASH.FENTRYR.WORD != 0x0080) {
//		myprintf("FACI 'turn_pe_' fail\r\n");
//	}
//	mode_ = PE;
//}
//
///// FCUファームウェア格納領域 FEFF F000h～FEFF FFFFh 4Kバイト
///// FCURAM領域 007F 8000h～007F 8FFFh 4Kバイト
///// コンフィギュレーション設定領域 0012 0040h～0012 007Fh 64バイト
//char init_fcu_() {
//	if (trans_farm_)
//		return true;
//	FLASH.FAEINT.BIT.CFAEIE = 0;
//	FLASH.FAEINT.BIT.CMDLKIE = 0;
//	FLASH.FAEINT.BIT.DFAEIE = 0;
//	FLASH.FAEINT.BIT.ECRCTIE = 0;
//	IPR(FCU, FIFERR) = 0;
//	IEN(FCU, FIFERR) = 0;
//	IPR(FCU, FRDYI) = 0;
//	IEN(FCU, FRDYI) = 0;
//	if (FLASH.FENTRYR.WORD != 0) {
//		FLASH.FENTRYR.WORD = 0xAA00;
//		uint32_t wait = 4;
//		while (FLASH.FENTRYR.WORD != 0) {
//			if (wait > 0) {
//				--wait;
//			} else {
//				myprintf("FACI Tras FARM timeout\r\n");
//				return false;
//			}
//		}
//	}
//	FLASH.FCURAME.WORD = 0xC403;  // Write only
//	const uint32_t *src = (const uint32_t*) (0xFEFFF000);  // Farm master
//	uint32_t* dst = (uint32_t*) (0x007F8000);  // Farm section
//	for (uint32_t i = 0; i < (4096 / 4); ++i) {
//		*dst++ = *src++;
//	}
//	FLASH.FCURAME.WORD = 0xC400;
//	turn_pe_();
//	auto f = turn_break_();
//	if (f) {
//		turn_rd_();
//		trans_farm_ = true;
//	} else {
//		turn_break_();
//		myprintf("FACI Tras FARM lock\r\n");
//	}
//	return trans_farm_;
//}
//#define DF_SIZE 2
//static uint8_t data_flash_write2(uint32_t address, uint32_t data, uint32_t size) {
//	volatile int32_t wait_cnt;
//	volatile uint32_t n = 0;
//	FLASH.FPROTR.WORD = 0x5501;
//	FLASH.FSADDR.BIT.FSADDR = address;
//	if (DF_SIZE != size) {
//		return false;
//	}
//
//	size = (uint8_t) (size >> 1);
//	size = 4;
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0xE8;
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0x02;
//
//	const uint8_t* p = (const uint8_t*) (data);
//
//	myprintf("%d %d %d %d\r\n", p[0], p[1], p[2], p[3]);
//	*(FCU_WORD_PTR) FACI_CMD_AREA16 = ((uint16_t) (p[1]) << 8)
//			| (uint16_t) (p[0]);
//
//	while (FLASH.FSTATR.BIT.DBFULL != 0) {
//	}
//
//	*(FCU_WORD_PTR) FACI_CMD_AREA16 = ((uint16_t) (p[3]) << 8)
//			| (uint16_t) (p[2]);
//
//	while (FLASH.FSTATR.BIT.DBFULL != 0) {
//	}
//
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0xD0;
//	wait_cnt = 4800000;
//	while (FLASH.FSTATR.BIT.FRDY == 0) {
//		wait_cnt--;
//		if (wait_cnt == 0) {
//			turn_break_();
//			error_ = TIMEOUT;
//			myprintf("FSTATR 'data_flash_write' timeout\r\n");
//			return false;
//		}
//	}
//	if (FLASH.FSTATR.BIT.ILGLERR == 1) {
//		error_ = ILGLERR;
//		myprintf("ILGLERR 'data_flash_write' \r\n");
//		return false;
//	}
//	if (FLASH.FSTATR.BIT.PRGERR == 1) {
//		error_ = PRGERR;
//		myprintf("PRGERR 'data_flash_write' \r\n");
//		return false;
//	}
//
//	return true;
//}
////uint8_t R_FlashWrite(uint32_t flash_addr, uint32_t buffer_addr, uint16_t bytes) {
////	uint8_t result = true;
////	flash_addr &= 0x00FFFFFF;
////	if (error_ != NONE) {
////		statusClear();
////	}
////	if (mode_ != PE) {
////		turn_pe_();
////	}
////
////	FLASH.FCURAME.WORD = 0xC403;  // Write only
////	int i = 0;
////	while (bytes) {
////		result = data_flash_write(flash_addr, buffer_addr, DF_SIZE);
////		myprintf("%d:	%d\r\n", i++, result);
////		if (result != true) {
////			break;
////		}
////		flash_addr += DF_SIZE;
////		buffer_addr += DF_SIZE;
////		bytes -= DF_SIZE;
////	}
////
////	FLASH.FCURAME.WORD = 0xC400;  // Write only
////	return result;
////}
//// 4 バイト書き込み
//// org: align 4 bytes
//char write32_(const void* src, uint32_t org) {
//	FLASH.FPROTR.WORD = 0x5501;
//	FLASH.FSADDR.BIT.FSADDR = org;
//
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0xE8;
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0x02;
//
//	const uint8_t * p = (const uint8_t*) (src);
//	*(FCU_BYTE_PTR) FACI_CMD_AREA16 = ((uint16_t) (p[1]) << 8)
//			| (uint16_t) (p[0]);
//
//	while (FLASH.FSTATR.BIT.DBFULL != 0) {
//	}
//
//	*(FCU_BYTE_PTR) FACI_CMD_AREA16 = ((uint16_t) (p[3]) << 8)
//			| (uint16_t) (p[2]);
//
//	while (FLASH.FSTATR.BIT.DBFULL != 0) {
//	}
//
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0xD0;
//
//	// write (4 bytes): FCLK 20MHz to 60MHz max 1.7ms
//	//                  FCLK 4MHz max 3.8ms
//	// * 1.1
//	uint32_t cnt = 18700;
//	if (F_FCLK < 20000000)
//		cnt = 41800;
//	while (FLASH.FSTATR.BIT.FRDY == 0) {
//		--cnt;
//		if (cnt == 0)
//			break;
//	}
//	if (cnt == 0) {  // time out
//		turn_break_();
//		error_ = TIMEOUT;
//		myprintf("FACI 'write32_' timeout\r\n");
//		return false;
//	}
//
//	if (FLASH.FASTAT.BIT.CMDLK != 0) {
//		error_ = LOCK;
//		myprintf("FACI 'write32_' CMD Lock fail\r\n");
//		return false;
//	}
//
//	error_ = NONE;
//	return true;
//}
//
//// 4 バイト書き込み
//// org: align 4 bytes
//char write32_2(const void* src, uint32_t org) {
//	FLASH.FPROTR.WORD = 0x5501;
//	FLASH.FSADDR.BIT.FSADDR = org;
//
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0xE8;
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0x02;
//
//	const uint8_t *p = (const uint8_t*) (src);
//	*(FCU_BYTE_PTR) FACI_CMD_AREA16 = ((uint16_t) (p[1]) << 8)
//			| (uint16_t) (p[0]);
//
//	while (FLASH.FSTATR.BIT.DBFULL != 0) {
//	}
//
//	*(FCU_BYTE_PTR) FACI_CMD_AREA16 = ((uint16_t) (p[3]) << 8)
//			| (uint16_t) (p[2]);
//
//	while (FLASH.FSTATR.BIT.DBFULL != 0) {
//	}
//
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0xD0;
//
//	// write (4 bytes): FCLK 20MHz to 60MHz max 1.7ms
//	//                  FCLK 4MHz max 3.8ms
//	// * 1.1
//	uint32_t cnt = 1870;
//	if (F_FCLK < 20000000)
//		cnt = 4180;
//	while (FLASH.FSTATR.BIT.FRDY == 0) {
//		--cnt;
//		if (cnt == 0)
//			break;
//	}
//	if (cnt == 0) {  // time out
//		turn_break_();
//		error_ = TIMEOUT;
//		myprintf("FACI 'write32_' timeout\r\n");
//		return false;
//	}
//
//	if (FLASH.FASTAT.BIT.CMDLK != 0) {
//		error_ = LOCK;
//		myprintf("FACI 'write32_' CMD Lock fail\r\n");
//		return false;
//	}
//
//	error_ = NONE;
//	return true;
//}
//
////-----------------------------------------------------------------//
//char start() {
//	if (trans_farm_)
//		return false;  // ファームが既に転送済み
//	FLASH.FWEPROR.BIT.FLWE = 1;
//	FLASH.FPCKAR.WORD = 0x1E3C;
//	init_fcu_();
//	error_ = NONE;
//	return true;
//}
//
////-----------------------------------------------------------------//
///*!
// @brief  読み出し
// @param[in]	org	開始アドレス
// @return データ
// */
////-----------------------------------------------------------------//
////uint8_t read(uint32_t org) {
////	if (org >= data_flash_size) {
////		error_ = ADDRESS;
////		return 0;
////	}
////
////	if (mode_ != RD) {
////		turn_rd_();
////	}
////
////	error_ = NONE;
////
////	return (0x00100000 + org);
////}
////
//////-----------------------------------------------------------------//
/////*!
//// @brief  読み出し
//// @param[in]	org	開始アドレス
//// @param[out]	dst	先
//// @param[in]	len	バイト数
//// @return エラー無ければ「true」
//// */
//////-----------------------------------------------------------------//
////char read(uint32_t org, void* dst, uint32_t len) {
////	if (org >= data_flash_size) {
////		error_ = ADDRESS;
////		return false;
////	}
////	if ((org + len) > data_flash_size) {
////		len = data_flash_size - org;
////	}
////	if (mode_ != RD) {
////		turn_rd_();
////	}
////
////	const void* src = (const void*) (0x00100000 + org);
//////	std.memcpy(dst, src, len);
////
////	error_ = NONE;
////
////	return true;
////}
////-----------------------------------------------------------------//
///*!
// @brief  消去チェック
// @param[in]	org		開始アドレス
// @param[in]	len		検査長（バイト単位）
// @return 消去されていれば「true」（エラーは「false」）
// */
////-----------------------------------------------------------------//
//char R_FLASH_Erase_check(uint32_t org, uint32_t len) {
//	if (mode_ != PE) {
//		turn_pe_();
//	}
//	FLASH.FBCCNT.BYTE = 0x00;  // address increment
//	FLASH.FSADDR.BIT.FSADDR = org;
//	FLASH.FEADDR.BIT.FEADDR = org + len - 1;
//
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0x71;
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0xD0;
//
//	uint32_t cnt = 4800000;
//	if (F_FCLK < 20000000)
//		cnt = 4800000;
//	while (FLASH.FSTATR.BIT.FRDY == 0) {
//		--cnt;
//		if (cnt == 0)
//			break;
//	}
//	if (cnt == 0) {  // time out
//		turn_break_();
//		error_ = TIMEOUT;
//		myprintf("FACI 'R_FLASH_Erase_check' timeout\r\n");
//		return false;
//	}
//	if (FLASH.FASTAT.BIT.CMDLK == 0) {
//		return FLASH.FBCSTAT.BIT.BCST == 0;
//	} else {
//		error_ = LOCK;
//		myprintf("FACI 'R_FLASH_Erase_check' lock fail\r\n");
//		return false;
//	}
//}
//
//char isFormatting(long start, long end) {
//	FLASH.FBCCNT.BIT.BCDIR = 0;
//	FLASH.FSADDR.BIT.FSADDR = start;
//	FLASH.FEADDR.BIT.FEADDR = end;
//
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0x71;
//	*(FCU_BYTE_PTR) FACI_CMD_AREA = 0xD0;
//
//	uint32_t cnt = 1100;
//	if (F_FCLK < 20000000)
//		cnt = 1980;
//	while (FLASH.FSTATR.BIT.FRDY == 0) {
//		--cnt;
//		if (cnt == 0)
//			break;
//	}
//	if (cnt == 0) {  // time out
//		turn_break_();
//		error_ = TIMEOUT;
//		myprintf("FACI 'format check' timeout\r\n");
//		return false;
//	}
//
//	if (FLASH.FASTAT.BIT.CMDLK == 0) {
//		error_ = NONE;
//		return true;
//	} else {
//		error_ = LOCK;
//		myprintf("FACI 'format check' lock fail\r\n");
//		return false;
//	}
//}
//
//char write(uint32_t org, uint8_t data) {
//	uint8_t d = data;
//	return write2(org, &d, 1);
//}
//void printError() {
//	if (error_ == NONE) {
//		myprintf("ERROR_CODE = NONE\r\n");
//	} else if (error_ == ADDRESS) {
//		myprintf("ERROR_CODE = ADDRESS\r\n");
//	} else if (error_ == TIMEOUT) {
//		myprintf("ERROR_CODE = TIMEOUT\r\n");
//	} else if (error_ == LOCK) {
//		myprintf("ERROR_CODE = LOCK\r\n");
//	} else if (error_ == ILGLERR) {
//		myprintf("ERROR_CODE = ILGLERR \r\n");
//	} else if (error_ == PRGERR) {
//		myprintf("ERROR_CODE = PRGERR \r\n");
//	} else {
//		myprintf("ERROR_CODE = UNDEFINED \r\n");
//	}
//	myprintf("FPESTAT = %d \r\n", FLASH.FPESTAT.BIT.PEERRST);
//	myprintf("CMDLK = %d \r\n", FLASH.FASTAT.BIT.CMDLK);
//	myprintf("CFAE = %d \r\n", FLASH.FASTAT.BIT.CFAE);
//	myprintf("DFAE = %d \r\n", FLASH.FASTAT.BIT.DFAE);
//	myprintf("FRDY = %d \r\n", FLASH.FSTATR.BIT.FRDY);
//	myprintf("ILGLERR = %d \r\n", FLASH.FSTATR.BIT.ILGLERR);
//	myprintf("FCUERR = %d \r\n", FLASH.FSTATR.BIT.FCUERR);
//	myprintf("FRDTCT = %d \r\n", FLASH.FSTATR.BIT.FRDTCT);
//	myprintf("FLWEERR = %d \r\n", FLASH.FSTATR.BIT.FLWEERR);
//}
//void testFcu() {
//	unsigned char wall[16][16] = { { 14, 6, 6, 5, 14, 7, 12, 6, 5, 12, 6, 4, 6,
//			6, 6, 5 },
//			{ 12, 5, 15, 10, 6, 6, 3, 15, 8, 1, 15, 11, 14, 7, 12, 1 }, { 9, 10,
//					6, 6, 6, 4, 4, 6, 3, 8, 4, 6, 6, 6, 3, 9 }, { 9, 12, 6, 6,
//					4, 1, 9, 12, 7, 9, 10, 4, 6, 6, 5, 9 }, { 9, 10, 6, 4, 3, 9,
//					9, 11, 15, 9, 15, 10, 4, 6, 3, 9 }, { 9, 13, 12, 2, 6, 3,
//					10, 6, 6, 2, 6, 6, 2, 5, 13, 9 }, { 9, 11, 9, 12, 5, 12, 4,
//					7, 14, 4, 5, 12, 5, 9, 11, 9 }, { 10, 5, 9, 9, 9, 9, 9, 12,
//					5, 9, 9, 9, 9, 9, 12, 3 }, { 15, 9, 8, 3, 9, 9, 11, 8, 3,
//					11, 9, 9, 10, 1, 9, 15 }, { 12, 1, 9, 15, 8, 3, 13, 9, 15,
//					13, 10, 1, 15, 11, 10, 5 }, { 9, 9, 9, 12, 3, 13, 9, 8, 5,
//					9, 13, 10, 4, 6, 4, 1 }, { 9, 10, 2, 2, 5, 11, 11, 9, 9, 11,
//					11, 12, 3, 15, 9, 9 }, { 8, 7, 12, 5, 9, 12, 5, 9, 9, 13,
//					13, 9, 12, 5, 10, 1 }, { 9, 15, 9, 9, 9, 9, 9, 8, 1, 8, 1,
//					9, 9, 9, 15, 9 }, { 8, 6, 1, 10, 3, 9, 9, 9, 9, 9, 9, 10, 3,
//					8, 6, 1 }, { 10, 6, 2, 6, 6, 3, 10, 3, 10, 3, 10, 6, 6, 2,
//					6, 3 } };
//	for (int i = 0; i < 16; i++) {
//		for (int j = 0; j < 16; j++) {
//			map[i][j] = wall[i][j];
//		}
//	}
//	myprintf("init :%d\r\n", start());
//	cmt_wait(1000);
//	char res;
//	while (1) {
//		int mode = encorderOperation();
//		myprintf("%d \r\n", mode);
//		if (mode == 0) {
//			char res1 = R_FLASH_Erase(FLASH_DF_BLOCK_0, 1);
//			char res2 = R_FLASH_Erase(FLASH_DF_BLOCK_1, 1);
//			myprintf("delete result is %d ,%d \r\n", res1, res2);
//			myprintf("format is %d \r\n", res);
//			res = writeMap(FLASH_DF_BLOCK_0);
//			myprintf("res=%d \r\n", res);
//		} else if (mode == 1) {
//			readMaze(FLASH_DF_BLOCK_0);
//		} else if (mode == 2) {
////			char res1 = R_FLASH_Erase(g_flash_BlockAddresses[BLOCK_DB2]);
////			char res2 = R_FLASH_Erase(g_flash_BlockAddresses[BLOCK_DB3]);
////			myprintf("delete result is %d ,%d \r\n", res1, res2);
////			res = isFormatting(g_flash_BlockAddresses[BLOCK_DB2],
////					g_flash_BlockAddresses[BLOCK_DB4] - 1);
////			myprintf("format is %d \r\n", res);
////			res = writeMap2(g_flash_BlockAddresses[BLOCK_DB2]);
////			myprintf("res=%d \r\n", res);
//		} else if (mode == 3) {
////			readMaze(BLOCK_DB2);
//		}
//		if (res != 1) {
//			printError();
//			*(FCU_BYTE_PTR) FACI_CMD_AREA = 0xB3;
//			while (FLASH.FSTATR.BIT.FRDY == 0)
//				;
//			statusClear();
//			start();
//		}
//	}
//}
//
//#endif /* FLASH2_H_ */
