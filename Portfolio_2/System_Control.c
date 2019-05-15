/***************************** Include files *******************************/
#include "tm4c123gh6pm.h"
#include "EMP_type.h"
#include "uart_protocol.h"
#include "system_setup.h"
#include "queue.h"
#include "System_Control.h"
#include "FreeRTOS.h"
#include "lcd.h"

/*****************************    Defines    *******************************/

enum Controller_States
{
  Choose_fuel,
  Payment_Type,
  Cash,
  Account,
  Password,
  Fueling
};

#define OCTANE_92   '1'
#define OCTANE_95   '2'
#define E10_BIO     '3'

#define CASH        '1'
#define ACCOUNT     '2'

#define CONTINUE    '#'
#define ACCOUNT_ID_LENGTH 16

#define MAX_BALANCE         9999
#define MAX_BALANCE_LENGTH  7
/********************** External declaration of Variables ******************/


/****************************    Semaphores    ***************************/



/*****************************   Constants   *******************************/


/*************************  Function interfaces ****************************/
void add_to_log(INT8U log_no,
                INT8U* id,
                float* Price,
                INT16U* litres_pumped,
                INT8U* Time_sec,
                INT8U* Time_min,
                INT8U* Time_hour,
                INT8U* Fuel_Type
                )
{
    //po_log_data[log_no].id;
}

void vClear_Array(INT8U *arr, INT8U size)
{
    INT8U i;
    for(i=0;i<size;i++)
    {
        arr[i]=0;
    }
}

void Float_to_String(INT8U *arr, float number)
{
    INT32U numb = number*100 + 0.5;
    INT32U divisor = 100000;
    INT8U trailing_zero_flag = 0;
    arr[4]=',';
    for(INT8U i = 0; i<7;i++)
    {
        if(i!=4)
        {
            if(i==3)
            {
                trailing_zero_flag = 1;
            }
            if(numb/divisor!=0)
            {
                arr[i]=numb/divisor + '0';

            }
            else if(trailing_zero_flag == 0)
            {
                arr[i]=' ';
            }
            else
            {
                arr[i]= '0';
            }
            numb= numb % divisor;
            divisor = divisor/10;
        }
    }

}
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : -
******************************************************************************/
void vControl_task(void *pvParameters)
{
    INT8U Control_State = Choose_fuel;
    INT8U key_Receive;
    INT8U Cash_q_receive;
    INT16U Cash_inserted = 0;
    INT8U Account_ID[ACCOUNT_ID_LENGTH+1];
    INT8U Password_text[ACCOUNT_ID_LENGTH+1];
    INT8U Current_Price_Arr[MAX_BALANCE_LENGTH+1];
    INT8U Liter_Sum_Arr[MAX_BALANCE_LENGTH+1];
    vClear_Array(Account_ID,ACCOUNT_ID_LENGTH+1);
    vClear_Array(Password_text,ACCOUNT_ID_LENGTH+1);
    vClear_Array(Current_Price_Arr,MAX_BALANCE_LENGTH+1);
    vClear_Array(Liter_Sum_Arr,MAX_BALANCE_LENGTH+1);
    INT8U i = 0;
    for(;;)
    {
        switch(Control_State)
        {
            case Choose_fuel:

                move_LCD(0,0);
                wr_str_LCD("Choose Fuel Type");
                move_LCD(0,1);
                wr_str_LCD("1:92 2:95 3:E10");
                if(xQueueReceive(KEYBOARD_QUEUE_HANDLE,&key_Receive,50))
                {
                   if(key_Receive == OCTANE_92 || key_Receive == OCTANE_95 || key_Receive == E10_BIO)
                   {
                       Fuel_Type = key_Receive;
                       Control_State = Payment_Type;
                       clear_LCD();
                   }

                }
                break;
            case Payment_Type:
                move_LCD(0,0);
                wr_str_LCD("Choose Payment");
                move_LCD(0,1);
                wr_str_LCD("1:Cash 2:Account");
                if(xQueueReceive(KEYBOARD_QUEUE_HANDLE,&key_Receive,50))
                {
                    if(key_Receive == CASH)
                    {
                        Control_State = Cash;
                        xQueueReset(DIGI_SW_QUEUE_HANDLE);
                        clear_LCD();
                    }
                    else if(key_Receive == ACCOUNT)
                    {
                        Control_State = Account;
                        clear_LCD();
                    }

                }
                break;
            case Cash:
                move_LCD(0,0);
                wr_str_LCD("Insert Cash");

                move_LCD(12,0);
                wr_ch_LCD(Cash_inserted%10000/1000 + '0');
                wr_ch_LCD(Cash_inserted%1000/100 + '0');
                wr_ch_LCD((Cash_inserted%100)/10 + '0');
                wr_ch_LCD((Cash_inserted%10) + '0');

                move_LCD(0,1);
                wr_str_LCD("# to continue");
                if(xQueueReceive(DIGI_SW_QUEUE_HANDLE,&Cash_q_receive,50))
                {
                    if(Cash_q_receive == DSE_CCW)
                        Cash_inserted += 50;
                    else if(Cash_q_receive == DSE_CW)
                        Cash_inserted += 100;
                }

                if(xQueueReceive(KEYBOARD_QUEUE_HANDLE,&key_Receive,50))
                {
                    if(key_Receive == CONTINUE)
                    {
                        Control_State = Fueling;
                        Balance = Cash_inserted;
                        clear_LCD();
                    }
                }
                break;

            case Account:
                move_LCD(0,0);
                wr_str_LCD("Enter Account ID");
                move_LCD(0,1);
                wr_str_LCD(Account_ID);
                if(xQueueReceive(KEYBOARD_QUEUE_HANDLE,&key_Receive,50))
                {
                    if(key_Receive != CONTINUE)
                    {
                        if(i<ACCOUNT_ID_LENGTH)
                        {
                            Account_ID[i]=key_Receive;
                            i++;
                        }
                        else
                        {
                            vClear_Array(Account_ID,ACCOUNT_ID_LENGTH);
                            i=0;
                            clear_LCD();
                        }

                    }
                    else //Add check for account
                    {
                        Control_State = Password;
                        i=0;
                        clear_LCD();
                    }
                }
                break;
            case Password:
                move_LCD(0,0);
                wr_str_LCD("Enter Password");
                move_LCD(0,1);
                if(xQueueReceive(KEYBOARD_QUEUE_HANDLE,&key_Receive,50))
                {
                    if(key_Receive != CONTINUE)
                    {
                        if(i<16)
                        {

                            Password_text[i]=key_Receive;
                            move_LCD(i,1);
                            wr_ch_LCD('*');
                            i++;
                        }
                        else
                        {
                            vClear_Array(Password_text,ACCOUNT_ID_LENGTH);
                            i=0;
                            clear_LCD();
                        }
                    }
                    else //Add check for Password
                    {
                        Control_State = Fueling;
                        Balance = MAX_BALANCE;
                        i=0;
                        clear_LCD();
                    }
                }

                break;
            case Fueling:
                Float_to_String(Current_Price_Arr,Current_Price);
                Float_to_String(Liter_Sum_Arr,((float)Amount_Pumped/TICK_PER_LITER));

                move_LCD(0,0);
                wr_str_LCD("Price: ");
                move_LCD(7,0);
                wr_str_LCD(Current_Price_Arr);
                move_LCD(0,1);
                wr_str_LCD("Liter: ");
                move_LCD(7,1);
                wr_str_LCD(Liter_Sum_Arr);

                if(xSemaphoreTake(ACTIVATE_PUMP_HANDLER_SEM, 0))
                {
                    Control_State = Choose_fuel;
                    xSemaphoreGive(ACTIVATE_PUMP_HANDLER_SEM);

                    po_log_data.//Update Log
                }
                break;
            default:
                Control_State = Choose_fuel;
                break;
        }

    }

}



