/**
 * DIO_private.h
 *
 *  Created on: May 17, 2022
 *      Author: Mohammed Ramadan
 */

#ifndef MCAL_DIO_DIO_PRIVATE_H_
#define MCAL_DIO_DIO_PRIVATE_H_
/***
 *Four PORTs 
      *PORTA
      *PORTB
      *PORTC
      *PORTD
 */
#define DIO_PORTA      1
#define DIO_PORTB      2
#define DIO_PORTC      3
#define DIO_PORTD      4

/***
 *Each PORT have eight pins
      *PIN0
      *PIN1
      *PIN2
      *PIN3
	  *PIN4
	  *PIN5
	  *PIN6
      *PIN7
 */	   
#define DIO_PIN0        0                      
#define DIO_PIN1        1
#define DIO_PIN2        2
#define DIO_PIN3        3
#define DIO_PIN4        4
#define DIO_PIN5        5
#define DIO_PIN6        6
#define DIO_PIN7        7

/***
 *Direction pin selection 
      *OUTPUT_PIN
      *INPUT_PIN 
 */
#define DIO_OUTPUT_PIN 1
#define DIO_INPUT_PIN  0

/***
 *OUTPUT pin selection 
      *HIGH
      *LOW 
 */
#define DIO_HIGH 1
#define DIO_LOW  0

/***
 * Clear all pins
*/
#define ALL_PINS_ZERO 0x00

/***
 * SET all pins
*/
#define ALL_PINS_ONE  0xFF

/***
 *two nibbles of port
      *LOW_NIBBLE
	  *HIGH_NIBBLE
*/
#define LOW_NIBBLE_OUTPUT  0x0f
#define HIGH_NIBBLE_OUTPUT 0xf0

#define ONE_BIT     1
#define TWO_BITS    2
#define THREE_BITS  3
#define FOUR_BITS   4
#define FIVE_BITS   5
#define SIX_BITS    6
#define SEVEN_BITS  7
#define EIGHT_BITS  8

/***
 *options of pullup connection
        *ENABLE_PULLUP 
        *DISABLE_PULLUP
*/
#define ENABLE_PULLUP  1
#define DISABLE_PULLUP 2

#endif /** MCAL_DIO_DIO_PRIVATE_H_ */
