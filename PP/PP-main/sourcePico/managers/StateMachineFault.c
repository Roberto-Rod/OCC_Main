/********************************************************************************
* File : StateMachineFault.c
*
* Description : Implements the FAULT state for the device state machine
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

#include "StateMachineFault.h"
#include "Timer.h"
#include "UIInterfaces.h"
#include "PowerControl.h"
#include "PushButton.h"
#include "Assert.h"
#include "Battery.h"

static void executeEntryIfNewState(void);

/****************************************************************************
Function Name  :  Fault

Parameters     :  bool_t aCurrentStateOnEntry   - TRUE if this is the first pass through this state
                  State_t nextState             - pointer to the next state 

Return Value   :  EC_OK_E

Description    :  Implements the Fault state for the device state machine
 *****************************************************************************/
/*lint -e{613} Suppress: Possible use of null pointer 'nextState' in argument to operator 'unary *'. */
ErrorCode_t Fault(bool_t aCurrentStateOnEntry, State_t *nextState)
{
    ASSERT(nextState != NULL);

    *nextState = FAULT_E;

    if (aCurrentStateOnEntry)
    {
        executeEntryIfNewState();
    }

    // Monitor for switch off event
    if (PushButton_IsPressed() && PushButton_IsShortPress())
    {
        *nextState = PUMP_DOWN_E;
        DeviceStatus_SetButtonPressFromLeak(TRUE);
    }
    else
    {
        if (EXPIRED_COUNTER_E == TimerCounter_Status(STATE_MACHINE_COUNTER_E))
        {
            TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
            *nextState = PUMP_DOWN_E;
        }
        else
        {
            // Set the boost reference voltage
            MP_SetReferenceVoltageBoost(MP_GetBoostDemand());

            // Wait for it to settle
            PM_Delay((uint32_t) TWENTY_MILLISECONDS_DELAY);

            // Check the boost voltage
            ErrorCode_t result = Battery_CheckVoltageBounds();
            
            // Handle voltage errors
            if (EC_VOLTAGE_OUT_OF_RANGE_E == result)
            {
                *nextState = NRE_E;
                DeviceStatus_SetNRE_Event (NRE_VDC_BRIDGE_RANGE_EVENT_E);
            }
            else if (EC_BATTERY_END_OF_LIFE_E == result)
            {
                *nextState = NRE_E;
                DeviceStatus_SetNRE_Event (NRE_BAT_EOL_EVENT_E);
            }

            // Turn off the boost voltage reference
            MP_SetReferenceVoltageBoost(VBOOST_REF_0V);
        }
    }

    return (EC_OK_E);
}

/****************************************************************************
Function Name  :  executeEntryIfNewState

Parameters     :  None 

Return Value   :  None

Description    :  Executes calls only required on first entry to Fault state 
 *****************************************************************************/
static void executeEntryIfNewState(void)
{
    // Start timeout for leaving the state
    TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
    TimerCounter_Start(STATE_MACHINE_COUNTER_E, (uint32_t) FAULT_COUNT_TICK_DURATION);

    MP_SetReferenceVoltageBoost(VBOOST_REF_0V);
    MP_DisablePumpPWM();
    MP_DisableExternalPeripheralsSupply();
    PushButton_ResetEvent();

    DeviceStatus_SetButtonPressFromLeak(FALSE);

    // Tell Logging Manager the tick is available to log
    DeviceStatus_SetPumpIsRunning(FALSE);

    // Pumping and Pressure Sensor Reading are marked as completed
    DeviceStatus_SetPressureSensorIsReading(FALSE);
}
