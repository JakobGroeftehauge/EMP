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

void add_to_log(INT8U log_no,
                INT8U* id,
                float* amount_paid,
                float* Price,
                float* litres_pumped,
                INT8U* Time_sec,
                INT8U* Time_min,
                INT8U* Time_hour,
                INT8U* Fuel_Type
                );

void vControl_task(void *pvParameters);
void vClear_Array(INT8U *arr, INT8U size);
void Float_to_String(INT8U *arr, float number);

#endif /* SYSTEM_CONTROL_H_ */
