/*
 * I2c.c
 *
 *  Created on: Jul 28, 2021
 *      Author: rahma
 */
#include "I2c.h"
void TWI_init(void){
	 TWCR = (1<<TWEN);
	 /* Bit Rate: 62.000 kbps using zero pre-scaler TWPS=00 and F_CPU=1Mhz */
	    TWBR =  0x02;
	 	TWSR = 0x00;
}
 void TWI_start(void){
	/*TWINT Bit is flag that is set when TWI finishes its current job so it must be cleared by setting
	 * one to it and TWSTA is Start bit , TWEN is TWI Enable
	 */
	TWCR|=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (BIT_IS_CLEAR(TWCR,TWINT));
	//wait until TWI start successfully by setting 1 to TWINT

}
void TWI_stop(void){
	TWCR|=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	/* TWINT Must be cleared before sending stop bit
	 * Stop bit TWSTO is set
	 * TWEN TWI Enable bit
	 */
}
void TWI_write(uint8 data){
	TWDR=data;
	 TWCR = (1 << TWINT) | (1 << TWEN);
	 //wait until TWI start successfully by setting 1 to TWINT
	  while(BIT_IS_CLEAR(TWCR,TWINT));
}
uint8 TWI_readWithACK(void){
	//after reading or recieving enable sending ack TWEA =1
	// Clear TWINT before recieving
	// Enable TWI
	TWCR = (1 << TWINT) | (1 << TWEN)|(1<<TWEA);

     //wait until TWI start successfully by setting 1 to TWINT
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}
uint8 TWI_readWithNACK(void){

		// Clear TWINT before recieving
		// Enable TWI
		TWCR = (1 << TWINT) | (1 << TWEN);

	     //wait until TWI start successfully by setting 1 to TWINT
		while(BIT_IS_CLEAR(TWCR,TWINT));
		return TWDR;
}
uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}

