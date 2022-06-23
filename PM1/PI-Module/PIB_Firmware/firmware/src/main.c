/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

void set_slew_rates(void){
    SRCON1A = 0xFFFF;
    SRCON1B = 0xFFFF;
    SRCON1C = 0xFFFF;
    SRCON1D = 0xFFFF;//adds greenish tint a bit
    SRCON1E = 0xFFFF;
    SRCON1F = 0xFFFF;//makes black text dark-green
    SRCON1G = 0xFFFF;
    SRCON1H = 0xFFFF;
    //SRCON1I = 0xFFFF;
    SRCON1J = 0xFFFF;
    SRCON1K = 0xFFFF;
    
    SRCON0A = 0xFFFF;
    SRCON0B = 0xFFFF;
    SRCON0C = 0xFFFF;
    SRCON0D = 0xFFFF;//looks like no effect but maybe a bit redish-yelowish
    SRCON0E = 0xFFFF;
    SRCON0F = 0xFFFF;//looks like no effect but maybe black a bit greenish-yelowish
    SRCON0G = 0xFFFF;
    SRCON0H = 0xFFFF;
    //SRCON1I = 0xFFFF;
    SRCON0J = 0xFFFF;
    SRCON0K = 0xFFFF;

    SRCON1J = 0xFFBF;
    SRCON0J = 0xFFBF;
    
    SRCON1F = 0xFFFC;
    
    SRCON1D = 0xEFFF;//some part of it add more redish tint (0xEFFF - less green)
    
    //0b 0000 0000 0000 0XX0 - they have impact on red
    SRCON0K = 0xFF9F;
    //first F 'kind of' have a bit of yellow effect on white things on LCD
    
    SRCON1Cbits.SR1C15 = 0;
    SRCON0Cbits.SR0C15 = 0;
}

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    __XC_UART = 1;

    /* Initialize all modules */
    SYS_Initialize ( NULL );
    EIB_IRQ_OutputEnable();
    
    set_slew_rates();
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();
    }

    /* Execution should not come here during normal operation */
    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

