/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: leds.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

#ifndef _LCD_H
  #define _LCD_H

/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/
// Special ASCII characters
// ------------------------

#define LF		0x0A
#define FF		0x0C
#define CR		0x0D

#define ESC		0x1B


// Buffer size
#define COL_SIZE				16
#define ROW_SIZE				2


/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

INT8U wr_ch_LCD( INT8U );
void  wr_str_LCD( INT8U* );
void  move_LCD( INT8U, INT8U );
void clear_LCD();
void vLCD_task( void *pvParameters );

void lcd_task( INT8U );
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/


/****************************** End Of Module *******************************/
#endif

