/**
 * DIO_int.h
 *
 *  Created on: May 17, 2022
 *      Author: Mohammed Ramadan
 */

#ifndef MCAL_DIO_DIO_INT_H_
#define MCAL_DIO_DIO_INT_H_

#include "DIO_reg.h"
#include "DIO_private.h"

/**
	Function Name        : MDIO_voidSetPinDir
	Function Returns     : void
	Function Arguments   : u8 A_u8PortNo , u8 A_u8PinNo , u8 A_u8PinDir
	Function Description : Set the direction of the given pin in the given port (direction 0 = input : 1 = output)
*/
void MDIO_voidSetPinDir (u8 A_u8PortNo , u8 A_u8PinNo , u8 A_u8PinDir) ;

/**
	Function Name        : MDIO_voidSetPinVal
	Function Returns     : void
	Function Arguments   : u8 A_u8PortNo , u8 A_u8PinNo
	Function Description : Set the value of the given pin in the given port with high
*/
void MDIO_voidSetPinVal (u8 A_u8PortNo , u8 A_u8PinNo) ;

/**
	Function Name        : MDIO_u8GetPinVal
	Function Returns     : unsigned char
	Function Arguments   : u8 A_u8PortNo , u8 A_u8PinNo
	Function Description : Returns 1 if the value of the given pin is high and zero if the value is low
*/
void MDIO_voidClrPinVal (u8 A_u8PortNo , u8 A_u8PinNo) ;

/**
	Function Name        : MDIO_voidClrPort
	Function Returns     : void
	Function Arguments   : u8 A_u8PortNo
	Function Description : Write zero to all port pins.
*/
u8   MDIO_u8GetPinVal   (u8 A_u8PortNo , u8 A_u8PinNo) ;

/**
	Function Name        : MDIO_voidSetPortDir
	Function Returns     : void
	Function Arguments   : u8 A_u8PortNo , u8 A_u8PortVal
	Function Description : set the direction of whole port .
*/
void MDIO_voidTogPinVal (u8 A_u8PortNo , u8 A_u8PinNo) ;

/**
	Function Name        : MDIO_voidClrPinVal
	Function Returns     : void
	Function Arguments   : u8 A_u8PortNo , u8 A_u8PinNo
	Function Description : Set the value of the given pin in the given port with low
*/
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

void MDIO_voidSetPortDir (u8 A_u8PortNo , u8 A_u8PortVal) ;

/**
	Function Name        : MDIO_voidSetPortVal
	Function Returns     : void
	Function Arguments   : u8 A_u8PortNo , u8 A_u8PortVal
	Function Description : Write the value to all port pins.
*/
void MDIO_voidSetPortVal (u8 A_u8PortNo , u8 A_u8PortVal) ;

/**
	Function Name        : MDIO_u8GetPortVal
	Function Returns     : unsigned char
	Function Arguments   : u8 A_u8PortNo
	Function Description : read the value of the port .
*/
u8   MDIO_u8GetPortVal   (u8 A_u8PortNo) ;

/**
	Function Name        : MDIO_voidWriteHighNibble
	Function Returns     : void
	Function Arguments   : u8 A_u8PortNo , u8 A_u8PinVal
	Function Description : write a value to the high nibble of the port
*/
void MDIO_voidWriteHighNibble (u8 A_u8PortNo , u8 A_u8PortVal) ;

/**
	Function Name        : MDIO_voidWriteLowNibble
	Function Returns     : void
	Function Arguments   : u8 A_u8PortNo , u8 A_u8PinVal
	Function Description : write a value to the low nibble of the port
*/
void MDIO_voidWriteLowNibble (u8 A_u8PortNo , u8 A_u8PortVal) ;

/**
	Function Name        : MDIO_voidTogPort
	Function Returns     : void
	Function Arguments   : u8 A_u8PortNo
	Function Description : Reverse the value to all port pins.
*/
void MDIO_voidTogPort (u8 A_u8PortNo) ;

/**
	Function Name        : MDIO_voidTogPinVal
	Function Returns     : void
	Function Arguments   : u8 A_u8PortNo , u8 A_u8PinNo
	Function Description : Reverse the value of the given pin in the given port.
*/

void MDIO_voidClrPort (u8 A_u8PortNo) ;

/**
	Function Name        : MDIO_voidConnectPullup
	Function Returns     : void
	Function Arguments   : u8 A_u8PortNo ,u8 A_u8PinNo, u8 A_u8ConnectPullup
	Function Description : Connect and disconnect pull up resistor to the given pin at the given port
*/
void MDIO_voidConnectPullup(u8 A_u8PortNo ,u8 A_u8PinNo, u8 A_u8ConnectPullup);

#endif /* MCAL_DIO_DIO_INT_H_ */
