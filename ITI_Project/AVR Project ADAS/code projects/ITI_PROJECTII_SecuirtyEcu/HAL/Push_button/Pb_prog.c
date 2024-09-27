/*
 * Pb_prog.h
 *
 *  Created on: May 18, 2022
 *      Author: Mohamed Ramadan
 */
 
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "Pb_int.h"
#include "Pb_private.h"
#include "Pb_conf.h"
#include <util/delay.h>


void HPushBotton_voidPbInt (u8 A_u8PbID)
{
	switch (A_u8PbID)
	{                  /** make direction of Pb1 is input */
		case Pb1_ID :  MDIO_voidSetPinDir     (Pb1_PORT , Pb1_PIN , Pb_INPUT) ;
		
		               /**active pull up of Pb1 */
		               MDIO_voidConnectPullup (Pb1_PORT , Pb1_PIN , ENABLE_PULLUP) ;
					   break ;
					   
					   /** make direction of Pb2 is input */
		case Pb2_ID :  MDIO_voidSetPinDir     (Pb2_PORT , Pb2_PIN , Pb_INPUT) ;
		 
		               /**active pull up of Pb2 */
		               MDIO_voidConnectPullup (Pb2_PORT , Pb2_PIN , ENABLE_PULLUP) ;
					   break ;
					   
					   /** make direction of Pb3 is input */
		case Pb3_ID :  MDIO_voidSetPinDir     (Pb3_PORT , Pb3_PIN , Pb_INPUT) ;
		      
			           /**active pull up of Pb3 */
		               MDIO_voidConnectPullup (Pb3_PORT , Pb3_PIN , ENABLE_PULLUP) ;
					   break ;
		default     :  /** Error */
		               break ;
	}
}

u8 HPushBotton_u8PbStatus (u8 A_u8PbID)
{
	u8 L_u8PbStatus = NOT_PRESSED ;
	switch (A_u8PbID)
	{                  /**check Pb1 is pressed or not*/
		case Pb1_ID :  if (MDIO_u8GetPinVal (Pb1_PORT , Pb1_PIN) == PRESSED)
		                {
							/**delay 20ms to detect bouncing*/
		                	_delay_ms (DELAY_FOR_DEPOUNCING) ;
							
							/**check Pb1 is still pressed or not after debouncing*/
							if (MDIO_u8GetPinVal (Pb1_PORT , Pb1_PIN) == PRESSED)
							{
								L_u8PbStatus = PRESSED ;
							}
		                }
					   break ;
					   
					   /**check Pb2 is pressed or not*/
		case Pb2_ID :  if (MDIO_u8GetPinVal (Pb2_PORT , Pb2_PIN) == PRESSED)
		                {
							/**delay 20ms to detect bouncing*/
		                	_delay_ms (DELAY_FOR_DEPOUNCING) ;
							
							/**check Pb2 is still pressed or not after debouncing*/
							if (MDIO_u8GetPinVal (Pb2_PORT , Pb2_PIN) == PRESSED)
							{
								L_u8PbStatus = PRESSED ;
							}
		                }
					   break ;
					   
					   /**check Pb3 is pressed or not*/
		case Pb3_ID :  if (MDIO_u8GetPinVal (Pb3_PORT , Pb3_PIN) == PRESSED)
		                {
							/**delay 20ms to detect bouncing*/
		                	_delay_ms (DELAY_FOR_DEPOUNCING) ;
							
							/**check Pb3 is still pressed or not after debouncing*/
							if (MDIO_u8GetPinVal (Pb3_PORT , Pb3_PIN) == PRESSED)
							{
								L_u8PbStatus = PRESSED ;
							}
		                }
					   break ;
		default     :  /** Error */
		               break ;
	}
	/**delay 20ms to detect bouncing*/
	_delay_ms (DELAY_FOR_DEPOUNCING) ;
	return L_u8PbStatus ;
}
