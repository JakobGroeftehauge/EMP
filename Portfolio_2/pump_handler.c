/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: pump_handler.c
*
* PROJECT....: Portfolio 2
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190501  JGR    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "pump_handler.h"
#include "system_setup.h"
/*****************************    Defines    *******************************/
#define PUMP_OFF_STATE            0 //DONE
#define PUMP_READY                1
#define PUMP_ON_STATE             2 //DONE
#define PUMPING_SHUNT_ON_STATE    3
#define PUMPING_SHUNT_OFF_STATE   4
#define FINISH_PUMPING_STATE      5





#define TRUE                      1
#define FALSE                     0

#define MAX_DEACTIVATION_TIME     1000 //15000/5  //when schedueled every 1ms
#define SHUNT_ACTIVATION_PERIOD   1000   //when schedueled every 1 ms
//#define TICK_PER_LITER            1125
#define DELAY_TIME                5 //ms

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void pump_handler_task(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    uint8_t state = PUMP_OFF_STATE;
    uint16_t time_since_handle_activation = 0;
    TickType_t xLastWakeTime;
    uint16_t amount_pumped_shunt_activated =  0;


    //Check order of state assignment (priorities)
    //PUMP_OFF_STATE NEEDS TO ASSIGNEED LAST

    for(;;)
    {

    xLastWakeTime = xTaskGetTickCount();

    switch(state)
    {
        case PUMP_OFF_STATE:

            Motor_ON = FALSE; //make sure the physical pump is deactivated

            if(Hook_Activated == 1 && Amount_to_pump > 0)
            {
            state = PUMP_ON_STATE;
            time_since_handle_activation = 0;
            }
            break;

//        case PUMP_READY:
//
//            if(Hook_Activated == TRUE)
//            {
//                state = PUMP_ON_STATE;
//                time_since_handle_activation = 0;
//            }
//            else
//            {
//                state = PUMP_OFF_STATE;
//            }
//            break;

        case PUMP_ON_STATE:

            Motor_ON = TRUE;
            Flow_ON = FALSE;
            Shunt_ON = TRUE;

            time_since_handle_activation++;

            if(Handle_Activated == TRUE)
            {
            state = PUMPING_SHUNT_ON_STATE;

            xSemaphoreTake(AMOUNT_PUMPED_SEM, portMAX_DELAY);
            amount_pumped_shunt_activated = Amount_Pumped;
            xSemaphoreGive(AMOUNT_PUMPED_SEM);
            time_since_handle_activation = 0;

            }

            if(time_since_handle_activation >= MAX_DEACTIVATION_TIME || Hook_Activated == FALSE)
            {
            state = FINISH_PUMPING_STATE;
            }


            break;

        case PUMPING_SHUNT_ON_STATE:

            Flow_ON = TRUE;
            Shunt_ON = TRUE;

            time_since_handle_activation++; //test

            if(Handle_Activated == FALSE)
            {
            state = PUMP_ON_STATE;
            time_since_handle_activation = 0;
            }

            if((amount_pumped_shunt_activated + 0.1 * TICK_PER_LITER) <= Amount_Pumped)
            {
                if(Amount_Pumped <= (Amount_to_pump - TICK_PER_LITER*0.1))
                {
                state = PUMPING_SHUNT_OFF_STATE;
                }

            }

            break;

        case PUMPING_SHUNT_OFF_STATE:

            Shunt_ON = FALSE;

            time_since_handle_activation++; //test

            if(Handle_Activated == FALSE)
            {
            state = PUMP_ON_STATE;
            time_since_handle_activation = 0;
            }

            if(Amount_Pumped >= (Amount_to_pump - TICK_PER_LITER*0.1))
            {
                state = PUMPING_SHUNT_ON_STATE;
                xSemaphoreTake(AMOUNT_PUMPED_SEM, portMAX_DELAY);
                amount_pumped_shunt_activated = Amount_Pumped;
                xSemaphoreGive(AMOUNT_PUMPED_SEM);
                state = FINISH_PUMPING_STATE;

            }

            break;
        case FINISH_PUMPING_STATE:
            Motor_ON = FALSE;
            Flow_ON = FALSE;
            xSemaphoreGive(FINISH_PUMPING_SEM); //Signal to the the UI task that the refueling has ended.
            break;
        default:
            state = PUMP_OFF_STATE;
            break;
    }

    //vTaskDelay(pdMS_TO_TICKS(5));
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(DELAY_TIME));
    }
}



/****************************** End Of Module *******************************/











