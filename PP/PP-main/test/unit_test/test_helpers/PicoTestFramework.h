/*****************************************************************************
 *   File        : PicoTestFramework.h
 *
 *   Description: API's for test framework helper functions.
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

#ifndef PICOONBOARD_PICOTESTFRAMEWORK_H
#define PICOONBOARD_PICOTESTFRAMEWORK_H

#include "PaTypes.h"
#include "ErrorCode.h"

typedef struct {
  bool_t isPushButtonPress;
  bool_t isGreenLEDEnabled;
  bool_t isOrangeLEDEnabled;
  bool_t isPumpActivated;
  bool_t isMainCircuitPowerEnabled;
  
  //flashing LED patterns
  uint32_t countSetGreenLED;
  uint32_t countSetOrangeLED;

  //Wait for interrupt in low power 
  uint32_t countWaitForInterrupInLowPowerIfPossible;

  //timer and sleep counters
  uint16_t countSleepUntilWokenByRelaxationOscillator;
  uint16_t countDisablePeripheral;
  uint16_t countTimerTick;
  uint16_t countDeepSleep;

  //battery related
  bool_t isBoostVoltageDemandAtReference27V;
  
  //pressure related
  uint16_t getInternalVacuumMeasurement;
  uint16_t getExternalVacuumMeasurement;
  uint16_t getVacuumMeasurement;
  uint16_t getVacuumTickCount;
  ErrorCode_t getVacuumResult;
  bool_t isTargetPumpDownVacuumAchieved;
  bool_t isTherapyDeliveryLeakDetected;
  bool_t isTargetTherapyDeliveryVacuumAchieved;
  
  //pump related
  ErrorCode_t pumpActivateResult;
  uint16_t pumpActivateTickCount;

  //watchdog related
  uint16_t countWatchdogInit;
  uint16_t countWatchdogClear;
} PicoTestFrameworkIO_t;

void PicoTestFramework_Tick();
void PicoTestFramework_Setup();
void PicoTestFramework_SetPushButton(bool_t isButtonPressed);

extern PicoTestFrameworkIO_t picoTestFrameworkIo;

#endif //PICOONBOARD_PICOTESTFRAMEWORK_H
