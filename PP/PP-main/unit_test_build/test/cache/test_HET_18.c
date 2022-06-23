#include "Assert.h"
#include "MockWatchdog.h"
#include "MockPerformanceLogger.h"
#include "Mocki2c.h"
#include "Battery.h"
#include "MockDutyCycle.h"
#include "Mockadc.h"
#include "MockTransmit.h"
#include "MockPump.h"
#include "MockPressure_Part1.h"
#include "MockPushButton.h"
#include "MockLED.h"
#include "MockPowerControl.h"
#include "MockHardwareInterface.h"
#include "Timer.h"
#include "I2CEEPROM.h"
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
#include "MockUIInterfaces.h"
#include "MockLoggingManager.h"
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

  MP_EnableExternalPeripheralsSupply_CMockIgnore();

  MP_DisableExternalPeripheralsSupply_CMockIgnore();

  MP_DisableMainCircuitPower_CMockIgnore();

  MP_EnableRelaxationOscillator_CMockIgnore();





  SetInitialExternalPressure_CMockIgnore();

  GetVacuum_CMockIgnoreAndReturn(95, EC_OK_E);

  InitPumpDownVacuum_CMockIgnore();

  isTargetPumpDownVacuumAchieved_CMockIgnoreAndReturn(97, (bool_t) 

 0

 );

  InitTherapyDeliveryVacuum_CMockIgnore();

  DCHistoryReset_CMockIgnore();



  AlertManager_Init_CMockIgnoreAndReturn(101, EC_OK_E);



  AlertManager_Run_CMockIgnoreAndReturn(103, EC_OK_E);



  LoggingManager_Init_CMockIgnore();

  LoggingManager_Run_CMockIgnoreAndReturn(106, EC_OK_E);



  MP_SleepUntilWokenByRelaxationOscillator_CMockIgnore();

  MP_DisablePeripheral_CMockIgnore();

  TX_Init_CMockIgnore();

  I2C_Initialize_CMockIgnore();

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



  PushButton_IsPressed_StubWithCallback(Stub_PushButton_IsPressed);

  LED_SetGreen_StubWithCallback(Stub_LED_SetGreen);

  LED_SetOrange_StubWithCallback(Stub_LED_SetOrange);





  PORTAbits.RA0 = 0;

  PORTAbits.RA1 = 1;

}



void tearDown(void)

{}



void test_TestEEPROMWriteAndReadHappyCase(void)

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





  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(142)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(143)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(144), UNITY_DISPLAY_STYLE_INT);





  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(150)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(151)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(152), UNITY_DISPLAY_STYLE_INT);





  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(158)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(159)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(160), UNITY_DISPLAY_STYLE_INT);





  POSTSubState_t expectedState = POST_STATE_00;

  ADC_GetConversion_CMockIgnoreAndReturn(164, 0x2000);

  for (int count = 1; count < 6; count++)

  {

    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((iPOST_getSubStateNum())), (

   ((void *)0)

   ), (_U_UINT)(167), UNITY_DISPLAY_STYLE_INT);





    PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;

    PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;

    if ((1 == count) || (4 == count) || (5 == count))

    {

      TX_Write_CMockExpectAnyArgsAndReturn(174, EC_OK_E);

    }



    TMR1_CallBack();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(180), UNITY_DISPLAY_STYLE_INT);

    expectedState++;

  }

  UnityAssertEqualNumber((_U_SINT)((POST_STATE_05)), (_U_SINT)((iPOST_getSubStateNum())), (

 ((void *)0)

 ), (_U_UINT)(183), UNITY_DISPLAY_STYLE_INT);







  PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;

  PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;



  I2C_MESSAGE_STATUS ptrVal = I2C_MESSAGE_COMPLETE;

  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;

  uint8_t data[2] = {0xAA, 0x55};

  uint8_t addrData[2] = {0, 0};

  uint8_t readData[2] = {0xAA, 0x55};

  uint8_t EEPROMBusAddr = 0x50;





  I2C_MasterWriteTRBBuild_CMockExpectWithArray(198, 

 ((void *)0)

 , 0, addrData, 2, 4, EEPROMBusAddr);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(199);

  I2C_MasterTRBInsert_CMockExpect(200, 1, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(201);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(202);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(203, &ptrVal, sizeof(*&ptrVal));





  I2C_MasterWriteTRBBuild_CMockExpectWithArray(206, 

 ((void *)0)

 , 0, addrData, 2, 2, EEPROMBusAddr);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(207);

  I2C_MasterReadTRBBuild_CMockExpect(208, 

 ((void *)0)

 , 

 ((void *)0)

 , 2, EEPROMBusAddr);

  I2C_MasterReadTRBBuild_CMockIgnoreArg_ptrb(209);

  I2C_MasterReadTRBBuild_CMockIgnoreArg_pdata(210);

  I2C_MasterReadTRBBuild_CMockReturnMemThruPtr_pdata(211, readData, 2);

  I2C_MasterTRBInsert_CMockExpect(212, 2, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(213);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(214);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(215, &ptrVal, sizeof(*&ptrVal));





  uint8_t TXMessage[4] = {0x06, 0x03, 0x03, 0x06 ^ 0x03 ^ 0x03};

  TX_Write_CMockExpectWithArrayAndReturn(219, TXMessage, 4, 4, EC_OK_E);





  I2C_MasterWriteTRBBuild_CMockExpectWithArray(222, 

 ((void *)0)

 , 0, addrData, 2, 4, EEPROMBusAddr);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(223);

  I2C_MasterTRBInsert_CMockExpect(224, 1, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(225);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(226);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(227, &ptrVal, sizeof(*&ptrVal));







  TMR1_CallBack();

  Application_Run();



}



void test_TestEEPROMWriteAndReadWithIncorrectBytesRead(void)

{

  PerformanceLogger_GetNRE_CMockExpectAndReturn(238, (bool_t) 

 0

 );

  Application_Init();

  iPOST_setSubStateNum(0);





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(243), UNITY_DISPLAY_STYLE_INT);

  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(247)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(248)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(249), UNITY_DISPLAY_STYLE_INT);





  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(255)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(256)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(257), UNITY_DISPLAY_STYLE_INT);





  TMR1_CallBack();



  Application_Run();





  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(265)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(266)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(267), UNITY_DISPLAY_STYLE_INT);





  POSTSubState_t expectedState = POST_STATE_00;

  ADC_GetConversion_CMockIgnoreAndReturn(271, 0x2000);

  for (int count = 1; count < 6; count++)

  {

    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((iPOST_getSubStateNum())), (

   ((void *)0)

   ), (_U_UINT)(274), UNITY_DISPLAY_STYLE_INT);





    PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;

    PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;

    if ((1 == count) || (4 == count) || (5 == count))

    {

      TX_Write_CMockExpectAnyArgsAndReturn(281, EC_OK_E);

    }



    TMR1_CallBack();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(287), UNITY_DISPLAY_STYLE_INT);

    expectedState++;

  }

  UnityAssertEqualNumber((_U_SINT)((POST_STATE_05)), (_U_SINT)((iPOST_getSubStateNum())), (

 ((void *)0)

 ), (_U_UINT)(290), UNITY_DISPLAY_STYLE_INT);





  PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;

  PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;



  I2C_MESSAGE_STATUS ptrVal = I2C_MESSAGE_COMPLETE;

  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;

  uint8_t data[2] = {0xAA, 0x55};

  uint8_t addrData[2] = {0, 0};

  uint8_t readData[2] = {0xAA, 0x42};

  uint8_t EEPROMBusAddr = 0x50;





  I2C_MasterWriteTRBBuild_CMockExpectWithArray(304, 

 ((void *)0)

 , 0, addrData, 2, 4, EEPROMBusAddr);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(305);

  I2C_MasterTRBInsert_CMockExpect(306, 1, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(307);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(308);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(309, &ptrVal, sizeof(*&ptrVal));





  I2C_MasterWriteTRBBuild_CMockExpectWithArray(312, 

 ((void *)0)

 , 0, addrData, 2, 2, EEPROMBusAddr);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(313);

  I2C_MasterReadTRBBuild_CMockExpect(314, 

 ((void *)0)

 , 

 ((void *)0)

 , 2, EEPROMBusAddr);

  I2C_MasterReadTRBBuild_CMockIgnoreArg_ptrb(315);

  I2C_MasterReadTRBBuild_CMockIgnoreArg_pdata(316);

  I2C_MasterReadTRBBuild_CMockReturnMemThruPtr_pdata(317, readData, 2);

  I2C_MasterTRBInsert_CMockExpect(318, 2, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(319);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(320);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(321, &ptrVal, sizeof(*&ptrVal));





  uint8_t TXMessage[4] = {0x06, 0x03, 0x01, 0x06 ^ 0x03 ^ 0x01};

  TX_Write_CMockExpectWithArrayAndReturn(325, TXMessage, 4, 4, EC_OK_E);







  I2C_MasterWriteTRBBuild_CMockExpectWithArray(329, 

 ((void *)0)

 , 0, addrData, 2, 4, EEPROMBusAddr);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(330);

  I2C_MasterTRBInsert_CMockExpect(331, 1, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(332);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(333);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(334, &ptrVal, sizeof(*&ptrVal));





  TMR1_CallBack();

  Application_Run();



}
