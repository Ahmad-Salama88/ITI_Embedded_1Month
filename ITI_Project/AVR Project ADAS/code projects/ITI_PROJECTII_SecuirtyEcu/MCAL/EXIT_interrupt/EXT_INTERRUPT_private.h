/*
 * EXT_INTERUPT_private.h
 *
 *  Created on: Jun 2, 2022
 *      Author: Mohamed Ramadan
 */

#ifndef MCAL_EXT_INTERUPT_EXT_INTERUPT_PRIVATE_H_
#define MCAL_EXT_INTERUPT_EXT_INTERUPT_PRIVATE_H_

/**MCU control register*/
#define ISC00  0
#define ISC01  1
#define ISC10  2
#define ISC11  3

/**MCU control and status register*/
#define ISC2   6

/**General interrupt control register*/
#define INT0   6
#define INT1   7
#define INT2   5

/**General interrupt flag register*/
#define INTF0  6
#define INTF1  7
#define INTF2  5

/**status register*/
#define I_BIT  7 

#define Null  0

#endif /*MCAL_EXT_INTERUPT_EXT_INTERUPT_PRIVATE_H_*/
