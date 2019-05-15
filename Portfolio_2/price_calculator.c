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
#define ON        1


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
    float temp_fuel_price = 0;


    for(;;)
    {

    switch(state)
    {
    case OFF:

    if(Fuel_Type != 0)
    {

    if(Fuel_Type == Fuel_92)
    {
    temp_fuel_price = Fuel_Price_92;
    }
    else if(Fuel_Type == Fuel_95)
    {
    temp_fuel_price = Fuel_Price_95;
    }
    else if(Fuel_Type == Fuel_E10)
    {
    temp_fuel_price = Fuel_Price_E10;
    }
    //Amount_to_pump = ((uint16_t) ((Balance/temp_fuel_price)*TICK_PER_LITER));
    state = ON;

    }
    Current_Price = 0;
    break;

    case ON:


    Current_Price = (Amount_Pumped/TICK_PER_LITER) * temp_fuel_price;
    Amount_to_pump = ((uint16_t) ((Balance/temp_fuel_price)*TICK_PER_LITER));
    if(Fuel_Type == 0)
    {
    state = OFF;
    Amount_to_pump = 0;
    }
    break;

    default:
    break;

    }

    vTaskDelay(pdMS_TO_TICKS(5));

    }
}


/****************************** End Of Module *******************************/

