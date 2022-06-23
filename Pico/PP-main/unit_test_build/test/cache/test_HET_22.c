#include "Assert.h"
#include "MockWatchdog.h"
#include "MockPerformanceLogger.h"
#include "Mocki2c.h"
#include "MockBattery.h"
#include "MockDutyCycle.h"
#include "Mockadc.h"
#include "MockTransmit.h"
#include "MockPressure_Part1.h"
#include "MockPushButton.h"
#include "MockLED.h"
#include "MockPumpFrequencyTracker.h"
#include "MockPowerControl.h"
#include "MockHardwareInterface.h"
#include "Timer.h"
#include "Pump.h"
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

static uint32_t disablePumpPwmCount = 0;

static uint32_t switchoffVoltageBoostCount = 0;

static uint8_t boostDemand = 0;

static bool_t isShortPress = (bool_t) 

                            0

                                 ;

static bool_t isTargetIpdVacuumAchieved = (bool_t) 

                                         0

                                              ;

static uint32_t enableExternalPeripheralsSupplyCount = 0;





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



static void Stub_MP_EnableExternalPeripheralsSupply(int NumCall)

{



  enableExternalPeripheralsSupplyCount++;

}



static void Stub_MP_DisablePumpPWM(int NumCall)

{

  disablePumpPwmCount++;

}



static void Stub_MP_SetReferenceVoltageBoost(uint8_t demand, int NumCall)

{

  if ((0) == demand)

  {

    switchoffVoltageBoostCount++;

  }

  boostDemand = demand;

}



bool_t Stub_PushButton_IsShortPress()

{

  return isShortPress;

}



bool_t Stub_isTargetPumpDownVacuumAchieved(uint16_t Vacuum, int NumCall)

{

  return isTargetIpdVacuumAchieved;

}





void setUp(void)

{

  HardwareInterface_SystemInitialise_CMockIgnore();

  HardwareInterface_EnableGlobalInterrupt_CMockIgnore();

  HardwareInterface_DisableGlobalInterrupt_CMockIgnore();

  HardwareInterface_EnablePeripheralInterrupt_CMockIgnore();



  MP_DisableExternalPeripheralsSupply_CMockIgnore();

  MP_DisableMainCircuitPower_CMockIgnore();

  MP_EnableRelaxationOscillator_CMockIgnore();



  SetInitialExternalPressure_CMockIgnore();

  GetVacuum_CMockIgnoreAndReturn(136, EC_OK_E);

  InitPumpDownVacuum_CMockIgnore();

  PumpFrequencyTracker_Optimise_CMockIgnoreAndReturn(138, EC_OK_E);

  Battery_CheckVoltageBounds_CMockIgnoreAndReturn(139, EC_OK_E);

  InitTherapyDeliveryVacuum_CMockIgnore();

  DCHistoryReset_CMockIgnore();

  MP_EnablePumpPWM_CMockIgnore();

  AlertManager_Init_CMockIgnoreAndReturn(143, EC_OK_E);

  AlertManager_Run_CMockIgnoreAndReturn(144, EC_OK_E);

  LoggingManager_Init_CMockIgnore();

  LoggingManager_Run_CMockIgnoreAndReturn(146, EC_OK_E);

  PerformanceLogger_SetPumpDownDuration_CMockIgnore();

  MP_SleepUntilWokenByRelaxationOscillator_CMockIgnore();

  MP_DisablePeripheral_CMockIgnore();

  MP_EnableMainCircuitPower_CMockIgnore();

  MP_GetBoostDemand_CMockIgnoreAndReturn(151, ((uint8_t)19));

  PushButton_ResetEvent_CMockIgnore();

  PushButton_GetDepressedTickCount_CMockIgnoreAndReturn(153, 1);

  TX_Init_CMockIgnore();

  I2C_Initialize_CMockIgnore();

  Watchdog_Init_CMockIgnore();

  Watchdog_Clear_CMockIgnore();



  checkLEDSequenceCompleted_CMockIgnoreAndReturn(159, (bool_t) 

 0

 );

  DCCalculateAll_CMockIgnore();

  isTherapyDeliveryLeakDetected_CMockIgnoreAndReturn(161, (bool_t) 

 0

 );

  isTargetTherapyDeliveryVacuumAchieved_CMockIgnoreAndReturn(162, (bool_t) 

 1

 );

  DCPumpOffUpdate_CMockIgnore();



  PushButtonPress = (bool_t) 

                   0

                        ;

  GreenLEDEnabled = (bool_t) 

                   0

                        ;

  OrangeLEDEnabled = (bool_t) 

                    0

                         ;

  enableExternalPeripheralsSupplyCount = 0;

  disablePumpPwmCount = 0;

  switchoffVoltageBoostCount = 0;

  boostDemand = 0;

  isShortPress = (bool_t) 

                0

                     ;

  isTargetIpdVacuumAchieved = (bool_t) 

                             0

                                  ;



  PushButton_IsPressed_StubWithCallback(Stub_PushButton_IsPressed);

  PushButton_IsShortPress_StubWithCallback(Stub_PushButton_IsShortPress);

  isTargetPumpDownVacuumAchieved_StubWithCallback(Stub_isTargetPumpDownVacuumAchieved);

  LED_SetGreen_StubWithCallback(Stub_LED_SetGreen);

  LED_SetOrange_StubWithCallback(Stub_LED_SetOrange);

  MP_SetReferenceVoltageBoost_StubWithCallback(Stub_MP_SetReferenceVoltageBoost);

  MP_DisablePumpPWM_StubWithCallback(Stub_MP_DisablePumpPWM);

  MP_EnableExternalPeripheralsSupply_StubWithCallback(Stub_MP_EnableExternalPeripheralsSupply);





  PORTAbits.RA0 = 1;

  PORTAbits.RA1 = 0;

}



void tearDown(void)

{}



void test_PeriodicallyTurnThePumpOffAndDisableBoostVoltageCircuitToMakeSureThePumpIsDeactivatedWhenNotNeeded(void)

{

  PerformanceLogger_GetNRE_CMockExpectAndReturn(194, (bool_t) 

 0

 );

  Application_Init();





  TMR1_CallBack();

  Application_Run();





  if (!(GreenLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(202)));};

  if (!(OrangeLEDEnabled)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (_U_UINT)((_U_UINT)(203)));};

  UnityAssertEqualNumber((_U_SINT)((IDLE_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(204), UNITY_DISPLAY_STYLE_INT);





  StartLEDSequence_CMockExpect(207, LED_CTRL_PUMP_DOWN_E);





  PushButtonPress = (bool_t) 

                   1

                       ;



  isShortPress = (bool_t) 

                1

                    ;



  TMR1_CallBack();

  Application_Run();





  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(218), UNITY_DISPLAY_STYLE_INT);







  PushButtonPress = (bool_t) 

                   0

                        ;

  isShortPress = (bool_t) 

                0

                     ;

  disablePumpPwmCount = 0;

  switchoffVoltageBoostCount = 0;

  enableExternalPeripheralsSupplyCount = 0;

  for (uint32_t i = 0; 10 > i; i++)

  {

    TMR1_CallBack();

    Application_Run();



  }



  UnityAssertEqualNumber((_U_SINT)((PUMP_DOWN_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(234), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((disablePumpPwmCount)), (

 ((void *)0)

 ), (_U_UINT)(235), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((switchoffVoltageBoostCount)), (

 ((void *)0)

 ), (_U_UINT)(236), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((enableExternalPeripheralsSupplyCount)), (

 ((void *)0)

 ), (_U_UINT)(237), UNITY_DISPLAY_STYLE_INT);





  isTargetIpdVacuumAchieved = (bool_t) 

                             1

                                 ;



  uint32_t tickCount = (200);

  State_t expectedState = PUMP_DOWN_E;











  for (uint32_t i = 0; i < tickCount; i++)

  {



    if (i >= ((200) - 10 ))

    {

       expectedState = THERAPY_DELIVERY_E;

    }



    TMR1_CallBack();

    Application_Run();



    isTargetIpdVacuumAchieved = (bool_t) 

                               1

                                   ;

    UnityAssertEqualNumber((_U_SINT)((expectedState)), (_U_SINT)((DeviceStatus_GetState())), (

   ((void *)0)

   ), (_U_UINT)(261), UNITY_DISPLAY_STYLE_INT);

  }





  UnityAssertEqualNumber((_U_SINT)((204)), (_U_SINT)((disablePumpPwmCount)), (

 ((void *)0)

 ), (_U_UINT)(265), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((204)), (_U_SINT)((switchoffVoltageBoostCount)), (

 ((void *)0)

 ), (_U_UINT)(266), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((enableExternalPeripheralsSupplyCount)), (

 ((void *)0)

 ), (_U_UINT)(267), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(269), UNITY_DISPLAY_STYLE_INT);







  disablePumpPwmCount = 0;

  switchoffVoltageBoostCount = 0;

  enableExternalPeripheralsSupplyCount = 0;

  for (uint32_t i = 0; 10 > i; i++)

  {

    TMR1_CallBack();

    Application_Run();



  }



  UnityAssertEqualNumber((_U_SINT)((THERAPY_DELIVERY_E)), (_U_SINT)((DeviceStatus_GetState())), (

 ((void *)0)

 ), (_U_UINT)(283), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((disablePumpPwmCount)), (

 ((void *)0)

 ), (_U_UINT)(284), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((10)), (_U_SINT)((switchoffVoltageBoostCount)), (

 ((void *)0)

 ), (_U_UINT)(285), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((enableExternalPeripheralsSupplyCount)), (

 ((void *)0)

 ), (_U_UINT)(286), UNITY_DISPLAY_STYLE_INT);



}
