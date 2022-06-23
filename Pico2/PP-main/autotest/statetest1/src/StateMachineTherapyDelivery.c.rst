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
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
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

void logError ( const uint16_t errorNo );
static uint8_t errorCount1 = 0;

#define MAX_VACUUM_READ_ERROR_COUNT    ((uint8_t) 20)

static bool_t  PumpOn                  = FALSE;
static uint8_t targetVacuumUpdateCount = 0;
static uint8_t vacuumReadErrorCount    = 0;

static ErrorCode_t TherapyDelivery_OnEntry(bool_t aCurrentStateOnEntry);

extern uint16_t ExternalPressureForNRVBlockage;

/****************************************************************************
   Function Name  :  TherapyStateDeepSleepAllowed

   Parameters     :  None

   Return Value   :  bool  TRUE if in state where deep sleep is ok 
                           FALSE state where deep sleep is not ok 

   Description    :  Checks if therapy is in one of the states where the processor 
                     can safely go into sleep mode 
 *****************************************************************************/
bool_t TherapyStateDeepSleepAllowed(void)
{
    bool_t result = FALSE;

    if (DeviceStatus_GetState() == THERAPY_DELIVERY_E)
    {
        // These ticker tick are just wait states so you can goto sleep.
        if (TimerCounter_GetTimeout(STATE_MACHINE_COUNTER_E) < 9)
        {
            result = TRUE;
        }
    }

    return result;
}

/****************************************************************************
   Function Name  :  TherapyDelivery_Init

   Parameters     :  None

   Return Value   :  EC_OK or error code

   Description    :  Initialises STOPPED state
 *****************************************************************************/
ErrorCode_t TherapyDelivery_Init(void)
{
    // Initialise the Target Vacuum
    InitTherapyDeliveryVacuum();

    // Reset the update period for Target Vacuum
    targetVacuumUpdateCount = 0;

    // Reset the vacuum read error count
    vacuumReadErrorCount = 0;

    // Reset the Pump On\Off duty cycle history
    DCHistoryReset();

    // No pump on for the next DUTY_CYCLE_UPDATE_TICK_DURATION
    PumpOn = FALSE;

    return EC_OK_E;
}

void convertA ( uint16_t val );

/****************************************************************************
   Function Name  :  TherapyDelivery

   Parameters     :  None

   Return Value   :  EC_OK or error code

   Description    :  Implements the THERAPY DEMIVERY state for the device state
                  machine
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
    TherapyDelivery_OnEntry(aCurrentStateOnEntry);

    ErrorCode_t result        = EC_OK_E;
    uint16_t    currentVacuum = 0;
    State_t     tmpNextState  = THERAPY_DELIVERY_E;

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
        if ((EC_POWER_TRACKER_FREQUENCY_OUT_OF_RANGE_E == result) || (EC_VOLTAGE_OUT_OF_RANGE_E == result))
        {
            printf ( "Err 1\r");
            tmpNextState = FAULT_E;
        }
        else if (EC_BATTERY_END_OF_LIFE_E == result)
        {
             printf ( "Err 2\r");
            tmpNextState = NRE_E;
        }

        // Update the Pump On Duty Cycle and power down peripherals
        if (PumpOn)
        {
            PumpOn = FALSE;
            MP_DisableExternalPeripheralsSupply();
            // Update the Pump On Duty Cycle
            DCPumpOnUpdate();
        }
    }// End of PUMP ON

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
             printf ( "Err 3\r");
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
                 //    DeviceStatus_SetPressureSensorIsReading(FALSE);
                     printf ( "Err 4\r");
                    tmpNextState = FAULT_E;
                }
                else
                {
                    // Reset error count
                    vacuumReadErrorCount = 0;

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
            else if (MAX_VACUUM_READ_ERROR_COUNT < (++vacuumReadErrorCount))
            {
                // retry exceeded
                 printf ( "Err 5\r");
                tmpNextState = FAULT_E;
            }
            else    // SCU Log Error 
            {
                logError((8<<10)+errorCount1++); 
            }
        }

        // Update the Pump Off Duty Cycle
        DCPumpOffUpdate();

        // Start timeout for next read cycle
        TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
        TimerCounter_Start(STATE_MACHINE_COUNTER_E, (uint32_t) DUTY_CYCLE_UPDATE_TICK_DURATION);
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
   Function Name  :

   Parameters     :

   Return Value   :

   Description    :
 *****************************************************************************/
static ErrorCode_t TherapyDelivery_OnEntry(bool_t aCurrentStateOnEntry)
{
    if (aCurrentStateOnEntry)
    {
        // Start timeout for next read cycle
        TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
        TimerCounter_Start(STATE_MACHINE_COUNTER_E, (uint32_t) DUTY_CYCLE_UPDATE_TICK_DURATION);

        TherapyDelivery_Init();

        // Reset the button press event only if that was not generated in FAULT (i.e. Leak)
        if (!DeviceStatus_GetButtonPressFromLeak())
        {
            PushButton_ResetEvent();
        }
    }

    return EC_OK_E;
}
