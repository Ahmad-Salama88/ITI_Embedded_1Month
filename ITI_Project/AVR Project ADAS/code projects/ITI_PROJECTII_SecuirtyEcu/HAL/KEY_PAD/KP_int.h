/*
 * KP_int.h
 *
 *  Created on: May 18, 2022
 *      Author: Mohammed Ramadan
 */

#ifndef HAL_KEY_PAD_KP_INT_H
#define HAL_KEY_PAD_KP_INT_H

/*
	Function Name        : HKP_voidKpInt
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize the Rows & columns of keypad
*/
void HKP_voidKpInt (void) ;

/*
	Function Name        : HKP_u8GetPressedKey
	Function Returns     : u8
	Function Arguments   : void
	Function Description : read the value of pressed  key 
*/
u8 HKP_u8GetPressedKey (void) ;

#endif /* HAL_KEY_PAD_KP_INT_H */
