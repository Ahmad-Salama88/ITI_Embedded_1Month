/*
 * ADC_conf.h
 *
 *  Created on: Jul 5, 2022
 *      Author: Mohammed Ramadan
 */
 
#ifndef MCAL_ADC_ADC_CONF_H_
#define MCAL_ADC_ADC_CONF_H_

/**referance voltage selection
   **Options
        *AVCC
        *AREF_INTERNAL
        *AREF
 */
#define ADC_REF_VOLT  AVCC

/**set prescaller of ADC clk
   **Options
        *ADC_PS_2       (clk = 4MHZ)
        *ADC_PS_4       (clk = 2MHZ)
        *ADC_PS_8       (clk = 1MHZ)
        *ADC_PS_16      (clk = 500KHZ)
        *ADC_PS_32      (clk = 250KHZ)
        *ADC_PS_64      (clk = 125KHZ)
        *ADC_PS_128     (clk = 62.5KHZ)
 */
#define ADC_PRESCALER ADC_PS_64


#endif /*MCAL_ADC_ADC_CONF_H_*/