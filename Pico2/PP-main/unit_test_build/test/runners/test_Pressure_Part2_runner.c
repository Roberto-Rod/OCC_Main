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
#include "MockPressure_Part3.h"
#include "MockPerformanceLogger.h"
#include "MockStateMachine.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_TryToGetSingleDifferentialVacuumMeasurementOkAndCheck(void);
extern void test_TryToGetSingleVacuumInternalMeasurementOkAndCheck(void);
extern void test_TryToGetSingleVacuumExternalMeasurementOkAndCheck(void);
extern void test_TryToGetSingleVacuumMeasurementInvalidInputParameterAndCheck(void);
extern void test_TryToGetSingleVacuumMeasurementExternalSensorNotReadyAndCheck(void);
extern void test_TryToGetSingleVacuumMeasurementInternalSensorNotReadyAndCheck(void);
extern void test_TryToGetSingleVacuumMeasurementBothSensorsNotReadyAndCheck(void);
extern void test_TryToGetSingleVacuumMeasurementFailGettingExtPressureAndCheck(void);
extern void test_TryToGetSingleVacuumMeasurementFailGettingIntPressureAndCheck(void);
extern void test_TryToGetSingleVacuumMeasurementFailToCalculatePressureDiffAndCheck(void);
extern void test_TryToGetSingleVacuumMeasurementFailToCalculatePressureExternalTemperatureThreshholdReached(void);
extern void test_TryToGetSingleVacuumMeasurementFailToCalculatePressureInternalTemperatureThreshholdReached(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockPressure_Part3_Init();
  MockPerformanceLogger_Init();
  MockStateMachine_Init();
}
static void CMock_Verify(void)
{
  MockPressure_Part3_Verify();
  MockPerformanceLogger_Verify();
  MockStateMachine_Verify();
}
static void CMock_Destroy(void)
{
  MockPressure_Part3_Destroy();
  MockPerformanceLogger_Destroy();
  MockStateMachine_Destroy();
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
  UnityBegin("test_Pressure_Part2.c");
  RUN_TEST(test_TryToGetSingleDifferentialVacuumMeasurementOkAndCheck, 160);
  RUN_TEST(test_TryToGetSingleVacuumInternalMeasurementOkAndCheck, 191);
  RUN_TEST(test_TryToGetSingleVacuumExternalMeasurementOkAndCheck, 222);
  RUN_TEST(test_TryToGetSingleVacuumMeasurementInvalidInputParameterAndCheck, 252);
  RUN_TEST(test_TryToGetSingleVacuumMeasurementExternalSensorNotReadyAndCheck, 289);
  RUN_TEST(test_TryToGetSingleVacuumMeasurementInternalSensorNotReadyAndCheck, 306);
  RUN_TEST(test_TryToGetSingleVacuumMeasurementBothSensorsNotReadyAndCheck, 324);
  RUN_TEST(test_TryToGetSingleVacuumMeasurementFailGettingExtPressureAndCheck, 342);
  RUN_TEST(test_TryToGetSingleVacuumMeasurementFailGettingIntPressureAndCheck, 361);
  RUN_TEST(test_TryToGetSingleVacuumMeasurementFailToCalculatePressureDiffAndCheck, 379);
  RUN_TEST(test_TryToGetSingleVacuumMeasurementFailToCalculatePressureExternalTemperatureThreshholdReached, 400);
  RUN_TEST(test_TryToGetSingleVacuumMeasurementFailToCalculatePressureInternalTemperatureThreshholdReached, 420);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
