
#include <stdbool.h>
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"


uint32_t SystemCoreClock = 50000000;

void setupHardware(void)
{
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    //
    // Do a dummy read to insert a few cycles after enabling the peripheral.
    //
    volatile uint32_t ui32Loop;
    ui32Loop = SYSCTL_RCGC2_R;
    ui32Loop = 500;
    SystemCoreClock = ui32Loop; // keeps compiler happy
                                // set properly below..

    //
    // Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIO_PORTF_DIR_R = (1<<3);
    GPIO_PORTF_DEN_R = (1<<3); 
    
    //
    // Set the clocking to run at (SYSDIV_2_5) 80.0 MHz from the PLL.
    //                            (SYSDIV_3) 66.6 MHz     
    //                            (SYSDIV_4) 50.0 MHz     
    //                            (SYSDIV_5) 40.0 MHz     
    //                            (SYSDIV_6) 33.3 MHz     
    //                            (SYSDIV_8) 25.0 MHz     
    //                            (SYSDIV_10) 20.0 MHz     
    //
    SystemCoreClock = 80000000;  // Required for FreeRTOS.
    
    SysCtlClockSet( SYSCTL_SYSDIV_2_5 | 
                    SYSCTL_USE_PLL | 
                    SYSCTL_XTAL_16MHZ | 
                    SYSCTL_OSC_MAIN);
                    
}
    

static int ledState = 0;

void mainTOGGLE_LED(void)
{
    if (ledState)
    {
        //
        // Turn off the LED.
        //
        GPIO_PORTF_DATA_R &= ~(1<<3);
        ledState = 0;
    }
    else
    {
        //
        // Turn on the LED.
        //
        GPIO_PORTF_DATA_R |= (1<<3);    
        ledState = 1;
    }
        
   
}
