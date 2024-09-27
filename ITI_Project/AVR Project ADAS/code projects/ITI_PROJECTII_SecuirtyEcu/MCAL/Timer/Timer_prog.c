/*
 * Timer_prog.c
 *
 *  Created on: Jun 2, 2022
 *      Author: Mohamed Ramadan
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_int.h"
#include "Timer_register.h"
#include "Timer_private.h"
#include "Timer_conf.h"
#include "Timer_int.h"

static volatile void (*Timer0_Overflow_CallBack)(void) ; /**pointer to function to set call back of Timer0_Overflow_ISR*/
static volatile void (*Timer1_Overflow_CallBack)(void) ; /**pointer to function to set call back of Timer1_Overflow_ISR*/
static volatile void (*Timer2_Overflow_CallBack)(void) ; /**pointer to function to set call back of Timer2_Overflow_ISR*/
static volatile void (*Timer0_CTC_CallBack)     (void) ; /**pointer to function to set call back of Timer0_CTC_ISR     */
static volatile void (*Timer2_CTC_CallBack)     (void) ; /**pointer to function to set call back of Timer2_CTC_ISR     */
static volatile void (*Timer1_CTC_A_CallBack)   (void) ; /**pointer to function to set call back of Timer2_CTC_ISR     */
static volatile void (*Timer1_CTC_B_CallBack)   (void) ; /**pointer to function to set call back of Timer2_CTC_ISR     */

 /*set counter to tack action with timer 0 at over flow*/
volatile u32 G_u32Timer0IntervalCount = 0 ;

 /*set counter to tack action with timer 0 at compare match*/
volatile u32 G_u32Timer0IntervalCtcCount = 0 ;

 /*set counter to tack action with timer 2 at over flow*/
volatile u32 G_u32Timer2IntervalCount = 0 ;

 /*set counter to tack action with timer 2 at compare match*/
volatile u32 G_u32Timer2IntervalCtcCount = 0 ;

 /*set counter to tack action with timer 1 at compare match A*/
volatile u32 G_u32Timer1IntervalCtcACount = 0 ;

 /*set counter to tack action with timer 1 at compare match A*/
 volatile u32 G_u32Timer1IntervalCtcBCount = 0 ;

 /*set counter to tack action with timer 1 at over flow*/
volatile u32 G_u32Timer1IntervalCount = 0 ;

 /*to store number of over flow counts to use it for calculate frequency and duty cycle using ICU*/
volatile u32 G_u32OverFlowCounts = 0 ;

static u32 G_u32CountsForFirstRising  = 0 ; /*number of counts until arrived to first rising of input signal*/
static u32 G_u32CountsForFirstFaling  = 0 ; /*number of counts until arrived to first falling of input signal*/
static u32 G_u32CountsForSecondRising = 0 ; /*number of counts until arrived to second rising of input signal*/
static u32 G_u32FrequancyOfTimeOn     = 0 ; /*counts of (time on) range */
static u32 G_u32FrequancyOfTimeTotal  = 0 ; /*counts of (time total) range */

void MTimer_voidInt (void)
{

	/** Enable global interrupt flag */
	    SET_BIT(SREG, I_BIT);

        /****************************************************************/
        /*                         TIMER0                               */
        /****************************************************************/
	#if   TIMER0 == ENABLE0
	    /**set prescaller of Timer clk*/
	    #if   TIMER0_PRESCALER == CLK_PS_1          /**clk = 8MHZ    */
		    SET_BIT(TCCR0 , CS00) ;
	        CLR_BIT(TCCR0 , CS01) ;
	        CLR_BIT(TCCR0 , CS02) ;
	    #elif TIMER0_PRESCALER == CLK_PS_8          /**clk = 1MHZ    */
			CLR_BIT(TCCR0 , CS00) ;
	        SET_BIT(TCCR0 , CS01) ;
	        CLR_BIT(TCCR0 , CS02) ;
	    #elif TIMER0_PRESCALER == CLK_PS_64         /**clk = 125KHZ  */
		    SET_BIT(TCCR0 , CS00) ;
	        SET_BIT(TCCR0 , CS01) ;
	        CLR_BIT(TCCR0 , CS02) ;
	    #elif TIMER0_PRESCALER == CLK_PS_256        /**clk = 31.25KHZ*/
            CLR_BIT(TCCR0 , CS00) ;
	        CLR_BIT(TCCR0 , CS01) ;
	        SET_BIT(TCCR0 , CS02) ;
	    #elif TIMER0_PRESCALER == CLK_PS_1024       /**clk = 7.8KHZ  */
		    SET_BIT(TCCR0 , CS00) ;
	        CLR_BIT(TCCR0 , CS01) ;
	        SET_BIT(TCCR0 , CS02) ;
	    #elif TIMER0_PRESCALER == EXIT_FALLING_EDGE /**external clk source on T0 pin (clock on faling edge)*/
	        CLR_BIT(TCCR0 , CS00) ;
	        SET_BIT(TCCR0 , CS01) ;
	        SET_BIT(TCCR0 , CS02) ;
		#elif TIMER0_PRESCALER == EXIT_RISING_EDGE  /**external clk source on T0 pin (clock on rising edge)*/
		    SET_BIT(TCCR0 , CS00) ;
	        SET_BIT(TCCR0 , CS01) ;
	        SET_BIT(TCCR0 , CS02) ;
		#else #error "select correct options of TIMER0_PRESCALER"
		#endif

		/**Timer/counter0 mode*/
		#if   TIMER0_MODE == NORMAL_MODE
		    CLR_BIT(TCCR0 , WGM00) ;/*Normal mode (over flow mode)*/
		    CLR_BIT(TCCR0 , WGM01) ;
			SET_BIT(TIMSK , TOIE0);/*Enable interrupt of over flow mode*/
		#elif TIMER0_MODE == PWM_PHASE_CORRECT_MODE
		    SET_BIT(TCCR0 , WGM00) ;/*phase correct mode*/
		    CLR_BIT(TCCR0 , WGM01) ;
			CLR_BIT(TCCR0 , COM00)  ;/*clear OC0 on compare match , set at botton*/
			SET_BIT(TCCR0 , COM01)  ;
			CLR_BIT(TIMSK , OCIE0) ;/*Disable interrupt of compare match mode*/
			MDIO_voidSetPinDir (DIO_PORTB , DIO_PIN3 , DIO_HIGH) ; /*set OC0 pin as output*/
		#elif TIMER0_MODE == COMPARE_MATCH_MODE
		    CLR_BIT(TCCR0 , WGM00) ;/*output compare match mode*/
		    SET_BIT(TCCR0 , WGM01) ;
			SET_BIT(TIMSK , OCIE0);/*Enable interrupt of compare match mode*/
			G_u32Timer0IntervalCtcCount = TIMER0_INTERVAL_COUNTS ;
			#if TIMER0_COMPAREVALUE >= 0 && TIMER0_COMPAREVALUE <= 255
		        OCR0 = TIMER0_COMPAREVALUE ;
			#else
				#error "the value of TIMER0_COMPAREVALUE must be from 0 to 255"
			#endif
		#elif TIMER0_MODE == FAST_PWM_MODE
		    SET_BIT(TCCR0 , WGM00) ;/*fast pwm*/
		    SET_BIT(TCCR0 , WGM01) ;
			CLR_BIT(TCCR0 , COM00)  ;/*clear OC0 on compare match , set at botton*/
			SET_BIT(TCCR0 , COM01)  ;
			CLR_BIT(TIMSK , OCIE0) ;/*Disable interrupt of compare match mode*/
			MDIO_voidSetPinDir (DIO_PORTB , DIO_PIN3 , DIO_HIGH) ; /*set OC0 pin as output*/
		#else #error "select correct mode of TIMER0_MODE"
		#endif

	#elif TIMER0 == DISABLE0
	/** NO clk source (Timer0 stopped) */
	    CLR_BIT(TCCR0 , CS00) ;
	    CLR_BIT(TCCR0 , CS01) ;
	    CLR_BIT(TCCR0 , CS02) ;
	#else
		#error "TIMER0 must be ENABLE0 or DISABLE0"
    #endif

        /****************************************************************/
        /*                         TIMER2                               */
        /****************************************************************/
	#if   TIMER2 == ENABLE2
	    /**set prescaller of timer clk*/
	    #if   TIMER2_PRESCALER == CLK_PS_1          /**clk = 8MHZ    */
		    SET_BIT(TCCR2 , CS20) ;
	        CLR_BIT(TCCR2 , CS21) ;
	        CLR_BIT(TCCR2 , CS22) ;
	    #elif TIMER2_PRESCALER == CLK_PS_8          /**clk = 1MHZ    */
			CLR_BIT(TCCR2 , CS20) ;
	        SET_BIT(TCCR2 , CS21) ;
	        CLR_BIT(TCCR2 , CS22) ;
	    #elif TIMER2_PRESCALER == CLK_PS_32         /**clk = 250KHZ  */
		    SET_BIT(TCCR2 , CS20) ;
	        SET_BIT(TCCR2 , CS21) ;
	        CLR_BIT(TCCR2 , CS22) ;
	    #elif TIMER2_PRESCALER == CLK_PS_64        /**clk = 125KHZ*/
            CLR_BIT(TCCR2 , CS20) ;
	        CLR_BIT(TCCR2 , CS21) ;
	        SET_BIT(TCCR2 , CS22) ;
	    #elif TIMER2_PRESCALER == CLK_PS_128       /**clk = 62.5KHZ  */
		    SET_BIT(TCCR2 , CS20) ;
	        CLR_BIT(TCCR2 , CS21) ;
	        SET_BIT(TCCR2 , CS22) ;
	    #elif TIMER2_PRESCALER == CLK_PS_256       /**clk = 31.25KHZ  */
	        CLR_BIT(TCCR2 , CS20) ;
	        SET_BIT(TCCR2 , CS21) ;
	        SET_BIT(TCCR2 , CS22) ;
		#elif TIMER2_PRESCALER == CLK_PS_1024       /**clk = 7.8KHZ  */
		    SET_BIT(TCCR2 , CS20) ;
	        SET_BIT(TCCR2 , CS21) ;
	        SET_BIT(TCCR2 , CS22) ;
		#else
			#error "select correct options of TIMER2_PRESCALER"
		#endif

		/**Timer/counter2 mode*/
		#if   TIMER0_MODE == NORMAL_MODE
		    CLR_BIT(TCCR2 , WGM20) ;/*Normal mode (over flow mode)*/
		    CLR_BIT(TCCR2 , WGM21) ;
			SET_BIT(TIMSK , TOIE2);/*Enable interrupt of over flow mode*/
		#elif TIMER0_MODE == PWM_PHASE_CORRECT_MODE
		    SET_BIT(TCCR2 , WGM20) ;/*phase correct mode*/
		    CLR_BIT(TCCR2 , WGM21) ;
			CLR_BIT(TCCR2 , COM20) ;/*clear OC2 on compare match , set at botton*/
			SET_BIT(TCCR2 , COM21) ;
			CLR_BIT(TIMSK , OCIE2) ;/*Disable interrupt of compare match mode*/
			MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN7  , DIO_HIGH) ; /*set OC2 pin as output*/
		#elif TIMER0_MODE == COMPARE_MATCH_MODE
		    CLR_BIT(TCCR2 , WGM20) ;/*output compare match mode*/
		    SET_BIT(TCCR2 , WGM21) ;
			SET_BIT(TIMSK , OCIE2) ;/*Enable interrupt of compare match mode*/
			G_u32Timer2IntervalCtcCount = TIMER2_INTERVAL_COUNTS ;
			#if TIMER2_COMPAREVALUE >= 0 && TIMER2_COMPAREVALUE <= 255
		        OCR2 = TIMER0_COMPAREVALUE ;
			#else #error "the value of TIMER2_COMPAREVALUE must be from 0 to 255"
			#endif
		#elif TIMER0_MODE == FAST_PWM_MODE
		    SET_BIT(TCCR2 , WGM20) ;/*fast pwm*/
		    SET_BIT(TCCR2 , WGM21) ;
			CLR_BIT(TCCR2 , COM20) ;/*clear OC2 on compare match , set at botton*/
			SET_BIT(TCCR2 , COM21) ;
			CLR_BIT(TIMSK , OCIE2) ;/*Disable interrupt of compare match mode*/
			MDIO_voidSetPinDir (DIO_PORTB , DIO_PIN3 , DIO_HIGH) ; /*set OC2 pin as output*/
		#else #error "select correct mode of TIMER2_MODE"
		#endif
	#elif TIMER2 == DISABLE2
	/** NO clk source (Timer2 stopped) */
	    CLR_BIT(TCCR2 , CS20) ;
	    CLR_BIT(TCCR2 , CS21) ;
	    CLR_BIT(TCCR2 , CS22) ;
	#else #error "TIMER2 must be ENABLE2 or DISABLE2"
    #endif

        /****************************************************************/
        /*                         TIMER1                               */
        /****************************************************************/
	#if   TIMER1 == ENABLE1
	    /**set prescaller of Timer clk*/
	    #if   TIMER1_PRESCALER == CLK_PS_1          /**clk = 8MHZ    */
		    SET_BIT(TCCR1B , CS10) ;
	        CLR_BIT(TCCR1B , CS11) ;
	        CLR_BIT(TCCR1B , CS12) ;
	    #elif TIMER1_PRESCALER == CLK_PS_8          /**clk = 1MHZ    */
			CLR_BIT(TCCR1B , CS10) ;
	        SET_BIT(TCCR1B , CS11) ;
	        CLR_BIT(TCCR1B , CS12) ;
	    #elif TIMER1_PRESCALER == CLK_PS_64         /**clk = 125KHZ  */
		    SET_BIT(TCCR1B , CS10) ;
	        SET_BIT(TCCR1B , CS11) ;
	        CLR_BIT(TCCR1B , CS12) ;
	    #elif TIMER1_PRESCALER == CLK_PS_256        /**clk = 31.25KHZ*/
            CLR_BIT(TCCR1B , CS10) ;
	        CLR_BIT(TCCR1B , CS11) ;
	        SET_BIT(TCCR1B , CS12) ;
	    #elif TIMER1_PRESCALER == CLK_PS_1024       /**clk = 7.8KHZ  */
		    SET_BIT(TCCR1B , CS10) ;
	        CLR_BIT(TCCR1B , CS11) ;
	        SET_BIT(TCCR1B , CS12) ;
	    #elif TIMER1_PRESCALER == EXIT_FALLING_EDGE /**external clk source on T1 pin (clock on faling edge)*/
	        CLR_BIT(TCCR1B , CS10) ;
	        SET_BIT(TCCR1B , CS11) ;
	        SET_BIT(TCCR1B , CS12) ;
		#elif TIMER1_PRESCALER == EXIT_RISING_EDGE  /**external clk source on T1 pin (clock on rising edge)*/
		    SET_BIT(TCCR1B , CS10) ;
	        SET_BIT(TCCR1B , CS11) ;
	        SET_BIT(TCCR1B , CS12) ;
		#else #error "select correct options of TIMER1_PRESCALER"
		#endif

		/**Timer/counter1 mode*/
		#if   TIMER1_MODE == NORMAL_MODE
		    CLR_BIT(TCCR1A , WGM10) ;/*Normal mode (over flow mode)*/
		    CLR_BIT(TCCR1A , WGM11) ;
		    CLR_BIT(TCCR1B , WGM12) ;
		    CLR_BIT(TCCR1B , WGM13) ;
			SET_BIT(TIMSK  , TOIE1) ;/*Enable interrupt of over flow mode*/
			#if ICU_ENABLE == ENABLE_ICU
				SET_BIT(TCCR1B , ICNC1) ;/*input capture noise cancler*/
			#endif
		#elif TIMER1_MODE == PHASE_CORRECT_MODE_8_BITS
		    SET_BIT(TCCR1A , WGM10) ;
		    CLR_BIT(TCCR1A , WGM11) ;
		    CLR_BIT(TCCR1B , WGM12) ;
		    CLR_BIT(TCCR1B , WGM13) ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1A0) ;/*clear OC1A on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1A1) ;
			    CLR_BIT(TIMSK  , OCIE1A) ;/*Disable interrupt of compare match A mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN5 , DIO_HIGH) ; /*set OC1A pin as output*/
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1B0) ;/*clear OC1B on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1B1) ;
			    CLR_BIT(TIMSK  , OCIE1B) ;/*Disable interrupt of compare match B mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN4 , DIO_HIGH) ; /*set OC1B pin as output*/
			#endif

		#elif TIMER1_MODE == PHASE_CORRECT_MODE_9_BITS
		    CLR_BIT(TCCR1A , WGM10) ;
		    SET_BIT(TCCR1A , WGM11) ;
		    CLR_BIT(TCCR1B , WGM12) ;
		    CLR_BIT(TCCR1B , WGM13) ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1A0) ;/*clear OC1A on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1A1) ;
			    CLR_BIT(TIMSK  , OCIE1A) ;/*Disable interrupt of compare match A mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN5 , DIO_HIGH) ; /*set OC1A pin as output*/
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1B0) ;/*clear OC1B on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1B1) ;
			    CLR_BIT(TIMSK  , OCIE1B) ;/*Disable interrupt of compare match B mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN4 , DIO_HIGH) ; /*set OC1B pin as output*/
			#endif

		#elif TIMER1_MODE == PHASE_CORRECT_MODE_10_BITS
		    SET_BIT(TCCR1A , WGM10) ;
		    SET_BIT(TCCR1A , WGM11) ;
		    CLR_BIT(TCCR1B , WGM12) ;
		    CLR_BIT(TCCR1B , WGM13) ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1A0) ;/*clear OC1A on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1A1) ;
			    CLR_BIT(TIMSK  , OCIE1A) ;/*Disable interrupt of compare match A mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN5 , DIO_HIGH) ; /*set OC1A pin as output*/
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1B0) ;/*clear OC1B on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1B1) ;
			    CLR_BIT(TIMSK  , OCIE1B) ;/*Disable interrupt of compare match B mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN4 , DIO_HIGH) ; /*set OC1B pin as output*/
			#endif

		#elif TIMER1_MODE == COMPARE_MATCH_MODE_TOP_IS_OCR1A
		    CLR_BIT(TCCR1A , WGM10) ;/*output compare match mode*/
		    CLR_BIT(TCCR1A , WGM11) ;
		    SET_BIT(TCCR1B , WGM12) ;
		    CLR_BIT(TCCR1B , WGM13) ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    SET_BIT(TIMSK , OCIE1A) ;/*Enable interrupt of compare match A mode*/
			    G_u32Timer1IntervalCtcACount = TIMER1_INTERVAL_A_COUNTS ;
			    #if TIMER1_COMPAREVALUE_A >= 0 && TIMER1_COMPAREVALUE_A <= 65535
			        OCR1A = TIMER1_COMPAREVALUE_A ;
			    #else #error "the value of TIMER1_COMPAREVALUE_A must be from 0 to 65535 && the value of TIMER1_COMPAREVALUE_B must be from 0 to 65535"
			    #endif
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    SET_BIT(TIMSK , OCIE1B) ;/*Enable interrupt of compare match A mode*/
			    G_u32Timer1IntervalCtcBCount = TIMER1_INTERVAL_B_COUNTS ;
			    #if TIMER1_COMPAREVALUE_B >= 0 && TIMER1_COMPAREVALUE_B <= 65535 && TIMER1_COMPAREVALUE_A >= 0 && TIMER1_COMPAREVALUE_A <= 65535
				    #if TIMER1_COMPAREVALUE_A < TIMER1_COMPAREVALUE_B
					    #error "TIMER1_COMPAREVALUE_A < TIMER1_COMPAREVALUE_B"
					#endif+
			        OCR1A = TIMER1_COMPAREVALUE_A ;
					OCR1B = TIMER1_COMPAREVALUE_B ;
			    #else  #error "the value of TIMER1_COMPAREVALUE_B must be from 0 to 65535 && the value of TIMER1_COMPAREVALUE_A must be from 0 to 65535"
			    #endif
			#endif

		#elif TIMER1_MODE == FAST_PWM_MODE_8_BITS
		    SET_BIT(TCCR1A , WGM10) ;
		    CLR_BIT(TCCR1A , WGM11) ;
		    SET_BIT(TCCR1B , WGM12) ;
		    CLR_BIT(TCCR1B , WGM13) ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1A0) ;/*clear OC1A on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1A1) ;
			    CLR_BIT(TIMSK  , OCIE1A) ;/*Disable interrupt of compare match A mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN5 , DIO_HIGH) ; /*set OC1A pin as output*/
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1B0) ;/*clear OC1B on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1B1) ;
			    CLR_BIT(TIMSK  , OCIE1B) ;/*Disable interrupt of compare match B mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN4 , DIO_HIGH) ; /*set OC1B pin as output*/
			#endif

		#elif TIMER1_MODE == FAST_PWM_MODE_9_BITS
		    CLR_BIT(TCCR1A , WGM10) ;
		    SET_BIT(TCCR1A , WGM11) ;
		    SET_BIT(TCCR1B , WGM12) ;
		    CLR_BIT(TCCR1B , WGM13) ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1A0) ;/*clear OC1A on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1A1) ;
			    CLR_BIT(TIMSK  , OCIE1A) ;/*Disable interrupt of compare match A mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN5 , DIO_HIGH) ; /*set OC1A pin as output*/
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1B0) ;/*clear OC1B on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1B1) ;
			    CLR_BIT(TIMSK  , OCIE1B) ;/*Disable interrupt of compare match B mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN4 , DIO_HIGH) ; /*set OC1B pin as output*/
			#endif

		#elif TIMER1_MODE == FAST_PWM_MODE_10_BITS
		    SET_BIT(TCCR1A , WGM10) ;
		    SET_BIT(TCCR1A , WGM11) ;
		    SET_BIT(TCCR1B , WGM12) ;
		    CLR_BIT(TCCR1B , WGM13) ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1A0) ;/*clear OC1A on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1A1) ;
			    CLR_BIT(TIMSK  , OCIE1A) ;/*Disable interrupt of compare match A mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN5 , DIO_HIGH) ; /*set OC1A pin as output*/
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1B0) ;/*clear OC1B on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1B1) ;
			    CLR_BIT(TIMSK  , OCIE1B) ;/*Disable interrupt of compare match B mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN4 , DIO_HIGH) ; /*set OC1B pin as output*/
			#endif

		#elif TIMER1_MODE == FREQUANCY_CORRECT_MODE_TOP_IS_ICR1
		    CLR_BIT(TCCR1A , WGM10) ;
		    CLR_BIT(TCCR1A , WGM11) ;
		    CLR_BIT(TCCR1B , WGM12) ;
		    SET_BIT(TCCR1B , WGM13) ;
			ICR1 = TOP_ICR1_VALUE ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1A0) ;/*clear OC1A on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1A1) ;
			    CLR_BIT(TIMSK  , OCIE1A) ;/*Disable interrupt of compare match A mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN5 , DIO_HIGH) ; /*set OC1A pin as output*/
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1B0) ;/*clear OC1B on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1B1) ;
			    CLR_BIT(TIMSK  , OCIE1B) ;/*Disable interrupt of compare match B mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN4 , DIO_HIGH) ; /*set OC1B pin as output*/
			#endif

		#elif TIMER1_MODE == FREQUANCY_CORRECT_MODE_TOP_IS_OCR1A
		    SET_BIT(TCCR1A , WGM10) ;
		    CLR_BIT(TCCR1A , WGM11) ;
		    CLR_BIT(TCCR1B , WGM12) ;
		    SET_BIT(TCCR1B , WGM13) ;
			OCR1A = TOP_OCR1A_VALUE ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1A0) ;/*clear OC1A on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1A1) ;
			    CLR_BIT(TIMSK  , OCIE1A) ;/*Disable interrupt of compare match A mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN5 , DIO_HIGH) ; /*set OC1A pin as output*/
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1B0) ;/*clear OC1B on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1B1) ;
			    CLR_BIT(TIMSK  , OCIE1B) ;/*Disable interrupt of compare match B mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN4 , DIO_HIGH) ; /*set OC1B pin as output*/
			#endif

		#elif TIMER1_MODE == PHASE_CORRECT_MODE_TOP_IS_ICR1
		    CLR_BIT(TCCR1A , WGM10) ;
		    SET_BIT(TCCR1A , WGM11) ;
		    CLR_BIT(TCCR1B , WGM12) ;
		    SET_BIT(TCCR1B , WGM13) ;
			ICR1 = TOP_ICR1_VALUE ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1A0) ;/*clear OC1A on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1A1) ;
			    CLR_BIT(TIMSK  , OCIE1A) ;/*Disable interrupt of compare match A mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN5 , DIO_HIGH) ; /*set OC1A pin as output*/
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1B0) ;/*clear OC1B on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1B1) ;
			    CLR_BIT(TIMSK  , OCIE1B) ;/*Disable interrupt of compare match B mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN4 , DIO_HIGH) ; /*set OC1B pin as output*/
			#endif

		#elif TIMER1_MODE == PHASE_CORRECT_MODE_TOP_IS_OCR1A
		    SET_BIT(TCCR1A , WGM10) ;
		    SET_BIT(TCCR1A , WGM11) ;
		    CLR_BIT(TCCR1B , WGM12) ;
		    SET_BIT(TCCR1B , WGM13) ;
			OCR1A = TOP_OCR1A_VALUE ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1A0) ;/*clear OC1A on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1A1) ;
			    CLR_BIT(TIMSK  , OCIE1A) ;/*Disable interrupt of compare match A mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN5 , DIO_HIGH) ; /*set OC1A pin as output*/
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1B0) ;/*clear OC1B on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1B1) ;
			    CLR_BIT(TIMSK  , OCIE1B) ;/*Disable interrupt of compare match B mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN4 , DIO_HIGH) ; /*set OC1B pin as output*/
			#endif

		#elif TIMER1_MODE == COMPARE_MATCH_MODE_TOP_IS_ICR1
		    CLR_BIT(TCCR1A , WGM10) ;
		    CLR_BIT(TCCR1A , WGM11) ;
		    SET_BIT(TCCR1B , WGM12) ;
		    SET_BIT(TCCR1B , WGM13) ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    SET_BIT(TIMSK , OCIE1A) ;/*Enable interrupt of compare match A mode*/
			    G_u32Timer1IntervalCtcACount = TIMER1_INTERVAL_A_COUNTS ;
			    #if TIMER1_COMPAREVALUE_A >= 0 && TIMER1_COMPAREVALUE_A <= 65535
				    ICR1 = TOP_ICR1_VALUE ;
			        OCR1A = TIMER1_COMPAREVALUE_A ;
			    #else #error "the value of TIMER1_COMPAREVALUE_A must be from 0 to 65535 && the value of TIMER1_COMPAREVALUE_B must be from 0 to 65535"
			    #endif
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    SET_BIT(TIMSK , OCIE1B) ;/*Enable interrupt of compare match A mode*/
			    G_u32Timer1IntervalCtcBCount = TIMER1_INTERVAL_B_COUNTS ;
			    #if TIMER1_COMPAREVALUE_B >= 0 && TIMER1_COMPAREVALUE_B <= 65535 && TIMER1_COMPAREVALUE_A >= 0 && TIMER1_COMPAREVALUE_A <= 65535
			        #if TIMER1_COMPAREVALUE_A < TIMER1_COMPAREVALUE_B
			            #error "TIMER1_COMPAREVALUE_A < TIMER1_COMPAREVALUE_B"
			        #endif
					ICR1 = TOP_ICR1_VALUE ;
			        OCR1A = TIMER1_COMPAREVALUE_A ;
			        OCR1B = TIMER1_COMPAREVALUE_B ;
			    #else #error "the value of TIMER1_COMPAREVALUE_B must be from 0 to 65535 && the value of TIMER1_COMPAREVALUE_A must be from 0 to 65535"
			    #endif
		    #endif

		#elif TIMER1_MODE == FAST_PWM_MODE_TOP_IS_ICR1
		    CLR_BIT(TCCR1A , WGM10) ;
		    SET_BIT(TCCR1A , WGM11) ;
		    SET_BIT(TCCR1B , WGM12) ;
		    SET_BIT(TCCR1B , WGM13) ;
			ICR1 = TOP_ICR1_VALUE ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1A0) ;/*clear OC1A on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1A1) ;
			    CLR_BIT(TIMSK  , OCIE1A) ;/*Disable interrupt of compare match A mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN5 , DIO_HIGH) ; /*set OC1A pin as output*/
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1B0) ;/*clear OC1B on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1B1) ;
			    CLR_BIT(TIMSK  , OCIE1B) ;/*Disable interrupt of compare match B mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN4 , DIO_HIGH) ; /*set OC1B pin as output*/
			#endif

		#elif TIMER1_MODE == FAST_PWM_MODE_TOP_IS_OCR1A
		    SET_BIT(TCCR1A , WGM10) ;
		    SET_BIT(TCCR1A , WGM11) ;
		    SET_BIT(TCCR1B , WGM12) ;
		    SET_BIT(TCCR1B , WGM13) ;
			OCR1A = TOP_OCR1A_VALUE ;
			#if COMPARE_TYPE == COMPARE_A || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1A0) ;/*clear OC1A on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1A1) ;
			    CLR_BIT(TIMSK  , OCIE1A) ;/*Disable interrupt of compare match A mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN5 , DIO_HIGH) ; /*set OC1A pin as output*/
			#endif
			#if COMPARE_TYPE == COMPARE_B || COMPARE_TYPE == COMPARE_BOTH
			    CLR_BIT(TCCR1A , COM1B0) ;/*clear OC1B on compare match , set at botton*/
			    SET_BIT(TCCR1A , COM1B1) ;
			    CLR_BIT(TIMSK  , OCIE1B) ;/*Disable interrupt of compare match B mode*/
			    MDIO_voidSetPinDir (DIO_PORTD , DIO_PIN4 , DIO_HIGH) ; /*set OC1B pin as output*/
			#endif

		#else #error "select correct options of TIMER1_MODE"
		#endif

	#elif TIMER1 == DISABLE1
	/** NO clk source (Timer1 stopped) */
	    CLR_BIT(TCCR1B , CS10) ;
	    CLR_BIT(TCCR1B , CS11) ;
	    CLR_BIT(TCCR1B , CS12) ;
	#else #error "TIMER1 must be ENABLE1 or DISABLE1"
	#endif
}

void MTimer_voidSetDisiredTime (u8 A_u8TimerID , f32 A_f32DisiredTime , void (*A_fptr)(void) )
{
	if (A_u8TimerID == TIMER0)
	{
		#if   TIMER0_MODE == NORMAL_MODE
		    /**
			  ** OverFlowTime       = (2^resolution) * Prescaller / system frequancy
			  ** OverFlowCount      = DisiredTime / OverFlowTime
			  ** NumberOfTimerCount = OverFlowCount * (2^resolution)
			  ** PreloadValue       = (2^resolution) - NumberOfTimerCount
			*/
		    f32 L_f32OverFlowTime        = 256 ;
	        f32 L_f32OverFlowCount       = 0 ;
	        u16  L_u16NumberOfTimerCount = 256 ;
	        u16  L_u16PreloadValue       = 0 ;		/*** Should be global to reuse it again in ISR
	         	 	 	 	 	 	 	 	 	 	 	 	to re-initialize TCNT0 	 ***/

	        L_f32OverFlowTime  = L_f32OverFlowTime * TIMER0_PRESCALER ;
            L_f32OverFlowTime  = L_f32OverFlowTime / CLOK_SYSTEM ;		/* NOW, this is the OVF time */
			L_f32OverFlowCount = A_f32DisiredTime / L_f32OverFlowTime ;	/* more or less than one */
			Timer0_Overflow_CallBack = A_fptr ;
			L_u16NumberOfTimerCount = L_u16NumberOfTimerCount * A_f32DisiredTime ;
			L_u16NumberOfTimerCount = L_u16NumberOfTimerCount / L_f32OverFlowTime ;
			if (L_f32OverFlowCount < 1.0)
			{
				/* PRELOAD SITUATION ONLY */
				L_u16PreloadValue       = 256 - L_u16NumberOfTimerCount ;
				TCNT0 = L_u16PreloadValue ;
				G_u32Timer0IntervalCount = 1 ;
			}
			else
			{
				/* ?????????? */
				G_u32Timer0IntervalCount = (u32)L_f32OverFlowCount ;
				if (L_f32OverFlowCount - (u32)L_f32OverFlowCount != 0.0) /* IF there is no pre-load */
				{
					L_u16NumberOfTimerCount = (u16)((L_u16NumberOfTimerCount / 256.0) * 256) ;
				    L_u16PreloadValue    = 256 - L_u16NumberOfTimerCount ;
				    TCNT0 = L_u16PreloadValue ;
					G_u32Timer0IntervalCount ++ ;
				}
			}
	    #endif
	}
	else if (A_u8TimerID == TIMER2)
	{
		#if   TIMER2_MODE == NORMAL_MODE
		    /**
			  ** OverFlowTime       = (2^resolution) * Prescaller / system frequancy
			  ** OverFlowCount      = DisiredTime / OverFlowTime
			  ** NumberOfTimerCount = OverFlowCount * (2^resolution)
			  ** PreloadValue       = (2^resolution) - NumberOfTimerCount
			*/
		    f32 L_f32OverFlowTime        = 256 ;
	        f32 L_f32OverFlowCount       = 0 ;
	        u16  L_u16NumberOfTimerCount = 256 ;
	        u16  L_u16PreloadValue       = 0 ;

	        L_f32OverFlowTime  = L_f32OverFlowTime * TIMER0_PRESCALER ;
            L_f32OverFlowTime  = L_f32OverFlowTime / CLOK_SYSTEM ;
			L_f32OverFlowCount = A_f32DisiredTime / L_f32OverFlowTime ;
			Timer2_Overflow_CallBack = A_fptr ;
			L_u16NumberOfTimerCount = L_u16NumberOfTimerCount * A_f32DisiredTime ;
			L_u16NumberOfTimerCount = L_u16NumberOfTimerCount / L_f32OverFlowTime ;
			if (L_f32OverFlowCount < 1.0)
			{
				L_u16PreloadValue       = 256 - L_u16NumberOfTimerCount ;
				TCNT2 = L_u16PreloadValue ;
				G_u32Timer2IntervalCount = 1 ;
			}
			else
			{
				G_u32Timer2IntervalCount = (u32)L_f32OverFlowCount ;
				if (L_f32OverFlowCount - (u32)L_f32OverFlowCount != 0.0)
				{
					L_u16NumberOfTimerCount = (u16)((L_u16NumberOfTimerCount / 256.0) * 256) ;
				    L_u16PreloadValue    = 256 - L_u16NumberOfTimerCount ;
				    TCNT2 = L_u16PreloadValue ;
					G_u32Timer2IntervalCount ++ ;
				}
			}
	    #endif
	}
	else if (A_u8TimerID == TIMER1)
	{
		#if   TIMER1_MODE == NORMAL_MODE
		    /**
			  ** OverFlowTime       = (2^resolution) * Prescaller / system frequancy
			  ** OverFlowCount      = DisiredTime / OverFlowTime
			  ** NumberOfTimerCount = OverFlowCount * (2^resolution)
			  ** PreloadValue       = (2^resolution) - NumberOfTimerCount
			*/
		    f32 L_f32OverFlowTime        = 65535 ;
	        f32 L_f32OverFlowCount       = 0 ;
	        u16  L_u16NumberOfTimerCount = 65535 ;
	        u16  L_u16PreloadValue       = 0 ;

	        L_f32OverFlowTime  = L_f32OverFlowTime * TIMER1_PRESCALER ;
            L_f32OverFlowTime  = L_f32OverFlowTime / CLOK_SYSTEM ;
			L_f32OverFlowCount = A_f32DisiredTime / L_f32OverFlowTime ;
			Timer1_Overflow_CallBack = A_fptr ;
			L_u16NumberOfTimerCount = L_u16NumberOfTimerCount * A_f32DisiredTime ;
			L_u16NumberOfTimerCount = L_u16NumberOfTimerCount / L_f32OverFlowTime ;
			if (L_f32OverFlowCount < 1.0)
			{
				L_u16PreloadValue       = 65535 - L_u16NumberOfTimerCount ;
				TCNT1 = L_u16PreloadValue ;
				G_u32Timer1IntervalCount = 1 ;
			}
			else
			{
				G_u32Timer1IntervalCount = (u32)L_f32OverFlowCount ;
				if (L_f32OverFlowCount - (u32)L_f32OverFlowCount != 0.0)
				{
					L_u16NumberOfTimerCount = (u16)((L_u16NumberOfTimerCount / 65535.0) * 65535) ;
				    L_u16PreloadValue    = 65535 - L_u16NumberOfTimerCount ;
				    TCNT1 = L_u16PreloadValue ;
					G_u32Timer1IntervalCount ++ ;
				}
			}
	    #endif
	}
}

void MTimer_voidCtcCallBack (u8  A_u8TimerID , void (*A_fptr1)(void) , void (*A_fptr2)(void))
{
	if (A_u8TimerID == TIMER0)
	{
        Timer0_CTC_CallBack = A_fptr1 ;
	}
	else if (A_u8TimerID == TIMER2)
	{
		Timer2_CTC_CallBack = A_fptr1 ;
	}
	else if (A_u8TimerID == TIMER1)
	{
		#if   COMPARE_TYPE == COMPARE_A
		    Timer1_CTC_A_CallBack = A_fptr1 ;
		#elif COMPARE_TYPE == COMPARE_B
		    Timer1_CTC_B_CallBack = A_fptr2 ;
		#elif COMPARE_TYPE == COMPARE_BOTH
		    Timer1_CTC_A_CallBack = A_fptr1 ;
			Timer1_CTC_B_CallBack = A_fptr2 ;
		#endif
	}
}

void MTimer_voidSetPWM (u8  A_u8TimerID , u16 A_u16CompareValueA , u16 A_u16CompareValueB)
{
    if (A_u8TimerID == TIMER0)
	{
		#if TIMER0_MODE == FAST_PWM_MODE || TIMER0_MODE == PWM_PHASE_CORRECT_MODE
		    OCR0 = A_u16CompareValueA ;
		#endif
	}
	else if (A_u8TimerID == TIMER2)
	{
		#if TIMER2_MODE == FAST_PWM_MODE || TIMER2_MODE == PWM_PHASE_CORRECT_MODE
	        OCR2 = A_u16CompareValueA ;
		#endif
	}
	else if (A_u8TimerID == TIMER1)
	{
		#if TIMER1_MODE == FAST_PWM_MODE_8_BITS      || TIMER1_MODE == FAST_PWM_MODE_9_BITS      || TIMER1_MODE == FAST_PWM_MODE_10_BITS      || \
		    TIMER1_MODE == PHASE_CORRECT_MODE_8_BITS || TIMER1_MODE == PHASE_CORRECT_MODE_9_BITS || TIMER1_MODE == PHASE_CORRECT_MODE_10_BITS || \
			TIMER1_MODE == FREQUANCY_CORRECT_MODE_TOP_IS_ICR1 || TIMER1_MODE == FREQUANCY_CORRECT_MODE_TOP_IS_OCR1A || \
			TIMER1_MODE == PHASE_CORRECT_MODE_TOP_IS_ICR1     || TIMER1_MODE == PHASE_CORRECT_MODE_TOP_IS_OCR1A     || \
			TIMER1_MODE == FAST_PWM_MODE_TOP_IS_ICR1          || TIMER1_MODE == FAST_PWM_MODE_TOP_IS_OCR1A
		    #if   COMPARE_TYPE == COMPARE_A
		          OCR1A = A_u16CompareValueA ;
		    #elif COMPARE_TYPE == COMPARE_B
		    	  OCR1B = A_u16CompareValueB ;
			#elif COMPARE_TYPE == COMPARE_BOTH
			      OCR1A = A_u16CompareValueA ;
			      OCR1B = A_u16CompareValueB ;
		    #endif
		#endif
	}
}

u32 MTimerCalcFreqofTon (void)
{
	u32 L_u32Period = 0 ;
	G_u32OverFlowCounts = 0 ;

	SET_BIT (TIFR , ICF1) ;              /*clear PIF flag*/
	SET_BIT(TCCR1B , ICES1) ;            /*set input capture edge to detect rising edge*/
	while (READ_BIT (TIFR , ICF1) == 0) ;/*wait for capture happened*/
	G_u32CountsForFirstRising = (ICR1 + ((u32)65535*G_u32OverFlowCounts)) ;   /*take value of capture register*/

	SET_BIT (TIFR , ICF1) ;              /*clear PIF flag*/
	CLR_BIT(TCCR1B , ICES1) ;            /*set input capture edge to detect falling edge*/
	while (READ_BIT (TIFR , ICF1) == 0) ;/*wait for capture happened*/
	G_u32CountsForFirstFaling = (ICR1 + ((u32)65535*G_u32OverFlowCounts)) ;   /*take value of capture register*/

	G_u32OverFlowCounts = 0 ;

	L_u32Period = G_u32CountsForFirstFaling - G_u32CountsForFirstRising ;

	G_u32FrequancyOfTimeOn = CLOK_SYSTEM / (L_u32Period * (u32)TIMER1_PRESCALER) ;
	return G_u32FrequancyOfTimeOn ;

}

f32 MTimerCalcDutyCycle (void)
{
	u32 L_u32Period = 0 ;
	u32 L_u32High  = 0 ;
	f32  L_f32Duty = 0.0 ;
	G_u32OverFlowCounts = 0 ;

	SET_BIT (TIFR , ICF1) ;              /*clear PIF flag*/
	SET_BIT(TCCR1B , ICES1) ;            /*set input capture edge to detect rising edge*/
	while (READ_BIT (TIFR , ICF1) == 0) ;/*wait for capture happened*/
	G_u32CountsForFirstRising = (ICR1 + ((u32)65535*G_u32OverFlowCounts)) ;   /*take value of capture register*/

	SET_BIT (TIFR , ICF1) ;              /*clear PIF flag*/
	CLR_BIT(TCCR1B , ICES1) ;            /*set input capture edge to detect falling edge*/
	while (READ_BIT (TIFR , ICF1) == 0) ;/*wait for capture happened*/
	G_u32CountsForFirstFaling = (ICR1 + ((u32)65535*G_u32OverFlowCounts)) ;   /*take value of capture register*/

	SET_BIT (TIFR , ICF1) ;              /*clear PIF flag*/
	SET_BIT(TCCR1B , ICES1) ;            /*set input capture edge to detect rising edge*/
	while (READ_BIT (TIFR , ICF1) == 0) ;/*wait for capture happened*/
	G_u32CountsForSecondRising = (ICR1 + ((u32)65535*G_u32OverFlowCounts)) ;   /*take value of capture register*/
	SET_BIT (TIFR , ICF1) ;              /*clear PIF flag*/

	G_u32OverFlowCounts = 0 ;

	L_u32High   = G_u32CountsForFirstFaling - G_u32CountsForFirstRising ;
	L_u32Period = G_u32CountsForSecondRising - G_u32CountsForFirstRising ;
	L_f32Duty = L_u32High * 100 ;
	L_f32Duty = L_f32Duty / (f32)L_u32Period ;
	return L_f32Duty ;
}

u32 MTimerCalcFreqofTtotal (void)
{
		u32 L_u32Period = 0 ;
		G_u32OverFlowCounts = 0 ;

		SET_BIT (TIFR , ICF1) ;              /*clear PIF flag*/
		SET_BIT(TCCR1B , ICES1) ;            /*set input capture edge to detect rising edge*/
		while (READ_BIT (TIFR , ICF1) == 0) ;/*wait for capture happened*/
		G_u32CountsForFirstRising = (ICR1 + ((u32)65535*G_u32OverFlowCounts)) ;   /*take value of capture register*/

		SET_BIT (TIFR , ICF1) ;              /*clear PIF flag*/
		SET_BIT(TCCR1B , ICES1) ;            /*set input capture edge to detect rising edge*/
		while (READ_BIT (TIFR , ICF1) == 0) ;/*wait for capture happened*/
		G_u32CountsForSecondRising = (ICR1 + ((u32)65535*G_u32OverFlowCounts)) ;   /*take value of capture register*/
		SET_BIT (TIFR , ICF1) ;              /*clear PIF flag*/

		G_u32OverFlowCounts = 0 ;

		L_u32Period = G_u32CountsForSecondRising - G_u32CountsForFirstRising ;
		G_u32FrequancyOfTimeTotal = CLOK_SYSTEM / (L_u32Period * (u32)TIMER1_PRESCALER) ;
		return G_u32FrequancyOfTimeTotal ;
}

/*ISR of Timer0 over flow*/
//void __vector_11(void)__attribute__((signal))__attribute__((interrupt));
//void __vector_11(void)
//{
//	static u32 LS_u32Counter = 0;
//
//	LS_u32Counter++ ;
//	if(LS_u32Counter == G_u32Timer0IntervalCount)
//	{
//		if(Timer0_Overflow_CallBack != NULL)
//		{
//			Timer0_Overflow_CallBack();
//			LS_u32Counter = 0;
//		}
//	}
//}

/*ISR of Timer0 compare match*/
void __vector_10(void)__attribute__((signal))__attribute__((interrupt));
void __vector_10(void)
{
	static u32 LS_u32Counter = 0;

	LS_u32Counter++ ;

	if(LS_u32Counter == G_u32Timer0IntervalCtcCount)
	{
		if(Timer0_CTC_CallBack != NULL)
		{
			Timer0_CTC_CallBack();
			LS_u32Counter = 0;
		}
	}
}

/*ISR of Timer2 over flow*/
void __vector_5(void)__attribute__((signal))__attribute__((interrupt));
void __vector_5(void)
{
	static u32 LS_u32Counter = 0;

	LS_u32Counter++ ;
	if(LS_u32Counter == G_u32Timer2IntervalCount)
	{
		if(Timer2_Overflow_CallBack != NULL)
		{
			Timer2_Overflow_CallBack();
			LS_u32Counter = 0;
		}
	}
}

/*ISR of Timer2 compare match*/
void __vector_4(void)__attribute__((signal))__attribute__((interrupt));
void __vector_4(void)
{
	static u32 LS_u32Counter = 0;

	LS_u32Counter++ ;

	if(LS_u32Counter == G_u32Timer2IntervalCtcCount)
	{
		if(Timer2_CTC_CallBack != NULL)
		{
			Timer2_CTC_CallBack();
			LS_u32Counter = 0;
		}
	}
}
//
///*ISR of Timer1 over flow*/
//void __vector_9(void)__attribute__((signal))__attribute__((interrupt));
//void __vector_9(void)
//{
//	static u32 LS_u32Counter = 0;
//    G_u32OverFlowCounts ++ ;
//	LS_u32Counter++ ;
//	DDRC = DDRC+1 ; ;
//	if(LS_u32Counter == G_u32Timer1IntervalCount)
//	{
//		if(Timer1_Overflow_CallBack != NULL)
//		{
//			Timer1_Overflow_CallBack();
//			LS_u32Counter = 0;
//		}
//	}
//}
//
///*ISR of Timer1 compare match A*/
//void __vector_7(void)__attribute__((signal))__attribute__((interrupt));
//void __vector_7(void)
//{
//	static u32 LS_u32Counter = 0;
//
//	LS_u32Counter++ ;
//
//	if(LS_u32Counter == G_u32Timer1IntervalCtcACount)
//	{
//		if(Timer1_CTC_A_CallBack != NULL)
//		{
//			Timer1_CTC_A_CallBack();
//			LS_u32Counter = 0;
//		}
//	}
//}

/*ISR of Timer1 compare match B*/
//void __vector_8(void)__attribute__((signal))__attribute__((interrupt));
//void __vector_8(void)
//{
//	static u32 LS_u32Counter = 0;
//
//	LS_u32Counter++ ;
//
//	if(LS_u32Counter == G_u32Timer1IntervalCtcBCount)
//	{
//		if(Timer1_CTC_B_CallBack != NULL)
//		{
//			Timer1_CTC_B_CallBack();
//			LS_u32Counter = 0;
//		}
//	}
//}
