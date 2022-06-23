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
void Auto_Voltage_End_Of_Life();
void Auto_Voltage_Out_Of_Range(void);  // xxxyyyxxx remove x and zap other
// void Auto_Failed_To_Reach_Pressure ();  // this needs to always return false .....
void Auto_Tracker_Freq_Fail(void);
// void)
void Auto_Leak_Detected(void);

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
} Test_Action_t;


struct test_entry
{
    int      test_event;
    int      test_parameter;
    uint32_t tick_delay;
};


#define SECOND_DELAY    10
#define BASE_DELAY      (600*3) // 3 minutes 


// Stress test with repeated pump downs
struct test_entry test_array[9] = {
    
    { ACTION_BUTTON_E,  3, BASE_DELAY },  // Green LED comes on for 2 second, Short Button Press, - switch on 
    { ACTION_BUTTON_E, 21, BASE_DELAY },  // LED Switch off sequence ,   Long Press Switch off, 
    { ACTION_BUTTON_E,  3, BASE_DELAY },  // Green LED comes on for 2 second, Short Button Press, 
    { ACTION_BUTTON_E, 21, BASE_DELAY },  // LED Switch off sequence ,   Long Press Switch off, 
    { ACTION_BUTTON_E,  3, BASE_DELAY },  // Green LED comes on for 2 second, Short Button Press, 
    { ACTION_BUTTON_E, 21, BASE_DELAY },  // LED Switch off sequence ,   Long Press Switch off, 
    { ACTION_BUTTON_E,  3, BASE_DELAY },  // Green LED comes on for 2 second, Short Button Press, 
    { ACTION_TRACK_FREQ_FAIL,0,(uint32_t)80*60*10},  // 80 mins wait - Cause a freq fail and wait long enough to verify auto start again 
    { ACTION_BUTTON_E, 21, BASE_DELAY*2 },  // LED Switch off sequence ,   Long Press Switch off, State Change 8  
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
            case ACTION_LEAK_E:
            {
                Auto_Leak_Detected();
            }
            break;

            case ACTION_VOLT_OUT_OF_RANGE:
            {
                Auto_Voltage_Out_Of_Range();
            }
            break;
            case ACTION_TRACK_FREQ_FAIL:
            {
                Auto_Tracker_Freq_Fail();
            }
            break;
            case ACTION_END_OF_LIFE_VOLT:
            {
                Auto_Voltage_End_Of_Life();
            }
            break;
            case ACTION_LOCAL_HANG:
            {
                // Hang the system
                for (;;)
                    ;
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
    
    // SCU some debug 
    if ( tick >= 100 ) 
    {
        tick = 0;
        tickTotal++;
        printf ("tick ");
        convertA(tick);  
    }
    tickTotal++;

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
