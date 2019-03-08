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
#define BIT(x)              (0x01 << (x))
/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
extern int16_t ticks;

int main(void)
{
    uint8_t event;
    uint8_t activated_lights;



    disable_global_int();
    init_systick();
    gpio_init();
    enable_global_int();

    // ------------------------------
    while( !ticks );

    // The following will be executed every 5mS
    ticks--;

    if( ! --alive_timer )
    {
      alive_timer        = TIM_500_MSEC;
      GPIO_PORTD_DATA_R ^= 0x40;
    }

    event = select_button();
    activated_lights = light_combination(event);
    activate_LED(activated_lights);


	return 0;
}
