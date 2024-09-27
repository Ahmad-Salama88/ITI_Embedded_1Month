/*
 * KP_conf.h
 *
 *  Created on: May 18, 2022
 *      Author: Mohamed Ramadan
 */

#ifndef HAL_KEY_PAD_KP_CONF_H
#define HAL_KEY_PAD_KP_CONF_H
#include "KP_private.h"
#include "KP_conf.h"
#include "KP_int.h"
/**
 * Key Pad connections 
 * Options :
        *DIO_PORTA
		*DIO_PORTB
		*DIO_PORTC
		*DIO_PORTD
*/
#define KP_PORT  DIO_PORTA

/**
 * Options of first Column connection 
        *DIO_PIN0
		*DIO_PIN4
 */ 
#define COL_START   DIO_PIN0

/**
 * Options of end Column connection 
        *DIO_PIN3
		*DIO_PIN7
 */
#define COL_END     DIO_PIN3

/**
 * Options of first Row connection 
        *DIO_PIN0
		*DIO_PIN4
 */
#define ROW_START   DIO_PIN4

/**
 * Options of end Row connection 
        *DIO_PIN3
		*DIO_PIN7
 */
#define ROW_END     DIO_PIN7

/**
 *Define Size of Rows & Columns
 */
#define ROW_SIZE    4
#define COL_SIZE    4


#endif /* HAL_KEY_PAD_KP_CONF_H */
