/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: key.c
*
* PROJECT....: EMP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150321  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "system_setup.h"
#include "tmodel.h"

INT8U row( INT8U y )
{
  INT8U result = 0;

  switch( y )
  {
    case 0x01: result = 1; break;
    case 0x02: result = 2; break;
    case 0x04: result = 3; break;
    case 0x08: result = 4; break;
  }
  return( result );
}



INT8U key_catch( x, y )
INT8U x, y;
{
  const INT8U matrix[3][4] = {{'#','9','6','3'},
                              {'0','8','5','2'},
                              {'*','7','4','1'}};

  return( matrix[x-1][y-1] );

}

extern void key_task(void* pvParameters)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
  uint8_t my_state = 0;
  INT8U y;
  INT8U ch;
  INT8U x = 1;
  INT8U LCD_pos = 0;


  for(;;)
  {
      switch( my_state )
      {
        case 0:
          GPIO_PORTA_DATA_R |= 0x04; //Set X3 high
          my_state = 1;

          break;
        case 1:
          y = GPIO_PORTE_DATA_R & 0x0F; //Read Y1-Y4
          if( y ) // if any of them is set, meaning a btn is pressed
          {
            // depending on the button pressed, y can be either
            // 0x01, 0x02, 0x04, 0x08.
            // returns the character located at the X-pos scanned
            // and Y-pos caught
            ch = key_catch( x, row(y) );
            // after key is sent to queue, wait for no key
            // to be pressed
            xQueueSend(KEYBOARD_QUEUE_HANDLE,(void*)&ch,1);
            my_state = 2;
          }
          else //  move on to next column (X)
          {
            x++;
            if( x > 3 )
              x = 1;
            GPIO_PORTA_DATA_R &= 0xE3; //clear X1-X3
            GPIO_PORTA_DATA_R |= ( 0x01 << (x+1 ));
            y = GPIO_PORTA_DATA_R; // dont think this does anything
          }
          break;
        case 2:
          if( !(GPIO_PORTE_DATA_R & 0x0F )) // if no key is pressed
          {
            x=1; //reset x
            GPIO_PORTA_DATA_R |= 0x04; // set X3
            vTaskDelay(2);
            my_state = 1;
          }
          break;
      }
  }
}
