/********************************************************************************
* File : AlertManager.h
*
* Description : Manage the display of visual alerts based on the device status.
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

#ifndef PICOONBOARD_ALERTMANAGER_H
#define PICOONBOARD_ALERTMANAGER_H

#include "PaTypes.h"
#include "ErrorCode.h"

/**
 * Initialise the Alert Manager.
 * @return EC_OK if the controller is successfully initialised.
 */
ErrorCode_t AlertManager_Init(void);

/**
 * Called by the application periodically to execute the alert manager periodically.
 * @return  EC_OK if success.
 */
ErrorCode_t AlertManager_Run(void);

// these represent the display sequences which can take place.
typedef enum
{
    LED_CTRL_OFF_E = 0,     
    LED_CTRL_PUMP_DOWN_E,
    LED_CTRL_POWER_DOWN_E,
    LED_CTRL_LEAK_E,
    LED_CTRL_GOOD_STATUS_E,

    LED_CTRL_COMPLETED_E,    // State the alert module goes into when a sequence has completed
} LEDControl_t;

// Start a LED sequence 
void StartLEDSequence(LEDControl_t seq);

// Interface which checks if this current display sequence has completed
bool_t checkLEDSequenceCompleted (void);

#endif //PICOONBOARD_ALERTMANAGER_H
