/* ************************************************************************** */
/** Descriptive File Name

  @Company
   Occuity Limited

  @File Name
    device_settings_screen.h

  @Summary
    Device settings dialogue box.

  @Description
    Allows the user to change device settings.
 */
/* ************************************************************************** */

#ifndef _DEVICE_SETTINGS_SCREEN_H    /* Guard against multiple inclusion */
#define _DEVICE_SETTINGS_SCREEN_H


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */

#define P1_SCALE_FACTOR         1310U
#define P2_SCALE_FACTOR         131U
#define VOLTAGE_SCALE           13107U 

// *****************************************************************************
// Section: Data Types
// *****************************************************************************



// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
double calculate_amplifier_gain(uint16_t digipot_setting);


void App_DeviceSettingsCancelButtonWidget_PressedEvent(laButtonWidget* btn);
void App_DeviceSettingsApplyButtonWidget_PressedEvent(laButtonWidget* btn);

//void App_DeviceSettingsBtEnButtonWidget_PressedEvent(laButtonWidget* btn);
//void App_DeviceSettingsBtEnButtonWidget_ReleasedEvent(laButtonWidget* btn);
void App_DeviceSettings_ShowEvent(laScreen* scr);

void App_DeviceSettingsLcdSliderWidget_ValueChangedEvent(laSliderWidget* sld);


/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DEVICE_SETTINGS_SCREEN_H */

/* *****************************************************************************
 End of File
 */
