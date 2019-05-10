/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: pump_emulator.c
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
* 190501  JGR    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "pump_emulator.h"
#include "system_setup.h"
#include "FreeRTOS.h"

/*****************************    Defines    *******************************/
#define TIME_BETWEEN_PULSES 4 //4ms - maybe needs to be corrected to accomodate specifications.
/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/

void pump_emulator_task(void *pvParameters)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    uint8_t delta_time;
    uint8_t power_state;
    TickType_t xLastWakeTime;

    for(;;)
    {

    power_state = (Motor_ON > 0);
    xLastWakeTime = xTaskGetTickCount();


    switch(power_state)
    {
    case 1:
        //RED LED ON
        if(Flow_ON > 0)
        {

            if(Shunt_ON > 0)
            {
                delta_time = 5 * TIME_BETWEEN_PULSES;
            }
            else
            {
                delta_time = TIME_BETWEEN_PULSES;
            }

            xTaskNotifyGive(ENCODER_TASK_HANDLE);

        }
        break;

    default:
        //RED LED OFF
        delta_time = TIME_BETWEEN_PULSES;
        break;
    }

    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(delta_time));

    }
}
/****************************** End Of Module *******************************/











