/********************************************************************************
* File : StateMachineNre.c
*
* Description : Implements the Non Recoverable Error state for the device state
*               machine, that is turning off the device if a NRE or a battery
*               depleted condition is detected. The device cannot exit this state
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

#include "StateMachineNre.h"
#include "Pressure_Part1.h"
#include "PowerControl.h"
#include "PerformanceLogger.h"
#include "Timer.h"
#include "Assert.h"

static ErrorCode_t NonRecoverableError_OnEntry(void);

/****************************************************************************
Function Name  :  NonRecoverableError

Parameters     :  bool_t executeEntry   - TRUE if this is the first pass through this state
                  State_t *newState     - pointer to the next state, which remains NRE_E

Return Value   :  EC_OK_E

Description    :  Implements the NRE state for the device state machine.
                  The device cannot leave this state
******************************************************************************/
/*lint -e{613} Suppress: Possible use of null pointer 'newState' in argument to operator 'unary *'. */
ErrorCode_t NonRecoverableError(bool_t executeEntry, State_t *newState)
{
    ASSERT(newState != NULL);

    *newState = NRE_E;

    // Normal operations
    if (executeEntry)
    {
        NonRecoverableError_OnEntry();
    }

    return EC_OK_E;
}

/****************************************************************************
Function Name  :  NonRecoverableError_OnEntry

Parameters     :  None

Return Value   :  EC_OK_E

Description    :  Run only once on entering the state. It shuts the entire
                  device down
*****************************************************************************/
static ErrorCode_t NonRecoverableError_OnEntry(void)
{
    // Save the NRE reason in the Device Status
    uint8_t combinedStatus = (uint8_t) DeviceStatus_GetState() & 0xF;
    combinedStatus |= ((uint8_t) DeviceStatus_GetNRE_Event() & 0xF) << 4;
    PerformanceLogger_SetStatus(combinedStatus);

    //Force a write of the last performance record containing the NRE reason
    PerformanceLogger_Persist();

    // Set NRE flag in EEPROM
    PerformanceLogger_SetNRE();

    TimerCounters_Init();
    MP_SetReferenceVoltageBoost(VBOOST_REF_0V);
    MP_DisablePumpPWM();
    MP_DisableExternalPeripheralsSupply();
    MP_DisableMainCircuitPower();

    return EC_OK_E;
}
