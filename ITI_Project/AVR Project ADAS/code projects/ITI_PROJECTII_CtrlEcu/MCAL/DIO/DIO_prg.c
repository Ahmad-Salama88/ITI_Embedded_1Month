/**
 * DIO_prg.c
 *
 *  Created on: May 17, 2022
 *      Author: Al-Mostafa
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "DIO_int.h"

void MDIO_voidSetPinDir (u8 A_u8PortNo , u8 A_u8PinNo , u8 A_u8PinDir)
{
	switch (A_u8PortNo)
	    {
	    case DIO_PORTA : WRT_BIT(DDRA , A_u8PinNo , A_u8PinDir) ; break ;
	    case DIO_PORTB : WRT_BIT(DDRB , A_u8PinNo , A_u8PinDir) ; break ;
	    case DIO_PORTC : WRT_BIT(DDRC , A_u8PinNo , A_u8PinDir) ; break ;
	    case DIO_PORTD : WRT_BIT(DDRD , A_u8PinNo , A_u8PinDir) ; break ;
	    default : /**Error*/ break ;
	    }
}

void MDIO_voidSetPinVal (u8 A_u8PortNo , u8 A_u8PinNo)
{
	switch (A_u8PortNo)
		{
		case DIO_PORTA : SET_BIT(PORTA , A_u8PinNo ) ; break ;
		case DIO_PORTB : SET_BIT(PORTB , A_u8PinNo ) ; break ;
		case DIO_PORTC : SET_BIT(PORTC , A_u8PinNo ) ; break ;
		case DIO_PORTD : SET_BIT(PORTD , A_u8PinNo ) ; break ;
		default : /**Error*/ break ;
		}
}

u8   MDIO_u8GetPinVal   (u8 A_u8PortNo , u8 A_u8PinNo)
{
	u8 L_u8PinVal ;
	switch (A_u8PortNo)
		{
		case DIO_PORTA : L_u8PinVal = READ_BIT(PINA , A_u8PinNo) ; break ;
		case DIO_PORTB : L_u8PinVal = READ_BIT(PINB , A_u8PinNo) ; break ;
		case DIO_PORTC : L_u8PinVal = READ_BIT(PINC , A_u8PinNo) ; break ;
		case DIO_PORTD : L_u8PinVal = READ_BIT(PIND , A_u8PinNo) ; break ;
		default : /**Error*/ break ;
		}
	return L_u8PinVal ;
}

void MDIO_voidSetPortVal (u8 A_u8PortNo , u8 A_u8PortVal)
{
	switch (A_u8PortNo)
		{
		case DIO_PORTA : PORTA = A_u8PortVal  ; break ;
		case DIO_PORTB : PORTB = A_u8PortVal  ; break ;
		case DIO_PORTC : PORTC = A_u8PortVal  ; break ;
		case DIO_PORTD : PORTD = A_u8PortVal  ; break ;
		default : /**Error*/ break ;
		}
}

void MDIO_voidSetPortDir (u8 A_u8PortNo , u8 A_u8PortVal)
{
	switch (A_u8PortNo)
		{
		case DIO_PORTA : DDRA = A_u8PortVal  ; break ;
		case DIO_PORTB : DDRB = A_u8PortVal  ; break ;
		case DIO_PORTC : DDRC = A_u8PortVal  ; break ;
		case DIO_PORTD : DDRD = A_u8PortVal  ; break ;
		default : /**Error*/ break ;
		}
}

u8   MDIO_u8GetPortVal   (u8 A_u8PortNo)
{
	u8 L_u8PinVal ;
	switch (A_u8PortNo)
		{
		case DIO_PORTA : L_u8PinVal = PINA ; break ;
		case DIO_PORTB : L_u8PinVal = PINB ; break ;
		case DIO_PORTC : L_u8PinVal = PINC ; break ;
		case DIO_PORTD : L_u8PinVal = PIND ; break ;
		default : /**Error*/ break ;
		}
	return L_u8PinVal ;
}

void MDIO_voidClrPinVal (u8 A_u8PortNo , u8 A_u8PinNo)
{
	switch (A_u8PortNo)
		{
		case DIO_PORTA : CLR_BIT(PORTA , A_u8PinNo) ; break ;
		case DIO_PORTB : CLR_BIT(PORTB , A_u8PinNo) ; break ;
		case DIO_PORTC : CLR_BIT(PORTC , A_u8PinNo) ; break ;
		case DIO_PORTD : CLR_BIT(PORTD , A_u8PinNo) ; break ;
		default : /**Error*/ break ;
		}
}

void MDIO_voidClrPort (u8 A_u8PortNo)
{
	switch (A_u8PortNo)
		{
		case DIO_PORTA : PORTA = ALL_PINS_ZERO ; break ;
		case DIO_PORTB : PORTB = ALL_PINS_ZERO ; break ;
		case DIO_PORTC : PORTC = ALL_PINS_ZERO ; break ;
		case DIO_PORTD : PORTD = ALL_PINS_ZERO ; break ;
		default : /**Error*/ break ;
		}
}

void MDIO_voidTogPinVal (u8 A_u8PortNo , u8 A_u8PinNo)
{
	switch (A_u8PortNo)
		{
		case DIO_PORTA : TOG_BIT(PORTA , A_u8PinNo) ; break ;
		case DIO_PORTB : TOG_BIT(PORTB , A_u8PinNo) ; break ;
		case DIO_PORTC : TOG_BIT(PORTC , A_u8PinNo) ; break ;
		case DIO_PORTD : TOG_BIT(PORTD , A_u8PinNo) ; break ;
		default : /**Error*/ break ;
		}
}

void MDIO_voidTogPort (u8 A_u8PortNo)
{
	switch (A_u8PortNo)
		{
		case DIO_PORTA : PORTA = ~PORTA ; break ;
		case DIO_PORTB : PORTB = ~PORTB ; break ;
		case DIO_PORTC : PORTC = ~PORTC ; break ;
		case DIO_PORTD : PORTD = ~PORTD ; break ;
		default : /**Error*/ break ;
		}
}

void MDIO_voidWriteLowNibble (u8 A_u8PortNo , u8 A_u8PortVal)
{
	A_u8PortVal = A_u8PortVal & LOW_NIBBLE_OUTPUT ;
	switch (A_u8PortNo)
		{
		case DIO_PORTA : PORTA = PORTA & HIGH_NIBBLE_OUTPUT ;
						 PORTA = PORTA | A_u8PortVal        ;
		                 break ;                        
		case DIO_PORTB : PORTB = PORTB & HIGH_NIBBLE_OUTPUT ;
						 PORTB = PORTB | A_u8PortVal        ;		
		                 break ;                        
		case DIO_PORTC : PORTC = PORTC & HIGH_NIBBLE_OUTPUT ; 
						 PORTC = PORTC | A_u8PortVal        ;		
		                 break ;                        
		case DIO_PORTD : PORTD = PORTD & HIGH_NIBBLE_OUTPUT ;
						 PORTD = PORTD | A_u8PortVal        ;		
		                 break ;
		default : /**Error*/ break ;
		}
}

void MDIO_voidWriteHighNibble (u8 A_u8PortNo , u8 A_u8PortVal)
{
	A_u8PortVal = A_u8PortVal << FOUR_BITS ;
	switch (A_u8PortNo)
		{
		case DIO_PORTA : PORTA = PORTA & LOW_NIBBLE_OUTPUT ; 
						 PORTA = PORTA | A_u8PortVal       ;
		                 break ;                      
		case DIO_PORTB : PORTB = PORTB & LOW_NIBBLE_OUTPUT ; 
						 PORTB = PORTB | A_u8PortVal       ;
		                 break ;               
		case DIO_PORTC : PORTC = PORTC & LOW_NIBBLE_OUTPUT ; 
						 PORTC = PORTC | A_u8PortVal       ;
		                 break ;                        
		case DIO_PORTD : PORTD = PORTD & LOW_NIBBLE_OUTPUT ;
						 PORTD = PORTD | A_u8PortVal       ;
		                 break ;
		default : /**Error*/ break ;
		}
}

void MDIO_voidConnectPullup(u8 A_u8PortNo ,u8 A_u8PinNo, u8 A_u8ConnectPullup)
{
	switch (A_u8ConnectPullup)
	{
	case ENABLE_PULLUP  : MDIO_voidSetPinVal (A_u8PortNo , A_u8PinNo) ;break ;
	case DISABLE_PULLUP : MDIO_voidClrPinVal (A_u8PortNo , A_u8PinNo) ;break ;
	default : /**Error*/ break ;
	}
}
