/*
 * EXT_INTERUPT_private.h
 *
 *  Created on: Jun 2, 2022
 *      Author: Mohamed Ramadan
 */

#ifndef MCAL_EXT_INTERUPT_EXT_INTERUPT_INT_H_
#define MCAL_EXT_INTERUPT_EXT_INTERUPT_INT_H_

#define LOW_LEVEL			1   /* low level                   */
#define ON_CHANGE		    2   /* rising edge or falling edge */
#define FALLING_EDGE		3   /* falling edge                */
#define RISING_EDGE 		4   /* rising edge                 */
									 						  
#define ENABLE              1   /* Enable External interrupt   */
#define DISABLE             2   /* Disable External interrupt  */

/**
	Function Name        : MEXTI_voidInit
	Function Returns     : void
	Function Arguments   : void
	Function Description : initialize External interrupts that be enabled
*/
void MINT_voidInit (void) ;

void MINT0_voidSetCallback_Three( void (*A_fptr1)(void), void (*A_fptr2)(void), void (*A_fptr3)(void)  );

/*
	Function Name        : MINT0_voidSetCallback
	Function Returns     : void
	Function Arguments   : pointer to function  void (*A_fptr)(void)
	Function Description : set INT0 callback to call ISR
*/
void MINT0_voidSetCallback( void (*A_fptr)(void)  );

/*
	Function Name        : MINT1_voidSetCallback
	Function Returns     : void
	Function Arguments   : pointer to function  void (*A_fptr)(void)
	Function Description : set INT1 callback to call ISR
*/
void MINT1_voidSetCallback( void (*A_fptr)(void)  );

/*
	Function Name        : MINT2_voidSetCallback
	Function Returns     : void
	Function Arguments   : pointer to function  void (*A_fptr)(void)
	Function Description : set INT2 callback to call ISR
*/
void MINT2_voidSetCallback( void (*A_fptr)(void)  );

#endif /*MCAL_EXT_INTERUPT_EXT_INTERUPT_INT_H_*/

