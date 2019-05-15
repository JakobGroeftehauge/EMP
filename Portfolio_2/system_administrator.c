/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: system_administrator.c
*
* PROJECT....: EMP portfolio 2
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190513  JGR    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "system_administrator.h"
#include "system_setup.h"
/*****************************    Defines    *******************************/
// States
#define IDLE                         0
#define WAIT_FOR_FUEL_TYPE           1
#define WAIT_FOR_FIRST_BYTE          2
#define WAIT_FOR_SECOND_BYTE         3
#define WAIT_FOR_THIRD_BYTE          4
#define WAIT_FOR_FOURTH_BYTE         5
/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/

void write_time(INT8U log_no)
{
    INT8U c;

    c = po_log_data[log_no].Time_hour/10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
    c = po_log_data[log_no].Time_hour%10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = po_log_data[log_no].Time_min/10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
    c = po_log_data[log_no].Time_min%10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = po_log_data[log_no].Time_sec/10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
    c = po_log_data[log_no].Time_sec%10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = ':';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
    c = ' ';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
}

void write_account_ID(INT8U log_no)
{
    INT8U c;
    INT8U j;

    j = 0;
    while(j < 16 && po_log_data[log_no].id[j]!=0)
    {
        c = po_log_data[log_no].id[j];
        xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
        j++;
    }

    c = ' ';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
}

void write_fuel_type(INT8U log_no)
{
    INT8U c;
    switch(po_log_data[log_no].Fuel_Type)
        {
        case Fuel_92:
            c = 'O';
            xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
            c = '_';
            xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
            c = '9';
            xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
            c = '2';
            xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
            break;

        case Fuel_95:
            c = 'O';
            xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
            c = '_';
            xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
            c = '9';
            xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
            c = '5';
            xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
            break;

        case Fuel_E10:
            c = 'E';
            xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
            c = '1';
            xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
            c = '0';
            xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
            break;

        default:
            break;

        }

        c = ' ';
        xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
}

void write_litres_pumped(INT8U log_no)
{
    INT8U c;
    c = po_log_data[log_no].litres_pumped/10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = (INT16U)po_log_data[log_no].litres_pumped%10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = '.';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = ((INT16U)(po_log_data[log_no].litres_pumped*100)%100)/10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = (INT16U)(po_log_data[log_no].litres_pumped*100)%10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = 'l';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = ' ';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
}

void write_fuel_price(INT8U log_no)
{
    INT8U c;
    c = po_log_data[log_no].Price/10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = (INT16U)po_log_data[log_no].Price%10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = '.';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = ((INT16U)(po_log_data[log_no].Price*100)%100)/10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = (INT16U)(po_log_data[log_no].Price*100)%10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = 'k';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = 'r';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = ' ';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
}

void write_amount_paid(INT8U log_no)
{
    INT8U c;
    c = po_log_data[log_no].amount_paid/10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = (INT16U)po_log_data[log_no].amount_paid%10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = '.';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = ((INT16U)(po_log_data[log_no].amount_paid*100)%100)/10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = (INT16U)(po_log_data[log_no].amount_paid*100)%10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = 'k';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = 'r';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = ' ';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = 0x0A;
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);
}

void print_log()
{
    INT8U i;
    for(i=0;i<log_pointer;i++)
    {
    // write Time
       write_time(i);

       //write account ID
       write_account_ID(i);

       //Write fuel type
       write_fuel_type(i);

       //write litres pumped
       write_litres_pumped(i);

       //Fuel price
       write_fuel_price(i);

       //Amount paid
       write_amount_paid(i);
    }
}


void system_administrator_task(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    uint8_t temp_message;
    uint8_t state = IDLE;
    float tempPrice;
    uint8_t  tempFuelType;

    for(;;)
    {
        xQueueReceive(UART_RX_QUEUE_HANDLE, &temp_message, portMAX_DELAY);

        switch(state)
        {
        case IDLE:
            if(temp_message == '0')
            {
                print_log();
            }
            else if(temp_message == '1')
            {
                state = WAIT_FOR_FUEL_TYPE;
            }
            break;

        case WAIT_FOR_FUEL_TYPE:
            tempFuelType = temp_message;

            if(tempFuelType == Fuel_E10 || tempFuelType == Fuel_95 || tempFuelType == Fuel_92)
                state = WAIT_FOR_FIRST_BYTE;
            else
            {
                state = IDLE;
            }
            break;

        case WAIT_FOR_FIRST_BYTE:
            tempPrice = (temp_message - '0')*10;
            state = WAIT_FOR_SECOND_BYTE;
            break;

        case WAIT_FOR_SECOND_BYTE:
            tempPrice = tempPrice + (temp_message - '0');
            state = WAIT_FOR_THIRD_BYTE;
            break;

        case WAIT_FOR_THIRD_BYTE:
            tempPrice = tempPrice + (float)(temp_message - '0')*0.1;
            state = WAIT_FOR_FOURTH_BYTE;
            break;

        case WAIT_FOR_FOURTH_BYTE:
            tempPrice = tempPrice + (float)(temp_message - '0')*0.01;

            if(tempFuelType == Fuel_92)
            {
                Fuel_Price_92 = tempPrice;
            }
            else if(tempFuelType == Fuel_95)
            {
                Fuel_Price_95 = tempPrice;
            }
            else if(tempFuelType == Fuel_E10)
            {
                Fuel_Price_E10 = tempPrice;
            }
            state = IDLE;
            break;

        default:
            state = IDLE;
            break;
        }



    }

}

/****************************** End Of Module *******************************/











