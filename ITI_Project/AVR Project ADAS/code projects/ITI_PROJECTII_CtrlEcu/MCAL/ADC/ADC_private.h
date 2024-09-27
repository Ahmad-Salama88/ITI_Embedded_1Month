/*
 * ADC_private.h
 *
 *  Created on: Jul 5, 2022
 *      Author: Mohammed Ramadan
 */
 
#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

/**(ADMUX) ADC Multiplexer Selection Register*/
#define MUX0   0
#define MUX1   1
#define MUX2   2
#define MUX3   3
#define MUX4   4
#define ADLAR  5
#define REFS0  6
#define REFS1  7

/**(ADCSRA) ADC Control Status Register*/
#define ADPS0  0
#define ADPS1  1
#define ADPS2  2
#define ADIE   3
#define ADIF   4
#define ADATE  5
#define ADSC   6
#define ADEN   7

/**(SREG) status register*/
#define I_BIT  7      /**global interrupt flag */

/**referance of ADC*/
#define AVCC		   0
#define AREF_INTERNAL  1
#define AREF		   2

#define Null 0

#endif /*MCAL_ADC_ADC_PRIVATE_H_*/
