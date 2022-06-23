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
#include "MockLED.h"
#include "MockPushButton.h"
#include "MockTimer.h"
#include "MockPowerControl.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_SetLEDToOrangeEnablesPowerAndDrivesLEDOrange(void);
extern void test_SetLEDToGreenEnablesPowerAndDrivesLEDGreen(void);
extern void test_SetLEDDisablesLEDAtOffPeriod(void);
extern void test_PushButtonPressed(void);
extern void test_FlashPattern(void);
extern void test_FlashPatternForTwoLeds(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockLED_Init();
  MockPushButton_Init();
  MockTimer_Init();
  MockPowerControl_Init();
}
static void CMock_Verify(void)
{
  MockLED_Verify();
  MockPushButton_Verify();
  MockTimer_Verify();
  MockPowerControl_Verify();
}
static void CMock_Destroy(void)
{
  MockLED_Destroy();
  MockPushButton_Destroy();
  MockTimer_Destroy();
  MockPowerControl_Destroy();
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
  UnityBegin("test_UIInterfaces.c");
  RUN_TEST(test_SetLEDToOrangeEnablesPowerAndDrivesLEDOrange, 53);
  RUN_TEST(test_SetLEDToGreenEnablesPowerAndDrivesLEDGreen, 65);
  RUN_TEST(test_SetLEDDisablesLEDAtOffPeriod, 87);
  RUN_TEST(test_PushButtonPressed, 113);
  RUN_TEST(test_FlashPattern, 122);
  RUN_TEST(test_FlashPatternForTwoLeds, 149);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
