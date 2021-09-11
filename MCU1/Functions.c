/*
 * Functions.c
 *
 *  Created on: Jul 27, 2021
 *      Author: rahma
 */

#include "Functions.h"
uint8 second;
void get_pass(char arr[],uint8 sent_pass[]){
	uint8 key;
	LCD_sendCommand(CLEAR_COMMAND);
	LCD_displayStringRowColumn(0,0,arr);
	LCD_goToRowColumn(1,0);
	for (int i=0 ;i<5 ; i++){
		key=KeyPad_getPressedKey(); // get pressed key
		_delay_ms (250); // no pressed key can until 250 ms , if key pressed more than 500 milli seconds its count more than press
		LCD_displayCharacter('*');
		sent_pass[i]=key;

	}

	key=KeyPad_getPressedKey();

	while (key!=13){
	LCD_sendCommand(CLEAR_COMMAND);
	LCD_displayStringRowColumn(0,0,"press on/c on Err");
	key = KeyPad_getPressedKey(); /* get the pressed key number */
	_delay_ms(250); /* Press time  */}
	if (key==13){
		LCD_sendCommand(CLEAR_COMMAND);

	}
}
uint8 compare(uint8 new_pass[], uint8 match_pass[] ){
	int j=0;
	/* int j=0;
	 while (j!=5){
		if( new_pass [j]== match_pass[j])
		{j++;}

	 }
	 return j;*/
	for (int i=0 ; i<5 ; i++)
	{if (new_pass [i]== match_pass[i]){
		j++;

	}}
	if (j==5){LCD_sendCommand(CLEAR_COMMAND);
	LCD_displayStringRowColumn(0,0,"Matched password");}
	else {LCD_sendCommand(CLEAR_COMMAND);
	LCD_displayStringRowColumn(0,0," Not Matched password");}
	return j;  /*this function compare each element in two arrays check if two are matched or not*/
}
void F_compare(uint8 new_pass[], uint8 match_pass[],char arr[],enum Ready R){
	int j ,z=0;
	j= compare(new_pass, match_pass);
	while (j!=5){
		get_pass(arr, match_pass);
		j= compare(new_pass, match_pass);
		z++;
		if (z==3){
			UART_sendByte(READY4);
			_delay_ms(100);
			 LCD_sendCommand(CLEAR_COMMAND);
			 LCD_displayStringRowColumn(0,0,"Thief!");
			 timer0_init_normal_mode(clk_1024, 5);
			 while (second != 4);
			 second = 0;
			 LCD_sendCommand(CLEAR_COMMAND);
			 LCD_displayStringRowColumn(0,0,"Reopen system.");
			 _delay_ms(10000);
			 LCD_sendCommand(CLEAR_COMMAND);
			 _delay_ms(100000);
			 z=0;
		}
	}
	if (j==5){
	UART_sendByte(R);
	for (int i=0 ;i<5; i++){
		while (UART_recieveByte()!=R);
		UART_sendByte(new_pass[i]);

	}
	}
	}

