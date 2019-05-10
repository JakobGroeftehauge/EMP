/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: uart.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150228  MoH   Module created.
*
*****************************************************************************/

#ifndef _UART_H
  #define _UART_H

/***************************** Include files *******************************/
#include <stdint.h>
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

extern uint8_t uart0_rx_rdy();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Character ready at uart0 RX
******************************************************************************/

extern uint8_t uart0_getc();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Get character from uart0 RX
******************************************************************************/

extern uint8_t uart0_tx_rdy();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : uart0 TX buffer ready
******************************************************************************/

extern void uart0_putc( uint8_t );
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Put character to uart0 TX
******************************************************************************/

extern void uart0_init( uint32_t, uint8_t, uint8_t, uint8_t );
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initialize uart 0
******************************************************************************/

//User defined functions - 4. semester projekt
void get_uart_message(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Put character to UART queue
******************************************************************************/

/****************************** End Of Module *******************************/
#endif
