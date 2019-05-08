/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: RTC.c
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
#include "RTC.h"
#include "system_setup.h"
/*****************************    Defines    *******************************/
#define ONE_SEK    1000
/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/

void RTC_task(void* pvParameters)
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/
{
    TickType_t xLastWakeTime;

    for(;;)
    {

    xLastWakeTime = xTaskGetTickCount();

    xSemaphoreTake(RTC_SEM, portMAX_DELAY);

    RTC_sek++;

    if(RTC_sek >= 60)
    {
    RTC_sek = 0;
    RTC_min++;

    if(RTC_min >= 60)
    {
    RTC_min = 0;
    RTC_hour++;

    if(RTC_hour >= 24)
    {
    RTC_hour = 0;
    }

    }
    }

    xSemaphoreGive(RTC_SEM);



    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(ONE_SEK));
    }
}


/****************************** End Of Module *******************************/
