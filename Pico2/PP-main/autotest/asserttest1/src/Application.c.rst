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
#include "Assert.h"

static void Peripherals_Init(void);


uint8_t  buf1[7];
 
void convertA ( uint16_t val )
{
    buf1[5] = 0;
    //for(int i=4,temp=val;i>=0;i--)
     for(int i=4;i>=0;i--)
     {
        buf1[i]=(val%10)+0x30;
        val/=10;
     }
    
    printf (buf1);
    printf ("\r");    
}

// SCU  Test harness and sequences 
void Auto_Button(uint16_t ticks);


static int serial_count = 0;

static int      test_event_entry  = 0;
static uint32_t test_tick         = 0;
static int      test_active_param = 0;


typedef enum
{
    ACTION_WAIT_E = 0,
    ACTION_BUTTON_E,
    ACTION_LEAK_E,
    ACTION_VOLT_OUT_OF_RANGE,
    ACTION_END_OF_LIFE_VOLT,
    ACTION_TRACK_FREQ_FAIL,
    ACTION_LOCAL_HANG,
    ACTION_ASSERT,
} Test_Action_t;


struct test_entry
{
    int      test_event;
    int      test_parameter;
    uint32_t tick_delay;
};


#define SECOND_DELAY    10
#define BASE_DELAY      (10*10) // 10 seconds 


// Stress test with repeated pump downs
struct test_entry test_array[6] = {
    
    { ACTION_WAIT_E,0, 100 },
    { ACTION_BUTTON_E,  3, BASE_DELAY },  // Pump Down for a while 
    { ACTION_ASSERT, 0, BASE_DELAY*2 },  // Cause an assert which confirms that it has no effect 
    { ACTION_BUTTON_E,  21, BASE_DELAY*3 },  // Switch off 
    { ACTION_BUTTON_E, 3, BASE_DELAY },  // Switch on again and halfway thru the pump down cause a hang 
    { ACTION_LOCAL_HANG,  3, BASE_DELAY*100 },  // Green LED comes on for 2 second, Short Button Press, 

};

void auto_test_harness_event(void)
{
    if (test_tick > 0)
    {
        test_tick--;
    }
    else
    {
        printf ("New Entry\r");
        test_active_param = test_array[test_event_entry].test_parameter;
        test_tick         = test_array[test_event_entry].tick_delay;

        switch (test_array[test_event_entry].test_event)
        {
            case ACTION_WAIT_E:
            {
                // Do nothing other than wait
            }
            break;
            case ACTION_BUTTON_E:
            {
                Auto_Button(test_active_param);
            }
            break;
  
            break;
            case ACTION_LOCAL_HANG:
            {
                printf ("Hang\r");
                // Hang the system
                for (;;)
                    ;
            }
            break;
            case ACTION_ASSERT:
            {
                printf ("assert \r");
                ASSERT(FALSE);
                printf ("past assert\r");
            }
            break;
            
            default:
            {
            }
            break;
        }

        // next entry
        test_event_entry++;

        if (test_event_entry >= sizeof(test_array) / sizeof(test_array[0]))
        {
            printf ("Seq End\r");
            test_event_entry = 0;
        }
    }
}

uint16_t  tick = 0;
uint16_t  tickTotal = 0;

// SCU End 

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

ErrorCode_t Application_Run(void)
{
    // If state allows wait in sleep mode, and be woken by irq. ( timer or button )
    MP_WaitForInterrupInLowPowerIfPossible();

    // Loop until next tick occurs and then execute application functions
    while (!PM_GetT1Flag())
    {
    }
    ;
    
    // SCU some debug to show when system starts
    if ( tick == 0 ) 
    {
        tick = 1;
        printf ("start\r"); 
    }

    AlertManager_Run();
    auto_test_harness_event();   // Auto generate events .. SCU for running test harness
    StateMachine_Run();
    LoggingManager_Run();

    Watchdog_Clear();

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
