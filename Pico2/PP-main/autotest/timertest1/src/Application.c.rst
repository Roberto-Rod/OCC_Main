/********************************************************************************
* File : Application.c
*
* Description : Main program entry point.
*
********************************************************************************/
/* ******************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend.
 *
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 *
 ***************************************************************************** */

#include "Application.h"
#include "AlertManager.h"
#include "LoggingManager.h"
#include "StateMachine.h"
#include "Timer.h"
#include "PowerControl.h"
#include "HardwareInterface.h"
#include "Watchdog.h"


// SCU print integer
uint8_t  ascii_buf[7];
 
void convertAscii ( uint16_t val )
{
    ascii_buf[5] = 0;
    for(int i=4;i>=0;i--)
    {
       ascii_buf[i]=(val%10)+0x30;
       val/=10;
    } 
    
    printf (ascii_buf);
    printf ("\r");   
}

static void Peripherals_Init(void);

/****************************************************************************
   Function Name  :  Application_Init

   Parameters     :  None

   Return Value   :  EC_OK

   Description    :  Initialise the application
 *****************************************************************************/
ErrorCode_t Application_Init(void)
{
    // initialize the device
    TimerCounters_Init();
    DeviceStatus_Init(); // keep this before any Manager initialisation
    AlertManager_Init();
    StateMachine_Init();
    Peripherals_Init();
    LoggingManager_Init();
    Watchdog_Init();

    return EC_OK_E;
}

/****************************************************************************
   Function Name  :  Application_Run

   Parameters     :  None

   Return Value   :  EC_OK

   Description    :  Run the application in 100ms loop. This waits for the next tick
                     and then executes the application functions.
 *****************************************************************************/

// SCU 
uint16_t freeCount = 0;  // Count which indicate the time free 
bool_t  powerSaving = TRUE;
uint16_t alternateCount;  // Switch between power saving and not 

ErrorCode_t Application_Run(void)
{
    // If state allows wait in sleep mode, and be woken by irq. ( timer or button )
    if ( powerSaving )  // SCU to verify power saving off 
    {

    MP_WaitForInterrupInLowPowerIfPossible();

    }
    
    // Loop until next tick occurs and then execute application functions
    
    freeCount = 0;  
    while (!PM_GetT1Flag())
    {
        freeCount++;
    }
    ;
    

    printf ("Free count ");
    convertAscii(freeCount);
    AlertManager_Run();
    StateMachine_Run();
    LoggingManager_Run();

    Watchdog_Clear();
    
    // SCU print out message if 
    if ((!powerSaving) && (freeCount < 200))
    {
        printf ( "Timer Schedule Fail\r");
    }
    else if (( freeCount != 0 ) && ( freeCount < 200 ))
    {
        // If it is ever in this range then its a fail 
        printf ( "Timer Schedule Fail1\r");
    }
    
    alternateCount++;
    if ( alternateCount > ( 60*10))
    {
        powerSaving = !powerSaving;  // switch power saving 
        if ( powerSaving)
        {
            printf ( "Power Saving On\r");
        }
        else
        {
            printf ( "Power Saving Off\r"); 
        } 
        
        alternateCount = 0;    
    }

    return EC_OK_E;
}


/****************************************************************************
   Function Name  :  Application_Stop

   Parameters     :  None

   Return Value   :  EC_OK

   Description    :  Stop the application by halting the CPU (all the peripherals
                  retain their status)and wait for the Relaxation Oscillator
                  to re-start it
 *****************************************************************************/
ErrorCode_t Application_Stop(void)
{
    if (DeviceStatus_GetState() != POST_E)
    {
        MP_SleepUntilWokenByRelaxationOscillator();
    }
    else
    {
        MP_EnableRelaxationOscillator();
    }

    return EC_OK_E;
}

/****************************************************************************
   Function Name  :  Peripherals_Init

   Parameters     :  None

   Return Value   :  None

   Description    :  Initialise all the device peripherals
 *****************************************************************************/
static void Peripherals_Init(void)
{
    HardwareInterface_SystemInitialise();
    HardwareInterface_EnableGlobalInterrupt();
    HardwareInterface_EnablePeripheralInterrupt();
}
