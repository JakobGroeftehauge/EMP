

/**
 * main.c
 */

/***************************** Include files *******************************/

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Hardware includes. */
#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "uart0.h"

/* Application includes */
#include "system_setup.h"
#include "pump_emulator.h"
#include "encoder.h"
#include "pump_handler.h"
#include "Button_driver.h"
#include "price_calculator.h"
#include "lcd.h"
#include "emp_type.h"
#include "RTC.h"
#include "digisw.h"
#include "key.h"
#include "System_Control.h"
#include "uart_protocol.h"
#include "system_administrator.h"

/*****************************    Defines    *******************************/
//#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define IDLE_PRIO 0
#define LOW_PRIO  1
#define MED_PRIO  2
#define HIGH_PRIO 3


/*****************************   Constants   *******************************/
SemaphoreHandle_t taskSignalSem;
/*****************************   Variables   *******************************/



/*****************************   Functions   *******************************/



int main(void)
{
    init_gpio();
    init_system_parameter();
    uart0_init(115200,8,'o',1);
    setup_queues();
    //Create semaphores
    setup_semaphores();

    KEYBOARD_QUEUE_HANDLE = xQueueCreate( 10, sizeof( char ) );


    // Start the tasks.


    xTaskCreate(UARTTX,"UART TX", 100, 0, 1, &UARTTX_TASK_HANDLE);
    xTaskCreate(UARTRX,"UART RX", 100, 0, 1, &UARTRX_TASK_HANDLE);
    xTaskCreate(pump_handler_task, "Pump Handler Task",  200, 0, 1, &PUMP_TASK_HANDLE);
    xTaskCreate(button_driver_task, "Button driver task", 100, 0, 1, &BUTTON_DRIVER_HANDLE);
    xTaskCreate(price_calulator_task, "Price Calculator Task", 200, 0, 1, &PRICE_CALCULATOR_TASK_HANDLE);
    xTaskCreate(pump_emulator_task, "Pump emulator", 200, 0, 1, &PUMP_EMULATOR_TASK_HANDLE);
    xTaskCreate(encoder_task, "Encoder Task", 100, 0, 1, &ENCODER_TASK_HANDLE);
    xTaskCreate(digiSwitch_task, "Drehimpulsgeber", 100, 0, 1, &DREHIMPULS_TASK_HANDLE);
    xTaskCreate(vLCD_task, "LCD driver task", 100, 0, 1, &LCD_DRIVER_TASK);
    xTaskCreate(key_task, "keyboard driver task", 100, 0, 1, &KEYBOARD_TASK_HANDLE);
    xTaskCreate(RTC_task, "RTC taks", 100, 0, 1, &RTC_CLOCK_TASK_HANDLE);
    xTaskCreate(vControl_task,"Controller task",100, 0, 1, &CONTROLLER_TASK_HANDLE);
    xTaskCreate(system_administrator_task,"system admin",300, 0, 2, &SYS_ADMIN_TASK_HANDLE);

    // Start the scheduler.
    // --------------------

    vTaskStartScheduler();


    // Will only get here, if there was insufficient memory.
    // -----------------------------------------------------
    return 0;
}
