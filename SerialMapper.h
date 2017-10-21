/*
 * SerialMapper.h
 *
 *  Created on: 2017/08/17
 *      Author: Naoto
 */

#ifndef SERIALMAPPER_H_
#define SERIALMAPPER_H_

#include "string.h"
#include <stdlib.h>

#define STAY 0
#define KEY 1
#define VALUE 2
#define END 3
volatile int recieveMode = STAY;
volatile char lastData = 0;
#define MAX_BUFFER 20
typedef struct {
	int index;
	int length;
	char buffer[MAX_BUFFER];
} s_key;
volatile s_key keys, values;

void pushKey(char key) {
	if (keys.length < MAX_BUFFER) {
		keys.buffer[keys.length] = key;
		keys.length++;
	}
}
void pushValue(char val) {
	if (values.length < MAX_BUFFER) {
		values.buffer[values.length] = val;
		values.length++;
	}
}
void flushData() {
	for (int i = 0; i < MAX_BUFFER; i++) {
		keys.buffer[i] = values.buffer[i] = 0;
	}
	keys.index = keys.length = values.index = values.length = 0;
}
char writeParam(int key, float val);
void mapping() {
	long key = atoi(keys.buffer);
	double value = atof(values.buffer);
	myprintf("%d	%f\r\n", key, value);
	writeParam((int) key, (float) value);
	flushData();
}
void applyRecieveData(char type, char data) {
	if (type == KEY) {
		pushKey(data);
	} else if (type == VALUE) {
		pushValue(data);
	} else if (type == END) {
		mapping();
	} else if (type == STAY) {
	}
}
void detectChar() {
	SCI1.SSR.BIT.RDRF = 0; // 受信フラグを解除
	char recieveData = SCI1.RDR;
	lastData = recieveData;
	if (!enableSciUpdate) {
		return;
	}
	switch (recieveData) {
	case '{':
		recieveMode = KEY;
		break;
	case '}':
		recieveMode = END;
		applyRecieveData(recieveMode, recieveData);
		break;
	case ':':
		recieveMode = VALUE;
		break;
	default:
		applyRecieveData(recieveMode, recieveData);
		break;
	}
}

#endif /* SERIALMAPPER_H_ */
