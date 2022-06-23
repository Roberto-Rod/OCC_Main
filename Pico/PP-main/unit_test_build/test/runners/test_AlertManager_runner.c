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
#include "MockUIInterfaces.h"
#include "MockTimer.h"
#include "MockDeviceStatus.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_AlertManagerInitialise(void);
extern void test_RunAlertManagerWhenStateMachineInFaultOrUnknownStateAndCheck(void);
extern void test_RunAlertManagerWhenSwitchingBetweenDisplaySequences(void);
extern void test_RunAlertManagerWhenSwitchingToPowerDownSeq(void);
extern void test_RunAlertManagerWhenStateMachineInIdleStateAndCheck(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockUIInterfaces_Init();
  MockTimer_Init();
  MockDeviceStatus_Init();
}
static void CMock_Verify(void)
{
  MockUIInterfaces_Verify();
  MockTimer_Verify();
  MockDeviceStatus_Verify();
}
static void CMock_Destroy(void)
{
  MockUIInterfaces_Destroy();
  MockTimer_Destroy();
  MockDeviceStatus_Destroy();
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
  UnityBegin("test_AlertManager.c");
  RUN_TEST(test_AlertManagerInitialise, 143);
  RUN_TEST(test_RunAlertManagerWhenStateMachineInFaultOrUnknownStateAndCheck, 165);
  RUN_TEST(test_RunAlertManagerWhenSwitchingBetweenDisplaySequences, 280);
  RUN_TEST(test_RunAlertManagerWhenSwitchingToPowerDownSeq, 356);
  RUN_TEST(test_RunAlertManagerWhenStateMachineInIdleStateAndCheck, 421);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}