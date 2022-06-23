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
#include "MockAlertManager.h"
#include "MockStateMachineIdle.h"
#include "MockStateMachinePumpDown.h"
#include "MockStateMachinePOST.h"
#include "MockStateMachineNre.h"
#include "MockStateMachineTherapyDelivery.h"
#include "MockStateMachineShutdown.h"
#include "MockStateMachineFault.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_OnInitReturnIdleState(void);
extern void test_RunInIdleStateWithNoButtonPresses(void);
extern void test_RunInIdleStateWithError(void);
extern void test_RunInIdleStateAndGoToPumpDownStateAndTherapyDelivery(void);
extern void test_RunInPumpDownStateReturningUnknownStateAndGoToFaultState(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockAlertManager_Init();
  MockStateMachineIdle_Init();
  MockStateMachinePumpDown_Init();
  MockStateMachinePOST_Init();
  MockStateMachineNre_Init();
  MockStateMachineTherapyDelivery_Init();
  MockStateMachineShutdown_Init();
  MockStateMachineFault_Init();
}
static void CMock_Verify(void)
{
  MockAlertManager_Verify();
  MockStateMachineIdle_Verify();
  MockStateMachinePumpDown_Verify();
  MockStateMachinePOST_Verify();
  MockStateMachineNre_Verify();
  MockStateMachineTherapyDelivery_Verify();
  MockStateMachineShutdown_Verify();
  MockStateMachineFault_Verify();
}
static void CMock_Destroy(void)
{
  MockAlertManager_Destroy();
  MockStateMachineIdle_Destroy();
  MockStateMachinePumpDown_Destroy();
  MockStateMachinePOST_Destroy();
  MockStateMachineNre_Destroy();
  MockStateMachineTherapyDelivery_Destroy();
  MockStateMachineShutdown_Destroy();
  MockStateMachineFault_Destroy();
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
  UnityBegin("test_StateMachine.c");
  RUN_TEST(test_OnInitReturnIdleState, 78);
  RUN_TEST(test_RunInIdleStateWithNoButtonPresses, 87);
  RUN_TEST(test_RunInIdleStateWithError, 110);
  RUN_TEST(test_RunInIdleStateAndGoToPumpDownStateAndTherapyDelivery, 131);
  RUN_TEST(test_RunInPumpDownStateReturningUnknownStateAndGoToFaultState, 165);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}