/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "MockStateMachineFault.h"

static const char* CMockString_Fault = "Fault";
static const char* CMockString_aCurrentStateOnEntry = "aCurrentStateOnEntry";
static const char* CMockString_nextState = "nextState";

typedef struct _CMOCK_Fault_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  ErrorCode_t ReturnVal;
  int CallOrder;
  bool_t Expected_aCurrentStateOnEntry;
  State_t* Expected_nextState;
  int Expected_nextState_Depth;
  int ReturnThruPtr_nextState_Used;
  State_t* ReturnThruPtr_nextState_Val;
  int ReturnThruPtr_nextState_Size;
  int IgnoreArg_aCurrentStateOnEntry;
  int IgnoreArg_nextState;

} CMOCK_Fault_CALL_INSTANCE;

static struct MockStateMachineFaultInstance
{
  int Fault_IgnoreBool;
  ErrorCode_t Fault_FinalReturn;
  CMOCK_Fault_CALLBACK Fault_CallbackFunctionPointer;
  int Fault_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE Fault_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void MockStateMachineFault_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  if (Mock.Fault_IgnoreBool)
    Mock.Fault_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_Fault);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.Fault_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.Fault_CallbackFunctionPointer != NULL)
    Mock.Fault_CallInstance = CMOCK_GUTS_NONE;
}

void MockStateMachineFault_Init(void)
{
  MockStateMachineFault_Destroy();
}

void MockStateMachineFault_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  Mock.Fault_CallbackFunctionPointer = NULL;
  Mock.Fault_CallbackCalls = 0;
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

ErrorCode_t Fault(bool_t aCurrentStateOnEntry, State_t* nextState)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_Fault);
  CMOCK_Fault_CALL_INSTANCE* cmock_call_instance = (CMOCK_Fault_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.Fault_CallInstance);
  Mock.Fault_CallInstance = CMock_Guts_MemNext(Mock.Fault_CallInstance);
  if (Mock.Fault_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.Fault_FinalReturn;
    memcpy(&Mock.Fault_FinalReturn, &cmock_call_instance->ReturnVal, sizeof(ErrorCode_t));
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.Fault_CallbackFunctionPointer != NULL)
  {
    return Mock.Fault_CallbackFunctionPointer(aCurrentStateOnEntry, nextState, Mock.Fault_CallbackCalls++);
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  if (cmock_call_instance->IgnoreMode != CMOCK_ARG_NONE)
  {
  if (!cmock_call_instance->IgnoreArg_aCurrentStateOnEntry)
  {
    UNITY_SET_DETAILS(CMockString_Fault,CMockString_aCurrentStateOnEntry);
    UNITY_TEST_ASSERT_EQUAL_INT(cmock_call_instance->Expected_aCurrentStateOnEntry, aCurrentStateOnEntry, cmock_line, CMockStringMismatch);
  }
  if (!cmock_call_instance->IgnoreArg_nextState)
  {
    UNITY_SET_DETAILS(CMockString_Fault,CMockString_nextState);
    if (cmock_call_instance->Expected_nextState == NULL)
      { UNITY_TEST_ASSERT_NULL(nextState, cmock_line, CMockStringExpNULL); }
    else
      { UNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY((void*)(cmock_call_instance->Expected_nextState), (void*)(nextState), sizeof(State_t), cmock_call_instance->Expected_nextState_Depth, cmock_line, CMockStringMismatch); }
  }

  }
  if (cmock_call_instance->ReturnThruPtr_nextState_Used)
  {
    memcpy(nextState, cmock_call_instance->ReturnThruPtr_nextState_Val,
      cmock_call_instance->ReturnThruPtr_nextState_Size);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_Fault(CMOCK_Fault_CALL_INSTANCE* cmock_call_instance, bool_t aCurrentStateOnEntry, State_t* nextState, int nextState_Depth)
{
  cmock_call_instance->Expected_aCurrentStateOnEntry = aCurrentStateOnEntry;
  cmock_call_instance->IgnoreArg_aCurrentStateOnEntry = 0;
  cmock_call_instance->Expected_nextState = nextState;
  cmock_call_instance->Expected_nextState_Depth = nextState_Depth;
  cmock_call_instance->IgnoreArg_nextState = 0;
  cmock_call_instance->ReturnThruPtr_nextState_Used = 0;
}

void Fault_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Fault_CALL_INSTANCE));
  CMOCK_Fault_CALL_INSTANCE* cmock_call_instance = (CMOCK_Fault_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Fault_CallInstance = CMock_Guts_MemChain(Mock.Fault_CallInstance, cmock_guts_index);
  Mock.Fault_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.Fault_IgnoreBool = (int)1;
}

void Fault_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Fault_CALL_INSTANCE));
  CMOCK_Fault_CALL_INSTANCE* cmock_call_instance = (CMOCK_Fault_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Fault_CallInstance = CMock_Guts_MemChain(Mock.Fault_CallInstance, cmock_guts_index);
  Mock.Fault_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void Fault_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, bool_t aCurrentStateOnEntry, State_t* nextState, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Fault_CALL_INSTANCE));
  CMOCK_Fault_CALL_INSTANCE* cmock_call_instance = (CMOCK_Fault_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Fault_CallInstance = CMock_Guts_MemChain(Mock.Fault_CallInstance, cmock_guts_index);
  Mock.Fault_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  CMockExpectParameters_Fault(cmock_call_instance, aCurrentStateOnEntry, nextState, 1);
  memcpy(&cmock_call_instance->ReturnVal, &cmock_to_return, sizeof(ErrorCode_t));
  UNITY_CLR_DETAILS();
}

void Fault_StubWithCallback(CMOCK_Fault_CALLBACK Callback)
{
  Mock.Fault_CallbackFunctionPointer = Callback;
}

void Fault_CMockExpectWithArrayAndReturn(UNITY_LINE_TYPE cmock_line, bool_t aCurrentStateOnEntry, State_t* nextState, int nextState_Depth, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Fault_CALL_INSTANCE));
  CMOCK_Fault_CALL_INSTANCE* cmock_call_instance = (CMOCK_Fault_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Fault_CallInstance = CMock_Guts_MemChain(Mock.Fault_CallInstance, cmock_guts_index);
  Mock.Fault_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  CMockExpectParameters_Fault(cmock_call_instance, aCurrentStateOnEntry, nextState, nextState_Depth);
  cmock_call_instance->ReturnVal = cmock_to_return;
}

void Fault_CMockReturnMemThruPtr_nextState(UNITY_LINE_TYPE cmock_line, State_t* nextState, int cmock_size)
{
  CMOCK_Fault_CALL_INSTANCE* cmock_call_instance = (CMOCK_Fault_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.Fault_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringPtrPreExp);
  cmock_call_instance->ReturnThruPtr_nextState_Used = 1;
  cmock_call_instance->ReturnThruPtr_nextState_Val = nextState;
  cmock_call_instance->ReturnThruPtr_nextState_Size = cmock_size;
}

void Fault_CMockIgnoreArg_aCurrentStateOnEntry(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_Fault_CALL_INSTANCE* cmock_call_instance = (CMOCK_Fault_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.Fault_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_aCurrentStateOnEntry = 1;
}

void Fault_CMockIgnoreArg_nextState(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_Fault_CALL_INSTANCE* cmock_call_instance = (CMOCK_Fault_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.Fault_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_nextState = 1;
}
