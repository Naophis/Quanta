/*
 * WallOff.h
 *
 *  Created on: 2016/08/27
 *      Author: Naoto
 */

#ifndef WALLOFF_H_
#define WALLOFF_H_

#define SEN_R RS_SEN1.now
#define SEN_L LS_SEN1.now
#define SEN_R2 RS_SEN2.now
#define SEN_L2 LS_SEN2.now

char wallOff(char RorL);
char wallOff_D(char RorL);
volatile int wall_off_limit = 40;
volatile int wall_off_limit_d = 40;
char wallOff(char RorL) {
	if (dia == 1) {
		return wallOff_D(RorL);
	}
	sensingMode = AtackStraight;
	positionControlValueFlg = 1;
	ang = 0;
	angle = 0;
	distance = 0;
	char up = false;
	if (RorL == R) {
		while (SEN_R < R_WALL_OFF && distance <= wall_off_limit) {
//			if (!up) {
//				up = checkUp(R);
//			} else {
//				if (checkDown(R)) {
//					positionControlValueFlg = 0;
//					return true;
//				}
//			}
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
		while (SEN_R > R_WALL_OFF && distance <= wall_off_limit) {
//			if (checkDown2(R)) {
//				positionControlValueFlg = 0;
//				return true;
//			}
//			if (checkDown3(R)) {
//				positionControlValueFlg = 0;
//				return true;
//			}
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	} else {
		while (SEN_L < L_WALL_OFF && distance <= wall_off_limit) {
//			if (!up) {
//				up = checkUp(L);
//			} else {
//				if (checkDown(L)) {
//					positionControlValueFlg = 0;
//					return true;
//				}
//			}
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
		while (SEN_L > L_WALL_OFF && distance <= wall_off_limit) {
//			if (checkDown2(L)) {
//				positionControlValueFlg = 0;
//				return true;
//			}
//			if (checkDown3(L)) {
//				positionControlValueFlg = 0;
//				return true;
//			}
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	}
	positionControlValueFlg = 0;
	return 1;
}
char wallOff_D(char RorL) {
//	positionCoontrolValueFlg = 1;
	ang = 0;
	angle = 0;
	distance = 0;
	sensingMode = AtackDia;
	char up = false;
	if (RorL == R) {
		while (SEN_R < R_WALL_OFF_D && distance <= wall_off_limit_d) {
//			if (!up) {
//				up = checkUp2(R);
//			} else {
//				if (checkDown2(R)) {
//					positionControlValueFlg = 0;
//					return true;
//				}
//			}
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
		while (SEN_R > R_WALL_OFF_D && distance <= wall_off_limit_d) {
//			if (!up) {
//				up = checkUp2(L);
//			} else {
//				if (checkDown2(L)) {
//					positionControlValueFlg = 0;
//					return true;
//				}
//			}
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	} else {
		while (SEN_L < L_WALL_OFF_D && distance <= wall_off_limit_d) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
		while (SEN_L > L_WALL_OFF_D && distance <= wall_off_limit_d) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	}
	positionControlValueFlg = 0;
	return 1;
}
#endif /* WALLOFF_H_ */
