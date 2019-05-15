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
#include "emp_type.h"
/*****************************    Defines    *******************************/
#define TRUE  1
#define FALSE 0

#define Fuel_92   '1'
#define Fuel_95   '2'
#define Fuel_E10  '3'

#define DSE_CCW     3
#define DSE_CW      6

#define TICK_PER_LITER            1125
/********************** External declaration of Variables ******************/

//Structs
struct log_data{
    INT8U id[16];
    INT16U amount_paid;
    float Price;
    float litres_pumped;
    INT8U Time_sec;
    INT8U Time_min;
    INT8U Time_hour;
    INT8U Fuel_Type;
};


struct Accounts {
    INT8U id[16];
    INT8U password[16];
};

// State buffers:

uint8_t Hook_Activated;
uint8_t Handle_Activated;
uint8_t Flow_ON;
uint8_t Motor_ON;
uint8_t Shunt_ON;

uint8_t Fuel_Type;
float Fuel_Price_92;
float Fuel_Price_95;
float Fuel_Price_E10;

uint16_t Amount_Pumped;
uint16_t Amount_to_pump;
uint16_t Balance;
volatile float Current_Price;

uint8_t RTC_sek;
uint8_t RTC_min;
uint8_t RTC_hour;

struct log_data po_log_data[128];
uint8_t log_pointer;


/**************************   Semaphore Handles    *************************/

extern SemaphoreHandle_t MOTOR_ON_SEM;
extern SemaphoreHandle_t FLOW_ON_SEM;
extern SemaphoreHandle_t AMOUNT_PUMPED_SEM;
//extern SemaphoreHandle_t ACTIVATE_PUMP_HANDLER_SEM;
extern SemaphoreHandle_t RTC_SEM;
extern SemaphoreHandle_t FINISH_PUMPING_SEM;
/**************************   Task Handles    ******************************/

extern TaskHandle_t PUMP_EMULATOR_TASK_HANDLE;
extern TaskHandle_t ENCODER_TASK_HANDLE;
extern TaskHandle_t PUMP_TASK_HANDLE;
extern TaskHandle_t BUTTON_DRIVER_HANDLE;
extern TaskHandle_t PRICE_CALCULATOR_TASK_HANDLE;
extern TaskHandle_t RTC_CLOCK_TASK_HANDLE;
extern TaskHandle_t DREHIMPULS_TASK_HANDLE;
extern TaskHandle_t LCD_DRIVER_TASK;
extern TaskHandle_t KEYBOARD_TASK_HANDLE;
extern TaskHandle_t CONTROLLER_TASK_HANDLE;
extern TaskHandle_t UARTTX_TASK_HANDLE;
extern TaskHandle_t UARTRX_TASK_HANDLE;
extern TaskHandle_t SYS_ADMIN_TASK_HANDLE;

/**************************   Queue Handles    ******************************/

extern QueueHandle_t UART_RX_QUEUE_HANDLE;
extern QueueHandle_t UART_TX_QUEUE_HANDLE;
extern QueueHandle_t KEYBOARD_QUEUE_HANDLE;
extern QueueHandle_t DIGI_SW_QUEUE_HANDLE;

/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/

extern void setup_semaphores();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

extern void setup_queues();
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
