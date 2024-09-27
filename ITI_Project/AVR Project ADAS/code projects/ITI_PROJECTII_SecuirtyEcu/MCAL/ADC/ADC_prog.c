/*
 * ADC_prog.c
 *
 *  Created on: Jul 5, 2022
 *      Author: Mohammed Ramadan
 */
 
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "ADC_int.h"
#include "ADC_register.h"
#include "ADC_private.h"
#include "ADC_conf.h"

/**pointer to function to set call back of ADC*/
void (*ADC_Callback) (void) ;

void MADC_voidInt (void)
{
	/** referance voltage selection*/
	#if   ADC_REF_VOLT == AREF          /**external ADC referance voltage (internal Vref turrned off)*/
	    CLR_BIT(ADMUX , REFS0) ;
	    CLR_BIT(ADMUX , REFS1) ;
	#elif ADC_REF_VOLT == AVCC          /**Vcc of ADC*/
	    SET_BIT(ADMUX , REFS0) ;
	    CLR_BIT(ADMUX , REFS1) ;
	#elif ADC_REF_VOLT == AREF_INTERNAL /**internal 2.56 voltage*/
	    SET_BIT(ADMUX , REFS0) ;
	    SET_BIT(ADMUX , REFS1) ;
	#else
		#error "Please select correct refence voltage"
	#endif
	
	/**set adjust result to right adjust*/
	CLR_BIT(ADMUX , ADLAR) ;
	
	/**set prescaller of ADC clk*/
	#if   ADC_PRESCALER == ADC_PS_2 /**clk = 4MHZ*/
	    SET_BIT(ADCSRA , ADPS0) ;
		CLR_BIT(ADCSRA , ADPS1) ;
		CLR_BIT(ADCSRA , ADPS2) ;
	#elif ADC_PRESCALER == ADC_PS_4 /**clk = 2MHZ*/
	    CLR_BIT(ADCSRA , ADPS0) ;
		SET_BIT(ADCSRA , ADPS1) ;
		CLR_BIT(ADCSRA , ADPS2) ;   
	#elif ADC_PRESCALER == ADC_PS_8 /**clk = 1MHZ*/
	    SET_BIT(ADCSRA , ADPS0) ;
		SET_BIT(ADCSRA , ADPS1) ;
		CLR_BIT(ADCSRA , ADPS2) ;
	#elif ADC_PRESCALER == ADC_PS_16 /**clk = 500KHZ*/
	    CLR_BIT(ADCSRA , ADPS0) ;
		CLR_BIT(ADCSRA , ADPS1) ;
		SET_BIT(ADCSRA , ADPS2) ;
	#elif ADC_PRESCALER == ADC_PS_32 /**clk = 250KHZ*/
	    SET_BIT(ADCSRA , ADPS0) ;
		CLR_BIT(ADCSRA , ADPS1) ;
		SET_BIT(ADCSRA , ADPS2) ;
	#elif ADC_PRESCALER == ADC_PS_64 /**clk = 125KHZ*/
	    CLR_BIT(ADCSRA , ADPS0) ;
		SET_BIT(ADCSRA , ADPS1) ;
		SET_BIT(ADCSRA , ADPS2) ;
	#elif ADC_PRESCALER == ADC_PS_128 /**clk = 62.5KHZ*/
	    SET_BIT(ADCSRA , ADPS0) ;
		SET_BIT(ADCSRA , ADPS1) ;
		SET_BIT(ADCSRA , ADPS2) ;
	#else 
		#error "select correct division factor"
	#endif
	
	/**Enable ADC peripheral*/
	SET_BIT(ADCSRA, ADEN);
	
	/**ADC Interrupt Enable*/
    SET_BIT(ADCSRA, ADIE);
	
	/**Auto trigger Disable*/
	CLR_BIT(ADCSRA, ADATE);		// ??
	
	/**Enable global interrupt flag*/
	SET_BIT (SREG , I_BIT) ;
}

void MADC_voidStartConversion(u8 A_u8ChannelNo)
{
	switch (A_u8ChannelNo)
	{
		case CHANNEL_0 :  CLR_BIT(ADMUX , MUX0) ;
						  CLR_BIT(ADMUX , MUX1) ;
						  CLR_BIT(ADMUX , MUX2) ;
						  CLR_BIT(ADMUX , MUX3) ;
						  CLR_BIT(ADMUX , MUX4) ;
						  break ;
						  
		case CHANNEL_1 :  SET_BIT(ADMUX , MUX0) ;
						  CLR_BIT(ADMUX , MUX1) ;
						  CLR_BIT(ADMUX , MUX2) ;
						  CLR_BIT(ADMUX , MUX3) ;
						  CLR_BIT(ADMUX , MUX4) ;
						  break ;
						  
		case CHANNEL_2 :  CLR_BIT(ADMUX , MUX0) ;
						  SET_BIT(ADMUX , MUX1) ;
						  CLR_BIT(ADMUX , MUX2) ;
						  CLR_BIT(ADMUX , MUX3) ;
						  CLR_BIT(ADMUX , MUX4) ;
						  break ;
						  
		case CHANNEL_3 :  SET_BIT(ADMUX , MUX0) ;
						  SET_BIT(ADMUX , MUX1) ;
						  CLR_BIT(ADMUX , MUX2) ;
						  CLR_BIT(ADMUX , MUX3) ;
						  CLR_BIT(ADMUX , MUX4) ;
						  break ;
						  
		case CHANNEL_4 :  CLR_BIT(ADMUX , MUX0) ;
						  CLR_BIT(ADMUX , MUX1) ;
						  SET_BIT(ADMUX , MUX2) ;
						  CLR_BIT(ADMUX , MUX3) ;
						  CLR_BIT(ADMUX , MUX4) ;
						  break ;
						  
		case CHANNEL_5 :  SET_BIT(ADMUX , MUX0) ;
						  CLR_BIT(ADMUX , MUX1) ;
						  SET_BIT(ADMUX , MUX2) ;
						  CLR_BIT(ADMUX , MUX3) ;
						  CLR_BIT(ADMUX , MUX4) ;
						  break ;
						  
		case CHANNEL_6 :  CLR_BIT(ADMUX , MUX0) ;
						  SET_BIT(ADMUX , MUX1) ;
						  SET_BIT(ADMUX , MUX2) ;
						  CLR_BIT(ADMUX , MUX3) ;
						  CLR_BIT(ADMUX , MUX4) ;
						  break ;
						  
		case CHANNEL_7 :  SET_BIT(ADMUX , MUX0) ;
						  SET_BIT(ADMUX , MUX1) ;
						  SET_BIT(ADMUX , MUX2) ;
						  CLR_BIT(ADMUX , MUX3) ;
						  CLR_BIT(ADMUX , MUX4) ;
						  break ;
		default         : /**ERROR*/
		                  break ;				  
	}
	
	/**Start Conversion */
	SET_BIT(ADCSRA, ADSC);
}

/* 2 OPTIONS : 1- PULLING (SYNCH) & 2- INTERRUPT (ASYNCH)
	 *
	 * OPTION 1 :
	/* POLLING ON THE FLAG UNTIL HARDWARE SET IT TO 1
	 *THAT HAPPENS AFTER FINSHING THE CONVERSION */
	/*
	 *
	 * while ((READ_BIT(ADCSRA, ADCSRA_ADIF)) == 0);
			// stuck here, until finish, blocking other processes

	/*CLEAR THE FLAG
	 *SET_BIT(ADCSRA, ADCSRA_ADIF);
	 *
	 * OPTION 2 => IN MAIN
	 */


/* You can benefit from this function : either by pooling or by ISR */
u16  MADC_u16GetADCData(void)
{
//	while ((READ_BIT(ADCSRA,ADIF)) == 1);
//	SET_BIT(ADCSRA,ADIF);

	/**return ADC Data  */
	return ADC ;

}

void MADC_voidSetCallback( void (*A_fptr)(void)  )
{
	ADC_Callback = A_fptr;
}

/**ISR of ADC*/
void __vector_16(void)__attribute__((signal))__attribute__((interrupt));
void __vector_16(void)
{
	if (ADC_Callback != Null)
	{
		ADC_Callback () ;
	}
}
