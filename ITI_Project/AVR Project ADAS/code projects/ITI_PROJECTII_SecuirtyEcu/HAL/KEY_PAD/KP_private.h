/*
 * KP_private.h
 *
 *  Created on: May 18, 2022
 *      Author: Mohamed Ramadan
 */

#ifndef HAL_KEY_PAD_KP_PRIVATE_H
#define HAL_KEY_PAD_KP_PRIVATE_H

#include "KP_conf.h"

/**
 *Define Size of Rows & Columns
 */
#define ROW_SIZE    4
#define COL_SIZE    4

#define NOT_PRESSED              255
#define PRESSED                  0
#define DELAY_FOR_DRBOUNCING     20 

static const u8 G_u8SwitchVal[ROW_SIZE][COL_SIZE] =
{
	{
		'7', /* Row 0 Column 0 */
		'4', /* Row 1 Column 0 */
		'1', /* Row 2 Column 0 */
		'D'  /* Row 3 Column 0 */
	},
	{
		'8', /* Row 0 Column 1 */
		'5', /* Row 1 Column 1 */
		'2', /* Row 2 Column 1 */
		'0'  /* Row 4 Column 1 */
	},
	{
		'9', /* Row 0 Column 2 */
		'6', /* Row 1 Column 2 */
		'3', /* Row 2 Column 2 */
		'='  /* Row 3 Column 2 */
	},
	{
		'/', /* Row 0 Column 3 */
		'*', /* Row 1 Column 3 */
		'-', /* Row 2 Column 3 */
		'+'  /* Row 3 Column 3 */
	}
};
#endif /* HAL_KEY_PAD_KP_PRIVATE_H */
