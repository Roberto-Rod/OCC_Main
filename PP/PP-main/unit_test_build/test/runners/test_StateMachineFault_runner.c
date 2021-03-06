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
#include "MockStateMachineCommon.h"
#include "MockTimer.h"
#include "MockUIInterfaces.h"
#include "MockPowerControl.h"
#include "MockPushButton.h"
#include "MockBattery.h"
#include "Mockadc.h"
#include "MockPerformanceLogger.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_StateChecksAgainstNullPointer(void);
extern void test_OnEntryInitialiseDependencyModules(void);
extern void test_OnShortPressTransitToPumpDown(void);
extern void test_AfterSetNumberOfMinutesTransitToIPD(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockStateMachineCommon_Init();
  MockTimer_Init();
  MockUIInterfaces_Init();
  MockPowerControl_Init();
  MockPushButton_Init();
  MockBattery_Init();
  Mockadc_Init();
  MockPerformanceLogger_Init();
}
static void CMock_Verify(void)
{
  MockStateMachineCommon_Verify();
  MockTimer_Verify();
  MockUIInterfaces_Verify();
  MockPowerControl_Verify();
  MockPushButton_Verify();
  MockBattery_Verify();
  Mockadc_Verify();
  MockPerformanceLogger_Verify();
}
static void CMock_Destroy(void)
{
  MockStateMachineCommon_Destroy();
  MockTimer_Destroy();
  MockUIInterfaces_Destroy();
  MockPowerControl_Destroy();
  MockPushButton_Destroy();
  MockBattery_Destroy();
  Mockadc_Destroy();
  MockPerformanceLogger_Destroy();
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
  UnityBegin("test_StateMachineFault.c");
  RUN_TEST(test_StateChecksAgainstNullPointer, 40);
  RUN_TEST(test_OnEntryInitialiseDependencyModules, 47);
  RUN_TEST(test_OnShortPressTransitToPumpDown, 65);
  RUN_TEST(test_AfterSetNumberOfMinutesTransitToIPD, 102);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
