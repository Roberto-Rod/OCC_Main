/*****************************************************************************
 *   File        : test_HET_31.c
 *
 *   Description: Acceptance test for HET-31
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "unity.h"
#include "DeviceStatus.h"
#include "pic16lf1509.h"
#include "Application.h"

#include "AlertManager.h"
#include "LoggingManager.h"
#include "StateMachine.h"
#include "StateMachineCommon.h"
#include "StateMachinePumpDown.h"
#include "StateMachineShutdown.h"
#include "StateMachineIdle.h"
#include "StateMachineTherapyDelivery.h"
#include "StateMachineFault.h"

#include "StateMachineNre.h"
#include "StateMachinePOST.h"
#include "StateMachinePOST_internal.h"

#include "Timer.h"
#include "UIInterfaces.h"
#include "Assert.h"
#include "PerformanceLogger.h"
#include "Battery.h"


#include "MockHardwareInterface.h"
#include "MockPowerControl.h"
#include "MockLED.h"
#include "MockPushButton.h"
#include "MockPressure_Part1.h"
#include "MockPump.h"
#include "MockI2CEEPROM.h"
#include "MockTransmit.h"
#include "Mockadc.h"
#include "MockDutyCycle.h"
#include "MockWatchdog.h"



extern void TMR1_CallBack(void);
static bool_t PushButtonPress = FALSE;
static bool_t GreenLEDEnabled = FALSE;
static bool_t OrangeLEDEnabled = FALSE;
static bool_t PumpActivated = FALSE;

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
  HardwareInterface_SystemInitialise_Ignore();
  HardwareInterface_EnableGlobalInterrupt_Ignore();
  HardwareInterface_DisableGlobalInterrupt_Ignore();
  HardwareInterface_EnablePeripheralInterrupt_Ignore();
  
  MP_SetReferenceVoltageBoost_Ignore();
  MP_DisablePumpPWM_Ignore();
  MP_EnableExternalPeripheralsSupply_Ignore();
  MP_DisableExternalPeripheralsSupply_Ignore();
  MP_DisableMainCircuitPower_Ignore();
  MP_EnableRelaxationOscillator_Ignore();

  SetInitialExternalPressure_Ignore();
  GetVacuum_IgnoreAndReturn(EC_OK_E); // to review
  PumpActivate_IgnoreAndReturn(EC_OK_E);
  InitPumpDownVacuum_Ignore();
  InitTherapyDeliveryVacuum_Ignore();
  DCHistoryReset_Ignore();
  isTargetPumpDownVacuumAchieved_IgnoreAndReturn(FALSE);

  MP_SleepUntilWokenByRelaxationOscillator_Ignore();
  MP_DisablePeripheral_Ignore();
  TX_Init_Ignore();
  I2E_Init_Ignore();
  Watchdog_Init_Ignore();
  Watchdog_Clear_Ignore();

  PushButtonPress = FALSE;
  GreenLEDEnabled = FALSE;
  OrangeLEDEnabled = FALSE;
  PumpActivated = FALSE;
  PushButton_IsPressed_StubWithCallback(Stub_PushButton_IsPressed);
  LED_SetGreen_StubWithCallback(Stub_LED_SetGreen);
  LED_SetOrange_StubWithCallback(Stub_LED_SetOrange);
  
  //skip through POST
  PORTAbits.RA0 = 0;
  PORTAbits.RA1 = 1;
}

void tearDown(void)
{}

void test_RunThroughPostStatesUsingTwoInputLinesDrivenByIct(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  Application_Init();

  // nothing happens still in POST
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  TMR1_CallBack();
  Application_Run(); 
  
  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  // nothing happens still in POST
  TMR1_CallBack();
  Application_Run();
  
  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  //simulate first timer tick, no button pressed, no LED change still in POST
  TMR1_CallBack();
  Application_Run();
  
  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  
  //simulate more timer ticks, no button pressed, no LED change, execute operations in POST
  //in a loop without being able to go into IDLE (or any other state)
  TX_Write_IgnoreAndReturn(EC_OK_E);
  I2E_Write_IgnoreAndReturn(EC_OK_E);
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  ADC_GetConversion_IgnoreAndReturn(0x2000);
  
  for(int loopRepetitions = 0; loopRepetitions < 5; loopRepetitions++)
  {
    POSTSubState_t expectedState = POST_STATE_00;

    for(int count = 0; count < POST_STATE_MAX; count++)
    {
      TEST_ASSERT_EQUAL_INT(expectedState, iPOST_getSubStateNum());

      //drive to the next POST state
      PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;
      PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;
      
      TMR1_CallBack();
      Application_Run();
      
      TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
      expectedState++;
    }    
    TEST_ASSERT_EQUAL_INT(POST_STATE_00, iPOST_getSubStateNum());
  }
}


void test_SkipPostAndGoToIdleIfTwoInputPinsAreConfiguredAsInNormalOperationMode(void)
{
  I2E_Read_IgnoreAndReturn(EC_OK_E);
  //skip POST
  PORTAbits.RA0 = 1;
  PORTAbits.RA1 = 0;
  
  Application_Init();

  // nothing happens still in POST but nothing is executed
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  TMR1_CallBack();
  Application_Run(); 
 
  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PushButton_ResetEvent_Ignore();
  MP_DeepSleep_Expect();
  // nothing happens still in POST but nothing is exectuted
  TMR1_CallBack();
  Application_Run();
  
  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());

  PushButton_ResetEvent_Ignore();
  MP_DeepSleep_Expect();

  //simulate first timer tick, no button pressed, no LED, change from POST to IDLE
  TMR1_CallBack();
  Application_Run();
  
  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //simulate second timer tick, no button pressed, no LED, still in IDLE and deep sleep mode
  PushButton_ResetEvent_Ignore();
  MP_DeepSleep_Expect();
  
  TMR1_CallBack();
  Application_Run();
    
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
  
  //simulate a third tick, changing the POST pin status, button pressed, no LED, still in IDLE and deep sleep mode
  //skip POST
  PORTAbits.RA0 = 0;
  PORTAbits.RA1 = 1;
  PushButtonPress = TRUE;
  PushButton_IsShortPress_ExpectAndReturn(FALSE);
  
  TMR1_CallBack();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(IDLE_E, DeviceStatus_GetState());
}
