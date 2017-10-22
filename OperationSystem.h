/*
 * OperationSystem.h
 *
 *  Created on: 2013/11/22
 *      Author: Naoto
 */

#ifndef OPERATIONSYSTEM_H_
#define OPERATIONSYSTEM_H_

void operation();
char encorderOperation();

void sensourCheck() {
	positionControlValueFlg = 1;
	ledOn = 1;
	resetGyroParam();
	resetAllData();
//	mtu_start();
	V_now = 0;
	while (Swich == 1) {
		myprintf("%d	%d	%d	%d	%d\n", (int) LS_SEN1.now, (int) LF_SEN1.now,
				(int) RF_SEN1.now, (int) RS_SEN1.now, (int) (Se.error_now));
		cmt_wait(100);
//		SCI_SCI_printf("%d %d	%d	%d\n", MTU2.TCNT, MTU1.TCNT, (int) V_Enc.l,
//				(int) V_Enc.r);
	}
	while (Swich == 0)
		;
	cmt_wait(500);
	ledOn = 0;
}
void testRun() {
	float velocity = 500;
	float accele = 2000;
	float diaccele = 2000;
	float vMax = 100;

	gyroZeroCheck(true);
	cmt_wait(500);
	if (velocity > 2000) {
		startVacume2(99);
		cmt_wait(200);
	}
	cc = 1;
	gyroOn = 1;
	V_now = 0;
	mtu_start();
//	dia = 1;
	realRun(velocity, accele, diaccele, 180.0 * 4.5, vMax);
//	wallOff(R);
//	running2(velocity, accele, 180, 1);
//	V_now = 0;
//	cmt_wait(1000);
//	resetAllData();

//	frontCtrl();
//	isOverFront();
//	resetAllData();
//	mtu_stop2();
//	ledOn = 1;

	mtu_stop2();
	logOutPut();
}
void testRun1(float v, float accele, float diaccele, float dist, float vM,
		char b1) {
	char check = 1;
	gyroZeroCheck(true);
	if (b1) {
		startVacume();
		cmt_wait(1000);
	}
	cc = 1;
	gyroOn = 1;
	V_now = 0;
	mtu_start();
	dia = 0;
	check = realRun(v, accele, diaccele, dist - 180, vM);
	if (check == 1) {
		running(100, -diaccele, 180, 1);
	}
	cc = 0;
	mtu_stop();
	stopVacume();
}
void testRun2(float v, float accele, float diaccele, float dist, float vM) {
	char check = 1;
	gyroZeroCheck(false);
	cc = 1;
	gyroOn = 1;
	V_now = 0;
	mtu_start();
	dia = 0;
	check = realRun(v, accele, diaccele, dist - 90, vM);
	if (check == 1) {
		running(100, -diaccele, 90, 1);
	}
	cc = 0;
	mtu_stop();
	stopVacume();
}
// search parm
//inputRadiusDatas(Normal, 44.5, 45.5, 108.75, 33, 9, 21.5, 0, 0);

void inputNaiperTurnAll500_2() {
	setPrms(Large, 90, 120.0, 16.0, 5.0, 0, 0, 0.1234884262084961, 4, 1000);
	setPrms3(Large, 14.0, 0);
	setPrms(Orval, 180, 86.25, 10.0, 20.0, 0, 0, 0.17751407623291016, 4, 1000);
	setPrms3(Orval, 13, 0);
	setPrms(Dia45, 45, 120, 10, 20.0, 60.75, 9, 0.06174468994140625, 4, 1000);
	setPrms3(Dia45, 10.5, 58.25);
	setPrms(Dia135, 135, 80.0, 32.0, 10, 26, 15.5, 0.1234884262084961, 4, 1000);
	setPrms3(Dia135, 19.5, 19.5);
	setPrms(Dia90, 90, 80.0, 14.0, 10.0, 0, 0, 0.08232593536376953, 4, 1000);
	setPrms3(Dia90, 12.5, 0);
	setPrms(Normal, 90, 43.5, 12.75, 28.0, 0, 0, 0.0943603515625, 2, 600);
	setPrms3(Normal, 17.5, 32.0);
}

void inputNaiperTurnAll1200() {
	setPrms(Large, 90, 120.0, 22.75, 5.0, 0, 0, 0.10290718078613281, 4, 1200);
	setPrms3(Large, 24.0, 0);
	setPrms(Orval, 180, 86.125, 35.0, 35.0, 0, 0, 0.14771461486816406, 4, 1200);
	setPrms3(Orval, 35, 0);
	setPrms(Dia45, 45, 120.0, 20.50, 20.0, 64.5, 1, 0.0517578125, 4, 1200);
	setPrms3(Dia45, 23, 58);
	setPrms(Dia135, 135, 83.0, 27, 15, 14.5, 5.5, 0.1067657470703125, 4, 1200);
	setPrms3(Dia135, 31.0, 13.5);
	setPrms(Dia90, 90, 80.0, 19.5, 10.0, 0, 0, 0.0686044692993164, 4, 1200);
	setPrms3(Dia90, 18.75, 0);
}

void inputNaiperTurnAll1500() {
	setPrms(Large, 90, 120.0, 19.0, 5.0, 0, 0, 0.08232593536376953, 4, 1500);
	setPrms3(Large, 16.0, 0);
	setPrms(Orval, 180, 86.125, 35.0, 25.0, 0, 0, 0.11817169189453125, 4, 1500);
	setPrms3(Orval, 35, 0);
	setPrms(Dia45, 45, 120, 15.5, 5, 55, 5, 0.04116344451904297, 4, 1500);
	setPrms3(Dia45, 11.750, 47);
	setPrms(Dia135, 135, 83, 19.0, 10, 5, 10, 0.08541297912597656, 4, 1500);
	setPrms3(Dia135, 23.0, 1.50);
	setPrms(Dia90, 90, 83.0, 12.0, 7.0, 0, 0, 0.056941986083984375, 4, 1500);
	setPrms3(Dia90, 7.0, 0);
}

void inputNaiperTurnAll1700() {
	setPrms(Large, 90, 120.0, 8.0, 2.0, 0, 0, 0.07264041900634766, 4, 1700);
	setPrms3(Large, 11.0, 0);
	setPrms(Orval, 180, 86.125, 35.0, 45.0, 0, 0, 0.10426902770996094, 4, 1700);
	setPrms3(Orval, 35, 0);
	setPrms(Dia45, 45, 120.0, 5.0, 2, 47, 1, 0.03632068634033203, 4, 1700);
	setPrms3(Dia45, 7.5, 47);
	setPrms(Dia135, 135, 80.0, 21.50, 16.5, 8.5, 12, 0.07264041900634766, 4,
			1700);
	setPrms3(Dia135, 20.5, 0);
	setPrms(Dia90, 90, 80.0, 5, 10.0, 0, 0, 0.048427581787109375, 4, 1700);
	setPrms3(Dia90, 5.0, 0);
}
void inputNaiperTurnAll1800() {
	setPrms(Large, 90, 120.0, 15, 15.0, 0, 0, 0.0686044692993164, 4, 1800);
	setPrms3(Large, 15.0, 0);
	setPrms(Orval, 180, 86.125, 35.0, 45.0, 0, 0, 0.09847640991210938, 4, 1800);
	setPrms3(Orval, 35, 0);
	setPrms(Dia45, 45, 105.0, 7, 30.0, 52.5, 2, 0.030014991760253906, 4, 1800);
	setPrms3(Dia45, 8.50, 54);
	setPrms(Dia135, 135, 80.0, 19.75, 15, 5, 25, 0.0686044692993164, 4, 1800);
	setPrms3(Dia135, 17.50, 0);
	setPrms(Dia90, 90, 80.0, 4.0, 15.0, 0, 0, 0.04573631286621094, 4, 1800);
	setPrms3(Dia90, 5, 0);
}
void inputNaiperTurnAll1900() {
	setPrms(Large, 90, 120.0, 1.0, 2.0, 0, 0, 0.06499385833740234, 4, 1900);
	setPrms3(Large, 0, 0);
	setPrms(Orval, 180, 86.125, 35.0, 45.0, 0, 0, 0.0932931900024414, 4, 1900);
	setPrms3(Orval, 35, 0);
	setPrms(Dia45, 45, 105.0, 0.0, 5, 48, 5, 0.02843475341796875, 4, 1900);
	setPrms3(Dia45, 2, 45.5);
	setPrms(Dia135, 135, 80, 16.0, 15, 0, 15, 0.06499385833740234, 4, 1900);
	setPrms3(Dia135, 15, 0);
	setPrms(Dia90, 90, 75.0, 1.0, 12.0, 0, 0, 0.04062175750732422, 4, 1900);
	setPrms3(Dia90, 1.0, 0);
}
void inputNaiperTurnAll2000() {
	setPrms(Large, 90, 110.0, 7, 25, 0, 0, 0.056598663330078125, 4, 2000);
	setPrms(Orval, 180, 86.125, 35.0, 25.0, 0, 0, 0.08862876892089844, 4, 2000);
	setPrms(Dia45, 45, 97.75, 2.5, 50.0, 42, 25, 0.0260, 4, 2000);
	setPrms(Dia135, 135, 80.0, 4.0, 15.0, 0, 25, 0.06174468994140625, 4, 2000);
	setPrms(Dia90, 90, 80.0, 1.5, 20.0, 0, 0, 0.04270648956298828, 4, 2000);
}
/**
 * 	t_radiusData large;
 t_radiusData orval;
 t_radiusData dia45;
 t_radiusData dia135;
 t_radiusData dia90;
 t_radiusData kojima;
 */
void testSlalom() {
	float vMax = 500;
	float maxVelocity = 500;
	float accele = 15000;
	float diaccele = 15000;
	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);
	mtu_start();
	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	mode_FF = 1;
	dia = 1;
	realRun(maxVelocity, accele, diaccele, 90 * 1, vMax);
	gyroOn = 0;
	logs = 0;
	time = 0;
	cc = 1;
	led(1, 1, 1);
	slalom3(R, Normal, vMax, vMax, 0);
	led(0, 0, 0);
	cc = 0;
	realRun(maxVelocity, accele, diaccele, 90.0 * 1.0, 50);
	C.g = 0;
	C.angles = 0;
	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	Angle.error_old = 0;
	mtu_stop();
	cmt_wait(500);
	logOutPut();
}
void sla3(float vMax) {
	float maxVelocity = vMax;
	float accele = 18000;
	float diaccele = 18000;
	inputNaiperTurnAll1500();
	char RorL = eigherRightLeft() == Right ? R : L;

	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);
	mtu_start();
	readGyroParam();
	readVelocityGain();

	if (vMax >= 1200) {
		startVacume2(95);
//		cmt_wait(500);
	}
	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	mode_FF = 1;
//	dia = 1;

//	changeMode(true);

	setPrms(Large, 90, 120.0, 16.0, 5.0, 0, 0, 0.1234884262084961, 4, 1000);
	setPrms3(Large, 14.0, 0);
	setPrms(Orval, 180, 86.25, 10.0, 20.0, 0, 0, 0.17751407623291016, 4, 1000);
	setPrms3(Orval, 13, 0);
	setPrms(Dia45, 45, 120, 10, 20.0, 60.75, 9, 0.06174468994140625, 4, 1000);
	setPrms3(Dia45, 10.5, 58.25);
	setPrms(Dia135, 135, 80.0, 32.0, 10, 26, 15.5, 0.1234884262084961, 4, 1000);
	setPrms3(Dia135, 19.5, 19.5);
	setPrms(Dia90, 90, 80.0, 14.0, 10.0, 0, 0, 0.08232593536376953, 4, 1000);
	setPrms3(Dia90, 12.5, 0);

	save();

	running2(maxVelocity, accele, 200, 1);
	gyroOn = 0;
	logs = 0;
	time = 0;
	cc = 1;
	logs = 0;

	wallOff(RorL);
	slalom3(RorL, Large, vMax, vMax, 0);
//	wallOff(RorL == R ? L : R);
//	slalom3(RorL == R ? L : R, Dia45, vMax, vMax, 0);
	cc = 0;
	realRun(vMax, accele, diaccele, 90.0 * 1, 50);
//	running(50, 0, 90, 0);
	mtu_stop2();
	stopVacume();
	cmt_wait(500);
	logOutPut();
}
void testNormalSlalom(float vMax) {
	float maxVelocity = vMax;
	float accele = 4000;
	float diaccele = 4000;
	inputNaiperTurnAll1500();
	char RorL = eigherRightLeft() == Right ? R : L;

	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);
	mtu_start();
	readGyroParam();
	readVelocityGain();

	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	mode_FF = 1;
	changeMode(true);
	inputNaiperTurnAll1500();

	setPrms(Normal, 90, 43.5, 12.75, 28.0, 0, 0, 0.0943603515625, 2, 600);
	setPrms3(Normal, 17.5, 32.0);

	save();

	running2(maxVelocity, accele, 360, 1);
//	realRun(vMax, accele, diaccele, 180.0 * 0.5, vMax);
	gyroOn = 0;
	logs = 0;
	time = 0;
	cc = 1;
	logs = 0;
//
//	frontCtrl();
//	resetAllData();
//	mtu_stop2();
//	ledOn = 1;
//	while (1) {
//		myprintf("%f %f %d %d %f %f  \r\n", LF_SEN1.now, RF_SEN1.now,
//				LF_SEN1.now < FRONT_CTRL_L, RF_SEN1.now < FRONT_CTRL_R,
//				FRONT_CTRL_L, FRONT_CTRL_R);
//		cmt_wait(10);
//	}
//		printSensor();
	slalom3(RorL, Normal, vMax, vMax, 0);
//	slalom3(RorL == R ? L : R, Normal, vMax, vMax, 0);
//	slalom3(RorL == R ? L : R, Normal, vMax, vMax, 0);
//	slalom3(RorL == R ? L : R, Normal, vMax, vMax, 0);
//	slalom3(RorL == R ? L : R, Normal, vMax, vMax, 0);
	cc = 0;
	realRun(vMax, accele, diaccele, 180.0 * 0.5, 50);
//	running(50, 0, 90, 0);
	mtu_stop2();
	stopVacume();
	cmt_wait(500);
	logOutPut();
}
void testWallOff(float vMax) {
	float maxVelocity = vMax;
	float accele = 2000;
	float diaccele = 2000;

	inputNaiperTurnAll1500();
	char RorL = eigherRightLeft() == Right ? R : L;

	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);
	mtu_start();
	readGyroParam();
	readVelocityGain();

	if (vMax > 1100) {
		startVacume2(70);
	}
	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	mode_FF = 1;
	dia = 1;

	changeMode(true);
//	realRun(maxVelocity, accele, diaccele, 90.0 * 1.22, vMax);
	running2(maxVelocity, accele, 180, 1);
	gyroOn = 0;
	logs = 0;
	time = 0;
	cc = 1;
	logs = 0;
	wallOff(RorL);
	cc = 0;
	V_now = 0;
	cmt_wait(1000);
//	realRun(vMax, accele, diaccele, 45.0 * 1, 50);
	mtu_stop2();
	stopVacume();
	cmt_wait(500);
	logOutPut();
}
void testWallOffSeach(float vMax) {
	float maxVelocity = vMax;
	float accele = 2000;
	float diaccele = 2000;

	inputNaiperTurnAll1500();

	motionCheck();
	cmt_wait(500);
	gyroZeroCheck(false);
	mtu_start();
	readGyroParam();
	readVelocityGain();

	ang = 0;
	angle = 0;
	Gy.error_old = 0;
	mode_FF = 1;
//	dia = 1;

	changeMode(true);
	realRun(maxVelocity, accele, diaccele, 180, vMax);
	cc = 1;
	running2(maxVelocity, accele, 200, 1);
	gyroOn = 0;
	logs = 0;
	time = 0;
	cc = 1;
	logs = 0;
	cc = 0;
	realRun(vMax, accele, diaccele, 90.0 * 1, 50);
	mtu_stop2();
	stopVacume();
	cmt_wait(500);
	logOutPut();
}

void testRoll(char r) {
	char a = 0;
	r = eigherRightLeft() == Right ? R : L;
	gyroZeroCheck(true);

	for (a = 0; a < 1 * 1; a++) {
		cmt_wait(150);
		cc = 1;
//		gyroRoll(L, 180, 60, 80);
//		gyroRoll(r, 180 * 2 * 1, 10, 15);
//		gyroRoll(r, 180 * 2 * 1, 60, 20);
//		gyroRollTest(r, 180 * 2 * 1, 15, 7);
		gyroRoll(r == R ? L : R, 180 * 2 * 1, 20, 25);
//		cmt_wait(250);
//		gyroZeroCheck(false);
		cc = 0;
	}
	logOutPut();
}

void searchMode(char X, char Y) {
	char x1 = 0, y1 = 0;
	char check = 0;
	x = 0;
	y = 0;
	next_dir = North;
	gyroZeroCheck(true);
	cmt_wait(500);
	now_dir = North;
//	check = Adachi2(X, Y, 1);
	if (check == 0) {
		return;
	}
	cmt_wait(500);
	roll(L, 180, 5, 30);
	x1 = x;
	y1 = y;
	now_dir = direction(now_dir, Back);
	next_dir = now_dir;
	x = x1;
	y = y1;
	cmt_wait(500);
	gyroZeroCheck(false);
//	Adachi(0, 0);
}

char isFullMaze(char X, char Y) {
	return ((X == 7 && Y == 7) || (X == 8 && Y == 7) || (X == 7 && Y == 8)
			|| (X == 8 && Y == 8));
}

void flushcheckQ() {
	for (int i = 0; i < checkQlength; i++) {
		checkQ[i] = 0;
	}
}

void printRealPath();
char makePath3(char goalX, char goalY, char isFull) {
	Dia2 = Dia - minus + 2;
	Dia3 = Dia - minus + 1;
	St2 = St1 - minus;
	St3 = St1 - minus - 1;
	x = 0;
	y = 0;
	now_dir = North;
	vetorPathCreate(goalX, goalY, isFull);
	drawChangePathRoot(goalX, goalY, isFull);
	largePath(true);
	diagonalPath(isFull, true);
	return countPathLength2();
}
char makePath4() {
	Dia2 = Dia - minus + 2;
	Dia3 = Dia - minus + 1;
	St2 = St1 - minus;
	St3 = St1 - minus - 1;
	vetorPathCreate(0, 0, false);
	largePath(true);
	diagonalPath(false, true);

	return true;
}
void makePath(char goalX, char goalY, char isFull) {
	flushcheckQ();
	printMap();
	if (cirquitMode == false) {
		minus = 3;
		int minus3 = makePath3(goalX, goalY, isFull);
	}
	printRealPath();
}
void makePath2() {
	flushcheckQ();
	if (cirquitMode == false) {
		minus = 3;
		makePath4();
	}
	printRealPath();
}
void testVacume() {
	gyroZeroCheck(true);
	cmt_wait(500);
	mtu_start();
	readVelocityGain();
	resetGyroParam();
	startVacume();
	cmt_wait(50000);
	stopVacume();
	mtu_stop();
}
void testVacume2(int duty) {
	gyroZeroCheck(true);
	cmt_wait(500);
	mtu_start();
	readVelocityGain();
	resetGyroParam();
	startVacume2(duty);
//	cmt_wait(15000);
	for (int i = 0; i < 200; i++) {
		myprintf("%d %f \r\n", (int) (FAN_AMP / battery * FAN_CYCLE), battery);
		cmt_wait(100);

	}
	stopVacume();
	mtu_stop();
}
char switchOn() {
	return !Swich;
}

char modeCheck() {
	char swTop = !PushTop;
	char swBottom = !PushBottom;
	char swRight = !PushRight;
	char swLeft = !PushLeft;
	char swCenter = !PushCenter;
	return swTop + swBottom * 2 + swLeft * 4 + swRight * 8 + swCenter * 16;
}
char encorderOperation() {
	volatile signed char mode = SEARCH;
	os_escape = 0;
	MTU1.TCNT = 4500;
	MTU2.TCNT = 30000;
	MTU.TSTRA.BIT.CST4 = 0;
	while (1) {
		char swTop = !PushTop;
		char swBottom = !PushBottom;
		char swRight = !PushRight;
		char swLeft = !PushLeft;
		char swCenter = !PushCenter;

		if (mode == SEARCH) {
			led(1, 0, 0);
		} else if (mode == SEARCH2) {
			led(0, 1, 0);
		} else if (mode == RUN) {
			led(1, 1, 0);
		} else if (mode == RUN2) {
			led(0, 0, 1);
		} else if (mode == RUN3) {
			led(1, 0, 1);
		} else if (mode == RUN4) {
			led(0, 1, 1);
		} else if (mode == RUN5) {
			led(1, 1, 1);
		} else if (mode == CONFIG) {
			mode = CONFIG;
			led(1, 0, 0);
			cmt_wait(50);
			led(0, 0, 0);
			cmt_wait(50);
			led(1, 0, 0);
			cmt_wait(50);
		} else if (mode == CONFIG2) {
			led(0, 1, 0);
			cmt_wait(50);
			led(0, 0, 0);
			cmt_wait(50);
			led(0, 1, 0);
			cmt_wait(50);
		} else if (mode == CONFIG3) {
			led(0, 0, 1);
			cmt_wait(50);
			led(0, 0, 0);
			cmt_wait(50);
			led(0, 0, 1);
			cmt_wait(50);
		} else if (mode == CONFIG4) {
			led(0, 0, 0);
			LED6 = true;
		}
		myprintf("%d %d %d %d %d	%d\r\n", swTop, swLeft, swRight, swBottom,
				swCenter, mode);
		cmt_wait(10);
		if (swTop || swBottom) {
			if (swTop) {
				mode++;
				if (mode > CONFIG4) {
					mode = 0;
				}
			}
			if (swBottom) {
				mode--;
				if (mode < 0) {
					mode = CONFIG4;
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
			decide(250);
			led(1, 1, 1);
			cmt_wait(500);
			led(0, 0, 0);
			cmt_wait(500);
			break;
		}
		cmt_wait(10);
	}
	os_escape = true;
	MTU.TSTRA.BIT.CST4 = 1;
	return mode;
}

void cirquitRun() {
	cirquit();
}
void FF_print() {
	mtu_start();
	while (1) {
		cmt_wait(50);
		myprintf("%d %d \n", (int) (FF_calc(L) * 1000),
				(int) (FF_calc(R) * 1000));
	}
	mtu_stop();
}

#define goal7 10000
#define goal8 25000

char selectGoal() {
	char goal = 0;
	os_escape = 0;
	MTU1.TCNT = 4500;
	MTU2.TCNT = 30000;

	MTU.TSTRA.BIT.CST4 = 0;
	while (1) {
		if (MTU1.TCNT < goal7) {
			LED1 = 1;
			LED6 = 0;
			goal = 7;
		} else if (MTU1.TCNT < goal8) {
			LED1 = 0;
			LED6 = 1;
			goal = 8;
		}
		if (MTU1.TCNT > OVERFLOW) {
			MTU1.TCNT = 5000;
		}
		if (MTU1.TCNT < UNDERFLOW) {
			MTU1.TCNT = 15000;
		}
		if (!Swich) {
			os_escape = 1;
			LED1 = 1;
			LED2 = 1;
			LED3 = 1;
			cmt_wait(500);
			LED1 = 0;
			LED2 = 0;
			LED3 = 0;
			cmt_wait(500);
			break;
		}
	}
	led(0, 0, 0);
	if (goal == 7) {
		coin(250);
		cmt_wait(100);
	}
	if (goal == 8) {
		coin(250);
		cmt_wait(100);
		coin(250);
		cmt_wait(100);
	}

	MTU.TSTRA.BIT.CST4 = 1;
	return goal;
}

void printCheckMapping() {
	myprintf("\r\n");
	for (int i = 0; i < 255; i++) {
		int x = (checkQ[i] & 0xf0) >> 4;
		int y = checkQ[i] & 0x0f;
		myprintf("(%2x,%2x)\r\n", x, y);
		if (x == 0 && y == 0) {
			break;
		}
	}
	myprintf("\r\n");
	for (int j = 15; j >= 0; j--) {
		for (int i = 0; i < 16; i++) {
			myprintf("%2x, ", checkMap[i][j]);
		}
		myprintf("\r\n");
	}
	myprintf("\r\n");
}
volatile void action2(char mode, char goalX, char goalY) {
	char isFull = isFullMaze(goalX, goalY);
	if (mode == SEARCH) {
		if (!motionCheck()) {
			return;
		}
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1900();
		save();
		inputNaiperTurnAll1500();
		save2();
		runForPath(4700, 20000, 22000);
	} else if (mode == SEARCH2) {
		if (!motionCheck()) {
			return;
		}
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1900();
		save();
		inputNaiperTurnAll1500();
		save2();
		runForPath(4800, 18000, 22000);
	} else if (mode == RUN) {
		aheadTears(200);
		if (!motionCheck()) {
			return;
		}
		inputNaiperTurnAll1900();
		save();
		inputNaiperTurnAll1500();
		save2();
		runForPath(4900, 18000, 22000);
	} else if (mode == RUN2) {
		aheadTears(200);
		if (!motionCheck()) {
			return;
		}
		inputNaiperTurnAll1900();
		setPrms(Orval, 180, 86.125, 35.0, 25.0, 0, 0, 0.08862876892089844, 4,
				2000);
		setPrms3(Orval, 35, 0);
		save();
		inputNaiperTurnAll1500();
		save2();
		runForPath(4900, 18000, 22000);
	} else if (mode == RUN3) {
		aheadTears(200);
		if (!motionCheck()) {
			return;
		}
		inputNaiperTurnAll1900();
		setPrms(Orval, 180, 86.125, 35.0, 25.0, 0, 0, 0.08862876892089844, 4,
				2000);
		setPrms3(Orval, 35, 0);
		save();
		inputNaiperTurnAll1500();
		save2();
		runForPath(5000, 18000, 22000);
	} else if (mode == RUN4) {
//		if (!motionCheck()) {
//			return;
//		}
	} else if (mode == RUN5) {
//		if (!motionCheck()) {
//			return;
//		}
	} else if (mode == CONFIG) {
//		if (!motionCheck()) {
//			return;
//		}
	} else if (mode == CONFIG2) {
	} else if (mode == CONFIG3) {
	} else if (mode == CONFIG4) {
	}
	mtu_stop2();
	TRANSAM = false;
	LED6 = false;
	LED1 = false;
}

char action(char mode, char goalX, char goalY, char fastMode) {
	char isFull = isFullMaze(goalX, goalY);
	char m2;
	if (mode == SEARCH2) {
		m2 = selectGoal() == 7 ? Oufuku : Kata;
	}
	if (mode == SEARCH || mode == SEARCH2) {
//		Sen.Kp = 0.01;
//		Sen.Ki = 0.001;
//		Sen.Kp = 0.01;
//		Sen.Ki = 0.00125;
	} else {
//		Sen.Kp = 0.0175;
//		Sen.Ki = 0.0025;

//		Sen.Kp = 0.02;
//		Sen.Ki = 0.00275;
	}
	if (fastMode == 0) {
		if (!motionCheck()) {
			return 0;
		}
	}

	if (mode == SEARCH) {
		gyroKeepFlg = 0;
		now_dir = North;
		next_dir = North;
		x = 0;
		y = 0;
		cirquitMode = 0;
		inputNaiperTurnAll500_2();
		save();
		pathClear();
		char res = Adachi2(goalX, goalY, Zentansaku, isFull);
		return res;
	} else if (mode == SEARCH2) {
		gyroKeepFlg = 0;
		now_dir = North;
		next_dir = North;
		x = 0;
		y = 0;
		cirquitMode = 0;
		inputNaiperTurnAll500_2();
		save();
		pathClear();
		char res = Adachi2(goalX, goalY, m2, isFull);
		return res;
	} else if (mode == RUN) {
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1200();
		save();
		inputNaiperTurnAll1800();
		save2();
		char check = runForPath(3500, 18000, 18000);
	} else if (mode == RUN2) {
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1200();
		save();
		inputNaiperTurnAll1800();
		save2();
		char check = runForPath(4000, 20000, 18000);
	} else if (mode == RUN3) {
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1200();
		save();
		inputNaiperTurnAll1800();
		save2();
		char check = runForPath(4500, 20000, 18000);
	} else if (mode == RUN4) {
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1200();
		save();
		inputNaiperTurnAll1800();
		save2();
		char check = runForPath(5000, 20000, 18000);
	} else if (mode == RUN5) {
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1200();
		save();
		inputNaiperTurnAll1800();
		save2();
		char check = runForPath(4500, 20000, 18000);
	} else if (mode == CONFIG) {
		makePath(goalX, goalY, isFull);
		inputNaiperTurnAll1200();
		save();
		inputNaiperTurnAll1800();
		save2();
		char check = runForPath(4500, 20000, 18000);
	} else if (mode == CONFIG2) {
		oneUp(250);
//		TRANSAM = true;
		LED6 = true;
		LED1 = true;
		testVacume2(10);
	} else if (mode == CONFIG3) {
		printSensor();
	} else if (mode == CONFIG4) {
//		printSensor
	}
	mtu_stop2();
//	TRANSAM = false;
	LED6 = false;
	LED1 = false;
	return 0;
}

void exportMap() {
	myprintf("{");
	for (int i = 0; i < 16; i++) {
		myprintf("{");
		for (int j = 0; j < 16; j++) {
			myprintf("%d", (map[i][j] & 0x0f));
			if (j != 15) {
				myprintf(",");
			}
		}
		myprintf("}");
		if (i != 15) {
			myprintf(",");
		}
		myprintf("\r\n");
	}
	myprintf("}\r\n");
}
void exportMap2() {
	myprintf("[");
	for (int i = 0; i < 16; i++) {
		myprintf("[");
		for (int j = 0; j < 16; j++) {
			myprintf("%d", (map[i][j] & 0x0f));
			if (j != 15) {
				myprintf(",");
			}
		}
		myprintf("]");
		if (i != 15) {
			myprintf(",");
		}
		myprintf("");
	}
	myprintf("]\r\n");
}
void checkMemory(int goalX, int goalY) {
//	if (writeMap2(g_flash_BlockAddresses[BLOCK_DB1])) {
//		startTransam(150);
//	} else {
//		coin(125);
//	}
// readMaze();
	updateDist(goalX, goalY, 0, isFullMaze(goalX, goalY));
	int tmpStart = dist[0][0];
	myprintf("%d \r\n", tmpStart);
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 15; i++) {
			if ((existWall(i, j, North) != existWall(i, j + 1, South))
					|| (existWall(i, j, East) != existWall(i + 1, j, West))) {
//				resetFull();
				return;
			}
		}
	}
	exportMap();
	cirquitMode = false;
	myprintf("not cirquit \r\n");
//	resetMap();
	printMap();

	exportMap2();
}
void test12() {
	sensingMode = AtackStraight;
	ledOn = true;
	char up = false;
	while (1) {
		myprintf("%d	%d\r\n", (sen_log_r[0] > sen_log_r[1]),
				(sen_log_r[1] > sen_log_r[2]));

		myprintf("%f	%f	%f	%f	%f\r\n", sen_log_r[0], sen_log_r[1], sen_log_r[2],
				sen_log_r[3], sen_log_r[4]);
		cmt_wait(100);
		if (!up) {
			up = checkUp(R);
		} else {
			if (checkDown(R)) {
				positionControlValueFlg = 0;
				cmtMusic(C2_, 500);
				cmt_wait(500);
				up = false;
//				return true;
			}
		}
	}
	ledOn = false;
}
void operation() {
	volatile char goalX = 1; // selectGoal();
	volatile char goalY = 0; //selectGoal();

	if (goalChangeFlg == 1) {
		goalX = selectGoal();
		goalY = selectGoal();
	}
	global_goal_x = goalX;
	global_goal_y = goalY;

//	while (true) {
//		encorderOperation();
//	}
//	printSensor();
//	testRun();
//	keepZeroPoint();
//	testRoll(L);
//	testWallOff(200);
//	testWallOffSeach(500);
//	testNormalSlalom(600);
//	sla3(1700);
//	inputData2();
//	testVacume2(90);
//	testWallOff();
//	checkIsoukeisu();
//	cirquit();
//	checkMemory(goalX, goalY);
	cirquit();

	while (1) {
		int res = action(encorderOperation(), goalX, goalY, false);
		mtu_stop2();
		if (res != 0) {
//			action(RUN2, goalX, goalY, true);
//			mazefinishMusic(150);
		}
		mtu_stop2();
	}
}

#endif /* OPERATIONSYSTEM_H_ */
;
