#include "MockWatchdog.h"
#include "MockDutyCycle.h"
#include "Mockadc.h"
#include "MockTransmit.h"
#include "MockI2CEEPROM.h"
#include "MockPump.h"
#include "MockPressure_Part1.h"
#include "MockPushButton.h"
#include "MockLED.h"
#include "MockPowerControl.h"
#include "MockHardwareInterface.h"
#include "Battery.h"
#include "PerformanceLogger.h"
#include "Assert.h"
#include "UIInterfaces.h"
#include "Timer.h"
#include "StateMachinePOST_internal.h"
#include "StateMachinePOST.h"
#include "StateMachineNre.h"
#include "StateMachineFault.h"
#include "StateMachineTherapyDelivery.h"
#include "StateMachineIdle.h"
#include "StateMachineShutdown.h"
#include "StateMachinePumpDown.h"
#include "StateMachineCommon.h"
#include "StateMachine.h"
#include "LoggingManager.h"
#include "AlertManager.h"
#include "Application.h"
#include "pic16lf1509.h"
#include "DeviceStatus.h"
#include "unity.h"
















extern void TMR1_CallBack(void);

static bool_t PushButtonPress = (bool_t) 

                               0

                                    ;

static bool_t GreenLEDEnabled = (bool_t) 

                               0

                                    ;

static bool_t OrangeLEDEnabled = (bool_t) 

                                0

                                     ;

static bool_t PumpActivated = (bool_t) 

                             0

                                  ;



static bool_t Stub_PushButton_IsPressed(int NumCall)

{

  return (PushButtonPress);

}



static void Stub_LED_SetGreen(bool_t on, int NumCall)

{

  GreenLEDEnabled = on;

}



static void Stub_LED_SetOrange(bool_t on, int NumCall)

{

  OrangeLEDEnabled = on;

}







void setUp(void)

{

  HardwareInterface_SystemInitialise_CMockIgnore();

  HardwareInterface_EnableGlobalInterrupt_CMockIgnore();

  HardwareInterface_DisableGlobalInterrupt_CMockIgnore();

  HardwareInterface_EnablePeripheralInterrupt_CMockIgnore();



  MP_SetReferenceVoltageBoost_CMockIgnore();

  MP_DisablePumpPWM_CMockIgnore();

  MP_EnableExternalPeripheralsSupply_CMockIgnore();

  MP_DisableExternalPeripheralsSupply_CMockIgnore();

  MP_DisableMainCircuitPower_CMockIgnore();

  MP_EnableRelaxationOscillator_CMockIgnore();



  SetInitialExternalPressure_CMockIgnore();

  GetVacuum_CMockIgnoreAndReturn(96, EC_OK_E);

  PumpActivate_CMockIgnoreAndReturn(97, EC_OK_E);

  InitPumpDownVacuum_CMockIgnore();

  InitTherapyDeliveryVacuum_CMockIgnore();

  DCHistoryReset_CMockIgnore();

  isTargetPumpDownVacuumAchieved_CMockIgnoreAndReturn(101, (bool_t) 

 0

 );



  MP_SleepUntilWokenByRelaxationOscillator_CMockIgnore();

  MP_DisablePeripheral_CMockIgnore();

  TX_Init_CMockIgnore();

  I2E_Init_CMockIgnore();

  Watchdog_Init_CMockIgnore();

  Watchdog_Clear_CMockIgnore();



  PushButtonPress = (bool_t) 

                   0

                        ;

  GreenLEDEnabled = (bool_t) 

                   0

                        ;

  OrangeLEDEnabled = (bool_t) 

                    0

                         ;

  PumpActivated = (bool_t) 

                 0

                      ;

  PushButton_IsPressed_StubWithCallback(Stub_PushButton_IsPressed);

  LED_SetGreen_StubWithCallback(Stub_LED_SetGreen);

  LED_SetOrange_StubWithCallback(Stub_LED_SetOrange);





  PORTAbits.RA0 = 0;

  PORTAbits.RA1 = 1;

}



void tearDown(void)

{}



void test_RunThroughPostStatesUsingTwoInputLinesDrivenByIct(void)

{

  I2E_Read_CMockIgnoreAndReturn(128, EC_OK_E);

  Application_Init();





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(132), UNITY_DISPLAY_STYLE_INT);

  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(136)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(137)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(138), UNITY_DISPLAY_STYLE_INT);





  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(144)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(145)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(146), UNITY_DISPLAY_STYLE_INT);





  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(152)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(153)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(154), UNITY_DISPLAY_STYLE_INT);







  TX_Write_CMockIgnoreAndReturn(158, EC_OK_E);

  I2E_Write_CMockIgnoreAndReturn(159, EC_OK_E);

  I2E_Read_CMockIgnoreAndReturn(160, EC_OK_E);

  ADC_GetConversion_CMockIgnoreAndReturn(161, 0x2000);



  for(int loopRepetitions = 0; loopRepetitions < 5; loopRepetitions++)

  {

    POSTSubState_t expectedState = POST_STATE_00;



    for(int count = 0; count < POST_STATE_MAX; count++)

    {

      UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((iPOST_getSubStateNum())), (

     ((void *)0)

     ), (_U_UINT)(169), UNITY_DISPLAY_STYLE_INT);





      PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;

      PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;



      TMR1_CallBack();

      Application_Run();



      UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

     ((void *)0)

     ), (_U_UINT)(178), UNITY_DISPLAY_STYLE_INT);

      expectedState++;

    }

    UnityAssertEqualNumber((_U_SINT)((POST_STATE_00)), (_U_SINT)((iPOST_getSubStateNum())), (

   ((void *)0)

   ), (_U_UINT)(181), UNITY_DISPLAY_STYLE_INT);

  }

}





void test_SkipPostAndGoToIdleIfTwoInputPinsAreConfiguredAsInNormalOperationMode(void)

{

  I2E_Read_CMockIgnoreAndReturn(188, EC_OK_E);



  PORTAbits.RA0 = 1;

  PORTAbits.RA1 = 0;



  Application_Init();





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(196), UNITY_DISPLAY_STYLE_INT);

  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(200)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(201)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(202), UNITY_DISPLAY_STYLE_INT);



  PushButton_ResetEvent_CMockIgnore();

  MP_DeepSleep_CMockExpect(205);



  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(210)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(211)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(212), UNITY_DISPLAY_STYLE_INT);



  PushButton_ResetEvent_CMockIgnore();

  MP_DeepSleep_CMockExpect(215);





  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(221)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(222)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(223), UNITY_DISPLAY_STYLE_INT);





  PushButton_ResetEvent_CMockIgnore();

  MP_DeepSleep_CMockExpect(227);



  TMR1_CallBack();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(232), UNITY_DISPLAY_STYLE_INT);







  PORTAbits.RA0 = 0;

  PORTAbits.RA1 = 1;

  PushButtonPress = (bool_t) 

                   1

                       ;

  PushButton_IsShortPress_CMockExpectAndReturn(239, (bool_t) 

 0

 );



  TMR1_CallBack();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(244), UNITY_DISPLAY_STYLE_INT);

}
