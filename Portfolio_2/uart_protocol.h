#ifndef UART_PROTOCOL_H_
#define UART_PROTOCOL_H_

/***************************** Include files *******************************/
#include "tm4c123gh6pm.h"
#include "EMP_type.h"

/*****************************    Defines    *******************************/

/********************** External declaration of Variables ******************/

/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/

extern void UARTRX (void *);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : -
******************************************************************************/
extern void UARTTX(void *pvParameters);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : -
******************************************************************************/

#endif /* UART_PROTOCOL_H_ */
