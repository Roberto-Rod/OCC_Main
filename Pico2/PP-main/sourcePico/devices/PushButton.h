/********************************************************************************
* File : PushButton.h
*
* Description : Header file to detect button pressed
*
********************************************************************************/
/* ******************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend.
 *
 * (c) 2018 - 2021 Smith & Nephew Medical Ltd.
 *
 ***************************************************************************** */

#ifndef PICOONBOARD_PUSHBUTTON_H
#define PICOONBOARD_PUSHBUTTON_H

#include "PaTypes.h"

#define MAX_BUTTON_PRESSED_DURATION         (0xff)
#define PUSHBUTTON_SHORT_PRESS_TICK_COUNT      (2) // 100ms tick, 0.2 second for short press
#define PUSHBUTTON_LONG_PRESS_TICK_COUNT      (20) // 100ms tick, 2 second for short press

                                                   // In the status the number of ticks are counted
#define PUSHBUTTON_TICK_PRESSES_FOR_STATUS     (2) // 100ms tick, 0.2 second for status press

void PushButton_ResetEvent(void);

bool_t PushButton_IsPressed(void);

bool_t PushButton_IsShortPress(void);

bool_t PushButton_IsLongPress(void);

/**
 * Get the number of depressed count when button is pressed. For Unit test purpose
 * @return number of ticks when the button is detected depressed.
 */
uint8_t PushButton_GetDepressedTickCount(void);

#endif //PICOONBOARD_PUSHBUTTON_H
