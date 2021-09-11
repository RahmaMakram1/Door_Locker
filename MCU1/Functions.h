/*
 * Functions.h
 *
 *  Created on: Jul 27, 2021
 *      Author: rahma
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "Timer0.h"
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#define Overflow_num 4
 enum Ready {

	READY1=10,
	READY2=20,
	READY3=30,
	READY4=40,
	READY5=50,
	READY6=60,
	READY7=70
} ;            // these are the orders that will be sent to other microcontroller

void get_pass(char arr[],uint8 sent_pass[]);
uint8 compare(uint8 new_pass[], uint8 match_pass[] );
void F_compare(uint8 new_pass[], uint8 match_pass[],char arr[],enum Ready R);

#endif /* FUNCTIONS_H_ */
