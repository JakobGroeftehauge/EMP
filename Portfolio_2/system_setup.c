/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: system_setup.c
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
#include "system_setup.h"
#include "FreeRTOS.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
SemaphoreHandle_t MOTOR_ON_SEM;
SemaphoreHandle_t FLOW_ON_SEM;
SemaphoreHandle_t PUMP_ENCODER_TICKS_SEM;

TaskHandle_t PUMP_EMULATOR_TASK_HANDLE;
TaskHandle_t ENCODER_TASK_HANDLE;
/*****************************   Functions   *******************************/

void setup_semaphores()
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    //SIGNALING SEMAPHORES
    MOTOR_ON_SEM = xSemaphoreCreateCounting(1, 0);
    FLOW_ON_SEM = xSemaphoreCreateCounting(1, 0);

    //MUTEXS
    PUMP_ENCODER_TICKS_SEM = xSemaphoreCreateCounting(1, 1);
}

void init_system_parameter()
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/
{
    PUMP_ENCODER_TICKS = 0;
    MOTOR_ON = 0;
    FLOW_ON = 0;
    SHUNT_ON = 0;
}
/****************************** End Of Module *******************************/
