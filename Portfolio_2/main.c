

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
    setup_queues();
    //Create semaphores
    setup_semaphores();


    // Start the tasks.

//    xTaskCreate(pump_emulator_task, "Pump emulator", 100, 0, 1, &PUMP_EMULATOR_TASK_HANDLE);
//    xTaskCreate(encoder_task, "Encoder Task", 100, 0, 1, &ENCODER_TASK_HANDLE);
//    xTaskCreate(pump_handler_task, "Pump Handler Task",  100, 0, 1, &PUMP_TASK_HANDLE);
//    xTaskCreate(button_driver_task, "Button driver task", 10, 0, 1, &BUTTON_DRIVER_HANDLE);
//    xTaskCreate(price_calulator_task, "Price Calculator Task", 10, 0, 1, &PRICE_CALCULATOR_TASK);
//    xTaskCreate(vLCD_task, "LCD driver task", 100, 0, 1, &LCD_DRIVER_TASK);
    xTaskCreate(digiSwitch_task, "Drehimpulsgeber", 100, 0, 1, &DREHIMPULS_TASK_HANDLE);


    // Start the scheduler.
    // --------------------

    vTaskStartScheduler();


    // Will only get here, if there was insufficient memory.
    // -----------------------------------------------------
    return 0;
}
