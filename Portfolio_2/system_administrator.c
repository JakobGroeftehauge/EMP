/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: system_administrator.c
*
* PROJECT....: EMP portfolio 2
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190513  JGR    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "system_administrator.h"
#include "system_setup.h"
/*****************************    Defines    *******************************/
// States
#define IDLE                         0
#define WAIT_FOR_FUEL_TYPE           1
#define WAIT_FOR_FIRST_BYTE          2
#define WAIT_FOR_SECOND_BYTE         3
#define WAIT_FOR_THIRD_BYTE          4
#define WAIT_FOR_FOURTH_BYTE         5
/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/

void system_administrator_task(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    uint8_t temp_message;
    uint8_t state = IDLE;
    uint32_t tempPrice;
    uint8_t  tempFuelType;
    float temp_float_price;

    for(;;)
    {
        xQueueReceive(UART_TX_QUEUE_HANDLE, &temp_message, portMAX_DELAY);

        switch(state)
        {
        case IDLE:
            if(temp_message == 0x00)
            {
                //Print log
            }
            else if(temp_message == 0x01)
            {
                state = WAIT_FOR_FUEL_TYPE;
            }
            break;

        case WAIT_FOR_FUEL_TYPE:
            tempFuelType = temp_message;

            if(tempFuelType == Fuel_E10 || tempFuelType == Fuel_95 || tempFuelType == Fuel_92)
                state = WAIT_FOR_FIRST_BYTE;
            else
            {
                state = IDLE;
            }
            break;

        case WAIT_FOR_FIRST_BYTE:
            tempPrice = temp_message;
            state = WAIT_FOR_SECOND_BYTE;
            break;

        case WAIT_FOR_SECOND_BYTE:
            tempPrice = (tempPrice << 8) | temp_message;
            state = WAIT_FOR_THIRD_BYTE;
            break;

        case WAIT_FOR_THIRD_BYTE:
            tempPrice = (tempPrice << 8) | temp_message;
            state = WAIT_FOR_FOURTH_BYTE;
            break;

        case WAIT_FOR_FOURTH_BYTE:
            tempPrice = (tempPrice << 8) | temp_message;

            // convert to float
            temp_float_price = ((float*)&tempPrice);

            if(tempFuelType == Fuel_92)
            {

            }
            else if(tempFuelType == Fuel_92)
            {

            }
            else if(tempFuelType == Fuel_E10)
            {

            }
            // store the specified place
            state = IDLE;
            break;

        default:
            state = IDLE;
            break;
        }



    }

}

/****************************** End Of Module *******************************/











