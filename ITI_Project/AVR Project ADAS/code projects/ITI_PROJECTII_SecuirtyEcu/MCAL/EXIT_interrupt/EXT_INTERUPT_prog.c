/*
 * EXT_INTERUPT_prg.c
 *
 *  Created on: Jun 2, 2022
 *      Author: Mohamed Ramadan
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../DIO/DIO_int.h"
#include "EXT_INTERUPT_register.h"
#include "EXT_INTERRUPT_private.h"
#include "EXT_INTERUPT_conf.h"
#include "EXT_INTERUPT_int.h"

static void (*INT0_CallBack)(void) ; /**pointer to function to set call back of INT0_ISR*/
static void (*INT1_CallBack)(void) ; /**pointer to function to set call back of INT1_ISR*/
static void (*INT2_CallBack)(void) ; /**pointer to function to set call back of INT2_ISR*/

static void (*INT0_CallBack1)(void) ;
static void (*INT0_CallBack2)(void) ;
static void (*INT0_CallBack3)(void) ;

void MINT_voidInit (void)
{
	/** Enable global interrupt flag */
	    SET_BIT(SREG, I_BIT);

	/******************************************/
	/**         External interrupt 0          */
	#if   EXTI0 == ENABLE

	    /** Enable PIE of INT0 */
	    SET_BIT(GICR, INT0);

		    /** Sence control of INT0*/
	        #if   EXTI0_SENCE == LOW_LEVEL
		        /** sense INT0 to low level */
		        CLR_BIT (MCUCR , ISC00 ) ;
		    	CLR_BIT (MCUCR , ISC01 ) ;

	        #elif EXTI0_SENCE == ON_CHANGE
		        /** sense INT0 to any change (rising edge or falling edge) */
		    	SET_BIT (MCUCR , ISC00 ) ;
		    	CLR_BIT (MCUCR , ISC01 ) ;

	        #elif EXTI0_SENCE == FALLING_EDGE
		        /** sense INT0 to falling edge */
		    	CLR_BIT (MCUCR , ISC00 ) ;
		    	SET_BIT (MCUCR , ISC01 ) ;

	        #elif EXTI0_SENCE == RISING_EDGE
		        /** sense INT0 to rising edge */
		    	SET_BIT (MCUCR , ISC00 ) ;
		    	SET_BIT (MCUCR , ISC01 ) ;

	        #else
		    	#error "EXTI0_SENCE must be LOW_LEVEL or ON_CHANGE or FALLING_EDGE or RISING_EDGE"
		    #endif

	#elif EXTI0 == DISABLE
	    /** disable PIE of INT0 */
	    CLR_BIT(GICR, INT0);

	#else
	    #error "EXTI0 must be ENABLE or DISABLE"
	#endif

	/******************************************/
	/**         External interrupt 1          */
	#if   EXTI1 == ENABLE

	    /** Enable PIE of INT1 */
	    SET_BIT(GICR, INT1);

		/** Sence control of INT0*/
	        #if   EXTI1_SENCE == LOW_LEVEL
		        /** sense INT1 to low level */
		    	CLR_BIT (MCUCR , ISC10 ) ;
		    	CLR_BIT (MCUCR , ISC11 ) ;

	        #elif EXTI1_SENCE == ON_CHANGE
		        /** sense INT1 to any change (rising edge or falling edge) */
		    	SET_BIT (MCUCR , ISC10 ) ;
		    	CLR_BIT (MCUCR , ISC11 ) ;

	        #elif EXTI1_SENCE == FALLING_EDGE
		        /** sense INT1 to falling edge */
		    	CLR_BIT (MCUCR , ISC10 ) ;
    	        SET_BIT (MCUCR , ISC11 ) ;

	        #elif EXTI1_SENCE == RISING_EDGE
		        /** sense INT1 to rising edge */
		    	SET_BIT (MCUCR , ISC10 ) ;
		    	SET_BIT (MCUCR , ISC11 ) ;

	        #else
		    	#error "EXTI1_SENCE must be LOW_LEVEL or ON_CHANGE or FALLING_EDGE or RISING_EDGE"
		    #endif

	#elif EXTI1 == DISABLE
	    /** disable PIE of INT1 */
	    CLR_BIT(GICR, INT1);

	#else
	    #error "EXTI1 must be ENABLE or DISABLE"
	#endif

	/******************************************/
	/**         External interrupt 2          */
	#if   EXTI2 == ENABLE

	    /** Enable PIE of INT2 */
	    SET_BIT(GICR, INT2) ;

		/** Sence control of INT2*/
	        #if   EXTI2_SENCE == FALLING_EDGE
		         /** sense INT2 to falling edge */
		         CLR_BIT (MCUCSR , ISC2 ) ;

	        #elif EXTI2_SENCE == RISING_EDGE
		        /** sense INT2 to rising edge */
		    	SET_BIT (MCUCSR , ISC2 ) ;

	        #else
		    	#error "EXTI2_SENCE must be FALLING_EDGE or RISING_EDGE"
		    #endif

	#elif EXTI2 == DISABLE
	    /** disable PIE of INT2 */
	    CLR_BIT(GICR, INT2);

	#else
	    #error "EXTI2 must be ENABLE or DISABLE"
	#endif
}

void MINT0_voidSetCallback( void (*A_fptr)(void)  )
{
	INT0_CallBack = A_fptr;
}

void MINT1_voidSetCallback( void (*A_fptr)(void)  )
{
	INT1_CallBack = A_fptr;
}

void MINT2_voidSetCallback( void (*A_fptr)(void)  )
{
	INT2_CallBack = A_fptr;
}

void MINT0_voidSetCallback_Three( void (*A_fptr1)(void), void (*A_fptr2)(void), void (*A_fptr3)(void)  )
{
	INT0_CallBack1 = A_fptr1;
	INT0_CallBack2 = A_fptr2;
	INT0_CallBack3 = A_fptr3;
}



/**ISR of INT0*/
void __vector_1(void)__attribute__((signal))__attribute__((interrupt));
void __vector_1(void)
{

	u8 static L_State = 0;
	if(L_State == 0)
	{
		L_State = 1; 	/* change it to the next state */
		if (INT0_CallBack1 != Null){
			INT0_CallBack1 () ;
		}
	}

	if(L_State == 1)
	{
		L_State = 2;	/* change it to the next state */
		if (INT0_CallBack2 != Null){
			INT0_CallBack2 () ;
		}
	}

	if(L_State == 2)
	{
		L_State = 0;	/* reset */
		if (INT0_CallBack3 != Null){
			INT0_CallBack3 () ;
		}
	}

}




/**ISR of INT1*/
void __vector_2(void)__attribute__((signal))__attribute__((interrupt));
void __vector_2(void)
{
	if (INT1_CallBack != Null)
	{
		INT1_CallBack () ;
	}
}

/**ISR of INT2*/
void __vector_3(void)__attribute__((signal))__attribute__((interrupt));
void __vector_3(void)
{
	if (INT2_CallBack != Null)
	{
		INT2_CallBack () ;
	}
}

