/*
 * Pb_int.h
 *
 *  Created on: May 18, 2022
 *      Author: Mohamed Ramadan
 */

#ifndef HAL_PUSH_BOTTON_PB_INT_H
#define HAL_PUSH_BOTTON_PB_INT_H

#include "Pb_private.h"
#include "Pb_conf.h"


/*
	Function Name        : HPushBotton_voidPbInt
	Function Returns     : void
	Function Arguments   : u8 A_u8PbID
	Function Description : Define the PushBotton as INTPUT
*/
void HPushBotton_voidPbInt (u8 A_u8PbID) ;


/*
	Function Name        : HPushBotton_u8PbStatus
	Function Returns     : u8
	Function Arguments   : u8 A_u8PbID
	Function Description : read the status of push button (Pressed / not pressed)
*/
u8 HPushBotton_u8PbStatus (u8 A_u8PbID) ;	/* NO USE FOR INTERRUPTS */

#endif /* HAL_PUSH_BOTTON_Pb_INT_H */
