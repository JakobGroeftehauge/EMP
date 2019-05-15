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
#include "tm4c123gh6pm.h"

/*****************************    Defines    *******************************/
#define TIME_BETWEEN_PULSES 9 //4ms - maybe needs to be corrected to accomodate specifications.
#define ON  1
#define OFF 0

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

    xLastWakeTime = xTaskGetTickCount();

    if (Motor_ON > 0)
    {
        power_state = ON;
    }
    else
    {
        power_state = OFF;
    }




    switch(power_state)
    {
    case ON:
        GPIO_PORTF_DATA_R &= ~0x02;
        if(Flow_ON > 0)
        {

            if(Shunt_ON > 0)
            {
                delta_time = 10 * TIME_BETWEEN_PULSES;
                GPIO_PORTF_DATA_R &= ~0x04; //Yellow LED
            }
            else
            {
                delta_time = TIME_BETWEEN_PULSES;

                GPIO_PORTF_DATA_R |= 0x04; //Yellow LED
            }

            xTaskNotifyGive(ENCODER_TASK_HANDLE);

        }
        break;

    case OFF:
        GPIO_PORTF_DATA_R |= 0x02;
        GPIO_PORTF_DATA_R |= 0x04; //Yellow LED
        delta_time = TIME_BETWEEN_PULSES;
        break;

    default:
        GPIO_PORTF_DATA_R |= 0x02;
        GPIO_PORTF_DATA_R |= 0x04; //Yellow LED
        delta_time = TIME_BETWEEN_PULSES;
        break;
    }

    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(delta_time)); // Increases 2 tick every time the encoder is signaled
    // Due too lack of CPU power
        //vTaskDelay(pdMS_TO_TICKS(1));
    }
}
/****************************** End Of Module *******************************/











