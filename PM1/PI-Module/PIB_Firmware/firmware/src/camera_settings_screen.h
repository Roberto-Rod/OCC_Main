/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    camera_settings_screen.h

  @Summary
    Screen for configuring camera settings.

  @Description
    Allows camera settings to be viewed and changed.
 */
/* ************************************************************************** */

#ifndef _CAMERA_SETTINGS_SCREEN_H    /* Guard against multiple inclusion */
#define _CAMERA_SETTINGS_SCREEN_H


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



// *****************************************************************************
// Section: Data Types
// *****************************************************************************



// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************


void hMinusButtonWidget_PressedEvent(laButtonWidget* btn);
void hMinusButtonWidget_ReleasedEvent(laButtonWidget* btn);
void hPlusButtonWidget_PressedEvent(laButtonWidget* btn);
void hPlusButtonWidget_ReleasedEvent(laButtonWidget* btn);
void vMinusButtonWidget_PressedEvent(laButtonWidget* btn);
void vMinusButtonWidget_ReleasedEvent(laButtonWidget* btn);
void vPlusButtonWidget_PressedEvent(laButtonWidget* btn);
void vPlusButtonWidget_ReleasedEvent(laButtonWidget* btn);

void show_camera_settings_dialog(void);
void show_or_hide_camera_settings_dialog(laBool show);

void App_CameraSettings_ShowEvent(laScreen* scr);
void App_CameraSettingsApplyButtonWidget_PressedEvent(laButtonWidget* btn);
void App_CameraSettingsCancelButtonWidget_PressedEvent(laButtonWidget* btn);

void App_CameraLeftButtonWidget_PressedEvent(laButtonWidget* btn);
void App_CameraLeftButtonWidget_ReleasedEvent(laButtonWidget* btn);
void App_CameraUpButtonWidget_PressedEvent(laButtonWidget* btn);
void App_CameraUpButtonWidget_ReleasedEvent(laButtonWidget* btn);
void App_CameraRightButtonWidget_PressedEvent(laButtonWidget* btn);
void App_CameraRightButtonWidget_ReleasedEvent(laButtonWidget* btn);
void App_CameraDownButtonWidget_PressedEvent(laButtonWidget* btn);
void App_CameraDownButtonWidget_ReleasedEvent(laButtonWidget* btn);
void App_CameraApplyButtonWidget_PressedEvent(laButtonWidget* btn);
void App_CameraCancelButtonWidget_PressedEvent(laButtonWidget* btn);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _CAMERA_SETTINGS_SCREEN_H */

/* *****************************************************************************
 End of File
 */
