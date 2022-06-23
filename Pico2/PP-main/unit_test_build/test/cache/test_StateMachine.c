#include "MockStateMachineFault.h"
#include "MockStateMachineShutdown.h"
#include "MockStateMachineTherapyDelivery.h"
#include "MockStateMachineNre.h"
#include "MockStateMachinePOST.h"
#include "MockStateMachinePumpDown.h"
#include "MockStateMachineIdle.h"
#include "MockAlertManager.h"
#include "DeviceStatus.h"
#include "StateMachine.h"
#include "unity.h"




static State_t TestIdleReturnState = NONE_E;

static State_t TestPumpDownReturnState = NONE_E;

static State_t TestPOSTReturnState = IDLE_E;

static State_t TestSingleStateReturnError = EC_OK_E;

static ErrorCode_t TestPOSTReturnVal = EC_OK_E;







static ErrorCode_t Stub_Idle(bool_t aCurrentStateOnEntry, State_t *aNewState, int NumCall)

{

  *aNewState = TestIdleReturnState;



  return TestSingleStateReturnError;

}





static ErrorCode_t Stub_POST(bool_t aCurrentStateOnEntry, State_t *aNewState, int NumCall)

{

  *aNewState = TestPOSTReturnState;



  return TestPOSTReturnVal;

}





ErrorCode_t Stub_PumpDown(

                         _Bool 

                              aCurrentStateOnEntry, State_t *aNewState, int NumCall)

{

  *aNewState = TestPumpDownReturnState;



  return TestSingleStateReturnError;

}





void setUp(void)

{

  TestIdleReturnState = NONE_E;

  TestPumpDownReturnState = NONE_E;

  TestSingleStateReturnError = EC_OK_E;



  Idle_Init_CMockExpectAndReturn(68, EC_OK_E);

  PumpDown_Init_CMockExpectAndReturn(69, EC_OK_E);

  TherapyDelivery_Init_CMockExpectAndReturn(70, EC_OK_E);

  POST_Init_CMockExpectAndReturn(71, EC_OK_E);

}



void tearDown(void)

{}





void test_OnInitReturnIdleState(void)

{

  StateMachine_Init();



  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(82), UNITY_DISPLAY_STYLE_INT);

  if ((DeviceStatus_GetOnEntry)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(83)));};

}





void test_RunInIdleStateWithNoButtonPresses(void)

{

  Idle_StubWithCallback(Stub_Idle);

  TestIdleReturnState = IDLE_E;

  TestSingleStateReturnError = EC_OK_E;



  POST_Run_StubWithCallback(Stub_POST);

  TestPOSTReturnVal = EC_OK_E;

  TestPOSTReturnState = IDLE_E;



  StateMachine_Init();



  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(99), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((StateMachine_Run())), (

 ((void *)0)

 ), (_U_UINT)(100), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(101), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((StateMachine_Run())), (

 ((void *)0)

 ), (_U_UINT)(102), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(103), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((StateMachine_Run())), (

 ((void *)0)

 ), (_U_UINT)(104), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(105), UNITY_DISPLAY_STYLE_INT);

  if (!(DeviceStatus_GetOnEntry())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(106)));};

}





void test_RunInIdleStateWithError(void)

{

  Idle_StubWithCallback(Stub_Idle);

  TestIdleReturnState = IDLE_E;

  TestSingleStateReturnError = EC_FAILED_E;



  POST_Run_StubWithCallback(Stub_POST);

  TestPOSTReturnVal = EC_OK_E;

  TestPOSTReturnState = IDLE_E;



  StateMachine_Init();



  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(122), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((StateMachine_Run())), (

 ((void *)0)

 ), (_U_UINT)(123), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(124), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((EC_FAILED_E)), (_U_SINT)((StateMachine_Run())), (

 ((void *)0)

 ), (_U_UINT)(125), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(126), UNITY_DISPLAY_STYLE_INT);

  if (!(DeviceStatus_GetOnEntry())) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(127)));};

}





void test_RunInIdleStateAndGoToPumpDownStateAndTherapyDelivery(void)

{

  Idle_StubWithCallback(Stub_Idle);





  TestIdleReturnState = PUMP_DOWN_E;

  TestSingleStateReturnError = EC_OK_E;



  POST_Run_StubWithCallback(Stub_POST);

  TestPOSTReturnVal = EC_OK_E;

  TestPOSTReturnState = IDLE_E;



  StateMachine_Init();



  StartLEDSequence_CMockExpect(145, LED_CTRL_PUMP_DOWN_E);



  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(147), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((StateMachine_Run())), (

 ((void *)0)

 ), (_U_UINT)(148), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(149), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((StateMachine_Run())), (

 ((void *)0)

 ), (_U_UINT)(150), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(151), UNITY_DISPLAY_STYLE_INT);

  if ((DeviceStatus_GetOnEntry())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(152)));};





  TestPumpDownReturnState = THERAPY_DELIVERY_E;

  TestSingleStateReturnError = EC_OK_E;

  PumpDown_StubWithCallback(Stub_PumpDown);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((StateMachine_Run())), (

 ((void *)0)

 ), (_U_UINT)(159), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(160), UNITY_DISPLAY_STYLE_INT);

  if ((DeviceStatus_GetOnEntry())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(161)));};

}





void test_RunInPumpDownStateReturningUnknownStateAndGoToFaultState(void)

{

  Idle_StubWithCallback(Stub_Idle);

  TestIdleReturnState = PUMP_DOWN_E;

  TestSingleStateReturnError = EC_OK_E;

  POST_Run_StubWithCallback(Stub_POST);

  TestPOSTReturnVal = EC_OK_E;

  TestPOSTReturnState = IDLE_E;

  StateMachine_Init();

  StartLEDSequence_CMockExpect(174, LED_CTRL_PUMP_DOWN_E);



  StateMachine_Run();

  StartLEDSequence_CMockExpect(177, LED_CTRL_LEAK_E);

  StateMachine_Run();

  TestIdleReturnState = NONE_E;

  PumpDown_StubWithCallback(Stub_PumpDown);



  UnityAssertEqualNumber((_U_SINT)((EC_OK_E)), (_U_SINT)((StateMachine_Run())), (

 ((void *)0)

 ), (_U_UINT)(182), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((FAULT_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(183), UNITY_DISPLAY_STYLE_INT);

  if ((DeviceStatus_GetOnEntry())) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(184)));};

}
