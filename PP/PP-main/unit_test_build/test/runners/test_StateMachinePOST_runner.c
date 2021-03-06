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
#include "MockStateMachinePOST_internal.h"
#include "MockDeviceStatus.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_OnInitSetsStateToZeroAndReturnsZero(void);
extern void test_ifNotDoingPOSTRunTransistionsToIdleState(void);
extern void test_onRunStateTestGoToDefaultWithInvalidSwitch(void);
extern void test_onRunState00CalledWhenStateIsZero(void);
extern void test_onRunState01CalledWhenStateIsOne(void);
extern void test_onRunState02CalledWhenStateIsTwo(void);
extern void test_onRunState03CalledWhenStateIsThree(void);
extern void test_onRunState04CalledWhenStateIsFour(void);
extern void test_onRunState05CalledWhenStateIsFive(void);
extern void test_onRunState06CalledWhenStateIsSix(void);
extern void test_onRunState07CalledWhenStateIsSeven(void);
extern void test_onRunState08CalledWhenStateIsEight(void);
extern void test_onRunState09CalledWhenStateIsNine(void);
extern void test_onRunState10CalledWhenStateIsTen(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockStateMachinePOST_internal_Init();
  MockDeviceStatus_Init();
}
static void CMock_Verify(void)
{
  MockStateMachinePOST_internal_Verify();
  MockDeviceStatus_Verify();
}
static void CMock_Destroy(void)
{
  MockStateMachinePOST_internal_Destroy();
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
  UnityBegin("test_StateMachinePOST.c");
  RUN_TEST(test_OnInitSetsStateToZeroAndReturnsZero, 29);
  RUN_TEST(test_ifNotDoingPOSTRunTransistionsToIdleState, 35);
  RUN_TEST(test_onRunStateTestGoToDefaultWithInvalidSwitch, 48);
  RUN_TEST(test_onRunState00CalledWhenStateIsZero, 76);
  RUN_TEST(test_onRunState01CalledWhenStateIsOne, 99);
  RUN_TEST(test_onRunState02CalledWhenStateIsTwo, 120);
  RUN_TEST(test_onRunState03CalledWhenStateIsThree, 141);
  RUN_TEST(test_onRunState04CalledWhenStateIsFour, 162);
  RUN_TEST(test_onRunState05CalledWhenStateIsFive, 183);
  RUN_TEST(test_onRunState06CalledWhenStateIsSix, 204);
  RUN_TEST(test_onRunState07CalledWhenStateIsSeven, 225);
  RUN_TEST(test_onRunState08CalledWhenStateIsEight, 246);
  RUN_TEST(test_onRunState09CalledWhenStateIsNine, 267);
  RUN_TEST(test_onRunState10CalledWhenStateIsTen, 288);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
