/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp.h
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
* 190308  MA    Module created.
*
*****************************************************************************/
#ifndef TRAFFIC_LIGHT_H_
#define TRAFFIC_LIGHT_H_

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/
#define LED_RED 1
#define LED_YELLOW 2
#define LED_GREEN 3

/*****************************   Constants   *******************************/
enum state{
    REGULAR_CYCLE,
    NORWEGIAN,
    EMERGENCY
};

/*****************************   Functions   *******************************/


/****************************** End Of Module *******************************/



#endif /* TRAFFIC_LIGHT_H_ */
