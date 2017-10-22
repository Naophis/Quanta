/*
 * sensor.h
 *
 *  Created on: 2017/07/30
 *      Author: Naoto
 */

#ifndef SENSOR_H_
#define SENSOR_H_
void sensor_led_off() {
	PORTE.PODR.BIT.B1 = 0;
	PORTD.PODR.BIT.B7 = 0;
	PORT2.PODR.BIT.B7 = 0;
	PORT2.PODR.BIT.B5 = 0;
	PORT2.PODR.BIT.B4 = 0;
	PORT2.PODR.BIT.B3 = 0;
}
void getBattery();
void sensing_battery() {
	S12AD.ADANSA0.BIT.ANSA0 = 0x80; //battery
	S12AD.ADCSR.BIT.ADST = 1;
	while (S12AD.ADCSR.BIT.ADST)
		;
	getBattery();
}
void sensing_in_off() {
	S12AD.ADANSA0.BIT.ANSA0 = 0x7E; //battery
	S12AD.ADCSR.BIT.ADST = 1;
	while (S12AD.ADCSR.BIT.ADST)
		;
	RF_SEN1.off = RF;
	RS_SEN1.off = RS;
	LS_SEN1.off = LS;
	LF_SEN1.off = LF;
	RS_SEN2.off = RS2;
	LS_SEN2.off = LS2;
}

void sensing_side2() {
	S12AD.ADANSA0.BIT.ANSA0 = 0x24;
	S12AD.ADCSR.BIT.ADST = 1;
	while (S12AD.ADCSR.BIT.ADST)
		;
	LS_SEN2.on = LS2;
	RS_SEN2.on = RS2;
}

void sensing_side() {
	S12AD.ADANSA0.BIT.ANSA0 = 0x18;
	S12AD.ADCSR.BIT.ADST = 1;
	while (S12AD.ADCSR.BIT.ADST)
		;
	LS_SEN1.on = LS;
	RS_SEN1.on = RS;
}

void sensing_front() {
	S12AD.ADANSA0.BIT.ANSA0 = 0x42;
	S12AD.ADCSR.BIT.ADST = 1;
	while (S12AD.ADCSR.BIT.ADST)
		;
	LF_SEN1.on = LF;
	RF_SEN1.on = RF;
}

#endif /* SENSOR_H_ */
