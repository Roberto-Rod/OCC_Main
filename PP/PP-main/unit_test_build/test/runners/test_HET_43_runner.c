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
#include "MockUIInterfaces.h"
#include "MockLoggingManager.h"
#include "MockHardwareInterface.h"
#include "MockPowerControl.h"
#include "MockLED.h"
#include "MockPushButton.h"
#include "MockPressure_Part1.h"
#include "MockPump.h"
#include "Mockeusart.h"
#include "Mockadc.h"
#include "MockDutyCycle.h"
#include "MockPerformanceLogger.h"
#include "MockWatchdog.h"
#include "Mocki2c.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_TestTXHappyCase(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockAlertManager_Init();
  MockUIInterfaces_Init();
  MockLoggingManager_Init();
  MockHardwareInterface_Init();
  MockPowerControl_Init();
  MockLED_Init();
  MockPushButton_Init();
  MockPressure_Part1_Init();
  MockPump_Init();
  Mockeusart_Init();
  Mockadc_Init();
  MockDutyCycle_Init();
  MockPerformanceLogger_Init();
  MockWatchdog_Init();
  Mocki2c_Init();
}
static void CMock_Verify(void)
{
  MockAlertManager_Verify();
  MockUIInterfaces_Verify();
  MockLoggingManager_Verify();
  MockHardwareInterface_Verify();
  MockPowerControl_Verify();
  MockLED_Verify();
  MockPushButton_Verify();
  MockPressure_Part1_Verify();
  MockPump_Verify();
  Mockeusart_Verify();
  Mockadc_Verify();
  MockDutyCycle_Verify();
  MockPerformanceLogger_Verify();
  MockWatchdog_Verify();
  Mocki2c_Verify();
}
static void CMock_Destroy(void)
{
  MockAlertManager_Destroy();
  MockUIInterfaces_Destroy();
  MockLoggingManager_Destroy();
  MockHardwareInterface_Destroy();
  MockPowerControl_Destroy();
  MockLED_Destroy();
  MockPushButton_Destroy();
  MockPressure_Part1_Destroy();
  MockPump_Destroy();
  Mockeusart_Destroy();
  Mockadc_Destroy();
  MockDutyCycle_Destroy();
  MockPerformanceLogger_Destroy();
  MockWatchdog_Destroy();
  Mocki2c_Destroy();
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
  UnityBegin("test_HET_43.c");
  RUN_TEST(test_TestTXHappyCase, 131);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
