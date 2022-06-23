/********************************************************************************
* File : AlertManager.c
*
* Description : Manage the display of visual alerts based on the device status.
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

#include "UIInterfaces.h"
#include "Timer.h"
#include "DeviceStatus.h"
#include "AlertManager.h"


#define LED_ON_1_SECOND_IN_TICKS              (10) // multiple of 100ms
#define LED_ON_2_SECOND_IN_TICKS              (20) // multiple of 100ms

#define LED_ON_100_MILLI_SECONDS_IN_TICKS     (1)  // multiple of 100ms
#define LED_OFF_100_MILLI_SECONDS_IN_TICKS    (1)  // multiple of 100ms

// period time for 5 second flash
#define LED_FLASH_PERIOD_IN_5_SECONDS         (25) //   number of periods of 100ms on / off in 5 seconds

// after the 5 second flash, there is a 15 seconds where the
// frequency starts to decrease, this is the total time this happens
#define LED_VARY_FLASH_FREQUENCY_LENGTH    (15 * 10)   //  total length of time which flash

//
// in the pump down phase every 3 periods the frequence is decreased
//
#define LED_PERIODS_BEFORE_FREQ_DECREASE    (3)

/*lint --e{749} Suppress: local enumeration constant 'DisplaySeqAlertPhase_t::DP_PHASE_MAX_E' not referenced */
typedef enum
{
    DP_PHASE_NONE_E = 0,
    DP_PHASE_1_E,
    DP_PHASE_2_E,
    DP_PHASE_3_E,
    DP_PHASE_4_E,

    DP_PHASE_START_E,
    
    DP_PHASE_MAX_E
} DisplaySeqAlertPhase_t;


static void AlertActivate(void);

void flash_LED(void);

static DisplaySeqAlertPhase_t displaySeqAlertPhase = DP_PHASE_NONE_E;

static void AlertSetupDisable(void);

LEDControl_t ledOperation = LED_CTRL_COMPLETED_E;

/****************************************************************************
   Function Name  :  AlertManager_Init

   Parameters     :  None

   Return Value   :  None

   Description    :  Sets up the alert manager
 *****************************************************************************/
ErrorCode_t AlertManager_Init()
{
    AlertSetupDisable();

    return EC_OK_E;
}

/****************************************************************************
   Function Name  :  StateMachine_Run

   Parameters     :  None

   Return Value   :  bool  - Returns true is the current flashing sequence has been
                          otherwise false

   Description    :  Runs the device state machine
 *****************************************************************************/
bool_t checkLEDSequenceCompleted(void)
{
    bool_t completed = FALSE;

    if (ledOperation == LED_CTRL_COMPLETED_E)
    {
        completed = TRUE;
    }

    return(completed);
}

/****************************************************************************
   Function Name  :  AlertManager_Run

   Parameters     :  None

   Return Value   :  EC_OK_E

   Description    :  The alert manager is scheduled every 100ms and updates and displays
                  the LEDs depending on the current state

 *****************************************************************************/
ErrorCode_t AlertManager_Run()
{
    flash_LED();

    return(EC_OK_E);
}

/********************************************************************************
   Function Name : StartLEDSequence

   Parameters : LEDControl_t seq  This is the sequence which is to be started.

   Return Value : None

   Description : The function starts a new flash sequence. It puts the flash
   module into the state for the new sequence and then calls the function for the
   start of the sequence. A new sequence can be started at any time.

 *********************************************************************************/

void StartLEDSequence(LEDControl_t seq)
{
    ledOperation = seq;

    displaySeqAlertPhase = DP_PHASE_START_E;

    TimerCounter_Disable(LED_ALERT_COUNTER_1_E);

    flash_LED();
}

/********************************************************************************
   Function Name : flash_LED

   Parameters : None

   Return Value : None

   Description : Implements the active flashing of the LEDs. When active this function
   is called every 100ms and from a known state flashes the LEDs. This is implemented
   as a state machine.

 *********************************************************************************/
void flash_LED(void)
{
    static uint32_t periodIncrement = 0;


    // Simply switch on the current state and phase the set the LEDs
    // to the correct value

    switch (ledOperation)
    {
        case LED_CTRL_OFF_E: // OFF
        case LED_CTRL_COMPLETED_E:
        {
            UI_SetLED(LD_GREEN_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
            UI_SetLED(LD_ORANGE_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
            ledOperation = LED_CTRL_COMPLETED_E;
        }
        break;

        case LED_CTRL_GOOD_STATUS_E:
        {
            // The good status, flash the green led for one second
            if (displaySeqAlertPhase == DP_PHASE_START_E)
            {
                UI_SetLED(LD_ORANGE_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
                UI_SetLED(LD_GREEN_E, (uint32_t) LED_ON_2_SECOND_IN_TICKS, (uint32_t) LED_OFF);
                displaySeqAlertPhase = DP_PHASE_2_E;
            }
            else if ((displaySeqAlertPhase == DP_PHASE_2_E) && (UI_GetPeriodCount(LD_GREEN_E) == 1))
            {
                // this will continue to flash forever.. until main state is moved
                UI_SetLED(LD_GREEN_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
                UI_SetLED(LD_ORANGE_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);

                ledOperation = LED_CTRL_COMPLETED_E;
            }
        }
        break;

        case LED_CTRL_PUMP_DOWN_E:
        {
            // This is a long sequence and will go on to the end if everything is ok
            // If not then the state will be changed and this will cause a new sequence started
            //
            // This sequence is started by entry to the PUMP_DOWN state but when the
            // correct pressure is reached the state is changed to the THERAPY_STATE
            // but this sequence is allowed to continue. If a button is pressed in the
            // THERAPY_STATE to show status, then  a function is called to check the sequence
            // has completed.
            //

            // Pump Down Sequence is
            //
            // 1 Second Green on Only
            // 5 Seconds Green on for 100ms and off for 100ms
            //

            // start with putting the green LED on for 1 second
            if (displaySeqAlertPhase == DP_PHASE_START_E)
            {
                UI_SetLED(LD_GREEN_E, (uint32_t) LED_ON_1_SECOND_IN_TICKS, (uint32_t) LED_OFF);
                UI_SetLED(LD_ORANGE_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
                displaySeqAlertPhase = DP_PHASE_1_E;
            }
            // then flash for 5 seconds with 100mS on and 100mS off start with the 5 second
            else if ((displaySeqAlertPhase == DP_PHASE_1_E) && (UI_GetPeriodCount(LD_GREEN_E) == 1))
            {
                UI_SetLED(LD_GREEN_E, (uint32_t) LED_ON_100_MILLI_SECONDS_IN_TICKS, (uint32_t) LED_OFF_100_MILLI_SECONDS_IN_TICKS);
                UI_SetLED(LD_ORANGE_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);

                displaySeqAlertPhase = DP_PHASE_2_E;
            }
            else if (displaySeqAlertPhase == DP_PHASE_2_E)
            {
                if (UI_GetPeriodCount(LD_GREEN_E) == LED_FLASH_PERIOD_IN_5_SECONDS)
                {
                    // Now go back to 100mS on and then 100mS off
                    UI_SetLED(LD_GREEN_E, (uint32_t) LED_ON_100_MILLI_SECONDS_IN_TICKS, (uint32_t) LED_OFF_100_MILLI_SECONDS_IN_TICKS);
                    UI_SetLED(LD_ORANGE_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);

                    periodIncrement = LED_OFF_100_MILLI_SECONDS_IN_TICKS;

                    TimerCounter_Disable(LED_ALERT_COUNTER_1_E);
                    TimerCounter_Start(LED_ALERT_COUNTER_1_E, (uint32_t) LED_VARY_FLASH_FREQUENCY_LENGTH); // This is an overall timer which stop the pump down

                    displaySeqAlertPhase = DP_PHASE_3_E;
                }
            }
            else if (displaySeqAlertPhase == DP_PHASE_3_E)
            {
                // After the overall timer stop the flashing and hold the green
                // LED on for 2 second
                //
                if (EXPIRED_COUNTER_E == TimerCounter_Status(LED_ALERT_COUNTER_1_E))
                {
                    UI_SetLED(LD_GREEN_E, (uint32_t) LED_ON_2_SECOND_IN_TICKS, (uint32_t) LED_OFF);
                    UI_SetLED(LD_ORANGE_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
                    displaySeqAlertPhase = DP_PHASE_4_E;
                }
                else
                {
                    // After every 3 periods add a further 100_MILLI
                    if (UI_GetPeriodCount(LD_GREEN_E) == LED_PERIODS_BEFORE_FREQ_DECREASE)
                    {
                        // Now increase the off time after 3 periods
                        periodIncrement += LED_OFF_100_MILLI_SECONDS_IN_TICKS;

                        UI_SetLED(LD_GREEN_E, (uint32_t) LED_ON_100_MILLI_SECONDS_IN_TICKS, periodIncrement);
                        UI_SetLED(LD_ORANGE_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
                    }
                }
            }
            // check that the final 2 seconds with the green LED on has completed
            else if (displaySeqAlertPhase == DP_PHASE_4_E)
            {
                if (UI_GetPeriodCount(LD_GREEN_E) == 1)
                {
                    UI_SetLED(LD_GREEN_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
                    UI_SetLED(LD_ORANGE_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);

                    ledOperation = LED_CTRL_COMPLETED_E;
                }
            }
        }
        break;

        case LED_CTRL_POWER_DOWN_E:
        {
            // Green on for 2 s
            // Orange on for 1 s
            // Both off

            if (displaySeqAlertPhase == DP_PHASE_START_E)
            {
                UI_SetLED(LD_GREEN_E, (uint32_t) LED_ON_2_SECOND_IN_TICKS, (uint32_t) LED_OFF);
                UI_SetLED(LD_ORANGE_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
                displaySeqAlertPhase = DP_PHASE_1_E;
            }
            // Now put the orange on for 1 second
            else if ((displaySeqAlertPhase == DP_PHASE_1_E) && (UI_GetPeriodCount(LD_GREEN_E) == 1))
            {
                UI_SetLED(LD_ORANGE_E, (uint32_t) LED_ON_1_SECOND_IN_TICKS, (uint32_t) LED_OFF);
                UI_SetLED(LD_GREEN_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
                displaySeqAlertPhase = DP_PHASE_2_E;
            }
            else if ((displaySeqAlertPhase == DP_PHASE_2_E) && (UI_GetPeriodCount(LD_ORANGE_E) == 1))
            {
                UI_SetLED(LD_GREEN_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
                UI_SetLED(LD_ORANGE_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);

                ledOperation = LED_CTRL_COMPLETED_E;
            }
        }
        break;

        case LED_CTRL_LEAK_E:
        {
            //  Green is off all the time
            //  Orange on for 2 s
            //  Orange on for 2 s , off for 1.8 second continuously until changed
            //
            //  This is changed by the main finite state machine if a button is pressed
            //  or if a 60 min time out occurs.

            if (displaySeqAlertPhase == DP_PHASE_START_E)
            {
                UI_SetLED(LD_ORANGE_E, (uint32_t) LED_ON_2_SECOND_IN_TICKS, (uint32_t) LED_OFF);
                UI_SetLED(LD_GREEN_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
                displaySeqAlertPhase = DP_PHASE_2_E;
            }
            else if ((displaySeqAlertPhase == DP_PHASE_2_E) && (UI_GetPeriodCount(LD_ORANGE_E) == 1))
            {
                // this will continue to flash forever.. until main state is moved
                UI_SetLED(LD_GREEN_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
                UI_SetLED(LD_ORANGE_E, (uint32_t) LED_ON_2_SYSTEM_TICKS, (uint32_t) LED_OFF_18_SYSTEM_TICKS);
                displaySeqAlertPhase = DP_PHASE_3_E; // State will not cause any change
            }
        }
        break;

        default:
        {
        }
        break;
    }

    /* Finally update the LEDs themselves */
    AlertActivate();
}

/****************************************************************************
   Function Name  :  AlertActivate

   Parameters     :  None

   Return Value   :  None


   Description    :  Update the lower level with the correct LED values

 *****************************************************************************/
static void AlertActivate(void)
{
    // Update LED status (i.e. flash them according to the existing setup)
    // and keep the Device Status aligned
    DeviceStatus_SetLedsOnStatus(UI_UpdateLEDs());
}

/****************************************************************************
   Function Name  :  AlertSetupDisable

   Parameters     :  None

   Return Value   :  None

   Description    :  Disable the lower level and set the states to the default

 *****************************************************************************/
static void AlertSetupDisable(void)
{
    TimerCounter_Disable(LED_ALERT_COUNTER_1_E);

    displaySeqAlertPhase = DP_PHASE_NONE_E;

    ledOperation = LED_CTRL_COMPLETED_E;

    UI_SetLED(LD_GREEN_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);
    UI_SetLED(LD_ORANGE_E, (uint32_t) LED_OFF, (uint32_t) LED_OFF);

    TimerCounter_Disable(LED_ALERT_COUNTER_1_E);
}

