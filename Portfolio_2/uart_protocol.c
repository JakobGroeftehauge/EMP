
/***************************** Include files *******************************/
#include "tm4c123gh6pm.h"
#include "EMP_type.h"
#include "uart_protocol.h"
#include "uart0.h"
#include "system_setup.h"
#include "queue.h"

/*****************************    Defines    *******************************/

/********************** External declaration of Variables ******************/

volatile UBaseType_t elementsInQueue            = 0;
volatile uint8_t     *receive_character         = 0;



/****************************    Semaphores    ***************************/



/*****************************   Constants   *******************************/


/*************************  Function interfaces ****************************/

void UARTRX (void * pvParameters)
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : -
******************************************************************************/
{
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();


    for (;;)
    {
        if (uart0_rx_rdy())
        {
            receive_character = uart0_getc();
            if( xQueueSend(UART_RX_QUEUE_HANDLE, &receive_character, (TickType_t) 0) == pdPASS); //(void *)
                //elementsInQueue = 100;

        }

        elementsInQueue = uxQueueMessagesWaiting( UART_RX_QUEUE_HANDLE );
        vTaskDelayUntil (&xLastWakeTime, pdMS_TO_TICKS( 50 ) );
        //vTaskDelay(pdMS_TO_TICKS( 50 ));
    }
}

void UARTTX (void * pvParameters)
{
   char c='a';
   for(;;)
   {
       if(uart0_tx_rdy())
       {
           uart0_putc(xQueueReceive(UART_TX_QUEUE_HANDLE,&c,(TickType_t) 10));
       }
   }
}



