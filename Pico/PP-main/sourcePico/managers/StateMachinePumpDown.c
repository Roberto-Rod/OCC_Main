/********************************************************************************
* File : StateMachinePumpDown.c
*
* Description : Implements the PUMP DOWN state for the device state machine
*
********************************************************************************/
/* ******************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend.
 *
 * (c) 2018, 2019, 2020 Smith & Nephew Medical Ltd.
 *
 ***************************************************************************** */

#include "StateMachinePumpDown.h"
#include "Timer.h"
#include "Pump.h"
#include "Pressure_Part1.h"
#include "PushButton.h"
#include "PerformanceLogger.h"
#include "Assert.h"

static bool_t TargetPressureAchieved        = FALSE;    // TRUE if the target pressure is met during the last 5 seconds
                                                        // of pump down
static bool_t TargetPressureTimeAllowed     = FALSE;    // TRUE during for the last 5 second of pump down
static bool_t InitialPumpDownTimeRecorded   = FALSE;
static bool_t readPressure                  = FALSE;
static ErrorCode_t PumpDown_OnEntry(void);

#define TARGET_ALLOWED_COUNT_TICK_DURATION  (5 * 10)    // Last 5 seconds of pump down.

// Added to hold the NRV pressure which indicates an NRV error
// Note: This value is shared with the theapy module
uint16_t ExternalPressureForNRVBlockage     = 0;
static bool_t FirstExternalPressureRead     = FALSE;
#define NRV_THRESHOLD                           30      // This the amount in millibars that the external pressure has to rise
                                                        // to detect that a Non Return Valve error has occurred

/****************************************************************************
   Function Name  :  PumpDown_Init

   Parameters     :  None

   Return Value   :  EC_OK

   Description    :  Initialises PUMP DOWN state
 *****************************************************************************/
ErrorCode_t PumpDown_Init(void)
{
    TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
    InitPumpDownVacuum();
    readPressure = TRUE;
    return EC_OK_E;
}

/****************************************************************************
   Function Name  :  PumpDown

   Parameters     :  aCurrentStateOnEntry   - TRUE if this is the first pass through this state
                     aNewState              - pointer to the next state   

   Return Value   :  EC_OK or error code

   Description    :  Implements the PUMP DOWN state for the device state machine
 *****************************************************************************/
/*lint -e{613} Suppress: Possible use of null pointer 'aNewState' in argument to operator 'unary *'. */
ErrorCode_t PumpDown(bool_t aCurrentStateOnEntry, State_t *aNewState)
{
    ASSERT(aNewState != NULL);
    DeviceStatus_SetPressureSensorIsReading(FALSE); //reset pressure sensor read flag in this tick

    // One off operations when entering this state for the first time
    if (aCurrentStateOnEntry)
    {
        PumpDown_OnEntry();
    }

    ErrorCode_t result           = EC_OK_E;
    uint16_t    currentVacuum    = 0;
    State_t     tmpNextState     = PUMP_DOWN_E;
    uint32_t    outstandingTime  = 0;
    uint16_t    externalPressure = 0;
    uint16_t    internalPressure = 0;

    // Monitor for switch off event
    if (PushButton_IsPressed() && PushButton_IsLongPress())
    {
        tmpNextState = SHUT_DOWN_E;
    }
    else    // Proceed with Pump Down
    {
        outstandingTime = TimerCounter_GetTimeout(STATE_MACHINE_COUNTER_E);

        // Its only in the last 5 seconds of the pump down that the pressure is checked to be
        // correct.
        if (outstandingTime <= TARGET_ALLOWED_COUNT_TICK_DURATION)
        {
            TargetPressureTimeAllowed = TRUE;
        }

        // Normal operations. If the outstanding time is zero then the timer has expired
        if (outstandingTime != 0)
        {
            // Activate the PUMP if no pressure reading is needed
            result = PumpActivate((bool_t) (!readPressure));

            if (EC_POWER_TRACKER_FREQUENCY_OUT_OF_RANGE_E == result)
            {
                tmpNextState = FAULT_E;
            }
            else if (EC_VOLTAGE_OUT_OF_RANGE_E == result)
            {
                tmpNextState = NRE_E;
                DeviceStatus_SetNRE_Event(NRE_VDC_BRIDGE_RANGE_EVENT_E);
            }
            else if (EC_BATTERY_END_OF_LIFE_E == result)
            {
                tmpNextState = NRE_E;
                DeviceStatus_SetNRE_Event(NRE_BAT_EOL_EVENT_E);
            }

            // Read the vacuum (i.e. difference between internal and
            // external pressure) if needed
            if ((EC_OK_E == result) && (readPressure))
            {
                result = GetVacuum(&internalPressure, &externalPressure, &currentVacuum);

                if (!FirstExternalPressureRead)
                {
                    FirstExternalPressureRead = TRUE;
                    // Calculate the total pressure which indicates an NRV  error
                    // As below the current external pressure plas the NRV threshold which is 30 millibars
                    ExternalPressureForNRVBlockage = externalPressure + NRV_THRESHOLD;
                }

                DeviceStatus_SetPressureSensorIsReading(TRUE);      //let others know pressure sensor is being read in this tick

                // Deal with vacuum read result
                if (EC_OK_E == result)
                {
                    if (externalPressure > ExternalPressureForNRVBlockage)
                    {
                        // External pressure has risen so its deemed that a blockage has taken place
                        tmpNextState = FAULT_E;
                    }
                    else if (isTargetPumpDownVacuumAchieved(currentVacuum))
                    {
                        // If in last 5 seconds, set the flag that pressure has been achieved
                        if (TargetPressureTimeAllowed)
                        {
                            TargetPressureAchieved = TRUE;
                        }

                        if (InitialPumpDownTimeRecorded == FALSE)
                        {
                            // Log the time, the pump down pressure is first achieved
                            uint8_t duration100Ms = (uint8_t)(PUMP_DOWN_COUNT_TICK_DURATION - outstandingTime);
                            PerformanceLogger_SetPumpDownDuration(duration100Ms);
                            InitialPumpDownTimeRecorded = TRUE;
                        }
                    }
                    else
                    {
                        // Alternate pressure readings with pump on operations
                        readPressure = (bool_t) (!readPressure);
                    }
                }
                else
                {
                    tmpNextState = NRE_E;

                    // Establish NRE reason
                    if ((EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result) ||
                        (EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E == result) ||
                        (EC_INT_PRESSURE_SENSOR_NOT_READY_E == result) ||
                        (EC_INT_PRESSURE_SENSOR_READ_FAILED_E == result))
                    {
                        DeviceStatus_SetNRE_Event(NRE_INT_SENSOR_UNRELIABLE_EVENT_E);
                    }
                    else if ((EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E == result) ||
                             (EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E == result) ||
                             (EC_EXT_PRESSURE_SENSOR_NOT_READY_E == result) ||
                             (EC_EXT_PRESSURE_SENSOR_READ_FAILED_E == result))
                    {
                        DeviceStatus_SetNRE_Event(NRE_EXT_SENSOR_UNRELIABLE_EVENT_E);
                    }
                    else if (EC_INT_TEMPERATURE_HIGH == result)
                    {
                        DeviceStatus_SetNRE_Event(NRE_INT_SENSOR_OVERHEAT_EVENT_E);
                    }
                    else if (EC_EXT_TEMPERATURE_HIGH == result)
                    {
                        DeviceStatus_SetNRE_Event(NRE_EXT_SENSOR_OVERHEAT_EVENT_E);
                    }
                    else
                    {
                        DeviceStatus_SetNRE_Event(NRE_LOGIC_FAIL_EVENT_E);
                    }
                }
            }
            else
            {
                // Alternate pressure readings with pump on operations
                readPressure = (bool_t) (!readPressure);
            }
        }
        else
        {
            // Handle the main pump down timeout. It time to decide if we can go to the therapy state
            // If pressure achieved go to therapy otherwise fault
            if (TargetPressureAchieved == TRUE)
            {
                tmpNextState = THERAPY_DELIVERY_E;
            }
            else
            {
                tmpNextState = FAULT_E;
            }
        }
    }

    // Cleanup when leaving PUMP DOWN state
    if (PUMP_DOWN_E != tmpNextState)
    {
        TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
        InitPumpDownVacuum();
        readPressure                = FALSE;
        TargetPressureAchieved      = FALSE;
        InitialPumpDownTimeRecorded = FALSE;
        TargetPressureTimeAllowed   = FALSE;
        FirstExternalPressureRead   = FALSE;
    }

    // Update the next state if possible
    *aNewState = tmpNextState;

    return result;
}

/****************************************************************************
   Function Name  :  PumpDown_OnEntry

   Parameters     :  None

   Return Value   :  EC_OK

   Description    :  Executed commands only required on the first entry to Pump Down
 *****************************************************************************/
static ErrorCode_t PumpDown_OnEntry(void)
{
    // Currently not checking the result for Timer COunter operations
    // This is safe but a result variable is available in case this changes
    TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
    TimerCounter_Start(STATE_MACHINE_COUNTER_E, (uint32_t)PUMP_DOWN_COUNT_TICK_DURATION);

    InitPumpDownVacuum();
    readPressure                = TRUE;
    TargetPressureAchieved      = FALSE;
    InitialPumpDownTimeRecorded = FALSE;
    TargetPressureTimeAllowed   = FALSE;
    FirstExternalPressureRead   = FALSE;

    // Reset the button press event only if that was not generated in FAULT (i.e. Leak)
    if (!DeviceStatus_GetButtonPressFromLeak())
    {
        PushButton_ResetEvent();
    }

    DeviceStatus_SetDeepSleepModeStatus(FALSE);

    return EC_OK_E;
}
