/*
 * LCD_conf.h
 *
 *  Created on: May 18, 2022
 *      Author: Mohammed Ramadan
 */
 
#ifndef HAL_LCD_LCD_CONF_H_
#define HAL_LCD_LCD_CONF_H_

/*
 *Connections of Data
     ** Options of PORTS :
	           *DIO_PORTA
			   *DIO_PORTB
			   *DIO_PORTC
			   *DIO_PORTD
			   
	 ** Options of PINS :
	           *DIO_PIN0
			   *DIO_PIN1
			   *DIO_PIN2
			   *DIO_PIN3
			   *DIO_PIN4
			   *DIO_PIN5
			   *DIO_PIN6
			   *DIO_PIN7
 */
 
/* Data */
#define LCD_DATA_PORT DIO_PORTC

/* Enable */
#define LCD_EN_PORT   DIO_PORTB
#define LCD_EN_PIN    DIO_PIN7

/* Read / write  */
#define LCD_RW_PORT   DIO_PORTB
#define LCD_RW_PIN    DIO_PIN6

/* Register Select */
#define LCD_RS_PORT   DIO_PORTB
#define LCD_RS_PIN    DIO_PIN5







/*
 *Select the mode of connections
    ** Options 
	      *EIGHT_BIT_CONNECTION
		  *FOUR_BIT_CONNECTION
		  
	** If you select EIGHT_BIT_CONNECTION
	        eight pins of port connected to  eight data pins
			
	** If you select EIGHT_BIT_CONNECTION
	        high nibble pins of port connected to  last four data pins		
 */
#define MODE       EIGHT_BIT_CONNECTION

/** Base of number that be converted to string */
#define BASE   10

#endif /* HAL_LCD_LCD_CONF_H_ */
