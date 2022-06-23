/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "MockStateMachineTherapyDelivery.h"

static const char* CMockString_TherapyDelivery = "TherapyDelivery";
static const char* CMockString_TherapyDelivery_Init = "TherapyDelivery_Init";
static const char* CMockString_cmock_arg1 = "cmock_arg1";
static const char* CMockString_cmock_arg2 = "cmock_arg2";

typedef struct _CMOCK_TherapyDelivery_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  ErrorCode_t ReturnVal;
  int CallOrder;
  bool_t Expected_cmock_arg1;
  State_t* Expected_cmock_arg2;
  int Expected_cmock_arg2_Depth;
  int ReturnThruPtr_cmock_arg2_Used;
  State_t* ReturnThruPtr_cmock_arg2_Val;
  int ReturnThruPtr_cmock_arg2_Size;
  int IgnoreArg_cmock_arg1;
  int IgnoreArg_cmock_arg2;

} CMOCK_TherapyDelivery_CALL_INSTANCE;

typedef struct _CMOCK_TherapyDelivery_Init_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  ErrorCode_t ReturnVal;
  int CallOrder;

} CMOCK_TherapyDelivery_Init_CALL_INSTANCE;

static struct MockStateMachineTherapyDeliveryInstance
{
  int TherapyDelivery_IgnoreBool;
  ErrorCode_t TherapyDelivery_FinalReturn;
  CMOCK_TherapyDelivery_CALLBACK TherapyDelivery_CallbackFunctionPointer;
  int TherapyDelivery_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE TherapyDelivery_CallInstance;
  int TherapyDelivery_Init_IgnoreBool;
  ErrorCode_t TherapyDelivery_Init_FinalReturn;
  CMOCK_TherapyDelivery_Init_CALLBACK TherapyDelivery_Init_CallbackFunctionPointer;
  int TherapyDelivery_Init_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE TherapyDelivery_Init_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void MockStateMachineTherapyDelivery_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  if (Mock.TherapyDelivery_IgnoreBool)
    Mock.TherapyDelivery_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_TherapyDelivery);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.TherapyDelivery_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.TherapyDelivery_CallbackFunctionPointer != NULL)
    Mock.TherapyDelivery_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.TherapyDelivery_Init_IgnoreBool)
    Mock.TherapyDelivery_Init_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_TherapyDelivery_Init);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.TherapyDelivery_Init_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.TherapyDelivery_Init_CallbackFunctionPointer != NULL)
    Mock.TherapyDelivery_Init_CallInstance = CMOCK_GUTS_NONE;
}

void MockStateMachineTherapyDelivery_Init(void)
{
  MockStateMachineTherapyDelivery_Destroy();
}

void MockStateMachineTherapyDelivery_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  Mock.TherapyDelivery_CallbackFunctionPointer = NULL;
  Mock.TherapyDelivery_CallbackCalls = 0;
  Mock.TherapyDelivery_Init_CallbackFunctionPointer = NULL;
  Mock.TherapyDelivery_Init_CallbackCalls = 0;
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

ErrorCode_t TherapyDelivery(bool_t cmock_arg1, State_t* cmock_arg2)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_TherapyDelivery);
  CMOCK_TherapyDelivery_CALL_INSTANCE* cmock_call_instance = (CMOCK_TherapyDelivery_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.TherapyDelivery_CallInstance);
  Mock.TherapyDelivery_CallInstance = CMock_Guts_MemNext(Mock.TherapyDelivery_CallInstance);
  if (Mock.TherapyDelivery_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.TherapyDelivery_FinalReturn;
    memcpy(&Mock.TherapyDelivery_FinalReturn, &cmock_call_instance->ReturnVal, sizeof(ErrorCode_t));
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.TherapyDelivery_CallbackFunctionPointer != NULL)
  {
    return Mock.TherapyDelivery_CallbackFunctionPointer(cmock_arg1, cmock_arg2, Mock.TherapyDelivery_CallbackCalls++);
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  if (cmock_call_instance->IgnoreMode != CMOCK_ARG_NONE)
  {
  if (!cmock_call_instance->IgnoreArg_cmock_arg1)
  {
    UNITY_SET_DETAILS(CMockString_TherapyDelivery,CMockString_cmock_arg1);
    UNITY_TEST_ASSERT_EQUAL_INT(cmock_call_instance->Expected_cmock_arg1, cmock_arg1, cmock_line, CMockStringMismatch);
  }
  if (!cmock_call_instance->IgnoreArg_cmock_arg2)
  {
    UNITY_SET_DETAILS(CMockString_TherapyDelivery,CMockString_cmock_arg2);
    if (cmock_call_instance->Expected_cmock_arg2 == NULL)
      { UNITY_TEST_ASSERT_NULL(cmock_arg2, cmock_line, CMockStringExpNULL); }
    else
      { UNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY((void*)(cmock_call_instance->Expected_cmock_arg2), (void*)(cmock_arg2), sizeof(State_t), cmock_call_instance->Expected_cmock_arg2_Depth, cmock_line, CMockStringMismatch); }
  }

  }
  if (cmock_call_instance->ReturnThruPtr_cmock_arg2_Used)
  {
    memcpy(cmock_arg2, cmock_call_instance->ReturnThruPtr_cmock_arg2_Val,
      cmock_call_instance->ReturnThruPtr_cmock_arg2_Size);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_TherapyDelivery(CMOCK_TherapyDelivery_CALL_INSTANCE* cmock_call_instance, bool_t cmock_arg1, State_t* cmock_arg2, int cmock_arg2_Depth)
{
  cmock_call_instance->Expected_cmock_arg1 = cmock_arg1;
  cmock_call_instance->IgnoreArg_cmock_arg1 = 0;
  cmock_call_instance->Expected_cmock_arg2 = cmock_arg2;
  cmock_call_instance->Expected_cmock_arg2_Depth = cmock_arg2_Depth;
  cmock_call_instance->IgnoreArg_cmock_arg2 = 0;
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Used = 0;
}

void TherapyDelivery_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_TherapyDelivery_CALL_INSTANCE));
  CMOCK_TherapyDelivery_CALL_INSTANCE* cmock_call_instance = (CMOCK_TherapyDelivery_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.TherapyDelivery_CallInstance = CMock_Guts_MemChain(Mock.TherapyDelivery_CallInstance, cmock_guts_index);
  Mock.TherapyDelivery_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.TherapyDelivery_IgnoreBool = (int)1;
}

void TherapyDelivery_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_TherapyDelivery_CALL_INSTANCE));
  CMOCK_TherapyDelivery_CALL_INSTANCE* cmock_call_instance = (CMOCK_TherapyDelivery_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.TherapyDelivery_CallInstance = CMock_Guts_MemChain(Mock.TherapyDelivery_CallInstance, cmock_guts_index);
  Mock.TherapyDelivery_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void TherapyDelivery_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_arg1, State_t* cmock_arg2, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_TherapyDelivery_CALL_INSTANCE));
  CMOCK_TherapyDelivery_CALL_INSTANCE* cmock_call_instance = (CMOCK_TherapyDelivery_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.TherapyDelivery_CallInstance = CMock_Guts_MemChain(Mock.TherapyDelivery_CallInstance, cmock_guts_index);
  Mock.TherapyDelivery_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  CMockExpectParameters_TherapyDelivery(cmock_call_instance, cmock_arg1, cmock_arg2, 1);
  memcpy(&cmock_call_instance->ReturnVal, &cmock_to_return, sizeof(ErrorCode_t));
  UNITY_CLR_DETAILS();
}

void TherapyDelivery_StubWithCallback(CMOCK_TherapyDelivery_CALLBACK Callback)
{
  Mock.TherapyDelivery_CallbackFunctionPointer = Callback;
}

void TherapyDelivery_CMockExpectWithArrayAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_arg1, State_t* cmock_arg2, int cmock_arg2_Depth, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_TherapyDelivery_CALL_INSTANCE));
  CMOCK_TherapyDelivery_CALL_INSTANCE* cmock_call_instance = (CMOCK_TherapyDelivery_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.TherapyDelivery_CallInstance = CMock_Guts_MemChain(Mock.TherapyDelivery_CallInstance, cmock_guts_index);
  Mock.TherapyDelivery_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  CMockExpectParameters_TherapyDelivery(cmock_call_instance, cmock_arg1, cmock_arg2, cmock_arg2_Depth);
  cmock_call_instance->ReturnVal = cmock_to_return;
}

void TherapyDelivery_CMockReturnMemThruPtr_cmock_arg2(UNITY_LINE_TYPE cmock_line, State_t* cmock_arg2, int cmock_size)
{
  CMOCK_TherapyDelivery_CALL_INSTANCE* cmock_call_instance = (CMOCK_TherapyDelivery_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.TherapyDelivery_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringPtrPreExp);
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Used = 1;
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Val = cmock_arg2;
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Size = cmock_size;
}

void TherapyDelivery_CMockIgnoreArg_cmock_arg1(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_TherapyDelivery_CALL_INSTANCE* cmock_call_instance = (CMOCK_TherapyDelivery_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.TherapyDelivery_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_cmock_arg1 = 1;
}

void TherapyDelivery_CMockIgnoreArg_cmock_arg2(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_TherapyDelivery_CALL_INSTANCE* cmock_call_instance = (CMOCK_TherapyDelivery_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.TherapyDelivery_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_cmock_arg2 = 1;
}

ErrorCode_t TherapyDelivery_Init(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_TherapyDelivery_Init);
  CMOCK_TherapyDelivery_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_TherapyDelivery_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.TherapyDelivery_Init_CallInstance);
  Mock.TherapyDelivery_Init_CallInstance = CMock_Guts_MemNext(Mock.TherapyDelivery_Init_CallInstance);
  if (Mock.TherapyDelivery_Init_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.TherapyDelivery_Init_FinalReturn;
    memcpy(&Mock.TherapyDelivery_Init_FinalReturn, &cmock_call_instance->ReturnVal, sizeof(ErrorCode_t));
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.TherapyDelivery_Init_CallbackFunctionPointer != NULL)
  {
    return Mock.TherapyDelivery_Init_CallbackFunctionPointer(Mock.TherapyDelivery_Init_CallbackCalls++);
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

void TherapyDelivery_Init_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_TherapyDelivery_Init_CALL_INSTANCE));
  CMOCK_TherapyDelivery_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_TherapyDelivery_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.TherapyDelivery_Init_CallInstance = CMock_Guts_MemChain(Mock.TherapyDelivery_Init_CallInstance, cmock_guts_index);
  Mock.TherapyDelivery_Init_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.TherapyDelivery_Init_IgnoreBool = (int)1;
}

void TherapyDelivery_Init_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_TherapyDelivery_Init_CALL_INSTANCE));
  CMOCK_TherapyDelivery_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_TherapyDelivery_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.TherapyDelivery_Init_CallInstance = CMock_Guts_MemChain(Mock.TherapyDelivery_Init_CallInstance, cmock_guts_index);
  Mock.TherapyDelivery_Init_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void TherapyDelivery_Init_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_TherapyDelivery_Init_CALL_INSTANCE));
  CMOCK_TherapyDelivery_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_TherapyDelivery_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.TherapyDelivery_Init_CallInstance = CMock_Guts_MemChain(Mock.TherapyDelivery_Init_CallInstance, cmock_guts_index);
  Mock.TherapyDelivery_Init_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  memcpy(&cmock_call_instance->ReturnVal, &cmock_to_return, sizeof(ErrorCode_t));
  UNITY_CLR_DETAILS();
}

void TherapyDelivery_Init_StubWithCallback(CMOCK_TherapyDelivery_Init_CALLBACK Callback)
{
  Mock.TherapyDelivery_Init_CallbackFunctionPointer = Callback;
}

