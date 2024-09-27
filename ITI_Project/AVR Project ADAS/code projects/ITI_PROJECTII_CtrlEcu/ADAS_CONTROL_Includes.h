/*
 * ADAS_CONTROL_Includes.h
 *
 *  Created on: ???/???/????
 *      Author: Ahmad Azab
 */

#ifndef ADAS_CONTROL_INCLUDES_H_
#define ADAS_CONTROL_INCLUDES_H_


#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/DIO/DIO_int.h"
#include "MCAL/Timer/Timer_conf.h"
#include "MCAL/Timer/Timer_int.h"
#include "HAL/LCD/LCD_conf.h"
#include "HAL/LCD/LCD_int.h"
#include "HAL/Push_button/Pb_conf.h"
#include "HAL/Push_button/Pb_int.h"
#include "MCAL/EXIT_interrupt/EXT_INTERUPT_conf.h"
#include "MCAL/EXIT_interrupt/EXT_INTERUPT_int.h"
#include "MCAL/ADC/ADC_conf.h"
#include "MCAL/ADC/ADC_int.h"

#include "MCAL/UART/UART.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SL_LED  PIN4
#define CCS_LED PIN5
#define BUZ_PIN PIN6
#define BAS_LED	PIN3

#define OVF_COUNTS_FOR_5sec	 153  /* f_clk = 8MHz & PS = 1024 */
#define OVF_COUNTS_FOR_1sec  30		/* used for kilometer counter */
#define TICK_TIME (1/F_CPU)
#define SOUND_SPEED 34300	/* cm/s */




#endif /* ADAS_CONTROL_INCLUDES_H_ */
