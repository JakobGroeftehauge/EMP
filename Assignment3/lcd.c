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

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"
#include "lcd.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/



/*****************************   Functions   *******************************/

void port_init(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    uint8_t dummy;

    // Enable clock to port
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC;

    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;

    // Do a dummy read to insert a few cycles after enabling the peripheral.
    dummy = SYSCTL_RCGC2_R;

    // set PC4-PC7 as output
    GPIO_PORTC_DIR_R = 0xF0;

    // enable
    GPIO_PORTC_DEN_R = 0xF0;

    // set PD2-PD3 as output
    GPIO_PORTD_DIR_R = 0x0C;

    // enable
    GPIO_PORTD_DEN_R = 0x0C;


}

void write_data(uint8_t data)
{
     GPIO_PORTD_DATA_R &= ~(0x0C);
     GPIO_PORTC_DATA_R &= ~(0xF0);
     GPIO_PORTC_DATA_R |= (data & 0xF0);
     //set enable
     GPIO_PORTD_DATA_R |= (0x08);

     delay(2);
     // clear RS and enable
     GPIO_PORTD_DATA_R &= ~(0x0C);
     GPIO_PORTC_DATA_R &= ~(0xF0);
     GPIO_PORTC_DATA_R |= ((data & 0x0F)<<4);
     //set enable
     GPIO_PORTD_DATA_R |= (0x08);
}



void lcd_init(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    port_init();

    // Clear high bits
    GPIO_PORTC_DATA_R &= ~(0xF0);

    // Reset enable
    GPIO_PORTD_DATA_R &= ~(0x0C);

    delay(10);
    // Set high bits
    GPIO_PORTC_DATA_R &= ~(0xF0);
    GPIO_PORTC_DATA_R |= 0x30;

    //set enable
    GPIO_PORTD_DATA_R |= (0x08);


    delay(2);
    // clear RS and enable
    GPIO_PORTD_DATA_R &= ~(0x0C);
    GPIO_PORTC_DATA_R |= 0x30;

    //set enable
    GPIO_PORTD_DATA_R |= (0x08);

    delay(2);
    // clear RS and enable
    GPIO_PORTD_DATA_R &= ~(0x0C);
    GPIO_PORTC_DATA_R |= 0x30;

    //set enable
    GPIO_PORTD_DATA_R |= (0x08);

    delay(2);
    // clear RS and enable
    GPIO_PORTD_DATA_R &= ~(0x0C);

    GPIO_PORTC_DATA_R &= ~(0xF0);
    // set 4-bit mode
    GPIO_PORTC_DATA_R |= 0x20;

    //set enable
    GPIO_PORTD_DATA_R |= (0x08);

//------------------------- STEP 5 ---------------------------------
    delay(2);
    write_data(0x28);

//------------------------- STEP 6 ---------------------------------
    delay(2);
    write_data(0x08);

 //------------------------ STEP 7 ----------------------------------
    delay(2);
     write_data(0x0C);

 //------------------------ STEP 8 ----------------------------------
    delay(2);
    write_data(0x06);

 //------------------------ STEP 9 ----------------------------------
     delay(2);
     write_data(0x01);
}


/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
void return_home()
{
    write_data(0x02);
}

void shift_cursor(uint8_t total_shift, uint8_t direction)
{
    uint8_t shifts;
    for( shifts = 0; shifts < total_shift; shifts++ )
    {
       delay(2);
       write_data(0x10 | (direction << 2));
    }
}

void set_cursor(uint8_t position)
{
    delay(2);
    return_home();
    shift_cursor(position, RIGHT_SHIFT);
}

void clear_display()
{
    write_data(0x01);
}

void send_H()
{
    delay(2);
     // clear RS and enable
     GPIO_PORTD_DATA_R &= ~(0x0C);
     GPIO_PORTC_DATA_R &= ~(0xF0);

     GPIO_PORTD_DATA_R |= 0x04;
     GPIO_PORTC_DATA_R |= 0x40;
     //set enable
     GPIO_PORTD_DATA_R |= (0x08);

     delay(2);
     // clear RS and enable
     GPIO_PORTD_DATA_R &= ~(0x0C);
     GPIO_PORTC_DATA_R &= ~(0xF0);

     GPIO_PORTD_DATA_R |= 0x04;
     GPIO_PORTC_DATA_R |= 0x80;
     //set enable
     GPIO_PORTD_DATA_R |= (0x08);

     delay(2);
     GPIO_PORTD_DATA_R &= ~(0x0C);
}

/****************************** End Of Module *******************************/











