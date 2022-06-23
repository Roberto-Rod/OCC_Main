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
 * (c) 2018, 2019, 2020 Smith & Nephew Medical Ltd.
 *
 ***************************************************************************** */

#include "LoggingManager.h"
#include "PerformanceLogger.h"
#include "DeviceStatus.h"
#include "Battery.h"
#include "StateMachine.h"


#define LOGGING_DELAY_ONE_MINUTE_TICKS    (600u) //60 * 10
#define LOG_SIZE_BYTES                    (16)
#define EEPROM_END_OF_LIFE_ADDRESS        (60ul * 24ul * 8ul * LOG_SIZE_BYTES)  // EOL is now 8 days to account for the internal oscillator inaccuracies

static uint16_t tickCounter;

/****************************************************************************
   Function Name  :  LoggingManager_Init

   Parameters     :  None

   Return Value   :  None

   Description    :  Initialise the logging manager
 *****************************************************************************/
void LoggingManager_Init()
{
    tickCounter = LOGGING_DELAY_ONE_MINUTE_TICKS;
    PerformanceLogger_Init();
}

/****************************************************************************
   Function Name  :  LoggingManager_Run

   Parameters     :  None

   Return Value   :  EC_OK or error code

   Description    :  Store performance logs in the EEPROM
                     Check if 7 days of logging have passed and enter NRE

 *****************************************************************************/
ErrorCode_t LoggingManager_Run()
{
    ErrorCode_t errorCode = EC_OPS_NOT_EXECUTED_E;

    if (tickCounter > 0)
    {
        tickCounter--;
    }

    if (tickCounter == 0)
    {
        // Ensure no logging occurs during NRE
        if (DeviceStatus_GetState() != NRE_E)
        {
            if (PerformanceLogger_GetCurrentAddress() >= EEPROM_END_OF_LIFE_ADDRESS)
            {
                // Store NRE event
                DeviceStatus_SetNRE_Event (NRE_EEPROM_EOL_EVENT_E);
                // Set state machine to NRE
                DeviceStatus_StateAndOnEntrySet(TRUE, NRE_E);
                // Write the final performance record and set the NRE flag
                StateMachine_Enter_NRE(TRUE);
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

                    //Write to logger
                    errorCode = PerformanceLogger_Persist();

                    if (errorCode == EC_OK_E)
                    {
                        tickCounter = LOGGING_DELAY_ONE_MINUTE_TICKS;
                    }
                    else
                    {
                        // EEPROM write operation failed so enter NRE
                        DeviceStatus_StateAndOnEntrySet(FALSE, NRE_E);
                        // Don't try to write the EEPROM flag as this will also fail
                        StateMachine_Enter_NRE(FALSE);
                    }
                    
                }
                else
                {
                    errorCode = EC_LOGGING_POSTPONE_E;
                }
            }
        }
    }

    return errorCode;
}

/****************************************************************************
   Function Name  :  LoggingManager_GetTicks

   Parameters     :  None

   Return Value   :  tickCounter

   Description    :  Return the logging manager tick counter
 *****************************************************************************/
uint16_t LoggingManager_GetTicks()
{
    return tickCounter;
}



