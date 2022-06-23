// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

/*******************************************************************************
  MPLAB Harmony Graphics Composer Generated Implementation File

  File Name:
    libaria_events.c

  Summary:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

  Description:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

    Created with MPLAB Harmony Version 3.0
*******************************************************************************/

#include "gfx/libaria/libaria_events.h"
#include "app.h"

// MainGUI - ShowEvent
void MainGUI_ShowEvent(laScreen* scr)
{
    #ifndef DISABLE_AUDIO
    piezo_two_tone(DRV_PIEZO_TONE_1, 100U, 100U,DRV_PIEZO_TONE_2, 100U);
    #endif
}

// ScanButtonWidget - PressedEvent
void ScanButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_ScanButtonWidget_PressedEvent(btn); 
}

// MenuButtonWidget - PressedEvent
void MenuButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_MenuButtonWidget_PressedEvent(btn);
}

// CameraSettingsMenuButtonWidget - PressedEvent
void CameraSettingsMenuButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_CameraSettingsMenuButtonWidget_PressedEvent(btn);
}

// DeviceSettingsMenuButtonWidget - PressedEvent
void DeviceSettingsMenuButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_DeviceSettingsMenuButtonWidget_PressedEvent(btn);
}

// DisplaySettingsMenuButtonWidget - PressedEvent
void DisplaySettingsMenuButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_DisplaySettingsMenuButtonWidget_PressedEvent(btn);
    //App_DisplaySettings_ShowEvent(scr);
}

// CameraLeftButtonWidget - PressedEvent
void CameraLeftButtonWidget_PressedEvent(laButtonWidget* btn)
{
    //App_CameraLeftButtonWidget_ReleasedEvent(btn);
    //harmony exception
    App_CameraLeftButtonWidget_PressedEvent(btn);
}

// CameraLeftButtonWidget - ReleasedEvent
void CameraLeftButtonWidget_ReleasedEvent(laButtonWidget* btn)
{
    App_CameraLeftButtonWidget_ReleasedEvent(btn);
}

// CameraUpButtonWidget - PressedEvent
void CameraUpButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_CameraUpButtonWidget_PressedEvent(btn);
}

// CameraUpButtonWidget - ReleasedEvent
void CameraUpButtonWidget_ReleasedEvent(laButtonWidget* btn)
{
    App_CameraUpButtonWidget_ReleasedEvent(btn);
}

// CameraRightButtonWidget - PressedEvent
void CameraRightButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_CameraRightButtonWidget_PressedEvent(btn);
}

// CameraRightButtonWidget - ReleasedEvent
void CameraRightButtonWidget_ReleasedEvent(laButtonWidget* btn)
{
    App_CameraRightButtonWidget_ReleasedEvent(btn);
}

// CameraDownButtonWidget - PressedEvent
void CameraDownButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_CameraDownButtonWidget_PressedEvent(btn);
}

// CameraDownButtonWidget - ReleasedEvent
void CameraDownButtonWidget_ReleasedEvent(laButtonWidget* btn)
{
    App_CameraDownButtonWidget_ReleasedEvent(btn);
}

// CameraCancelButtonWidget - PressedEvent
void CameraCancelButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_CameraCancelButtonWidget_PressedEvent(btn);
}

// CameraApplyButtonWidget - PressedEvent
void CameraApplyButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_CameraApplyButtonWidget_PressedEvent(btn);
}

// DeviceSettings - ShowEvent
void DeviceSettings_ShowEvent(laScreen* scr)
{
    App_DeviceSettings_ShowEvent(scr);
}

// DeviceSettingsLcdSliderWidget - ValueChangedEvent
void DeviceSettingsLcdSliderWidget_ValueChangedEvent(laSliderWidget* sld)
{
    // lcdSliderValueChanged
    App_DeviceSettingsLcdSliderWidget_ValueChangedEvent(sld);
}

// DeviceSettingsPeak2AmplitudeSliderWidget - ValueChangedEvent
void DeviceSettingsPeak2AmplitudeSliderWidget_ValueChangedEvent(laSliderWidget* sld)
{
    App_DeviceSettingsPeak2AmplitudeSliderWidget_ValueChangedEvent(sld);
}

// LaserCheckButtonWidget - PressedEvent
void LaserCheckButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_DeviceSettingsLaserCheckButtonWidget_PressedEvent(btn);
    //App_DeviceSettings_ShowEvent(scr);
}

// DeviceSettingsApplyButtonWidget - PressedEvent
void DeviceSettingsApplyButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_DeviceSettingsApplyButtonWidget_PressedEvent(btn);
}

// DeviceSettingsCancelButtonWidget - PressedEvent
void DeviceSettingsCancelButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_DeviceSettingsCancelButtonWidget_PressedEvent(btn);
}

// ScanSettings - ShowEvent
void ScanSettings_ShowEvent(laScreen* scr)
{
}

// ScanSettingsApplyButtonWidget - PressedEvent
void ScanSettingsApplyButtonWidget_PressedEvent(laButtonWidget* btn)
{
}

// ScanSettingsCancelButtonWidget - PressedEvent
void ScanSettingsCancelButtonWidget_PressedEvent(laButtonWidget* btn)
{
}

// DisplaySettings - ShowEvent
void DisplaySettings_ShowEvent(laScreen* scr)
{
    App_DisplaySettings_ShowEvent(scr);
}

// DisplaySettingsApplyButtonWidget - PressedEvent
void DisplaySettingsApplyButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_DisplaySettingsApplyButtonWidget_PressedEvent(btn);
}

// DisplaySettingsCancelButtonWidget - PressedEvent
void DisplaySettingsCancelButtonWidget_PressedEvent(laButtonWidget* btn)
{
    App_DisplaySettingsCancelButtonWidget_PressedEvent(btn);
}

// DeviceSettingsLEDSliderWidget - ValueChangedEvent
void DeviceSettingsLEDSliderWidget_ValueChangedEvent(laSliderWidget* sld)
{
    App_DeviceSettingsLEDSliderWidget_ValueChangedEvent(sld);
}





