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
#include "MockTransmit.h"
#include "Mockpin_manager.h"
#include "MockPowerControl.h"
#include "MockPressure_Part1.h"
#include "Mockadc.h"
#include "MockTimer.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_getAndSetOfStateNumber(void);
extern void test_doPostChecksThePinsOnlyTheFirstTime_POST_is_a_go(void);
extern void test_doPostChecksThePinsOnlyTheFirstTime_POST_is_a_no(void);
extern void test_weCycleThroughTheStatesProperly(void);
extern void test_State00SetsRC4(void);
extern void test_State01SetsReferenceVBoostReadsBoostVoltageADCAndTransmitsOnTX(void);
extern void test_State02SetsRC7AndClearsVBoost(void);
extern void test_State03SetsRC5ClearsRC7(void);
extern void test_State04SetsRC2ClearsRC5ReadsAndTransmitsTheExternalVacuum(void);
extern void test_State05ClearsRC2ReadsAndTransmitsTheInternalVacuum(void);
extern void test_State06WritesToTheEEPROMAndReadsItBack(void);
extern void test_State07TogglesRC6ClearsRC3SetsVBoostReadsTheADCAndTransmitsADCOnTX(void);
extern void test_State08TogglesRC6SetsRC3SetsVBoostReadsTheADCAndTransmitsADCOnTX(void);
extern void test_State09ClearsRC3SetsDACto0ReadsRA5AndTransmitsRA5OnTX(void);
extern void test_State10SetsRB5(void);
extern void test_StateErrorSendsAMessageOnTheTXLine(void);
extern void test_InitInitialiseTransmit(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  MockI2CEEPROM_Init();
  MockTransmit_Init();
  Mockpin_manager_Init();
  MockPowerControl_Init();
  MockPressure_Part1_Init();
  Mockadc_Init();
  MockTimer_Init();
}
static void CMock_Verify(void)
{
  MockI2CEEPROM_Verify();
  MockTransmit_Verify();
  Mockpin_manager_Verify();
  MockPowerControl_Verify();
  MockPressure_Part1_Verify();
  Mockadc_Verify();
  MockTimer_Verify();
}
static void CMock_Destroy(void)
{
  MockI2CEEPROM_Destroy();
  MockTransmit_Destroy();
  Mockpin_manager_Destroy();
  MockPowerControl_Destroy();
  MockPressure_Part1_Destroy();
  Mockadc_Destroy();
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
  UnityBegin("test_StateMachinePOST_internal.c");
  RUN_TEST(test_getAndSetOfStateNumber, 148);
  RUN_TEST(test_doPostChecksThePinsOnlyTheFirstTime_POST_is_a_go, 155);
  RUN_TEST(test_doPostChecksThePinsOnlyTheFirstTime_POST_is_a_no, 181);
  RUN_TEST(test_weCycleThroughTheStatesProperly, 205);
  RUN_TEST(test_State00SetsRC4, 245);
  RUN_TEST(test_State01SetsReferenceVBoostReadsBoostVoltageADCAndTransmitsOnTX, 256);
  RUN_TEST(test_State02SetsRC7AndClearsVBoost, 293);
  RUN_TEST(test_State03SetsRC5ClearsRC7, 306);
  RUN_TEST(test_State04SetsRC2ClearsRC5ReadsAndTransmitsTheExternalVacuum, 317);
  RUN_TEST(test_State05ClearsRC2ReadsAndTransmitsTheInternalVacuum, 369);
  RUN_TEST(test_State06WritesToTheEEPROMAndReadsItBack, 422);
  RUN_TEST(test_State07TogglesRC6ClearsRC3SetsVBoostReadsTheADCAndTransmitsADCOnTX, 511);
  RUN_TEST(test_State08TogglesRC6SetsRC3SetsVBoostReadsTheADCAndTransmitsADCOnTX, 570);
  RUN_TEST(test_State09ClearsRC3SetsDACto0ReadsRA5AndTransmitsRA5OnTX, 627);
  RUN_TEST(test_State10SetsRB5, 679);
  RUN_TEST(test_StateErrorSendsAMessageOnTheTXLine, 690);
  RUN_TEST(test_InitInitialiseTransmit, 719);

  CMock_Guts_MemFreeFinal();
  return (UnityEnd());
}
