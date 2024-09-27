#include "ADAS_CONTROL_Includes.h"
#include "ADAS_CONTROL.h"

extern u8 G_Reciv_A;

/* GLOBAL VARIABLEs to be accessed by all the program */
volatile u8 G_u8_GRBox_rtrn;
volatile u8 G_u8_SL_rtrn;
volatile u8 G_u8_CCS_rtrn;


volatile u32 CounterOVFsForBuzzer = 0;

/* AFTER 5sec it is 1 and 0 if there is any change */
volatile u8 BUZ_FLAG = 0;
u32 CalcTimeforKilomCounter = 0;		/* OVFs of TIMER2 */

/* FOR BAS & ULTRASONIC */
volatile uint16_t OVF_CounterTimer1;
volatile uint16_t OVF_CounterTimer1_Copy;	/* To take OVFs value when it is done */
volatile uint8_t EdgeStatus;		/* 0 => before rising edg, 1=> after it, 2 => after falling edg*/
volatile uint32_t CAP1, CAP2;		/* for each edge */
float G_Ultrasonic_Distance = 0;



/***********************************************************************************************/
/********************************   GEAR BOX   *************************************************/
/***********************************************************************************************/

u8 GRBOX_SELECT(void)
{
	HLCD_voidMovCursor(1,9);

	/* UPDATE depend on previous position */
	switch (G_u8_GRBox_rtrn)
	{
	case GEAR_N : G_u8_GRBox_rtrn = GEAR_D; HLCD_voidSendData('D'); break;
	case GEAR_D : G_u8_GRBox_rtrn = GEAR_P; HLCD_voidSendData('P'); break;
	case GEAR_P : G_u8_GRBox_rtrn = GEAR_R; HLCD_voidSendData('R'); break;
	case GEAR_R : G_u8_GRBox_rtrn = GEAR_N; HLCD_voidSendData('N'); break;
	}

	TCNT2 = 0;
	CounterOVFsForBuzzer = 0;	/* for have EXTI before get 5sec without change */
	BUZ_FLAG = 0;				/* EXTI after 5sec */
	return G_u8_GRBox_rtrn;
}

/***********************************************************************************************/
/********************************  SL SYSTEM  *************************************************/
/***********************************************************************************************/
void SL_STATUS(void)
{
	/* you are here, it means you push button INT0 */
	if (G_u8_SL_rtrn == 0)
	{
		G_u8_SL_rtrn = 1;
		if(G_u8_GRBox_rtrn ==1)	/* Is GBox in D? */
			SL_ON();
	}
	else if (G_u8_SL_rtrn == 1)
	{
		G_u8_SL_rtrn = 0;
		SL_OFF();
	}

	/* A change happened --> Reset TIMER2 for Drive Monitoring */
	TCNT2 = 0;
	CounterOVFsForBuzzer = 0;	/* for have EXTI before get 5sec without change */
	BUZ_FLAG = 0;				/* EXTI after 5sec */

}
void SL_ON(void)
{

	PORTA |= (1<<SL_LED);
	HLCD_voidMovCursor(1,1);
	HLCD_voidDispStr("SL: ON");


}

void SL_OFF(void)
{

	PORTA &= ~(1<<SL_LED);
	HLCD_voidMovCursor(1,1);
	HLCD_voidDispStr("SL:OFF");


}

/***********************************************************************************************/
/********************************  CCS SYSTEM  *************************************************/
/***********************************************************************************************/
void CCS_STATUS(void)
{
	/* you are here, it means you push button INT1 */
	if (G_u8_CCS_rtrn == 0)
	{
		G_u8_CCS_rtrn = 1;
		if(G_u8_GRBox_rtrn ==1)	/* Is GBox in D? */
			CCS_ON();
	}
	else if (G_u8_CCS_rtrn == 1)
	{
		G_u8_CCS_rtrn = 0;
		CCS_OFF();
	}

	/* A change happened --> Reset TIMER2 for Drive Monitoring */
	TCNT2 = 0;
	CounterOVFsForBuzzer = 0;	/* for have EXTI before get 5sec without change */
	BUZ_FLAG = 0;				/* EXTI after 5sec */
}


void CCS_ON(void)
{
	PORTA |= (1<<CCS_LED);
	HLCD_voidMovCursor(2,1);
	HLCD_voidDispStr("CCS:ON ");
	HLCD_voidMovCursor(1,1);	/* return the cursor back */
	//HLCD_voidSendCmd(0X01);
}
void CCS_OFF(void)
{
	PORTA &= ~(1<<CCS_LED);
	HLCD_voidMovCursor(2,1);
	HLCD_voidDispStr("CCS:OFF");
	HLCD_voidMovCursor(1,1);
	//HLCD_voidSendCmd(0X01);
}


/***********************************************************************************************/
/*******************************  KILOMETER COUNTER  *******************************************/
/***********************************************************************************************/

void KilometerCounter(u16 GasVal)
{
	static float kilos = 0;
	static float seconds = 0;

	HLCD_voidMovCursor(1,11);
	HLCD_voidDispStr("K=");
	HLCD_voidDispIntNum(kilos);
	HLCD_voidMovCursor(1,1);
	seconds = (float)CalcTimeforKilomCounter/OVF_COUNTS_FOR_1sec;
	if(G_u8_GRBox_rtrn == 1)	/* the car is moving */
	{
		kilos += ((GasVal*7.5)/1023)*(seconds); 	/* 90km/h = 7.5 km/5mins is the max speed
		 	 	 	 	 	 	 	 	 	 				(5-min time is our 1 sec ) */
	}

}

/***********************************************************************************************/
/********************************  BAS SYSTEM  *************************************************/
/***********************************************************************************************/
void Ultrasonic_Init(void)
{
	//cli(); /* Clear any interrupt until I allow for it */

	TCCR1A = 0;	/* NORMAL MODE */
	TCCR1B = 0; /* Reset it */
	TCNT1 = 0;	/* Reset it */
	TCCR1B |= (1<<CS10) | (1<<ICES1); 	/* PS 1 & Rising edge detect */
	TIMSK |= (1<<TOIE1) | (1<<TICIE1);	/* Enable OV1 INT & ICU1 */

	sei(); /* Set Global INterrupt */
}

void UltrasonicTriggerAndEcho(void)
{
	DDRD |= (1<<PD6);	/* TRIGGER PIN TO ULTRASONIC */
	PORTD |= (1<<PD6);
	_delay_us(10);
	PORTD &= ~(1<<PD6);

	DDRD &= ~(1<<PD6); /* ICP as input to get ECHO  */
}

void Ultrasonic_CalcDist(void)
{
	uint32_t TICKS;

	if(EdgeStatus == 2)
	{
		EdgeStatus = 0;

		/* Calculations */
		TICKS = CAP2 + OVF_CounterTimer1*65536 - CAP1;	/* Ticks count (Rising -> Falling */

		/* FOR ULTRASONIC */
		/*
		 * Time period = TICKS * (1/8MHz)
		 * Distance = Time period * 34300 / 2 = TICKS / 466.5
		 */
		G_Ultrasonic_Distance = (float)TICKS /466.5;
		//		HLCD_voidDispFloatNum(DistIOfInput,1);		/* value => 7.9 */
		//		_delay_ms(1000);

		/* Reset variables and bits */
		OVF_CounterTimer1 = 0; OVF_CounterTimer1_Copy = 0;
		TCCR1B |= (1<<ICES1); 				/* Detect Rising edge */
		TIFR |= (1<<TOV1) | (1<<ICF1); 		/* Clear the flags */
		TIMSK |= (1<<TOIE1)|(1<<TICIE1);	/* Enable Interrupts */
	}
}

ISR(TIMER1_OVF_vect)
{
	if(G_Reciv_A == 'A')
		OVF_CounterTimer1 ++;
}

ISR(TIMER1_CAPT_vect)
{
	if(G_Reciv_A == 'A')
	{
		if(EdgeStatus == 0)
		{
			CAP1 = ICR1;	/* RISING captured */

			OVF_CounterTimer1 = 0; /* @ Start of Pulse_input to count all next OVFs until the falling edge */
			TCCR1B &= ~(1<<ICES1); /* Now, Detect Falling edge */
			EdgeStatus = 1;

		}
		else if (EdgeStatus == 1)
		{
			CAP2 = ICR1;	/* FALLING captured */
			OVF_CounterTimer1_Copy = OVF_CounterTimer1;	/* OVFs between RISING and FALLING */

			/* Disable INTs for OVF1 & ICU1 until Calculations end*/
			TIMSK &= ~((1<<TOIE1)|(1<<TICIE1));
			EdgeStatus = 2;
		}


		Ultrasonic_CalcDist();

	}

}




void update_BAS_SystemON(void)
{
	G_Ultrasonic_Distance = 11;		/* COMMENT IT WHILE USING HW */
	/* AS ULTRASONIC HAVE A VALUE OF 7.9 DOESN'T CHANGE */
	/* SO IT TOGGLE ALL THE THIME STUCK IN WHILE(1) */

	HLCD_voidMovCursor(2,9);

	if (G_Ultrasonic_Distance > 10) {
		PORTA &= ~(1<<BAS_LED);
		HLCD_voidDispStr("BAS:OFF");
	}

	else if (G_Ultrasonic_Distance > 5)
	{
		while(G_Ultrasonic_Distance > 5)	/* This global changes in ISR of TIMER1_CAPT_vect */
		{
			HLCD_voidDispStr("BAS:TOG");
			PORTA  |= (1<<BAS_LED);
			_delay_ms(100);
			PORTA &= ~(1<<BAS_LED);
			HLCD_voidMovCursor(2,9);	/* return it */
		}

	}

	else {
		PORTA  |= (1<<BAS_LED);
		HLCD_voidDispStr("BAS: ON");
	}

}
void update_BAS_SystemOFF(void){
	HLCD_voidMovCursor(2,9);
	PORTA &= ~(1<<BAS_LED);
	HLCD_voidDispStr("BAS:OFF");
}

/***********************************************************************************************/
/********************************  DRIVE MONITORING SYSTEM  *************************************************/
/***********************************************************************************************/
ISR(TIMER2_OVF_vect)
{
	if (G_Reciv_A == 'A')
			BuzzerDriveMonitoring();
}

void BuzzerDriveMonitoring(void)
{

	CounterOVFsForBuzzer++ ;
	CalcTimeforKilomCounter++;
	if(CounterOVFsForBuzzer == OVF_COUNTS_FOR_5sec)
	{

		CounterOVFsForBuzzer = 0;
		BUZ_FLAG = 1;

	}
}

