/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    display_settings_screen.h

  @Summary
    Display settings.

  @Description
    Configures display settings.
 */
/* ************************************************************************** */

#ifndef _DISPLAY_SETTINGS_SCREEN_H    /* Guard against multiple inclusion */
#define _DISPLAY_SETTINGS_SCREEN_H


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "gfx/libaria/libaria_events.h"
#include "app.h"
#include "settings.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */

#define TARGET_RADIUS_MIN       5       // range is 5 - 32
#define RADIUS_TOLERANCE_MIN    1       // range is 1 - 10
#define ALIGNMENT_TOLERANCE_MIN 1       // range is 1 - 10

#define VALUE_FIELD_FONT     Apertura_14

// *****************************************************************************
// Section: Data Types
// *****************************************************************************



// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void App_DisplaySettings_ShowEvent(laScreen* scr);
void App_DisplaySettingsCancelButtonWidget_PressedEvent(laButtonWidget* btn);
void App_DisplaySettingsApplyButtonWidget_PressedEvent(laButtonWidget* btn);

void App_DeviceSettingsLEDSliderWidget_ValueChangedEvent(laSliderWidget* sld);
void App_DeviceSettingsPeak2AmplitudeSliderWidget_ValueChangedEvent(laSliderWidget* sld);
void App_DeviceSettingsLaserCheckButtonWidget_PressedEvent(laButtonWidget* btn);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DISPLAY_SETTINGS_SCREEN_H */

/* *****************************************************************************
 End of File
 */
