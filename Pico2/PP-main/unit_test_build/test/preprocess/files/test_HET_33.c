#include "Assert.h"
#include "MockWatchdog.h"
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
#include "MockPerformanceLogger.h"
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





static void StubMP_WaitForInterrupInLowPowerIfPossible(int numCall)

{

}





void setUp(void)

{

  HardwareInterface_SystemInitialise_CMockIgnore();

  HardwareInterface_EnableGlobalInterrupt_CMockIgnore();

  HardwareInterface_DisableGlobalInterrupt_CMockIgnore();

  HardwareInterface_EnablePeripheralInterrupt_CMockIgnore();



  PerformanceLogger_GetNRE_CMockExpectAndReturn(93, (bool_t) 

 0

 );



  MP_SetReferenceVoltageBoost_CMockIgnore();

  MP_DisablePumpPWM_CMockIgnore();

  MP_EnableExternalPeripheralsSupply_CMockIgnore();

  MP_DisableExternalPeripheralsSupply_CMockIgnore();

  MP_DisableMainCircuitPower_CMockIgnore();

  MP_EnableRelaxationOscillator_CMockIgnore();

  SetInitialExternalPressure_CMockIgnore();

  GetVacuum_CMockIgnoreAndReturn(102, EC_OK_E);

  InitPumpDownVacuum_CMockIgnore();

  InitTherapyDeliveryVacuum_CMockIgnore();

  DCHistoryReset_CMockIgnore();

  isTargetPumpDownVacuumAchieved_CMockIgnoreAndReturn(106, (bool_t) 

 0

 );



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



  AlertManager_Init_CMockIgnoreAndReturn(115, EC_OK_E);

  AlertManager_Run_CMockIgnoreAndReturn(116, EC_OK_E);



  LoggingManager_Init_CMockIgnore();

  LoggingManager_Run_CMockIgnoreAndReturn(119, EC_OK_E);



  Watchdog_Init_CMockIgnore();

  Watchdog_Clear_CMockIgnore();



  TX_Init_CMockIgnore();

  I2C_Initialize_CMockIgnore();



  MP_SleepUntilWokenByRelaxationOscillator_CMockIgnore();

  MP_DisablePeripheral_CMockIgnore();





  PORTAbits.RA0 = 0;

  PORTAbits.RA1 = 1;

}



void tearDown(void)

{}



void test_TestEEPROMWriteAndReadHappyCase(void)

{



  Application_Init();





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(144), UNITY_DISPLAY_STYLE_INT);



  iPOST_setSubStateNum(0);





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(149), UNITY_DISPLAY_STYLE_INT);



  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(154)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(155)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(156), UNITY_DISPLAY_STYLE_INT);





  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(162)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(163)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(164), UNITY_DISPLAY_STYLE_INT);





  TMR1_CallBack();



  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(171)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(172)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(173), UNITY_DISPLAY_STYLE_INT);





  POSTSubState_t expectedState = POST_STATE_00;

  ADC_GetConversion_CMockIgnoreAndReturn(177, 0x2000);

  for (int count = 1; count < 6; count++)

  {

    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((iPOST_getSubStateNum())), (

   ((void *)0)

   ), (_U_UINT)(180), UNITY_DISPLAY_STYLE_INT);





    PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;

    PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;

    if ((1 == count) || (4 == count) || (5 == count))

    {

      TX_Write_CMockExpectAnyArgsAndReturn(187, EC_OK_E);

    }



    TMR1_CallBack();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(193), UNITY_DISPLAY_STYLE_INT);

    expectedState++;

  }

  UnityAssertEqualNumber((_U_SINT)((POST_STATE_05)), (_U_SINT)((iPOST_getSubStateNum())), (

 ((void *)0)

 ), (_U_UINT)(196), UNITY_DISPLAY_STYLE_INT);





  PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;

  PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;



  I2C_MESSAGE_STATUS ptrVal = I2C_MESSAGE_COMPLETE;

  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;

  uint8_t data[2] = {0xAA, 0x55};

  uint8_t addrData[2] = {0, 0};

  uint8_t readData[2] = {0xAA, 0x55};

  uint8_t EEPROMBusAddr = 0x50;





  I2C_MasterWriteTRBBuild_CMockExpectWithArray(210, 

 ((void *)0)

 , 0, addrData, 2, 4, EEPROMBusAddr);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(211);

  I2C_MasterTRBInsert_CMockExpect(212, 1, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(213);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(214);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(215, &ptrVal, sizeof(*&ptrVal));





  I2C_MasterWriteTRBBuild_CMockExpectWithArray(218, 

 ((void *)0)

 , 0, addrData, 2, 2, EEPROMBusAddr);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(219);

  I2C_MasterReadTRBBuild_CMockExpect(220, 

 ((void *)0)

 , 

 ((void *)0)

 , 2, EEPROMBusAddr);

  I2C_MasterReadTRBBuild_CMockIgnoreArg_ptrb(221);

  I2C_MasterReadTRBBuild_CMockIgnoreArg_pdata(222);

  I2C_MasterReadTRBBuild_CMockReturnMemThruPtr_pdata(223, readData, 2);

  I2C_MasterTRBInsert_CMockExpect(224, 2, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(225);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(226);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(227, &ptrVal, sizeof(*&ptrVal));





  uint8_t TXMessage[4] = {0x06, 0x03, 0x03, 0x06 ^ 0x03 ^ 0x03};

  TX_Write_CMockExpectWithArrayAndReturn(231, TXMessage, 4, 4, EC_OK_E);





  I2C_MasterWriteTRBBuild_CMockExpectWithArray(234, 

 ((void *)0)

 , 0, addrData, 2, 4, EEPROMBusAddr);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(235);

  I2C_MasterTRBInsert_CMockExpect(236, 1, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(237);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(238);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(239, &ptrVal, sizeof(*&ptrVal));





  TMR1_CallBack();

  Application_Run();



}



void test_TestEEPROMWriteAndReadWithIncorrectBytesRead(void)

{

  I2C_MasterWriteTRBBuild_CMockIgnore();

  I2C_MasterReadTRBBuild_CMockIgnore();

  Application_Init();

  iPOST_setSubStateNum(0);





  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(255), UNITY_DISPLAY_STYLE_INT);

  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(259)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(260)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(261), UNITY_DISPLAY_STYLE_INT);





  TMR1_CallBack();

  Application_Run();



  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(267)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(268)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(269), UNITY_DISPLAY_STYLE_INT);





  TMR1_CallBack();



  Application_Run();





  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(277)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(278)));};

  UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(279), UNITY_DISPLAY_STYLE_INT);





  POSTSubState_t expectedState = POST_STATE_00;

  ADC_GetConversion_CMockIgnoreAndReturn(283, 0x2000);

  for (int count = 1; count < 6; count++)

  {

    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((iPOST_getSubStateNum())), (

   ((void *)0)

   ), (_U_UINT)(286), UNITY_DISPLAY_STYLE_INT);





    PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;

    PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;

    if ((1 == count) || (4 == count) || (5 == count))

    {

      TX_Write_CMockExpectAnyArgsAndReturn(293, EC_OK_E);

    }



    TMR1_CallBack();

    Application_Run();



    UnityAssertEqualNumber((_U_SINT)((POST_E)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(299), UNITY_DISPLAY_STYLE_INT);

    expectedState++;

  }

  UnityAssertEqualNumber((_U_SINT)((POST_STATE_05)), (_U_SINT)((iPOST_getSubStateNum())), (

 ((void *)0)

 ), (_U_UINT)(302), UNITY_DISPLAY_STYLE_INT);





  PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;

  PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;



  I2C_MESSAGE_STATUS ptrVal = I2C_MESSAGE_COMPLETE;

  ErrorCode_t result = EC_INVALID_INPUT_PARAMETER_E;

  uint8_t data[2] = {0xAA, 0x55};

  uint8_t addrData[2] = {0, 0};

  uint8_t readData[2] = {0xAA, 0x42};

  uint8_t EEPROMBusAddr = 0x50;





  I2C_MasterWriteTRBBuild_CMockExpectWithArray(316, 

 ((void *)0)

 , 0, addrData, 2, 4, EEPROMBusAddr);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(317);

  I2C_MasterTRBInsert_CMockExpect(318, 1, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(319);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(320);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(321, &ptrVal, sizeof(*&ptrVal));





  I2C_MasterWriteTRBBuild_CMockExpectWithArray(324, 

 ((void *)0)

 , 0, addrData, 2, 2, EEPROMBusAddr);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(325);

  I2C_MasterReadTRBBuild_CMockExpect(326, 

 ((void *)0)

 , 

 ((void *)0)

 , 2, EEPROMBusAddr);

  I2C_MasterReadTRBBuild_CMockIgnoreArg_ptrb(327);

  I2C_MasterReadTRBBuild_CMockIgnoreArg_pdata(328);

  I2C_MasterReadTRBBuild_CMockReturnMemThruPtr_pdata(329, readData, 2);

  I2C_MasterTRBInsert_CMockExpect(330, 2, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(331);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(332);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(333, &ptrVal, sizeof(*&ptrVal));





  uint8_t TXMessage[4] = {0x06, 0x03, 0x01, 0x06 ^ 0x03 ^ 0x01};

  TX_Write_CMockExpectWithArrayAndReturn(337, TXMessage, 4, 4, EC_OK_E);





  I2C_MasterWriteTRBBuild_CMockExpectWithArray(340, 

 ((void *)0)

 , 0, addrData, 2, 4, EEPROMBusAddr);

  I2C_MasterWriteTRBBuild_CMockIgnoreArg_ptrb(341);

  I2C_MasterTRBInsert_CMockExpect(342, 1, 

 ((void *)0)

 , 

 ((void *)0)

 );

  I2C_MasterTRBInsert_CMockIgnoreArg_ptrb_list(343);

  I2C_MasterTRBInsert_CMockIgnoreArg_pflag(344);

  I2C_MasterTRBInsert_CMockReturnMemThruPtr_pflag(345, &ptrVal, sizeof(*&ptrVal));





  TMR1_CallBack();

  Application_Run();





}
