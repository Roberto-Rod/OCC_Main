#include "Assert.h"
#include "Mocki2c.h"
#include "Battery.h"
#include "MockWatchdog.h"
#include "MockPerformanceLogger.h"
#include "MockDutyCycle.h"
#include "Mockadc.h"
#include "Mockeusart.h"
#include "MockPump.h"
#include "MockPressure_Part1.h"
#include "MockPushButton.h"
#include "MockLED.h"
#include "MockPowerControl.h"
#include "MockHardwareInterface.h"
#include "I2CEEPROM.h"
#include "Transmit.h"
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
#include "MockLoggingManager.h"
#include "MockUIInterfaces.h"
#include "MockAlertManager.h"
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

  MP_DisableExternalPeripheralsSupply_CMockIgnore();

  MP_DisableMainCircuitPower_CMockIgnore();

  MP_EnableRelaxationOscillator_CMockIgnore();



  SetInitialExternalPressure_CMockIgnore();

  InitPumpDownVacuum_CMockIgnore();

  isTargetPumpDownVacuumAchieved_CMockIgnoreAndReturn(98, (bool_t) 

 0

 );

  InitTherapyDeliveryVacuum_CMockIgnore();

  DCHistoryReset_CMockIgnore();



  AlertManager_Init_CMockIgnoreAndReturn(102, EC_OK_E);

  AlertManager_Run_CMockIgnoreAndReturn(103, EC_OK_E);

  Watchdog_Init_CMockIgnore();

  Watchdog_Clear_CMockIgnore();





  MP_SleepUntilWokenByRelaxationOscillator_CMockIgnore();

  MP_DisablePeripheral_CMockIgnore();



  PushButtonPress = (bool_t) 

                   0

                        ;

  GreenLEDEnabled = (bool_t) 

                   0

                        ;

  OrangeLEDEnabled = (bool_t) 

                    0

                         ;

  PushButton_IsPressed_StubWithCallback(Stub_PushButton_IsPressed);

  LED_SetGreen_StubWithCallback(Stub_LED_SetGreen);

  LED_SetOrange_StubWithCallback(Stub_LED_SetOrange);



  EUSART_Initialize_CMockIgnore();

  I2C_Initialize_CMockIgnore();

  LoggingManager_Init_CMockIgnore();

  LoggingManager_Run_CMockIgnoreAndReturn(121, EC_OK_E);





  PORTAbits.RA0 = 0;

  PORTAbits.RA1 = 1;

}



void tearDown(void)

{}



void test_TestTXHappyCase(void)

{

  PerformanceLogger_GetNRE_CMockExpectAndReturn(133, (bool_t) 

 0

 );

  Application_Init();





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(137), UNITY_DISPLAY_STYLE_INT);

  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(141)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(142)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(143), UNITY_DISPLAY_STYLE_INT);





  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(149)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(150)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(151), UNITY_DISPLAY_STYLE_INT);





  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(157)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(158)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(159), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((POST_STATE_00)), (_U_SINT)((iPOST_getSubStateNum())), (

 ((void *)0)

 ), (_U_UINT)(160), UNITY_DISPLAY_STYLE_INT);





  PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;

  PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;



  ADC_GetConversion_CMockIgnoreAndReturn(166, 0xABCD);

  EUSART_Write_CMockExpect(167, 1);

  EUSART_Write_CMockExpect(168, 0xCD);

  EUSART_Write_CMockExpect(169, 0xAB);

  EUSART_Write_CMockExpect(170, 1^0xCD^0xAB);



  TMR1_CallBack();

  Application_Run();



  UnityAssertEqualNumber((_U_SINT)((POST_STATE_01)), (_U_SINT)((iPOST_getSubStateNum())), (

 ((void *)0)

 ), (_U_UINT)(175), UNITY_DISPLAY_STYLE_INT);

}
