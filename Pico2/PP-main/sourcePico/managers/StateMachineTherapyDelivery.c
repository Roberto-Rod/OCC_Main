/********************************************************************************
* File : StateMachineTherapyDelivery.c
*
* Description : Implements the THERAPY DELIVERY state for the device state machine
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

#include "StateMachineTherapyDelivery.h"
#include "Timer.h"
#include "Pump.h"
#include "Pressure_Part1.h"
#include "UIInterfaces.h"
#include "PowerControl.h"
#include "DutyCycle.h"
#include "DeviceStatus.h"
#include "PushButton.h"
#include "Assert.h"

static bool_t PumpOn                    = FALSE;
static uint8_t targetVacuumUpdateCount  = 0;

static ErrorCode_t TherapyDelivery_OnEntry(void);

extern uint16_t ExternalPressureForNRVBlockage;

/****************************************************************************
   Function Name  :  TherapyDelivery_Init

   Parameters     :  None

   Return Value   :  EC_OK

   Description    :  Initialises STOPPED state
 *****************************************************************************/
ErrorCode_t TherapyDelivery_Init(void)
{
    // Initialise the Target Vacuum
    InitTherapyDeliveryVacuum();

    // Reset the update period for Target Vacuum
    targetVacuumUpdateCount = 0;

    // Reset the Pump On\Off duty cycle history
    DCHistoryReset();

    // No pump on for the next DUTY_CYCLE_UPDATE_TICK_DURATION
    PumpOn = FALSE;

    return EC_OK_E;
}

/****************************************************************************
   Function Name  :  TherapyDelivery

   Parameters     :  aCurrentStateOnEntry   - TRUE if this is the first pass through this state
                     aNewState 	            - pointer to the next state 

   Return Value   :  EC_OK or error code

   Description    :  Implements the THERAPY DEMIVERY state for the device state machine
 *****************************************************************************/
/*lint -e{613} Suppress: Possible use of null pointer 'aNewState' in argument to operator 'unary *'. */
ErrorCode_t TherapyDelivery(bool_t aCurrentStateOnEntry, State_t *aNewState)
{
    uint16_t internalPressure = 0;
    uint16_t externalPressure = 0;

    ASSERT(aNewState != NULL);
    DeviceStatus_SetPressureSensorIsReading(FALSE); //reset pressure sensor read flag in this tick

    // Initialise Therapy Delivery when running for first time
    // One off operations when entering this state for the first time
    if (aCurrentStateOnEntry)
    {
        TherapyDelivery_OnEntry();
    }

    ErrorCode_t result          = EC_OK_E;
    uint16_t    currentVacuum   = 0;
    State_t     tmpNextState    = THERAPY_DELIVERY_E;

    // Monitor for switch off event
    if (PushButton_IsPressed() && PushButton_IsLongPress())
    {
        tmpNextState = SHUT_DOWN_E;
    }
    // Deliver therapy
    else
    {
        // Enable the device status alert
        if (PUSHBUTTON_TICK_PRESSES_FOR_STATUS == PushButton_GetDepressedTickCount())
        {
            DeviceStatus_SetCheckStatusAlert(TRUE);
        }

        // Disable Main Circuit Power if no LED is ON
        if (!DeviceStatus_GetLedsOnStatus())
        {
            MP_DisableMainCircuitPower();
        }

        // Activate or deactivate the Pump
        result = PumpActivate(PumpOn);
        if (EC_POWER_TRACKER_FREQUENCY_OUT_OF_RANGE_E == result)
        {
            tmpNextState = FAULT_E;
        }
        else if (EC_VOLTAGE_OUT_OF_RANGE_E == result)
        {
            tmpNextState = NRE_E;
            DeviceStatus_SetNRE_Event (NRE_VDC_BRIDGE_RANGE_EVENT_E);
        }
        else if (EC_BATTERY_END_OF_LIFE_E == result)
        {
            tmpNextState = NRE_E;
            DeviceStatus_SetNRE_Event (NRE_BAT_EOL_EVENT_E);
        }

        // Update the Pump On Duty Cycle and power down peripherals
        if (PumpOn)
        {
            PumpOn = FALSE;
            MP_DisableExternalPeripheralsSupply();
            // Update the Pump On Duty Cycle
            DCPumpOnUpdate();
        }
    } // End of PUMP ON

    // PUMP OFF (if needed)
    if ((EC_OK_E == result) && (THERAPY_DELIVERY_E == tmpNextState) &&
        (EXPIRED_COUNTER_E == TimerCounter_Status(STATE_MACHINE_COUNTER_E)))
    {
        // Increment the counter for updating the Target Vacuum
        targetVacuumUpdateCount++;

        // Calculate all the duty cycle statistics up until now
        DCCalculateAll();

        // Check for LEAK
        if (isTherapyDeliveryLeakDetected())
        {
            tmpNextState = FAULT_E;
        }
        else
        {
            // Read the vacuum
            result = GetVacuum(&internalPressure, &externalPressure, &currentVacuum);
            DeviceStatus_SetPressureSensorIsReading(TRUE); //let others know pressure sensor is being read in this tick

            // and state is correct
            if (EC_OK_E == result)
            {
                // Good reading has taken place so check if the external pressure is
                // higher which will cause NRV error
                if (externalPressure > ExternalPressureForNRVBlockage)
                {
                    tmpNextState = FAULT_E;
                }
                else
                {
                    // Vacuum too low, Pump on in the next cycle
                    if (!isTargetTherapyDeliveryVacuumAchieved(currentVacuum))
                    {
                        PumpOn = TRUE;
                    }

                    // Update Target Vacuum
                    if (THERAPY_DELIVERY_TARGET_VACCUM_UPDATE_PERIOD_SECONDS == targetVacuumUpdateCount)
                    {
                        TherapyDeliveryTargetVacuumUpdate();
                        targetVacuumUpdateCount = 0;
                    }
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

        // Update the Pump Off Duty Cycle
        DCPumpOffUpdate();

        // Start timeout for next read cycle
        TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
        TimerCounter_Start(STATE_MACHINE_COUNTER_E, (uint32_t)DUTY_CYCLE_UPDATE_TICK_DURATION);
    } // End of PUMP OFF

    // Cleanup state when moving to a different state
    if (THERAPY_DELIVERY_E != tmpNextState)
    {
        TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
    }

    // Update the next state if possible
    *aNewState = tmpNextState;

    return result;
}

/****************************************************************************
   Function Name  : TherapyDelivery_OnEntry

   Parameters     : None    

   Return Value   : EC_OK

   Description    : Executed commands only required on the first entry to TherapyDelivery
 *****************************************************************************/
static ErrorCode_t TherapyDelivery_OnEntry(void)
{
    // Start timeout for next read cycle
    TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
    TimerCounter_Start(STATE_MACHINE_COUNTER_E, (uint32_t)DUTY_CYCLE_UPDATE_TICK_DURATION);

    TherapyDelivery_Init();

    // Reset the button press event only if that was not generated in FAULT (i.e. Leak)
    if (!DeviceStatus_GetButtonPressFromLeak())
    {
        PushButton_ResetEvent();
    }

    return EC_OK_E;
}
