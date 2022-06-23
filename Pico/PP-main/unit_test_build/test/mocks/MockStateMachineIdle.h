/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCKSTATEMACHINEIDLE_H
#define _MOCKSTATEMACHINEIDLE_H

#include "StateMachineIdle.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void MockStateMachineIdle_Init(void);
void MockStateMachineIdle_Destroy(void);
void MockStateMachineIdle_Verify(void);




#define Idle_IgnoreAndReturn(cmock_retval) Idle_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void Idle_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return);
#define Idle_ExpectAnyArgsAndReturn(cmock_retval) Idle_CMockExpectAnyArgsAndReturn(__LINE__, cmock_retval)
void Idle_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return);
#define Idle_ExpectAndReturn(cmock_arg1, cmock_arg2, cmock_retval) Idle_CMockExpectAndReturn(__LINE__, cmock_arg1, cmock_arg2, cmock_retval)
void Idle_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_arg1, State_t* cmock_arg2, ErrorCode_t cmock_to_return);
typedef ErrorCode_t (* CMOCK_Idle_CALLBACK)(bool_t cmock_arg1, State_t* cmock_arg2, int cmock_num_calls);
void Idle_StubWithCallback(CMOCK_Idle_CALLBACK Callback);
#define Idle_ExpectWithArrayAndReturn(cmock_arg1, cmock_arg2, cmock_arg2_Depth, cmock_retval) Idle_CMockExpectWithArrayAndReturn(__LINE__, cmock_arg1, cmock_arg2, cmock_arg2_Depth, cmock_retval)
void Idle_CMockExpectWithArrayAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_arg1, State_t* cmock_arg2, int cmock_arg2_Depth, ErrorCode_t cmock_to_return);
#define Idle_ReturnThruPtr_cmock_arg2(cmock_arg2) Idle_CMockReturnMemThruPtr_cmock_arg2(__LINE__, cmock_arg2, sizeof(*cmock_arg2))
#define Idle_ReturnArrayThruPtr_cmock_arg2(cmock_arg2, cmock_len) Idle_CMockReturnMemThruPtr_cmock_arg2(__LINE__, cmock_arg2, (int)(cmock_len * (int)sizeof(*cmock_arg2)))
#define Idle_ReturnMemThruPtr_cmock_arg2(cmock_arg2, cmock_size) Idle_CMockReturnMemThruPtr_cmock_arg2(__LINE__, cmock_arg2, cmock_size)
void Idle_CMockReturnMemThruPtr_cmock_arg2(UNITY_LINE_TYPE cmock_line, State_t* cmock_arg2, int cmock_size);
#define Idle_IgnoreArg_cmock_arg1() Idle_CMockIgnoreArg_cmock_arg1(__LINE__)
void Idle_CMockIgnoreArg_cmock_arg1(UNITY_LINE_TYPE cmock_line);
#define Idle_IgnoreArg_cmock_arg2() Idle_CMockIgnoreArg_cmock_arg2(__LINE__)
void Idle_CMockIgnoreArg_cmock_arg2(UNITY_LINE_TYPE cmock_line);
#define Idle_Init_IgnoreAndReturn(cmock_retval) Idle_Init_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void Idle_Init_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return);
#define Idle_Init_ExpectAnyArgsAndReturn(cmock_retval) Idle_Init_CMockExpectAnyArgsAndReturn(__LINE__, cmock_retval)
void Idle_Init_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return);
#define Idle_Init_ExpectAndReturn(cmock_retval) Idle_Init_CMockExpectAndReturn(__LINE__, cmock_retval)
void Idle_Init_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return);
typedef ErrorCode_t (* CMOCK_Idle_Init_CALLBACK)(int cmock_num_calls);
void Idle_Init_StubWithCallback(CMOCK_Idle_Init_CALLBACK Callback);

#endif