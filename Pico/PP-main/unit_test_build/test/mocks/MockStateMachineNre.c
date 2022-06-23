/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "MockStateMachineNre.h"

static const char* CMockString_NonRecoverableError = "NonRecoverableError";
static const char* CMockString_cmock_arg1 = "cmock_arg1";
static const char* CMockString_cmock_arg2 = "cmock_arg2";

typedef struct _CMOCK_NonRecoverableError_CALL_INSTANCE
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

} CMOCK_NonRecoverableError_CALL_INSTANCE;

static struct MockStateMachineNreInstance
{
  int NonRecoverableError_IgnoreBool;
  ErrorCode_t NonRecoverableError_FinalReturn;
  CMOCK_NonRecoverableError_CALLBACK NonRecoverableError_CallbackFunctionPointer;
  int NonRecoverableError_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE NonRecoverableError_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void MockStateMachineNre_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  if (Mock.NonRecoverableError_IgnoreBool)
    Mock.NonRecoverableError_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_NonRecoverableError);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.NonRecoverableError_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.NonRecoverableError_CallbackFunctionPointer != NULL)
    Mock.NonRecoverableError_CallInstance = CMOCK_GUTS_NONE;
}

void MockStateMachineNre_Init(void)
{
  MockStateMachineNre_Destroy();
}

void MockStateMachineNre_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  Mock.NonRecoverableError_CallbackFunctionPointer = NULL;
  Mock.NonRecoverableError_CallbackCalls = 0;
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

ErrorCode_t NonRecoverableError(bool_t cmock_arg1, State_t* cmock_arg2)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_NonRecoverableError);
  CMOCK_NonRecoverableError_CALL_INSTANCE* cmock_call_instance = (CMOCK_NonRecoverableError_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.NonRecoverableError_CallInstance);
  Mock.NonRecoverableError_CallInstance = CMock_Guts_MemNext(Mock.NonRecoverableError_CallInstance);
  if (Mock.NonRecoverableError_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.NonRecoverableError_FinalReturn;
    memcpy(&Mock.NonRecoverableError_FinalReturn, &cmock_call_instance->ReturnVal, sizeof(ErrorCode_t));
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.NonRecoverableError_CallbackFunctionPointer != NULL)
  {
    return Mock.NonRecoverableError_CallbackFunctionPointer(cmock_arg1, cmock_arg2, Mock.NonRecoverableError_CallbackCalls++);
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
    UNITY_SET_DETAILS(CMockString_NonRecoverableError,CMockString_cmock_arg1);
    UNITY_TEST_ASSERT_EQUAL_INT(cmock_call_instance->Expected_cmock_arg1, cmock_arg1, cmock_line, CMockStringMismatch);
  }
  if (!cmock_call_instance->IgnoreArg_cmock_arg2)
  {
    UNITY_SET_DETAILS(CMockString_NonRecoverableError,CMockString_cmock_arg2);
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

void CMockExpectParameters_NonRecoverableError(CMOCK_NonRecoverableError_CALL_INSTANCE* cmock_call_instance, bool_t cmock_arg1, State_t* cmock_arg2, int cmock_arg2_Depth)
{
  cmock_call_instance->Expected_cmock_arg1 = cmock_arg1;
  cmock_call_instance->IgnoreArg_cmock_arg1 = 0;
  cmock_call_instance->Expected_cmock_arg2 = cmock_arg2;
  cmock_call_instance->Expected_cmock_arg2_Depth = cmock_arg2_Depth;
  cmock_call_instance->IgnoreArg_cmock_arg2 = 0;
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Used = 0;
}

void NonRecoverableError_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_NonRecoverableError_CALL_INSTANCE));
  CMOCK_NonRecoverableError_CALL_INSTANCE* cmock_call_instance = (CMOCK_NonRecoverableError_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.NonRecoverableError_CallInstance = CMock_Guts_MemChain(Mock.NonRecoverableError_CallInstance, cmock_guts_index);
  Mock.NonRecoverableError_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.NonRecoverableError_IgnoreBool = (int)1;
}

void NonRecoverableError_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_NonRecoverableError_CALL_INSTANCE));
  CMOCK_NonRecoverableError_CALL_INSTANCE* cmock_call_instance = (CMOCK_NonRecoverableError_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.NonRecoverableError_CallInstance = CMock_Guts_MemChain(Mock.NonRecoverableError_CallInstance, cmock_guts_index);
  Mock.NonRecoverableError_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void NonRecoverableError_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_arg1, State_t* cmock_arg2, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_NonRecoverableError_CALL_INSTANCE));
  CMOCK_NonRecoverableError_CALL_INSTANCE* cmock_call_instance = (CMOCK_NonRecoverableError_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.NonRecoverableError_CallInstance = CMock_Guts_MemChain(Mock.NonRecoverableError_CallInstance, cmock_guts_index);
  Mock.NonRecoverableError_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  CMockExpectParameters_NonRecoverableError(cmock_call_instance, cmock_arg1, cmock_arg2, 1);
  memcpy(&cmock_call_instance->ReturnVal, &cmock_to_return, sizeof(ErrorCode_t));
  UNITY_CLR_DETAILS();
}

void NonRecoverableError_StubWithCallback(CMOCK_NonRecoverableError_CALLBACK Callback)
{
  Mock.NonRecoverableError_CallbackFunctionPointer = Callback;
}

void NonRecoverableError_CMockExpectWithArrayAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_arg1, State_t* cmock_arg2, int cmock_arg2_Depth, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_NonRecoverableError_CALL_INSTANCE));
  CMOCK_NonRecoverableError_CALL_INSTANCE* cmock_call_instance = (CMOCK_NonRecoverableError_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.NonRecoverableError_CallInstance = CMock_Guts_MemChain(Mock.NonRecoverableError_CallInstance, cmock_guts_index);
  Mock.NonRecoverableError_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  CMockExpectParameters_NonRecoverableError(cmock_call_instance, cmock_arg1, cmock_arg2, cmock_arg2_Depth);
  cmock_call_instance->ReturnVal = cmock_to_return;
}

void NonRecoverableError_CMockReturnMemThruPtr_cmock_arg2(UNITY_LINE_TYPE cmock_line, State_t* cmock_arg2, int cmock_size)
{
  CMOCK_NonRecoverableError_CALL_INSTANCE* cmock_call_instance = (CMOCK_NonRecoverableError_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.NonRecoverableError_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringPtrPreExp);
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Used = 1;
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Val = cmock_arg2;
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Size = cmock_size;
}

void NonRecoverableError_CMockIgnoreArg_cmock_arg1(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_NonRecoverableError_CALL_INSTANCE* cmock_call_instance = (CMOCK_NonRecoverableError_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.NonRecoverableError_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_cmock_arg1 = 1;
}

void NonRecoverableError_CMockIgnoreArg_cmock_arg2(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_NonRecoverableError_CALL_INSTANCE* cmock_call_instance = (CMOCK_NonRecoverableError_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.NonRecoverableError_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_cmock_arg2 = 1;
}

