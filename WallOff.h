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

void walloff1(char RorL) {
	if (RorL == R) {
		while (SEN_R < R_WALL_OFF && distance <= wall_off_limit) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
		while (SEN_R > R_WALL_OFF && distance <= wall_off_limit) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	} else {
		while (SEN_L < L_WALL_OFF && distance <= wall_off_limit) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
		while (SEN_L > L_WALL_OFF && distance <= wall_off_limit) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	}
}
void walloff2(char RorL) {
	if (RorL == R) {
		while (SEN_R > R_WALL_OFF2 && distance <= wall_off_limit) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	} else {
		while (SEN_L > L_WALL_OFF2 && distance <= wall_off_limit) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	}
}

char wallOff(char RorL) {
	if (dia == 1) {
		return wallOff_D(RorL);
	}
	sensingMode = AtackStraight;
	positionControlValueFlg = 1;
	ang = 0;
	angle = 0;
	distance = 0;
	if (RorL == R) {
		if (SEN_R < existRightWall4) {
			walloff1(R);
		} else {
			walloff2(R);
		}
	} else {
		if (SEN_L < existLeftWall4) {
			walloff1(L);
		} else {
			walloff2(L);
		}
	}
	positionControlValueFlg = 0;
	return 1;
}

void walloff3(char RorL) {
	if (RorL == R) {
		while (SEN_R < R_WALL_OFF_D && distance <= wall_off_limit_d) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
		while (SEN_R > R_WALL_OFF_D && distance <= wall_off_limit_d) {
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
}
void walloff4(char RorL) {
	if (RorL == R) {
		while (SEN_R > R_WALL_OFF_D2 && distance <= wall_off_limit_d) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	} else {
		while (SEN_L > L_WALL_OFF_D2 && distance <= wall_off_limit_d) {
			if (!fail) {
				positionControlValueFlg = 0;
				break;
			}
		}
	}
}

char wallOff_D(char RorL) {
//	positionControlValueFlg = 1;
	ang = 0;
	angle = 0;
	distance = 0;
	sensingMode = AtackDia;
	if (RorL == R) {
		if (SEN_R < existRightWall5) {
			walloff3(R);
		} else {
			walloff4(R);
		}
	} else {
		if (SEN_L < existLeftWall5) {
			walloff3(L);
		} else {
			walloff4(L);
		}
	}
	positionControlValueFlg = 0;
	return 1;
}
#endif /* WALLOFF_H_ */
