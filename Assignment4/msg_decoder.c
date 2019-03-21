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
* 150228  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "tmodel.h"
#include "queue.h"

/*****************************    Defines    *******************************/
#define DS_GET_CLOCK 1
#define DS_GET_CLOCK2 2
#define DS_GET_CLOCK3 3
#define DS_GET_CLOCK4 4
#define DS_GET_CLOCK5 5
#define DS_GET_CLOCK6 6
#define DS_GET_CLOCK7 7

#define DS_SET_CLOCK 10
#define DS_SET_CLOCK1 11
#define DS_SET_CLOCK2 12
#define DS_SET_CLOCK3 13
#define DS_SET_CLOCK4 14
#define DS_SET_CLOCK5 15
#define DS_SET_CLOCK6 16

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/

void msg_decoder_task(INT8U task_no)
{
    static INT8U sec = 0;
    static INT8U min = 0;
    static INT8U hour = 0;
    static INT8U state = 0;

    switch(state)
    {
        case 0:
            if (queue_test(Q_RX))
            {
                switch(queue_get(Q_RX))
                {
                    case '1':
                        state = DS_SET_CLOCK;
                        break;
                    case '2':
                        state = DS_GET_CLOCK;
                        queue_put(Q_TX, '2');
                        break;
                    default:
                        break;
                }
            }
            break;

        case DS_SET_CLOCK:
            if (queue_test(Q_RX))
            {
                hour = 0;
                hour = (queue_get(Q_RX) - 0x30) * 10;
                state = DS_SET_CLOCK1;
            }
            break;
        case DS_SET_CLOCK1:
            if (queue_test(Q_RX))
            {
                hour = hour + (queue_get(Q_RX) - 0x30);
                state = DS_SET_CLOCK2;
            }
            break;

        case DS_SET_CLOCK2:
            if (queue_test(Q_RX))
            {
                min = 0;
                min = (queue_get(Q_RX) - 0x30) * 10;
                state = DS_SET_CLOCK3;
            }
            break;
        case DS_SET_CLOCK3:
            if (queue_test(Q_RX))
            {
                min = min + (queue_get(Q_RX) - 0x30);
                state = DS_SET_CLOCK4;
            }
            break;
        case DS_SET_CLOCK4:
            if (queue_test(Q_RX))
            {
                sec = 0;
                sec = (queue_get(Q_RX) - 0x30) * 10;
                state = DS_SET_CLOCK5;
            }
            break;
        case DS_SET_CLOCK5:
            if (queue_test(Q_RX))
            {
                sec = sec + (queue_get(Q_RX) - 0x30);
                state = DS_SET_CLOCK6;
            }
            break;
        case DS_SET_CLOCK6:
            // include mutex for system RTC
            put_msg_state( SSM_RTC_SEC, sec );
            put_msg_state( SSM_RTC_MIN, min );
            put_msg_state( SSM_RTC_HOUR, hour );
            state = 0;
            break;

        case DS_GET_CLOCK:
            // include mutex
            sec  = get_msg_state( SSM_RTC_SEC  );
            min  = get_msg_state( SSM_RTC_MIN  );
            hour = get_msg_state( SSM_RTC_HOUR );

            queue_put(Q_TX, (INT8U)(hour/10+'0'));
            queue_put(Q_TX, (INT8U)(hour%10+'0'));
            queue_put(Q_TX, (INT8U)(min/10+'0'));
            queue_put(Q_TX, (INT8U)(min%10+'0'));
            queue_put(Q_TX, (INT8U)(sec/10+'0'));
            queue_put(Q_TX, (INT8U)(sec%10+'0'));

            state=0;
            break;

    }

}


/****************************** End Of Module *******************************/












