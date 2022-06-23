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
  MPLAB Harmony Graphics Composer Generated Definitions Header

  File Name:
    libaria_macros.h

  Summary:
    Build-time generated definitions header based on output by the MPLAB Harmony
    Graphics Composer.

  Description:
    Build-time generated definitions header based on output by the MPLAB Harmony
    Graphics Composer.

    Created with MPLAB Harmony Version 3.0
*******************************************************************************/


#ifndef _LIBARIA_INIT_H
#define _LIBARIA_INIT_H

#include "gfx/libaria/libaria.h"
#include "gfx/libaria/libaria_events.h"

#include "gfx/gfx_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END 

#define LIBARIA_SCREEN_COUNT   5

// reference IDs for generated libaria screens
// screen "DeviceSettings"
#define DeviceSettings_ID    2

// screen "DisplaySettings"
#define DisplaySettings_ID    3

// screen "ErrorScreen"
#define ErrorScreen_ID    4

// screen "MainGUI"
#define MainGUI_ID    1

// screen "SplashScreen"
#define SplashScreen_ID    0



extern laScheme OverlayYellow;
extern laScheme BatteryVolume;
extern laScheme TitleText;
extern laScheme MainGui;
extern laScheme MainButtons;
extern laScheme Screen;
extern laScheme ClearScheme;
extern laScheme OverlayBlue;
extern laScheme StatusBar;
extern laScheme OverlayRed;
extern laScheme defaultScheme;
extern laScheme OverlayGreen;
extern laScheme TouchOverlay;
extern laScheme BlackBackground;
extern laScheme OverlayOrange;
extern laScheme GreyBackground;
extern laScheme OverlayWhite;
extern laScheme BatteryVolumeLow;
extern laScheme ScanningProgress;
extern laScheme WhiteBackground;
extern laScheme OverlayLogo;
extern laScheme GeneralText;
extern laImageWidget* ImageWidget2;
extern laLabelWidget* LabelWidget3;
extern laLabelWidget* LabelWidget4;
extern laLabelWidget* DeviceIDLabel;
extern laLabelWidget* PIVersionLabel;
extern laLabelWidget* PDAVersionLabel;
extern laLabelWidget* LSCVersionLabel;
extern laLabelWidget* PEVersionLabel;
extern laWidget* LogoWidget;
extern laCircleWidget* StartCircle;
extern laProgressBarWidget* LogoLine;
extern laCircularSliderWidget* LogoCircle;
extern laGroupBoxWidget* GroupScanStats;
extern laLabelWidget* TimeToScanLW;
extern laLabelWidget* TimeScanningTookLW;
extern laLabelWidget* AverageZInScanLW;
extern laLabelWidget* AverageTempInScanLW;
extern laWidget* StatusBarPanelWidget;
extern laImageWidget* LaserWidget;
extern laImageWidget* LaserErrorWidget;
extern laImageWidget* ScanWidget;
extern laImageWidget* UsbWidget;
extern laProgressBarWidget* BatteryWidget;
extern laImageWidget* ChargeWidget;
extern laRectangleWidget* BatteryWidget2;
extern laWidget* MainGuiPanelWidget;
extern laImagePlusWidget* CameraWidget;
extern laImageWidget* SaturatedWidget;
extern laArcWidget* CameraAlignmentArcWidget;
extern laArcWidget* ScanningProgressArcWidget;
extern laButtonWidget* ScanButtonWidget;
extern laButtonWidget* MenuButtonWidget;
extern laLabelWidget* MeasurementWidget0;
extern laLabelWidget* StdevWidget0;
extern laLabelWidget* ScanLabelWidget0;
extern laLabelWidget* MeasurementWidget1;
extern laLabelWidget* StdevWidget1;
extern laLabelWidget* ScanLabelWidget1;
extern laLabelWidget* MeasurementWidget2;
extern laLabelWidget* StdevWidget2;
extern laLabelWidget* ScanLabelWidget2;
extern laLabelWidget* MeasurementWidget3;
extern laLabelWidget* StdevWidget3;
extern laLabelWidget* ScanLabelWidget3;
extern laWidget* MenuPanelWidget;
extern laButtonWidget* CameraSettingsMenuButtonWidget;
extern laButtonWidget* DeviceSettingsMenuButtonWidget;
extern laButtonWidget* DisplaySettingsMenuButtonWidget;
extern laWidget* CameraSettingsPanelWidget;
extern laButtonWidget* CameraLeftButtonWidget;
extern laButtonWidget* CameraUpButtonWidget;
extern laButtonWidget* CameraRightButtonWidget;
extern laButtonWidget* CameraDownButtonWidget;
extern laLabelWidget* CameraHSTARTLabelWidget;
extern laLabelWidget* CameraHSTARTValueLabelWidget;
extern laLabelWidget* CameraVSTARTLabelWidget;
extern laLabelWidget* CameraVSTARTValueLabelWidget;
extern laButtonWidget* CameraCancelButtonWidget;
extern laButtonWidget* CameraApplyButtonWidget;
extern laCircleWidget* CameraAlinmentCircleWidget;
extern laRectangleWidget* mainscreen_cover;
extern laLabelWidget* DeviceSettingsLabelWidget;
extern laLabelWidget* DeviceSettingsLcdBrtLabelWidget;
extern laSliderWidget* DeviceSettingsLcdSliderWidget;
extern laButtonWidget* DeviceSettingsApplyButtonWidget;
extern laButtonWidget* DeviceSettingsCancelButtonWidget;
extern laLabelWidget* DisplaySettingsLabelWidget;
extern laButtonWidget* DisplaySettingsApplyButtonWidget;
extern laButtonWidget* DisplaySettingsCancelButtonWidget;
extern laLabelWidget* LabelWidget1;
extern laSliderWidget* DeviceSettingsLEDSliderWidget;
extern laLabelWidget* DevSettingsPeak2AmplitudeValueLabelWidget;
extern laLabelWidget* LabelWidget2;
extern laSliderWidget* DeviceSettingsPeak2AmplitudeSliderWidget;
extern laButtonWidget* AutoScanButtonWidget;
extern laButtonWidget* LaserCheckButtonWidget;
extern laGroupBoxWidget* GroupBoxWidget4;
extern laImageWidget* ImageWidget5;
extern laLabelWidget* ErrorLabelWidget;





int32_t libaria_initialize(void);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // _LIBARIA_INIT_H
/*******************************************************************************
 End of File
*/
