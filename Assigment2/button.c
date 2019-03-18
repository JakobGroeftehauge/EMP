/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: button.c
*
* PROJECT....: EMP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 090215  MoH   Module created.
* 190308  MA    Edited
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "events.h"
#include "button.h"
#include "swtimers.h"
/*****************************    Defines    *******************************/
#define BS_IDLE           0
#define BS_FIRST_PUSH     1
#define BS_FIRST_RELEASE  2
#define BS_SECOND_PUSH    3
#define BS_LONG_PUSH      4

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
uint8_t button_pushed()
{
  return( !(GPIO_PORTF_DATA_R & 0x10) );  // SW1 at PF4
}

uint8_t select_button(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
  static uint8_t  button_state = BS_IDLE;
  static uint16_t button_timer;
         uint8_t  button_event = GE_NO_EVENT;

  switch( button_state )
  {
    case BS_IDLE:
	    if( button_pushed( ))		// if button pushed
	    {
  	    button_state = BS_FIRST_PUSH;
		    button_timer = TIM_2_SEC;		// start timer = 2 sek;
      }
	    break;
    case BS_FIRST_PUSH:
	    if( ! --button_timer )			// if timeout
	    {
	      button_state = BS_LONG_PUSH;
		    button_event = BE_LONG_PUSH;
	    }
	    else
	    {
        if(  !button_pushed( ) )	// if button released
		    {
	        button_state = BS_FIRST_RELEASE;
		      button_timer = TIM_100_MSEC;	// start timer = 100 milli sek;
        }
	    }
	    break;
    case BS_FIRST_RELEASE:
	    if( ! --button_timer )			// if timeout
	    {
	      button_state = BS_IDLE;
		    button_event = BE_SINGLE_PUSH;
	    }
	    else
	    {
        if(  button_pushed(  ))		// if button pressed
		    {
	        button_state = BS_SECOND_PUSH;
		      button_timer = TIM_2_SEC;		// start timer = 2 sek;
        }
	    }
	    break;
    case BS_SECOND_PUSH:
	    if( ! --button_timer )			// if timeout
	    {
	      button_state = BS_LONG_PUSH;
		    button_event = BE_LONG_PUSH;
	    }
	    else
	    {
        if( ! button_pushed( ) )					// if button released
		    {
	        button_state = BS_IDLE;
		      button_event = BE_DOUBLE_PUSH;
        }
	    }
	    break;
    case BS_LONG_PUSH:
      if( ! button_pushed(  ) )					// if button released
	      button_state = BS_IDLE;
	    break;
    default:
      break;
  }
  return( button_event );
}

/****************************** End Of Module *******************************/











