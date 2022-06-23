/*****************************************************************************
 *   File        : test_AlertManager.c
 *
 *   Description: Source Code for test of the Alert Manager.
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "unity.h"
#include "AlertManager.h"
#include "MockUIInterfaces.h"
#include "MockTimer.h"
#include "MockDeviceStatus.h"

#define ONE_TICK_ON_MANY_OFF_FLASHING_PATTERN                 (0x0001)
#define PUMP_DOWN_PAHSE_2_FLASHING_PATTERN_START_LENGTH       (2)
#define PUMP_DOWN_PAHSE_2_FLASHING_PATTERN_LENGTH_INCREASE    (0)
#define PUMP_DOWN_PAHSE_2_FLASHING_PATTERN_PERIODICITY        (0xFF) // i.e. for ever

#define PUMP_DOWN_PAHSE_3_FLASHING_PATTERN_START_LENGTH       (2)
#define PUMP_DOWN_PAHSE_3_FLASHING_PATTERN_LENGTH_INCREASE    (1)
#define PUMP_DOWN_PAHSE_3_FLASHING_PATTERN_PERIODICITY        (3) //

#define PUMP_DOWN_PAHSE_3_FLASHING_PATTERN_LENGTH             (2)
#define PUMP_DOWN_PAHSE_3_FLASHING_PATTERN_PERIODICITY        (3)


extern LEDControl_t ledOperation;

State_t             DeviceStatus           = NONE_E;
CounterStatus_t     LedAlertCounter1Status = UNKNOWN_STATE_E;
//CounterStatus_t LedAlertCounter2Status = UNKNOWN_STATE_E;
CounterStatus_t     ForcedStatus          = UNKNOWN_STATE_E;
bool_t              ForceCounter2         = FALSE;
bool_t              CheckDeviceStatusFlag = FALSE;
uint32_t            SetTimerCounterValue  = 0;
uint32_t            TimerDisableCount     = 0;
uint32_t            TimerEnableCount      = 0;

static State_t Stub_DeviceStatus_GetState(int NumCalls)
{
    return DeviceStatus;
}

// Stub for TimerCounter_Disable
static ErrorCode_t Stub_TimerCounter_Disable(CounterName_t TimerCounter, int NumCalls)
{
    ErrorCode_t result = EC_OK_E;

    if (LED_ALERT_COUNTER_1_E == TimerCounter)
    {
        LedAlertCounter1Status = DISABLED_COUNTER_E;
        TimerDisableCount++;
    }
    else
    {
        result = EC_TIMER_COUNT_UNAVAILABLE_E;
    }

    return result;
}

// Stub for TimerCounter_Start
static ErrorCode_t Stub_TimerCounter_Start(CounterName_t TimerCounter, uint32_t CounterValue, int NumCalls)
{
    ErrorCode_t result = EC_OK_E;

    if (LED_ALERT_COUNTER_1_E == TimerCounter)
    {
        LedAlertCounter1Status = RUNNING_COUNTER_E;
        SetTimerCounterValue   = CounterValue;
        TimerEnableCount++;
    }
    else
    {
        SetTimerCounterValue = 0;
        result               = EC_TIMER_COUNT_UNAVAILABLE_E;
    }

    return result;
}

// Stub for returning the status of a timer counter
// Note - it uses a different set of static variables from Stub_TimerCounter_Disable
//        for testing purposes
CounterStatus_t Stub_TimerCounter_Status(CounterName_t CounterName, int NumCalls)
{
    CounterStatus_t status = UNKNOWN_STATE_E;

    switch (CounterName)
    {
        case LED_ALERT_COUNTER_1_E:
        status = LedAlertCounter1Status;
        break;
        // use this if you add futher counters
        default:
        status = UNKNOWN_STATE_E;
        break;
    }

    return status;
}
void Stub_DeviceStatus_SetCheckStatusAlert(bool_t Enable, int NumCalls)
{
    CheckDeviceStatusFlag = Enable;
}

bool_t Stub_DeviceStatus_GetCheckStatusAlert(int NumCalls)
{
    return CheckDeviceStatusFlag;
}

void setUp(void)
{
    LedAlertCounter1Status = UNKNOWN_STATE_E;
    ForcedStatus           = UNKNOWN_STATE_E;
    ForceCounter2          = FALSE;
    CheckDeviceStatusFlag  = FALSE;

    TimerCounter_Disable_StubWithCallback(Stub_TimerCounter_Disable);
    TimerCounter_Start_StubWithCallback(Stub_TimerCounter_Start);
    TimerCounter_Status_StubWithCallback(Stub_TimerCounter_Status);
    DeviceStatus_GetState_StubWithCallback(Stub_DeviceStatus_GetState);
    DeviceStatus_GetCheckStatusAlert_StubWithCallback(Stub_DeviceStatus_GetCheckStatusAlert);
    DeviceStatus_SetCheckStatusAlert_StubWithCallback(Stub_DeviceStatus_SetCheckStatusAlert);
}

void tearDown(void)
{
}


// Initialise the Alert manager and check that the timers and the LEDs are disabled
void test_AlertManagerInitialise(void)
{
    UI_SetLED_Expect(LD_GREEN_E, 0, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);

    TEST_ASSERT_EQUAL_INT(EC_OK_E, AlertManager_Init());
    TEST_ASSERT_EQUAL_INT(DISABLED_COUNTER_E, LedAlertCounter1Status);


    // Verify the state is in the completed state
    TEST_ASSERT_TRUE(checkLEDSequenceCompleted());

    // Verify the operation is marked as completed
    TEST_ASSERT_EQUAL_INT(LED_CTRL_COMPLETED_E, ledOperation);
}

//
// Run the Alert manager when state machine is in LED_CTRL_OFF_E state
// and verify it is ok, then put it in PUMP DOWN and verify it is ok
// This ensures that all the surrounding functionality works ie
// timers are switched off and the correct termination states are reached
// The detailed testing of the pump down sequence is tested else where
void test_RunAlertManagerWhenStateMachineInFaultOrUnknownStateAndCheck(void)
{
    UI_SetLED_Expect(LD_GREEN_E, 0, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);

    TEST_ASSERT_EQUAL_INT(EC_OK_E, AlertManager_Init());
    TEST_ASSERT_EQUAL_INT(DISABLED_COUNTER_E, LedAlertCounter1Status);


    // Verify the state is in the completed state
    TEST_ASSERT_TRUE(checkLEDSequenceCompleted());

    TEST_ASSERT_EQUAL_INT(LED_CTRL_COMPLETED_E, ledOperation);

    //
    // Prep stage - First times it runs make sure it is in the LED_CTRL_OFF_E state
    //
    for (int i = 0; i < 10; i++)
    {
        UI_SetLED_Expect(LD_GREEN_E, 0, 0);
        UI_SetLED_Expect(LD_ORANGE_E, 0, 0);
        UI_UpdateLEDs_IgnoreAndReturn(TRUE);
        DeviceStatus_SetLedsOnStatus_Ignore();
        AlertManager_Run();

        // Verify no timers are enabled
        TEST_ASSERT_EQUAL_INT(DISABLED_COUNTER_E, LedAlertCounter1Status);
    }

    UI_SetLED_Expect(LD_GREEN_E, 10, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);
    StartLEDSequence(LED_CTRL_PUMP_DOWN_E);

    // Verify the state is not in the completed state
    TEST_ASSERT_FALSE(checkLEDSequenceCompleted());

    // Flash the green for 1 second completed
    UI_GetPeriodCount_ExpectAndReturn(LD_GREEN_E, 1);

    // Setup for flashing green LED for an amount of time
    UI_SetLED_Expect(LD_GREEN_E, 1, 1);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);
    AlertManager_Run();

    // Verify the state is not in the completed state
    TEST_ASSERT_FALSE(checkLEDSequenceCompleted());

    // Verify no timers are enabled
    TEST_ASSERT_EQUAL_INT(DISABLED_COUNTER_E, LedAlertCounter1Status);

    // Flash the green for 1 second completed
    UI_GetPeriodCount_ExpectAndReturn(LD_GREEN_E, 25);

    // Setup for flashing green LED for  the variable length
    // of flash time
    UI_SetLED_Expect(LD_GREEN_E, 1, 1);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);

    AlertManager_Run();

    // Verify timer is now enabled
    TEST_ASSERT_EQUAL_INT(RUNNING_COUNTER_E, LedAlertCounter1Status);

    // Timer is set for 15 seconds
    TEST_ASSERT_EQUAL_INT(150, SetTimerCounterValue);

    // Now show that 3 periods have passed
    UI_GetPeriodCount_ExpectAndReturn(LD_GREEN_E, 3);

    UI_SetLED_Expect(LD_GREEN_E, 1, 2);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);

    AlertManager_Run();


    // Now show that 3 periods have passed  and off time is increased
    UI_GetPeriodCount_ExpectAndReturn(LD_GREEN_E, 3);

    UI_SetLED_Expect(LD_GREEN_E, 1, 3);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);

    AlertManager_Run();


    // Now set the timer to time out
    LedAlertCounter1Status = EXPIRED_COUNTER_E;

    // The green LED comes on for 2 seconds
    UI_SetLED_Expect(LD_GREEN_E, 20, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);


    AlertManager_Run();

    // Verify no timers are enabled... currently expired
    TEST_ASSERT_EQUAL_INT(EXPIRED_COUNTER_E, LedAlertCounter1Status);

    // Verify the state is not in the completed state
    TEST_ASSERT_FALSE(checkLEDSequenceCompleted());

    // Now show that 3 periods have passed  and off time is increased
    UI_GetPeriodCount_ExpectAndReturn(LD_GREEN_E, 1);

    // Complete the final seconds so the LEDs go off
    UI_SetLED_Expect(LD_GREEN_E, 0, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);

    AlertManager_Run();

    // Verify the state is not in the completed state
    TEST_ASSERT_TRUE(checkLEDSequenceCompleted());
}

//
// Run the Alert manager when the display state is in LED_CTRL_OFF_E state
void test_RunAlertManagerWhenSwitchingBetweenDisplaySequences(void)
{
    UI_SetLED_Expect(LD_GREEN_E, 0, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);

    TEST_ASSERT_EQUAL_INT(EC_OK_E, AlertManager_Init());
    TEST_ASSERT_EQUAL_INT(DISABLED_COUNTER_E, LedAlertCounter1Status);


    // Verify the state is in the completed state
    TEST_ASSERT_TRUE(checkLEDSequenceCompleted());

    TEST_ASSERT_EQUAL_INT(LED_CTRL_COMPLETED_E, ledOperation);


    // Prep stage - First times it runs make sure it is in the LED_CTRL_OFF_E state
    //
    UI_SetLED_Expect(LD_GREEN_E, 0, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);
    UI_UpdateLEDs_IgnoreAndReturn(TRUE);
    DeviceStatus_SetLedsOnStatus_Ignore();
    AlertManager_Run();

    // Verify no timers are enabled
    TEST_ASSERT_EQUAL_INT(DISABLED_COUNTER_E, LedAlertCounter1Status);

    // Start a pump down
    UI_SetLED_Expect(LD_GREEN_E, 10, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);
    StartLEDSequence(LED_CTRL_PUMP_DOWN_E);


    // Verify the state is not in the completed state
    TEST_ASSERT_FALSE(checkLEDSequenceCompleted());

    TEST_ASSERT_EQUAL_INT(LED_CTRL_PUMP_DOWN_E, ledOperation);


    // Change to leak and ensure correct sequence followed
    TimerDisableCount = 0;

    UI_SetLED_Expect(LD_ORANGE_E, 20, 0);
    UI_SetLED_Expect(LD_GREEN_E, 0, 0);
    StartLEDSequence(LED_CTRL_LEAK_E);

    // Verify a timer disable has taken place
    TEST_ASSERT_EQUAL_INT(1, TimerDisableCount);

    // Verify the state is in the completed state
    TEST_ASSERT_FALSE(checkLEDSequenceCompleted());

    TEST_ASSERT_EQUAL_INT(LED_CTRL_LEAK_E, ledOperation);


    // Now disable the display
    //

    // Change to leak and ensure correct sequence followed
    TimerDisableCount = 0;

    UI_SetLED_Expect(LD_GREEN_E, 0, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);
    StartLEDSequence(LED_CTRL_OFF_E);

    TEST_ASSERT_EQUAL_INT(1, TimerDisableCount);

    // Verify the state is in the completed state
    TEST_ASSERT_TRUE(checkLEDSequenceCompleted());

    TEST_ASSERT_EQUAL_INT(LED_CTRL_COMPLETED_E, ledOperation);
}


//
// Run the Alert manager when in the power down sequence
//
void test_RunAlertManagerWhenSwitchingToPowerDownSeq(void)
{
    UI_SetLED_Expect(LD_GREEN_E, 0, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);

    TEST_ASSERT_EQUAL_INT(EC_OK_E, AlertManager_Init());
    TEST_ASSERT_EQUAL_INT(DISABLED_COUNTER_E, LedAlertCounter1Status);


    // Verify the state is in the completed state
    TEST_ASSERT_TRUE(checkLEDSequenceCompleted());

    TEST_ASSERT_EQUAL_INT(LED_CTRL_COMPLETED_E, ledOperation);


    //
    // Prep stage - First times it runs make sure it is in the LED_CTRL_OFF_E state
    //
    UI_SetLED_Expect(LD_GREEN_E, 0, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);
    UI_UpdateLEDs_IgnoreAndReturn(TRUE);
    DeviceStatus_SetLedsOnStatus_Ignore();
    AlertManager_Run();

    // Verify no timers are enabled
    TEST_ASSERT_EQUAL_INT(DISABLED_COUNTER_E, LedAlertCounter1Status);

    // Change to leak and ensure correct sequence is followed
    TimerDisableCount = 0;
    TimerEnableCount  = 0;

    // Start a power down sequence
    UI_SetLED_Expect(LD_GREEN_E, 20, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);
    StartLEDSequence(LED_CTRL_POWER_DOWN_E);


    // Verify the state is not in the completed state
    TEST_ASSERT_FALSE(checkLEDSequenceCompleted());


    // Verify in the power down state
    TEST_ASSERT_EQUAL_INT(LED_CTRL_POWER_DOWN_E, ledOperation);


    // Flash the green for 2 second completed
    UI_GetPeriodCount_ExpectAndReturn(LD_GREEN_E, 1);

    // Setup for flashing orange LED for an amount of time
    // green off
    //
    UI_SetLED_Expect(LD_ORANGE_E, 10, 0);
    UI_SetLED_Expect(LD_GREEN_E, 0, 0);
    AlertManager_Run();

    // Verify the state is in the completed state
    TEST_ASSERT_FALSE(checkLEDSequenceCompleted());

    // Verify a timer disable has taken place
    TEST_ASSERT_EQUAL_INT(1, TimerDisableCount);
    TEST_ASSERT_EQUAL_INT(0, TimerEnableCount);
}

// Run the Alert manager when state machine is IDLE state
// and check that the timers and the LEDs are disabled
void test_RunAlertManagerWhenStateMachineInIdleStateAndCheck(void)
{
    // Prep stage - Force the initial state to IDLE_E
    DeviceStatus = IDLE_E;
    UI_SetLED_Expect(LD_GREEN_E, 0, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);
    UI_UpdateLEDs_IgnoreAndReturn(TRUE);
    DeviceStatus_SetLedsOnStatus_Ignore();
    AlertManager_Init();

    // Run for first time - process IDLE_E state and stays in IDLE_E
    // Note that the timers must stay deactivated and the next state
    // (chosen as NONE_E) does not matter
    DeviceStatus = NONE_E;
    UI_SetLED_Expect(LD_GREEN_E, 0, 0);
    UI_SetLED_Expect(LD_ORANGE_E, 0, 0);
    UI_UpdateLEDs_IgnoreAndReturn(TRUE);

    TEST_ASSERT_EQUAL_INT(EC_OK_E, AlertManager_Run());
    TEST_ASSERT_EQUAL_INT(DISABLED_COUNTER_E, LedAlertCounter1Status);
}

