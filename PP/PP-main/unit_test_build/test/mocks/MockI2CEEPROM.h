/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCKI2CEEPROM_H
#define _MOCKI2CEEPROM_H

#include "I2CEEPROM.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void MockI2CEEPROM_Init(void);
void MockI2CEEPROM_Destroy(void);
void MockI2CEEPROM_Verify(void);




#define I2E_Init_Ignore() I2E_Init_CMockIgnore()
void I2E_Init_CMockIgnore(void);
#define I2E_Init_ExpectAnyArgs() I2E_Init_CMockExpectAnyArgs(__LINE__)
void I2E_Init_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define I2E_Init_Expect() I2E_Init_CMockExpect(__LINE__)
void I2E_Init_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_I2E_Init_CALLBACK)(int cmock_num_calls);
void I2E_Init_StubWithCallback(CMOCK_I2E_Init_CALLBACK Callback);
#define I2E_Read_IgnoreAndReturn(cmock_retval) I2E_Read_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void I2E_Read_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return);
#define I2E_Read_ExpectAnyArgsAndReturn(cmock_retval) I2E_Read_CMockExpectAnyArgsAndReturn(__LINE__, cmock_retval)
void I2E_Read_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return);
#define I2E_Read_ExpectAndReturn(address, data, numBytes, cmock_retval) I2E_Read_CMockExpectAndReturn(__LINE__, address, data, numBytes, cmock_retval)
void I2E_Read_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, uint32_t address, uint8_t* data, uint8_t numBytes, ErrorCode_t cmock_to_return);
typedef ErrorCode_t (* CMOCK_I2E_Read_CALLBACK)(uint32_t address, uint8_t* data, uint8_t numBytes, int cmock_num_calls);
void I2E_Read_StubWithCallback(CMOCK_I2E_Read_CALLBACK Callback);
#define I2E_Read_ExpectWithArrayAndReturn(address, data, data_Depth, numBytes, cmock_retval) I2E_Read_CMockExpectWithArrayAndReturn(__LINE__, address, data, data_Depth, numBytes, cmock_retval)
void I2E_Read_CMockExpectWithArrayAndReturn(UNITY_LINE_TYPE cmock_line, uint32_t address, uint8_t* data, int data_Depth, uint8_t numBytes, ErrorCode_t cmock_to_return);
#define I2E_Read_ReturnThruPtr_data(data) I2E_Read_CMockReturnMemThruPtr_data(__LINE__, data, sizeof(*data))
#define I2E_Read_ReturnArrayThruPtr_data(data, cmock_len) I2E_Read_CMockReturnMemThruPtr_data(__LINE__, data, (int)(cmock_len * (int)sizeof(*data)))
#define I2E_Read_ReturnMemThruPtr_data(data, cmock_size) I2E_Read_CMockReturnMemThruPtr_data(__LINE__, data, cmock_size)
void I2E_Read_CMockReturnMemThruPtr_data(UNITY_LINE_TYPE cmock_line, uint8_t* data, int cmock_size);
#define I2E_Read_IgnoreArg_address() I2E_Read_CMockIgnoreArg_address(__LINE__)
void I2E_Read_CMockIgnoreArg_address(UNITY_LINE_TYPE cmock_line);
#define I2E_Read_IgnoreArg_data() I2E_Read_CMockIgnoreArg_data(__LINE__)
void I2E_Read_CMockIgnoreArg_data(UNITY_LINE_TYPE cmock_line);
#define I2E_Read_IgnoreArg_numBytes() I2E_Read_CMockIgnoreArg_numBytes(__LINE__)
void I2E_Read_CMockIgnoreArg_numBytes(UNITY_LINE_TYPE cmock_line);
#define I2E_Write_IgnoreAndReturn(cmock_retval) I2E_Write_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void I2E_Write_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return);
#define I2E_Write_ExpectAnyArgsAndReturn(cmock_retval) I2E_Write_CMockExpectAnyArgsAndReturn(__LINE__, cmock_retval)
void I2E_Write_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, ErrorCode_t cmock_to_return);
#define I2E_Write_ExpectAndReturn(address, data, numBytes, cmock_retval) I2E_Write_CMockExpectAndReturn(__LINE__, address, data, numBytes, cmock_retval)
void I2E_Write_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, uint32_t address, const uint8_t* data, uint8_t numBytes, ErrorCode_t cmock_to_return);
typedef ErrorCode_t (* CMOCK_I2E_Write_CALLBACK)(uint32_t address, const uint8_t* data, uint8_t numBytes, int cmock_num_calls);
void I2E_Write_StubWithCallback(CMOCK_I2E_Write_CALLBACK Callback);
#define I2E_Write_ExpectWithArrayAndReturn(address, data, data_Depth, numBytes, cmock_retval) I2E_Write_CMockExpectWithArrayAndReturn(__LINE__, address, data, data_Depth, numBytes, cmock_retval)
void I2E_Write_CMockExpectWithArrayAndReturn(UNITY_LINE_TYPE cmock_line, uint32_t address, const uint8_t* data, int data_Depth, uint8_t numBytes, ErrorCode_t cmock_to_return);
#define I2E_Write_IgnoreArg_address() I2E_Write_CMockIgnoreArg_address(__LINE__)
void I2E_Write_CMockIgnoreArg_address(UNITY_LINE_TYPE cmock_line);
#define I2E_Write_IgnoreArg_data() I2E_Write_CMockIgnoreArg_data(__LINE__)
void I2E_Write_CMockIgnoreArg_data(UNITY_LINE_TYPE cmock_line);
#define I2E_Write_IgnoreArg_numBytes() I2E_Write_CMockIgnoreArg_numBytes(__LINE__)
void I2E_Write_CMockIgnoreArg_numBytes(UNITY_LINE_TYPE cmock_line);

#endif
