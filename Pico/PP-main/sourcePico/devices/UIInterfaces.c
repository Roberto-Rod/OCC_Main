/********************************************************************************
* File : UIInterfaces.c
*
* Description : Source Code for implementation of user interfaces
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

#include "UIInterfaces.h"
#include "PowerControl.h"
#include "LED.h"
#include "PushButton.h"


typedef void (*ActivateLed_t)(bool_t);

typedef struct
{
    /*lint -esym(754, LED_Interval_t::ledName) Suppress: local structure member 'LED_Interval_t::ledName' (Location) not referenced. */
    LED_Colour_t  ledName;
    uint32_t      onCounterInterval;
    uint32_t      offCounterInterval;
    ActivateLed_t activateLedFn;
    uint32_t      tickCounter;
    uint32_t      periodsCount; //  period count
} LED_Interval_t;


static LED_Interval_t Leds[LD_MAX_E] = {
    { LD_GREEN_E,  0, 0, LED_SetGreen,  0, 0 },
    { LD_ORANGE_E, 0, 0, LED_SetOrange, 0, 0 }
};


static bool_t UI_UpdatedSingleLED(LED_Interval_t *LedOnOffSetup);

/*********************************************//**
*  @brief   Set LED operation
*  @param   Colour, Time for flash on (ms), Time for flash off (ms)
*  @return  None
*
*************************************************/
void UI_SetLED(LED_Colour_t Colour, uint32_t FlashTOn, uint32_t FlashTOff)
{
    if (LD_MAX_E > Colour)
    {
        Leds[Colour].onCounterInterval  = FlashTOn;
        Leds[Colour].offCounterInterval = FlashTOff;
        Leds[Colour].tickCounter        = 0;
        Leds[Colour].periodsCount       = 0;
    }
}


/****************************************************************************
   Function Name  :  UI_GetPeriodCount

   Parameters     :  None

   Return Value   :  uint32_t  - number of periods


   Description    :  Given the LED colour this returns the number of periods
                     which LED has been displayed.
 *****************************************************************************/
uint32_t UI_GetPeriodCount(LED_Colour_t Colour)
{
    if (LD_MAX_E > Colour)
    {
        return Leds[Colour].periodsCount;
    }

    return 0;
}

/*********************************************//**
*  @brief   Update flash of LED. This function should be called once every tick (100ms)
*  @param   None
*  @return  TRUE if any of the LED is set to ON
*
*************************************************/
bool_t UI_UpdateLEDs(void)
{
    bool_t isPowerRequired = FALSE;

    for (uint8_t i = 0; i < LD_MAX_E; i++)
    {
        // As long as one LED needs power we will energize the circuit
        if (UI_UpdatedSingleLED(&Leds[i]))
        {
            isPowerRequired = TRUE;
        }
    }

    if (isPowerRequired)
    {
        MP_EnableMainCircuitPower();
    }

    return isPowerRequired;
}


/*********************************************//**
*  @brief   Get switch status
*  @param   None
*  @return  TRUE for button pressed
*           FALSE for button release
*
*************************************************/
bool_t UI_IsPushButtonPressed(void)
{
    return(PushButton_IsPressed());
}


/*lint -e{613} Suppress: Possible use of null pointer 'LedOnOffSetup' in left argument to operator '->'. */
static bool_t UI_UpdatedSingleLED(LED_Interval_t *LedOnOffSetup)
{
    // The tick count is the offset within the period and the onCounterInterval is
    // the on part of the period, so if the tick count is less that the onCounterInterval you
    // know the LED is on, otherwise it is in the off part of the period.

    bool_t enableLed = (LedOnOffSetup->tickCounter < LedOnOffSetup->onCounterInterval);
    LedOnOffSetup->activateLedFn(enableLed);

    if ((++LedOnOffSetup->tickCounter) >= (LedOnOffSetup->onCounterInterval + LedOnOffSetup->offCounterInterval))
    {
        LedOnOffSetup->tickCounter = 0;
        LedOnOffSetup->periodsCount++;
    }
    return enableLed;
}
