/********************************************************************************
* File : StateMachine.c
*
* Description : State Machine for Pump DOwn and Therapy Delivery
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

#include "StateMachine.h"
#include "StateMachineIdle.h"
#include "StateMachinePumpDown.h"
#include "StateMachineTherapyDelivery.h"
#include "StateMachineFault.h"
#include "StateMachineShutdown.h"
#include "StateMachineNre.h"
#include "StateMachinePOST.h"
#include "AlertManager.h"

typedef ErrorCode_t (*StateFunc_t)(bool_t, State_t *);

static State_t           currentState       = NONE_E;
static bool              isEnteringNewState = TRUE;
static const StateFunc_t StateMachine[]     = { Idle, PumpDown, TherapyDelivery, Shutdown, Fault, NonRecoverableError, POST_Run };

static ErrorCode_t updateState(State_t *existingState, bool *currentStateOnEntry, State_t newState);

/****************************************************************************
   Function Name  :  StateMachine_Init

   Parameters     :  None

   Return Value   :  EC_OK or error code

   Description    :  Initialises the device state machine putting it into IDLE
 *****************************************************************************/
ErrorCode_t StateMachine_Init(void)
{
    currentState       = POST_E;
    isEnteringNewState = TRUE;

    DeviceStatus_StateAndOnEntrySet(isEnteringNewState, currentState);

    Idle_Init();
    PumpDown_Init();
    TherapyDelivery_Init();
    POST_Init();

    return EC_OK_E;
}

/****************************************************************************
   Function Name  :  StateMachine_Enter_NRE

   Parameters     :  enteringNewState   - Run the OnEntry function

   Return Value   :  None 

   Description    :  This function forces the state machine into the NRE state.
                     This is used on a None Recovery Error and no exit strategy
                     is  needed.
 *****************************************************************************/
void StateMachine_Enter_NRE (bool_t enteringNewState)
{
    currentState = NRE_E; 
    isEnteringNewState = enteringNewState; 
    StartLEDSequence(LED_CTRL_OFF_E);
}

/****************************************************************************
   Function Name  :  StateMachine_Run

   Parameters     :  None

   Return Value   :  EC_OK or error code

   Description    :  Runs the device state machine
 *****************************************************************************/

ErrorCode_t StateMachine_Run(void)
{
    State_t newState = NONE_E;

    // run the current state
    ErrorCode_t result = StateMachine[currentState](isEnteringNewState, &newState);

    // This should be an unrecoverable error because each state should update
    // the new state variable to a valid value
    if (NONE_E == newState)
    {
        newState = FAULT_E;
    }

    // update the current state
    updateState(&currentState, &isEnteringNewState, newState);


    // if a new state is entered then update the LEDs for the new state
    if (isEnteringNewState)
    {
        switch (newState)
        {
            case  PUMP_DOWN_E:
            {
                StartLEDSequence(LED_CTRL_PUMP_DOWN_E);
            }
            break;
            case  FAULT_E:
            {
                StartLEDSequence(LED_CTRL_LEAK_E);
            }
            break;
            case  SHUT_DOWN_E:
            {
                StartLEDSequence(LED_CTRL_POWER_DOWN_E);
            }
            break;
            case NRE_E:
            {
                StartLEDSequence(LED_CTRL_OFF_E);
            }
            break;
            default:
            {
            }
            break;
        }
    }

    // Check if a button has been pressed to display a status message
    //  Need to check if the LEDs are currently flashing... if so then don't
    if (DeviceStatus_GetCheckStatusAlert())
    {
        if (checkLEDSequenceCompleted())    // LED status shows previous
        {
            StartLEDSequence(LED_CTRL_GOOD_STATUS_E);
        }

        DeviceStatus_SetCheckStatusAlert(FALSE);
    }

    return result;
}

/****************************************************************************
   Function Name  :  UpdateState

   Parameters     : State_t * existingState    - Current state to be set to
                                                 the a new state
                    bool * CurrentStateOnEntry - Current state on entry
                                                 condition to be updated to
                                                 a new state on entry condition
                                                 the a new state
                    State_t newState           - New state device state machine

   Return Value   :  EC_OK or error code

   Description    :  Updates state for the device state machine
 *****************************************************************************/
/*lint -e{613} Suppress: Possible use of null pointer 'existingState', 'currentStateOnEntry' in argument to operator 'unary *'. */
static ErrorCode_t updateState(State_t *existingState, bool *currentStateOnEntry, State_t newState)
{
    ErrorCode_t result = EC_OK_E;

    // Check input parameters
    if ((NULL == existingState) || (NULL == currentStateOnEntry) || (NONE_E == newState))
    {
        result = EC_INVALID_INPUT_PARAMETER_E;
    }

    if (EC_OK_E == result)
    {
        switch (newState)
        {
            case IDLE_E:
            case PUMP_DOWN_E:
            case THERAPY_DELIVERY_E:
            case SHUT_DOWN_E:
            case FAULT_E:
            case NRE_E:
            case POST_E:
            {
                if (newState != *existingState)
                {
                    *currentStateOnEntry = TRUE;
                }
                else
                {
                    *currentStateOnEntry = FALSE;
                }
                *existingState = newState;
            }
            break;

            default:
            {
                result = EC_UNKNOWN_STATE_E;
            }
            break;
        }

        DeviceStatus_StateAndOnEntrySet(*currentStateOnEntry, *existingState);
    }

    return result;
}
