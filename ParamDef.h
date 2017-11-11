/*
 * ParamDef.h
 *
 *  Created on: 2013/11/21
 *      Author: Naoto
 */

#ifndef PARAMDEF_H_
#define PARAMDEF_H_

#define TIRE 24.975f
const float WHEEL = TIRE / 2000;
const float GEAR = 63.0 / 19.0;
#define DUTY_MAX 90.0f
#define Ke 0.000368613538f
#define Km 0.00352f
#define Resist 2.93f
#define Mass 0.101f
#define Lm 0.001f
#define friction 0.00125f
#define friction2 0.001925f

#define W_ENCORDER_LIMIT 100
#define W_ENCORDER_LIMIT2 10
#define W_ENCORDER_LIMIT_DIA 150
#define W_ENCORDER_LIMIT_DIA2 10
float gyroTh_R, gyroTh_L;
float pivotR, pivotL;
float Gkp, Gki, Gkd;
float Gkp2, Gki2, Gkd2;
float Akp, Aki, Akd;
float Akp2, Aki2, Akd2;
float Wkp, Wki, Wkd;
float Beta = 0;
float BetaOld = 0;
float k = 10;
float Vkp_r, Vki_r, Vkd_r;
float Vkp_l, Vki_l, Vkd_l;
float Vkp, Vki, Vkd;

#define orderup_r 4000
#define orderup_l 4000
#define supR_WALL 2000
#define supL_WALL 2000

//#define KIREME_R_DIA_SIDE 20
//#define KIREME_L_DIA_SIDE 20

/**
 * ↓　迷路・壁に依存する　調整パラメータ
 */

float wallhosei = 100;

/**
 * 調整以上
 */
int bias = 1;
int strBias = 3;
int diaBias = 3;
int Dia = 5;
int St1 = 7;
int minus = 3;
int Dia2;
int Dia3;
int St2;
int St3;
void importParam() {
	Dia2 = Dia - minus + 2;
	Dia3 = Dia - minus + 1;
	St2 = St1 - minus;
	St3 = St1 - minus - 1;

//	gyroTh_R = 0.00106065; 	// 2017/11/05
//	gyroTh_L = 0.00106065;	// 2017/11/05

	gyroTh_R = 0.00106435; //超新地
	gyroTh_L = 0.00106375;

	pivotR = gyroTh_R; //超新地
	pivotL = gyroTh_L;

	G.th = gyroTh_R;
	tempGyro = 0;

	Vel.Kp = 0.00125;
	Vel.Ki = 0.00085;
	Vel.Kd = 0.0;

//	Vel.Kp = 0.00325;
//	Vel.Ki = 0.00125;
//	Vel.Kd = 0.0;


	Gyro.Kp = 1.25; //本来
	Gyro.Ki = 0.01;

//	Sen.Kp = 0.00245;
//	Sen.Ki = 0.001;
//	Sen.Kd = 0.00025;

	Sen.Kp = 0.0025;
	Sen.Ki = 0.001;
	Sen.Kd = 0.065;

//	Backs.Kp = 0.005;
//	Backs.Ki = 0;
//	Backs.Kd = 0;

//	Sen_Dia.Kp = 0.0075;
//	Sen_Dia_Side.Kp = 0.0005;

//	Sen_Dia.Kp = 0.0175;
//	Sen_Dia_Side.Kp = 0.0005;


	Vkp = Vel.Kp;
	Vki = Vel.Ki;
	Vkd = Vel.Kd;
	Gkp = Gyro.Kp;
	Gki = Gyro.Ki;
	Gkd = Gyro.Kd;
	Akp = Angles.Kp;
	Aki = Angles.Ki;
	Akd = Angles.Kd;

	// 直線中央値
	RS_SEN1.ref = 562;
	LS_SEN1.ref = 710;

	// 直線中央値(斜め）
	RS_SEN1.ref2 = 1025;
	LS_SEN1.ref2 = 1425;

	// 斜め中央値　壁ナシ
	RF_SEN1.ref = RF_SEN1.ref2 = 150;
	LF_SEN1.ref = LF_SEN1.ref2 = 250;
	// 斜め中央値　壁あり

	RF_SEN1.ref3 = 1688;
	LF_SEN1.ref3 = 1666;

	wallhosei = 100;

	FrontCtrl.Kp = 0.125;
	FrontCtrl.Ki = 0.000;

//	FrontCtrlAngle.Kp = 0.0005;
//	FrontCtrlAngle.Ki = 0.01;

//	FrontCtrl.Kd = 0.1;

}

void resetFB() {
	Vel_r.Kp = 0.0;
	Vel_r.Ki = 0.0;
	Vel_r.Kd = 0.0;
	Vel_l.Kp = 0.0;
	Vel_l.Ki = 0.00;
	Vel_l.Kd = 0.0;
}

void readGyroParamP() {
	Gyro.Kp = Gkp;
	Gyro.Ki = 0;
	Gyro.Kd = 0;
}
void readGyroParam() {
	Gyro.Kp = Gkp;
	Gyro.Ki = Gki;
	Gyro.Kd = Gkd;
}
void readGyroParam2() {
	Gyro.Kp = Gkp2;
	Gyro.Ki = Gki2;
	Gyro.Kd = Gkd2;
}
void resetGyroParam() {
	Gyro.Kp = 0;
	Gyro.Ki = 0;
	Gyro.Kd = 0;
}
void resetAngleParam() {
	Angles.Kp = 0;
	Angles.Ki = 0;
	Angles.Kd = 0;
}

void resetOmegaParam() {
	Omega.Kp = 0;
	Omega.Ki = 0;
	Omega.Kd = 0;
}
void readOmegaParam() {
	Omega.Kp = Wkp;
	Omega.Ki = Wki;
	Omega.Kd = Wkd;
}
void readAngleParam() {
	Angles.Kp = Akp;
	Angles.Ki = Aki;
	Angles.Kd = Akd;
}
void readAngleParamP() {
	Angles.Kp = Akp;
	Angles.Ki = 0;
	Angles.Kd = 0;
}
void readVelocityGain() {
	Vel.Kp = Vkp;
	Vel.Ki = Vki;
	Vel.Kd = Vkd;
}
#endif /* PARAMDEF_H_ */
