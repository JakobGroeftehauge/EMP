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
#define OFF       0
#define STATE_95  1
#define STATE_92  2
#define STATE_E10 3

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
    float temp_92;
    float temp_95;
    float temp_E10;


    for(;;)
    {

    switch(state)
    {
    case OFF:

    if(Fuel_Type != 0)
    {

    if(Fuel_Type == Fuel_92)
    {
    state = STATE_92;
    temp_92 = Fuel_Price_92;
    }
    else if(Fuel_Type == Fuel_95)
    {
    state = STATE_95;
    temp_95 = Fuel_Price_95;
    }
    else if(Fuel_Type == Fuel_E10)
    {
    state = STATE_E10;
    temp_E10 = Fuel_Price_E10;
    }

    }

    break;

    case STATE_92:

    Current_Price = (Amount_Pumped/TICK_PER_LITER) * temp_92;

    if(Fuel_Type == 0)
    {
    state = OFF;
    Current_Price = 0;
    }
    break;

    case STATE_95:

    if(Fuel_Type == Fuel_95)
    {
    Current_Price = (Amount_Pumped/TICK_PER_LITER) * temp_95;
    }

    if(Fuel_Type == 0)
    {
    state = OFF;
    Current_Price = 0;
    }

    break;

    case STATE_E10:

    if(Fuel_Type == Fuel_E10)
    {
    Current_Price = (Amount_Pumped/TICK_PER_LITER) * temp_E10;
    }

    if(Fuel_Type == 0)
    {
    state = OFF;
    Current_Price = 0;
    }

    break;

    default:
    break;

    }


    }
}


/****************************** End Of Module *******************************/

