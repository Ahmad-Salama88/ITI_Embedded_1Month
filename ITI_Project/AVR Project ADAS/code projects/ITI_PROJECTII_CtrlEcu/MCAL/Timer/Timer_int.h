/*
 * Timer_int.h
 *
 *  Created on: Jun 2, 2022
 *      Author: Mohamed Ramadan
 */
 
#ifndef MCAL_TIMER_TIMER_INT_H_
#define MCAL_TIMER_TIMER_INT_H_

/*
	Function Name        : MTimer_voidInt
	Function Returns     : void
	Function Arguments   : void
	Function Description : intialize Timer
*/
void MTimer_voidInt (void) ;

/*
	Function Name        : MTimer_voidSetDisiredTime
	Function Returns     : void
	Function Arguments   : u8 A_u8TimerID , f32 A_f32DisiredTime , void (*A_fptr)(void) 
	Function Description : take action after Disired Time selected
*/
void MTimer_voidSetDisiredTime (u8 A_u8TimerID , f32 A_f32DisiredTime , void (*A_fptr)(void) ) ;

/*
	Function Name        : MTimer_voidCtcCallBack
	Function Returns     : void
	Function Arguments   : u8  A_u8TimerID , void (*A_fptr1)(void) , void (*A_fptr2)(void) 
	Function Description : set call back of CTC
*/
void MTimer_voidCtcCallBack (u8  A_u8TimerID , void (*A_fptr1)(void) , void (*A_fptr2)(void)) ;

/*
	Function Name        : MTimer_voidSetPWM
	Function Returns     : void
	Function Arguments   : u8  A_u8TimerID , u16 A_u16CompareValueA , u16 A_u16CompareValueB
	Function Description : set pwm 
*/
void MTimer_voidSetPWM (u8  A_u8TimerID , u16 A_u16CompareValueA , u16 A_u16CompareValueB) ;

/*
	Function Name        : MTimerCalcFreqofTtotal
	Function Returns     : u32
	Function Arguments   : void
	Function Description : calc frequancy of input signal 
*/
u32 MTimerCalcFreqofTtotal (void) ;

/*
	Function Name        : MTimerCalcFreqofTtotal
	Function Returns     : f32
	Function Arguments   : void
	Function Description : calc Duty cycle of input signal 
*/
f32 MTimerCalcDutyCycle (void) ;

/*
	Function Name        : MTimerCalcFreqofTtotal
	Function Returns     : u32
	Function Arguments   : void
	Function Description : calc frequancy of high level (Ton) of input signal 
*/
u32 MTimerCalcFreqofTon (void) ;

#endif /*MCAL_TIMER_TIMER_INT_H_*/