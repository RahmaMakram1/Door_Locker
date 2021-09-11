/*
 * Functions.h
 *
 *  Created on: Jul 28, 2021
 *      Author: rahma
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include "Eeprom.h"
#include "uart.h"
#include "Timer0.h"

enum READY{
	READY1=10,
	READY2=20,
	READY3=30,
	READY4=40,
	READY5=50,
	READY6=60, READY7=70
};
#define overflow_num 4
void motoropen();
void motorclose();
void recieve_write(enum READY R);


#endif /* FUNCTIONS_H_ */
