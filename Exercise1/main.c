

/**
 * main.c
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"

int main(void)
{
    uint8_t counter = 0;
    uint8_t LEDList[8] = {0x00, 0x08, 0x04, 0x0C, 0x02, 0x0A, 0x06, 0x0E};

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


    SYSCTL_RCGC1_R = SYSCTL_RCGC1_TIMER0;

    // timer setup
    TIMER0_CTL_R &= ~(0x01);
    //TIMER0_CTL_R = 0;

    TIMER0_CFG_R = 0;

    TIMER0_TAMR_R &= ~(0x03);
    TIMER0_TAMR_R |= 0x02;

    // start value
    TIMER0_TAILR_R = 2000;

    //Enable timer A
    TIMER0_CTL_R |= (0x00000001);


    SYSCTL_RCGCTIMER_R |= 1;



    while(1)
    {

//        if(GPIO_PORTF_DATA_R & 0x10)
//            GPIO_PORTF_DATA_R &= ~(0b00001010);
//        else
//            GPIO_PORTF_DATA_R |= 0b00001010;

   ///////////////////////////////////////////////////////////////////////

        GPIO_PORTF_DATA_R |= LEDList[counter];

//        if(!(GPIO_PORTF_DATA_R & 0x10))
//        {
//            while(!(GPIO_PORTF_DATA_R & 0x10))
//            {
//
//            }
//            counter++;
//            if (counter > 7)
//                counter = 0;
//            GPIO_PORTF_DATA_R &= ~(0x0E);
//        }

        uint16_t timer;
        timer = TIMER0_TAR_R;

        if (!(timer %2 == 0))
            GPIO_PORTF_DATA_R &= ~(0b00001010);
                    else
            GPIO_PORTF_DATA_R |= 0b00001010;



            //GPIO_PORTF_DATA_R |= 0b00001010;
    }

    return 0;
}
