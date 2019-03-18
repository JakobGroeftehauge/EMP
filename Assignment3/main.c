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
* 190318  MA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "lcd.h"
#include "systick.h"


/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/



/*****************************   Functions   *******************************/

void main(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
 {
    uint8_t dummy2 = 0;

    disable_global_int();

    init_systick();

    enable_global_int();

    lcd_init();

    delay(2);
    shift_cursor(4, RIGHT_SHIFT);

    send_H();

    //shift_cursor(3, LEFT_SHIFT);
    set_cursor(10);
    delay(2);
    send_H();

    delay(100);

    write_data(0x01);
//    clear_display();

    while(1)
    {
        dummy2++;
    }

}

/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/


/****************************** End Of Module *******************************/











