
/*
 * main.c
 *
 *  Created on: Jul 27, 2021
 *      Author: rahma
 */

#include "Functions.h"


uint8 g_tick = 0;
uint8 second;

/* Description :
 * For clock = 1Mhz and prescaler F_CPU/1024 every count will take 1 milli second
 * so put initial timer counter=5   5 --> 255 (0.25 sec per overflow)
 * so we need timer to overflow 4 times to get a 1 second
 * This is the ISR of timer0 overflow mode
 */
ISR(TIMER0_OVF_vect)
{
	g_tick++;
	if (g_tick ==Overflow_num)
	{
		second++;
		g_tick = 0;
	}
}


//START OF MAIN FUNCTION

int main(void)
{

	//Variable Declarations

	uint8 i,key
	,new_pass[7],match_pass[7],old_pass[7],match_pass2[7];

	//init lcd
	LCD_init();

	//init uart
	UART_init();
	LCD_sendCommand(CLEAR_COMMAND);
	LCD_displayStringRowColumn(0,0,"LCD Active");

	/* These statements for first password for new user just one time
	 * second MCU  don't have to check for any stranger
	 * as my user is new , there is no reserved data in E2PROM
	 */

	get_pass("Enter Pass", new_pass);
	_delay_ms(10);
	get_pass("Renter pass:",match_pass);
	F_compare(new_pass,match_pass,"Renter Pass:",READY1);


    while(1)
    {
    	/*
    	 * once the program started and get new password from new user you will
    	 * see the following messages
    	 */

		LCD_displayStringRowColumn(0,0,"= open the door");
		LCD_displayStringRowColumn(1,0,"+ change pass");
		_delay_ms(250);

		//Get user option to do specific actions on the second MCU

		key = KeyPad_getPressedKey(); /* get the pressed key number */
		_delay_ms(250); /* Press time  */

		if (key =='+'){
			get_pass("Enter old Pass:", old_pass);
			UART_sendByte(READY2);
			for(i=0;i<5;i++){
				while(UART_recieveByte()!=READY2){};
				match_pass2[i]=UART_recieveByte();
				_delay_ms(100);
			}
			//Check_Stranger(match_pass2,old_pass,"Renter old Pss:");
			F_compare(match_pass2,old_pass,"Renter old Pass:",READY3);
			get_pass("Enter new Pass:", new_pass);
			_delay_ms(10);
			get_pass("Renter Pass:",match_pass);
			F_compare(new_pass,match_pass,"Renter pass:",READY1);
		}

		else if(key=='='){
			get_pass("Enter your Pass:", new_pass);
			UART_sendByte(READY6);
			for(i=0;i<5;i++){
				while(UART_recieveByte()!=READY6){};
				match_pass2[i]=UART_recieveByte();
				_delay_ms(100);
			}

			F_compare(match_pass2,new_pass,"Renter your Pss:",READY7);
			_delay_ms(100);

			LCD_sendCommand(CLEAR_COMMAND);
			LCD_displayStringRowColumn(0,0,"DOOR OPENING");
			timer0_init_normal_mode(clk_1024, 5);
			while (second != 2);
			second = 0;

			LCD_sendCommand(CLEAR_COMMAND);

			LCD_displayStringRowColumn(0,0,"DOOR CLOSING");
			while (second != 2);
			second = 0;
		}
		LCD_sendCommand(CLEAR_COMMAND);
    }

}
