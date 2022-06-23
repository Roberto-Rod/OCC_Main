/*****************************************************************************
 *   File        : PushButton.c
 *
 *   Description : Source Code to detect button pressed
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "PushButton.h"
#ifdef UNIT_TEST
    #include "pic16lf1509.h"
    extern volatile PORTAbits_t PORTAbits;
#else
    #include "mcc.h"
#endif
 
// 
// SCU Auto test functionality 
//
static uint16_t auto_testcount = 0; 

void Auto_Button( uint16_t ticks) 
{   
    auto_testcount = ticks; // 3;
}  


uint8_t buttonPressedDurationTick = 0;
bool_t hasDetectUnpressed = FALSE;
bool_t shortEventRaised = FALSE;
bool_t longEventRaised = FALSE;

static bool_t PushButton_HasDepressedForDuration(bool_t * EventRaised, const uint8_t depressedDurationTick);

void PushButton_ResetEvent()
{
  buttonPressedDurationTick = 0;
  shortEventRaised = FALSE;
  longEventRaised = FALSE;
  hasDetectUnpressed = FALSE;
}

bool_t PushButton_IsPressed(void)
{
  bool_t isButtonPressed = (bool_t)(PORTAbits.RA5 == 1);
  
  // SCU 
  if ( auto_testcount > 0 )
  {
      isButtonPressed = TRUE;
      auto_testcount--;   
  } 

  if (!isButtonPressed)
  {
    buttonPressedDurationTick = 0;
    shortEventRaised = FALSE;
    longEventRaised = FALSE;
    hasDetectUnpressed = TRUE;
  }
  else if (hasDetectUnpressed && buttonPressedDurationTick < MAX_BUTTON_PRESSED_DURATION)
  {
    buttonPressedDurationTick++;
  }

  return isButtonPressed;
}

bool_t PushButton_IsLongPress()
{
  return PushButton_HasDepressedForDuration(&longEventRaised, PUSHBUTTON_LONG_PRESS_TICK_COUNT);
}

bool_t PushButton_IsShortPress()
{
  return PushButton_HasDepressedForDuration(&shortEventRaised, PUSHBUTTON_SHORT_PRESS_TICK_COUNT);
}

static bool_t PushButton_HasDepressedForDuration(bool_t * EventRaised, const uint8_t depressedDurationTick)
{
    if (EventRaised)
    {
      if ((buttonPressedDurationTick > depressedDurationTick) &&
          !*EventRaised)
      {
        *EventRaised = TRUE;
        return TRUE;
      }
    }

  return FALSE;
}

uint8_t PushButton_GetDepressedTickCount()
{
  return buttonPressedDurationTick;
}
