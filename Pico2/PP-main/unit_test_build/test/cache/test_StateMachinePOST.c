#include "MockDeviceStatus.h"
#include "MockStateMachinePOST_internal.h"
#include "StateMachinePOST.h"
#include "unity.h"


void setUp(void)

{}



void tearDown(void)

{}



void test_OnInitSetsStateToZeroAndReturnsZero(void)

{

  iPOST_setSubStateNum_CMockExpect(31, 0xFF);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((POST_Init())), (

 ((void *)0)

 ), (_U_UINT)(32), UNITY_DISPLAY_STYLE_INT);

}



void test_ifNotDoingPOSTRunTransistionsToIdleState(void)

{

  uint8_t subStateNum = 0;

  ErrorCode_t stateResult;

  State_t newState;



  iPOST_doPOST_CMockExpectAndReturn(41, 0);

  DeviceStatus_SetDeepSleepModeStatus_CMockExpect(42, (bool_t) 

 1

 );

  stateResult = POST_Run((bool_t) 

                        1

                            , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(44), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(45), UNITY_DISPLAY_STYLE_INT);

}



void test_onRunStateTestGoToDefaultWithInvalidSwitch(void)

{

  uint8_t subStateNum = 0;

  ErrorCode_t stateResult;

  State_t newState;



  iPOST_updateSubStateNum_CMockExpect(54);

  iPOST_getSubStateNum_CMockExpectAndReturn(55, POST_STATE_MAX);

  iPOST_StateError_CMockExpectAndReturn(56, EC_OK_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(58), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(59), UNITY_DISPLAY_STYLE_INT);



  iPOST_updateSubStateNum_CMockExpect(61);

  iPOST_getSubStateNum_CMockExpectAndReturn(62, POST_STATE_MAX + 1);

  iPOST_StateError_CMockExpectAndReturn(63, EC_FAILED_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(65), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(66), UNITY_DISPLAY_STYLE_INT);



  iPOST_updateSubStateNum_CMockExpect(68);

  iPOST_getSubStateNum_CMockExpectAndReturn(69, POST_STATE_MAX + 2);

  iPOST_StateError_CMockExpectAndReturn(70, EC_OK_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(72), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(73), UNITY_DISPLAY_STYLE_INT);

}



void test_onRunState00CalledWhenStateIsZero(void)

{

  uint8_t subStateNum = 0;

  ErrorCode_t stateResult;

  State_t newState;



  iPOST_updateSubStateNum_CMockExpect(82);

  iPOST_getSubStateNum_CMockExpectAndReturn(83, subStateNum);

  iPOST_Init_CMockExpect(84);

  iPOST_State00_CMockExpectAndReturn(85, EC_OK_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(87), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(88), UNITY_DISPLAY_STYLE_INT);



  iPOST_updateSubStateNum_CMockExpect(90);

  iPOST_getSubStateNum_CMockExpectAndReturn(91, subStateNum);

  iPOST_Init_CMockExpect(92);

  iPOST_State00_CMockExpectAndReturn(93, EC_FAILED_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(95), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(96), UNITY_DISPLAY_STYLE_INT);

}



void test_onRunState01CalledWhenStateIsOne(void)

{

  uint8_t subStateNum = 1;

  ErrorCode_t stateResult;

  State_t newState;



  iPOST_updateSubStateNum_CMockExpect(105);

  iPOST_getSubStateNum_CMockExpectAndReturn(106, subStateNum);

  iPOST_State01_CMockExpectAndReturn(107, EC_OK_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(109), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(110), UNITY_DISPLAY_STYLE_INT);



  iPOST_updateSubStateNum_CMockExpect(112);

  iPOST_getSubStateNum_CMockExpectAndReturn(113, subStateNum);

  iPOST_State01_CMockExpectAndReturn(114, EC_FAILED_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(116), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(117), UNITY_DISPLAY_STYLE_INT);

}



void test_onRunState02CalledWhenStateIsTwo(void)

{

  uint8_t subStateNum = 2;

  ErrorCode_t stateResult;

  State_t newState;



  iPOST_updateSubStateNum_CMockExpect(126);

  iPOST_getSubStateNum_CMockExpectAndReturn(127, subStateNum);

  iPOST_State02_CMockExpectAndReturn(128, EC_OK_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(130), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(131), UNITY_DISPLAY_STYLE_INT);



  iPOST_updateSubStateNum_CMockExpect(133);

  iPOST_getSubStateNum_CMockExpectAndReturn(134, subStateNum);

  iPOST_State02_CMockExpectAndReturn(135, EC_FAILED_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(137), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(138), UNITY_DISPLAY_STYLE_INT);

}



void test_onRunState03CalledWhenStateIsThree(void)

{

  uint8_t subStateNum = 3;

  ErrorCode_t stateResult;

  State_t newState;



  iPOST_updateSubStateNum_CMockExpect(147);

  iPOST_getSubStateNum_CMockExpectAndReturn(148, subStateNum);

  iPOST_State03_CMockExpectAndReturn(149, EC_OK_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(151), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(152), UNITY_DISPLAY_STYLE_INT);



  iPOST_updateSubStateNum_CMockExpect(154);

  iPOST_getSubStateNum_CMockExpectAndReturn(155, subStateNum);

  iPOST_State03_CMockExpectAndReturn(156, EC_FAILED_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(158), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(159), UNITY_DISPLAY_STYLE_INT);

}



void test_onRunState04CalledWhenStateIsFour(void)

{

  uint8_t subStateNum = 4;

  ErrorCode_t stateResult;

  State_t newState;



  iPOST_updateSubStateNum_CMockExpect(168);

  iPOST_getSubStateNum_CMockExpectAndReturn(169, subStateNum);

  iPOST_State04_CMockExpectAndReturn(170, EC_OK_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(172), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(173), UNITY_DISPLAY_STYLE_INT);



  iPOST_updateSubStateNum_CMockExpect(175);

  iPOST_getSubStateNum_CMockExpectAndReturn(176, subStateNum);

  iPOST_State04_CMockExpectAndReturn(177, EC_FAILED_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(179), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(180), UNITY_DISPLAY_STYLE_INT);

}



void test_onRunState05CalledWhenStateIsFive(void)

{

  uint8_t subStateNum = 5;

  ErrorCode_t stateResult;

  State_t newState;



  iPOST_updateSubStateNum_CMockExpect(189);

  iPOST_getSubStateNum_CMockExpectAndReturn(190, subStateNum);

  iPOST_State05_CMockExpectAndReturn(191, EC_OK_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(193), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(194), UNITY_DISPLAY_STYLE_INT);



  iPOST_updateSubStateNum_CMockExpect(196);

  iPOST_getSubStateNum_CMockExpectAndReturn(197, subStateNum);

  iPOST_State05_CMockExpectAndReturn(198, EC_FAILED_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(200), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(201), UNITY_DISPLAY_STYLE_INT);

}



void test_onRunState06CalledWhenStateIsSix(void)

{

  uint8_t subStateNum = 6;

  ErrorCode_t stateResult;

  State_t newState;



  iPOST_updateSubStateNum_CMockExpect(210);

  iPOST_getSubStateNum_CMockExpectAndReturn(211, subStateNum);

  iPOST_State06_CMockExpectAndReturn(212, EC_OK_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(214), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(215), UNITY_DISPLAY_STYLE_INT);



  iPOST_updateSubStateNum_CMockExpect(217);

  iPOST_getSubStateNum_CMockExpectAndReturn(218, subStateNum);

  iPOST_State06_CMockExpectAndReturn(219, EC_FAILED_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(221), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(222), UNITY_DISPLAY_STYLE_INT);

}



void test_onRunState07CalledWhenStateIsSeven(void)

{

  uint8_t subStateNum = 7;

  ErrorCode_t stateResult;

  State_t newState;



  iPOST_updateSubStateNum_CMockExpect(231);

  iPOST_getSubStateNum_CMockExpectAndReturn(232, subStateNum);

  iPOST_State07_CMockExpectAndReturn(233, EC_OK_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(235), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(236), UNITY_DISPLAY_STYLE_INT);



  iPOST_updateSubStateNum_CMockExpect(238);

  iPOST_getSubStateNum_CMockExpectAndReturn(239, subStateNum);

  iPOST_State07_CMockExpectAndReturn(240, EC_FAILED_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(242), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(243), UNITY_DISPLAY_STYLE_INT);

}



void test_onRunState08CalledWhenStateIsEight(void)

{

  uint8_t subStateNum = 8;

  ErrorCode_t stateResult;

  State_t newState;



  iPOST_updateSubStateNum_CMockExpect(252);

  iPOST_getSubStateNum_CMockExpectAndReturn(253, subStateNum);

  iPOST_State08_CMockExpectAndReturn(254, EC_OK_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(256), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(257), UNITY_DISPLAY_STYLE_INT);



  iPOST_updateSubStateNum_CMockExpect(259);

  iPOST_getSubStateNum_CMockExpectAndReturn(260, subStateNum);

  iPOST_State08_CMockExpectAndReturn(261, EC_FAILED_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(263), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(264), UNITY_DISPLAY_STYLE_INT);

}



void test_onRunState09CalledWhenStateIsNine(void)

{

  uint8_t subStateNum = 9;

  ErrorCode_t stateResult;

  State_t newState;



  iPOST_updateSubStateNum_CMockExpect(273);

  iPOST_getSubStateNum_CMockExpectAndReturn(274, subStateNum);

  iPOST_State09_CMockExpectAndReturn(275, EC_OK_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(277), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(278), UNITY_DISPLAY_STYLE_INT);



  iPOST_updateSubStateNum_CMockExpect(280);

  iPOST_getSubStateNum_CMockExpectAndReturn(281, subStateNum);

  iPOST_State09_CMockExpectAndReturn(282, EC_FAILED_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(284), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(285), UNITY_DISPLAY_STYLE_INT);

}



void test_onRunState10CalledWhenStateIsTen(void)

{

  uint8_t subStateNum = 10;

  ErrorCode_t stateResult;

  State_t newState;



  iPOST_updateSubStateNum_CMockExpect(294);

  iPOST_getSubStateNum_CMockExpectAndReturn(295, subStateNum);

  iPOST_State10_CMockExpectAndReturn(296, EC_OK_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(298), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(299), UNITY_DISPLAY_STYLE_INT);



  iPOST_updateSubStateNum_CMockExpect(301);

  iPOST_getSubStateNum_CMockExpectAndReturn(302, subStateNum);

  iPOST_State10_CMockExpectAndReturn(303, EC_FAILED_E);

  stateResult = POST_Run((bool_t) 

                        0

                             , &newState);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((stateResult)), (

 ((void *)0)

 ), (_U_UINT)(305), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((newState)), (

 ((void *)0)

 ), (_U_UINT)(306), UNITY_DISPLAY_STYLE_INT);

}
