 /*
 * gpio.c
 *
 *  Created on: 13. mar. 2019
 *      Author: chris
 */

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "gpio.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void init_gpio(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
  uint8_t dummy;

  // Enable the GPIO port that is used for the on-board LED.
  SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOC | SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOE | SYSCTL_RCGC2_GPIOF |SYSCTL_RCGC2_GPIOA;

  // Do a dummy read to insert a few cycles after enabling the peripheral.
  dummy = SYSCTL_RCGC2_R;

  /*PORT F setup*/
  GPIO_PORTF_LOCK_R = 0x4C4F434B;  // Unlock the CR register
  GPIO_PORTF_CR_R   = 0xFF;        // Enable overwrite of PUR to FP0

  // Set the direction as output (PF1, PF2 and PF3).
  GPIO_PORTF_DIR_R = 0x0E;

  // Enable the GPIO pins for digital function (PF0, PF1, PF2, PF3, PF4).
  GPIO_PORTF_DEN_R = 0x1F;

  // Enable internal pull-up (PF0 and PF4).
  GPIO_PORTF_PUR_R = 0x11;

  /*PORT D setup*/
  // Set the direction as output (PD6).
  GPIO_PORTD_DIR_R = 0x40;
  GPIO_PORTD_DIR_R |= 0x4C;

  // Enable the GPIO pins for digital function (PD6).
  GPIO_PORTD_DEN_R = 0x40;
  GPIO_PORTD_DEN_R |= 0x4C;

  /* PORT C setup */
  GPIO_PORTC_DIR_R = 0xF0;
  GPIO_PORTC_DEN_R = 0xF0;

  /*PORT E setup */
  GPIO_PORTE_DEN_R = 0x0F;

  // SETUP PORT A as input:
  GPIO_PORTA_DIR_R = 0x00;
  GPIO_PORTA_PUR_R = 0x60;
  GPIO_PORTA_DIR_R |= 0x1C;
  GPIO_PORTA_DEN_R |= 0x1C;
  GPIO_PORTA_DEN_R |= 0xE0;

}

/****************************** End Of Module *******************************/
