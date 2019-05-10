/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: Drehimpulsegeber.c
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
* 190508  JGR    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Drehimpulsgeber.h"
#include "system_setup.h"

/*****************************    Defines    *******************************/


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/

void Drehimpulsgeber_task(void* pvParameters)
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/
{
    uint8_t AB;
    uint8_t AB_delayed;
    uint8_t YY;
    //uint8_t temp_100;
    //uint8_t temp_50;


    YY = 0x00;
    for(;;)
    {

    AB = (GPIO_PORTA_DATA_R >> 5) & 0x03;

    //sample AB.
    if(AB != AB_delayed)
    {
        YY = AB ^= AB_delayed;

        if((AB >> 1) == (AB & 0x01))
        {
            switch(YY)
            {
            case 1:
            bill_50_inserted++;
            break;
            // one
            case 2:
            bill_100_inserted++;
            break;

            default:
            break;

            }
        }
        else
        {
            switch(YY)
            {
            case 2:
            bill_50_inserted++;
            break;

            case 1:
            bill_100_inserted++;
            break;

            default:
            break;
            }



        }

    }

    AB_delayed = AB;
    vTaskDelay(pdMS_TO_TICKS(1));
    }

}

/****************************** End Of Module *******************************/
