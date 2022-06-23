/*****************************************************************************
 *   File        : PerformanceLogger.c
 *
 *   Description : Source Code for implementation of performance logging on the EEPROM
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

#include "PerformanceLogger.h"
#include "I2CEEPROM.h"

#include <string.h>
#include "PowerControl.h"
#include "Timer.h"

#define LOG_SIZE_BYTES       (16)
// Set the NRE FLAG location after the last possible performance record.
// NonRecoverableError_OnEntry may add an additional record after EEPROM_END_OF_LIFE_ADDRESS
// if the NRE is caused by EEPROM_END_OF_LIFE_ADDRESS having been reached.
// i.e. NRE_FLAG_ADDRESS = EEPROM_END_OF_LIFE_ADDRESS + LOG_SIZE_BYTES
#define NRE_FLAG_ADDRESS     ((60ul * 24ul * 8ul * LOG_SIZE_BYTES) +  LOG_SIZE_BYTES)  // EOL is now 8 days to account for the internal oscillator inaccuracies
#define NRE_FLAG_VALUE       (0x66)

static uint32_t            addressCounter = 0;
static PerformanceLogger_t performanceLogger;

static void toBytes(PerformanceLogger_t const * const performanceLogger, uint8_t * const destData);

void PerformanceLogger_Init()
{
    addressCounter = 0;
    I2E_Init();
    memset(&performanceLogger, 0, LOG_SIZE_BYTES);
}

ErrorCode_t PerformanceLogger_Persist()
{
    ErrorCode_t result = EC_FAILED_E;
    uint8_t     writeData[LOG_SIZE_BYTES];
    toBytes(&performanceLogger, writeData);

    MP_EnableExternalPeripheralsSupply();
    PM_Delay((uint32_t) 8);

    result = I2E_Write(addressCounter, writeData, LOG_SIZE_BYTES);
    if (result == EC_OK_E)
    {
        addressCounter += LOG_SIZE_BYTES;
    }

    // Allow the longest write time of 10 ms
    PM_Delay((uint32_t) 10);

    MP_DisableExternalPeripheralsSupply();

    memset(&performanceLogger, 0, LOG_SIZE_BYTES);

    return result;
}

ErrorCode_t PerformanceLogger_SetNRE()
{
    ErrorCode_t result = EC_FAILED_E;
    uint8_t nre_byte = NRE_FLAG_VALUE;

    MP_EnableExternalPeripheralsSupply();
    PM_Delay((uint32_t) 8);

    result = I2E_Write((uint32_t)NRE_FLAG_ADDRESS, &nre_byte, 0x01);

    // Allow the longest write time of 10 ms
    PM_Delay((uint32_t) 10);

    MP_DisableExternalPeripheralsSupply();

    return result;
}

bool PerformanceLogger_GetNRE()
{
    bool result = false;
    uint8_t nre_byte;
    MP_EnableExternalPeripheralsSupply();
    PM_Delay((uint32_t) 8);

    ErrorCode_t retVal = I2E_Read((uint32_t)NRE_FLAG_ADDRESS, &nre_byte, 0x01);

    // Allow the longest write time of 10 ms
    PM_Delay((uint32_t) 10);

    MP_DisableExternalPeripheralsSupply();

    if ((retVal != EC_OK_E) || (nre_byte == NRE_FLAG_VALUE))
    {
        // return NRE state if EEPROM read operation failed or
        // NRE flag value is read. 
        result = true;
    }

    return result;
}

void PerformanceLogger_SetDifferentialPressure(const uint16_t pressureMilliBar)
{
    performanceLogger.differentialPressureMilliBar = pressureMilliBar;
}

void PerformanceLogger_SetExternalPressure(const uint16_t pressureMilliBar)
{
    performanceLogger.externalPressureMilliBar = pressureMilliBar;
}

void PerformanceLogger_SetPumpHistory(const uint32_t pumpHistory)
{
    performanceLogger.pumpHistory = pumpHistory;
}

void PerformanceLogger_SetBatteryVoltage(const uint16_t voltageMilliVolts)
{
    performanceLogger.batteryVoltageMilliVolts = voltageMilliVolts;
}


//
//  This sets the temperatures in the log buffer
//  The temperature values are the raw value read from the internal and external sensors
//
//  see folowing document on how to interpret the temperature
//  https://www.st.com/content/ccc/resource/technical/document/technical_note/23/dd/08/f8/ac/cf/47/83/DM00242307.pdf/files/DM00242307.pdf/jcr:content/translations/en.DM00242307.pdf
//
void PerformanceLogger_SetInternalTemperature(const uint16_t temperatureRawSensorValue)
{
    performanceLogger.intTemperatureRaw = temperatureRawSensorValue;
}

void PerformanceLogger_SetExternalTemperature(const uint16_t temperatureRawSensorValue)
{
    performanceLogger.extTemperatureRaw = temperatureRawSensorValue;
}

void PerformanceLogger_SetStatus(const uint8_t deviceStatus)
{
    performanceLogger.deviceStatus = deviceStatus;
}

void PerformanceLogger_SetPumpDownDuration(const uint8_t duration100Ms)
{
    performanceLogger.lastPumpDownDuration100Ms = duration100Ms;
}

uint32_t PerformanceLogger_GetCurrentAddress(void)
{
    return addressCounter;
}

// For unit test use only
void PerformanceLogger_SetCurrentAddress(const uint32_t address)
{
    addressCounter = address;
}

uint8_t PerformanceLogger_GetPumpDownDuration100Ms()
{
    return performanceLogger.lastPumpDownDuration100Ms;
}

PerformanceLogger_t* PerformanceLogger_Get()
{
    return &performanceLogger;
}

void PerformanceLogger_SkipToNextTimeline()
{
    addressCounter += LOG_SIZE_BYTES;
}

// Note that this function maintain the 16 bit alignment of the processor therefore
// it assumes that the data structure PerformanceLogger_t is as such that it has no padding
// for its internal fields
//
// The following PC-lint suppression is used since the function is only called once within this module with valid pointer parameters.
// Suppressing the lint message in this case avoids adding null parameter check code.
/*lint -e{668} Suppress: Possibly passing a null pointer to function 'memcpy(void *, const void *, unsigned int)', args. no. 1 & 2. */
static void toBytes(PerformanceLogger_t const * const performanceLoggerData, uint8_t * const destData)
{
    memcpy(destData, performanceLoggerData, LOG_SIZE_BYTES);
}

