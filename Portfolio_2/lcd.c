/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: leds.c
*
* PROJECT....: ECP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "emp_type.h"
#include "lcd.h"
#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
//#include "glob_def.h"
//#include "tmodel.h"

/*****************************    Defines    *******************************/

#define QUEUE_LEN   128

enum LCD_states
{
  LCD_POWER_UP,
  LCD_INIT,
  LCD_READY,
  LCD_SET_CURSOR
};

/*****************************   Constants   *******************************/
const INT8U LCD_init_sequense[]= 
{
  0x30,		// Reset
  0x30,		// Reset
  0x30,		// Reset
  0x20,		// Set 4bit interface
  0x28,		// 2 lines Display
  0x0C,		// Display ON, Cursor OFF, Blink OFF
  0x06,		// Cursor Increment
  0x01,		// Clear Display
  0x02,     // Home
  0xFF		// stop
}; 

/*****************************   Variables   *******************************/
INT8U display_buffer[COL_SIZE][ROW_SIZE];
INT8U col_pointer = 0;
INT8U row_pointer = 0;
INT8U cursor_x = 0;
INT8U cursor_y = 0;

INT8U testBuf;

enum LCD_states LCD_state = LCD_POWER_UP;
INT8U LCD_init;
INT8U LCD_timer = 3; 		// Wait for 30 mS after power up



/*****************************   Functions   *******************************/
INT8U wr_ch_LCD( INT8U ch )
/*****************************************************************************
*   OBSERVE  : LCD_PROC NEEDS 20 mS TO PRINT OUT ONE CHARACTER 
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  if( cursor_x < COL_SIZE )
  {
	display_buffer[cursor_x][cursor_y] = ch;
    cursor_x++;
  }
  return( 1 );
}

void wr_str_LCD( INT8U *pStr )
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  while( *pStr )
  {
    wr_ch_LCD( *pStr );
	pStr++;
  }
}

void move_LCD( INT8U x, INT8U y )
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  INT8U Pos;

  if( x < COL_SIZE )
	cursor_x = x;
  if( y < ROW_SIZE )
	cursor_y = y;
}

void clear_LCD()
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  INT8U x,y;

  for( y = 0; y < ROW_SIZE; y++ )
	for( x = 0; x < COL_SIZE; x++ )
	  display_buffer[x][y] = ' ';
}
//----------------------------

void wr_ctrl_LCD_low( INT8U Ch )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Write low part of control data to LCD.
******************************************************************************/
{
    INT8U temp;
    volatile int i;

    temp = GPIO_PORTC_DATA_R & 0x0F;
    temp  = temp | ((Ch & 0x0F) << 4);
    GPIO_PORTC_DATA_R  = temp;
    for( i=0; i<1000; i )
        i++;
    GPIO_PORTD_DATA_R &= 0xFB;        // Select Control mode, write
    for( i=0; i<1000; i )
        i++;
    GPIO_PORTD_DATA_R |= 0x08;        // Set E High

    for( i=0; i<1000; i )
        i++;

    GPIO_PORTD_DATA_R &= 0xF7;        // Set E Low

    for( i=0; i<1000; i )
        i++;

//  INT8U temp;
//
//  temp = GPIO_PORTB_DATA_R & 0xC2;
//  temp  = temp | ((Ch & 0x0F) << 2);
//  GPIO_PORTB_DATA_R  = temp;
//  GPIO_PORTA_DATA_R &= 0x3F;        // Select Control mode, write
//  GPIO_PORTB_DATA_R |= 0x40;		// Set E High
//  GPIO_PORTB_DATA_R &= 0xBF;		// Set E Low
}

void wr_ctrl_LCD_high( INT8U Ch )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Write high part of control data to LCD.
******************************************************************************/
{
  wr_ctrl_LCD_low(( Ch & 0xF0 ) >> 4 );
}

void out_LCD_low( INT8U Ch )
/*****************************************************************************
*   Input    : Mask
*   Output   : -
*   Function : Send low part of character to LCD. 
*              This function works only in 4 bit data mode.
******************************************************************************/
{
    INT8U temp;

    temp = GPIO_PORTC_DATA_R & 0x0F;
    GPIO_PORTC_DATA_R  = temp | ((Ch & 0x0F) << 4);
    //GPIO_PORTD_DATA_R &= 0x7F;        // Select write
    GPIO_PORTD_DATA_R |= 0x04;        // Select data mode
    GPIO_PORTD_DATA_R |= 0x08;        // Set E High
    GPIO_PORTD_DATA_R &= 0xF7;        // Set E Low

//  INT8U temp;
//
//  temp = GPIO_PORTB_DATA_R & 0xC2;
//  GPIO_PORTB_DATA_R  = temp | ((Ch & 0x0F) << 2);
//  GPIO_PORTA_DATA_R &= 0xBF;        // Select Control mode, write
//  GPIO_PORTA_DATA_R |= 0x80;        // Select data mode, write
//  GPIO_PORTB_DATA_R |= 0x40;		// Set E High
//  GPIO_PORTB_DATA_R &= 0xBF;		// Set E Low
}

void out_LCD_high( INT8U Ch )
/*****************************************************************************
*   Input    : Mask
*   Output   : -
*   Function : Send high part of character to LCD. 
*              This function works only in 4 bit data mode.
******************************************************************************/
{
  out_LCD_low((Ch & 0xF0) >> 4);
}

void wr_ctrl_LCD( INT8U Ch )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Write control data to LCD.
******************************************************************************/
{
  static INT8U Mode4bit = 0;
  INT16U i;

  wr_ctrl_LCD_high( Ch );
  if( Mode4bit )
  {
	for(i=0; i<1000; i++);
	wr_ctrl_LCD_low( Ch );
  }
  else
  {
	if( (Ch & 0x30) == 0x20 )
	  Mode4bit = 1;
  }
}

void clr_LCD()
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Clear LCD.
******************************************************************************/
{
  wr_ctrl_LCD( 0x01 );
}


void home_LCD()
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Return cursor to the home position.
******************************************************************************/
{
  wr_ctrl_LCD( 0x02 );
}

void set_cursor( INT8U col, INT8U row )
/*****************************************************************************
*   Input    : New Cursor position
*   Output   : -
*   Function : Place cursor at given position.
******************************************************************************/
{
  wr_ctrl_LCD(  0x80 + row*0x40 + col );
}


void out_LCD( INT8U Ch )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Write control data to LCD.
******************************************************************************/
{
  INT16U i;

  out_LCD_high( Ch );
  for(i=0; i<1000; i++);
  out_LCD_low( Ch );
}

void vLCD_task( void *pvParameters )
    {
    INT8U i;
    for(i=0;i<16;i++)
    {
        display_buffer[i][1]= 65+i;
    }
        INT8U LCD_task_state = LCD_POWER_UP;
        for( ;; )
        {
            switch( LCD_task_state )
             {
               case LCD_POWER_UP:
                 LCD_init = 0;
                 LCD_task_state = LCD_INIT;
                 vTaskDelay(50);
                 break;


               case LCD_INIT:
                  if( LCD_init_sequense[LCD_init] != 0xFF )
                    wr_ctrl_LCD( LCD_init_sequense[LCD_init++] );
                  else
                  {
                    LCD_task_state = LCD_READY;
                    home_LCD();
                    clear_LCD();
                    col_pointer = 0;
                    row_pointer = 0;

                    move_LCD( 4, 0 );
                    wr_ch_LCD( (INT8U)('i') );
                    wr_ch_LCD( (INT8U)('j') );
                  }
                  vTaskDelay(20);
                  break;

               case LCD_READY:
                   testBuf = display_buffer[col_pointer][row_pointer];
                   out_LCD( testBuf );
                   //out_LCD( 'k' );
                   vTaskDelay(1);
                   col_pointer++;
                   if( col_pointer >= COL_SIZE )
                   {
                     col_pointer = 0;
                     row_pointer++;
                     if( row_pointer >= ROW_SIZE )
                       row_pointer = 0;
                     LCD_task_state = LCD_SET_CURSOR;
                   }
                   break;
                 case LCD_SET_CURSOR:
                   set_cursor( col_pointer, row_pointer );
                   LCD_task_state = LCD_READY;
                   break;
                 default:
                   LCD_task_state = LCD_READY;
                   break;
             }
        }

        /* Tasks must not attempt to return from their implementing
        function or otherwise exit.  In newer FreeRTOS port
        attempting to do so will result in an configASSERT() being
        called if it is defined.  If it is necessary for a task to
        exit then have the task call vTaskDelete( NULL ) to ensure
        its exit is clean. */
        vTaskDelete( NULL );
    }


//
//void lcd_task( task_no )
//INT8U task_no;
///*****************************************************************************
//*   Input    :
//*   Output   :
//*   Function :
//******************************************************************************/
//{
//	  INT8U Ch;
//
//	  switch( LCD_state )
//	  {
//	    case LCD_POWER_UP:
//	      if( ! --LCD_timer )
//	      {
//	        LCD_init = 0;
//	        LCD_state = LCD_INIT;
//	      }
//	      break;
//	    case LCD_INIT:
//	      if( LCD_init_sequense[LCD_init] != 0xFF )
//		    wr_ctrl_LCD( LCD_init_sequense[LCD_init++] );
//	      else
//	      {
//		    LCD_state = LCD_READY;
//		    home_LCD();
//		    clear_LCD();
//		    col_pointer = 0;
//		    row_pointer = 0;
//	      }
//	      break;
//	    case LCD_READY:
//          out_LCD( display_buffer[col_pointer][row_pointer] );
//          col_pointer++;
//          if( col_pointer >= COL_SIZE )
//          {
//        	col_pointer = 0;
//        	row_pointer++;
//        	if( row_pointer >= ROW_SIZE )
//        	  row_pointer = 0;
//		    LCD_state = LCD_SET_CURSOR;
//          }
//		  break;
//	    case LCD_SET_CURSOR:
//   	      set_cursor( col_pointer, row_pointer );
//		  LCD_state = LCD_READY;
//          break;
//	    default:
//		  LCD_state = LCD_READY;
//
//	  }
//}


/****************************** End Of Module *******************************/




