/*****************************************************************************
 *   File        : PerformanceLogger.h
 *
 *   Description : Header file for performance logging on the EEPROM
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

#ifndef PICOONBOARD_PERFORMANCELOGGER_H
#define PICOONBOARD_PERFORMANCELOGGER_H

#include "ErrorCode.h"
#include "PaTypes.h"

typedef struct PerformanceLogger_tag
{
  uint16_t differentialPressureMilliBar;
  uint16_t externalPressureMilliBar;
  uint32_t pumpHistory;
  uint16_t batteryVoltageMilliVolts;
  uint16_t intTemperatureRaw;
  uint16_t extTemperatureRaw;
  uint8_t deviceStatus;
  uint8_t lastPumpDownDuration100Ms;
  //uint8_t reserveByte2;
} PerformanceLogger_t;    //16 bytes in total, Keep all the fields 16 bit aligned so to avoid empty bytes

void PerformanceLogger_Init(void);

void PerformanceLogger_SetDifferentialPressure(const uint16_t pressureMilliBar);
void PerformanceLogger_SetExternalPressure(const uint16_t pressureMilliBar);
void PerformanceLogger_SetPumpHistory(const uint32_t pumpHistory);
void PerformanceLogger_SetBatteryVoltage(const uint16_t voltageMilliVolts);
void PerformanceLogger_SetInternalTemperature(const uint16_t temperatureRawSensorValue);
void PerformanceLogger_SetExternalTemperature(const uint16_t temperatureRawSensorValue);
void PerformanceLogger_SetStatus(const uint8_t deviceStatus);
void PerformanceLogger_SetPumpDownDuration(const uint8_t duration100Ms);
void PerformanceLogger_SetIPDDuration(const uint8_t durationTicks);
uint8_t PerformanceLogger_GetPumpDownDuration100Ms();
void PerformanceLogger_SkipToNextTimeline(void);
/**
 * Log performance record to persistence storage and move the storage pointer forward.
 * @param performanceLogger struct contains the performance data
 */
ErrorCode_t PerformanceLogger_Persist(void);

ErrorCode_t PerformanceLogger_SetNRE(void);
bool PerformanceLogger_GetNRE(void);

PerformanceLogger_t* PerformanceLogger_Get();
uint32_t PerformanceLogger_GetCurrentAddress(void);
void PerformanceLogger_SetCurrentAddress(const uint32_t address);

#endif //PICOONBOARD_PERFORMANCELOGGER_H
