/*
 * Timer0.c
 *
 *  Created on: Jul 27, 2021
 *      Author: rahma
 */

#include "Timer0.h"
extern volatile uint8 second;
#if Mode == NORMAL_MODE
void timer0_init_normal_mode(uint8 prescaler , uint8 initial ){
	/* we can use prescalers No_Clock , No_prescaling ,clk_8 ,clk_64 , clk_256 , clk_1024 , Externalfalling_clk , Externalrising_clk
	 *The Timer Frequency is FCPU divided by Prescaler , and Timer clock is 1/TimerFrequency
	 *Time overflow time = timer count * timer clock
	 *to get number of overflows for one second divide 1sec over overflow time
      to get it more accurately we intialize TCNT0 by intial
      intial :the value that the timer will start count from,
			it varies from 0 to 255.

	 */

	second=0;
	SREG  |= (1<<7);    // global interrupt bit.
	TCNT0 = initial;  // the value that the timer will start count from.
	TIMSK |= (1<<TOIE0);    // interrupt enable bit for Timer0 in normal mode.
	TCCR0 = (1<<FOC0);    // this bit is set to one for any non-PWM mode.
	TCCR0 = (TCCR0 & 0xF8) | (prescaler & 0x07);  // Prescaler.
}
#elif Mode ==COMPARE_MODE
void timer0_init_compare_mode(uint8 prescaler , uint8 initial, uint8 tick, uint8 mode )
{/* we can use prescalers No_Clock , No_prescaling ,clk_8 ,clk_64 , clk_256 , clk_1024 , Externalfalling_clk , Externalrising_clk
 *The Timer Frequency is FCPU divided by Prescaler , and Timer clock is 1/TimerFrequency
 *TCNT0 get initialized by initial
 *tick is the value that timer will count to it stored in OCR0 when it reach it it starts count from begining it varies from 0 to 255 */
	SREG  |= (1<<7);  // global interrupt bit.
			TCNT0 = initial;  // the value that the timer will start count from.
			OCR0 = tick;  // the value that the timer will count to.
			TIMSK |= (1<<OCIE0);  // interrupt enable bit for Timer0 in compare mode.
			TCCR0 = (1<<FOC0) | (1<<WGM01);  //  enable compare mode.
			TCCR0 = (TCCR0 & 0xF8) | (prescaler & 0x07) |(mode & 0x30);  // Prescaler and compare output mode non pwm

		}

#endif
void timer0_deinit(void){
	/*
	 * This function is set to Deinit(stop) Time0.
	 */
	TCCR0 = 0;
}
