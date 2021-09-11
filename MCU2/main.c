/*
 * main.c
 *
 *  Created on: Jul 28, 2021
 *      Author: rahma
 */


#include "Functions.h"


uint8 g_tick = 0;
uint8 second;

/* Description :
 * For clock = 1Mhz and prescaler F_CPU/1024 every count will take milli second
 * so put initial timer counter=5  0 --> 255 (per overflow)
 * so we need timer to overflow 4 times to get a 1 second
 * This is the ISR of timer0 overflow mode
 */

ISR(TIMER0_OVF_vect)
{
	g_tick++;
	if (g_tick == overflow_num)
	{
		second++;
		g_tick = 0;
	}
}




int main(){
UART_init();
EEPROM_init();
uint8 i, arr[7];
recieve_write(READY1);
while (1){
	uint8 recieve = UART_recieveByte();
	if (recieve ==READY2){
		while (recieve !=READY2);
		for(i=0;i<5;i++){
			UART_sendByte(READY2);
			EEPROM_readByte((0x000|i),&arr[i]);
			 UART_sendByte(arr[i]);
			_delay_ms(100);

		}
		recieve_write (READY3);
		recieve_write (READY1);
	}
	else if (recieve== READY6){
	while (recieve !=READY6);
	for (i=0; i<5 ;i++){
		UART_sendByte (READY6);
		EEPROM_readByte((0x000|i),&arr[i]);
		 UART_sendByte(arr[i]);
		_delay_ms(100);

	}
	uint8 RERECIEVE=UART_recieveByte();

  if (RERECIEVE==READY4){
	while (RERECIEVE!= READY4);
	_delay_ms(100);
	SET_BIT(DDRA,0);
	SET_BIT(PORTA,0);
	 timer0_init_normal_mode(clk_1024 , 5 );
	 while (second!=4);
	 second = 0;
	 CLEAR_BIT(PORTA,0);

  }
else if (RERECIEVE==READY7){
	for(i=0;i<5;i++){
	UART_sendByte(READY7);
	arr[i]=UART_recieveByte();
	EEPROM_writeByte((0x000|i),arr[i]);
	_delay_ms(100);
}

timer0_init_normal_mode(clk_1024, 5);
			motoropen();

			while (second != 2);
			second=0;

			motorclose();
			while (second != 2);
			second = 0;
			PORTB=0XFC;
			timer0_deinit();
			}
}

}
}
