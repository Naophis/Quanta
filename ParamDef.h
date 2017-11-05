/*
 * ParamDef.h
 *
 *  Created on: 2013/11/21
 *      Author: Naoto
 */

#ifndef PARAMDEF_H_
#define PARAMDEF_H_

#define TIRE 24.625f
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

#define KIREME_R 25 //11/12
#define KIREME_L 25

//#define KIREME_R 11 //11/12
//#define KIREME_L 11

#define orderup_r 4000
#define orderup_l 4000
#define supR_WALL 2000
#define supL_WALL 2000

unsigned int R_WALL = 380; //#define R_WALL 4000	//サーキット用
unsigned int L_WALL = 530;	//制御壁閾値

unsigned int R_WALL3 = 340;
unsigned int L_WALL3 = 530;

unsigned int R_WALL4 = 50;
unsigned int L_WALL4 = 180;

#define KIREME_R2 10
#define KIREME_L2 10
#define KIREME_R_DIA 200
#define KIREME_L_DIA 200
#define KIREME_R_DIA_SIDE 20
#define KIREME_L_DIA_SIDE 20

/**
 * ↓　迷路・壁に依存する　調整パラメータ
 */

float R_WALL_EXIST = 330;  //探索時壁判定
float L_WALL_EXIST = 400;  //探索時壁判定
float RF_WALL_EXIST = 400; //探索時壁判定
float LF_WALL_EXIST = 360; //探索時壁判定

float FRONT_CTRL_R = 520;   //前壁補正
float FRONT_CTRL_L = 440;	//前壁補正
float RF_WALL_EXIST2 = 350; //前壁補正　開始
float LF_WALL_EXIST2 = 320;   //前壁補正　開始

float FRONT_CTRL_R4 = 1450;   //前壁補正
float FRONT_CTRL_L4 = 1345;	//前壁補正
float RF_WALL_EXIST4 = 450; //前壁補正　開始
float LF_WALL_EXIST4 = 50;   //前壁補正　開始

float wallhosei = 100;

float RF_WALL1 = 210; //斜め時 姿勢制御閾値(壁ナシ）
float LF_WALL1 = 260; //斜め時 姿勢制御閾値(壁ナシ）

float RF_WALL = 210; //斜め時 姿勢制御閾値(壁アリ）
float LF_WALL = 260;  //斜め時 姿勢制御閾値(壁アリ）

float RS_WALL2 = 800; //斜め時 姿勢制御閾値(壁ナシ）
float LS_WALL2 = 1200; //斜め時 姿勢制御閾値(壁ナシ）

float RF_WALL_FrontCTRL = 520; //斜め時 姿勢制御閾値(壁ナシ）
float LF_WALL_FrontCTRL = 450; //斜め時 姿勢制御閾値(壁ナシ）

float R_WALL_dia = 400;	//斜め時 横壁のアリ判定
float L_WALL_dia = 400;	//斜め時 横壁のアリ判定

float R_WALL_OFF = 335;	//壁切れ　閾値
float L_WALL_OFF = 480;	//壁切れ　閾値
float R_WALL_OFF2 = 390;	//壁切れ　閾値
float L_WALL_OFF2 = 572;	//壁切れ　閾値

float R_WALL_OFF_D = 515;  //壁切れ　閾値　斜め用
float L_WALL_OFF_D = 1080; //壁切れ　閾値　斜め用

float R_WALL_OFF_D2 = 485;  //壁切れ　閾値　斜め用
//float L_WALL_OFF_D2 = 1040; //壁切れ　閾値　斜め用
float L_WALL_OFF_D2 = 740; //壁切れ　閾値　斜め用

float FRONT_OUT_R = 1200;	//袋小路時前センサー閾値
float FRONT_OUT_L = 1200;	//袋小路時前センサー閾値

float existRightWall = 450;  //壁切れの予備
float existLeftWall = 750;   //壁切れの予備

float existRightWall2 = 400; //壁切れの予備 斜め
float existLeftWall2 = 400;  //壁切れの予備 斜め

float existRightWall3 = 150; //壁切れの予備
float existLeftWall3 = 150;  //壁切れの予備

float existRightWall4 = 250;  //壁切れの予備
float existLeftWall4 = 500;   //壁切れの予備

float existRightWall5 = 500;  //壁切れの予備
float existLeftWall5 = 400;   //壁切れの予備
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

	Gyro.Kp = 0.975; //本来
	Gyro.Ki = 0.025;

//	Sen.Kp = 0.00245;
//	Sen.Ki = 0.001;
//	Sen.Kd = 0.00025;

	Sen.Kp = 0.00275;
	Sen.Ki = 0.001;
	Sen.Kd = 0.00025;

//	Backs.Kp = 0.005;
//	Backs.Ki = 0;
//	Backs.Kd = 0;

	Sen_Dia.Kp = 0.0045;
	Sen_Dia_Side.Kp = 0.0005;

	Sen_Dia.Kp = 0.0075;
//	Sen_Dia_Side.Kp = 0.00075;

//	Sen_Dia.Kp = 0.00;
//	Sen_Dia_Side.Kp = 0.0;

//	Sen_Dia.Kp = 0.00125;
//	Sen_Dia_Side.Kp = 0.005;
//	Sen_Dia.Kp = 0.00025;
//	Sen_Dia_Side.Kp = 0.0001;

//	Sen_Dia.Kp = 0.0005;
//	Sen_Dia_Side.Kp = 0.001;

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
	RS_SEN1.ref = 536;
	LS_SEN1.ref = 711;
	// 直線中央値(斜め）
	RS_SEN1.ref2 = 860;
	LS_SEN1.ref2 = 1330;

	// 斜め中央値　壁ナシ
	RF_SEN1.ref = 200;
	LF_SEN1.ref = 250;
	// 斜め中央値　壁あり
	RF_SEN1.ref2 = 190;
	LF_SEN1.ref2 = 280;

	RF_SEN1.ref3 = 1635;
	LF_SEN1.ref3 = 1515;

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
