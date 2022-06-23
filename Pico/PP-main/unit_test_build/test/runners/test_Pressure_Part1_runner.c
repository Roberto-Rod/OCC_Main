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
#include "MockPressure_Part2.h"
#include "MockPressure_Part3.h"
#include "MockPressure_Part4.h"
#include "MockPowerControl.h"
#include "MockTimer.h"
#include "MockDutyCycle.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_SetInitiaExternalPressureAndCheck(void);
extern void test_InitialisePressureForPumpdownAndCheck(void);
extern void test_TargetPumpDownVacuumAchievedOrNotAndCheck(void);
extern void test_GetVacuumFailForInvalidInputParameterOrSensorsNotInitialisedAndCheck(void);
extern void test_GetVacuumPassFirstTryAndCheck(void);
extern void test_GetVacuumProvidesInternalPressureWhenAsked(void);
extern void test_GetVacuumProvidesExternalPressureWhenAsked(void);
extern void test_CheckTheLeakDetectionIsActiveWhenTheReferenceBoostVoltageIs27V(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockPressure_Part2_Init();
  MockPressure_Part3_Init();
  MockPressure_Part4_Init();
  MockPowerControl_Init();
  MockTimer_Init();
  MockDutyCycle_Init();
}
static void CMock_Verify(void)
{
  MockPressure_Part2_Verify();
  MockPressure_Part3_Verify();
  MockPressure_Part4_Verify();
  MockPowerControl_Verify();
  MockTimer_Verify();
  MockDutyCycle_Verify();
}
static void CMock_Destroy(void)
{
  MockPressure_Part2_Destroy();
  MockPressure_Part3_Destroy();
  MockPressure_Part4_Destroy();
  MockPowerControl_Destroy();
  MockTimer_Destroy();
  MockDutyCycle_Destroy();
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
  UnityBegin("test_Pressure_Part1.c");
  RUN_TEST(test_SetInitiaExternalPressureAndCheck, 83);
  RUN_TEST(test_InitialisePressureForPumpdownAndCheck, 99);
  RUN_TEST(test_TargetPumpDownVacuumAchievedOrNotAndCheck, 109);
  RUN_TEST(test_GetVacuumFailForInvalidInputParameterOrSensorsNotInitialisedAndCheck, 202);
  RUN_TEST(test_GetVacuumPassFirstTryAndCheck, 246);
  RUN_TEST(test_GetVacuumProvidesInternalPressureWhenAsked, 299);
  RUN_TEST(test_GetVacuumProvidesExternalPressureWhenAsked, 357);
  RUN_TEST(test_CheckTheLeakDetectionIsActiveWhenTheReferenceBoostVoltageIs27V, 410);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
