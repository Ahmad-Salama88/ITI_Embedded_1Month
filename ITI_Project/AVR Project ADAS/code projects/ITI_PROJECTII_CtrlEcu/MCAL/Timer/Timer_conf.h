/*
 * Timer_conf.h
 *
 *  Created on: Jun 2, 2022
 *      Author: Mohamed Ramadan
 */
 
#ifndef MCAL_TIMER_TIMER_CONF_H_
#define MCAL_TIMER_TIMER_CONF_H_

        /****************************************************************/
        /*                         TIMER0                               */
        /****************************************************************/
/*ENABLE/DISABLE TIMER0*/
#define ENABLE0   1  /*ENABLE TIMER0*/
#define DISABLE0  2  /*DISABLE TIMER0*/

/**ENABLE/DISABLE TIMER0
   **Options
       *ENABLE0
       *DISABLE0
 */
#define TIMER0  ENABLE0

/**select prescaller of clk timer0
   **Options
       *CLK_PS_1         
       *CLK_PS_8         
       *CLK_PS_64        
       *CLK_PS_256       
       *CLK_PS_1024      
       *EXIT_FALLING_EDGE
       *EXIT_RISING_EDGE 
 */
#define TIMER0_PRESCALER  CLK_PS_8

/**select mode of timer0
   **Options
       *NORMAL_MODE         
       *PWM_PHASE_CORRECT_MODE         
       *COMPARE_MATCH_MODE        
       *FAST_PWM_MODE       
 */
#define TIMER0_MODE NORMAL_MODE

/**set interval countes
  the value of TIMER0_INTERVAL_COUNTS must be stored in u32
 */
#define TIMER0_INTERVAL_COUNTS  000

/**set oc0
  the value of TIMER0_COMPAREVALUE must be from 0 to 255
 */
#define TIMER0_COMPAREVALUE     000
        /****************************************************************/
        /*                         TIMER1                               */
        /****************************************************************/
/**ENABLE/DISABLE TIMER1
   **Options
       *ENABLE1
       *DISABLE1
 */
#define TIMER1  DISABLE1

/**select prescaller of clk timer1
   **Options
       *CLK_PS_1         
       *CLK_PS_8         
       *CLK_PS_64        
       *CLK_PS_256       
       *CLK_PS_1024      
       *EXIT_FALLING_EDGE
       *EXIT_RISING_EDGE 
 */
#define TIMER1_PRESCALER  CLK_PS_1

/**select mode of timer0
   **Options
       *NORMAL_MODE         
       *PHASE_CORRECT_MODE_8_BITS
       *PHASE_CORRECT_MODE_9_BITS
       *PHASE_CORRECT_MODE_10_BITS
       *COMPARE_MATCH_MODE_TOP_IS_OCR1A
       *FAST_PWM_MODE_8_BITS
       *FAST_PWM_MODE_9_BITS
       *FAST_PWM_MODE_10_BITS
       *FREQUANCY_CORRECT_MODE_TOP_IS_ICR1
       *FREQUANCY_CORRECT_MODE_TOP_IS_OCR1
       *PHASE_CORRECT_MODE_TOP_IS_ICR1
       *PHASE_CORRECT_MODE_TOP_IS_OCR1A
       *COMPARE_MATCH_MODE_TOP_IS_ICR1
       *FAST_PWM_MODE_TOP_IS_ICR1
       *FAST_PWM_MODE_TOP_IS_OCR1A
 */
#define TIMER1_MODE NORMAL_MODE

/**set oc1A
  the value of TIMER1_COMPAREVALUE_A must be from 0 to 65535
 */
#define TIMER1_COMPAREVALUE_A 100

/**set interval counts
  the value of TIMER1_INTERVAL_A_COUNTS must be stored in u32
 */
#define TIMER1_INTERVAL_A_COUNTS  50

/**set oc1B
  the value of TIMER1_COMPAREVALUE_B must be from 0 to 65535
 */
#define TIMER1_COMPAREVALUE_B 100

/**set interval counts
  the value of TIMER1_INTERVAL_B_COUNTS must be stored in u32
 */
#define TIMER1_INTERVAL_B_COUNTS  50

/**select type of compare match
   **Options
       *COMPARE_A         
       *COMPARE_B
       *COMPARE_BOTH
 */
#define COMPARE_TYPE  COMPARE_BOTH

/**ENABLE/DISABLE ICU
   **Options
       *ENABLE_ICU
       *DISABLE_ICU
 */
#define ICU_ENABLE ENABLE_ICU

        /****************************************************************/
        /*                         TIMER2                               */
        /****************************************************************/
/**ENABLE/DISABLE TIMER2
   **Options
       *ENABLE2
       *DISABLE2
 */
#define TIMER2  DISABLE2

/**select prescaller of clk timer0
   **Options
       *CLK_PS_1         
       *CLK_PS_8         
       *CLK_PS_32        
       *CLK_PS_64       
       *CLK_PS_128      
       *CLK_PS_256      
       *CLK_PS_1024 
 */
#define TIMER2_PRESCALER  CLK_PS_8

/**select mode of timer2
   **Options
       *NORMAL_MODE         
       *PWM_PHASE_CORRECT_MODE         
       *COMPARE_MATCH_MODE        
       *FAST_PWM_MODE       
 */
#define TIMER2_MODE FAST_PWM_MODE

/**set interval countes
  the value of TIMER0_INTERVAL_COUNTS must be stored in u32
 */
#define TIMER2_INTERVAL_COUNTS  4000

/**set oc0
  the value of TIMER0_COMPAREVALUE must be from 0 to 255
 */
#define TIMER2_COMPAREVALUE     200

#endif /*MCAL_TIMER_TIMER_CONF_H_*/
