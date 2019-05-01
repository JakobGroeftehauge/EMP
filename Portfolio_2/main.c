

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
//#include "hardware_tm4c123g.h" // Requires TivaWare library
//#include "systick_frt.h"    // From Mortens Lessons
#include "tm4c123gh6pm.h"
#include "gpio.h"


/*****************************    Defines    *******************************/
//#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define IDLE_PRIO 0
#define LOW_PRIO  1
#define MED_PRIO  2
#define HIGH_PRIO 3

#define GREEN_LED_TASK 2
#define YELLOW_LED_TASK 3


/*****************************   Constants   *******************************/
SemaphoreHandle_t taskSignalSem;
/*****************************   Variables   *******************************/

//uint32_t SystemCoreClock;

/*****************************   Functions   *******************************/



int main(void)
{
    init_gpio();

    //Create semaphores



    // Start the tasks.




    // Start the scheduler.
    // --------------------
    vTaskStartScheduler();


    // Will only get here, if there was insufficient memory.
    // -----------------------------------------------------
    return 0;
}
