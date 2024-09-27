/*
 * ADC_register.h
 *
 *  Created on: Jul 5, 2022
 *      Author: Mohammed Ramadan
 */
 
#ifndef MCAL_ADC_ADC_REGISTER_H_
#define MCAL_ADC_ADC_REGISTER_H_

#define  ADMUX   *((volatile u8 *)(0x27)) /**ADC Multiplexer Selection Register       */
#define  ADCSRA  *((volatile u8 *)(0x26)) /**ADC Control Status Register              */
#define  ADC     *((volatile u16*)(0x24)) /**ADCL + ADCH to store result of conversion*/
#define  SFIOR   *((volatile u8 *)(0x50)) /**Special FunctionIO Register              */
#define SREG *((volatile u8 *)(0x5F))     /**status register*/
#endif /*MCAL_ADC_ADC_REGISTER_H_*/