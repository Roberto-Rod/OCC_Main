/*****************************************************************************
 *   File        : DeviceStatus.c
 *
 *   Description : Register device status globally as a means for inter-process
 * communication and decoupling between controllers.
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019, 2020 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "DeviceStatus.h"

#define LEDS_ON_MASK                         (0x1)
#define CHECK_STATUS_ALERT_MASK              (0x2)
#define DEEP_SLEEP_MODE_STATUS_MASK          (0x4)
#define BUTTON_PRESS_INITIATED_IN_FAULT_MASK (0x8)

static State_t DeviceState = NONE_E;
static NRE_Event_t NRE_Event = NRE_NO_EVENT;
static bool_t DeviceStateOnEntry = TRUE;
static uint8_t Miscellaneous = 0;
static bool_t isPumpRunning;
static bool_t isPressureSensorReading;

void DeviceStatus_Init(void)
{
  DeviceState = NONE_E;
  DeviceStateOnEntry = TRUE;
  Miscellaneous = 0;
  isPumpRunning = FALSE;
  isPressureSensorReading = FALSE;
}

void DeviceStatus_StateAndOnEntrySet(const bool_t StateOnEntry, const State_t state)
{
  DeviceStateOnEntry = StateOnEntry;
  DeviceState = state;
}

State_t DeviceStatus_GetState(void)
{
  return DeviceState;
}

void DeviceStatus_SetNRE_Event(NRE_Event_t event)
{
  NRE_Event = event;
}

NRE_Event_t DeviceStatus_GetNRE_Event(void)
{
  return NRE_Event;
}

// Test function to check when an OnEntryState function has been called.
// Can be removed to free memory space if needed (remember to update tests accordingly)
bool_t DeviceStatus_GetOnEntry(void)
{
  return DeviceStateOnEntry;
}

void DeviceStatus_SetLedsOnStatus(bool_t LedsPowerOnStatus)
{
  if(LedsPowerOnStatus)
  {
    Miscellaneous |= (uint8_t) (LEDS_ON_MASK);
  }
  else
  {
    Miscellaneous &= (uint8_t) (~LEDS_ON_MASK);
  }
}

bool_t DeviceStatus_GetLedsOnStatus(void)
{
  return ((bool_t) ((LEDS_ON_MASK & Miscellaneous) == LEDS_ON_MASK));
}

void DeviceStatus_SetCheckStatusAlert(bool_t EnableCheck)
{
  if(EnableCheck)
  {
    Miscellaneous |= CHECK_STATUS_ALERT_MASK;
  }
  else
  {
    Miscellaneous &= ~CHECK_STATUS_ALERT_MASK;
  }
}

bool_t DeviceStatus_GetCheckStatusAlert(void)
{
  return ((bool_t) ((CHECK_STATUS_ALERT_MASK & Miscellaneous) == CHECK_STATUS_ALERT_MASK));
}



void DeviceStatus_SetDeepSleepModeStatus(bool_t Enable)
{
  if(Enable)
  {
    Miscellaneous |= DEEP_SLEEP_MODE_STATUS_MASK;
  }
  else
  {
    Miscellaneous &= ~DEEP_SLEEP_MODE_STATUS_MASK;
  }
}

bool_t DeviceStatus_isGoingInDeepSleep(void)
{
  return ((bool_t) ((DEEP_SLEEP_MODE_STATUS_MASK & Miscellaneous) == DEEP_SLEEP_MODE_STATUS_MASK));
}

bool_t DeviceStatus_IsRunningPump(void)
{
  return isPumpRunning;
}

bool_t DeviceStatus_IsReadingPressureSensor(void)
{
  return isPressureSensorReading;
}

void DeviceStatus_SetPumpIsRunning(bool_t isRunning)
{
  isPumpRunning = isRunning;
}

void DeviceStatus_SetPressureSensorIsReading(bool_t isReading)
{
  isPressureSensorReading = isReading;
}

void DeviceStatus_SetButtonPressFromLeak(bool_t isPressed)
{
  if(isPressed)
  {
    Miscellaneous |= BUTTON_PRESS_INITIATED_IN_FAULT_MASK;
  }
  else
  {
    Miscellaneous &= ~BUTTON_PRESS_INITIATED_IN_FAULT_MASK;
  }
}

bool_t DeviceStatus_GetButtonPressFromLeak(void)
{
  return ((bool_t) ((BUTTON_PRESS_INITIATED_IN_FAULT_MASK & Miscellaneous) == BUTTON_PRESS_INITIATED_IN_FAULT_MASK));
}
