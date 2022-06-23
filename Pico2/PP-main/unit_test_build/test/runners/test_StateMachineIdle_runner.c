/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Test Runner Used To Run Each Test Below=====*/
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  CMock_Init(); \
  UNITY_CLR_DETAILS(); \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT() && !TEST_IS_IGNORED) \
  { \
    tearDown(); \
    CMock_Verify(); \
  } \
  CMock_Destroy(); \
  UnityConcludeTest(); \
}

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "cmock.h"
#include <setjmp.h>
#include <stdio.h>
#include "MockPushButton.h"
#include "MockPowerControl.h"
#include "MockTimer.h"
#include "MockPressure_Part1.h"
#include "MockStateMachineCommon.h"
#include "MockHardwareInterface.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_OnInitClearSystemTimerReferenceReturnOk(void);
extern void test_IdleCheckStateReturnsInvalidParameter(void);
extern void test_OnEntryInitialiseUIAndPowerSettingAndWhenSwitchIsNotPressedGoToIdle(void);
extern void test_IdleStateRunsWhenSwitchIsPressedNotLongEnoughToSwitchOnAndStayInIdle(void);
extern void test_IdleStateRunsWhenSwitchIsPressedLongEnoughToGoIntoPumpDown(void);
extern void test_OnRunIfPushButtonIsNotPressedDisablePeripheral(void);
extern void test_IfTimerExpireGoToIPDEvenIfNoButtonIsPressed(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockPushButton_Init();
  MockPowerControl_Init();
  MockTimer_Init();
  MockPressure_Part1_Init();
  MockStateMachineCommon_Init();
  MockHardwareInterface_Init();
}
static void CMock_Verify(void)
{
  MockPushButton_Verify();
  MockPowerControl_Verify();
  MockTimer_Verify();
  MockPressure_Part1_Verify();
  MockStateMachineCommon_Verify();
  MockHardwareInterface_Verify();
}
static void CMock_Destroy(void)
{
  MockPushButton_Destroy();
  MockPowerControl_Destroy();
  MockTimer_Destroy();
  MockPressure_Part1_Destroy();
  MockStateMachineCommon_Destroy();
  MockHardwareInterface_Destroy();
}

/*=======Test Reset Option=====*/
void resetTest(void);
void resetTest(void)
{
  CMock_Verify();
  CMock_Destroy();
  tearDown();
  CMock_Init();
  setUp();
}


/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_StateMachineIdle.c");
  RUN_TEST(test_OnInitClearSystemTimerReferenceReturnOk, 54);
  RUN_TEST(test_IdleCheckStateReturnsInvalidParameter, 59);
  RUN_TEST(test_OnEntryInitialiseUIAndPowerSettingAndWhenSwitchIsNotPressedGoToIdle, 65);
  RUN_TEST(test_IdleStateRunsWhenSwitchIsPressedNotLongEnoughToSwitchOnAndStayInIdle, 88);
  RUN_TEST(test_IdleStateRunsWhenSwitchIsPressedLongEnoughToGoIntoPumpDown, 107);
  RUN_TEST(test_OnRunIfPushButtonIsNotPressedDisablePeripheral, 121);
  RUN_TEST(test_IfTimerExpireGoToIPDEvenIfNoButtonIsPressed, 133);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
