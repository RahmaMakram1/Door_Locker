/*
 * Functions.c
 *
 *  Created on: Jul 28, 2021
 *      Author: rahma
 */

#include "Functions.h"
uint8 second=0;
void motoropen(){
	    DDRB |= 0x03; //output pins PB0, PB1
		PORTB |= (1<<PB1);
		PORTB &= (~(1<<PB0));
		// Rotate the motor --> clock wise
		_delay_ms(1000);
}
void motorclose(){
	DDRB |= 0x03;
	PORTB &= ~(1<<PB1);
	PORTB |= (1<<PB0);
	_delay_ms(1000);
}
void recieve_write(enum READY R){

	int i , arr [7];
	uint8 recieve = UART_recieveByte();
	while (recieve != R);
	for (i=0;i<5;i++){
		UART_sendByte(R);
		arr[i]=UART_recieveByte();
		EEPROM_writeByte((0x000|i),arr[i]);
				_delay_ms(100);
	}
}
