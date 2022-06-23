/********************************************************************************
* File : StateMachineIdle.c
*
* Description : Implements the IDLE state for the device state machine
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

#include "StateMachineIdle.h"
#include "PushButton.h"
#include "PowerControl.h"
#include "HardwareInterface.h"
#include "Pressure_Part1.h"
#include "Timer.h"
#include "Assert.h"

#define IDLE_STATE_PRESSURE_ZERO    (0)
#define ONE_HOUR_TICK_DURATION      (36000u) // i.e. 60 minutes at 10 ticks per second = 3600

static ErrorCode_t Idle_OnEntry(void);

/****************************************************************************
Function Name  :  Idle_Init

Parameters     :  None

Return Value   :  EC_OK_E

Description    :  Initialises IDLE state
 *****************************************************************************/
ErrorCode_t Idle_Init(void)
{
    ErrorCode_t result = EC_OK_E;
    return result;
}

/****************************************************************************
Function Name  :  Idle

Parameters     :  bool_t executeEntry   - TRUE if this is the first pass through this state
                  State_t newState      - pointer to the next state 

Return Value   :  EC_OK_E

Description    :  Implements the IDLE state for the device state machine
 *****************************************************************************/
/*lint -e{613} Suppress: Possible use of null pointer 'newState' in argument to operator 'unary *'. */
ErrorCode_t Idle(bool_t executeEntry, State_t *newState)
{
    ASSERT(newState != NULL);

    *newState = IDLE_E;

    // Normal operations
    if (executeEntry)
    {
        Idle_OnEntry();
    }

    if (PushButton_IsPressed())
    {
        if (PushButton_IsShortPress())
        {
            HardwareInterface_SystemInitialise();
            TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
            *newState = PUMP_DOWN_E;
        }
    }
    else if (EXPIRED_COUNTER_E == TimerCounter_Status(STATE_MACHINE_COUNTER_E))
    {
        HardwareInterface_SystemInitialise();
        TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
        *newState = PUMP_DOWN_E;
    }
    else
    {
        MP_DisablePeripheral();
        // Button is not pressed: go to sleep or deep sleep depending on
        // the device status flag
        if (DeviceStatus_isGoingInDeepSleep())
        {
            MP_DeepSleep();
        }
    }

    return EC_OK_E;
}

/****************************************************************************
Function Name  :  Idle_OnEntry

Parameters     :  None

Return Value   :  EC_OK_E

Description    :  Executes calls only required on first entry to Idle state 
*****************************************************************************/
static ErrorCode_t Idle_OnEntry(void)
{
    TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
    TimerCounter_Start(STATE_MACHINE_COUNTER_E, (uint32_t) ONE_HOUR_TICK_DURATION);

    MP_SetReferenceVoltageBoost(VBOOST_REF_0V);
    MP_DisablePumpPWM();
    MP_DisableExternalPeripheralsSupply();
    MP_DisableMainCircuitPower();
    SetInitialExternalPressure((uint32_t) IDLE_STATE_PRESSURE_ZERO);

    // Reset the tracking of short and long button presses
    PushButton_ResetEvent();
    DeviceStatus_SetButtonPressFromLeak(FALSE);

    // Tell Logging Manager the tick is available to log
    DeviceStatus_SetPumpIsRunning(FALSE);

    return EC_OK_E;
}
