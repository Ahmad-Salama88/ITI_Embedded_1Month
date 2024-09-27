/*
 * ADC_int.h
 *
 *  Created on: Jul 5, 2022
 *      Author: Mohammed Ramadan
 */

#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_

#define CHANNEL_0		0   /**PA0*/
#define CHANNEL_1		1   /**PA1*/
#define CHANNEL_2		2   /**PA2*/
#define CHANNEL_3		3   /**PA3*/
#define CHANNEL_4		4   /**PA4*/
#define CHANNEL_5		5   /**PA5*/
#define CHANNEL_6		6   /**PA6*/
#define CHANNEL_7		7   /**PA7*/


/* FOR POOLING
 * ' ADCSRA ' ADC Control Status Register
 * 	bit name :' ADIF '
 */
#define  ADCSRA  *((volatile u8 *)(0x26))
#define ADIF   4




/*
	Function Name        : MADC_voidInt
	Function Returns     : void
	Function Arguments   : void
	Function Description : intialize ADC
*/
void MADC_voidInt (void) ;

/*
	Function Name        : MADC_voidStartConversion
	Function Returns     : void
	Function Arguments   : u8 A_u8ChannelNo
	Function Description : set ADC to take sample and start conversion
*/
void MADC_voidStartConversion(u8 A_u8ChannelNo) ;

/*
	Function Name        : MADC_u16GetADCData
	Function Returns     : u16
	Function Arguments   : void
	Function Description : return result of conversion
*/
u16  MADC_u16GetADCData(void);

/*
	Function Name        : MADC_voidSetCallback
	Function Returns     : void
	Function Arguments   : pointer to function  void (*A_fptr)(void)
	Function Description : set ADC callback to call ISR
*/
void MADC_voidSetCallback( void (*A_fptr)(void)  );

#endif /*MCAL_ADC_ADC_INT_H_*/
