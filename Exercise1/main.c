

/**
 * main.c
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "timer0.h"
#include "systick.h"
#include <math.h>

#define DEBOUNCE_DELAY 2
#define HOLD_DELAY 4000

    volatile uint8_t LEDList[8] = {0x00, 0x08, 0x04, 0x0C, 0x02, 0x0A, 0x06, 0x0E};
    volatile uint16_t counter = 0;
    volatile uint32_t tick;
    volatile uint16_t automode_tick=0;


int main(void)
{
    tick = 0;

    uint8_t dummy;
    volatile uint32_t tick_initial_value;
    volatile uint32_t tick_current_value;
    volatile uint32_t difference;
    uint32_t waitTimer;
    volatile uint8_t auto_mode_enabled_flag;

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

        if (auto_mode_enabled_flag == 1)
        {
          if(automode_tick>0)
          {
              counter=(counter+1)%8;
              automode_tick--;
          }
        }
        //prescaler = TIMER0_TAPV_R;
        GPIO_PORTF_DATA_R &= ~(0x0E);
        GPIO_PORTF_DATA_R |= LEDList[counter];

        // button pressed?
        if(!(GPIO_PORTF_DATA_R & 0x10))
        {
            //save sytick timer value
            tick_initial_value = tick;

            // wait for a little bit
            difference=0;
            while(difference < DEBOUNCE_DELAY)
            {
                tick_current_value = tick;
                difference = tick_current_value - tick_initial_value;

            }
            // check if button still pressed
            if(!(GPIO_PORTF_DATA_R & 0x10))
            {
                auto_mode_enabled_flag = 0;
                // while pressed, do nothing
                while(!(GPIO_PORTF_DATA_R & 0x10))
                {
                   if (tick - tick_initial_value > HOLD_DELAY)
                       auto_mode_enabled_flag = 1;
                }
                // when released count up
                if (!(auto_mode_enabled_flag == 1))
                {
                    counter = (counter + 1) % 8;
                }
                //GPIO_PORTF_DATA_R &= ~(0x0E);
            }
        }
    }
    return 0;
}

void systick_handler(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    //counter++;
    //counter = (counter + 1) % 8;
    tick++;
    if(tick%400==0)
    {
        automode_tick++;
    }
//    counter = tick % 8;

    return;

}
