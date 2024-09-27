/*
 * TWI_EEPROM.h
 *
 *  Created on: ???/???/????
 *      Author: Ahmad
 */

#ifndef MCAL_TWI_EEPROM_H_
#define MCAL_TWI_EEPROM_H_



/*
 * IMPORTANT NOTES & BIG LESSON :
 *  note : TWCR |= (1<<TWINT) | (1<<TWEN); is written for every function
 *	note : We make "TWCR =" NOT "TWCR |=" not to left over any bits from previous states
 *
 *	THE BIG LESSON FOR TODAY : Do what's been done char by char
 *	AND after it works like him, then modify & try what you want !
 *
 *	BIG NOTE : These likes of codes is steps, you code what he says
 *	To get in detail what is going on is hard and not priority now.
 *
 *
 *	{
 *	TWDR = data;
	TWCR = (1<<TWEN) | (1<<TWINT); /* signal that the data in TWDR is ready to sent
	 * so if I reverse the order of these 2 statements, the data stayed in the buffer,
	 * 		no assignment until the next comm cycle

*/

#define F_CPU 	8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>

#define EEPROM_Write_Addess		0xA0 //1010000 0	/* 1010 000 default address + W/R bit */
#define EEPROM_Read_Addess		0xA1 //1010000 1

void TWI_INIT(void);
void TWI_START (void);
void TWI_STOP (void);
void TWI_WRITE(char data);
char TWI_READACK (void);
char TWI_READNACK (void);
char TWI_GETSTATUS (void);

void READ_EEPROM(char Address,char*str);
void WRITE_EEPROM(char Address,char*str);

#endif /* MCAL_TWI_EEPROM_H_ */
