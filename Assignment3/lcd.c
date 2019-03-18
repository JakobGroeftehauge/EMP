/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: lcd.c
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
* 190318  MA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/



/*****************************   Functions   *******************************/

void port_init(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    uint8_t dummy;

    // Enable clock to port
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOC;

    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOD;

    // Do a dummy read to insert a few cycles after enabling the peripheral.
    dummy = SYSCTL_RCGC2_R;

    // set PC4-PC7 as output
    GPIO_PORTC_DIR_R = 0xF0;

    // enable
    GPIO_PORTC_DEN_R = 0xF0;

    // set PD2-PD3 as output
    GPIO_PORTCD_DIR_R = 0x0C;

    // enable
    GPIO_PORTD_DEN_R = 0x0C;


}


void ldc_init(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    port_init();

    // Clear high bits
    GPIO_PORTC_DATA_R &= ~(0xF0);

    delay(8);
    // Set high bits
    GPIO_PORTC_DATA_R |= 0x30;

    delay(2);
    GPIO_PORTC_DATA_R |= 0x30;

    delay(1);
    GPIO_PORTC_DATA_R |= 0x30;

    GPIO_PORTC_DATA_R |= 0x20;


}


/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/


/****************************** End Of Module *******************************/











