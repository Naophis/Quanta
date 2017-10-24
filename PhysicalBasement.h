/*
 * PhysicalBasement.h
 *
 *  Created on: 2013/11/20
 *      Author: Naoto
 */

#ifndef PHYSICALBASEMENT_H_
#define PHYSICALBASEMENT_H_

char directionCheck_R = 0;
char directionCheck_L = 0;
float enc_r, enc_l;
long er, el;
float vr, vl;
float vr2, vl2;
#define logSize  20
float logR[logSize];
float logL[logSize];

void clearLogs() {
	for (char i = 0; i < logSize; i++) {
		logR[i] = 0;
		logL[i] = 0;
	}
}
void pushLog(float r, float l) {
	for (char i = 0; i < logSize - 1; i++) {
		logR[i + 1] = logR[i];
		logL[i + 1] = logL[i];
	}
	logR[0] = r;
	logL[0] = l;
}
float getAverageR() {
	float sum = 0;
	for (char i = 0; i < logSize; i++) {
		sum += logR[i];
	}
	return sum / logSize;
}
float getAverageL() {
	float sum = 0;
	for (char i = 0; i < logSize; i++) {
		sum += logL[i];
	}
	return sum / logSize;
}

void enc_to_vel(void) {
	float temp = Velocity.error_now;
	Velocity.error_old += Velocity.error_now;

	vr = -(float) (PI * TIRE * enc_r * CMT_CYCLE / GEAR / 4096.0);
	vl = (float) (PI * TIRE * enc_l * CMT_CYCLE / GEAR / 4096.0);

	V_Enc.r = vr; // vr * 0.1 + vr2 * 0.9;
	V_Enc.l = vl; // vl * 0.1 + vl2 * 0.9;

	vr2 = V_Enc.r;
	vl2 = V_Enc.l;

	Velocity.error_delta = (V_now - (V_Enc.l + V_Enc.r) / 2) - temp;

	rpmR = V_Enc.r * 60 / (PI * TIRE);
	rpmL = V_Enc.l * 60 / (PI * TIRE);
	Velocity.error_now = V_now - (V_Enc.r + V_Enc.l) / 2;
	distance += ABS(V_Enc.r + V_Enc.l) * dt / 2;
}

int checkStr = 0;
float check_sen_error(void) {
	int error = 0;
	char check = 0;
	if (ABS(RS_SEN1.now - RS_SEN1.old) < KIREME_R2) {
		wallCut_R = 1;
	} else {
		wallCut_R = 1;
	}
	if (ABS(LS_SEN1.now - LS_SEN1.old) < KIREME_L2) {
		wallCut_L = 1;
	} else {
		wallCut_L = 1;
	}
	if (ABS(RS_SEN1.now - RS_SEN1.old) < KIREME_R) {
		if (RS_SEN1.now > R_WALL) {
			if (RF_SEN1.now < FRONT_OUT_R) {
				error += RS_SEN1.now - RS_SEN1.ref;
				check++;
			}
		}
	} else {
		if (RS_SEN1.now > (R_WALL + orderup_r)) {
			error += RS_SEN1.now - RS_SEN1.ref;
			check++;
		}
	}
	if (ABS(LS_SEN1.now - LS_SEN1.old) < KIREME_L) {
		if (LS_SEN1.now > L_WALL) {
			if (LF_SEN1.now < FRONT_OUT_L) {
				error -= LS_SEN1.now - LS_SEN1.ref;
				check++;
			}
		}
	} else {
		if (LS_SEN1.now > (L_WALL + orderup_l)) {
			error -= LS_SEN1.now - LS_SEN1.ref;
			check++;
		}
	}
	RS_SEN1.old = RS_SEN1.now;
	LS_SEN1.old = LS_SEN1.now;
	if (check == 0) {
		Se.error_old = 0;
	} else {
		Angle.error_old = 0;
		Gy.error_old = 0;
		angle = 0;
		ang = 0;
		if (ABS(error) > W_ENCORDER_LIMIT) {
			W_enc.error_old = 0;
			Gy.error_old = 0;
		}
		if (ABS(Se.error_now) > 100) {
			checkStr++;
			Angle.error_old = 0;
			Gy.error_old = 0;
			angle = 0;
			ang = 0;
		} else {
			checkStr = 0;
		}
	}

	if (check != 0) {
		errorFlg = 1;
		globalError = error;
	} else {
		errorFlg = 0;
	}
	if (check == 2) {
		return error;
	}
	return 2 * error;
}
int gyroReset = 0;

volatile char isControl = 0;
volatile int errorOld_dia = 0;
volatile int errorOld_dia_side = 0;

int check_sen_error_dia_side(void) {
	int error = 0;
	char check = 0;
	if (ABS(RS_SEN1.now - RS_SEN1.old) < KIREME_R_DIA_SIDE) {
		if (RS_SEN1.now > RS_WALL2) {
			error += RS_SEN1.now - RS_SEN1.ref2;
			check++;
		}
	} else {
		if (RS_SEN1.now > (RS_WALL2 + orderup_r)) {
			error += RS_SEN1.now - RS_SEN1.ref2;
			check++;
		}
	}
	if (ABS(LS_SEN1.now - LS_SEN1.old) < KIREME_L_DIA_SIDE) {
		if (LS_SEN1.now > LS_WALL2) {
			error += LS_SEN1.now - LS_SEN1.ref2;
			check++;
		}
	} else {
		if (LS_SEN1.now > (LS_WALL2 + orderup_l)) {
			error += LS_SEN1.now - LS_SEN1.ref2;
			check++;
		}
	}

	RS_SEN1.old = RS_SEN1.now;
	LS_SEN1.old = LS_SEN1.now;

	if (check == 0) {
		Se2.error_old = 0;
		error = errorOld_dia_side;
	} else {
	}
	isControl = false;

	if (check != 0) {
		errorFlg = 1;
		errorOld_dia_side = error;
	} else {
		errorFlg = 0;
	}

	errorOld_dia = error;

	if (check == 2) {
		return error;
	}
	return 2 * error;
}

int check_sen_error_dia(void) {
	int error = 0;
	char check = 0;
	if (RS_SEN1.now > R_WALL_dia) {
		if (ABS(RF_SEN1.now - RF_SEN1.old) < KIREME_R_DIA) {
			if (RF_SEN1.now > RF_WALL1) {
				error += RF_SEN1.now - RF_SEN1.ref2;
				check++;
			}
		} else {
			if (RF_SEN1.now > (RF_WALL1 + orderup_r)) {
				error += RF_SEN1.now - RF_SEN1.ref2;
				check++;
			}
		}
	} else {
		if (ABS(RF_SEN1.now - RF_SEN1.old) < KIREME_R_DIA) {
			if (RF_SEN1.now > RF_WALL) {
				error += RF_SEN1.now - RF_SEN1.ref;
				check++;
			}
		} else {
			if (RF_SEN1.now > (RF_WALL + orderup_r)) {
				error += RF_SEN1.now - RF_SEN1.ref;
				check++;
			}
		}
	}

	if (LS_SEN1.now > L_WALL_dia) {
		if (ABS(LF_SEN1.now - LF_SEN1.old) < KIREME_L_DIA) {
			if (LF_SEN1.now > LF_WALL1) {
				error += LF_SEN1.now - LF_SEN1.ref2;
				check++;
			}
		} else {
			if (LF_SEN1.now > (LF_WALL1 + orderup_l)) {
				error += LF_SEN1.now - LF_SEN1.ref2;
				check++;
			}
		}
	} else {
		if (ABS(LF_SEN1.now - LF_SEN1.old) < KIREME_L_DIA) {
			if (LF_SEN1.now > LF_WALL1) {
				error += LF_SEN1.now - LF_SEN1.ref;
				check++;
			}
		} else {
			if (LF_SEN1.now > (LF_WALL + orderup_l)) {
				error += LF_SEN1.now - LF_SEN1.ref;
				check++;
			}
		}
	}

	RF_SEN1.old = RF_SEN1.now;
	LF_SEN1.old = LF_SEN1.now;

	if (check == 0) {
		Se.error_old = 0;
		error = errorOld_dia;
	} else {
//		Gy.error_old = 0;
//		angle = 0;
//		ang = 0;
	}
	isControl = false;

	if (check != 0) {
		errorFlg = 1;
		globalError = error;
	} else {
		errorFlg = 0;
	}

	errorOld_dia = error;

	if (check == 2) {
		return error;
	}
	return 2 * error;
}

float D1 = 0.0001;
float k1 = 76.25;
float k2 = 10370;
float P = 100;
void errorVelocity(void) {
	C.s2 = 0;
	if (positionControlValueFlg == 1) {
		if (dia == 0) {
			Se.error_now = check_sen_error();
			C.s = Sen.Kp * Se.error_now + Sen.Ki * Se.error_old
					+ Sen.Kd * Se.error_delta;
//			C.s = (D1 + k1 / k2 * (V_Enc.r + V_Enc.l) / 2000) * settleGyro
//					+ P / k2 * Se.error_now;
		} else if (dia == 1) {
			Se.error_now = check_sen_error_dia();
			if (Se.error_now != 0) {
				C.s = Sen_Dia.Kp * Se.error_now + Sen_Dia.Ki * Se.error_old
						+ Sen_Dia.Kd * Se.error_delta;
			}

			Se2.error_now = check_sen_error_dia_side();
			C.s2 = 0;
			if (Se2.error_now != 0) {
				C.s2 = Sen_Dia_Side.Kp * Se2.error_now
						+ Sen_Dia_Side.Ki * Se2.error_old
						+ Sen_Dia_Side.Kd * Se2.error_delta;
			}
		}
	} else {
		Se.error_delta = 0;
		Se.error_old = 0;
		C.s = 0;
	}
	Gy.error_delta = Gy.error_now - (W_now - settleGyro);
	Gy.error_old += Gy.error_now;
	Gy.error_now = (W_now - settleGyro);
	C.g = Gyro.Kp * Gy.error_now + Gyro.Ki * Gy.error_old
			+ Gyro.Kd * Gy.error_delta;
}

float checkDuty(float duty) {
	duty = ABS(duty);
	if (duty > DUTY_MAX) {
		duty = DUTY_MAX;
	}
	return duty;
}
void changeRotation(float duty, char RorL) {
	if (RorL == L) {
		if (duty > 0.0) {
			CW_L();
		} else {
			CCW_L();
		}
	} else if (RorL == R) {
		if (duty > 0.0) {
			CW_R();
		} else {
			CCW_R();
		}
	}
}
float getRpm(char RorL) {
	return RorL == R ? rpmR : rpmL;
}

float feadforward(char RorL) {
	return Mass * acc * WHEEL * Resist / (GEAR * Km * 1000);
}
float feadforward_para(char RorL) {
	if (RorL == R) {
		return Lm * (-alpha) * WHEEL * Resist / (GEAR * Km);
	}
	return Lm * (alpha) * WHEEL * Resist / (GEAR * Km);
}

float FF_calc(char RorL) {
//	return 0;
	float rpm = getRpm(RorL);
	float resist = Resist * friction / Km;
	if (rpm < 0) {
		resist *= -1;
	} else if (V_now == 0 && W_now == 0) {
		resist = 0;
	}
	resist = 0;
	return ((feadforward(RorL) + feadforward_para(RorL)) + Ke * rpm + resist);
}
float FB_calc(char RorL) {
	float duty;
	if (RorL == R) {
		duty = Vel_r.Kp * (Vr.error_now)
				+ Vel_r.Ki * (Vr.error_now + Vr.error_old)
				+ Vel_r.Kd * (Vr.error_now - Vr.error_delta);
		return duty;
	}
	duty = Vel_l.Kp * (Vl.error_now) + Vel_l.Ki * (Vl.error_now + Vl.error_old)
			+ Vel_l.Kd * (Vl.error_now - Vl.error_delta);
	return duty;
}

float FB_calc_omega() {
	return Omega.Kp * (W_enc.error_now)
			+ Omega.Ki * (W_enc.error_now + W_enc.error_old)
			+ Omega.Kd * (W_enc.error_now - W_enc.error_delta);
}

float FB_calc_straight() {
	return Vel.Kp * Velocity.error_now + Vel.Ki * Velocity.error_old
			+ Vel.Kd * Velocity.error_delta;
}

float FB_calc_pararell() {
	return C.angles + C.g - C.s; //- C.s2;
}

void dutyCalcuration2(void) {
	float dutyR = 0, dutyL = 0;
	float FB_straight_duty = FB_calc_straight();
	float FB_pararell_duty = FB_calc_pararell();
	ffR = FF_calc(R);
	ffL = FF_calc(L);

	dutyR = (ffL + FB_straight_duty + FB_pararell_duty) / battery * 100;
	dutyL = (ffR + FB_straight_duty - FB_pararell_duty) / battery * 100;
//	Duty_r = (ffL + FB_straight_duty + FB_pararell_duty) / battery * 100;
//	Duty_l = (ffR + FB_straight_duty - FB_pararell_duty) / battery * 100;

//	dutyR = dutyL = 30;

	Duty_r = dutyR;
	Duty_l = dutyL;
	changeRotation(dutyR, R);	//R_CW/CCW
	changeRotation(dutyL, L);	//L_CW/CCW

	failCheck(dutyR, dutyL);
	dutyR = checkDuty(dutyR);
	dutyL = checkDuty(dutyL);

	gra_r = (long) (dutyR * M_CYCLE / 100.0);
	gra_l = (long) (dutyL * M_CYCLE / 100.0);
	if (enablePWM) {
		GPT0.GTCCRA = gra_r;
		GPT0.GTCCRC = gra_r;
		GPT1.GTCCRA = gra_l;
		GPT1.GTCCRC = gra_l;
	} else {
		GPT0.GTCCRA = 0;
		GPT0.GTCCRC = 0;
		GPT1.GTCCRA = 0;
		GPT1.GTCCRC = 0;
	}

}
//物理量ベース計算
void Physical_Basement(void) {
	enc_l = MTU1.TCNT - 30000;
	enc_r = MTU2.TCNT - 30000;
	if (os_escape) {
		MTU2.TCNT = MTU1.TCNT = 30000;
	}
	if (alphaMode == 1) {
		if (dt * sinCount / slaTerm < 2.0) {
			alpha = alphaTemp * Et2(dt * sinCount, slaTerm, etN);
		} else {
			alpha = 0;
		}
	}
	if (dia == 1 && originalDiaMode == true && checkStablly() == true) {
		if (targetVelocity > V_now) {
			if (tmpDiac < 0) {
//				acc = tmpDiac;
				acc = 0;
			}
		}
	}
	errorVelocity();
	V_now += acc * dt;
	W_now += alpha * dt;
	ang += settleGyro * dt;
	angle += W_now * dt;

	enc_to_vel();
	dutyCalcuration2();
}
#endif /* PHYSICALBASEMENT_H_ */
