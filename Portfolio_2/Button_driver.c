/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: Button_driver.c
*
* PROJECT....: Portfolio 2
*
* DESCRIPTION:
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190504  JGR    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "system_setup.h"
#include "tm4c123gh6pm.h"
/*****************************    Defines    *******************************/

#define OFF 0
#define ON  1
/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/

uint8_t sw1_pressed()
{
    return( !(GPIO_PORTF_DATA_R & 0x10) );
}

uint8_t sw2_pressed()
{
    return( !(GPIO_PORTF_DATA_R & 0x01) );
}

void button_driver_task(void* pvParameters)
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/
{
    uint8_t sw2_state = OFF;

    for(;;)
    {

    if(sw1_pressed())
    {
    Handle_Activated = TRUE;
    }
    else
    {
    Handle_Activated = FALSE;
    }

    switch(sw2_state)
    {

    case OFF:

        Hook_Activated = FALSE;

        if(sw2_pressed())
        {
            sw2_state = ON;
        }
    case ON:

        Hook_Activated = TRUE;

        if(sw2_pressed())
        {
            sw2_state = OFF;
        }
    }

    vTaskDelay(pdMS_TO_TICKS(5));

    }


}



/****************************** End Of Module *******************************/
