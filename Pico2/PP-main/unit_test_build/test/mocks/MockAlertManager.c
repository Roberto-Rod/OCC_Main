/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "MockAlertManager.h"

static const char* CMockString_AlertManager_Init = "AlertManager_Init";
static const char* CMockString_AlertManager_Run = "AlertManager_Run";
static const char* CMockString_StartLEDSequence = "StartLEDSequence";
static const char* CMockString_checkLEDSequenceCompleted = "checkLEDSequenceCompleted";
static const char* CMockString_seq = "seq";

typedef struct _CMOCK_AlertManager_Init_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  ErrorCode_t ReturnVal;
  int CallOrder;

} CMOCK_AlertManager_Init_CALL_INSTANCE;

typedef struct _CMOCK_AlertManager_Run_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  ErrorCode_t ReturnVal;
  int CallOrder;

} CMOCK_AlertManager_Run_CALL_INSTANCE;

typedef struct _CMOCK_StartLEDSequence_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  int CallOrder;
  LEDControl_t Expected_seq;
  int IgnoreArg_seq;

} CMOCK_StartLEDSequence_CALL_INSTANCE;

typedef struct _CMOCK_checkLEDSequenceCompleted_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  CMOCK_ARG_MODE IgnoreMode;
  bool_t ReturnVal;
  int CallOrder;

} CMOCK_checkLEDSequenceCompleted_CALL_INSTANCE;

static struct MockAlertManagerInstance
{
  int AlertManager_Init_IgnoreBool;
  ErrorCode_t AlertManager_Init_FinalReturn;
  CMOCK_AlertManager_Init_CALLBACK AlertManager_Init_CallbackFunctionPointer;
  int AlertManager_Init_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE AlertManager_Init_CallInstance;
  int AlertManager_Run_IgnoreBool;
  ErrorCode_t AlertManager_Run_FinalReturn;
  CMOCK_AlertManager_Run_CALLBACK AlertManager_Run_CallbackFunctionPointer;
  int AlertManager_Run_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE AlertManager_Run_CallInstance;
  int StartLEDSequence_IgnoreBool;
  CMOCK_StartLEDSequence_CALLBACK StartLEDSequence_CallbackFunctionPointer;
  int StartLEDSequence_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE StartLEDSequence_CallInstance;
  int checkLEDSequenceCompleted_IgnoreBool;
  bool_t checkLEDSequenceCompleted_FinalReturn;
  CMOCK_checkLEDSequenceCompleted_CALLBACK checkLEDSequenceCompleted_CallbackFunctionPointer;
  int checkLEDSequenceCompleted_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE checkLEDSequenceCompleted_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void MockAlertManager_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  if (Mock.AlertManager_Init_IgnoreBool)
    Mock.AlertManager_Init_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_AlertManager_Init);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.AlertManager_Init_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.AlertManager_Init_CallbackFunctionPointer != NULL)
    Mock.AlertManager_Init_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.AlertManager_Run_IgnoreBool)
    Mock.AlertManager_Run_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_AlertManager_Run);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.AlertManager_Run_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.AlertManager_Run_CallbackFunctionPointer != NULL)
    Mock.AlertManager_Run_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.StartLEDSequence_IgnoreBool)
    Mock.StartLEDSequence_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_StartLEDSequence);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.StartLEDSequence_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.StartLEDSequence_CallbackFunctionPointer != NULL)
    Mock.StartLEDSequence_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.checkLEDSequenceCompleted_IgnoreBool)
    Mock.checkLEDSequenceCompleted_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_checkLEDSequenceCompleted);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.checkLEDSequenceCompleted_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.checkLEDSequenceCompleted_CallbackFunctionPointer != NULL)
    Mock.checkLEDSequenceCompleted_CallInstance = CMOCK_GUTS_NONE;
}

void MockAlertManager_Init(void)
{
  MockAlertManager_Destroy();
}

void MockAlertManager_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  Mock.AlertManager_Init_CallbackFunctionPointer = NULL;
  Mock.AlertManager_Init_CallbackCalls = 0;
  Mock.AlertManager_Run_CallbackFunctionPointer = NULL;
  Mock.AlertManager_Run_CallbackCalls = 0;
  Mock.StartLEDSequence_CallbackFunctionPointer = NULL;
  Mock.StartLEDSequence_CallbackCalls = 0;
  Mock.checkLEDSequenceCompleted_CallbackFunctionPointer = NULL;
  Mock.checkLEDSequenceCompleted_CallbackCalls = 0;
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

ErrorCode_t AlertManager_Init(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_AlertManager_Init);
  CMOCK_AlertManager_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_AlertManager_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.AlertManager_Init_CallInstance);
  Mock.AlertManager_Init_CallInstance = CMock_Guts_MemNext(Mock.AlertManager_Init_CallInstance);
  if (Mock.AlertManager_Init_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.AlertManager_Init_FinalReturn;
    memcpy(&Mock.AlertManager_Init_FinalReturn, &cmock_call_instance->ReturnVal, sizeof(ErrorCode_t));
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.AlertManager_Init_CallbackFunctionPointer != NULL)
  {
    return Mock.AlertManager_Init_CallbackFunctionPointer(Mock.AlertManager_Init_CallbackCalls++);
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

void AlertManager_Init_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_AlertManager_Init_CALL_INSTANCE));
  CMOCK_AlertManager_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_AlertManager_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.AlertManager_Init_CallInstance = CMock_Guts_MemChain(Mock.AlertManager_Init_CallInstance, cmock_guts_index);
  Mock.AlertManager_Init_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.AlertManager_Init_IgnoreBool = (int)1;
}

void AlertManager_Init_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_AlertManager_Init_CALL_INSTANCE));
  CMOCK_AlertManager_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_AlertManager_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.AlertManager_Init_CallInstance = CMock_Guts_MemChain(Mock.AlertManager_Init_CallInstance, cmock_guts_index);
  Mock.AlertManager_Init_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void AlertManager_Init_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_AlertManager_Init_CALL_INSTANCE));
  CMOCK_AlertManager_Init_CALL_INSTANCE* cmock_call_instance = (CMOCK_AlertManager_Init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.AlertManager_Init_CallInstance = CMock_Guts_MemChain(Mock.AlertManager_Init_CallInstance, cmock_guts_index);
  Mock.AlertManager_Init_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  memcpy(&cmock_call_instance->ReturnVal, &cmock_to_return, sizeof(ErrorCode_t));
  UNITY_CLR_DETAILS();
}

void AlertManager_Init_StubWithCallback(CMOCK_AlertManager_Init_CALLBACK Callback)
{
  Mock.AlertManager_Init_CallbackFunctionPointer = Callback;
}

ErrorCode_t AlertManager_Run(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_AlertManager_Run);
  CMOCK_AlertManager_Run_CALL_INSTANCE* cmock_call_instance = (CMOCK_AlertManager_Run_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.AlertManager_Run_CallInstance);
  Mock.AlertManager_Run_CallInstance = CMock_Guts_MemNext(Mock.AlertManager_Run_CallInstance);
  if (Mock.AlertManager_Run_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.AlertManager_Run_FinalReturn;
    memcpy(&Mock.AlertManager_Run_FinalReturn, &cmock_call_instance->ReturnVal, sizeof(ErrorCode_t));
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.AlertManager_Run_CallbackFunctionPointer != NULL)
  {
    return Mock.AlertManager_Run_CallbackFunctionPointer(Mock.AlertManager_Run_CallbackCalls++);
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

void AlertManager_Run_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_AlertManager_Run_CALL_INSTANCE));
  CMOCK_AlertManager_Run_CALL_INSTANCE* cmock_call_instance = (CMOCK_AlertManager_Run_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.AlertManager_Run_CallInstance = CMock_Guts_MemChain(Mock.AlertManager_Run_CallInstance, cmock_guts_index);
  Mock.AlertManager_Run_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.AlertManager_Run_IgnoreBool = (int)1;
}

void AlertManager_Run_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_AlertManager_Run_CALL_INSTANCE));
  CMOCK_AlertManager_Run_CALL_INSTANCE* cmock_call_instance = (CMOCK_AlertManager_Run_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.AlertManager_Run_CallInstance = CMock_Guts_MemChain(Mock.AlertManager_Run_CallInstance, cmock_guts_index);
  Mock.AlertManager_Run_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void AlertManager_Run_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_AlertManager_Run_CALL_INSTANCE));
  CMOCK_AlertManager_Run_CALL_INSTANCE* cmock_call_instance = (CMOCK_AlertManager_Run_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.AlertManager_Run_CallInstance = CMock_Guts_MemChain(Mock.AlertManager_Run_CallInstance, cmock_guts_index);
  Mock.AlertManager_Run_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  memcpy(&cmock_call_instance->ReturnVal, &cmock_to_return, sizeof(ErrorCode_t));
  UNITY_CLR_DETAILS();
}

void AlertManager_Run_StubWithCallback(CMOCK_AlertManager_Run_CALLBACK Callback)
{
  Mock.AlertManager_Run_CallbackFunctionPointer = Callback;
}

void StartLEDSequence(LEDControl_t seq)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_StartLEDSequence);
  CMOCK_StartLEDSequence_CALL_INSTANCE* cmock_call_instance = (CMOCK_StartLEDSequence_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.StartLEDSequence_CallInstance);
  Mock.StartLEDSequence_CallInstance = CMock_Guts_MemNext(Mock.StartLEDSequence_CallInstance);
  if (Mock.StartLEDSequence_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    return;
  }
  if (Mock.StartLEDSequence_CallbackFunctionPointer != NULL)
  {
    Mock.StartLEDSequence_CallbackFunctionPointer(seq, Mock.StartLEDSequence_CallbackCalls++);
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  if (cmock_call_instance->IgnoreMode != CMOCK_ARG_NONE)
  {
  if (!cmock_call_instance->IgnoreArg_seq)
  {
    UNITY_SET_DETAILS(CMockString_StartLEDSequence,CMockString_seq);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_seq), (void*)(&seq), sizeof(LEDControl_t), cmock_line, CMockStringMismatch);
  }

  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_StartLEDSequence(CMOCK_StartLEDSequence_CALL_INSTANCE* cmock_call_instance, LEDControl_t seq)
{
  memcpy(&cmock_call_instance->Expected_seq, &seq, sizeof(LEDControl_t));
  cmock_call_instance->IgnoreArg_seq = 0;
}

void StartLEDSequence_CMockIgnore(void)
{
  Mock.StartLEDSequence_IgnoreBool = (int)1;
}

void StartLEDSequence_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_StartLEDSequence_CALL_INSTANCE));
  CMOCK_StartLEDSequence_CALL_INSTANCE* cmock_call_instance = (CMOCK_StartLEDSequence_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.StartLEDSequence_CallInstance = CMock_Guts_MemChain(Mock.StartLEDSequence_CallInstance, cmock_guts_index);
  Mock.StartLEDSequence_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void StartLEDSequence_CMockExpect(UNITY_LINE_TYPE cmock_line, LEDControl_t seq)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_StartLEDSequence_CALL_INSTANCE));
  CMOCK_StartLEDSequence_CALL_INSTANCE* cmock_call_instance = (CMOCK_StartLEDSequence_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.StartLEDSequence_CallInstance = CMock_Guts_MemChain(Mock.StartLEDSequence_CallInstance, cmock_guts_index);
  Mock.StartLEDSequence_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  CMockExpectParameters_StartLEDSequence(cmock_call_instance, seq);
  UNITY_CLR_DETAILS();
}

void StartLEDSequence_StubWithCallback(CMOCK_StartLEDSequence_CALLBACK Callback)
{
  Mock.StartLEDSequence_CallbackFunctionPointer = Callback;
}

void StartLEDSequence_CMockIgnoreArg_seq(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_StartLEDSequence_CALL_INSTANCE* cmock_call_instance = (CMOCK_StartLEDSequence_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.StartLEDSequence_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_seq = 1;
}

bool_t checkLEDSequenceCompleted(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_SET_DETAIL(CMockString_checkLEDSequenceCompleted);
  CMOCK_checkLEDSequenceCompleted_CALL_INSTANCE* cmock_call_instance = (CMOCK_checkLEDSequenceCompleted_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.checkLEDSequenceCompleted_CallInstance);
  Mock.checkLEDSequenceCompleted_CallInstance = CMock_Guts_MemNext(Mock.checkLEDSequenceCompleted_CallInstance);
  if (Mock.checkLEDSequenceCompleted_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.checkLEDSequenceCompleted_FinalReturn;
    Mock.checkLEDSequenceCompleted_FinalReturn = cmock_call_instance->ReturnVal;
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.checkLEDSequenceCompleted_CallbackFunctionPointer != NULL)
  {
    return Mock.checkLEDSequenceCompleted_CallbackFunctionPointer(Mock.checkLEDSequenceCompleted_CallbackCalls++);
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

void checkLEDSequenceCompleted_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_checkLEDSequenceCompleted_CALL_INSTANCE));
  CMOCK_checkLEDSequenceCompleted_CALL_INSTANCE* cmock_call_instance = (CMOCK_checkLEDSequenceCompleted_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.checkLEDSequenceCompleted_CallInstance = CMock_Guts_MemChain(Mock.checkLEDSequenceCompleted_CallInstance, cmock_guts_index);
  Mock.checkLEDSequenceCompleted_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.checkLEDSequenceCompleted_IgnoreBool = (int)1;
}

void checkLEDSequenceCompleted_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_checkLEDSequenceCompleted_CALL_INSTANCE));
  CMOCK_checkLEDSequenceCompleted_CALL_INSTANCE* cmock_call_instance = (CMOCK_checkLEDSequenceCompleted_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.checkLEDSequenceCompleted_CallInstance = CMock_Guts_MemChain(Mock.checkLEDSequenceCompleted_CallInstance, cmock_guts_index);
  Mock.checkLEDSequenceCompleted_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_NONE;
}

void checkLEDSequenceCompleted_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_checkLEDSequenceCompleted_CALL_INSTANCE));
  CMOCK_checkLEDSequenceCompleted_CALL_INSTANCE* cmock_call_instance = (CMOCK_checkLEDSequenceCompleted_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.checkLEDSequenceCompleted_CallInstance = CMock_Guts_MemChain(Mock.checkLEDSequenceCompleted_CallInstance, cmock_guts_index);
  Mock.checkLEDSequenceCompleted_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->IgnoreMode = CMOCK_ARG_ALL;
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

void checkLEDSequenceCompleted_StubWithCallback(CMOCK_checkLEDSequenceCompleted_CALLBACK Callback)
{
  Mock.checkLEDSequenceCompleted_CallbackFunctionPointer = Callback;
}
