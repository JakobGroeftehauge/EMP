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
SemaphoreHandle_t AMOUNT_PUMPED_SEM;
SemaphoreHandle_t ACTIVATE_PUMP_HANDLER_SEM;
SemaphoreHandle_t UART_RECEIVE_SEM;
SemaphoreHandle_t QUEUE_SEM;

TaskHandle_t PUMP_EMULATOR_TASK_HANDLE;
TaskHandle_t ENCODER_TASK_HANDLE;
TaskHandle_t PUMP_TASK_HANDLE;
TaskHandle_t BUTTON_DRIVER_HANDLE;
TaskHandle_t PRICE_CALCULATOR_TASK;
TaskHandle_t KEYBOARD_TASK;
TaskHandle_t UART_RX_HANDLE;
TaskHandle_t UART_TX_HANDLE;

QueueHandle_t UART_RX_QUEUE_HANDLE;
QueueHandle_t UART_TX_QUEUE_HANDLE;
QueueHandle_t KEYBOARD_QUEUE_HANDLE;
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
    ACTIVATE_PUMP_HANDLER_SEM = xSemaphoreCreateCounting(1,0);
    UART_RECEIVE_SEM = xSemaphoreCreateCounting(1,0);
    QUEUE_SEM = xSemaphoreCreateCounting(1,0);


    //MUTEXS
    AMOUNT_PUMPED_SEM = xSemaphoreCreateCounting(1, 1);
}

void setup_queues()
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/
{
    KEYBOARD_QUEUE_HANDLE = xQueueCreate(10, sizeof(float));
    UART_RX_QUEUE_HANDLE = xQueueCreate(10, sizeof(char));
    UART_TX_QUEUE_HANDLE = xQueueCreate(10, sizeof(char));

}

void init_system_parameter()
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/
{

    Motor_ON = 0;
    Flow_ON = 0;
    Shunt_ON = 0;
}
/****************************** End Of Module *******************************/
