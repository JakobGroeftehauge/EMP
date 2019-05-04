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

#define TRUE  1
#define FALSE 0
/********************** External declaration of Variables ******************/

// State buffers:

uint8_t Hook_Activated;
uint8_t Handle_Activated;
uint8_t Flow_ON;
uint8_t Motor_ON;
uint8_t Shunt_ON;

uint8_t Fuel_Type;
uint8_t Fuel_Price_92;
uint8_t Fuel_Price_95;
uint8_t Fuel_Price_E10;

uint16_t Amount_Pumped;
uint16_t Balance;
uint16_t Current_Price;
uint16_t Real_Time_Clock;


//Event buffers:

uint16_t Money_Paid;


//uint8_t MOTOR_ON;
//uint8_t FLOW_ON;
//uint8_t SHUNT_ON;
//
//uint32_t PUMP_ENCODER_TICKS;
//uint32_t AMOUNT_FUEL_PAID;

/**************************   Semaphore Handles    *************************/

extern SemaphoreHandle_t MOTOR_ON_SEM;
extern SemaphoreHandle_t FLOW_ON_SEM;
extern SemaphoreHandle_t AMOUNT_PUMPED_SEM;
extern SemaphoreHandle_t ACTIVATE_PUMP_HANDLER_SEM;

extern TaskHandle_t PUMP_EMULATOR_TASK_HANDLE;
extern TaskHandle_t ENCODER_TASK_HANDLE;
extern TaskHandle_t PUMP_TASK_HANDLE;
extern TaskHandle_t BUTTON_DRIVER_HANDLE;

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
