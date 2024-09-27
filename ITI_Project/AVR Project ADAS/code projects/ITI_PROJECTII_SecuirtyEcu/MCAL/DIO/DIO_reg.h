/**
 * DIO_reg.h
 *
 *  Created on: May 17, 2022
 *      Author: Mohammed Ramadan
 */

#ifndef MCAL_DIO_DIO_REG_H_
#define MCAL_DIO_DIO_REG_H_

/***
 *Control memory register
	*  DDRA
	*  DDRB
	*  DDRC
	*  DDRD
 */
#define DDRA    *((volatile u8 *)(0x3A))
#define DDRB    *((volatile u8 *)(0x37))
#define DDRC    *((volatile u8 *)(0x34))
#define DDRD    *((volatile u8 *)(0x31))

/***
 *OUTPUT memory register
	  *  PORTA
	  *  PORTB
	  *  PORTC
	  *  PORTD
 */
#define PORTA   *((volatile u8 *)(0x3B))
#define PORTB   *((volatile u8 *)(0x38))
#define PORTC   *((volatile u8 *)(0x35))
#define PORTD   *((volatile u8 *)(0x32))

/***
 *INPUT memory register
	  *  PINA
	  *  PINB
	  *  PINC
	  *  PIND
 */
#define PINA    *((volatile u8 *)(0x39))
#define PINB    *((volatile u8 *)(0x36))
#define PINC    *((volatile u8 *)(0x33))
#define PIND    *((volatile u8 *)(0x30))

#endif /** MCAL_DIO_DIO_REG_H_ */