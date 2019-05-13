/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: System_Control.h
*
* PROJECT....: EMP
*
* DESCRIPTION:
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190513  PC   Module created.
*
*****************************************************************************/

#ifndef SYSTEM_CONTROL_H_
#define SYSTEM_CONTROL_H_

void vControl_task(void *pvParameters);
void vClear_Array(INT8U *arr, INT8U size);

#endif /* SYSTEM_CONTROL_H_ */
