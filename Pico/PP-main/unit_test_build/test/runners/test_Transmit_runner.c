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
#include "Mockeusart.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_InitDoesNothing(void);
extern void test_TransmitDoesRangeCheckingOnDataPointer(void);
extern void test_TransmitDoesRangeCheckingonDataSize(void);
extern void test_TransmitCallsEUSARTWriteForEachCharacter(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  Mockeusart_Init();
}
static void CMock_Verify(void)
{
  Mockeusart_Verify();
}
static void CMock_Destroy(void)
{
  Mockeusart_Destroy();
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
  UnityBegin("test_Transmit.c");
  RUN_TEST(test_InitDoesNothing, 33);
  RUN_TEST(test_TransmitDoesRangeCheckingOnDataPointer, 40);
  RUN_TEST(test_TransmitDoesRangeCheckingonDataSize, 47);
  RUN_TEST(test_TransmitCallsEUSARTWriteForEachCharacter, 56);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
