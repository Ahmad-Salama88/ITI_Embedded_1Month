
#include "UART.h"
void UART_INIT(uint16_t UBRR)
{
	UBRRH = (uint8_t)(UBRR>>8);	/* ERROR_1!! IT WAS --> (uint8_t)(UBRR)>>8 SO I LOST THE UPPER 4 BITS */
	UBRRL = (uint8_t)UBRR;

	/* Enable TX & RX */
	UCSRB |= (1<<RXEN) | (1<<TXEN) ;
	/* Default : ASYNC mode */
	UCSRC &= ~(1<<UMSEL);
	 	 	 	 	 	 	 /* SERIOUS !! */
	/* use register : 0x20 as UCSRC not UBBRH  as they have same register address*/
	UCSRC |= (1<<URSEL);
	/* 8-bit-data length (Char size) */
	UCSRC |= (1<<UCSZ0) | (1<<UCSZ1);
	UCSRB &= ~(1<<UCSZ2);
	/* Default : one stop bit selected */
	UCSRC &= ~(1<<USBS);		/* ERROR_2 !! IT WAS UCSRB (TXEN) !! */
}

void UART_TRANSMIT(uint8_t data)
{
	/* Check for buffer to be empty (from a previous transmitted data) */
	while(!(UCSRA & (1<<UDRE))); /* as long as it is 0  -- break when it is not 0*/
	/* AND it's cleared when there is any data */
	UDR = data;
}

uint8_t UART_RECIEV (void)
{
	/* Wait until recieving completes */
	while(!(UCSRA & (1<<RXC)));
	UCSRA |= (1<<RXC); /* Clear it as no ISR */
	return UDR;
}

void UART_TRANSMIT_STRING(uint8_t* str)
{
	uint8_t i = 0;
	while(str[i] != 0)
	{
		UART_TRANSMIT(str[i]);
		i++;
	}
}
