/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: ecp.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

#ifndef _SWTIMERS_H
  #define _SWTIMERS_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/
#define TICK_TIME	5		// tick time in milli seconds.

#define MILLISEC(time_in_msec)  time_in_msec / TICK_TIME


/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
INT16U swtimer( INT8U );
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

void start_swtimer( INT8U, INT8U, INT16U );
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

void swt_ctrl(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

void init_swtimers(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

/****************************** End Of Module *******************************/
#endif

