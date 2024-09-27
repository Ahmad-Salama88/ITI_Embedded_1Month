/*
 * Pb_conf.h
 *
 *  Created on: May 18, 2022
 *      Author: Mohamed Ramadan
 */

#ifndef HAL_PUSH_BOTTON_PB_CONF_H
#define HAL_PUSH_BOTTON_PB_CONF_H
/**
      ** Connections **
	  
 *Options of Pbx_PORT are :
            *DIO_PORTA
			*DIO_PORTB
			*DIO_PORTC
			*DIO_PORTD

 *Options of Pbx_PIN are :
            *DIO_PIN0
			*DIO_PIN1
			*DIO_PIN2
			*DIO_PIN3
			*DIO_PIN4
			*DIO_PIN5
			*DIO_PIN6
			*DIO_PIN7
			
	where x is the ID of Pb "x = 1 or 2 or 3"
*/

/**
 * Options of A_u8Pb_ID 
        *Pb1_ID 
		*Pb2_ID 
		*Pb3_ID 
*/

/**
 * connection of Pb 1
*/
#define Pb1_PORT    DIO_PORTD
#define Pb1_PIN     DIO_PIN2

/**
 * connection of Pb 2
*/
#define Pb2_PORT    DIO_PORTA 
#define Pb2_PIN     DIO_PIN1

/**
 * connection of Pb 3
*/
#define Pb3_PORT    DIO_PORTA 
#define Pb3_PIN     DIO_PIN2

#endif /* HAL_PUSH_BOTTON_PB_CONF_H */
