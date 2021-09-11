/*
 * Timer0.h
 *
 *  Created on: Jul 27, 2021
 *      Author: rahma
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#define COMPARE_MODE 1
#define NORMAL_MODE 0

#define Mode NORMAL_MODE
typedef enum { No_Clock , No_prescaling ,clk_8 ,clk_64 , clk_256 , clk_1024 , Externalfalling_clk , Externalrising_clk
} Prescaler;

typedef enum{ Normal , toggle ,clear , set

} compare_non_PWM_Mode;
typedef enum {
	Falling =6 , Rising =7
}Edge;
typedef enum{
	normal,Reserved,Clear , Set
}compare_Fast_PWM_Mode;

void timer0_init_normal_mode(uint8 , uint8 );
void timer0_init_compare_mode(uint8 , uint8 , uint8, uint8 );

void timer0_deinit(void);

#endif /* TIMER0_H_ */
