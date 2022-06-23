/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "MockBattery.h"

static const char* CMockString_Battery_CheckVoltageBounds = "Battery_CheckVoltageBounds";

typedef struct _CMOCK_Battery_CheckVoltageBounds_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  ErrorCode_t ReturnVal;
  int CallOrder;

} CMOCK_Battery_CheckVoltageBounds_CALL_INSTANCE;

static struct MockBatteryInstance
{
  int Battery_CheckVoltageBounds_IgnoreBool;
  ErrorCode_t Battery_CheckVoltageBounds_FinalReturn;
  CMOCK_Battery_CheckVoltageBounds_CALLBACK Battery_CheckVoltageBounds_CallbackFunctionPointer;
  int Battery_CheckVoltageBounds_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE Battery_CheckVoltageBounds_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void MockBattery_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  if (Mock.Battery_CheckVoltageBounds_IgnoreBool)
    Mock.Battery_CheckVoltageBounds_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_Battery_CheckVoltageBounds);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.Battery_CheckVoltageBounds_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.Battery_CheckVoltageBounds_CallbackFunctionPointer != NULL)
    Mock.Battery_CheckVoltageBounds_CallInstance = CMOCK_GUTS_NONE;
}

void MockBattery_Init(void)
{
  MockBattery_Destroy();
}

void MockBattery_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  Mock.Battery_CheckVoltageBounds_CallbackFunctionPointer = NULL;
  Mock.Battery_CheckVoltageBounds_CallbackCalls = 0;
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

ErrorCode_t Battery_CheckVoltageBounds(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_Battery_CheckVoltageBounds);
  CMOCK_Battery_CheckVoltageBounds_CALL_INSTANCE* cmock_call_instance = (CMOCK_Battery_CheckVoltageBounds_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.Battery_CheckVoltageBounds_CallInstance);
  Mock.Battery_CheckVoltageBounds_CallInstance = CMock_Guts_MemNext(Mock.Battery_CheckVoltageBounds_CallInstance);
  if (Mock.Battery_CheckVoltageBounds_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.Battery_CheckVoltageBounds_FinalReturn;
    memcpy(&Mock.Battery_CheckVoltageBounds_FinalReturn, &cmock_call_instance->ReturnVal, sizeof(ErrorCode_t));
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.Battery_CheckVoltageBounds_CallbackFunctionPointer != NULL)
  {
    return Mock.Battery_CheckVoltageBounds_CallbackFunctionPointer(Mock.Battery_CheckVoltageBounds_CallbackCalls++);
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void Battery_CheckVoltageBounds_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Battery_CheckVoltageBounds_CALL_INSTANCE));
  CMOCK_Battery_CheckVoltageBounds_CALL_INSTANCE* cmock_call_instance = (CMOCK_Battery_CheckVoltageBounds_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Battery_CheckVoltageBounds_CallInstance = CMock_Guts_MemChain(Mock.Battery_CheckVoltageBounds_CallInstance, cmock_guts_index);
  Mock.Battery_CheckVoltageBounds_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.Battery_CheckVoltageBounds_IgnoreBool = (int)1;
}

void Battery_CheckVoltageBounds_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Battery_CheckVoltageBounds_CALL_INSTANCE));
  CMOCK_Battery_CheckVoltageBounds_CALL_INSTANCE* cmock_call_instance = (CMOCK_Battery_CheckVoltageBounds_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Battery_CheckVoltageBounds_CallInstance = CMock_Guts_MemChain(Mock.Battery_CheckVoltageBounds_CallInstance, cmock_guts_index);
  Mock.Battery_CheckVoltageBounds_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void Battery_CheckVoltageBounds_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Battery_CheckVoltageBounds_CALL_INSTANCE));
  CMOCK_Battery_CheckVoltageBounds_CALL_INSTANCE* cmock_call_instance = (CMOCK_Battery_CheckVoltageBounds_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Battery_CheckVoltageBounds_CallInstance = CMock_Guts_MemChain(Mock.Battery_CheckVoltageBounds_CallInstance, cmock_guts_index);
  Mock.Battery_CheckVoltageBounds_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  memcpy(&cmock_call_instance->ReturnVal, &cmock_to_return, sizeof(ErrorCode_t));
  UNITY_CLR_DETAILS();
}

void Battery_CheckVoltageBounds_StubWithCallback(CMOCK_Battery_CheckVoltageBounds_CALLBACK Callback)
{
  Mock.Battery_CheckVoltageBounds_CallbackFunctionPointer = Callback;
}
