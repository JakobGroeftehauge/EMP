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
#include "System_Control.h"
/*****************************    Defines    *******************************/
// States
#define IDLE                         0
#define WAIT_FOR_FUEL_TYPE           1
#define WAIT_FOR_FIRST_BYTE          2
#define WAIT_FOR_SECOND_BYTE         3
#define WAIT_FOR_THIRD_BYTE          4
#define WAIT_FOR_FOURTH_BYTE         5

#define MAX_DIGITS_PRICE             7
#define MAX_DIGITS_LITER             4
#define MAX_DIGITS_TOTAL            10
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
    c = po_log_data[log_no].amount_paid/1000 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = (po_log_data[log_no].amount_paid%1000)/100 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = (po_log_data[log_no].amount_paid%100)/10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = (po_log_data[log_no].amount_paid%10) + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = 'k';
    xQueueSend(UART_TX_QUEUE_HANDLE, &c, (TickType_t) 20);

    c = 'r';
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

void print_prices_liters(float B92, float L92, float B95, float L95, float BE10, float LE10, float total)
{
    INT8U i;
    char s;
    INT8U total_price_92_arr[MAX_DIGITS_PRICE];
    INT8U total_liter_92_arr[MAX_DIGITS_LITER];
    INT8U text_B92[]={'T','o','t','a','l',' ','p','r','i','c','e',' ','F','u','e','l',' ', '9','2',':',' '};
    INT8U text_L92[]={'T','o','t','a','l',' ','p','r','i','c','e',' ','L','i','t','e','r',' ', '9','2',':',' '};

    INT8U total_price_95_arr[MAX_DIGITS_PRICE];
    INT8U total_liter_95_arr[MAX_DIGITS_LITER];
    INT8U text_B95[]={'T','o','t','a','l',' ','p','r','i','c','e',' ','F','u','e','l',' ', '9','5', ':',' '};
    INT8U text_L95[]={'T','o','t','a','l',' ','p','r','i','c','e',' ','L','i','t','e','r',' ', '9','5',':',' '};

    INT8U total_price_E10_arr[MAX_DIGITS_PRICE];
    INT8U total_liter_E10_arr[MAX_DIGITS_LITER];
    INT8U text_BE10[]={'T','o','t','a','l',' ','p','r','i','c','e',' ','F','u','e','l',' ', 'E','1','0', ':',' '};
    INT8U text_LE10[]={'T','o','t','a','l',' ','p','r','i','c','e',' ','L','i','t','e','r',' ','E', '1','0',':',' '};

    INT8U total_price_arr[MAX_DIGITS_TOTAL];
    INT8U text_total[]={'T','o','t','a','l',' ','p','r','i','c','e', ':',' '};

    Float_to_String(total_price_92_arr,B92);
    Float_to_String(total_price_95_arr,B95);
    Float_to_String(total_price_E10_arr,BE10);
    Float_to_String(total_liter_92_arr,L92);
    Float_to_String(total_liter_95_arr,L95);
    Float_to_String(total_liter_E10_arr,LE10);
    Float_to_String(total_price_arr,total);

    for(i=0;i<21;i++)
    {
        s = text_B92[i];
        xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
    }

    for(i=0;i<MAX_DIGITS_PRICE;i++)
    {
        s = total_price_92_arr[i];
        xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
    }

    s = 0x0A;
    xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);

    for(i=0;i<21;i++)
    {
        s = text_B95[i];
        xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
    }

    for(i=0;i<MAX_DIGITS_PRICE;i++)
    {
        s = total_price_95_arr[i];
        xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
    }

    s = 0x0A;
    xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);

    for(i=0;i<22;i++)
    {
        s = text_BE10[i];
        xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
    }

    for(i=0;i<MAX_DIGITS_PRICE;i++)
    {
        s = total_price_E10_arr[i];
        xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
    }

    s = 0x0A;
    xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);

    for(i=0;i<13;i++)
    {
        s = text_total[i];
        xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
    }

    for(i=0;i<MAX_DIGITS_TOTAL;i++)
    {
        s = total_price_arr[i];
        xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
    }

    s = 0x0A;
    xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);

    for(i=0;i<22;i++)
   {
       s = text_L92[i];
       xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
   }

    for(i=0;i<MAX_DIGITS_LITER;i++)
    {
        s = total_liter_92_arr[i];
        xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
    }

    s = 0x0A;
    xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);

    for(i=0;i<22;i++)
   {
       s = text_L95[i];
       xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
   }

    for(i=0;i<MAX_DIGITS_LITER;i++)
    {
        s = total_liter_95_arr[i];
        xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
    }

    s = 0x0A;
    xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);

    for(i=0;i<23;i++)
   {
       s = text_LE10[i];
       xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
   }

    for(i=0;i<MAX_DIGITS_LITER;i++)
    {
        s = total_liter_E10_arr[i];
        xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
    }

    s = 0x0A;
    xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);

}

void print_accounts(INT8U num)
{
    INT8U i;
    char s;
    INT8U account_arr[128];
    INT8U acc_text[]={'A','c','c','o','u','n','t','s',':',' '};


    for(i=0;i<10;i++)
    {
        s = acc_text[i];
        xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
    }

    s = 0x0A;
    xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);

    s = num/100+'0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);

    s = (num%100)/10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);

    s = num%10 + '0';
    xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);

    s = 0x0A;
    xQueueSend(UART_TX_QUEUE_HANDLE, &s, (TickType_t) 20);
}

void print_query()
{
    float Total_fuel_Price_92=0;
    float Total_fuel_Price_95=0;
    float Total_fuel_Price_E10=0;
    float Total_fuel_Liter_92=0;
    float Total_fuel_Liter_95=0;
    float Total_fuel_Liter_E10=0;
    float Sum_Of_All=0;
    INT8U Account_purchases=0;
    INT8U i;
    for(i=0;i<log_pointer;i++)
    {
        if(po_log_data[i].Fuel_Type == Fuel_92)
        {
            Total_fuel_Price_92 += po_log_data[i].amount_paid;
            Total_fuel_Liter_92 += po_log_data[i].litres_pumped;
        }
        if(po_log_data[i].Fuel_Type == Fuel_95)
        {
            Total_fuel_Price_95 += po_log_data[i].amount_paid;
            Total_fuel_Liter_95 += po_log_data[i].litres_pumped;
        }
        else
        {
            Total_fuel_Price_E10 += po_log_data[i].amount_paid;
            Total_fuel_Liter_E10 += po_log_data[i].litres_pumped;
        }

        Sum_Of_All += po_log_data[i].amount_paid;
        if(po_log_data[i].id[0]<10)
        {
            Account_purchases++;
        }
    }
    print_prices_liters(Total_fuel_Price_92, Total_fuel_Liter_92, Total_fuel_Price_95, Total_fuel_Liter_95, Total_fuel_Price_E10, Total_fuel_Liter_E10, Sum_Of_All);
    print_accounts(Account_purchases);


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
    uint32_t tempPrice;
    uint8_t  tempFuelType;
    float temp_float_price;

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
            else if(temp_message == '2')
            {
                print_query();
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
            tempPrice = temp_message;
            state = WAIT_FOR_SECOND_BYTE;
            break;

        case WAIT_FOR_SECOND_BYTE:
            tempPrice = (tempPrice << 8) | temp_message;
            state = WAIT_FOR_THIRD_BYTE;
            break;

        case WAIT_FOR_THIRD_BYTE:
            tempPrice = (tempPrice << 8) | temp_message;
            state = WAIT_FOR_FOURTH_BYTE;
            break;

        case WAIT_FOR_FOURTH_BYTE:
//            tempPrice = (tempPrice << 8) | temp_message;
//
//            // convert to float
//            temp_float_price = ((float*)&tempPrice);
//
//            if(tempFuelType == Fuel_92)
//            {
//
//            }
//            else if(tempFuelType == Fuel_92)
//            {
//
//            }
//            else if(tempFuelType == Fuel_E10)
//            {
//
//            }
            // store the specified place
            state = IDLE;
            break;

        default:
            state = IDLE;
            break;
        }



    }

}

/****************************** End Of Module *******************************/











