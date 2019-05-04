/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: price_calculator.c
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

void price_calulator_task(void* pvParameters)
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/
{
    uint8_t state = OFF;

    for(;;)
    {

    switch(state)
    {
    case OFF:

    break;

    case ON:
    break;

    default:
    break;


    }


    }
}


/****************************** End Of Module *******************************/

