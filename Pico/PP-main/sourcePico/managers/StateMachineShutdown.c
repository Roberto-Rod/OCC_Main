/********************************************************************************
* File : StateMachineShutdown.c
*
* Description : Implements the STOPPED state for the device state machine
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

#include "StateMachineShutdown.h"
#include "UIInterfaces.h"
#include "PowerControl.h"
#include "Timer.h"
#include "Assert.h"

/*
 * Private Prototypes
 */
static ErrorCode_t Shutdown_OnEntry(void);

/*
 * Public Functions
 */

/****************************************************************************
Function Name  :  Stopped

Parameters     :  aCurrentStateOnEntry  - TRUE if this is the first pass through this state
                  aNewState             - pointer to the next state   

Return Value   :  EC_OK

Description    :  Implements the STOPPED state for the device state machine
*****************************************************************************/
/*lint -e{613} Suppress: Possible use of null pointer 'aNewState' in argument to operator 'unary *'. */
ErrorCode_t Shutdown(bool_t aCurrentStateOnEntry, State_t* aNewState)
{
    ASSERT(aNewState != NULL);

    // Normal operations carried out every time this state runs
    *aNewState = SHUT_DOWN_E;

    if (aCurrentStateOnEntry)
    {
        Shutdown_OnEntry();
    }

    if (EXPIRED_COUNTER_E == TimerCounter_Status(STATE_MACHINE_COUNTER_E))
    {
        *aNewState = IDLE_E;

        // do something with shutting everything down
        MP_SetReferenceVoltageBoost(VBOOST_REF_0V);
        MP_DisablePumpPWM();
        MP_DisableExternalPeripheralsSupply();
        MP_DisableMainCircuitPower();
        TimerCounters_Init();
    }

    return EC_OK_E;
}

/****************************************************************************
Function Name  :  Shutdown_OnEntry

Parameters     :  None  

Return Value   :  EC_OK

Description    :  Executed commands only required on the first entry to Shutdown
*****************************************************************************/
static ErrorCode_t Shutdown_OnEntry(void)
{
    TimerCounter_Disable(STATE_MACHINE_COUNTER_E);
    TimerCounter_Start(STATE_MACHINE_COUNTER_E, (uint32_t) SHUT_DOWN_COUNT_TICK_DURATION);

    DeviceStatus_SetDeepSleepModeStatus(FALSE);

    // Tell Logging Manager the tick is available to log
    DeviceStatus_SetPumpIsRunning(FALSE);

    return EC_OK_E;
}

/**
 End of File
 */
