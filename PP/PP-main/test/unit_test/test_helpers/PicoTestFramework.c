/*****************************************************************************
 *   File        : PicoTestFramework.c
 *
 *   Description: Source Code for implementation of test framework helper functions.
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
#include "PicoTestFramework.h"
#include "pic16lf1509.h"


#include "MockHardwareInterface.h"
#include "MockPowerControl.h"
#include "MockLED.h"

#include "MockPressure_Part1.h"
#include "MockPump.h"
#include "MockI2CEEPROM.h"
#include "MockTransmit.h"
#include "Mockadc.h"
#include "MockWatchdog.h"

extern void TMR1_CallBack(void);


PicoTestFrameworkIO_t picoTestFrameworkIo;

static void Stub_LED_SetGreen(bool_t isEnabled, int numCall)
{
  picoTestFrameworkIo.isGreenLEDEnabled = isEnabled;
  picoTestFrameworkIo.countSetGreenLED++;
}

static void Stub_LED_SetOrange(bool_t isEnabled, int numCall)
{
  picoTestFrameworkIo.isOrangeLEDEnabled = isEnabled;
  picoTestFrameworkIo.countSetOrangeLED++;
}

static void StubMP_SleepUntilWokenByRelaxationOscillator(int numCall)
{
  picoTestFrameworkIo.countSleepUntilWokenByRelaxationOscillator++;
}

static void StubMP_DisablePeripheral(int numCall)
{
  picoTestFrameworkIo.countDisablePeripheral++;
}

static void StubMP_EnableMainCircuitPower(int numCall)
{
  picoTestFrameworkIo.isMainCircuitPowerEnabled = TRUE;
}

static void StubMP_DisableMainCircuitPower(int numCall)
{
  picoTestFrameworkIo.isMainCircuitPowerEnabled = FALSE;
}

static void StubMP_DeepSleep(int numCall)
{
  picoTestFrameworkIo.countDeepSleep++;
}


// Stub for gettingt the vacuum reading
static ErrorCode_t StubGetVacuum(uint16_t* pInternal, uint16_t* pExternal, uint16_t *pVacuum, int numCall)
{
  *pInternal =  picoTestFrameworkIo.getInternalVacuumMeasurement;
  *pExternal =  picoTestFrameworkIo.getExternalVacuumMeasurement;
  *pVacuum = picoTestFrameworkIo.getVacuumMeasurement;
  picoTestFrameworkIo.getVacuumTickCount++;
  return picoTestFrameworkIo.getVacuumResult;
}

static bool_t StubIsTargetPumpDownVacuumAchieved(uint16_t Vacuum, int numCall)
{
  return picoTestFrameworkIo.isTargetPumpDownVacuumAchieved;
}

static ErrorCode_t StubPumpActivate(bool_t activatePump, int numCall)
{
  picoTestFrameworkIo.isPumpActivated = activatePump;
  if (activatePump) picoTestFrameworkIo.pumpActivateTickCount++;
  return picoTestFrameworkIo.pumpActivateResult;
}

static bool_t StubisTherapyDeliveryLeakDetected(int numCall)
{
  return ((picoTestFrameworkIo.isBoostVoltageDemandAtReference27V) ?
            picoTestFrameworkIo.isTherapyDeliveryLeakDetected:FALSE);
}

static bool_t StubisTargetTherapyDeliveryVacuumAchieved(uint16_t Vacuum, int numCall)
{
  return picoTestFrameworkIo.isTargetTherapyDeliveryVacuumAchieved;
}

static void StubWD_Watchdog_Init(int numCall)
{
  picoTestFrameworkIo.countWatchdogInit++;
  
  //Actual HW register is: "extern volatile WDTCONbits_t WDTCONbits @ 0x097;" 
}

static void StubWD_Watchdog_Clear(int numCall)
{
  picoTestFrameworkIo.countWatchdogClear++;
  
  //Actual HW istruction: asm("clrwdt");
}

void PicoTestFramework_Setup()
{
  //Ignored functions
  HardwareInterface_SystemInitialise_Ignore();
  HardwareInterface_EnableGlobalInterrupt_Ignore();
  HardwareInterface_DisableGlobalInterrupt_Ignore();
  HardwareInterface_EnablePeripheralInterrupt_Ignore();

  MP_SetReferenceVoltageBoost_Ignore();
  MP_DisablePumpPWM_Ignore();
  MP_DisableExternalPeripheralsSupply_Ignore();
  MP_EnableExternalPeripheralsSupply_Ignore();
  MP_EnableFvr_Ignore();
  MP_EnableRelaxationOscillator_Ignore();

  SetInitialExternalPressure_Ignore();
  InitPumpDownVacuum_Ignore();
  InitTherapyDeliveryVacuum_Ignore();

  TX_Init_Ignore();
  I2E_Init_Ignore();

  //Watchdog_Init_Ignore();
  //Watchdog_Clear_Ignore();

  //Stubbed functions
  LED_SetGreen_StubWithCallback(Stub_LED_SetGreen);
  LED_SetOrange_StubWithCallback(Stub_LED_SetOrange);
  MP_SleepUntilWokenByRelaxationOscillator_StubWithCallback(StubMP_SleepUntilWokenByRelaxationOscillator);
  MP_DisablePeripheral_StubWithCallback(StubMP_DisablePeripheral);
  MP_EnableMainCircuitPower_StubWithCallback(StubMP_EnableMainCircuitPower);
  MP_DisableMainCircuitPower_StubWithCallback(StubMP_DisableMainCircuitPower);
  MP_DeepSleep_StubWithCallback(StubMP_DeepSleep);
  PumpActivate_StubWithCallback(StubPumpActivate);
  GetVacuum_StubWithCallback(StubGetVacuum);
  isTargetPumpDownVacuumAchieved_StubWithCallback(StubIsTargetPumpDownVacuumAchieved);
  isTherapyDeliveryLeakDetected_StubWithCallback(StubisTherapyDeliveryLeakDetected);
  isTargetTherapyDeliveryVacuumAchieved_StubWithCallback(StubisTargetTherapyDeliveryVacuumAchieved);
  Watchdog_Init_StubWithCallback(StubWD_Watchdog_Init);
  Watchdog_Clear_StubWithCallback(StubWD_Watchdog_Clear);
  
  //skip through POST
  PORTAbits.RA0 = 1;
  PORTAbits.RA1 = 0;
  PORTAbits.RA5 = 0;

  picoTestFrameworkIo.isPushButtonPress = FALSE;
  picoTestFrameworkIo.isGreenLEDEnabled = FALSE;
  picoTestFrameworkIo.isOrangeLEDEnabled = FALSE;
  picoTestFrameworkIo.isPumpActivated = FALSE;
  picoTestFrameworkIo.countDisablePeripheral = 0;
  picoTestFrameworkIo.countDeepSleep = 0;
  picoTestFrameworkIo.countSleepUntilWokenByRelaxationOscillator = 0;
  picoTestFrameworkIo.countTimerTick = 0;
  picoTestFrameworkIo.countWatchdogInit = 0;
  picoTestFrameworkIo.countWatchdogClear = 0;
  picoTestFrameworkIo.countSetGreenLED = 0;
  picoTestFrameworkIo.countSetOrangeLED = 0;

  picoTestFrameworkIo.countWaitForInterrupInLowPowerIfPossible = 0;
  
  picoTestFrameworkIo.isBoostVoltageDemandAtReference27V = TRUE;
  picoTestFrameworkIo.getVacuumMeasurement = 0;
  picoTestFrameworkIo.getInternalVacuumMeasurement = 0;
  picoTestFrameworkIo.getExternalVacuumMeasurement = 0;
  picoTestFrameworkIo.getVacuumTickCount = 0;
  picoTestFrameworkIo.getVacuumResult = EC_OK_E;
  picoTestFrameworkIo.isTargetPumpDownVacuumAchieved = FALSE;
  picoTestFrameworkIo.isTherapyDeliveryLeakDetected = FALSE;
  picoTestFrameworkIo.isTargetTherapyDeliveryVacuumAchieved = FALSE;
  picoTestFrameworkIo.pumpActivateTickCount = 0;

  
  picoTestFrameworkIo.pumpActivateResult = EC_OK_E;
}

void PicoTestFramework_Tick()
{
//  printf("%s, %d\n", __FUNCTION__, picoTestFrameworkIo.countTimerTick);
  picoTestFrameworkIo.countTimerTick++;
  TMR1_CallBack();
}

void PicoTestFramework_SetPushButton(bool_t isButtonPressed)
{
  PORTAbits.RA5 = isButtonPressed ? 1 : 0;
}

