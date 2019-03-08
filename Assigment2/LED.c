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
void activate_LED(uint8_t activated_lights)
{
    GPIO_PORTF_DATA_R |= (0x0E); // CLEAR LEDs
    GPIO_PORTF_DATA_R &= ~(activated_lights);
    return;
}



/****************************** End Of Module *******************************/











