

/* IMPROTANT::: */
/* WHEN_YOU_USE_HW : GO TO ADAS_CONTROL.C TO LINE 239 : G_Ultrasonic_Distance = 11; AND UNCOMMENT IT
 */

/* NOTE 1 :  The idea that I made to link between EXTI and showing functions in main based on if
 * - the function called in ISR for INTs is to change a value of GLOBAL VARIABLEs
 * - based on its updated value, some function is called : ON or OFF in main
 * - they are called in ISR if there is an interrupt & called in main for the last update.
 */


/* NOTE 2 : the feature of cancel the BUZZER if there is any change :
 * 		I didn't make it for GAS_POT_ADC, but if I want :
 * 			- I will use ADC_vect in ISR that is done after complete the conversion
 * 			- in the function called in ISR : void GasChange_CancelBuz(void) I will make :
 * 					- static previous_Val and updated_Val
 * 					- comparing between them, if NOT EQUAL => BUZ_FLAG = 0 (a change happened )
 *
 * 	And I really try it, but there is a problem with ADC_vect
 */


/* NOTE 3 : It was a good idea, Alhamdullilah, that I used the GLOBAl VARIABLES
 * 		and took action, based on their updated values, in main()
 * 			as for TIMER2_vect, IF I took the action its ISR
 * 				and make a change after the BUZZER's been turned ON,
 * 					THERE'VE BEEN NESTED INTs which is not provided in AVR.
 *
 * 		AND even if it is provided, for ARM for ex, may be the INTs of the changes
 * 			are less priority than TIMER OVF ISR.
 */

#include "ADAS_CONTROL_Includes.h"
#include "ADAS_CONTROL.h"

u8 G_Reciv_A;			/* From Security ECU using UART */

/* GLOBAL VARIABLEs to be accessed by all the program */
extern volatile u8 G_u8_GRBox_rtrn;
extern volatile u8 G_u8_SL_rtrn;
extern volatile u8 G_u8_CCS_rtrn;

/* counts until it get TICKS FOR 5sec of TIMER2 */
extern volatile u32 Timer2_OVFs_5sec;
extern volatile u8 BUZ_FLAG;			/* MADE 0 BY EXTIs = change happened */

int main()
{

	u16 ADC_GasVal;		/* For KILMOTER COUNTER */

	UART_INIT(MY_UBRR);		/* BAUD_R OF COMMUNICATION */
	HLCD_voidInit();
	MADC_voidInt();			/* KILOMETER COUNTER */
	Ultrasonic_Init();		/* BAS SYSTEM */


	/* For Drive Monitoring -- TIMER2_OVF */
	TIMSK |= (1<<TOIE2); 	/* Enable INT */
	sei(); 					/* Enable global INT */
	TCNT2 = 0;


	/* FOR BUTTON CONTROLS G_BOX & SL & CCS via EXTIs */
	HPushBotton_voidPbInt(Pb1_ID);	/* Enable pull-up for INT2 -- GearBox*/
	HPushBotton_voidPbInt(Pb2_ID);	/* Enable pull-up for INT0 -- SL*/
	HPushBotton_voidPbInt(Pb3_ID);	/* Enable pull-up for INT1 -- CCS*/
	MINT_voidInit();	/* Enable EXTI */

	/* Initiate LEDS for CCS & SL & BUZZER(DRIVE Monitoring) */
	DDRA |= (1<< SL_LED);
	DDRA |= (1<< CCS_LED);
	DDRA |= (1<< BUZ_PIN);

	/* Set call backs for EXTIs */
	MINT2_voidSetCallback(GRBOX_SELECT);
	MINT0_voidSetCallback(SL_STATUS);
	MINT1_voidSetCallback(CCS_STATUS);



	/* GET 'A' FROM SECURITY ECU */
		G_Reciv_A = UART_RECIEV();
		if ('A' == G_Reciv_A)
	{
		/* DRIVE MONITORING */
		/* Set prescaler 1024 -- TIMER2 Starts counting after open the car */
		TCCR2 |= (1<<CS20) | (1<<CS21) | (1<<CS22);

		while (1)
		{

			if (G_u8_GRBox_rtrn == GEAR_D)
			{
				/* BAS */
				UltrasonicTriggerAndEcho();

				/* G_BOX STATUS : D */
				HLCD_voidMovCursor(1,9);
				HLCD_voidSendData('D');

				/* SL & CCS */
				/* For SL & CCS => I've handled them in ISRs (using their buttons) */
				/* AND calling them here, too before ISR agian */
				if(G_u8_SL_rtrn == 1)
					SL_ON();
				else
					SL_OFF();

				if(G_u8_CCS_rtrn == 1)
					CCS_ON();
				else
					CCS_OFF();


				/* BAS ON  depened on G_Ultrasonic_Distance*/
				update_BAS_SystemON();


			}
			else
			{
				/* BAS OFF, as G_BOX not in D */
				update_BAS_SystemOFF();


				/* OTHER STATUS FOR G_BOX */
				if(G_u8_GRBox_rtrn == GEAR_P){
					HLCD_voidMovCursor(1,9);
					HLCD_voidSendData('P');
				}

				else if(G_u8_GRBox_rtrn == GEAR_R){
					HLCD_voidMovCursor(1,9);
					HLCD_voidSendData('R');
				}
				else if(G_u8_GRBox_rtrn == GEAR_N){
					HLCD_voidMovCursor(1,9);
					HLCD_voidSendData('N');
				}

				/* SL OFF , as G_BOX not in D */
				SL_OFF();

				/* CCS OFF , as G_BOX not in D */
				CCS_OFF();

			}



			/* KILOMETER COUNTER */
			/* Start conversion for each change of input (INSIDE WHILE(1) I MEAN) */
			MADC_voidStartConversion(CHANNEL_0);
			while(MDIO_u8GetPinVal(ADCSRA,ADIF) == 1);  /* It should be 0, but it works this way */
			/* Clear the flag */
			SET_BIT(ADCSRA,ADIF);
			ADC_GasVal = MADC_u16GetADCData();	/* Data is prepared */
			KilometerCounter(ADC_GasVal);		/* kilos depend on GAS_val */




			/* DRIVE MONITORING */
			while (BUZ_FLAG == 1)		/* made 0 with any change (THE 3 BUTTONS) */
			{
				PORTA |= (1<<BUZ_PIN);
				_delay_ms(100);
				PORTA &= ~(1<<BUZ_PIN);
			}


			/* DATA DISPLAYED FOR A DELAY TIME */
			_delay_ms(1000);
			HLCD_voidClrScreen();
		}
	}











	return 0;

}


