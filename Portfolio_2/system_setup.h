/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: system_setup.h
*
* PROJECT....: Portfolio - 2
*
* DESCRIPTION:
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190501  JGR    Module created.
*
*****************************************************************************/
#ifndef SYSTEM_SETUP_H_
#define SYSTEM_SETUP_H_

/***************************** Include files *******************************/
#include "FreeRTOS.h"
#include "semphr.h"
/*****************************    Defines    *******************************/

/********************** External declaration of Variables ******************/
uint8_t MOTOR_ON;
uint8_t FLOW_ON;
uint8_t SHUNT_ON;

uint32_t PUMP_ENCODER_TICKS;

/**************************   Semaphore Handles    *************************/

extern SemaphoreHandle_t MOTOR_ON_SEM;
extern SemaphoreHandle_t FLOW_ON_SEM;
extern SemaphoreHandle_t PUMP_ENCODER_TICKS_SEM;

extern TaskHandle_t PUMP_EMULATOR_TASK_HANDLE;
extern TaskHandle_t ENCODER_TASK_HANDLE;


/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/

extern void setup_semaphores();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

extern void init_system_parameter();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

/****************************** End Of Module *******************************/

#endif /* SYSTEM_SETUP_H_ */
