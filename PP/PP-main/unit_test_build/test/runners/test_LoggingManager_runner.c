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
#include "MockStateMachine.h"
#include "MockPerformanceLogger.h"
#include "MockBattery.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_Initialise(void);
extern void test_LogEveryMinuteWhenNotIdle(void);
extern void test_NoLoggingIfPumpIsRunning(void);
extern void test_NoLoggingIfPressureSensorReadingIsPerformed(void);
extern void test_SkipLoggingWhenStateIsIdle(void);
extern void test_LogEveryMinuteButEnterNREWhenEEPROMFull(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockStateMachine_Init();
  MockPerformanceLogger_Init();
  MockBattery_Init();
}
static void CMock_Verify(void)
{
  MockStateMachine_Verify();
  MockPerformanceLogger_Verify();
  MockBattery_Verify();
}
static void CMock_Destroy(void)
{
  MockStateMachine_Destroy();
  MockPerformanceLogger_Destroy();
  MockBattery_Destroy();
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
  UnityBegin("test_LoggingManager.c");
  RUN_TEST(test_Initialise, 34);
  RUN_TEST(test_LogEveryMinuteWhenNotIdle, 42);
  RUN_TEST(test_NoLoggingIfPumpIsRunning, 70);
  RUN_TEST(test_NoLoggingIfPressureSensorReadingIsPerformed, 86);
  RUN_TEST(test_SkipLoggingWhenStateIsIdle, 102);
  RUN_TEST(test_LogEveryMinuteButEnterNREWhenEEPROMFull, 123);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
