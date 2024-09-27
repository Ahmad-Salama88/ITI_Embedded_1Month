/*
 * LCD_prog.c
 *
 *  Created on: May 18, 2022
 *      Author: Mohammed Ramadan
 */
 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_int.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdlib.h>
#include "LCD_private.h"
#include "LCD_conf.h"
#include "LCD_int.h"

void HLCD_voidInit(void)
{
	/** Wait for more than 30ms after VDD rise to 4.5v */
	    _delay_ms (200) ;
		
	#if MODE == EIGHT_BIT_CONNECTION
	
	    /** set direction of PORT data to be output */
	    MDIO_voidSetPortDir (LCD_DATA_PORT , ALL_PINS_ONE) ;
		
		/** set direction of register select to be output */
	    MDIO_voidSetPinDir  (LCD_RS_PORT   , LCD_RS_PIN  , DIO_HIGH) ;
		
		/** set direction of Enable pin to be output */
	    MDIO_voidSetPinDir  (LCD_EN_PORT   , LCD_EN_PIN  , DIO_HIGH) ;

		/** set direction of read/write pin to be output */
	    MDIO_voidSetPinDir  (LCD_RW_PORT   , LCD_RW_PIN  , DIO_HIGH) ;
	    
	    /** function set */
	    HLCD_voidSendCmd (EIGHT_BIT_CONNECTION) ;
		
		/* Wait for command to settle */
	    _delay_ms (1) ;
	    
	    /** Display ON/OFF Control */
	    HLCD_voidSendCmd (CMD_CURSOR_On_DISPLAY_ON) ;
		
		/* Wait for command to settle */
	    _delay_ms (1) ;
	    
	    /** Display Clear */
	    HLCD_voidSendCmd (CMD_CLEAR) ;
		
		/* Wait for command to settle */
	    _delay_ms (10) ;
	    
	    /** Entry mode set */
	    HLCD_voidSendCmd (CMD_ENTRY_MODE) ;
		
		/* Wait for command to settle */
	    _delay_ms (1) ;
		
	#elif MODE == FOUR_BIT_CONNECTION
	
	    /** set direction of DIO_PIN4 to be output */
	    MDIO_voidSetPinDir  (LCD_DATA_PORT , DIO_PIN4 , DIO_HIGH) ;
		
		/** set direction of DIO_PIN5 to be output */
	    MDIO_voidSetPinDir  (LCD_DATA_PORT , DIO_PIN5 , DIO_HIGH) ;
		
		/** set direction of DIO_PIN6 to be output */
	    MDIO_voidSetPinDir  (LCD_DATA_PORT , DIO_PIN6 , DIO_HIGH) ;
		
		/** set direction of DIO_PIN7 to be output */
	    MDIO_voidSetPinDir  (LCD_DATA_PORT , DIO_PIN7 , DIO_HIGH) ;
		
	    /** set direction of register select to be output */
	    MDIO_voidSetPinDir  (LCD_RS_PORT   , LCD_RS_PIN  , DIO_HIGH) ;
		
		/** set direction of Enable pin to be output */
	    MDIO_voidSetPinDir  (LCD_EN_PORT   , LCD_EN_PIN  , DIO_HIGH) ;

		/** set direction of read/write pin to be output */
	    MDIO_voidSetPinDir  (LCD_RW_PORT   , LCD_RW_PIN  , DIO_HIGH) ;
	    
	    /** Return home*/
	    HLCD_voidSendCmd (CMD_RETURN_HOME) ;
		
		/* Wait for command to settle */
	    _delay_ms (10) ;
	    
	    /** function set */
	    HLCD_voidSendCmd (FOUR_BIT_CONNECTION) ;
		
		/* Wait for command to settle */
	    _delay_ms (1) ;
	    
	    /** Display ON/OFF Control */
	    HLCD_voidSendCmd (CMD_CURSOR_On_DISPLAY_ON) ;
		
		/* Wait for command to settle */
	    _delay_ms (1) ;
	    
	    /** Display Clear */
	    HLCD_voidSendCmd (CMD_CLEAR) ;
		
		/* Wait for command to settle */
	    _delay_ms (10) ;
	    
	    /** Entry mode set */
	    HLCD_voidSendCmd (CMD_ENTRY_MODE) ;
		
		/* Wait for command to settle */
	    _delay_ms (1) ;
	#else 
		#error "selecct right mode"
	#endif
}
void HLCD_voidSendData(u8 A_u8Char)
{
	#if MODE == EIGHT_BIT_CONNECTION
	    
		/**set read/write to low */
		MDIO_voidClrPinVal  (LCD_RW_PORT , LCD_RW_PIN ) ;
		
		/**send last four bits of data to last four bit at control register */
		MDIO_voidSetPortVal (LCD_DATA_PORT , A_u8Char) ;
		
		/**set register select to high */
		MDIO_voidSetPinVal  (LCD_RS_PORT , LCD_RS_PIN ) ;
		
		/**set enable to high */
		MDIO_voidSetPinVal  (LCD_EN_PORT , LCD_EN_PIN ) ;
		
		/* Wait for E to settle */
		_delay_ms (2) ;
		
		/**set enable to low */
		MDIO_voidClrPinVal  (LCD_EN_PORT , LCD_EN_PIN ) ;
		
		/* Wait for E to settle */
		_delay_ms (2) ;
	
	#elif MODE == FOUR_BIT_CONNECTION
	    /**set read/write to low */
	    MDIO_voidClrPinVal  (LCD_RW_PORT , LCD_RW_PIN ) ;
		
		/**send last four bits of data to last four bit at control register */
		MDIO_voidWriteHighNibble (LCD_DATA_PORT , A_u8Char >> FOUR_BITS) ;
		
		/**set register select to low */
		MDIO_voidSetPinVal  (LCD_RS_PORT , LCD_RS_PIN ) ;
		
		/**set enable to high */
		MDIO_voidSetPinVal  (LCD_EN_PORT , LCD_EN_PIN ) ;
		
		/* Wait for E to settle */
		_delay_ms (2) ;
		
		/**set enable to low */
		MDIO_voidClrPinVal  (LCD_EN_PORT , LCD_EN_PIN ) ;
		
		/* Wait for E to settle */
		_delay_ms (2) ;
		
		
		/**set read/write to low */
		MDIO_voidClrPinVal  (LCD_RW_PORT , LCD_RW_PIN ) ;
		
		/**send last four bits of data to last four bit at control register */
		MDIO_voidWriteHighNibble (LCD_DATA_PORT , A_u8Char) ;
		
		/**set register select to low */
		MDIO_voidSetPinVal  (LCD_RS_PORT , LCD_RS_PIN ) ;
		
		/**set enable to high */
		MDIO_voidSetPinVal  (LCD_EN_PORT , LCD_EN_PIN ) ;
		
		/* Wait for E to settle */
		_delay_ms (2) ;
		
		/**set enable to low */
		MDIO_voidClrPinVal  (LCD_EN_PORT , LCD_EN_PIN ) ;
		
		/* Wait for E to settle */
		_delay_ms (2) ;
	#else 
		 #error "select write mode"
	#endif
	_delay_ms(1) ;
}

void HLCD_voidDispStr(u8* A_Pu8String)
{
	/**Local loop index */
	u8 L_u8Index = 0 ;
	while (A_Pu8String [L_u8Index] != '\0')
	{
		/* Write Character on LCD */
		HLCD_voidSendData (A_Pu8String [L_u8Index]) ;
		
		/* Increment local loop index */
		L_u8Index ++ ;
	}
}

void HLCD_voidDispIntNum(u32 A_u32Number)
{
	if (A_u32Number < MIN_INT_NUM && A_u32Number > MAX_INT_NUM)
	{
		/**
		 * if the integer is more than MAX_INT_NUM or less than MIN_INT_NUM
		          **** "Overflow !!!!" will be displayed
		 */
		HLCD_voidClrScreen () ;
		HLCD_voidDispStr ("Overflow !!!!") ;
	}
	else
	{
		/**array to stored conversion character*/
	    s8* L_Ps8String [16] = {0} ;

		/** convert integer to string*/
	    ltoa (A_u32Number , (s8*)L_Ps8String , BASE) ;

		/**display number after convesion*/
	    HLCD_voidDispStr ((u8*)L_Ps8String) ;
	}
}

void HLCD_voidDispFloatNum(f32 A_f32Number , u8 A_u8AfterDigit)
{
	u16 L_u16AfterDigit = 1 ;
	u8  L_u8Iterator = 0 ;
	/** display integer part */
    HLCD_voidDispIntNum ((u32)A_f32Number) ;

	/** display dot */
	HLCD_voidSendData   (',') ;

	for (L_u8Iterator = 0 ; L_u8Iterator < A_u8AfterDigit ; L_u8Iterator ++)
	{
		L_u16AfterDigit = L_u16AfterDigit * BASE ;
	}

	/** display fraction part */
	HLCD_voidDispIntNum ((A_f32Number - (u32) A_f32Number) * L_u16AfterDigit) ;
}

void HLCD_voidMovCursor(u8 A_u8RowId, u8 A_u8ColId)
{
	/**local variable to stored DDRAM address*/
	u8 L_u8DDRAMAddress ;
	
	/**if the row and col are out of range 
	         *** Do nothing
	  */
	if (A_u8RowId >= MIN_NUM_OF_ROW && A_u8RowId <= MAX_NUM_OF_ROW &&
	A_u8ColId >= MIN_NUM_OF_COL && A_u8ColId <= MAX_NUM_OF_COL)
	{
		/**for first row*/
		if (A_u8RowId == LCD_ROW1)
		{
			L_u8DDRAMAddress = FIRST_ROW_ADDRESS + A_u8ColId - 1 ;
		}
		
		/**for second row*/
		else if (A_u8RowId == LCD_ROW2)
		{
			L_u8DDRAMAddress = SECOND_ROW_ADDRESS + A_u8ColId - 1 ;
		}
		
		/**set DDRAM address*/
		HLCD_voidSendCmd (L_u8DDRAMAddress) ;
	}
	else
	{
		/** DO Nothing */
	}
}

void HLCD_voidClrScreen (void)
{
	/**clear data and move cursor to first position*/
	HLCD_voidSendCmd (CMD_CLEAR) ;
}

void HLCD_voidShiftDisplayRight(void)
{
	/**shift display to right*/
	HLCD_voidSendCmd (SHIFT_DISPLAY_TO_RIGHT) ;
}

void HLCD_voidShiftDisplayLeft(void)
{
	/**shift display to left*/
	HLCD_voidSendCmd (SHIFT_DISPLAY_TO_LEFT) ;
}

void HLCD_voidDispSpecialChar(u8 * A_u8Array, u8 A_u8Block, u8 A_u8RowId, u8 A_u8ColId)
{
	/**iterator for for loop*/
	u8 L_u8Iterator ;
	
	/**set CGRAM address (001x xxxx) */
	HLCD_voidSendCmd ((A_u8Block * NUMBER_OF_BLOCKS_OF_CGRAM) + SET_CGRAM_ADDRESS) ;
	
	/** Send the array to be stored */
	for (L_u8Iterator =  FIRST_INDEX_OF_EACH_BLOCK ;
	     L_u8Iterator <= END_INDEX_OF_EACH_BLOCK   ;
		 L_u8Iterator ++ )
		 {
			 HLCD_voidSendData (A_u8Array [L_u8Iterator]) ;
		 }
    
	/* Move the cursor to required position */
	HLCD_voidMovCursor (A_u8RowId , A_u8ColId) ;
	
	/* Set the block to be displayed */
	HLCD_voidSendData (A_u8Block) ;
}
