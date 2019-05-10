#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

//#include "defines.h"
//#include "setup.h"
#include "digisw.h"
#include "system_setup.h"

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
uint8_t digisw_state = DSS_IDLE;
uint8_t event = 1;
uint8_t temp1 = 0;
bool temp2 = 0;

/*****************************   Functions   *******************************/



void digiSwitch_task(void *pvParameters)
{

  for( ;; )
  {

    if( GPIO_PORTA_DATA_R & 0x20 ){
      if( digisw_state != DSS_A_ON ){
        if( GPIO_PORTA_DATA_R & 0x40 ){
          event = DSE_CCW;
          //bill_50_inserted++;
          xQueueSend( DIGI_SW_QUEUE_HANDLE,  &event, portMAX_DELAY  );

        }
        else{
          event = DSE_CW;
          //bill_100_inserted++;
          xQueueSend( DIGI_SW_QUEUE_HANDLE,  &event, portMAX_DELAY  );

        }
        digisw_state = DSS_A_ON;

      }
      if(GPIO_PORTA_DATA_R & 0x80){
          event = DSE_PRESS;
          //xQueueSend(DIGI_SW_QUEUE_HANDLE, &event, portMAX_DELAY);

      }
    }
    else
    {
      if( digisw_state != DSS_A_OFF ){
        if( GPIO_PORTA_DATA_R & 0x40 ){
          event = DSE_CW;
          //bill_100_inserted++;
          xQueueSend( DIGI_SW_QUEUE_HANDLE,  &event, portMAX_DELAY  );
        }
        else
        {
          event = DSE_CCW;
          //bill_50_inserted++;
          xQueueSend( DIGI_SW_QUEUE_HANDLE,  &event, portMAX_DELAY  );
        }
        digisw_state = DSS_A_OFF;

      }
      if(GPIO_PORTA_DATA_R & 0x80)
      {
          event = DSE_PRESS;
          //xQueueSend(digiSwitch_queue, &event,portMAX_DELAY);

      }
    }

    vTaskDelay(pdMS_TO_TICKS(1));

  }
}


/****************************** End Of Module *******************************/
