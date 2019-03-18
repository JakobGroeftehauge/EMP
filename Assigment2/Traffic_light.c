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
* 050128  KA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "Traffic_light.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/

uint8_t light_combination(event)
{
    static uint8_t regular_cycle[4] = {BIT(LED_RED), BIT(LED_RED)|BIT(LED_YELLOW), BIT(LED_GREEN), BIT(LED_YELLOW)};
    static state = REGULAR_CYCLE;
    uint8_t activated_lights = 0;
    static uint8_t cycle_counter = 0;
    static uint16_t cycle_timer = 0;

    switch (state)
    {
        case REGULAR_CYCLE:
            switch (event)
            {
                case SINGLE_PUSH:
                    state = NORWEGIAN;
                    activated_lights = 0;
                    cycle_timer = TIM_2_SEC;
                    break;

                case DOUBLE_PUSH:
                    state = EMERGENCY;
                    activated_lights = LED_RED;
                    break;

                default:
                    if (!(--cycle_timer))
                    {
                        cycle_timer = TIM_SUITABLE;
                        cycle_counter =  (cycle_counter + 1) % 4;
                        activated_lights = regular_cycle[cycle_counter];

                    }
                    break;
            }

            break;

        case NORWEGIAN:
            switch (event)
            {
                case LONG_PUSH:
                    state = REGULAR_CYCLE;
                    cycle_counter = 0;
                    activated_lights = regular_cycle[cycle_counter];
                    cycle_timer = TIM_SUITABLE;
                    break;

                case DOUBLE_PUSH:
                    state = EMERGENCY;
                    activated_lights = LED_RED;
                    break;

                default:
                    if (!(--cycle_timer))
                    {
                        cycle_timer = TIM_2_SEC;
                        activated_lights ^= (1<<LED_YELLOW);
                    }
                    break;
            }

            break;

        case EMERGENCY:
            switch (event)
            {
                case SINGLE_PUSH:
                    state = NORWEGIAN;
                    activated_lights = 0;
                    cycle_timer = TIM_2_SEC;
                    break;

                case LONG_PUSH:
                    state = REGULAR_CYCLE;
                    cycle_counter = 0;
                    activated_lights = regular_cycle[cycle_counter];
                    cycle_timer = TIM_SUITABLE;
                    break;

                default:
                    activated_lights = LED_RED;
                    break;
            }
            break;

        default:
            break;
    }

    return activated_lights;
}

