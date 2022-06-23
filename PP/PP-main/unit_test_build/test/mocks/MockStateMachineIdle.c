/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "MockStateMachineIdle.h"

static const char* CMockString_Idle = "Idle";
static const char* CMockString_Idle_Init = "Idle_Init";
static const char* CMockString_cmock_arg1 = "cmock_arg1";
static const char* CMockString_cmock_arg2 = "cmock_arg2";

typedef struct _CMOCK_Idle_CALL_INSTANCE
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

} CMOCK_Idle_CALL_INSTANCE;

typedef struct _CMOCK_Idle_Init_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  ErrorCode_t ReturnVal;
  int CallOrder;

} CMOCK_Idle_Init_CALL_INSTANCE;

static struct MockStateMachineIdleInstance
{
  int Idle_IgnoreBool;
  ErrorCode_t Idle_FinalReturn;
  CMOCK_Idle_CALLBACK Idle_CallbackFunctionPointer;
  int Idle_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE Idle_CallInstance;
  int Idle_Init_IgnoreBool;
  ErrorCode_t Idle_Init_FinalReturn;
  CMOCK_Idle_Init_CALLBACK Idle_Init_CallbackFunctionPointer;
  int Idle_Init_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE Idle_Init_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void MockStateMachineIdle_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  if (Mock.Idle_IgnoreBool)
    Mock.Idle_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_Idle);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.Idle_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.Idle_CallbackFunctionPointer != NULL)
    Mock.Idle_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.Idle_Init_IgnoreBool)
    Mock.Idle_Init_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_Idle_Init);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.Idle_Init_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.Idle_Init_CallbackFunctionPointer != NULL)
    Mock.Idle_Init_CallInstance = CMOCK_GUTS_NONE;
}

void MockStateMachineIdle_Init(void)
{
  MockStateMachineIdle_Destroy();
}

void MockStateMachineIdle_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  Mock.Idle_CallbackFunctionPointer = NULL;
  Mock.Idle_CallbackCalls = 0;
  Mock.Idle_Init_CallbackFunctionPointer = NULL;
  Mock.Idle_Init_CallbackCalls = 0;
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

ErrorCode_t Idle(bool_t cmock_arg1, State_t* cmock_arg2)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_Idle);
  CMOCK_Idle_CALL_INSTANCE* cmock_call_instance = (CMOCK_Idle_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.Idle_CallInstance);
  Mock.Idle_CallInstance = CMock_Guts_MemNext(Mock.Idle_CallInstance);
  if (Mock.Idle_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.Idle_FinalReturn;
    memcpy(&Mock.Idle_FinalReturn, &cmock_call_instance->ReturnVal, sizeof(ErrorCode_t));
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.Idle_CallbackFunctionPointer != NULL)
  {
    return Mock.Idle_CallbackFunctionPointer(cmock_arg1, cmock_arg2, Mock.Idle_CallbackCalls++);
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
    UNITY_SET_DETAILS(CMockString_Idle,CMockString_cmock_arg1);
    UNITY_TEST_ASSERT_EQUAL_INT(cmock_call_instance->Expected_cmock_arg1, cmock_arg1, cmock_line, CMockStringMismatch);
  }
  if (!cmock_call_instance->IgnoreArg_cmock_arg2)
  {
    UNITY_SET_DETAILS(CMockString_Idle,CMockString_cmock_arg2);
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

void CMockExpectParameters_Idle(CMOCK_Idle_CALL_INSTANCE* cmock_call_instance, bool_t cmock_arg1, State_t* cmock_arg2, int cmock_arg2_Depth)
{
  cmock_call_instance->Expected_cmock_arg1 = cmock_arg1;
  cmock_call_instance->IgnoreArg_cmock_arg1 = 0;
  cmock_call_instance->Expected_cmock_arg2 = cmock_arg2;
  cmock_call_instance->Expected_cmock_arg2_Depth = cmock_arg2_Depth;
  cmock_call_instance->IgnoreArg_cmock_arg2 = 0;
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Used = 0;
}

void Idle_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Idle_CALL_INSTANCE));
  CMOCK_Idle_CALL_INSTANCE* cmock_call_instance = (CMOCK_Idle_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Idle_CallInstance = CMock_Guts_MemChain(Mock.Idle_CallInstance, cmock_guts_index);
  Mock.Idle_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.Idle_IgnoreBool = (int)1;
}

void Idle_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Idle_CALL_INSTANCE));
  CMOCK_Idle_CALL_INSTANCE* cmock_call_instance = (CMOCK_Idle_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Idle_CallInstance = CMock_Guts_MemChain(Mock.Idle_CallInstance, cmock_guts_index);
  Mock.Idle_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void Idle_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_arg1, State_t* cmock_arg2, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Idle_CALL_INSTANCE));
  CMOCK_Idle_CALL_INSTANCE* cmock_call_instance = (CMOCK_Idle_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Idle_CallInstance = CMock_Guts_MemChain(Mock.Idle_CallInstance, cmock_guts_index);
  Mock.Idle_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  CMockExpectParameters_Idle(cmock_call_instance, cmock_arg1, cmock_arg2, 1);
  memcpy(&cmock_call_instance->ReturnVal, &cmock_to_return, sizeof(ErrorCode_t));
  UNITY_CLR_DETAILS();
}

void Idle_StubWithCallback(CMOCK_Idle_CALLBACK Callback)
{
  Mock.Idle_CallbackFunctionPointer = Callback;
}

void Idle_CMockExpectWithArrayAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_arg1, State_t* cmock_arg2, int cmock_arg2_Depth, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Idle_CALL_INSTANCE));
  CMOCK_Idle_CALL_INSTANCE* cmock_call_instance = (CMOCK_Idle_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Idle_CallInstance = CMock_Guts_MemChain(Mock.Idle_CallInstance, cmock_guts_index);
  Mock.Idle_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  CMockExpectParameters_Idle(cmock_call_instance, cmock_arg1, cmock_arg2, cmock_arg2_Depth);
  cmock_call_instance->ReturnVal = cmock_to_return;
}

void Idle_CMockReturnMemThruPtr_cmock_arg2(UNITY_LINE_TYPE cmock_line, State_t* cmock_arg2, int cmock_size)
{
  CMOCK_Idle_CALL_INSTANCE* cmock_call_instance = (CMOCK_Idle_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.Idle_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringPtrPreExp);
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Used = 1;
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Val = cmock_arg2;
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Size = cmock_size;
}

void Idle_CMockIgnoreArg_cmock_arg1(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_Idle_CALL_INSTANCE* cmock_call_instance = (CMOCK_Idle_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.Idle_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_cmock_arg1 = 1;
}

void Idle_CMockIgnoreArg_cmock_arg2(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_Idle_CALL_INSTANCE* cmock_call_instance = (CMOCK_Idle_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.Idle_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_cmock_arg2 = 1;
}

ErrorCode_t Idle_Init(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_Idle_Init);
  CMOCK_Idle_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_Idle_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.Idle_Init_CallInstance);
  Mock.Idle_Init_CallInstance = CMock_Guts_MemNext(Mock.Idle_Init_CallInstance);
  if (Mock.Idle_Init_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.Idle_Init_FinalReturn;
    memcpy(&Mock.Idle_Init_FinalReturn, &cmock_call_instance->ReturnVal, sizeof(ErrorCode_t));
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.Idle_Init_CallbackFunctionPointer != NULL)
  {
    return Mock.Idle_Init_CallbackFunctionPointer(Mock.Idle_Init_CallbackCalls++);
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

void Idle_Init_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Idle_Init_CALL_INSTANCE));
  CMOCK_Idle_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_Idle_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Idle_Init_CallInstance = CMock_Guts_MemChain(Mock.Idle_Init_CallInstance, cmock_guts_index);
  Mock.Idle_Init_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.Idle_Init_IgnoreBool = (int)1;
}

void Idle_Init_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Idle_Init_CALL_INSTANCE));
  CMOCK_Idle_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_Idle_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Idle_Init_CallInstance = CMock_Guts_MemChain(Mock.Idle_Init_CallInstance, cmock_guts_index);
  Mock.Idle_Init_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void Idle_Init_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Idle_Init_CALL_INSTANCE));
  CMOCK_Idle_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_Idle_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Idle_Init_CallInstance = CMock_Guts_MemChain(Mock.Idle_Init_CallInstance, cmock_guts_index);
  Mock.Idle_Init_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  memcpy(&cmock_call_instance->ReturnVal, &cmock_to_return, sizeof(ErrorCode_t));
  UNITY_CLR_DETAILS();
}

void Idle_Init_StubWithCallback(CMOCK_Idle_Init_CALLBACK Callback)
{
  Mock.Idle_Init_CallbackFunctionPointer = Callback;
}

