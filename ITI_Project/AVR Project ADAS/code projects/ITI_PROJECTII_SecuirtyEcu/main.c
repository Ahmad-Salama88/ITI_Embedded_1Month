

/* NOTE : delay is done by delay function not TIMER0
 * It should be something like this
 * for ex : THE RED LED :
 *
 * 		LED ON;
 * 		TIMER0_Init(); 	 // TAKE OFF (counting 700 ms)
 *		while(OVF_FLAG == 0); 	// waiting OVF
 *		LED OFF;
 *
 *	UPDATE : DELAY_FUNCTION USING TIMER0 is done.
 */


#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/DIO/DIO_int.h"
#include "MCAL/Timer/Timer_conf.h"
#include "MCAL/Timer/Timer_int.h"
#include "HAL/KEY_PAD/KP_conf.h"
#include "HAL/KEY_PAD/KP_int.h"
#include "HAL/LCD/LCD_conf.h"
#include "HAL/LCD/LCD_int.h"

#include "MCAL/TWI_EEPROM/TWI_EEPROM.h"
#include "MCAL/UART/UART.h"

#include <avr/io.h>
#include <util/delay.h>

#define PASSWORD "1234"	/* cancel it by 'Password' */
#define PASS_LEN	4
#define FAILLED_LED	4
#define PASS_LED 	3
#define TIMER0_OVF_COUNTS_700ms 2745

void TurnServo90(void);
void Timer0Init(void);


volatile extern char PASS[];
u16 TIMER0_OVF_COUNT = 0;

int main()
{
	u8 Password[] = PASSWORD;
	u8 PassInput[5];
	u8 Pass_count = 0;
	u8 Char_pressed;
	u8 Check_flag = 1; /* assume matching */

	TWI_INIT();
	HLCD_voidInit();
	HKP_voidKpInt();
	UART_INIT(MY_UBRR);	/* BAUD = 9600 */



	/* Write PASS on EEPROM -- should be written before (for real : HW) */
	/* TWI-EEPROM (Send data to EEPROM) */
	WRITE_EEPROM(0x00,PASSWORD);

	/* Get data written on EEPROM to MCU as Rx and ASSIGN it in array (PASS) */
	READ_EEPROM(0x00,PASS);

	while (1)
	{

		/* Using Keypad to get PASS_INPUT and assign it to another array */
		do {
			Char_pressed = HKP_u8GetPressedKey();
			if (Char_pressed != '=')
			{
				/* Get characters entered into PassInput */
				PassInput[Pass_count] =Char_pressed;
				HLCD_voidSendData(Char_pressed);
			}
			Pass_count++;
		}while(Char_pressed != '=');	/* YOU ! */
		Pass_count = 0; /* reset it to be PassInput[0] */

		HLCD_voidClrScreen();


		/* Check PASS_INPUT using for-loop -- if correct, give a flag some value */
		if (strlen(PassInput) > strlen(Password))	/* may be it's (1234 + ... ) */
			Check_flag = 0;			/* wrong Password */
		else {
			for(u8 count = 0; count<strlen(Password); count++)
			{
				if(PassInput[count]!=Password[count])
				{
					/* if any character mismatches, it's wrong */
					Check_flag = 0;
					break;
				}

			}
		}

		/* Reset INPUT array with 0s -- as may be it's 3533 + ... and other situations */
		while(PassInput[Pass_count] != '\0')
		{
			PassInput[Pass_count] = '\0';
			Pass_count++;
		}
		Pass_count = 0;		/* reset it for next enter PassInput[0] */




		/* if doesn't match : red lamp for 700 ms using TIMER0_OVF */
		if(Check_flag == 0)
		{
			Check_flag = 1; /* reset it*/
			DDRC |= (1<<FAILLED_LED);
			PORTC |= (1<<FAILLED_LED);

			/* TIMER0 starts counting */
			Timer0Init();

			while(TIMER0_OVF_COUNT < TIMER0_OVF_COUNTS_700ms);
			TIMER0_OVF_COUNT = 0; 	// RESET
			//_delay_ms(700);
			PORTC &= ~(1<<FAILLED_LED);
		}
		else if(Check_flag == 1)
		{
			/* blink green led */

			DDRC |= (1<<PASS_LED);
			PORTC |= (1<<PASS_LED);

			/* TIMER0 starts counting */
			Timer0Init();

			while(TIMER0_OVF_COUNT < TIMER0_OVF_COUNTS_700ms);	/* wait for 700 */
			TIMER0_OVF_COUNT = 0; 	// RESET
											//_delay_ms(700);
			PORTC &= ~(1<<PASS_LED);


			/* Turn the servo */
			TurnServo90();


			/* Send 'A' via UART */
			UART_TRANSMIT('A');


			HLCD_voidDispStr("    -- OPEN --    ");
			_delay_ms(1500);
			HLCD_voidClrScreen();

		}






	}


	return 0;
}

void TurnServo90(void)
{
	/* TO GET HOW IT WORKS, THE NOTEBOOK OF ITI_EMBEDDED_MONTH => ARAFA_MICROYS */

	/* Select Mode 14 */
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13);
	/* Set prescaler 8  */
	TCCR1B |= (1<<CS11);
	/* Clear on COM for Fast PWM */
	TCCR1A |= (1<<COM1B1); 	// COM1B0 = 0

	/* from page 99 :
	 * I need to get f_req = 50 Hz
	 * N*(1+TOP) = f_clk / f_req
	 * We set N = 8 .. then, TOP = (8MHz / (50*8)) - 1
	 * then TOP =  19999 which is less than 65536 (so we can handle it)
	 *
	 */
	ICR1 = 19999; /* TOP VALUE OF TIMER1 => f_OCM = 50 Hz */
	TCNT1 = 0;
	DDRD |= (1<<PD4);

	/* f_timer = f_clk/8 --> 1 us for 1 tick
	 * 1.5ms -> 0 deg 	 --> 1.5ms /1us = 1500 ticks
	 * 1ms -> -90 deg	 --> 1000 ticks
	 * 2ms -> +90 deg	 --> 2000 ticks
	 */
	OCR1B = 2000;
	_delay_ms(1000);
	OCR1B = 1500;

}


void Timer0Init(void)
{
	TCNT0 = 0;
	TIMER0_OVF_COUNT = 0;
	/* Set Prescaler 8 */
	TCCR0 |= (1<<CS01);
	/* Default : NORMAL MODE */

	/* Enable the INT for TIMER0_OVF */
	TIMSK |= (1<<TOIE0);

	/* Enable Global INT */
			sei();
}

ISR(TIMER0_OVF_vect)
{

	TIMER0_OVF_COUNT++;
}








