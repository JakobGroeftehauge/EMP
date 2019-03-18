/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: lcd.c
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
* 190318  MA    Module created.
*
*****************************************************************************/
#ifndef LCD_H_
    #define LCD_H_

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

#define RIGHT_SHIFT 1
#define LEFT_SHIFT 0

/********************** External declaration of Variables ******************/

/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/

extern void lcd_init(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : I
******************************************************************************/
extern void return_home();

extern void shift_cursor(uint8_t, uint8_t);

extern void set_cursor(uint8_t position);

extern void clear_display();

extern void send_H();

extern void write_data(uint8_t);

/****************************** End Of Module *******************************/



#endif /* LCD_H_ */
