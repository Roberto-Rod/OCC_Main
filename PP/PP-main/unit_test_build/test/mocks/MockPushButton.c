/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "MockPushButton.h"

static const char* CMockString_PushButton_GetDepressedTickCount = "PushButton_GetDepressedTickCount";
static const char* CMockString_PushButton_IsLongPress = "PushButton_IsLongPress";
static const char* CMockString_PushButton_IsPressed = "PushButton_IsPressed";
static const char* CMockString_PushButton_IsShortPress = "PushButton_IsShortPress";
static const char* CMockString_PushButton_ResetEvent = "PushButton_ResetEvent";

typedef struct _CMOCK_PushButton_ResetEvent_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  int CallOrder;

} CMOCK_PushButton_ResetEvent_CALL_INSTANCE;

typedef struct _CMOCK_PushButton_IsPressed_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  bool_t ReturnVal;
  int CallOrder;

} CMOCK_PushButton_IsPressed_CALL_INSTANCE;

typedef struct _CMOCK_PushButton_IsShortPress_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  bool_t ReturnVal;
  int CallOrder;

} CMOCK_PushButton_IsShortPress_CALL_INSTANCE;

typedef struct _CMOCK_PushButton_IsLongPress_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  bool_t ReturnVal;
  int CallOrder;

} CMOCK_PushButton_IsLongPress_CALL_INSTANCE;

typedef struct _CMOCK_PushButton_GetDepressedTickCount_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  uint8_t ReturnVal;
  int CallOrder;

} CMOCK_PushButton_GetDepressedTickCount_CALL_INSTANCE;

static struct MockPushButtonInstance
{
  int PushButton_ResetEvent_IgnoreBool;
  CMOCK_PushButton_ResetEvent_CALLBACK PushButton_ResetEvent_CallbackFunctionPointer;
  int PushButton_ResetEvent_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE PushButton_ResetEvent_CallInstance;
  int PushButton_IsPressed_IgnoreBool;
  bool_t PushButton_IsPressed_FinalReturn;
  CMOCK_PushButton_IsPressed_CALLBACK PushButton_IsPressed_CallbackFunctionPointer;
  int PushButton_IsPressed_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE PushButton_IsPressed_CallInstance;
  int PushButton_IsShortPress_IgnoreBool;
  bool_t PushButton_IsShortPress_FinalReturn;
  CMOCK_PushButton_IsShortPress_CALLBACK PushButton_IsShortPress_CallbackFunctionPointer;
  int PushButton_IsShortPress_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE PushButton_IsShortPress_CallInstance;
  int PushButton_IsLongPress_IgnoreBool;
  bool_t PushButton_IsLongPress_FinalReturn;
  CMOCK_PushButton_IsLongPress_CALLBACK PushButton_IsLongPress_CallbackFunctionPointer;
  int PushButton_IsLongPress_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE PushButton_IsLongPress_CallInstance;
  int PushButton_GetDepressedTickCount_IgnoreBool;
  uint8_t PushButton_GetDepressedTickCount_FinalReturn;
  CMOCK_PushButton_GetDepressedTickCount_CALLBACK PushButton_GetDepressedTickCount_CallbackFunctionPointer;
  int PushButton_GetDepressedTickCount_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE PushButton_GetDepressedTickCount_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void MockPushButton_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  if (Mock.PushButton_ResetEvent_IgnoreBool)
    Mock.PushButton_ResetEvent_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_PushButton_ResetEvent);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.PushButton_ResetEvent_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.PushButton_ResetEvent_CallbackFunctionPointer != NULL)
    Mock.PushButton_ResetEvent_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.PushButton_IsPressed_IgnoreBool)
    Mock.PushButton_IsPressed_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_PushButton_IsPressed);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.PushButton_IsPressed_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.PushButton_IsPressed_CallbackFunctionPointer != NULL)
    Mock.PushButton_IsPressed_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.PushButton_IsShortPress_IgnoreBool)
    Mock.PushButton_IsShortPress_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_PushButton_IsShortPress);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.PushButton_IsShortPress_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.PushButton_IsShortPress_CallbackFunctionPointer != NULL)
    Mock.PushButton_IsShortPress_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.PushButton_IsLongPress_IgnoreBool)
    Mock.PushButton_IsLongPress_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_PushButton_IsLongPress);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.PushButton_IsLongPress_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.PushButton_IsLongPress_CallbackFunctionPointer != NULL)
    Mock.PushButton_IsLongPress_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.PushButton_GetDepressedTickCount_IgnoreBool)
    Mock.PushButton_GetDepressedTickCount_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_PushButton_GetDepressedTickCount);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.PushButton_GetDepressedTickCount_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.PushButton_GetDepressedTickCount_CallbackFunctionPointer != NULL)
    Mock.PushButton_GetDepressedTickCount_CallInstance = CMOCK_GUTS_NONE;
}

void MockPushButton_Init(void)
{
  MockPushButton_Destroy();
}

void MockPushButton_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  Mock.PushButton_ResetEvent_CallbackFunctionPointer = NULL;
  Mock.PushButton_ResetEvent_CallbackCalls = 0;
  Mock.PushButton_IsPressed_CallbackFunctionPointer = NULL;
  Mock.PushButton_IsPressed_CallbackCalls = 0;
  Mock.PushButton_IsShortPress_CallbackFunctionPointer = NULL;
  Mock.PushButton_IsShortPress_CallbackCalls = 0;
  Mock.PushButton_IsLongPress_CallbackFunctionPointer = NULL;
  Mock.PushButton_IsLongPress_CallbackCalls = 0;
  Mock.PushButton_GetDepressedTickCount_CallbackFunctionPointer = NULL;
  Mock.PushButton_GetDepressedTickCount_CallbackCalls = 0;
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

void PushButton_ResetEvent(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_PushButton_ResetEvent);
  CMOCK_PushButton_ResetEvent_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_ResetEvent_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.PushButton_ResetEvent_CallInstance);
  Mock.PushButton_ResetEvent_CallInstance = CMock_Guts_MemNext(Mock.PushButton_ResetEvent_CallInstance);
  if (Mock.PushButton_ResetEvent_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    return;
  }
  if (Mock.PushButton_ResetEvent_CallbackFunctionPointer != NULL)
  {
    Mock.PushButton_ResetEvent_CallbackFunctionPointer(Mock.PushButton_ResetEvent_CallbackCalls++);
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  UNITY_CLR_DETAILS();
}

void PushButton_ResetEvent_CMockIgnore(void)
{
  Mock.PushButton_ResetEvent_IgnoreBool = (int)1;
}

void PushButton_ResetEvent_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_ResetEvent_CALL_INSTANCE));
  CMOCK_PushButton_ResetEvent_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_ResetEvent_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_ResetEvent_CallInstance = CMock_Guts_MemChain(Mock.PushButton_ResetEvent_CallInstance, cmock_guts_index);
  Mock.PushButton_ResetEvent_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void PushButton_ResetEvent_CMockExpect(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_ResetEvent_CALL_INSTANCE));
  CMOCK_PushButton_ResetEvent_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_ResetEvent_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_ResetEvent_CallInstance = CMock_Guts_MemChain(Mock.PushButton_ResetEvent_CallInstance, cmock_guts_index);
  Mock.PushButton_ResetEvent_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  UNITY_CLR_DETAILS();
}

void PushButton_ResetEvent_StubWithCallback(CMOCK_PushButton_ResetEvent_CALLBACK Callback)
{
  Mock.PushButton_ResetEvent_CallbackFunctionPointer = Callback;
}

bool_t PushButton_IsPressed(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_PushButton_IsPressed);
  CMOCK_PushButton_IsPressed_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_IsPressed_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.PushButton_IsPressed_CallInstance);
  Mock.PushButton_IsPressed_CallInstance = CMock_Guts_MemNext(Mock.PushButton_IsPressed_CallInstance);
  if (Mock.PushButton_IsPressed_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.PushButton_IsPressed_FinalReturn;
    Mock.PushButton_IsPressed_FinalReturn = cmock_call_instance->ReturnVal;
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.PushButton_IsPressed_CallbackFunctionPointer != NULL)
  {
    return Mock.PushButton_IsPressed_CallbackFunctionPointer(Mock.PushButton_IsPressed_CallbackCalls++);
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

void PushButton_IsPressed_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_IsPressed_CALL_INSTANCE));
  CMOCK_PushButton_IsPressed_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_IsPressed_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_IsPressed_CallInstance = CMock_Guts_MemChain(Mock.PushButton_IsPressed_CallInstance, cmock_guts_index);
  Mock.PushButton_IsPressed_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.PushButton_IsPressed_IgnoreBool = (int)1;
}

void PushButton_IsPressed_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_IsPressed_CALL_INSTANCE));
  CMOCK_PushButton_IsPressed_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_IsPressed_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_IsPressed_CallInstance = CMock_Guts_MemChain(Mock.PushButton_IsPressed_CallInstance, cmock_guts_index);
  Mock.PushButton_IsPressed_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void PushButton_IsPressed_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_IsPressed_CALL_INSTANCE));
  CMOCK_PushButton_IsPressed_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_IsPressed_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_IsPressed_CallInstance = CMock_Guts_MemChain(Mock.PushButton_IsPressed_CallInstance, cmock_guts_index);
  Mock.PushButton_IsPressed_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

void PushButton_IsPressed_StubWithCallback(CMOCK_PushButton_IsPressed_CALLBACK Callback)
{
  Mock.PushButton_IsPressed_CallbackFunctionPointer = Callback;
}

bool_t PushButton_IsShortPress(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_PushButton_IsShortPress);
  CMOCK_PushButton_IsShortPress_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_IsShortPress_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.PushButton_IsShortPress_CallInstance);
  Mock.PushButton_IsShortPress_CallInstance = CMock_Guts_MemNext(Mock.PushButton_IsShortPress_CallInstance);
  if (Mock.PushButton_IsShortPress_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.PushButton_IsShortPress_FinalReturn;
    Mock.PushButton_IsShortPress_FinalReturn = cmock_call_instance->ReturnVal;
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.PushButton_IsShortPress_CallbackFunctionPointer != NULL)
  {
    return Mock.PushButton_IsShortPress_CallbackFunctionPointer(Mock.PushButton_IsShortPress_CallbackCalls++);
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

void PushButton_IsShortPress_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_IsShortPress_CALL_INSTANCE));
  CMOCK_PushButton_IsShortPress_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_IsShortPress_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_IsShortPress_CallInstance = CMock_Guts_MemChain(Mock.PushButton_IsShortPress_CallInstance, cmock_guts_index);
  Mock.PushButton_IsShortPress_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.PushButton_IsShortPress_IgnoreBool = (int)1;
}

void PushButton_IsShortPress_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_IsShortPress_CALL_INSTANCE));
  CMOCK_PushButton_IsShortPress_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_IsShortPress_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_IsShortPress_CallInstance = CMock_Guts_MemChain(Mock.PushButton_IsShortPress_CallInstance, cmock_guts_index);
  Mock.PushButton_IsShortPress_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void PushButton_IsShortPress_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_IsShortPress_CALL_INSTANCE));
  CMOCK_PushButton_IsShortPress_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_IsShortPress_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_IsShortPress_CallInstance = CMock_Guts_MemChain(Mock.PushButton_IsShortPress_CallInstance, cmock_guts_index);
  Mock.PushButton_IsShortPress_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

void PushButton_IsShortPress_StubWithCallback(CMOCK_PushButton_IsShortPress_CALLBACK Callback)
{
  Mock.PushButton_IsShortPress_CallbackFunctionPointer = Callback;
}

bool_t PushButton_IsLongPress(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_PushButton_IsLongPress);
  CMOCK_PushButton_IsLongPress_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_IsLongPress_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.PushButton_IsLongPress_CallInstance);
  Mock.PushButton_IsLongPress_CallInstance = CMock_Guts_MemNext(Mock.PushButton_IsLongPress_CallInstance);
  if (Mock.PushButton_IsLongPress_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.PushButton_IsLongPress_FinalReturn;
    Mock.PushButton_IsLongPress_FinalReturn = cmock_call_instance->ReturnVal;
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.PushButton_IsLongPress_CallbackFunctionPointer != NULL)
  {
    return Mock.PushButton_IsLongPress_CallbackFunctionPointer(Mock.PushButton_IsLongPress_CallbackCalls++);
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

void PushButton_IsLongPress_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_IsLongPress_CALL_INSTANCE));
  CMOCK_PushButton_IsLongPress_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_IsLongPress_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_IsLongPress_CallInstance = CMock_Guts_MemChain(Mock.PushButton_IsLongPress_CallInstance, cmock_guts_index);
  Mock.PushButton_IsLongPress_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.PushButton_IsLongPress_IgnoreBool = (int)1;
}

void PushButton_IsLongPress_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_IsLongPress_CALL_INSTANCE));
  CMOCK_PushButton_IsLongPress_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_IsLongPress_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_IsLongPress_CallInstance = CMock_Guts_MemChain(Mock.PushButton_IsLongPress_CallInstance, cmock_guts_index);
  Mock.PushButton_IsLongPress_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void PushButton_IsLongPress_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_IsLongPress_CALL_INSTANCE));
  CMOCK_PushButton_IsLongPress_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_IsLongPress_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_IsLongPress_CallInstance = CMock_Guts_MemChain(Mock.PushButton_IsLongPress_CallInstance, cmock_guts_index);
  Mock.PushButton_IsLongPress_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

void PushButton_IsLongPress_StubWithCallback(CMOCK_PushButton_IsLongPress_CALLBACK Callback)
{
  Mock.PushButton_IsLongPress_CallbackFunctionPointer = Callback;
}

uint8_t PushButton_GetDepressedTickCount(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_PushButton_GetDepressedTickCount);
  CMOCK_PushButton_GetDepressedTickCount_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_GetDepressedTickCount_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.PushButton_GetDepressedTickCount_CallInstance);
  Mock.PushButton_GetDepressedTickCount_CallInstance = CMock_Guts_MemNext(Mock.PushButton_GetDepressedTickCount_CallInstance);
  if (Mock.PushButton_GetDepressedTickCount_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.PushButton_GetDepressedTickCount_FinalReturn;
    Mock.PushButton_GetDepressedTickCount_FinalReturn = cmock_call_instance->ReturnVal;
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.PushButton_GetDepressedTickCount_CallbackFunctionPointer != NULL)
  {
    return Mock.PushButton_GetDepressedTickCount_CallbackFunctionPointer(Mock.PushButton_GetDepressedTickCount_CallbackCalls++);
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

void PushButton_GetDepressedTickCount_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, uint8_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_GetDepressedTickCount_CALL_INSTANCE));
  CMOCK_PushButton_GetDepressedTickCount_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_GetDepressedTickCount_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_GetDepressedTickCount_CallInstance = CMock_Guts_MemChain(Mock.PushButton_GetDepressedTickCount_CallInstance, cmock_guts_index);
  Mock.PushButton_GetDepressedTickCount_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.PushButton_GetDepressedTickCount_IgnoreBool = (int)1;
}

void PushButton_GetDepressedTickCount_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, uint8_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_GetDepressedTickCount_CALL_INSTANCE));
  CMOCK_PushButton_GetDepressedTickCount_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_GetDepressedTickCount_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_GetDepressedTickCount_CallInstance = CMock_Guts_MemChain(Mock.PushButton_GetDepressedTickCount_CallInstance, cmock_guts_index);
  Mock.PushButton_GetDepressedTickCount_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void PushButton_GetDepressedTickCount_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, uint8_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_PushButton_GetDepressedTickCount_CALL_INSTANCE));
  CMOCK_PushButton_GetDepressedTickCount_CALL_INSTANCE* cmock_call_instance = (CMOCK_PushButton_GetDepressedTickCount_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.PushButton_GetDepressedTickCount_CallInstance = CMock_Guts_MemChain(Mock.PushButton_GetDepressedTickCount_CallInstance, cmock_guts_index);
  Mock.PushButton_GetDepressedTickCount_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

void PushButton_GetDepressedTickCount_StubWithCallback(CMOCK_PushButton_GetDepressedTickCount_CALLBACK Callback)
{
  Mock.PushButton_GetDepressedTickCount_CallbackFunctionPointer = Callback;
}

