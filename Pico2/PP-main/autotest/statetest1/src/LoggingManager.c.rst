/********************************************************************************
* File : LoggingManager.c
*
* Description : Source Code for implementation of the logging manager.
*
********************************************************************************/
/* ******************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend.
 *
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 *
 ***************************************************************************** */

#include "LoggingManager.h"
#include "PerformanceLogger.h"
#include "DeviceStatus.h"
#include "Battery.h"
#include "StateMachine.h"


/*
#define LOGGING_DELAY_ONE_MINUTE_TICKS    (600u) //60 * 10
*/
#define LOGGING_DELAY_ONE_MINUTE_TICKS    (10u) //60 * 10  Log every second for testing
#define LOG_SIZE_BYTES                    (16)
#define EEPROM_END_OF_LIFE_ADDRESS        (60ul * 24ul * 7ul * LOG_SIZE_BYTES)

static uint16_t tickCounter;
static bool_t  logPumpDownEvent = FALSE; 

void LoggingManager_Init()
{
    tickCounter = LOGGING_DELAY_ONE_MINUTE_TICKS;
    PerformanceLogger_Init();
}

ErrorCode_t LoggingManager_Run()
{
    ErrorCode_t errorCode = EC_OPS_NOT_EXECUTED_E;

    if (tickCounter > 0)
    {
        tickCounter--;
    }

    if (tickCounter == 0)
    {
        if (DeviceStatus_GetState() == PUMP_DOWN_E)
        {
           logPumpDownEvent = TRUE;
        } 
        
        if (PerformanceLogger_GetCurrentAddress() >= EEPROM_END_OF_LIFE_ADDRESS)
        {
            DeviceStatus_StateAndOnEntrySet(TRUE, NRE_E);
            StateMachine_Enter_NRE();
            errorCode = EC_EEPROM_BUFFER_FULL_EOL;
        }
        else
        {
            if (DeviceStatus_GetState() == IDLE_E)
            {
                //just advance the pointer, but not write to EEPROM
                PerformanceLogger_SkipToNextTimeline();
                tickCounter = LOGGING_DELAY_ONE_MINUTE_TICKS;
                errorCode   = EC_OK_E;
            }
            else if (!DeviceStatus_IsRunningPump() &&
                     !DeviceStatus_IsReadingPressureSensor())
            {
                PerformanceLogger_SetStatus((uint8_t) DeviceStatus_GetState());
                
                // Log a PUMP DOWN as a sync identifier 
                if (logPumpDownEvent)
                {
                    logPumpDownEvent = FALSE;
                    PerformanceLogger_SetStatus((uint8_t) PUMP_DOWN_E);
                }
                
                Battery_CheckVoltageWithNoLoad();

                //Write to logger
                errorCode = PerformanceLogger_Persist();

                if (errorCode == EC_OK_E)
                {
                    tickCounter = LOGGING_DELAY_ONE_MINUTE_TICKS;
                }
            }
            else
            {
                errorCode = EC_LOGGING_POSTPONE_E;
            }
        }
    }

    return errorCode;
}

uint16_t LoggingManager_GetTicks()
{
    return tickCounter;
}



