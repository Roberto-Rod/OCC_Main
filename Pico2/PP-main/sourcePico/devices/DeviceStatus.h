/*****************************************************************************
 *   File        : DeviceStatus.h
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

#ifndef DEVICE_STATUS_FLAG_H
#define DEVICE_STATUS_FLAG_H

#include "PaTypes.h"

typedef enum
{
  IDLE_E = 0,
  PUMP_DOWN_E,
  THERAPY_DELIVERY_E,
  SHUT_DOWN_E,
  FAULT_E,
  NRE_E,
  POST_E,
  NONE_E
} State_t;

typedef enum
{
  NRE_NO_EVENT = 0,
  NRE_LOGIC_FAIL_EVENT_E,
  NRE_EXT_SENSOR_UNRELIABLE_EVENT_E,
  NRE_INT_SENSOR_UNRELIABLE_EVENT_E,
  NRE_EXT_SENSOR_OVERHEAT_EVENT_E,
  NRE_INT_SENSOR_OVERHEAT_EVENT_E,
  NRE_VDC_BRIDGE_RANGE_EVENT_E,
  NRE_BAT_EOL_EVENT_E,
  NRE_EEPROM_EOL_EVENT_E
} NRE_Event_t;

void DeviceStatus_Init(void);

void DeviceStatus_StateAndOnEntrySet(const bool_t StateOnEntry, const State_t state);

State_t DeviceStatus_GetState(void);

void DeviceStatus_SetNRE_Event(NRE_Event_t event);
NRE_Event_t DeviceStatus_GetNRE_Event(void);

bool_t DeviceStatus_GetOnEntry(void);
void DeviceStatus_SetLedsOnStatus(bool_t LedsPowerOnStatus);

bool_t DeviceStatus_GetLedsOnStatus(void);

void DeviceStatus_SetCheckStatusAlert(bool_t EnableCheck);
bool_t DeviceStatus_GetCheckStatusAlert(void);

void DeviceStatus_SetDeepSleepModeStatus(bool_t Enable);
bool_t DeviceStatus_isGoingInDeepSleep(void);

bool_t DeviceStatus_IsRunningPump(void);
bool_t DeviceStatus_IsReadingPressureSensor(void);
void DeviceStatus_SetPumpIsRunning(bool_t isRunning);
void DeviceStatus_SetPressureSensorIsReading(bool_t isReading);

void DeviceStatus_SetButtonPressFromLeak(bool_t isPressed);
bool_t DeviceStatus_GetButtonPressFromLeak(void);

#endif //DEVICE_STATUS_FLAG_H
