#include "iodefine.h"
#include "stdio.h"
#include <stdint.h>
#include <string.h>
#include "machine.h"
#include "mathf.h"
#include "defines.h"
#include "Table.h"

#include "Structor.h"

#include "init.h"
#include "serial.h"
#include "spi.h"
#include "Music.h"

#include "ParamDef.h"
#include "sensor.h"

#include "ParamDef.h"
#include "ParamsController.h"
#include "Util.h"
#include "PhysicalBasement.h"

#include "Run.h"
#include "WallOff.h"
#include "Map.h"
#include "Search.h"
#include "VectorSearch.h"
#include "VectorPath.h"
#include "Path.h"
#include "RealRun.h"
//#include "r_flash_api_rx_config.h"
//#include "r_flash_api_rx_if.h"
#include "Adachi.h"
#include "cirkit.h"

//#include "Flash.h"
#include "flash3.h"
#include "flash2.h"
#include "ParamImporter.h"
//#include "myFlash.h"

#include "Setting.h"
#include "Mram.h"

#include "OperationSystem.h"
#include "SerialMapper.h"

volatile void buzzer() {
	if ((buzzerTimer % 2) == 0) {
		PORTC.PODR.BIT.B6 = 1;
	} else {
		PORTC.PODR.BIT.B6 = 0;
	}
	buzzerTimer++;
	if (m_time != 0) {
		if (buzzerTimer == m_time) {
			stopCmt1();
			singing = false;
		}
	}
}
void mtu6A() {
	LED1 = 1;
	PORTC.PODR.BIT.B6 = 0;
	buzzerTimer++;
	if (m_time != 0) {
		if (buzzerTimer == m_time) {
			stopCmt1();
		}
	}
}
void mtu6B() {
	LED4 = 1;
	PORTC.PODR.BIT.B6 = 1;
}
volatile void cmt() {
	timer++;
	time++;
	sinCount++;
	swTop = !PushTop;
	swBottom = !PushBottom;
	swRight = !PushRight;
	swLeft = !PushLeft;
	swCenter = !PushCenter;
	if (!PushTop) {
		cmtMusic(D2s_, 250);
	}
	if (!PushRight) {
		cmtMusic(D2s_, 250);
	}
	if (!PushLeft) {
		cmtMusic(D2s_, 250);
	}
	if (!PushBottom) {
		cmtMusic(D2s_, 250);
	}
	if (singing) {
		buzzer();
	}
//	if ((time % 4) == 0) {
//
//		if ((buzzerTimer % 2) == 0) {
//			PORTC.PODR.BIT.B6 = 1;
//			LED4 = 1;
//			LED_RIGHT = 0;
//		} else {
//			PORTC.PODR.BIT.B6 = 0;
//			LED4 = 0;
//			LED_RIGHT = 1;
//		}
//		buzzerTimer++;
//	}

	Physical_Basement();
	if (logs < L_Length && cc == 1) {
		if ((time % 1) == 0) {
			log1[logs] = (int) (V_now);
			logs2[logs] = ((Wo * Wo - W_now * W_now) / (2.0 * alpha));
			log3[logs] = (V_Enc.r + V_Enc.l) / 2;
			log4[logs] = (ang * 180 / PI);
			log5[logs] = DutyL;
			log6[logs] = DutyR;
			log7[logs] = (battery);
			log8[logs] = (LS_SEN1.now);
			log9[logs] = (RS_SEN1.now);
			logs10[logs] = (LF_SEN1.now);
			log11[logs] = (RF_SEN1.now);
			log12[logs] = (settleGyro);
			log13[logs] = (W_now);
			log14[logs] = (angle * 180 / PI);
			log15[logs] = (V_Enc.r);
			log16[logs] = (V_Enc.l);
			log17[logs] = (float) (alpha);
			log18[logs] = (float) (MTU1.TCNT);
			logs++;

//			log1[logs] = (int) (V_now);
//			logs2[logs] = ((Wo * Wo - W_now * W_now) / (2.0 * alpha));
//			log3[logs] = (V_Enc.r + V_Enc.l) / 2;
//			log4[logs] = (ang * 180 / PI);
//			log5[logs] = Duty_l;
//			log6[logs] = Duty_r;
//			log7[logs] = (FB_calc_straight());
//			log8[logs] = (FB_calc_pararell());
//			log9[logs] = (FB_calc_straight() + FB_calc_pararell());
//			logs10[logs] = (FB_calc_straight() - FB_calc_pararell());
//			log11[logs] = (RF_SEN1.now);
//			log12[logs] = (settleGyro);
//			log13[logs] = (W_now);
//			log14[logs] = (angle * 180 / PI);
//			log15[logs] = (V_Enc.r);
//			log16[logs] = (V_Enc.l);
//			log17[logs] = (C.g);
//			log18[logs] = (C.s);
//			logs++;

		}
	}
}

volatile int timer2 = 0;

void mtu4_A() {
	tpu_count++;
	switch (tpu_count) {
	case 1:
		timer2++;
		sensing_in_off();
		if (mpu) {
			callMpu(0x47);
		}
		PORT2.PODR.BIT.B3 = 1; //LF
		PORTE.PODR.BIT.B1 = 1; //RF
		break;
	case 2:
		if (mpu) {
			callMpu(0x47);
		}
		PORT2.PODR.BIT.B7 = 1; //RS1
		PORT2.PODR.BIT.B5 = 1; //LS1
		break;
	case 3:
		if (mpu) {
			callMpu(0x47);
		}
		PORTD.PODR.BIT.B7 = 1; //RS2
		PORT2.PODR.BIT.B4 = 1; //LS2
		break;
	case 4:
		if (mpu) {
			callMpu(0x47);
		}
		sensing_battery();
		break;
	}
}

void getBattery() {
	if (BATTERY != 0) {
		battery = 0.1 * (3.3f * BATTERY / 4096 / (1.0 - 7.5 / (3.0 / 4 + 7.5)))
				+ 0.9 * batteryOld;
	} else {
		battery = 3.3f * BATTERY / 4096 / (1.0 - 7.5 / (3.0 / 4 + 7.5));
	}
	batteryOld = battery;
}
int gyros[4];

void mtu4_B() {
	switch (tpu_count) {
	case 1:
		sensing_front();
		gyros[0] = getMpuData();
		break;
	case 2:
		sensing_side();
		gyros[1] = getMpuData();
		break;
	case 3:
		sensing_side2();
		gyros[2] = getMpuData();
		break;
	case 4:
//		sensing_side_right();
//		getBattery();

		if (fanStart) {
			if ((FAN_AMP / battery) <= FAN_CYCLE) {
				GPT2.GTCCRA = GPT2.GTCCRC =
						(int) (FAN_AMP / battery * FAN_CYCLE);
			} else {
				GPT2.GTCCRA = GPT2.GTCCRC = FAN_CYCLE;
			}
		} else {
			GPT2.GTCCRA = GPT2.GTCCRC = 0;
		}

		gyros[3] = getMpuData();
		RS_SEN1.old = RS_SEN1.now;
		LS_SEN1.old = LS_SEN1.now;
		RF_SEN1.old = RF_SEN1.now;
		LF_SEN1.old = LF_SEN1.now;

		getSensorData();

		float tmpGyros = (gyros[0] + gyros[1] + gyros[2] + gyros[3]) / 4;
		settleGyro2 = (G.ref - tmpGyros) * G.th;
		G.now = settleGyro2;
		settleGyroOld = settleGyro;
		settleGyro = 0.1 * G.now + 0.9 * G.old;
//		settleGyro = settleGyro2;
		G.old = settleGyro;

		tpu_count = 0;

		sen_log_r[4] = sen_log_r[3];
		sen_log_r[3] = sen_log_r[2];
		sen_log_r[2] = sen_log_r[1];
		sen_log_r[1] = sen_log_r[0];

		sen_log_l[4] = sen_log_l[3];
		sen_log_l[3] = sen_log_l[2];
		sen_log_l[2] = sen_log_l[1];
		sen_log_l[1] = sen_log_l[0];

		sen_log_r[0] = RS_SEN1.now;
		sen_log_l[0] = LS_SEN1.now;

		sen_r[4] = sen_r[3];
		sen_r[3] = sen_r[2];
		sen_r[2] = sen_r[1];
		sen_r[1] = sen_r[0];
		sen_r[0] = RS_SEN1.now > R_WALL3;

		sen_l[4] = sen_l[3];
		sen_l[3] = sen_l[2];
		sen_l[2] = sen_l[1];
		sen_l[1] = sen_l[0];
		sen_l[0] = LS_SEN1.now > L_WALL3;

		sen_r2[4] = sen_r2[3];
		sen_r2[3] = sen_r2[2];
		sen_r2[2] = sen_r2[1];
		sen_r2[1] = sen_r2[0];
		sen_r2[0] = RS_SEN2.now > R_WALL4;

		sen_l2[4] = sen_l2[3];
		sen_l2[3] = sen_l2[2];
		sen_l2[2] = sen_l2[1];
		sen_l2[1] = sen_l2[0];
		sen_l2[0] = LS_SEN2.now > L_WALL4;
		break;
	}
	sensor_led_off();
}

void initRX64M() {
	importParam();
	initClock();
	initLED();
	initSensorLED();
	initMotorDriverRotate();
	initS12AD();
	initSci1();
	initCmt0();
	initIsouKeisu();
	initGPT01();
//	initGPT2();
	Init_SPI();
	init_Mtu4();
}
void test() {
	ComFlag = true;
}

void main(void) {
	initRX64M();
	batteryCheck();
	setupCmt = true;
	enableMPU = true;
	os_escape = true;

	while (1) {
		float result = getZeroPoint();
		if (ABS(result) < 0.5) {
			decide2(125);
			setupMpu6500();
		} else {
			break;
		}
	}
	coin(100);
	ledOn = 1;
	os_escape = 1;
//	for (int i = 0; i < 100; i++) {
//		makeMusic(400 + 400 * i, 500);
////		cmt_wait(500);
//	}

//	testFcu();
//	preread();
	myprintf("%c[33m", ESC); /* 文字を黄色に */
//	while (1) {
//		loadData();
//	}

//	myprintf("init :%d\r\n", start());
//	preread();
//	while (1) {
//	}
//	testFcu();

	operation();
	os_escape = 0;
}
