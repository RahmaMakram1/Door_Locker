/*
 * uart.h
 *
 *  Created on: Jul 27, 2021
 *      Author: rahma
 */

#ifndef UART_H_
#define UART_H_
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#define Baud_Rate 9600
void UART_init();
void UART_sendByte(const uint8 data);
uint8 UART_recieveByte();
void UART_sendString(const uint8*Str);
void UART_recieveString( uint8*Str);

#endif /* UART_H_ */
