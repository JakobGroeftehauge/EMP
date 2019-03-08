/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: EMP
*
* DESCRIPTION: Assignment 2, main module. No main.h file.
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190308  MA   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "swtimers.h"
#include "systick.h"
#include "button.h"
#include "GPIO.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
extern int16_t ticks;

int main(void)
{
    disable_global_int();
	return 0;
}
