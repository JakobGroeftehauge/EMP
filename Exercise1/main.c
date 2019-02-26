

/**
 * main.c
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "timer0.h"
#include "systick.h"

    volatile uint8_t LEDList[8] = {0x00, 0x08, 0x04, 0x0C, 0x02, 0x0A, 0x06, 0x0E};
    volatile uint16_t counter = 0;


int main(void)
{
    uint8_t dummy;
    // Enable the GPIO port that is used for the on-board LEDs and switchs
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    //Do a dummy read to insert a few cycles after enabling the peripheral.
    dummy = SYSCTL_RCGC2_R;

    // Set the direction as output (PF1 - PF3).
    GPIO_PORTF_DIR_R = 0x0E;

    //Enable the GPIO pins for digital function (PF1- PF4)
    GPIO_PORTF_DEN_R = 0x1E;

    // Enable internal pull-up (PF4).
    GPIO_PORTF_PUR_R = 0x10;

    //init_timer0_periodic();

    disable_global_int();
    init_systick();
    enable_global_int();

    while(1)
    {

        //prescaler = TIMER0_TAPV_R;
        GPIO_PORTF_DATA_R |= LEDList[counter];

        if(!(GPIO_PORTF_DATA_R & 0x10))
        {
            while(!(GPIO_PORTF_DATA_R & 0x10))
            {

            }
            counter++;
            if (counter > 7)
                counter = 0;
            GPIO_PORTF_DATA_R &= ~(0x0E);
        }

//        timer = TIMER0_TAR_R;
//
//        if ((timer > 60000))
//            {
//            TIMER0_TAR_R = 0x0;
//            counter++;
//            GPIO_PORTF_DATA_R &= ~(0x0E);
//            }



            //GPIO_PORTF_DATA_R |= 0b00001010;
    }

    return 0;
}

void systick_handler(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    if (counter == 0)
    {
        counter = 1;
    }
    else
    {
        counter = 0;
    }
    GPIO_PORTF_DATA_R &= ~(0x0E);

    return;

}
