/*****************************************************************************
 *   File        : test_Application.c
 *
 *   Description: Source Code for test Application.
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
#include "Application.h"

#include "MockAlertManager.h"
#include "MockLoggingManager.h"
#include "DeviceStatus.h"

#include "MockStateMachine.h"
#include "MockStateMachineIdle.h"
#include "MockStateMachinePumpDown.h"
#include "MockStateMachineShutdown.h"
#include "MockStateMachineFault.h"
#include "MockStateMachineTherapyDelivery.h"
#include "MockStateMachineNre.h"
#include "MockStateMachineCommon.h"
#include "MockStateMachinePOST.h"

#include "MockTimer.h"
#include "UIInterfaces.h"
#include "Assert.h"

#include "MockHardwareInterface.h"
#include "MockPowerControl.h"
#include "MockLED.h"
#include "MockPushButton.h"
#include "MockPump.h"
#include "MockPressure_Part1.h"
#include "MockDutyCycle.h"
#include "MockPowerControl.h"
#include "MockHardwareInterface.h"
#include "MockWatchdog.h"
#include "MockPerformanceLogger.h"
#include "MockI2CEEPROM.h"
#include "Mocki2c.h"



void setUp(void)
{
  HardwareInterface_EnableGlobalInterrupt_Ignore();
  HardwareInterface_DisableGlobalInterrupt_Ignore();
  Idle_Init_IgnoreAndReturn(EC_OK_E);
  PumpDown_Init_IgnoreAndReturn(EC_OK_E);
  TherapyDelivery_Init_IgnoreAndReturn(EC_OK_E);
  POST_Init_IgnoreAndReturn(EC_OK_E);
}

void tearDown(void)
{}

void test_ApplicationInitInitialiseManagers(void)
{
  TimerCounters_Init_Expect();
  AlertManager_Init_ExpectAndReturn(EC_OK_E);
  StateMachine_Init_ExpectAndReturn(EC_OK_E);

  HardwareInterface_SystemInitialise_Ignore();
  HardwareInterface_EnableGlobalInterrupt_Ignore();
  HardwareInterface_EnablePeripheralInterrupt_Ignore();

  LoggingManager_Init_Expect();
  Watchdog_Init_Expect();
  PerformanceLogger_GetNRE_ExpectAndReturn(FALSE);

  Application_Init();
}

void test_ApplicationSleepGoesToSleepWhenNotAtPOSTStateAndRelaxationOscillatorIsUsed(void)
{
  DeviceStatus_StateAndOnEntrySet(FALSE, IDLE_E);
  MP_SleepUntilWokenByRelaxationOscillator_Expect();
  Application_Stop();

  DeviceStatus_StateAndOnEntrySet(FALSE, PUMP_DOWN_E);
  MP_SleepUntilWokenByRelaxationOscillator_Expect();
  Application_Stop();

  DeviceStatus_StateAndOnEntrySet(FALSE, THERAPY_DELIVERY_E);
  MP_SleepUntilWokenByRelaxationOscillator_Expect();
  Application_Stop();

  DeviceStatus_StateAndOnEntrySet(FALSE, FAULT_E);
  MP_SleepUntilWokenByRelaxationOscillator_Expect();
  Application_Stop();

  DeviceStatus_StateAndOnEntrySet(FALSE, SHUT_DOWN_E);
  MP_SleepUntilWokenByRelaxationOscillator_Expect();
  Application_Stop();

  DeviceStatus_StateAndOnEntrySet(FALSE, NRE_E);
  MP_SleepUntilWokenByRelaxationOscillator_Expect();
  Application_Stop();
}

void test_ApplicationDoesNotGoToSleepWhenAtPOSTStateAndRelaxationOscillatorIsUsed(void)
{
  DeviceStatus_StateAndOnEntrySet(FALSE, POST_E);
  MP_EnableRelaxationOscillator_Expect();
  Application_Stop();
}

void test_RunDoesNotTickControllerWhenTimerFlagIsNotSet()
{
  PM_GetT1Flag_ExpectAndReturn(FALSE);
  PM_GetT1Flag_ExpectAndReturn(TRUE);

  AlertManager_Run_ExpectAndReturn(EC_OK_E);
  StateMachine_Run_ExpectAndReturn(EC_OK_E);
  LoggingManager_Run_ExpectAndReturn(EC_OK_E);
  Watchdog_Clear_Expect();

  //no other expect called
  Application_Run();
}

void test_RunTicksControllersAndState(void)
{
  PM_GetT1Flag_ExpectAndReturn(TRUE);

  AlertManager_Run_ExpectAndReturn(EC_OK_E);
  StateMachine_Run_ExpectAndReturn(EC_OK_E);
  LoggingManager_Run_ExpectAndReturn(EC_OK_E);
  Watchdog_Clear_Expect();

  Application_Run();
}
