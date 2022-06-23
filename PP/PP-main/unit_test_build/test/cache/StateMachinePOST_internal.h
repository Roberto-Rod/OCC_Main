#include "I2CEEPROM.h"
#include "Transmit.h"
#include "ErrorCode.h"
#include "StateMachineCommon.h"




typedef enum

{

    POST_STATE_INITIAL = 0xFF,

    POST_STATE_00 = 0,

    POST_STATE_01,

    POST_STATE_02,

    POST_STATE_03,

    POST_STATE_04,

    POST_STATE_05,

    POST_STATE_06,

    POST_STATE_07,

    POST_STATE_08,

    POST_STATE_09,

    POST_STATE_10,

    POST_STATE_MAX

} POSTSubState_t;



POSTSubState_t iPOST_getSubStateNum(void);



uint8_t iPOST_doPOST(void);



void iPOST_updateSubStateNum(void);



void iPOST_setSubStateNum(POSTSubState_t newStateNum);



ErrorCode_t iPOST_State00(void);



ErrorCode_t iPOST_State01(void);



ErrorCode_t iPOST_State02(void);



ErrorCode_t iPOST_State03(void);



ErrorCode_t iPOST_State04(void);



ErrorCode_t iPOST_State05(void);



ErrorCode_t iPOST_State06(void);



ErrorCode_t iPOST_State07(void);



ErrorCode_t iPOST_State08(void);



ErrorCode_t iPOST_State09(void);



ErrorCode_t iPOST_State10(void);



ErrorCode_t iPOST_StateError(void);



void iPOST_Init(void);
