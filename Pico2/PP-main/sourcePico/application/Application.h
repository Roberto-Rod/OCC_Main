/********************************************************************************
* File : Application.h
*
* Description : Main program entry point header.
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

#ifndef PICOONBOARD_APPLICATION_H
#define PICOONBOARD_APPLICATION_H

#include "PaTypes.h"
#include "ErrorCode.h"

/**
 * Initialise application on start-up. This function should be called only once by main.
 */
ErrorCode_t Application_Init(void);

/*
 * Called by main to run the application logic.
 */
ErrorCode_t Application_Run(void);

/*
 * Called by main to put the device in sleep mode (blocking call)
 */
ErrorCode_t Application_Stop(void);

#endif //PICOONBOARD_APPLICATION_H
