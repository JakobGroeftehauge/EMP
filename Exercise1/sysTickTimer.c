/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp.c
*
* PROJECT....: EMP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190226  JFR    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "sysTickTimer.h"

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "string.h"


/*****************************    Defines    *******************************/
#define SYSTICK_RELOAD_VALUE (80000*100) // 5*100 mS

// Missing definitions in tm4c123gh6pm.h file
#define NVIC_INT_CTRL_PEND_SYST   0x04000000  // Pend a systick int
#define NVIC_INT_CTRL_UNPEND_SYST 0x02000000  // Unpend a systick int

#define SYSTICK_PRIORITY    0x7E



void enable_global_int()
/*****************************************************************************
*   Function : Enable global interrupt
******************************************************************************/
{
  // enable interrupts.
  __asm("cpsie i");
}

void disable_global_int()
/*****************************************************************************
*   Function : disable global interrupt
******************************************************************************/
{
  // disable interrupts.
  __asm("cpsid i");
}




void SysTickInit()
/*****************************************************************************
*   Function : Setup the systick timer  (interrupt mode)
******************************************************************************/
{

  // Disable systick timer
  NVIC_ST_CTRL_R &= ~(NVIC_ST_CTRL_ENABLE);

  // Set current systick counter to reload value
  NVIC_ST_CURRENT_R = SYSTICK_RELOAD_VALUE;
  // Set Reload value, Systick reload register
  NVIC_ST_RELOAD_R = SYSTICK_RELOAD_VALUE;

  // NVIC systick setup, vector number 15
  // Clear pending systick interrupt request
  NVIC_INT_CTRL_R |= NVIC_INT_CTRL_UNPEND_SYST;

  // Set systick priority to 0x10, first clear then set.
  NVIC_SYS_PRI3_R &= ~(NVIC_SYS_PRI3_TICK_M);
  NVIC_SYS_PRI3_R |= (NVIC_SYS_PRI3_TICK_M & (SYSTICK_PRIORITY<<24));

  //NVIC_SYS_PRI3_R |= (NVIC_SYS_PRI3_TICK_M & (SYSTICK_PRIORITY<<NVIC_SYS_PRI3_TICK_S));

  // Select systick clock source, Use core clock
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC;

  // Enable systick interrupt
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_INTEN;

  // Enable and start timer
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
}

/****************************** End Of Module *******************************/

