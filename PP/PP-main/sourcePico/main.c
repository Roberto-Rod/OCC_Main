/*****************************************************************************
 *   File        : main.c
 *
 *   Description : This is the application software 'Main()' function.
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "mcc.h"
#include "Application.h"

int main(void)
{
    // Initialise the device
    Application_Init();
    
    // Run application
    while(true)
    {   
        Application_Run();
    }
    
    // End of infinite loop so should not reach here
    /*lint -e{527} Suppress: Unreachable code at token Name.*/
    return (0);
}

/**
 End of File
*/
