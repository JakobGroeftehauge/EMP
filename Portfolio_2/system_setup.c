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
//SemaphoreHandle_t ACTIVATE_PUMP_HANDLER_SEM;
SemaphoreHandle_t RTC_SEM;
SemaphoreHandle_t FINISH_PUMPING_SEM;
SemaphoreHandle_t INITIATE_PUMPING_SEM;

TaskHandle_t PUMP_EMULATOR_TASK_HANDLE;
TaskHandle_t ENCODER_TASK_HANDLE;
TaskHandle_t PUMP_TASK_HANDLE;
TaskHandle_t BUTTON_DRIVER_HANDLE;
TaskHandle_t PRICE_CALCULATOR_TASK_HANDLE;
TaskHandle_t RTC_CLOCK_TASK_HANDLE;
TaskHandle_t DREHIMPULS_TASK_HANDLE;
TaskHandle_t LCD_DRIVER_TASK;
TaskHandle_t KEYBOARD_TASK_HANDLE;
TaskHandle_t CONTROLLER_TASK_HANDLE;
TaskHandle_t UARTTX_TASK_HANDLE;
TaskHandle_t UARTRX_TASK_HANDLE;

QueueHandle_t UART_RX_QUEUE_HANDLE;
QueueHandle_t UART_TX_QUEUE_HANDLE;
QueueHandle_t KEYBOARD_QUEUE_HANDLE;
QueueHandle_t DIGI_SW_QUEUE_HANDLE;
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
    //ACTIVATE_PUMP_HANDLER_SEM = xSemaphoreCreateCounting(1,0);
    FINISH_PUMPING_SEM = xSemaphoreCreateCounting(1,0);
    //MUTEXS
    AMOUNT_PUMPED_SEM = xSemaphoreCreateCounting(1, 1);
    RTC_SEM = xSemaphoreCreateCounting(1, 1);
    INITIATE_PUMPING_SEM = xSemaphoreCreateCounting(1, 0);

}

void setup_queues()
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/
{
    DIGI_SW_QUEUE_HANDLE = xQueueCreate(5, 1);
    UART_RX_QUEUE_HANDLE = xQueueCreate(10,1);
    UART_TX_QUEUE_HANDLE = xQueueCreate(10,1);
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
    Fuel_Price_92 = 2;
    Fuel_Price_95 = 2;
    Fuel_Price_E10 = 2;
    Amount_to_pump = 10000;
}
/****************************** End Of Module *******************************/
