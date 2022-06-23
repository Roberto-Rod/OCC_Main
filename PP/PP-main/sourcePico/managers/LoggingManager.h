/********************************************************************************
* File : LoggingManager.h
*
* Description : Header Code for implementation of the logging manager.
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

#ifndef PICOONBOARD_LOGGINGMANAGER_H
#define PICOONBOARD_LOGGINGMANAGER_H

#include "PaTypes.h"
#include "ErrorCode.h"

void LoggingManager_Init(void);

/**
 * Tick every 100ms, collect performance log and write to storage every minute.
 * @return
 */
ErrorCode_t LoggingManager_Run(void);

uint16_t LoggingManager_GetTicks(void);


#endif //PICOONBOARD_LOGGINGMANAGER_H
