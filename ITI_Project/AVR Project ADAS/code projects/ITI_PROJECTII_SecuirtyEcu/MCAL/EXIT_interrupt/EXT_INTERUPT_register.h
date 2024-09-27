/*
 * EXT_INTERUPT_register.h
 *
 *  Created on: Jun 2, 2022
 *      Author: Mohamed Ramadan
 */

#ifndef MCAL_EXT_INTERUPT_EXT_INTERUPT_REGISTER_H_
#define MCAL_EXT_INTERUPT_EXT_INTERUPT_REGISTER_H_

/**MCU control register*/
#define MCUCR  *((volatile u8 *)(0x55))

/**MCU control and status register*/
#define MCUCSR *((volatile u8 *)(0x54))

/**General interrupt control register*/
#define GICR   *((volatile u8 *)(0x5B))

/**General interrupt flag register*/
#define GIFR   *((volatile u8 *)(0x5A))

/**status register*/
#define SREG *((volatile u8 *)(0x5F))

#endif /*MCAL_EXT_INTERUPT_EXT_INTERUPT_REGISTER_H_*/