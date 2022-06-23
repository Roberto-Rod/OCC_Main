#include "PaTypes.h"
#include "ErrorCode.h"


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



} PerformanceLogger_t;



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









ErrorCode_t PerformanceLogger_Persist(void);



ErrorCode_t PerformanceLogger_SetNRE(void);



_Bool 

    PerformanceLogger_GetNRE(void);



PerformanceLogger_t* PerformanceLogger_Get();

uint32_t PerformanceLogger_GetCurrentAddress(void);

void PerformanceLogger_SetCurrentAddress(const uint32_t address);
