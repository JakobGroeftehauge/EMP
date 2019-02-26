/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp.h
*
* PROJECT....: Assingment 1
*
* DESCRIPTION: Setup of systicktimer
*
* Change Log: 
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190226  JGR    Module created.
*
*****************************************************************************/


/*****************************    Defines    *******************************/

#ifndef SYSTICKTIMER_H_
#define SYSTICKTIMER_H_



extern void disable_global_int();
/*****************************************************************************
*   Function : disable global interrupt
******************************************************************************/

extern void enable_global_int();
/*****************************************************************************
*   Function : Enable global interrupt
******************************************************************************/

extern void SysTickInit();
/*****************************************************************************
*   Function : Setup the systick timer  (interrupt mode)
******************************************************************************/



/****************************** End Of Module *******************************/
#endif