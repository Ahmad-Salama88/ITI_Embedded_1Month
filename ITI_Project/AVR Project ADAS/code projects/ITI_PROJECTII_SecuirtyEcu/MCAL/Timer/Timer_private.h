/*
 * Timer_private.h
 *
 *  Created on: Jun 2, 2022
 *      Author: Mohamed Ramadan
 */
 
#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_

/**Status register(SREG) */		
#define I_BIT    7  /**(global interrupt flag)*/

/*Prescaller of clk mc*/
#define CLK_PS_1                1
#define CLK_PS_8                8
#define CLK_PS_32               32
#define CLK_PS_64               64
#define CLK_PS_128              128
#define CLK_PS_256              256
#define CLK_PS_1024             1024
#define EXIT_FALLING_EDGE       6
#define EXIT_RISING_EDGE        7

/*Modes of timer*/              
#define NORMAL_MODE                            1
#define PWM_PHASE_CORRECT_MODE                 2
#define COMPARE_MATCH_MODE                     3
#define FAST_PWM_MODE                          4
#define PHASE_CORRECT_MODE_8_BITS		       5
#define PHASE_CORRECT_MODE_9_BITS		       6
#define PHASE_CORRECT_MODE_10_BITS		       7
#define COMPARE_MATCH_MODE_TOP_IS_OCR1A	       8
#define FAST_PWM_MODE_8_BITS			       9
#define FAST_PWM_MODE_9_BITS			       10
#define FAST_PWM_MODE_10_BITS			       11
#define FREQUANCY_CORRECT_MODE_TOP_IS_ICR1     12
#define FREQUANCY_CORRECT_MODE_TOP_IS_OCR1A    13
#define PHASE_CORRECT_MODE_TOP_IS_ICR1	       14
#define PHASE_CORRECT_MODE_TOP_IS_OCR1A	       15
#define COMPARE_MATCH_MODE_TOP_IS_ICR1	       16
#define FAST_PWM_MODE_TOP_IS_ICR1		       17
#define FAST_PWM_MODE_TOP_IS_OCR1A		       18

/*frequancy of mc*/
#define CLOK_SYSTEM 8000000UL

/*Null address*/
#define NULL ((void *)0)

        /****************************************************************/
        /*                         TIMER0                               */
        /****************************************************************/

/**Timer0/counter0 control register (TCCR0)*/		
#define CS00     0 /*The thee Clock Select bits select the clock source to be used by the Timer/Counter*/
#define CS01     1
#define CS02     2
#define COM00    4 /*Compare Output Mode Bits*/
#define COM01    5
#define WGM01    3 /*Waveform Generation Mode Bits*/
#define WGM00    6
#define FOC0     7 /*Fource Output Compare*/

/**Timer interrupt mask register (TIMSK)*/		
#define TOIE0    0  /*Timer/Counter0 Overflow Interrupt Enable*/
#define OCIE0    1  /*Timer/Counter0 Output Compare Match Interrupt Enable*/

/**Timer interrupt flag register (TIFR)*/		
#define TOV0     0  /*Timer/Counter0 Overflow Flag*/
#define OCF0     1  /*Timer/Counter0 Output Compare Flag*/

/*number of bits of timer 0*/
#define TIMER0_RESOLUTION  8

/*ENABLE/DISABLE TIMER0*/
#define ENABLE0   1  /*ENABLE TIMER0*/
#define DISABLE0  2  /*DISABLE TIMER0*/

		
        /****************************************************************/
        /**                        TIMER2                              **/
        /****************************************************************/

/**Timer2/counter2 control register (TCCR2)*/
#define CS20     0 /*The thee Clock Select bits select the clock source to be used by the Timer/Counter*/
#define CS21     1
#define CS22     2
#define COM20    4 /*Compare Output Mode Bits*/
#define COM21    5
#define WGM21    3 /*Waveform Generation Mode Bits*/
#define WGM20    6
#define FOC2     7 /*Fource Output Compare*/                    

/**Asynchrous status register (ASSR)*/		
#define AS2      3

/**Timer interrupt mask register (TIMSK)*/		
#define TOIE2    6  /*Timer/Counter2 Overflow Interrupt Enable*/
#define OCIE2    7  /*Timer/Counter2 Output Compare Match Interrupt Enable*/

/**Timer interrupt flag register (TIFR)*/		
#define TOV2     6  /*Timer/Counter2 Overflow Flag*/
#define OCF2     7  /*Timer/Counter2 Output Compare Flag*/

/*number of bits of timer 2*/
#define TIMER2_RESOLUTION  8

/*ENABLE/DISABLE TIMER2*/
#define ENABLE2   3  /*ENABLE TIMER2*/
#define DISABLE2  4  /*DISABLE TIMER2*/

        /****************************************************************/
        /**                        TIMER1                              **/
        /****************************************************************/
/**Timer1/counter1 control register (TCCR1A)*/		
#define WGM10    0 /*Waveform Generation Mode Bits 0 , 1*/
#define WGM11    1
#define FOC1B    2 /*Fource Output Compare B*/
#define FOC1A    3 /*Fource Output Compare A*/
#define COM1B0   4 /*Compare A Output Mode Bits*/
#define COM1B1   5 
#define COM1A0   6 /*Compare B Output Mode Bits*/
#define COM1A1   7

/**Timer1/counter1 control register (TCCR1B)*/		
#define CS10     0 /*The thee Clock Select bits select the clock source to be used by the Timer/Counter*/
#define CS11     1
#define CS12     2
#define WGM12    3 /*Waveform Generation Mode Bits 2 , 3*/
#define WGM13    4 
#define ICES1    6 /*Input Capture Edge Select*/
#define ICNC1    7 /*Input Capture Noise Canceler*/

/**Timer interrupt mask register (TIMSK)*/		
#define TOIE1    2  /*Timer/Counter1 Overflow Interrupt Enable*/
#define OCIE1B   3  /*Timer/Counter1 Output Compare Match A Interrupt Enable*/
#define OCIE1A   4  /*Timer/Counter1 Output Compare Match B Interrupt Enable*/
#define TICIE1   5  /*Timer/Counter1 Input Capture Enable*/

/**Timer interrupt flag register (TIFR)*/		
#define TOV1     2  /*Timer/Counter1 Overflow Flag*/
#define OCF1A    3  /*Timer/Counter1 Output Compare Flag*/		
#define OCF1B    4  /*Timer/Counter1 Output Compare Flag*/		
#define ICF1     5  /*Timer/Counter1 Input Capture Flag*/	

/*ENABLE/DISABLE TIMER2*/
#define ENABLE1   5  /*ENABLE TIMER2*/
#define DISABLE1  6  /*DISABLE TIMER2*/

/*Types of ctc */
#define COMPARE_A    1 /*compare match A*/
#define COMPARE_B    2 /*compare match B*/
#define COMPARE_BOTH 3 /*compare match A and B*/

/*ENABLE/DISABLE TIMER2*/
#define ENABLE_ICU   7  /*ENABLE TIMER2*/
#define DISABLE_ICU  8  /*DISABLE TIMER2*/

/*Top value of TCR1 */
#define TOP_ICR1_VALUE 0xffff
#define TOP_OCR1A_VALUE 0xffff
#endif /*MCAL_TIMER_TIMER_PRIVATE_H_*/	