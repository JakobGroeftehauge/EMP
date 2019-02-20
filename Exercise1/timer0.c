/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: timer.c
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
* 190220  MA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "timer0.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void init_timer0_periodic(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : Set up the timer 0 for periodic mode
******************************************************************************/
  {
     // initialise the clock for the timer port
     SYSCTL_RCGC1_R = SYSCTL_RCGC1_TIMER0;

     // timer setup
     TIMER0_CTL_R &= ~(0x01);

     TIMER0_CFG_R = 0;

     TIMER0_TAMR_R &= ~(0x03);
     TIMER0_TAMR_R |= 0x0A;

     // start value
     TIMER0_TAILR_R = 0xFFFF;

     // Prescaler - ser ikke ud til at virke
     TIMER0_TAPMR_R = 0xFF;

     //Enable timer A
     TIMER0_CTL_R |= (0x00000001);


     SYSCTL_RCGCTIMER_R |= 1;

     return;
  }


/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/

/****************************** End Of Module *******************************/











