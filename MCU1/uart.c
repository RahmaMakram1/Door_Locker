/*
 * uart.c
 *
 *  Created on: Jul 27, 2021
 *      Author: rahma
 */

#include "uart.h"
#define BAUD_PRESCALE (((F_CPU / (Baud_Rate * 8UL))) - 1)
void UART_init(){
	UCSRA|=(1<<U2X);           //for double transmission rate
	UCSRB |=(1<<TXEN)|(1<<RXEN);           // transmitter and receiver enable
	UCSRC|= (1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL);         // UCSZ1 & UCSZ0 is 0 and UCSZ2 is 1 for8 bit mode and URSEL must be one for writing in UCSRC and URSEL is 0 for Asynchronous mode

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = BAUD_PRESCALE>>8;
	UBRRL = BAUD_PRESCALE;
}
void UART_sendByte(const uint8 data){
while  BIT_IS_CLEAR(UCSRA,UDRE); //polling until UDRE is set to one means that UDR is empty and ready for transmitting
UDR =data; // Data is stored in UDR and its now not empty make the UDRE cleared

}
uint8 UART_recieveByte(){
	while BIT_IS_CLEAR(UCSRA,RXC); //polling until receive complete , as RXC is set one when recieve complete
	return UDR; // read UART after receiving from UDR and the RXC flag  will be cleared after read this data
}
void UART_sendString(const uint8*Str){
	int i=0;
	while (Str[i]!='\0'){
		UART_sendByte(Str[i]);
		i++;
	}
}
void UART_recieveString(uint8*Str){

uint8 i = 0;
	Str[i] = UART_recieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0';}
