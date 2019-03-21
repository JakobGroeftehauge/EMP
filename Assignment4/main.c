#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "events.h"
#include "gpio.h"
#include "systick.h"
#include "swtimers.h"
#include "tmodel.h"
#include "messages.h"
#include "uart0.h"
#include "msg_decoder.h"


INT16S alive_timer = MILLISEC(500);

int main(void)
/*****************************************************************************
*   Input    : NONE
*   Output   : Returns 0
*   Function : Init hardware and then loop forever
******************************************************************************/
{
  INT8U event;
  INT8U counter_value;

  disable_global_int();
  init_systick();
  init_gpio();
  uart0_init(19200, 8, 1,'o');
  enable_global_int();

  signal( MUTEX_SYSTEM_RTC );
  signal( MUTEX_LCD_DISPLAY );
  signal( SEM_RTC_UPDATED );
  queue_open(Q_RX);
  queue_open(Q_TX);

  // Loop forever.
  while(1)
  {
	// System part of the super loop.
	// ------------------------------
	while( !ticks );

	// The following will be executed every 5mS
	ticks--;

	if( ! --alive_timer )
	{
      alive_timer =	MILLISEC( 500 );
	  GPIO_PORTD_DATA_R ^= 0x40;
	}

    // Protected operating system mode
    swt_ctrl();

    // Application mode
    //button_task( TASK_BUTTON );

    //uart0_putc('c');

    msg_decoder_task(TASK_MSG_DEC);
    uart0_task(TASK_MSG_DEC);

    rtc_task( TASK_RTC );
    display_rtc_task( TASK_RTC_DISPLAY );
    //ajust_rtc_task( TASK_RTC_ADJUST );
    lcd_task( TASK_LCD );

  }
  return( 0 );
}
