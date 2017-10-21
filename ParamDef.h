/*
 * ParamDef.h
 *
 *  Created on: 2013/11/21
 *      Author: Naoto
 */

#ifndef PARAMDEF_H_
#define PARAMDEF_H_

#define TIRE 24.0
const float WHEEL = TIRE / 2000;
const float GEAR = 63.0 / 19.0;
#define DUTY_MAX 70.0f
#define Ke 0.0000896f
#define Km 0.000855f
#define Resist 2.9f
#define Mass 0.101f
#define Lm 0.001f
#define friction 0.0001f

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

#define KIREME_R 11	//11/12
#define KIREME_L 11

//#define KIREME_R 11 //11/12
//#define KIREME_L 11

#define orderup_r 4000
#define orderup_l 4000
#define supR_WALL 2000
#define supL_WALL 2000
unsigned int R_WALL = 200;   //#define R_WALL 4000	//サーキット用
unsigned int L_WALL = 200;

unsigned int R_WALL3 = 130;
unsigned int L_WALL3 = 190;

#define KIREME_R2 20
#define KIREME_L2 20
#define KIREME_R_DIA 40
#define KIREME_L_DIA 40

/**
 * ↓　迷路・壁に依存する　調整パラメータ
 */

float R_WALL_EXIST = 70; //探索時壁判定
float L_WALL_EXIST = 70; //探索時壁判定
float RF_WALL_EXIST = 80; //探索時壁判定
float LF_WALL_EXIST = 50; //探索時壁判定

float FRONT_CTRL_R = 125; //前壁補正
float FRONT_CTRL_L = 100; //前壁補正
float RF_WALL_EXIST2 = 75; //前壁補正　開始
float LF_WALL_EXIST2 = 45; //前壁補正　開始

float wallhosei = 100;

float RF_WALL = 200;	//斜め時 姿勢制御閾値(壁アリ）
float LF_WALL = 30;		//斜め時 姿勢制御閾値(壁アリ）
float RF_WALL1 = 20;		//斜め時 姿勢制御閾値(壁ナシ）
float LF_WALL1 = 20;		//斜め時 姿勢制御閾値(壁ナシ）

float R_WALL_dia = 300;	//斜め時 横壁のアリ判定
float L_WALL_dia = 300;	//斜め時 横壁のアリ判定
float R_WALL_OFF = 168;	//壁切れ　閾値
float L_WALL_OFF = 168;	//壁切れ　閾値
float R_WALL_OFF_D = 180;	//壁切れ　閾値　斜め用
float L_WALL_OFF_D = 200;		//壁切れ　閾値　斜め用

float FRONT_OUT_R = 800;	//袋小路時前センサー閾値
float FRONT_OUT_L = 800;	//袋小路時前センサー閾値
float existRightWall = 400;		//壁切れの予備
float existLeftWall = 450;		//壁切れの予備
float existRightWall3 = 150;		//壁切れの予備
float existLeftWall3 = 150;		//壁切れの予備

float existRightWall2 = 400;	//壁切れの予備 斜め 不要
float existLeftWall2 = 400;		//壁切れの予備 斜め 不要

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

	gyroTh_R = 0.00106245;	//超新地
	gyroTh_L = 0.00106215;

	pivotR = gyroTh_R;	//超新地
	pivotL = gyroTh_L;

	G.th = gyroTh_R;
	tempGyro = 0;

	Vel.Kp = 0.00125;
	Vel.Ki = 0.00085;
	Vel.Kd = 0.0;

//	Gyro.Kp = 0.9;	//本来
//	Gyro.Ki = 0.01;
//	Gyro.Kd = 0.0;

//	Sen.Kp = 0.02;
//	Sen.Ki = 0.00075;
//	Sen.Kd = 0.0001;
//
//	Sen_Dia.Kp = 0.01;

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
	RS_SEN1.ref = 509;
	LS_SEN1.ref = 924;
	// 斜め中央値　壁ナシ
	RF_SEN1.ref = 30;
	LF_SEN1.ref = 30;
	// 斜め中央値　壁あり
	RF_SEN1.ref2 = 40;
	LF_SEN1.ref2 = 40;

	R_WALL_EXIST = 100; //探索時壁判定
	L_WALL_EXIST = 100; //探索時壁判定
	RF_WALL_EXIST = 80; //探索時壁判定
	LF_WALL_EXIST = 80; //探索時壁判定

	FRONT_CTRL_R = 138; //前壁補正
	FRONT_CTRL_L = 105; //前壁補正
	RF_WALL_EXIST2 = 80; //前壁補正　開始
	LF_WALL_EXIST2 = 80; //前壁補正　開始

	wallhosei = 100;

	RF_WALL = 200;	//斜め時 姿勢制御閾値(壁アリ）
	LF_WALL = 30;		//斜め時 姿勢制御閾値(壁アリ）
	RF_WALL1 = 20;		//斜め時 姿勢制御閾値(壁ナシ）
	LF_WALL1 = 20;		//斜め時 姿勢制御閾値(壁ナシ）

	R_WALL_dia = 300;	//斜め時 横壁のアリ判定
	L_WALL_dia = 300;	//斜め時 横壁のアリ判定
	R_WALL_OFF = 168;	//壁切れ　閾値
	L_WALL_OFF = 260;	//壁切れ　閾値
	R_WALL_OFF_D = 200;	//壁切れ　閾値　斜め用
	L_WALL_OFF_D = 200;		//壁切れ　閾値　斜め用

	FRONT_OUT_R = 800;	//袋小路時前センサー閾値
	FRONT_OUT_L = 800;	//袋小路時前センサー閾値
	existRightWall = 400;		//壁切れの予備
	existLeftWall = 150;		//壁切れの予備
	existRightWall3 = 150;		//壁切れの予備
	existLeftWall3 = 150;		//壁切れの予備

	existRightWall2 = 400;	//壁切れの予備 斜め 不要
	existLeftWall2 = 400;		//壁切れの予備 斜め 不要
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

