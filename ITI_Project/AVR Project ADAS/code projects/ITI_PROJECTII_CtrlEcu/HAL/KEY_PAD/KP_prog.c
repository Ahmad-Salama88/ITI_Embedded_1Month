/*
 * KP_prog.c
 *
 *  Created on: May 18, 2022
 *      Author: Mohammed Ramadan
 */
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "KP_conf.h"
#include "KP_private.h"
#include "KP_int.h"
#define F_CPU 8000000UL
#include <util/delay.h>

void HKP_voidKpInt (void) 
{
	/* Set Columns as Output & High */
#if   COL_START == DIO_PIN0 && ROW_START == DIO_PIN4
	/** first four pins of port are output
	          second four pins of port are input */   
	MDIO_voidSetPortDir (KP_PORT , LOW_NIBBLE_OUTPUT) ;

#elif COL_START == DIO_PIN4 && ROW_START == DIO_PIN0
	/** first four pins of port are input
	          second four pins of port are output */
	MDIO_voidSetPortDir (KP_PORT , HIGH_NIBBLE_OUTPUT) ;

#else
#error "Select right connections of Column start and Row start"
#endif

	/** Set Rows as Inputs & Pulled up */
#if   COL_START == DIO_PIN0 && ROW_START == DIO_PIN4
	/** first four pins of port are output
	          second four pins of port are input */
	MDIO_voidSetPortDir (KP_PORT , LOW_NIBBLE_OUTPUT) ;

	/** first four pins of port are high
	          and  active internal pull-up for second four pins of port */
	MDIO_voidSetPortVal (KP_PORT , ALL_PINS_ONE) ;

#elif ROW_START == DIO_PIN0 && COL_START == DIO_PIN4
	/** first four pins of port are input
	          second four pins of port are output */
	MDIO_voidSetPortDir (KP_PORT , HIGH_NIBBLE_OUTPUT) ;

	/** active internal pullup for first four pins of port
		      and first four pins of port are high */
	MDIO_voidSetPortVal (KP_PORT , ALL_PINS_ONE) ;
#else
#error "Select right connections of Column start and Row start"
#endif
}

u8 HKP_u8GetPressedKey (void)
{
	u8 L_u8Column ;
	u8 L_u8Row    ;
	u8 L_u8PinVal ;
	u8 L_GetAnyPressed = 0; 			// NEW FOR CALCULATOR -- stuck until you get a press
	u8 L_u8PressedKey = NOT_PRESSED;	// the pressed value

	while(!L_GetAnyPressed)		// NEW FOR CALCULATOR -- stuck until you get a press
	{
		/**external loop to active current column that be checked */
		for (L_u8Column = COL_START ; L_u8Column <= COL_END ; L_u8Column ++)
		{
			/**active current column by make it output low */
			MDIO_voidClrPinVal (KP_PORT , L_u8Column) ;

			/**internal loop to loop to each row
    			   and check pressed key that common current row and current column */
			for (L_u8Row = ROW_START ; L_u8Row <= ROW_END ; L_u8Row ++)
			{

				/** read value of key that common current row and current column */
				L_u8PinVal = MDIO_u8GetPinVal (KP_PORT , L_u8Row) ;

				/** if key is pressed ====> (MDIO_u8GetPinVal == 0) */
				if (L_u8PinVal == PRESSED)
				{
					L_GetAnyPressed = 1; 	// NEW FOR CALCULATOR

					/**get the value of the pressed key*/
					L_u8PressedKey = G_u8SwitchVal [L_u8Column - COL_START][L_u8Row - ROW_START] ;

					/**wait until leave the button */
					/* this While to return the last pressed button
					 *  (may be other is pressed while first pressing) */
					while (MDIO_u8GetPinVal (KP_PORT , L_u8Row) == PRESSED) ;

					/** wait 20 ms for debouncing */
					_delay_ms (DELAY_FOR_DRBOUNCING) ;
				}
			}

			/**deactivate current column by make it output low */
			MDIO_voidSetPinVal (KP_PORT , L_u8Column) ;
		}
	}
	return L_u8PressedKey ;
}


