/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "MockStateMachinePumpDown.h"

static const char* CMockString_PumpDown = "PumpDown";
static const char* CMockString_PumpDown_Init = "PumpDown_Init";
static const char* CMockString_cmock_arg1 = "cmock_arg1";
static const char* CMockString_cmock_arg2 = "cmock_arg2";

typedef struct _CMOCK_PumpDown_CALL_INSTANCE
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

} CMOCK_PumpDown_CALL_INSTANCE;

typedef struct _CMOCK_PumpDown_Init_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  ErrorCode_t ReturnVal;
  int CallOrder;

} CMOCK_PumpDown_Init_CALL_INSTANCE;

static struct MockStateMachinePumpDownInstance
{
  int PumpDown_IgnoreBool;
  ErrorCode_t PumpDown_FinalReturn;
  CMOCK_PumpDown_CALLBACK PumpDown_CallbackFunctionPointer;
  int PumpDown_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE PumpDown_CallInstance;
  int PumpDown_Init_IgnoreBool;
  ErrorCode_t PumpDown_Init_FinalReturn;
  CMOCK_PumpDown_Init_CALLBACK PumpDown_Init_CallbackFunctionPointer;
  int PumpDown_Init_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE PumpDown_Init_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void MockStateMachinePumpDown_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  if (Mock.PumpDown_IgnoreBool)
    Mock.PumpDown_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_PumpDown);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.PumpDown_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.PumpDown_CallbackFunctionPointer != NULL)
    Mock.PumpDown_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.PumpDown_Init_IgnoreBool)
    Mock.PumpDown_Init_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_PumpDown_Init);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.PumpDown_Init_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.PumpDown_Init_CallbackFunctionPointer != NULL)
    Mock.PumpDown_Init_CallInstance = CMOCK_GUTS_NONE;
}

void MockStateMachinePumpDown_Init(void)
{
  MockStateMachinePumpDown_Destroy();
}

void MockStateMachinePumpDown_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  Mock.PumpDown_CallbackFunctionPointer = NULL;
  Mock.PumpDown_CallbackCalls = 0;
  Mock.PumpDown_Init_CallbackFunctionPointer = NULL;
  Mock.PumpDown_Init_CallbackCalls = 0;
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

ErrorCode_t PumpDown(bool_t cmock_arg1, State_t* cmock_arg2)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_PumpDown);
  CMOCK_PumpDown_CALL_INSTANCE* cmock_call_instance = (CMOCK_PumpDown_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.PumpDown_CallInstance);
  Mock.PumpDown_CallInstance = CMock_Guts_MemNext(Mock.PumpDown_CallInstance);
  if (Mock.PumpDown_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.PumpDown_FinalReturn;
    memcpy(&Mock.PumpDown_FinalReturn, &cmock_call_instance->ReturnVal, sizeof(ErrorCode_t));
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.PumpDown_CallbackFunctionPointer != NULL)
  {
    return Mock.PumpDown_CallbackFunctionPointer(cmock_arg1, cmock_arg2, Mock.PumpDown_CallbackCalls++);
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
    UNITY_SET_DETAILS(CMockString_PumpDown,CMockString_cmock_arg1);
    UNITY_TEST_ASSERT_EQUAL_INT(cmock_call_instance->Expected_cmock_arg1, cmock_arg1, cmock_line, CMockStringMismatch);
  }
  if (!cmock_call_instance->IgnoreArg_cmock_arg2)
  {
    UNITY_SET_DETAILS(CMockString_PumpDown,CMockString_cmock_arg2);
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

void CMockExpectParameters_PumpDown(CMOCK_PumpDown_CALL_INSTANCE* cmock_call_instance, bool_t cmock_arg1, State_t* cmock_arg2, int cmock_arg2_Depth)
{
  cmock_call_instance->Expected_cmock_arg1 = cmock_arg1;
  cmock_call_instance->IgnoreArg_cmock_arg1 = 0;
  cmock_call_instance->Expected_cmock_arg2 = cmock_arg2;
  cmock_call_instance->Expected_cmock_arg2_Depth = cmock_arg2_Depth;
  cmock_call_instance->IgnoreArg_cmock_arg2 = 0;
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Used = 0;
}

void PumpDown_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PumpDown_CALL_INSTANCE));
  CMOCK_PumpDown_CALL_INSTANCE* cmock_call_instance = (CMOCK_PumpDown_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PumpDown_CallInstance = CMock_Guts_MemChain(Mock.PumpDown_CallInstance, cmock_guts_index);
  Mock.PumpDown_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.PumpDown_IgnoreBool = (int)1;
}

void PumpDown_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PumpDown_CALL_INSTANCE));
  CMOCK_PumpDown_CALL_INSTANCE* cmock_call_instance = (CMOCK_PumpDown_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PumpDown_CallInstance = CMock_Guts_MemChain(Mock.PumpDown_CallInstance, cmock_guts_index);
  Mock.PumpDown_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void PumpDown_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_arg1, State_t* cmock_arg2, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PumpDown_CALL_INSTANCE));
  CMOCK_PumpDown_CALL_INSTANCE* cmock_call_instance = (CMOCK_PumpDown_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PumpDown_CallInstance = CMock_Guts_MemChain(Mock.PumpDown_CallInstance, cmock_guts_index);
  Mock.PumpDown_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  CMockExpectParameters_PumpDown(cmock_call_instance, cmock_arg1, cmock_arg2, 1);
  memcpy(&cmock_call_instance->ReturnVal, &cmock_to_return, sizeof(ErrorCode_t));
  UNITY_CLR_DETAILS();
}

void PumpDown_StubWithCallback(CMOCK_PumpDown_CALLBACK Callback)
{
  Mock.PumpDown_CallbackFunctionPointer = Callback;
}

void PumpDown_CMockExpectWithArrayAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_arg1, State_t* cmock_arg2, int cmock_arg2_Depth, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PumpDown_CALL_INSTANCE));
  CMOCK_PumpDown_CALL_INSTANCE* cmock_call_instance = (CMOCK_PumpDown_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PumpDown_CallInstance = CMock_Guts_MemChain(Mock.PumpDown_CallInstance, cmock_guts_index);
  Mock.PumpDown_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  CMockExpectParameters_PumpDown(cmock_call_instance, cmock_arg1, cmock_arg2, cmock_arg2_Depth);
  cmock_call_instance->ReturnVal = cmock_to_return;
}

void PumpDown_CMockReturnMemThruPtr_cmock_arg2(UNITY_LINE_TYPE cmock_line, State_t* cmock_arg2, int cmock_size)
{
  CMOCK_PumpDown_CALL_INSTANCE* cmock_call_instance = (CMOCK_PumpDown_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.PumpDown_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringPtrPreExp);
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Used = 1;
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Val = cmock_arg2;
  cmock_call_instance->ReturnThruPtr_cmock_arg2_Size = cmock_size;
}

void PumpDown_CMockIgnoreArg_cmock_arg1(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_PumpDown_CALL_INSTANCE* cmock_call_instance = (CMOCK_PumpDown_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.PumpDown_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_cmock_arg1 = 1;
}

void PumpDown_CMockIgnoreArg_cmock_arg2(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_PumpDown_CALL_INSTANCE* cmock_call_instance = (CMOCK_PumpDown_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.PumpDown_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_cmock_arg2 = 1;
}

ErrorCode_t PumpDown_Init(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_PumpDown_Init);
  CMOCK_PumpDown_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_PumpDown_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.PumpDown_Init_CallInstance);
  Mock.PumpDown_Init_CallInstance = CMock_Guts_MemNext(Mock.PumpDown_Init_CallInstance);
  if (Mock.PumpDown_Init_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.PumpDown_Init_FinalReturn;
    memcpy(&Mock.PumpDown_Init_FinalReturn, &cmock_call_instance->ReturnVal, sizeof(ErrorCode_t));
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.PumpDown_Init_CallbackFunctionPointer != NULL)
  {
    return Mock.PumpDown_Init_CallbackFunctionPointer(Mock.PumpDown_Init_CallbackCalls++);
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

void PumpDown_Init_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PumpDown_Init_CALL_INSTANCE));
  CMOCK_PumpDown_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_PumpDown_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PumpDown_Init_CallInstance = CMock_Guts_MemChain(Mock.PumpDown_Init_CallInstance, cmock_guts_index);
  Mock.PumpDown_Init_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.PumpDown_Init_IgnoreBool = (int)1;
}

void PumpDown_Init_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PumpDown_Init_CALL_INSTANCE));
  CMOCK_PumpDown_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_PumpDown_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PumpDown_Init_CallInstance = CMock_Guts_MemChain(Mock.PumpDown_Init_CallInstance, cmock_guts_index);
  Mock.PumpDown_Init_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void PumpDown_Init_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PumpDown_Init_CALL_INSTANCE));
  CMOCK_PumpDown_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_PumpDown_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PumpDown_Init_CallInstance = CMock_Guts_MemChain(Mock.PumpDown_Init_CallInstance, cmock_guts_index);
  Mock.PumpDown_Init_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  memcpy(&cmock_call_instance->ReturnVal, &cmock_to_return, sizeof(ErrorCode_t));
  UNITY_CLR_DETAILS();
}

void PumpDown_Init_StubWithCallback(CMOCK_PumpDown_Init_CALLBACK Callback)
{
  Mock.PumpDown_Init_CallbackFunctionPointer = Callback;
}

