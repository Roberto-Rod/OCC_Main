/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_npda_scan_correct_data();
extern void test_npda_scan_offset_too_high();
extern void test_npda_scan_transform_fails();
extern void test_npda_scan_interpolation_fails();
extern void test_npda_scan_avg_calculation_fails();
extern void test_npda_block_end_correct_data();
extern void test_npda_measurement_end_correct_data();


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, int line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_u_npda.c");
  run_test(test_npda_scan_correct_data, "test_npda_scan_correct_data", 83);
  run_test(test_npda_scan_offset_too_high, "test_npda_scan_offset_too_high", 475);
  run_test(test_npda_scan_transform_fails, "test_npda_scan_transform_fails", 501);
  run_test(test_npda_scan_interpolation_fails, "test_npda_scan_interpolation_fails", 536);
  run_test(test_npda_scan_avg_calculation_fails, "test_npda_scan_avg_calculation_fails", 571);
  run_test(test_npda_block_end_correct_data, "test_npda_block_end_correct_data", 607);
  run_test(test_npda_measurement_end_correct_data, "test_npda_measurement_end_correct_data", 809);

  return UnityEnd();
}
