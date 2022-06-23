/********************************************************************************
* File : UIInterfaces.h
*
* Description : Header for implementation of user interfaces
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

#ifndef UIINTERFACES_H
#define	UIINTERFACES_H

#include "PaTypes.h"
#include "LEDType.h"

#define LED_ON_50_SYSTEM_TICKS  (50) // multiple of 100ms
#define LED_ON_20_SYSTEM_TICKS  (20) // multiple of 100ms
#define LED_OFF_20_SYSTEM_TICKS (20) // multiple of 100ms
#define LED_OFF_18_SYSTEM_TICKS (18) // multiple of 100ms
#define LED_ON_10_SYSTEM_TICKS  (10) // multiple of 100ms
#define LED_ON_5_SYSTEM_TICKS    (5) // multiple of 100ms
#define LED_OFF_5_SYSTEM_TICKS   (5) // multiple of 100ms
#define LED_ON_2_SYSTEM_TICKS    (2) // multiple of 100ms
#define LED_OFF_2_SYSTEM_TICKS   (2) // multiple of 100ms
#define SET_GN_LED_COUNTDOWN   (200) // 10s of continuous GN LED on
#define LED_ON_1_SYSTEM_TICKS    (1)
#define LED_ON_0_SYSTEM_TICKS    (0)
#define LED_OFF_0_SYSTEM_TICKS   (0)
#define LED_OFF               LED_ON_0_SYSTEM_TICKS

void UI_SetLED(LED_Colour_t Colour, uint32_t FlashTOn, uint32_t FlashTOff);// Set LED operation
bool_t UI_UpdateLEDs(void);    // Update LED flash
bool_t UI_IsPushButtonPressed(void);     // Returns state of switch
uint32_t UI_GetPeriodCount(LED_Colour_t Colour);     // Returns periods count

#endif	/* UIINTERFACES_H */

