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
* 190306  MA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/

void gpio_init(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : Setup switches and LED
******************************************************************************/
{
uint8_t dummy;

// Enable the GPIO port that is used for the on-board LED.
SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

// Do a dummy read to insert a few cycles after enabling the peripheral.
dummy = SYSCTL_RCGC2_R;

GPIO_PORTF_LOCK_R = 0x4C4F434B;  // Unlock the CR register
GPIO_PORTF_CR_R   = 0xFF;        // Enable overwrite of PUR to FP0

// Set the direction as output (PF1).
GPIO_PORTF_DIR_R = 0x0E;

// Enable the GPIO pins for digital function (PF0 to PF4).
GPIO_PORTF_DEN_R = 0x1F;

// Enable internal pull-up (PF0 and PF4).
GPIO_PORTF_PUR_R = 0x11;
}

extern uint8_t getButtonPress(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    uint8_t buttonPressed = 0;
    if (!(GPIO_PORTF_DATA_R & 0x10))
      buttonPressed = 1;
    if (!(GPIO_PORTF_DATA_R & 0x01))
      buttonPressed = 2;
    return buttonPressed;
}

/****************************** End Of Module *******************************/











