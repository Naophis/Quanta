/*
 * Util.h
 *
 *  Created on: 2013/11/20
 *      Author: Naoto
 */

#ifndef UTIL_H_
#define UTIL_H_
char eigherRightLeft() {
	char res;
	char flag = false;
	LED_RIGHT = LED_LEFT = true;
	while (true) {
		if (!PushLeft) {
			res = Left;
			flag = true;
			LED_RIGHT = false;
			LED_LEFT = true;
		}
		if (!PushRight) {
			res = Right;
			flag = true;
			LED_RIGHT = true;
			LED_LEFT = false;
		}
		if (!PushCenter && flag) {
			break;
		}
	}
	LED_RIGHT = LED_LEFT = false;
	return res;
}

char updown() {
	volatile signed char mode = SEARCH;
	os_escape = 0;
	int interval = 25;
	while (1) {
		char swTop = !PushTop;
		char swBottom = !PushBottom;
		char swRight = !PushRight;
		char swLeft = !PushLeft;
		char swCenter = !PushCenter;

		if (mode == SEARCH) {
			led(1, 0, 0, 0);
		} else if (mode == SEARCH2) {
			led(0, 1, 0, 0);
		} else if (mode == RUN) {
			led(1, 1, 0, 0);
		} else if (mode == RUN2) {
			led(0, 0, 1, 0);
		} else if (mode == RUN3) {
			led(1, 0, 1, 0);
		} else if (mode == RUN4) {
			led(0, 1, 1, 0);
		} else if (mode == RUN5) {
			led(1, 1, 1, 0);
		} else if (mode == CONFIG) {
			led(0, 0, 0, 1);
		} else if (mode == CONFIG2) {
			led(1, 0, 0, 1);
		} else if (mode == CONFIG3) {
			led(0, 1, 0, 1);
		}

		if (swTop || swBottom) {
			if (swTop) {
				mode++;
				if (mode > CONFIG3) {
					mode = SEARCH;
				}
			}
			if (swBottom) {
				mode--;
				if (mode < 0) {
					mode = CONFIG3;
				}
			}
			for (int i = 0; i < 60000; i++)
				;
		}

		while (swTop || swBottom) {
			swTop = !PushTop;
			swBottom = !PushBottom;
			swRight = !PushRight;
			swLeft = !PushLeft;
			swCenter = !PushCenter;
		};

		if (swCenter) {
			os_escape = 1;
			decide(100);
			led(1, 1, 1, 1);
			cmt_wait(500);
			led(0, 0, 0, 0);
			cmt_wait(500);
			break;
		}
		cmt_wait(10);
	}
	return mode;
}

float getMaxVeloctiy() {
	char mode = updown();
	if (mode == 1) {
		return 2000;
	} else if (mode == 2) {
		return 2500;
	} else if (mode == 3) {
		return 3000;
	} else if (mode == 4) {
		return 3500;
	} else if (mode == 5) {
		return 4000;
	} else if (mode == 6) {
		return 4500;
	} else if (mode == 7) {
		return 4750;
	} else if (mode == 8) {
		return 5000;
	} else if (mode == 9) {
		return 5100;
	}
	return 2000;
}
char selectGoal();
void resetData2() {
	ang = 0;
	angle = 0;
	V_now = 0;
	W_now = 0;
	w_now = 0;
	acc = 0;
	alpha = 0;
	fail = 1;
	dia = 0;
	Velocity.error_now = 0;
	Velocity.error_old = 0;
	Velocity.error_delta = 0;
	Vr.error_now = 0;
	Vr.error_old = 0;
	Vr.error_delta = 0;
	Vl.error_now = 0;
	Vl.error_old = 0;
	Vl.error_delta = 0;
	Gy.error_now = 0;
	Gy.error_old = 0;
	Gy.error_delta = 0;
	Angle.error_now = 0;
	Angle.error_old = 0;
	Angle.error_delta = 0;
	ledOn = 1;
	mode_FF = 1;
	distance = 0;
}

void resetAllData() {
	ang = 0;
	angle = 0;
	V_now = 0;
	W_now = 0;
	w_now = 0;
	acc = 0;
	alpha = 0;
	fail = 1;
	dia = 0;
	Velocity.error_now = 0;
	Velocity.error_old = 0;
	Velocity.error_delta = 0;
	W_enc.error_now = 0;
	W_enc.error_old = 0;
	W_enc.error_delta = 0;
	Vr.error_now = 0;
	Vr.error_old = 0;
	Vr.error_delta = 0;
	Vl.error_now = 0;
	Vl.error_old = 0;
	Vl.error_delta = 0;
	Gy.error_now = 0;
	Gy.error_old = 0;
	Gy.error_delta = 0;
	Angle.error_now = 0;
	Angle.error_old = 0;
	Angle.error_delta = 0;
	ledOn = 1;
	mode_FF = 1;
	distance = 0;
	resetOmegaParam();
}
void clearLogs();
void mtu_start() {
	ledOn = 1;
	cmt_wait(10);
	resetAllData();
	GPT0.GTCCRA = GPT0.GTCCRC = GPT1.GTCCRA = GPT1.GTCCRC = 0;
	enablePWM = true;
	clearLogs();
	GPT.GTSTR.BIT.CST0 = GPT.GTSTR.BIT.CST1 = 1;
}
void mtu_stop() {
	enablePWM = false;
	cmt_wait(25);
	GPT0.GTCCRA = GPT0.GTCCRC = GPT1.GTCCRA = GPT1.GTCCRC = 0;
	V_now = 0;
	W_now = 0;
	resetGyroParam();
	resetAngleParam();
	resetOmegaParam();
	resetData2();
	cmt_wait(5);
	GPT.GTSTR.BIT.CST0 = GPT.GTSTR.BIT.CST1 = 0;
//	stopVacume();
	ledOn = 0;
}
void mtu_stop2() {
	V_now = 0;
	W_now = 0;
	acc = 0;
	alpha = 0;
	resetGyroParam();
	resetAngleParam();
	resetOmegaParam();
	resetAllData();
	cmt_wait(750);
	enablePWM = false;
	GPT0.GTCCRA = GPT0.GTCCRC = GPT1.GTCCRA = GPT1.GTCCRC = 0;
	cmt_wait(5);
	GPT.GTSTR.BIT.CST0 = GPT.GTSTR.BIT.CST1 = 0;
	PORTB.PODR.BIT.B1 = 0;
	PORTB.PODR.BIT.B3 = 0;
	stopVacume();
	ledOn = 0;
}
char failOutR = 0, failOutL = 0;
#define order 200
#define vOrder 50
#define wOrder 1
char senCheck = 0;
#define conflictOrder 2000
#define TIME_LIMIT 100
char failR2, failL2;
char dutyLimit, velocityLimit;
#define DIST_LIMIT 50
#define ERROR_LIMIT 1000
//char sw;
void failCheck(float Dr, float Dl) {
	char checkR = 0;
	char checkL = 0;
	if (RF_SEN1.now > conflictOrder || LF_SEN1.now > conflictOrder) {
		senCheck++;
	} else {
		senCheck = 0;
	}
	if (ABS((V_Enc.r + V_Enc.l) / 2 - V_now) > vOrder) {
		failOutR++;
		checkR++;
	}
	if (checkR == 0) {
		failOutR = 0;
	}
	if (checkL == 0) {
		failOutL = 0;
		velocityLimit = 0;
		dutyLimit = 0;
	}
	if (ABS(C.g) > 100) {
//		fail = 0;
	}
//	if (G.ref > 0) {
//		if (ABS(ang - angle) > PI * 30 / 180) {
//			fail = 0;
//		}
//	}
	if (failOutR >= TIME_LIMIT) {
		fail = 0;
	}

	if (failOutL >= TIME_LIMIT) {
		fail = 0;
	}

//	if (sw >= 100) {
//		fail = 0;
//	}

//	if (!fail) {
//		TPU0.TGRB = 0;
//	}
}

void batteryCheck() {
	cmt_wait(1000);

	if (battery > 10) {
		if (battery < 11.5) {
			while (Swich) {
				cmt_wait(250);
				LED1 = 1;
				cmt_wait(250);
				LED2 = 1;
				cmt_wait(250);
				LED3 = 1;
				cmt_wait(250);
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
			}
		}
	} else {
		if (battery < 7.5) {
			while (Swich) {
				cmt_wait(250);
				LED1 = 1;
				cmt_wait(250);
				LED2 = 1;
				cmt_wait(250);
				LED3 = 1;
				cmt_wait(250);
				LED1 = 0;
				LED2 = 0;
				LED3 = 0;
			}
		}
	}

	if (battery < 3.75) {
		while (Swich) {
			cmt_wait(250);
			LED1 = 1;
			cmt_wait(250);
			LED2 = 1;
			cmt_wait(250);
			LED3 = 1;
			cmt_wait(250);
			LED1 = 0;
			LED2 = 0;
			LED3 = 0;
		}
	}
}

float exchangeBlockDistance(float dist) {
	return 180.0 * dist;
}

void printAdData() {
	myprintf("%d %d %d %d %d %d %d\r\n", LF, LS, RS, RF, BATTERY);
}
char checkStablly();
float check_sen_error(void);
void gyroZeroCheck(char bool);
void printSensor() {
	ledOn = 1;
	sensingMode = AtackDia;
//	sensingMode = CtrlMode;

	gyroZeroCheck(true);
//	dia = 1;
	ang = 0;
	while (1) {

//		myprintf("%c[2J%c[0;0H", ESC, ESC); /* 画面消去 */
//		myprintf("battery=%f V\r\nGyro=%f\t%f\r\n", battery, settleGyro, G.ref);
//		myprintf("\t\t%f\t%f\r\n\t%f\t\t\t%f\r\n%f\t\t\t\t\t%f\r\n",
//				LS_SEN2.now, RS_SEN2.now, LS_SEN1.now, RS_SEN1.now, LF_SEN1.now,
//				RF_SEN1.now);
		myprintf(
				"{\"battery\":%f,\"gyro\":%f,\"LS1\":%d,\"RS1\":%d,\"LF1\":%d,\"RF1\":%d,\"LS2\":%d,\"RS2\":%d,\"BATT\":%d}\r\n",
				battery, settleGyro, (int) LS_SEN1.now, (int) RS_SEN1.now,
				(int) LF_SEN1.now, (int) RF_SEN1.now, (int) LS_SEN2.now,
				(int) RS_SEN2.now, BATTERY

				);
		cmt_wait(50);
		if (!Swich) {
			break;
		}
	}
	ledOn = 0;
}
void printSensor2() {
	ledOn = 1;
	sensingMode = AtackDia;
//	gyroZeroCheck(true);
//	dia = 1;
	while (1) {
		myprintf("%c[2J", ESC); /* 画面消去 */

//		myprintf("a"); /* 画面消去 */
		myprintf("%c[0;0H", ESC); /* 戦闘戻す*/
		myprintf("battery=%f V\r\n", battery);
		myprintf("Gyro=%f %f\r\n", settleGyro, G.ref);
//		myprintf("	 %f %f\r\n", LS_SEN2.now, RS_SEN2.now);
		myprintf("	%f %f\r\n", LS_SEN1.now, RS_SEN1.now);
		myprintf("%f %f\r\n", LF_SEN1.now, RF_SEN1.now);
		//		float error = 0;
//		error -= LS_SEN1.now - LS_SEN1.ref;
//		error += RS_SEN1.now - RS_SEN1.ref;
		myprintf("%f %f %f\r\n", check_sen_error(), Gy.error_now, Gy.error_old);
		myprintf("%f\r\n", tmpData);
		cmt_wait(100);
//		checkStablly();
		if (Swich == 0) {
			break;
		}
	}
	ledOn = 0;
}
void checkIsoukeisu() {
	while (1) {
		cmt_wait(100);
		myprintf("%d %d %d %d %d %d\r\n", MTU2.TCNT, MTU1.TCNT,
				(int) (distance), (int) V_Enc.l, (int) V_Enc.r,
				(int) (ang * 180 / PI));
	}
}
#define CHECK_ORDER_RIGHT 800
#define CHECK_ORDER_LEFT 800
char motionCheck() {
	int tmp = sensingMode;
	sensingMode = SearchMode;
	ledOn = 1;
	while (1) {
		if (LF_SEN1.now > CHECK_ORDER_LEFT || RF_SEN1.now > CHECK_ORDER_RIGHT) {
			LED1 = 1;
			cmt_wait(100);
			LED1 = 0;
			cmt_wait(100);
			LED1 = 1;
			cmt_wait(100);
			LED1 = 0;
			sensingMode = tmp;
			os_escape = 1;
			return 1;
		} else {
			LED3 = 1;
			cmt_wait(50);
			LED3 = 0;
			cmt_wait(50);
			LED3 = 1;
			cmt_wait(50);
			LED3 = 0;
		}
	}
	ledOn = 0;
}

float getZeroPoint() {
	float tempData = 0;
	int limit = 256;
	float result = 0;
	mpu = false;
	for (int i = 0; i < limit; i++) {
		tempData += MPU6500_Read_2byte(0x47);
		cmt_wait(1);
	}
	mpu = true;
	result = tempData / limit;
	tempData = 0;
	tempGyro2 = result;
	settlegyroData = result;
	return result;
}
void gyroZeroCheck(char bool) {
	if (bool) {
		motionCheck();
	}
	resetGyroParam();
	resetAllData();
	float tmpData = 0;
	while (true) {
		tmpData = getZeroPoint();
//		myprintf("%f\r\n", tmpData);
		if (ABS(tmpData) < 0.01) {
			while (!setupMpu6500())
				;
		} else if (ABS(tmpData) < 50) {
			break;
		}
//		break;
	}
	if (bool) {
		coin(100);
	}
	myprintf("%f\r\n", tmpData);
	G.ref = tmpData;
}
long er, el;
void keepZeroPoint() {
//	motionCheck();
//	cmt_wait(500);
	gyroZeroCheck(true);
	readGyroParam();
	readVelocityGain();
//	resetGyroParam();
	mtu_start();
//	positionControlValueFlg = 1;
	ang = 0;
	angle = 0;

	cmt_wait(500);
	sensingMode = AtackStraight;
	while (1) {
		myprintf("%c[2J", ESC); /* 画面消去 */
		myprintf("%c[0;0H", ESC); /* 戦闘戻す*/
		myprintf("battery=%f V\r\n", battery);
		myprintf("Gyro=%f\r\n", settleGyro);
		myprintf("	%f %f\r\n", LS_SEN1.now, RS_SEN1.now);
		myprintf("%f 		%f\r\n", LF_SEN1.now, RF_SEN1.now);
		myprintf("Duty:	%f	%f\r\n", Duty_l, Duty_r);
		myprintf("Velocity:	%f	%f\r\n", V_Enc.l, V_Enc.r);
		myprintf("angle:	%f\r\n", ang * 180 / PI);
		myprintf("distance:	%f\r\n", distance);
//		myprintf(
//				"{\"mode\":%d,\"battery\":%f,\"gyro\":%f,\"LS1\":%f,\"RS1\":%f,\"LF1\":%f,\"RF1\":%f}\r\n",
//				ledOn, battery, settleGyro, LS_SEN1.now, RS_SEN1.now,
//				LF_SEN1.now, RF_SEN1.now);
		cmt_wait(100);
//		myprintf("%f	%f	%d	%d	%f	%f\r\n", V_Enc.l, V_Enc.r, el, er, Duty_l,
//				Duty_r);
		if (Swich == 0) {
			break;
		}
		if (!fail) {
//			break;
		}
	}
	mtu_stop();
}
void keepZeroPoint2() {
	//	motionCheck();
	//	cmt_wait(500);
	gyroZeroCheck(true);
	readGyroParam();
	readVelocityGain();
	//	resetGyroParam();
	mtu_start();
	//	positionControlValueFlg = 1;
	ang = 0;
	angle = 0;

	cmt_wait(500);
	sensingMode = AtackStraight;
	while (1) {
		myprintf("%c[2J", ESC); /* 画面消去 */
		myprintf("%c[0;0H", ESC); /* 戦闘戻す*/
		myprintf("battery=%f V\r\n", battery);
		myprintf("Gyro=%f\r\n", settleGyro);
		myprintf("	%f %f\r\n", LS_SEN1.now, RS_SEN1.now);
		myprintf("%f 		%f\r\n", LF_SEN1.now, RF_SEN1.now);
		myprintf("Duty:	%f	%f\r\n", Duty_l, Duty_r);
		myprintf("Velocity:	%f	%f\r\n", V_Enc.l, V_Enc.r);
		myprintf("angle:	%f\r\n", ang * 180 / PI);
		myprintf("distance:	%f\r\n", distance);
		//		myprintf(
		//				"{\"mode\":%d,\"battery\":%f,\"gyro\":%f,\"LS1\":%f,\"RS1\":%f,\"LF1\":%f,\"RF1\":%f}\r\n",
		//				ledOn, battery, settleGyro, LS_SEN1.now, RS_SEN1.now,
		//				LF_SEN1.now, RF_SEN1.now);
		cmt_wait(100);
		//		myprintf("%f	%f	%d	%d	%f	%f\r\n", V_Enc.l, V_Enc.r, el, er, Duty_l,
		//				Duty_r);
		if (Swich == 0) {
			break;
		}
		if (!fail) {
			//			break;
		}
	}
	mtu_stop();
}
char existWall(int x, int y, int dir);
void printMap() {
	int i = 0;
	int j = 0;
	myprintf("\r\n");
	for (int j = 15; j >= 0; j--) {
		myprintf("+");
		for (int i = 0; i < 16; i++) {
			if (existWall(i, j, North)) {
				myprintf("----+");
			} else {
				myprintf("    +");
			}
		}
		myprintf("\r\n");
		for (i = 0; i < 16; i++) {
			if (existWall(i, j, West)) {
				myprintf("| ");
			} else {
				myprintf("  ");
			}
			myprintf("%2x ", dist[i][j]);
		}
		myprintf("|\r\n");
	}
	myprintf("+");
	i = 0;
	for (i = 0; i < 16; i++) {
		if (existWall(i, j, South)) {
			myprintf("----+");
		} else {
			myprintf("    +");
		}
	}
	myprintf("\r\n");
}
int direction(int Dir, int SLRB) {
	if (Dir == North) {
		if (SLRB == Left) {
			Dir = West;
			x--;
		} else if (SLRB == Right) {
			Dir = East;
			x++;
		} else if (SLRB == Straight) {
			Dir = North;
			y++;
		} else {
			Dir = South;
			y--;
		}
	} else if (Dir == East) {
		if (SLRB == Left) {
			Dir = North;
			y++;
		} else if (SLRB == Right) {
			Dir = South;
			y--;
		} else if (SLRB == Straight) {
			Dir = East;
			x++;
		} else {
			Dir = West;
			x--;
		}
	} else if (Dir == West) {
		if (SLRB == Left) {
			Dir = South;
			y--;
		} else if (SLRB == Right) {
			Dir = North;
			y++;
		} else if (SLRB == Straight) {
			Dir = West;
			x--;
		} else {
			Dir = East;
			x++;
		}
	} else if (Dir == South) {
		if (SLRB == Left) {
			Dir = East;
			x++;
		} else if (SLRB == Right) {
			Dir = West;
			x--;
		} else if (SLRB == Straight) {
			Dir = South;
			y--;
		} else {
			Dir = North;
			y++;
		}
	}
	return Dir;
}
void logOutPut() {
	while (Swich == 1)
		;
//	myprintf("%c[2J", ESC); /* 画面消去 */
//	myprintf("%c[0;0H", ESC); /* 戦闘戻す*/
	for (c = 0; c < L_Length; c++) {
		if (c > 500 && log5[c] == 0) {
//			break;
		}
		myprintf("%d %f %f %f", log1[c], logs2[c], log3[c], log4[c]);
		cmt_wait(1);
		myprintf(" %f %f %f %f", log5[c], log6[c], log7[c], log8[c]);
		cmt_wait(1);
		myprintf(" %f %f %f %f", log9[c], logs10[c], log11[c], log12[c]);
		cmt_wait(1);
		myprintf(" %f %f %f %f %f %f", log13[c], log14[c], log15[c], log16[c],
				log17[c], log18[c]);
		myprintf(" %f %f %f %f %f %f", log19[c], log20[c], log21[c], log22[c],
				log23[c], log24[c]);
		myprintf(" %f %f %f\r\n", log25[c], log26[c], log27[c]);
	}
}

void logOutput3() {
	while (Swich == 1)
		;
	for (c = 0; c < L_Length; c++) {
		if (c > 500 && log5[c] == 0) {
//			break;
		}
		myprintf("[%f,%f,%f,", log1[c], 0, log3[c]);
		cmt_wait(1);
		myprintf("%f,%f,%f,%f,", log4[c], log5[c], log6[c], log7[c]);
		cmt_wait(1);
		myprintf(",%f,%f,%f,%f", log8[c], log9[c], logs10[c], log11[c]);
		cmt_wait(1);
		myprintf(",%f,%f,%f]\r\n", log12[c], log13[c], log14[c]);
		cmt_wait(1);
	}
}
int updateMap[MAZE_SIZE][MAZE_SIZE];
#define VectorMax 1023
int clearMap(int x, int y, char isFull) {
	int tail = 0;
	for (char i = 0; i < MAZE_SIZE; i++) {
		for (char j = 0; j < MAZE_SIZE; j++) {
			dist[i][j] = 255;
			m[i][j].n = VectorMax;
			m[i][j].e = VectorMax;
			m[i][j].w = VectorMax;
			m[i][j].s = VectorMax;
			m[i][j].step = 0;
			m[i][j].v = 0;
			m[i][j].N1 = 0;
			m[i][j].E1 = 0;
			m[i][j].W1 = 0;
			m[i][j].S1 = 0;
			m[i][j].NE = 0;
			m[i][j].NW = 0;
			m[i][j].SE = 0;
			m[i][j].SW = 0;
			updateMap[i][j] = 0;
		}
	}

	for (int i = 0; i < Q_LENGTH; i++) {
		que[i][0] = 0;
		que[i][1] = 0;
		que[i][2] = 0;
	}
	int goalMass = isFull ? 2 : 1;

	for (int i = 0; i < goalMass; i++) {
		for (int j = 0; j < goalMass; j++) {
			if (!existWall(x + i, y + j, North)) {
				m[x + i][y + j].n = 0;
				que[tail][0] = (x + i) * 16 + (y + j);
				que[tail][1] = North;
				tail++;
				if (y + j < 15) {
					m[x + i][y + 1 + j].s = 0;
				}
			}
			if (!existWall(x + i, y + j, East)) {
				m[x + i][y + j].e = 0;
				que[tail][0] = (x + i) * 16 + (y + j);
				que[tail][1] = East;
				tail++;
				if (x + i < 15) {
					m[x + 1 + i][y + j].w = 0;
				}
			}
			if (!existWall(x + i, y + j, West)) {
				m[x + i][y + j].w = 0;
				que[tail][0] = (x + i) * 16 + (y + j);
				que[tail][1] = West;
				tail++;
				if (x + i > 0) {
					m[x - 1 + i][y + j].e = 0;
				}
			}
			if (!existWall(x + i, y + j, South)) {
				m[x + i][y + j].s = 0;
				que[tail][0] = (x + i) * 16 + (y + j);
				que[tail][1] = South;
				tail++;
				if (y + j > 0) {
					m[x + i][y - 1 + j].n = 0;
				}
			}
		}
	}
	dist[x][y] = 0;
	return tail;
}
void printPath() {
	myprintf("\r\n");
	for (short i = 0; i < pathLength; i++) {
		myprintf("%d:	%f	%d	%d\r\n", i, (0.5 * path_s[i] - 1), path_s[i],
				path_t[i]);
		if (path_t[i] == 0xff || path_t[i] == 0x00) {
			break;
		}
	}
}
void printRealPath() {
	myprintf("\r\n");
	for (short i = 0; i < pathLength; i++) {
		myprintf("path_s[%d]=%d;path_t[%d]=%d;\r\n", i, path_s[i], i,
				path_t[i]);
		if (path_t[i] == 0xff || path_t[i] == 0) {
			break;
		}
	}
}
#define Euler  2.7182818284
const float z = 1.0f;
float Et2(float t, float s, float N) {
	float P = 0;
	float Q = 0;
	t = t / s;
	P = powf((t - z), N - z);
	Q = P * (t - z);
	return -N * P / ((Q - z) * (Q - z)) * powf(expf(1), z + z / (Q - z)) / s;
}
//double Et2(double t, double s, double N) {
//	double P = 0;
//	double Q = 0;
//	t = t / s;
//	P = pow((t - z), N - z);
//	Q = P * (t - z);
//	return -N * P / ((Q - z) * (Q - z)) * pow(exp(1), z + z / (Q - z)) / s;
//}
char turnRoL(char a) {
	return a % 2 == 1 ? R : L;
}
void pathClear() {
	for (int i = 0; i < pathLength; i++) {
		path_s[i] = 0;
		path_t[i] = 0;
	}
}

float turnVelocity(char a) {
	if (a != Finish) {
		return v_sla[a];
	}
	return 2000;
}
float turnVelocitySlow(char a) {
	if (a != Finish) {
		return v_sla[a];
	}
	return v_sla[Normal];
}
#endif /* UTIL_H_ */
