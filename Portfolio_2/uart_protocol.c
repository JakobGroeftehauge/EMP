
/***************************** Include files *******************************/
#include "tm4c123gh6pm.h"
#include "EMP_type.h"
#include "uart_protocol.h"
#include "uart0.h"
#include "system_setup.h"
#include "queue.h"
#include "FreeRTOS.h"

/*****************************    Defines    *******************************/



/********************** External declaration of Variables ******************/

volatile UBaseType_t elementsInQueue            = 0;
volatile uint8_t     *receive_character         = 0;
char dsend = 'a';
char csend;


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
    //TickType_t xLastWakeTime;
    //const TickType_t xFrequency = 50;


    for (;;)
    {
        if (uart0_rx_rdy())
        {
            receive_character = uart0_getc();
            if( xQueueSend(UART_RX_QUEUE_HANDLE, &receive_character, (TickType_t) 0) == pdPASS); //(void *)
                //elementsInQueue = 100;

        }

        elementsInQueue = uxQueueMessagesWaiting( UART_RX_QUEUE_HANDLE );
        vTaskDelayUntil (&xLastWakeTime, pdMS_TO_TICKS( 100 ) );
        //vTaskDelay(10);
    }
}

void UARTTX (void * pvParameters)
{

   xQueueSend(UART_TX_QUEUE_HANDLE, &dsend, portMAX_DELAY);

   for(;;)
   {
       if(uart0_tx_rdy())
       {
           xQueueReceive(UART_TX_QUEUE_HANDLE,&csend, portMAX_DELAY);
           uart0_putc(csend);//

       }
   }
}



