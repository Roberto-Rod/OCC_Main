/*****************************************************************************
 *   File        : test_HET_43.c
 *
 *   Description: Acceptance test for HET-43 Which tests the TX functionality (specifically in POST State 1)
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

#include "MockAlertManager.h"
#include "MockUIInterfaces.h"
#include "MockLoggingManager.h"

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


#include "Transmit.h"
#include "I2CEEPROM.h"
#include "MockHardwareInterface.h"
#include "MockPowerControl.h"
#include "MockLED.h"
#include "MockPushButton.h"
#include "MockPressure_Part1.h"
#include "MockPump.h"
#include "Mockeusart.h"
#include "Mockadc.h"
#include "MockDutyCycle.h"
#include "MockPerformanceLogger.h"
#include "MockWatchdog.h"

#include "Battery.h"
#include "Mocki2c.h"
#include "Assert.h"

extern void TMR1_CallBack(void);

static bool_t PushButtonPress = FALSE;
static bool_t GreenLEDEnabled = FALSE;
static bool_t OrangeLEDEnabled = FALSE;

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
  MP_DisableExternalPeripheralsSupply_Ignore();
  MP_DisableMainCircuitPower_Ignore();
  MP_EnableRelaxationOscillator_Ignore();

  SetInitialExternalPressure_Ignore();
  InitPumpDownVacuum_Ignore();
  isTargetPumpDownVacuumAchieved_IgnoreAndReturn(FALSE);
  InitTherapyDeliveryVacuum_Ignore();
  DCHistoryReset_Ignore();

  AlertManager_Init_IgnoreAndReturn(EC_OK_E);
  AlertManager_Run_IgnoreAndReturn(EC_OK_E);
  Watchdog_Init_Ignore();
  Watchdog_Clear_Ignore();


  MP_SleepUntilWokenByRelaxationOscillator_Ignore();
  MP_DisablePeripheral_Ignore();

  PushButtonPress = FALSE;
  GreenLEDEnabled = FALSE;
  OrangeLEDEnabled = FALSE;
  PushButton_IsPressed_StubWithCallback(Stub_PushButton_IsPressed);
  LED_SetGreen_StubWithCallback(Stub_LED_SetGreen);
  LED_SetOrange_StubWithCallback(Stub_LED_SetOrange);

  EUSART_Initialize_Ignore();
  I2C_Initialize_Ignore();
  LoggingManager_Init_Ignore();
  LoggingManager_Run_IgnoreAndReturn(EC_OK_E);

  //go through POST
  PORTAbits.RA0 = 0;
  PORTAbits.RA1 = 1;
}

void tearDown(void)
{}

void test_TestTXHappyCase(void)
{
  PerformanceLogger_GetNRE_ExpectAndReturn(FALSE);
  Application_Init();

  // timer callback, nothing happens still inPOST
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  TMR1_CallBack();
  Application_Run();
  
  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  //timer callback, nothing happens still in POST
  TMR1_CallBack();
  Application_Run();
  
  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());

  //simulate first timer tick, no button pressed, no LED change transistion from POST to IDLE
  TMR1_CallBack();
  Application_Run();

  TEST_ASSERT_FALSE(GreenLEDEnabled);
  TEST_ASSERT_FALSE(OrangeLEDEnabled);
  TEST_ASSERT_EQUAL_INT(POST_E, DeviceStatus_GetState());
  TEST_ASSERT_EQUAL_INT(POST_STATE_00, iPOST_getSubStateNum());

  //post 1 is the first one with TX stuff
  PORTAbits.RA0 = PORTAbits.RA0 ? 0 : 1;
  PORTAbits.RA1 = PORTAbits.RA1 ? 0 : 1;
  
  ADC_GetConversion_IgnoreAndReturn(0xABCD);
  EUSART_Write_Expect(1);
  EUSART_Write_Expect(0xCD);
  EUSART_Write_Expect(0xAB);
  EUSART_Write_Expect(1^0xCD^0xAB);
 
  TMR1_CallBack();
  Application_Run();
  
  TEST_ASSERT_EQUAL_INT(POST_STATE_01, iPOST_getSubStateNum());
}

