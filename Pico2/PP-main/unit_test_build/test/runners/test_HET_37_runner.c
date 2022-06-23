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
#include "MockHardwareInterface.h"
#include "MockPowerControl.h"
#include "MockLED.h"
#include "MockPressure_Part1.h"
#include "MockPump.h"
#include "MockI2CEEPROM.h"
#include "MockTransmit.h"
#include "Mockadc.h"
#include "MockWatchdog.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_UserCanTurnOffDeviceDuringPumpDown(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockHardwareInterface_Init();
  MockPowerControl_Init();
  MockLED_Init();
  MockPressure_Part1_Init();
  MockPump_Init();
  MockI2CEEPROM_Init();
  MockTransmit_Init();
  Mockadc_Init();
  MockWatchdog_Init();
}
static void CMock_Verify(void)
{
  MockHardwareInterface_Verify();
  MockPowerControl_Verify();
  MockLED_Verify();
  MockPressure_Part1_Verify();
  MockPump_Verify();
  MockI2CEEPROM_Verify();
  MockTransmit_Verify();
  Mockadc_Verify();
  MockWatchdog_Verify();
}
static void CMock_Destroy(void)
{
  MockHardwareInterface_Destroy();
  MockPowerControl_Destroy();
  MockLED_Destroy();
  MockPressure_Part1_Destroy();
  MockPump_Destroy();
  MockI2CEEPROM_Destroy();
  MockTransmit_Destroy();
  Mockadc_Destroy();
  MockWatchdog_Destroy();
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
  UnityBegin("test_HET_37.c");
  RUN_TEST(test_UserCanTurnOffDeviceDuringPumpDown, 71);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
