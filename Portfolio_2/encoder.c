/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: encoder.c
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
***************************** Include files *******************************/
#include "encoder.h"
#include "system_setup.h"
#include "FreeRTOS.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/

void encoder_task(void* pvParameters)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{

    for(;;)
    {

        ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

        xSemaphoreTake(PUMP_ENCODER_TICKS_SEM, portMAX_DELAY);
        PUMP_ENCODER_TICKS++;
        xSemaphoreGive(PUMP_ENCODER_TICKS_SEM);

    }
}


/****************************** End Of Module *******************************/











