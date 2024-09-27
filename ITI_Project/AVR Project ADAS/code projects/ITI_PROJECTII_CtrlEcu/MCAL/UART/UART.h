/*
 * UART.h
 *
 *  Created on: ???/???/????
 *      Author: Ahmad
 */

#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 	 8000000UL
#define BAUD_RATE 9600
#define MY_UBRR 	 (F_CPU/16/BAUD_RATE - 1) // (essential for spaces )

void UART_INIT(uint16_t UBRR);
void UART_TRANSMIT(uint8_t data);	/* They share the same UDR */
uint8_t UART_RECIEV (void);			/* They share the same UDR */
void UART_TRANSMIT_STRING(uint8_t* str);


#endif /* MCAL_UART_UART_H_ */
