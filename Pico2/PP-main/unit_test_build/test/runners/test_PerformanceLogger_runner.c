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
#include "MockI2CEEPROM.h"
#include "MockPowerControl.h"
#include "MockTimer.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_SetInternalTemperature(void);
extern void test_SetExternalTemperature(void);
extern void test_SetDifferentialPressure(void);
extern void test_SetExternalPressure(void);
extern void test_SetPumpHistory(void);
extern void test_SetBatteryVoltage(void);
extern void test_InitResetCounter(void);
extern void test_FailedEEPROMWriteDoesNotAdvanceAddress(void);
extern void test_PersistWriteToEEPROMAndAdvanceAddress(void);
extern void test_IPDDuration(void);
extern void test_SkipToNextBlock(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockI2CEEPROM_Init();
  MockPowerControl_Init();
  MockTimer_Init();
}
static void CMock_Verify(void)
{
  MockI2CEEPROM_Verify();
  MockPowerControl_Verify();
  MockTimer_Verify();
}
static void CMock_Destroy(void)
{
  MockI2CEEPROM_Destroy();
  MockPowerControl_Destroy();
  MockTimer_Destroy();
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
  UnityBegin("test_PerformanceLogger.c");
  RUN_TEST(test_SetInternalTemperature, 67);
  RUN_TEST(test_SetExternalTemperature, 74);
  RUN_TEST(test_SetDifferentialPressure, 81);
  RUN_TEST(test_SetExternalPressure, 88);
  RUN_TEST(test_SetPumpHistory, 95);
  RUN_TEST(test_SetBatteryVoltage, 102);
  RUN_TEST(test_InitResetCounter, 109);
  RUN_TEST(test_FailedEEPROMWriteDoesNotAdvanceAddress, 125);
  RUN_TEST(test_PersistWriteToEEPROMAndAdvanceAddress, 138);
  RUN_TEST(test_IPDDuration, 189);
  RUN_TEST(test_SkipToNextBlock, 196);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
