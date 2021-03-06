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
#include "MockTimer.h"
#include "MockPump.h"
#include "MockPressure_Part1.h"
#include "MockUIInterfaces.h"
#include "MockPowerControl.h"
#include "MockStateMachineCommon.h"
#include "MockPushButton.h"
#include "MockPerformanceLogger.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_OnInitDisableStateTimerInitialiseStateVacuumAndReurnOk(void);
extern void test_PumpDownStateReturnsInvalidInputParameter(void);
extern void test_PumpDownRunsUntilReachingTargetVacuumWithVacuumReadAndPumpActivateAlternating(void);
extern void test_PumpDownDurationUpdatedWithPerformanceLogger(void);
extern void test_PumpDownRunsFor20SecondWhenPressureReachedButOutwith5SecondWindow(void);
extern void test_PumpDownRunsCannotReachTargetVacuum(void);
extern void test_PumpDownFailsToTakeVacuumReadingAndReturnsError(void);
extern void test_PumpDownDetectButtonPressAndEventuallyGoesInShutdown(void);
extern void test_PumpDownRunsButExternalPressureIncreasesCausingNoneReturnValveError(void);
extern void test_PumpDownRunnningDetectsExternalOverTemperatureEventAndEntersNRE(void);
extern void test_PumpDownRunnningDetectsInternalOverTemperatureEventAndEntersNRE(void);
extern void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntInitalise(void);
extern void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntStart(void);
extern void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntNotReady(void);
extern void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntReadFailed(void);
extern void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtInitalise(void);
extern void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtStart(void);
extern void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtNotReady(void);
extern void test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtReadFailed(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockTimer_Init();
  MockPump_Init();
  MockPressure_Part1_Init();
  MockUIInterfaces_Init();
  MockPowerControl_Init();
  MockStateMachineCommon_Init();
  MockPushButton_Init();
  MockPerformanceLogger_Init();
}
static void CMock_Verify(void)
{
  MockTimer_Verify();
  MockPump_Verify();
  MockPressure_Part1_Verify();
  MockUIInterfaces_Verify();
  MockPowerControl_Verify();
  MockStateMachineCommon_Verify();
  MockPushButton_Verify();
  MockPerformanceLogger_Verify();
}
static void CMock_Destroy(void)
{
  MockTimer_Destroy();
  MockPump_Destroy();
  MockPressure_Part1_Destroy();
  MockUIInterfaces_Destroy();
  MockPowerControl_Destroy();
  MockStateMachineCommon_Destroy();
  MockPushButton_Destroy();
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
  UnityBegin("test_StateMachinePumpDown.c");
  RUN_TEST(test_OnInitDisableStateTimerInitialiseStateVacuumAndReurnOk, 100);
  RUN_TEST(test_PumpDownStateReturnsInvalidInputParameter, 110);
  RUN_TEST(test_PumpDownRunsUntilReachingTargetVacuumWithVacuumReadAndPumpActivateAlternating, 125);
  RUN_TEST(test_PumpDownDurationUpdatedWithPerformanceLogger, 178);
  RUN_TEST(test_PumpDownRunsFor20SecondWhenPressureReachedButOutwith5SecondWindow, 196);
  RUN_TEST(test_PumpDownRunsCannotReachTargetVacuum, 251);
  RUN_TEST(test_PumpDownFailsToTakeVacuumReadingAndReturnsError, 271);
  RUN_TEST(test_PumpDownDetectButtonPressAndEventuallyGoesInShutdown, 293);
  RUN_TEST(test_PumpDownRunsButExternalPressureIncreasesCausingNoneReturnValveError, 343);
  RUN_TEST(test_PumpDownRunnningDetectsExternalOverTemperatureEventAndEntersNRE, 391);
  RUN_TEST(test_PumpDownRunnningDetectsInternalOverTemperatureEventAndEntersNRE, 415);
  RUN_TEST(test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntInitalise, 438);
  RUN_TEST(test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntStart, 461);
  RUN_TEST(test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntNotReady, 484);
  RUN_TEST(test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_IntReadFailed, 507);
  RUN_TEST(test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtInitalise, 530);
  RUN_TEST(test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtStart, 553);
  RUN_TEST(test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtNotReady, 576);
  RUN_TEST(test_PumpDownRunnningReliablePreassureAndTemperatureReadingsCantBeObtainedFromSensorsAndEnterNRE_ExtReadFailed, 599);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
