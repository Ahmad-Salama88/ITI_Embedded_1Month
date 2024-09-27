/*
 * Timer_register.h
 *
 *  Created on: Jun 2, 2022
 *      Author: Mohamed Ramadan
 */
 
#ifndef MCAL_TIMER_TIMER_REGISTER_H_
#define MCAL_TIMER_TIMER_REGISTER_H_

/**Status register*/
#define SREG   *((volatile u8 *)(0x5F))

/*timers interrupt mask register*/
#define TIMSK  *((volatile u8 *)(0x59))

/*timers interrupt flags register*/
#define TIFR  *((volatile u8 *)(0x58))

        /****************************************************************/
        /**                        TIMER0                              **/
        /****************************************************************/

/**Timer0/counter0 control register*/		
#define TCCR0   *((volatile u8 *)(0x53))

/**Timer0/counter0 register*/		
#define TCNT0   *((volatile u8 *)(0x52))

/**Timer0 output compare register*/		
#define OCR0    *((volatile u8 *)(0x5C))

		
        /****************************************************************/
        /**                        TIMER2                              **/
        /****************************************************************/

/**Timer2/counter2 control register*/		
#define TCCR2   *((volatile u8 *)(0x45))

/**Timer2/counter2 register*/		
#define TCNT2   *((volatile u8 *)(0x44))

/**Timer2 output compare register*/		
#define OCR2    *((volatile u8 *)(0x43))

/**Asynchrous status register*/		
#define ASSR    *((volatile u8 *)(0x42))

#endif /*MCAL_TIMER_TIMER_REGISTER_H_*/

        /****************************************************************/
        /**                        TIMER1                              **/
        /****************************************************************/

/**Timer1/counter1 control registerA*/		
#define TCCR1A   *((volatile u8 *)(0x4F))

/**Timer1/counter1 control registerB*/		
#define TCCR1B   *((volatile u8 *)(0x4E))

/**Timer1 output compare registerA*/		
#define OCR1A    *((volatile u16*)(0x4A))

/**Timer1 output compare registerB*/		
#define OCR1B    *((volatile u16*)(0x48))

/**Timer1/counter1 register*/		
#define TCNT1    *((volatile u16*)(0x4C))

/**Input capture register*/		
#define ICR1     *((volatile u16*)(0x46))
