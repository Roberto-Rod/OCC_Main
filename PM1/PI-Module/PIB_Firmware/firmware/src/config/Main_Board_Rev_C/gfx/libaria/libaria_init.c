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
    libaria_init.c

  Summary:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

  Description:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

    Created with MPLAB Harmony Version 3.0
*******************************************************************************/

#include "gfx/libaria/libaria_init.h"
#include "gfx/libaria/inc/libaria_utils.h"

laScheme OverlayYellow;
laScheme BatteryVolume;
laScheme TitleText;
laScheme MainGui;
laScheme MainButtons;
laScheme Screen;
laScheme ClearScheme;
laScheme OverlayBlue;
laScheme StatusBar;
laScheme OverlayRed;
laScheme defaultScheme;
laScheme OverlayGreen;
laScheme TouchOverlay;
laScheme BlackBackground;
laScheme OverlayOrange;
laScheme GreyBackground;
laScheme OverlayWhite;
laScheme BatteryVolumeLow;
laScheme ScanningProgress;
laScheme WhiteBackground;
laScheme OverlayLogo;
laScheme GeneralText;
laImageWidget* ImageWidget2;
laLabelWidget* LabelWidget3;
laLabelWidget* LabelWidget4;
laLabelWidget* DeviceIDLabel;
laLabelWidget* PIVersionLabel;
laLabelWidget* PDAVersionLabel;
laLabelWidget* LSCVersionLabel;
laLabelWidget* PEVersionLabel;
laWidget* LogoWidget;
laCircleWidget* StartCircle;
laProgressBarWidget* LogoLine;
laCircularSliderWidget* LogoCircle;
laGroupBoxWidget* GroupScanStats;
laLabelWidget* TimeToScanLW;
laLabelWidget* TimeScanningTookLW;
laLabelWidget* AverageZInScanLW;
laLabelWidget* AverageTempInScanLW;
laWidget* StatusBarPanelWidget;
laImageWidget* LaserWidget;
laImageWidget* LaserErrorWidget;
laImageWidget* ScanWidget;
laImageWidget* UsbWidget;
laProgressBarWidget* BatteryWidget;
laImageWidget* ChargeWidget;
laRectangleWidget* BatteryWidget2;
laWidget* MainGuiPanelWidget;
laImagePlusWidget* CameraWidget;
laImageWidget* SaturatedWidget;
laArcWidget* CameraAlignmentArcWidget;
laArcWidget* ScanningProgressArcWidget;
laButtonWidget* ScanButtonWidget;
laButtonWidget* MenuButtonWidget;
laLabelWidget* MeasurementWidget0;
laLabelWidget* StdevWidget0;
laLabelWidget* ScanLabelWidget0;
laLabelWidget* MeasurementWidget1;
laLabelWidget* StdevWidget1;
laLabelWidget* ScanLabelWidget1;
laLabelWidget* MeasurementWidget2;
laLabelWidget* StdevWidget2;
laLabelWidget* ScanLabelWidget2;
laLabelWidget* MeasurementWidget3;
laLabelWidget* StdevWidget3;
laLabelWidget* ScanLabelWidget3;
laWidget* MenuPanelWidget;
laButtonWidget* CameraSettingsMenuButtonWidget;
laButtonWidget* DeviceSettingsMenuButtonWidget;
laButtonWidget* DisplaySettingsMenuButtonWidget;
laWidget* CameraSettingsPanelWidget;
laButtonWidget* CameraLeftButtonWidget;
laButtonWidget* CameraUpButtonWidget;
laButtonWidget* CameraRightButtonWidget;
laButtonWidget* CameraDownButtonWidget;
laLabelWidget* CameraHSTARTLabelWidget;
laLabelWidget* CameraHSTARTValueLabelWidget;
laLabelWidget* CameraVSTARTLabelWidget;
laLabelWidget* CameraVSTARTValueLabelWidget;
laButtonWidget* CameraCancelButtonWidget;
laButtonWidget* CameraApplyButtonWidget;
laCircleWidget* CameraAlinmentCircleWidget;
laRectangleWidget* mainscreen_cover;
laLabelWidget* DeviceSettingsLabelWidget;
laLabelWidget* DeviceSettingsLcdBrtLabelWidget;
laSliderWidget* DeviceSettingsLcdSliderWidget;
laButtonWidget* DeviceSettingsApplyButtonWidget;
laButtonWidget* DeviceSettingsCancelButtonWidget;
laLabelWidget* DisplaySettingsLabelWidget;
laButtonWidget* DisplaySettingsApplyButtonWidget;
laButtonWidget* DisplaySettingsCancelButtonWidget;
laLabelWidget* LabelWidget1;
laSliderWidget* DeviceSettingsLEDSliderWidget;
laLabelWidget* DevSettingsPeak2AmplitudeValueLabelWidget;
laLabelWidget* LabelWidget2;
laSliderWidget* DeviceSettingsPeak2AmplitudeSliderWidget;
laButtonWidget* AutoScanButtonWidget;
laButtonWidget* LaserCheckButtonWidget;
laGroupBoxWidget* GroupBoxWidget4;
laImageWidget* ImageWidget5;
laLabelWidget* ErrorLabelWidget;


static void ScreenCreate_SplashScreen(laScreen* screen);
static void ScreenCreate_MainGUI(laScreen* screen);
static void ScreenCreate_DeviceSettings(laScreen* screen);
static void ScreenCreate_DisplaySettings(laScreen* screen);
static void ScreenCreate_ErrorScreen(laScreen* screen);


int32_t libaria_initialize(void)
{
    laScreen* screen;

    laScheme_Initialize(&OverlayYellow, GFX_COLOR_MODE_RGB_565);
    OverlayYellow.base = 0xFFE0;
    OverlayYellow.highlight = 0xC67A;
    OverlayYellow.highlightLight = 0xFFFF;
    OverlayYellow.shadow = 0x8410;
    OverlayYellow.shadowDark = 0x4208;
    OverlayYellow.foreground = 0xFFE0;
    OverlayYellow.foregroundInactive = 0xD71C;
    OverlayYellow.foregroundDisabled = 0x8410;
    OverlayYellow.background = 0xFFFF;
    OverlayYellow.backgroundInactive = 0xD71C;
    OverlayYellow.backgroundDisabled = 0xC67A;
    OverlayYellow.text = 0xFFE0;
    OverlayYellow.textHighlight = 0xFFE0;
    OverlayYellow.textHighlightText = 0xFFFF;
    OverlayYellow.textInactive = 0xD71C;
    OverlayYellow.textDisabled = 0x8C92;

    laScheme_Initialize(&BatteryVolume, GFX_COLOR_MODE_RGB_565);
    BatteryVolume.base = 0xFFFF;
    BatteryVolume.highlight = 0xFFFF;
    BatteryVolume.highlightLight = 0xFFFF;
    BatteryVolume.shadow = 0xDEFB;
    BatteryVolume.shadowDark = 0xBDF7;
    BatteryVolume.foreground = 0xFFFF;
    BatteryVolume.foregroundInactive = 0xDEFB;
    BatteryVolume.foregroundDisabled = 0x8410;
    BatteryVolume.background = 0x0;
    BatteryVolume.backgroundInactive = 0xBDF7;
    BatteryVolume.backgroundDisabled = 0x8410;
    BatteryVolume.text = 0xFFFF;
    BatteryVolume.textHighlight = 0xFFFF;
    BatteryVolume.textHighlightText = 0xFFFF;
    BatteryVolume.textInactive = 0xBDF7;
    BatteryVolume.textDisabled = 0x4208;

    laScheme_Initialize(&TitleText, GFX_COLOR_MODE_RGB_565);
    TitleText.base = 0xC67A;
    TitleText.highlight = 0xC67A;
    TitleText.highlightLight = 0xFFFF;
    TitleText.shadow = 0x8410;
    TitleText.shadowDark = 0x4208;
    TitleText.foreground = 0x0;
    TitleText.foregroundInactive = 0xD71C;
    TitleText.foregroundDisabled = 0x8410;
    TitleText.background = 0x0;
    TitleText.backgroundInactive = 0xD71C;
    TitleText.backgroundDisabled = 0xC67A;
    TitleText.text = 0xFC00;
    TitleText.textHighlight = 0xBA00;
    TitleText.textHighlightText = 0xFFFF;
    TitleText.textInactive = 0xD71C;
    TitleText.textDisabled = 0x8C92;

    laScheme_Initialize(&MainGui, GFX_COLOR_MODE_RGB_565);
    MainGui.base = 0xFC00;
    MainGui.highlight = 0xFDF0;
    MainGui.highlightLight = 0xFEF7;
    MainGui.shadow = 0xFAE4;
    MainGui.shadowDark = 0xBA00;
    MainGui.foreground = 0xFFFF;
    MainGui.foregroundInactive = 0xD75F;
    MainGui.foregroundDisabled = 0x8410;
    MainGui.background = 0xFDF0;
    MainGui.backgroundInactive = 0xFEF7;
    MainGui.backgroundDisabled = 0xC67A;
    MainGui.text = 0x8410;
    MainGui.textHighlight = 0xBA00;
    MainGui.textHighlightText = 0xFFFF;
    MainGui.textInactive = 0xD71C;
    MainGui.textDisabled = 0x8C92;

    laScheme_Initialize(&MainButtons, GFX_COLOR_MODE_RGB_565);
    MainButtons.base = 0xFC00;
    MainButtons.highlight = 0xFDF0;
    MainButtons.highlightLight = 0xFEF7;
    MainButtons.shadow = 0xBA00;
    MainButtons.shadowDark = 0x8200;
    MainButtons.foreground = 0xFFFF;
    MainButtons.foregroundInactive = 0xFEF7;
    MainButtons.foregroundDisabled = 0x8410;
    MainButtons.background = 0xFDF0;
    MainButtons.backgroundInactive = 0xD71C;
    MainButtons.backgroundDisabled = 0xC67A;
    MainButtons.text = 0xFFFF;
    MainButtons.textHighlight = 0xBA00;
    MainButtons.textHighlightText = 0xFFFF;
    MainButtons.textInactive = 0xD71C;
    MainButtons.textDisabled = 0x8C92;

    laScheme_Initialize(&Screen, GFX_COLOR_MODE_RGB_565);
    Screen.base = 0xC67A;
    Screen.highlight = 0xC67A;
    Screen.highlightLight = 0xFFFF;
    Screen.shadow = 0x8410;
    Screen.shadowDark = 0x4208;
    Screen.foreground = 0x0;
    Screen.foregroundInactive = 0xD71C;
    Screen.foregroundDisabled = 0x8410;
    Screen.background = 0x0;
    Screen.backgroundInactive = 0xD71C;
    Screen.backgroundDisabled = 0xC67A;
    Screen.text = 0x2A7F;
    Screen.textHighlight = 0x1F;
    Screen.textHighlightText = 0xFFFF;
    Screen.textInactive = 0xD71C;
    Screen.textDisabled = 0x8C92;

    laScheme_Initialize(&ClearScheme, GFX_COLOR_MODE_RGB_565);
    ClearScheme.base = 0x0;
    ClearScheme.highlight = 0x0;
    ClearScheme.highlightLight = 0x0;
    ClearScheme.shadow = 0x0;
    ClearScheme.shadowDark = 0x0;
    ClearScheme.foreground = 0x0;
    ClearScheme.foregroundInactive = 0x0;
    ClearScheme.foregroundDisabled = 0x0;
    ClearScheme.background = 0x0;
    ClearScheme.backgroundInactive = 0x0;
    ClearScheme.backgroundDisabled = 0x0;
    ClearScheme.text = 0x0;
    ClearScheme.textHighlight = 0x0;
    ClearScheme.textHighlightText = 0x0;
    ClearScheme.textInactive = 0x0;
    ClearScheme.textDisabled = 0x0;

    laScheme_Initialize(&OverlayBlue, GFX_COLOR_MODE_RGB_565);
    OverlayBlue.base = 0x859F;
    OverlayBlue.highlight = 0xC67A;
    OverlayBlue.highlightLight = 0xFFFF;
    OverlayBlue.shadow = 0x8410;
    OverlayBlue.shadowDark = 0x4208;
    OverlayBlue.foreground = 0x859F;
    OverlayBlue.foregroundInactive = 0xD71C;
    OverlayBlue.foregroundDisabled = 0x8410;
    OverlayBlue.background = 0x859F;
    OverlayBlue.backgroundInactive = 0xD71C;
    OverlayBlue.backgroundDisabled = 0xC67A;
    OverlayBlue.text = 0x0;
    OverlayBlue.textHighlight = 0x0;
    OverlayBlue.textHighlightText = 0x0;
    OverlayBlue.textInactive = 0xD71C;
    OverlayBlue.textDisabled = 0x8C92;

    laScheme_Initialize(&StatusBar, GFX_COLOR_MODE_RGB_565);
    StatusBar.base = 0xC67A;
    StatusBar.highlight = 0xC67A;
    StatusBar.highlightLight = 0xFFFF;
    StatusBar.shadow = 0x8410;
    StatusBar.shadowDark = 0x4208;
    StatusBar.foreground = 0x0;
    StatusBar.foregroundInactive = 0xD71C;
    StatusBar.foregroundDisabled = 0x8410;
    StatusBar.background = 0xFFFF;
    StatusBar.backgroundInactive = 0xD71C;
    StatusBar.backgroundDisabled = 0xC67A;
    StatusBar.text = 0xFFFF;
    StatusBar.textHighlight = 0x1F;
    StatusBar.textHighlightText = 0xFFFF;
    StatusBar.textInactive = 0xD71C;
    StatusBar.textDisabled = 0x8C92;

    laScheme_Initialize(&OverlayRed, GFX_COLOR_MODE_RGB_565);
    OverlayRed.base = 0xF800;
    OverlayRed.highlight = 0xC67A;
    OverlayRed.highlightLight = 0xFFFF;
    OverlayRed.shadow = 0x8410;
    OverlayRed.shadowDark = 0x4208;
    OverlayRed.foreground = 0xF800;
    OverlayRed.foregroundInactive = 0xD71C;
    OverlayRed.foregroundDisabled = 0x8410;
    OverlayRed.background = 0xFFFF;
    OverlayRed.backgroundInactive = 0xD71C;
    OverlayRed.backgroundDisabled = 0xC67A;
    OverlayRed.text = 0xF800;
    OverlayRed.textHighlight = 0xF800;
    OverlayRed.textHighlightText = 0xFFFF;
    OverlayRed.textInactive = 0xD71C;
    OverlayRed.textDisabled = 0x8C92;

    laScheme_Initialize(&defaultScheme, GFX_COLOR_MODE_RGB_565);
    defaultScheme.base = 0x0;
    defaultScheme.highlight = 0xC67A;
    defaultScheme.highlightLight = 0xFFFF;
    defaultScheme.shadow = 0x8410;
    defaultScheme.shadowDark = 0x4208;
    defaultScheme.foreground = 0xFFFF;
    defaultScheme.foregroundInactive = 0xDEFB;
    defaultScheme.foregroundDisabled = 0x8410;
    defaultScheme.background = 0x0;
    defaultScheme.backgroundInactive = 0xDEFB;
    defaultScheme.backgroundDisabled = 0xDEFB;
    defaultScheme.text = 0xFFFF;
    defaultScheme.textHighlight = 0xDEFB;
    defaultScheme.textHighlightText = 0xFFFF;
    defaultScheme.textInactive = 0xBDF7;
    defaultScheme.textDisabled = 0x8C92;

    laScheme_Initialize(&OverlayGreen, GFX_COLOR_MODE_RGB_565);
    OverlayGreen.base = 0x7E0;
    OverlayGreen.highlight = 0xC67A;
    OverlayGreen.highlightLight = 0xFFFF;
    OverlayGreen.shadow = 0x8410;
    OverlayGreen.shadowDark = 0x4208;
    OverlayGreen.foreground = 0x7E0;
    OverlayGreen.foregroundInactive = 0xD71C;
    OverlayGreen.foregroundDisabled = 0x8410;
    OverlayGreen.background = 0xFFFF;
    OverlayGreen.backgroundInactive = 0xD71C;
    OverlayGreen.backgroundDisabled = 0xC67A;
    OverlayGreen.text = 0x7E0;
    OverlayGreen.textHighlight = 0x7E0;
    OverlayGreen.textHighlightText = 0xFFFF;
    OverlayGreen.textInactive = 0xD71C;
    OverlayGreen.textDisabled = 0x8C92;

    laScheme_Initialize(&TouchOverlay, GFX_COLOR_MODE_RGB_565);
    TouchOverlay.base = 0xC67A;
    TouchOverlay.highlight = 0xC67A;
    TouchOverlay.highlightLight = 0xFFFF;
    TouchOverlay.shadow = 0x8410;
    TouchOverlay.shadowDark = 0x4208;
    TouchOverlay.foreground = 0x0;
    TouchOverlay.foregroundInactive = 0xD71C;
    TouchOverlay.foregroundDisabled = 0x8410;
    TouchOverlay.background = 0xF800;
    TouchOverlay.backgroundInactive = 0xD71C;
    TouchOverlay.backgroundDisabled = 0xC67A;
    TouchOverlay.text = 0x0;
    TouchOverlay.textHighlight = 0x1F;
    TouchOverlay.textHighlightText = 0xFFFF;
    TouchOverlay.textInactive = 0xD71C;
    TouchOverlay.textDisabled = 0x8C92;

    laScheme_Initialize(&BlackBackground, GFX_COLOR_MODE_RGB_565);
    BlackBackground.base = 0x0;
    BlackBackground.highlight = 0xC67A;
    BlackBackground.highlightLight = 0xFFFF;
    BlackBackground.shadow = 0x8410;
    BlackBackground.shadowDark = 0x4208;
    BlackBackground.foreground = 0xFFFF;
    BlackBackground.foregroundInactive = 0xDEFB;
    BlackBackground.foregroundDisabled = 0x8410;
    BlackBackground.background = 0x0;
    BlackBackground.backgroundInactive = 0xDEFB;
    BlackBackground.backgroundDisabled = 0xDEFB;
    BlackBackground.text = 0xFFFF;
    BlackBackground.textHighlight = 0xDEFB;
    BlackBackground.textHighlightText = 0xFFFF;
    BlackBackground.textInactive = 0xBDF7;
    BlackBackground.textDisabled = 0x8C92;

    laScheme_Initialize(&OverlayOrange, GFX_COLOR_MODE_RGB_565);
    OverlayOrange.base = 0x0;
    OverlayOrange.highlight = 0xC67A;
    OverlayOrange.highlightLight = 0xFFFF;
    OverlayOrange.shadow = 0x8410;
    OverlayOrange.shadowDark = 0x4208;
    OverlayOrange.foreground = 0xFD66;
    OverlayOrange.foregroundInactive = 0xD71C;
    OverlayOrange.foregroundDisabled = 0x8410;
    OverlayOrange.background = 0xFFFF;
    OverlayOrange.backgroundInactive = 0xD71C;
    OverlayOrange.backgroundDisabled = 0xC67A;
    OverlayOrange.text = 0xFD66;
    OverlayOrange.textHighlight = 0xFD66;
    OverlayOrange.textHighlightText = 0xFFFF;
    OverlayOrange.textInactive = 0xD71C;
    OverlayOrange.textDisabled = 0x8C92;

    laScheme_Initialize(&GreyBackground, GFX_COLOR_MODE_RGB_565);
    GreyBackground.base = 0xC67A;
    GreyBackground.highlight = 0xC67A;
    GreyBackground.highlightLight = 0xFFFF;
    GreyBackground.shadow = 0x8410;
    GreyBackground.shadowDark = 0x4208;
    GreyBackground.foreground = 0x0;
    GreyBackground.foregroundInactive = 0xC67A;
    GreyBackground.foregroundDisabled = 0x8410;
    GreyBackground.background = 0xC67A;
    GreyBackground.backgroundInactive = 0xC67A;
    GreyBackground.backgroundDisabled = 0xC67A;
    GreyBackground.text = 0x0;
    GreyBackground.textHighlight = 0x1F;
    GreyBackground.textHighlightText = 0xFFFF;
    GreyBackground.textInactive = 0xC67A;
    GreyBackground.textDisabled = 0x8C92;

    laScheme_Initialize(&OverlayWhite, GFX_COLOR_MODE_RGB_565);
    OverlayWhite.base = 0xFFFF;
    OverlayWhite.highlight = 0xFFFF;
    OverlayWhite.highlightLight = 0xFFFF;
    OverlayWhite.shadow = 0xFFFF;
    OverlayWhite.shadowDark = 0x4208;
    OverlayWhite.foreground = 0xFFFF;
    OverlayWhite.foregroundInactive = 0xD71C;
    OverlayWhite.foregroundDisabled = 0x8410;
    OverlayWhite.background = 0xFFFF;
    OverlayWhite.backgroundInactive = 0xD71C;
    OverlayWhite.backgroundDisabled = 0xC67A;
    OverlayWhite.text = 0x0;
    OverlayWhite.textHighlight = 0x0;
    OverlayWhite.textHighlightText = 0x0;
    OverlayWhite.textInactive = 0xD71C;
    OverlayWhite.textDisabled = 0x8C92;

    laScheme_Initialize(&BatteryVolumeLow, GFX_COLOR_MODE_RGB_565);
    BatteryVolumeLow.base = 0xF802;
    BatteryVolumeLow.highlight = 0xF802;
    BatteryVolumeLow.highlightLight = 0xF802;
    BatteryVolumeLow.shadow = 0xDEFB;
    BatteryVolumeLow.shadowDark = 0xF802;
    BatteryVolumeLow.foreground = 0xF802;
    BatteryVolumeLow.foregroundInactive = 0xDEFB;
    BatteryVolumeLow.foregroundDisabled = 0x8410;
    BatteryVolumeLow.background = 0x0;
    BatteryVolumeLow.backgroundInactive = 0xBDF7;
    BatteryVolumeLow.backgroundDisabled = 0x8410;
    BatteryVolumeLow.text = 0xF802;
    BatteryVolumeLow.textHighlight = 0xF802;
    BatteryVolumeLow.textHighlightText = 0xF802;
    BatteryVolumeLow.textInactive = 0xBDF7;
    BatteryVolumeLow.textDisabled = 0x4208;

    laScheme_Initialize(&ScanningProgress, GFX_COLOR_MODE_RGB_565);
    ScanningProgress.base = 0x0;
    ScanningProgress.highlight = 0x189F;
    ScanningProgress.highlightLight = 0xD6DB;
    ScanningProgress.shadow = 0xDEFB;
    ScanningProgress.shadowDark = 0x8C51;
    ScanningProgress.foreground = 0xDEFB;
    ScanningProgress.foregroundInactive = 0xDEFB;
    ScanningProgress.foregroundDisabled = 0x8410;
    ScanningProgress.background = 0x0;
    ScanningProgress.backgroundInactive = 0xBDF7;
    ScanningProgress.backgroundDisabled = 0x8410;
    ScanningProgress.text = 0xBDF7;
    ScanningProgress.textHighlight = 0xFFFF;
    ScanningProgress.textHighlightText = 0xFFFF;
    ScanningProgress.textInactive = 0xBDF7;
    ScanningProgress.textDisabled = 0x4208;

    laScheme_Initialize(&WhiteBackground, GFX_COLOR_MODE_RGB_565);
    WhiteBackground.base = 0xFFFF;
    WhiteBackground.highlight = 0xFFFF;
    WhiteBackground.highlightLight = 0xFFFF;
    WhiteBackground.shadow = 0xDEFB;
    WhiteBackground.shadowDark = 0xFFFF;
    WhiteBackground.foreground = 0xFFFF;
    WhiteBackground.foregroundInactive = 0xD71C;
    WhiteBackground.foregroundDisabled = 0xFFFF;
    WhiteBackground.background = 0xFFFF;
    WhiteBackground.backgroundInactive = 0xDEFB;
    WhiteBackground.backgroundDisabled = 0xDEFB;
    WhiteBackground.text = 0x4208;
    WhiteBackground.textHighlight = 0xB6DF;
    WhiteBackground.textHighlightText = 0xFFFF;
    WhiteBackground.textInactive = 0xDEFB;
    WhiteBackground.textDisabled = 0xBDF7;

    laScheme_Initialize(&OverlayLogo, GFX_COLOR_MODE_RGB_565);
    OverlayLogo.base = 0xFFFF;
    OverlayLogo.highlight = 0xC67A;
    OverlayLogo.highlightLight = 0xFBA0;
    OverlayLogo.shadow = 0x8410;
    OverlayLogo.shadowDark = 0x4208;
    OverlayLogo.foreground = 0xFBA0;
    OverlayLogo.foregroundInactive = 0xD71C;
    OverlayLogo.foregroundDisabled = 0x8410;
    OverlayLogo.background = 0xFBA0;
    OverlayLogo.backgroundInactive = 0xD71C;
    OverlayLogo.backgroundDisabled = 0xC67A;
    OverlayLogo.text = 0xFBA0;
    OverlayLogo.textHighlight = 0xFBA0;
    OverlayLogo.textHighlightText = 0xFBA0;
    OverlayLogo.textInactive = 0xD71C;
    OverlayLogo.textDisabled = 0x8C92;

    laScheme_Initialize(&GeneralText, GFX_COLOR_MODE_RGB_565);
    GeneralText.base = 0xC67A;
    GeneralText.highlight = 0xC67A;
    GeneralText.highlightLight = 0xFFFF;
    GeneralText.shadow = 0x8410;
    GeneralText.shadowDark = 0x4208;
    GeneralText.foreground = 0x0;
    GeneralText.foregroundInactive = 0xD71C;
    GeneralText.foregroundDisabled = 0x8410;
    GeneralText.background = 0x0;
    GeneralText.backgroundInactive = 0xD71C;
    GeneralText.backgroundDisabled = 0xC67A;
    GeneralText.text = 0x8410;
    GeneralText.textHighlight = 0x5CDF;
    GeneralText.textHighlightText = 0xFFFF;
    GeneralText.textInactive = 0xD71C;
    GeneralText.textDisabled = 0x8C92;

    GFX_Set(GFXF_DRAW_PIPELINE_MODE, GFX_PIPELINE_GCUGPU);
    laContext_SetStringTable(&stringTable);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_SplashScreen);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_TRUE, LA_TRUE, &ScreenCreate_MainGUI);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_DeviceSettings);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_DisplaySettings);
    laContext_AddScreen(screen);

    screen = laScreen_New(LA_FALSE, LA_FALSE, &ScreenCreate_ErrorScreen);
    laContext_AddScreen(screen);

    laContext_SetPreemptionLevel(LA_PREEMPTION_LEVEL_2);
    laContext_SetActiveScreen(1);

	return 0;
}

static void ScreenCreate_SplashScreen(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 344, 800);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetScheme((laWidget*)layer0, &WhiteBackground);
    laLayer_SetBufferCount(layer0, 2);
    laLayer_SetMaskEnable(layer0, LA_TRUE);
    laLayer_SetMaskColor(layer0, 0x0);

    laScreen_SetLayer(screen, 0, layer0);

    ImageWidget2 = laImageWidget_New();
    laWidget_SetPosition((laWidget*)ImageWidget2, 20, 76);
    laWidget_SetSize((laWidget*)ImageWidget2, 309, 78);
    laWidget_SetScheme((laWidget*)ImageWidget2, &WhiteBackground);
    laWidget_SetBackgroundType((laWidget*)ImageWidget2, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ImageWidget2, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(ImageWidget2, &OccuityLogo);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)ImageWidget2);

    LabelWidget3 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget3, 71, 343);
    laWidget_SetSize((laWidget*)LabelWidget3, 197, 84);
    laWidget_SetScheme((laWidget*)LabelWidget3, &GeneralText);
    laWidget_SetBackgroundType((laWidget*)LabelWidget3, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget3, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget3, laString_CreateFromID(string_DeviceDescriptionString));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget3);

    LabelWidget4 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget4, 75, 193);
    laWidget_SetSize((laWidget*)LabelWidget4, 197, 68);
    laWidget_SetScheme((laWidget*)LabelWidget4, &TitleText);
    laWidget_SetBackgroundType((laWidget*)LabelWidget4, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget4, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LabelWidget4, laString_CreateFromID(string_DeviceString));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget4);

    DeviceIDLabel = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)DeviceIDLabel, 21, 652);
    laWidget_SetSize((laWidget*)DeviceIDLabel, 256, 60);
    laWidget_SetVisible((laWidget*)DeviceIDLabel, LA_FALSE);
    laWidget_SetBackgroundType((laWidget*)DeviceIDLabel, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)DeviceIDLabel, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(DeviceIDLabel, laString_CreateFromID(string_PIVersionString));
    laLabelWidget_SetHAlignment(DeviceIDLabel, LA_HALIGN_LEFT);
    laLabelWidget_SetTextLineSpace(DeviceIDLabel, 20);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)DeviceIDLabel);

    PIVersionLabel = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)PIVersionLabel, 21, 702);
    laWidget_SetSize((laWidget*)PIVersionLabel, 256, 20);
    laWidget_SetVisible((laWidget*)PIVersionLabel, LA_FALSE);
    laWidget_SetBackgroundType((laWidget*)PIVersionLabel, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)PIVersionLabel, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(PIVersionLabel, laString_CreateFromID(string_PIVersionString));
    laLabelWidget_SetHAlignment(PIVersionLabel, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)PIVersionLabel);

    PDAVersionLabel = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)PDAVersionLabel, 21, 722);
    laWidget_SetSize((laWidget*)PDAVersionLabel, 256, 20);
    laWidget_SetVisible((laWidget*)PDAVersionLabel, LA_FALSE);
    laWidget_SetBackgroundType((laWidget*)PDAVersionLabel, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)PDAVersionLabel, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(PDAVersionLabel, laString_CreateFromID(string_PDAVersionString));
    laLabelWidget_SetHAlignment(PDAVersionLabel, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)PDAVersionLabel);

    LSCVersionLabel = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LSCVersionLabel, 21, 742);
    laWidget_SetSize((laWidget*)LSCVersionLabel, 256, 20);
    laWidget_SetVisible((laWidget*)LSCVersionLabel, LA_FALSE);
    laWidget_SetBackgroundType((laWidget*)LSCVersionLabel, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LSCVersionLabel, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(LSCVersionLabel, laString_CreateFromID(string_LSCVersionString));
    laLabelWidget_SetHAlignment(LSCVersionLabel, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LSCVersionLabel);

    PEVersionLabel = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)PEVersionLabel, 21, 762);
    laWidget_SetSize((laWidget*)PEVersionLabel, 256, 20);
    laWidget_SetVisible((laWidget*)PEVersionLabel, LA_FALSE);
    laWidget_SetBackgroundType((laWidget*)PEVersionLabel, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)PEVersionLabel, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(PEVersionLabel, laString_CreateFromID(string_InitString));
    laLabelWidget_SetHAlignment(PEVersionLabel, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)PEVersionLabel);

    LogoWidget = laWidget_New();
    laWidget_SetPosition((laWidget*)LogoWidget, 99, 500);
    laWidget_SetSize((laWidget*)LogoWidget, 150, 100);
    laWidget_SetEnabled((laWidget*)LogoWidget, LA_FALSE);
    laWidget_SetOptimizationFlags((laWidget*)LogoWidget, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetBackgroundType((laWidget*)LogoWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LogoWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetAlphaEnable((laWidget*)LogoWidget, GFX_TRUE);
    laWidget_SetAlphaAmount((laWidget*)LogoWidget, 255);
    laWidget_AddChild((laWidget*)layer0, LogoWidget);

    StartCircle = laCircleWidget_New();
    laWidget_SetPosition((laWidget*)StartCircle, 12, 46);
    laWidget_SetSize((laWidget*)StartCircle, 12, 12);
    laWidget_SetEnabled((laWidget*)StartCircle, LA_FALSE);
    laWidget_SetVisible((laWidget*)StartCircle, LA_FALSE);
    laWidget_SetOptimizationFlags((laWidget*)StartCircle, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetScheme((laWidget*)StartCircle, &OverlayLogo);
    laWidget_SetBackgroundType((laWidget*)StartCircle, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)StartCircle, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)StartCircle, 0, 0, 0, 0);
    laWidget_SetAlphaEnable((laWidget*)StartCircle, GFX_TRUE);
    laWidget_SetAlphaAmount((laWidget*)StartCircle, 255);
    laCircleWidget_SetOrigin(StartCircle, 5, 4);
    laCircleWidget_SetRadius(StartCircle, 5);
    laCircleWidget_SetThickness(StartCircle, 5);
    laCircleWidget_SetFilled(StartCircle, true);
    laWidget_AddChild((laWidget*)LogoWidget, (laWidget*)StartCircle);

    LogoLine = laProgressBarWidget_New();
    laWidget_SetPosition((laWidget*)LogoLine, 20, 46);
    laWidget_SetSize((laWidget*)LogoLine, 110, 9);
    laWidget_SetEnabled((laWidget*)LogoLine, LA_FALSE);
    laWidget_SetVisible((laWidget*)LogoLine, LA_FALSE);
    laWidget_SetOptimizationFlags((laWidget*)LogoLine, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetScheme((laWidget*)LogoLine, &OverlayLogo);
    laWidget_SetBackgroundType((laWidget*)LogoLine, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)LogoLine, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)LogoLine, 0, 0, 0, 0);
    laWidget_SetAlphaEnable((laWidget*)LogoLine, GFX_TRUE);
    laWidget_SetAlphaAmount((laWidget*)LogoLine, 255);
    laProgressBarWidget_SetValue(LogoLine, 10);
    laWidget_AddChild((laWidget*)LogoWidget, (laWidget*)LogoLine);

    LogoCircle = laCircularSliderWidget_New();
    laWidget_SetPosition((laWidget*)LogoCircle, 2, 0);
    laWidget_SetSize((laWidget*)LogoCircle, 140, 100);
    laWidget_SetEnabled((laWidget*)LogoCircle, LA_FALSE);
    laWidget_SetVisible((laWidget*)LogoCircle, LA_FALSE);
    laWidget_SetOptimizationFlags((laWidget*)LogoCircle, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetScheme((laWidget*)LogoCircle, &OverlayLogo);
    laWidget_SetBackgroundType((laWidget*)LogoCircle, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LogoCircle, LA_WIDGET_BORDER_NONE);
    laWidget_SetAlphaEnable((laWidget*)LogoCircle, GFX_TRUE);
    laWidget_SetAlphaAmount((laWidget*)LogoCircle, 255);
    laCircularSliderWidget_SetRadius(LogoCircle, 40);
    laCircularSliderWidget_SetStartAngle(LogoCircle, 180);
    laCircularSliderWidget_SetValue(LogoCircle, 0);
    laCircularSliderWidget_SetStickyButton(LogoCircle, LA_FALSE);
    laCircularSliderWidget_SetTouchOnButtonOnly(LogoCircle, LA_FALSE);
    laCircularSliderWidget_SetDirection(LogoCircle, CIRCULAR_SLIDER_DIR_CLOCKWISE);
    laCircularSliderWidget_SetArcVisible(LogoCircle, OUTSIDE_CIRCLE_BORDER, LA_FALSE);
    laCircularSliderWidget_SetArcThickness(LogoCircle, OUTSIDE_CIRCLE_BORDER, 10);
    laCircularSliderWidget_SetArcVisible(LogoCircle, INSIDE_CIRCLE_BORDER, LA_FALSE);
    laCircularSliderWidget_SetArcThickness(LogoCircle, ACTIVE_AREA, 9);
    laCircularSliderWidget_SetArcVisible(LogoCircle, INACTIVE_AREA, LA_FALSE);
    laCircularSliderWidget_SetArcVisible(LogoCircle, CIRCLE_BUTTON, LA_FALSE);
    laCircularSliderWidget_SetArcRadius(LogoCircle, CIRCLE_BUTTON, 30);
    laCircularSliderWidget_SetArcThickness(LogoCircle, CIRCLE_BUTTON, 10);
    laCircularSliderWidget_SetArcScheme(LogoCircle, CIRCLE_BUTTON, &OverlayOrange);
    laWidget_AddChild((laWidget*)LogoWidget, (laWidget*)LogoCircle);

}

static void ScreenCreate_MainGUI(laScreen* screen)
{
    laLayer* layer0;

    laScreen_SetShowEventCallback(screen, &MainGUI_ShowEvent);

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 344, 800);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetScheme((laWidget*)layer0, &BlackBackground);
    laLayer_SetBufferCount(layer0, 2);
    laWidget_SetOptimizationFlags((laWidget*)layer0, LA_WIDGET_OPT_LOCAL_REDRAW);

    laScreen_SetLayer(screen, 0, layer0);

    GroupScanStats = laGroupBoxWidget_New();
    laWidget_SetPosition((laWidget*)GroupScanStats, 10, 405);
    laWidget_SetSize((laWidget*)GroupScanStats, 320, 80);
    laWidget_SetScheme((laWidget*)GroupScanStats, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)GroupScanStats, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)GroupScanStats, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GroupScanStats);

    TimeToScanLW = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TimeToScanLW, 5, 2);
    laWidget_SetSize((laWidget*)TimeToScanLW, 290, 20);
    laWidget_SetOptimizationFlags((laWidget*)TimeToScanLW, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetScheme((laWidget*)TimeToScanLW, &OverlayYellow);
    laWidget_SetBackgroundType((laWidget*)TimeToScanLW, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)TimeToScanLW, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetHAlignment(TimeToScanLW, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GroupScanStats, (laWidget*)TimeToScanLW);

    TimeScanningTookLW = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)TimeScanningTookLW, 5, 20);
    laWidget_SetSize((laWidget*)TimeScanningTookLW, 290, 20);
    laWidget_SetOptimizationFlags((laWidget*)TimeScanningTookLW, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetScheme((laWidget*)TimeScanningTookLW, &OverlayYellow);
    laWidget_SetBackgroundType((laWidget*)TimeScanningTookLW, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)TimeScanningTookLW, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetHAlignment(TimeScanningTookLW, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GroupScanStats, (laWidget*)TimeScanningTookLW);

    AverageZInScanLW = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)AverageZInScanLW, 5, 38);
    laWidget_SetSize((laWidget*)AverageZInScanLW, 290, 20);
    laWidget_SetOptimizationFlags((laWidget*)AverageZInScanLW, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetScheme((laWidget*)AverageZInScanLW, &OverlayYellow);
    laWidget_SetBackgroundType((laWidget*)AverageZInScanLW, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)AverageZInScanLW, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetHAlignment(AverageZInScanLW, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GroupScanStats, (laWidget*)AverageZInScanLW);

    AverageTempInScanLW = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)AverageTempInScanLW, 5, 56);
    laWidget_SetSize((laWidget*)AverageTempInScanLW, 300, 20);
    laWidget_SetOptimizationFlags((laWidget*)AverageTempInScanLW, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetScheme((laWidget*)AverageTempInScanLW, &OverlayYellow);
    laWidget_SetBackgroundType((laWidget*)AverageTempInScanLW, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)AverageTempInScanLW, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetHAlignment(AverageTempInScanLW, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)GroupScanStats, (laWidget*)AverageTempInScanLW);

    StatusBarPanelWidget = laWidget_New();
    laWidget_SetPosition((laWidget*)StatusBarPanelWidget, 0, 773);
    laWidget_SetSize((laWidget*)StatusBarPanelWidget, 340, 25);
    laWidget_SetScheme((laWidget*)StatusBarPanelWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)StatusBarPanelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)StatusBarPanelWidget, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, StatusBarPanelWidget);

    LaserWidget = laImageWidget_New();
    laWidget_SetPosition((laWidget*)LaserWidget, 170, 1);
    laWidget_SetSize((laWidget*)LaserWidget, 24, 18);
    laWidget_SetVisible((laWidget*)LaserWidget, LA_FALSE);
    laWidget_SetScheme((laWidget*)LaserWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)LaserWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LaserWidget, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(LaserWidget, &Laser_symbol_med);
    laWidget_AddChild((laWidget*)StatusBarPanelWidget, (laWidget*)LaserWidget);

    LaserErrorWidget = laImageWidget_New();
    laWidget_SetPosition((laWidget*)LaserErrorWidget, 166, -3);
    laWidget_SetSize((laWidget*)LaserErrorWidget, 31, 28);
    laWidget_SetVisible((laWidget*)LaserErrorWidget, LA_FALSE);
    laWidget_SetBackgroundType((laWidget*)LaserErrorWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LaserErrorWidget, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(LaserErrorWidget, &no_symbol);
    laWidget_AddChild((laWidget*)StatusBarPanelWidget, (laWidget*)LaserErrorWidget);

    ScanWidget = laImageWidget_New();
    laWidget_SetPosition((laWidget*)ScanWidget, 250, 2);
    laWidget_SetSize((laWidget*)ScanWidget, 32, 18);
    laWidget_SetVisible((laWidget*)ScanWidget, LA_FALSE);
    laWidget_SetScheme((laWidget*)ScanWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)ScanWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ScanWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)ScanWidget, 0, 0, 0, 0);
    laImageWidget_SetImage(ScanWidget, &Scanning_Icon);
    laWidget_AddChild((laWidget*)StatusBarPanelWidget, (laWidget*)ScanWidget);

    UsbWidget = laImageWidget_New();
    laWidget_SetPosition((laWidget*)UsbWidget, 205, 2);
    laWidget_SetSize((laWidget*)UsbWidget, 32, 18);
    laWidget_SetVisible((laWidget*)UsbWidget, LA_FALSE);
    laWidget_SetScheme((laWidget*)UsbWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)UsbWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)UsbWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)UsbWidget, 0, 0, 0, 0);
    laImageWidget_SetImage(UsbWidget, &USBLogo);
    laWidget_AddChild((laWidget*)StatusBarPanelWidget, (laWidget*)UsbWidget);

    BatteryWidget = laProgressBarWidget_New();
    laWidget_SetPosition((laWidget*)BatteryWidget, 300, 5);
    laWidget_SetSize((laWidget*)BatteryWidget, 25, 12);
    laWidget_SetScheme((laWidget*)BatteryWidget, &BatteryVolume);
    laWidget_SetBackgroundType((laWidget*)BatteryWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)BatteryWidget, LA_WIDGET_BORDER_LINE);
    laWidget_SetMargins((laWidget*)BatteryWidget, 0, 0, 0, 0);
    laProgressBarWidget_SetValue(BatteryWidget, 100);
    laWidget_AddChild((laWidget*)StatusBarPanelWidget, (laWidget*)BatteryWidget);

    ChargeWidget = laImageWidget_New();
    laWidget_SetPosition((laWidget*)ChargeWidget, 3, 1);
    laWidget_SetSize((laWidget*)ChargeWidget, 18, 10);
    laWidget_SetVisible((laWidget*)ChargeWidget, LA_FALSE);
    laWidget_SetBackgroundType((laWidget*)ChargeWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ChargeWidget, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(ChargeWidget, &Battery_charge_small);
    laWidget_AddChild((laWidget*)BatteryWidget, (laWidget*)ChargeWidget);

    BatteryWidget2 = laRectangleWidget_New();
    laWidget_SetPosition((laWidget*)BatteryWidget2, 24, 3);
    laWidget_SetSize((laWidget*)BatteryWidget2, 3, 6);
    laWidget_SetScheme((laWidget*)BatteryWidget2, &BatteryVolume);
    laWidget_SetBackgroundType((laWidget*)BatteryWidget2, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)BatteryWidget2, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)BatteryWidget2, 0, 0, 0, 0);
    laWidget_AddChild((laWidget*)BatteryWidget, (laWidget*)BatteryWidget2);

    MainGuiPanelWidget = laWidget_New();
    laWidget_SetSize((laWidget*)MainGuiPanelWidget, 340, 780);
    laWidget_SetScheme((laWidget*)MainGuiPanelWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)MainGuiPanelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MainGuiPanelWidget, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)layer0, MainGuiPanelWidget);

    CameraWidget = laImagePlusWidget_New();
    laWidget_SetSize((laWidget*)CameraWidget, 340, 300);
    laWidget_SetEnabled((laWidget*)CameraWidget, LA_FALSE);
    laWidget_SetOptimizationFlags((laWidget*)CameraWidget, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetBackgroundType((laWidget*)CameraWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CameraWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)CameraWidget, 0, 0, 0, 0);
    laImagePlusWidget_SetStretchEnabled(CameraWidget, LA_TRUE);
    laWidget_AddChild((laWidget*)MainGuiPanelWidget, (laWidget*)CameraWidget);

    SaturatedWidget = laImageWidget_New();
    laWidget_SetPosition((laWidget*)SaturatedWidget, 22, 14);
    laWidget_SetSize((laWidget*)SaturatedWidget, 50, 48);
    laWidget_SetEnabled((laWidget*)SaturatedWidget, LA_FALSE);
    laWidget_SetVisible((laWidget*)SaturatedWidget, LA_FALSE);
    laWidget_SetOptimizationFlags((laWidget*)SaturatedWidget, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetBackgroundType((laWidget*)SaturatedWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)SaturatedWidget, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(SaturatedWidget, &saturated_icon_small);
    laWidget_AddChild((laWidget*)CameraWidget, (laWidget*)SaturatedWidget);

    CameraAlignmentArcWidget = laArcWidget_New();
    laWidget_SetPosition((laWidget*)CameraAlignmentArcWidget, 95, 91);
    laWidget_SetSize((laWidget*)CameraAlignmentArcWidget, 150, 150);
    laWidget_SetOptimizationFlags((laWidget*)CameraAlignmentArcWidget, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetScheme((laWidget*)CameraAlignmentArcWidget, &OverlayRed);
    laWidget_SetBackgroundType((laWidget*)CameraAlignmentArcWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CameraAlignmentArcWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetAlphaEnable((laWidget*)CameraAlignmentArcWidget, GFX_TRUE);
    laWidget_SetAlphaAmount((laWidget*)CameraAlignmentArcWidget, 160);
    laArcWidget_SetStartAngle(CameraAlignmentArcWidget, -45);
    laArcWidget_SetCenterAngle(CameraAlignmentArcWidget, 270);
    laArcWidget_SetThickness(CameraAlignmentArcWidget, 14);
    laArcWidget_SetRoundEdge(CameraAlignmentArcWidget, LA_TRUE);
    laWidget_AddChild((laWidget*)CameraWidget, (laWidget*)CameraAlignmentArcWidget);

    ScanningProgressArcWidget = laArcWidget_New();
    laWidget_SetPosition((laWidget*)ScanningProgressArcWidget, 95, 91);
    laWidget_SetSize((laWidget*)ScanningProgressArcWidget, 150, 150);
    laWidget_SetOptimizationFlags((laWidget*)ScanningProgressArcWidget, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetScheme((laWidget*)ScanningProgressArcWidget, &OverlayWhite);
    laWidget_SetBackgroundType((laWidget*)ScanningProgressArcWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ScanningProgressArcWidget, LA_WIDGET_BORDER_NONE);
    laArcWidget_SetStartAngle(ScanningProgressArcWidget, 45);
    laArcWidget_SetCenterAngle(ScanningProgressArcWidget, 90);
    laArcWidget_SetThickness(ScanningProgressArcWidget, 4);
    laArcWidget_SetRoundEdge(ScanningProgressArcWidget, LA_TRUE);
    laWidget_AddChild((laWidget*)CameraWidget, (laWidget*)ScanningProgressArcWidget);

    ScanButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)ScanButtonWidget, 0, 303);
    laWidget_SetSize((laWidget*)ScanButtonWidget, 340, 100);
    laWidget_SetOptimizationFlags((laWidget*)ScanButtonWidget, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetScheme((laWidget*)ScanButtonWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)ScanButtonWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ScanButtonWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)ScanButtonWidget, 4, 8, 4, 8);
    laButtonWidget_SetPressedImage(ScanButtonWidget, &start_scan_round_orange);
    laButtonWidget_SetReleasedImage(ScanButtonWidget, &start_scan_round_orange);
    laButtonWidget_SetPressedEventCallback(ScanButtonWidget, &ScanButtonWidget_PressedEvent);

    laWidget_AddChild((laWidget*)MainGuiPanelWidget, (laWidget*)ScanButtonWidget);

    MenuButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)MenuButtonWidget, 0, 715);
    laWidget_SetSize((laWidget*)MenuButtonWidget, 340, 50);
    laWidget_SetScheme((laWidget*)MenuButtonWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)MenuButtonWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)MenuButtonWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)MenuButtonWidget, 4, 10, 4, 20);
    laButtonWidget_SetPressedImage(MenuButtonWidget, &Spanner_white);
    laButtonWidget_SetReleasedImage(MenuButtonWidget, &Spanner_white);
    laButtonWidget_SetPressedEventCallback(MenuButtonWidget, &MenuButtonWidget_PressedEvent);

    laWidget_AddChild((laWidget*)MainGuiPanelWidget, (laWidget*)MenuButtonWidget);

    MeasurementWidget0 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)MeasurementWidget0, 0, 490);
    laWidget_SetSize((laWidget*)MeasurementWidget0, 340, 56);
    laWidget_SetEnabled((laWidget*)MeasurementWidget0, LA_FALSE);
    laWidget_SetVisible((laWidget*)MeasurementWidget0, LA_FALSE);
    laWidget_SetScheme((laWidget*)MeasurementWidget0, &OverlayGreen);
    laWidget_SetBackgroundType((laWidget*)MeasurementWidget0, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MeasurementWidget0, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)MeasurementWidget0, 4, 0, 4, 0);
    laWidget_SetAlphaEnable((laWidget*)MeasurementWidget0, GFX_TRUE);
    laWidget_SetAlphaAmount((laWidget*)MeasurementWidget0, 255);
    laLabelWidget_SetText(MeasurementWidget0, laString_CreateFromID(string_MeasurementString));
    laLabelWidget_SetVAlignment(MeasurementWidget0, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)MainGuiPanelWidget, (laWidget*)MeasurementWidget0);

    StdevWidget0 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)StdevWidget0, 220, 2);
    laWidget_SetSize((laWidget*)StdevWidget0, 80, 44);
    laWidget_SetEnabled((laWidget*)StdevWidget0, LA_FALSE);
    laWidget_SetScheme((laWidget*)StdevWidget0, &OverlayGreen);
    laWidget_SetBackgroundType((laWidget*)StdevWidget0, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)StdevWidget0, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)StdevWidget0, 0, 0, 4, 2);
    laLabelWidget_SetText(StdevWidget0, laString_CreateFromID(string_StdevString));
    laLabelWidget_SetHAlignment(StdevWidget0, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)MeasurementWidget0, (laWidget*)StdevWidget0);

    ScanLabelWidget0 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)ScanLabelWidget0, 0, 2);
    laWidget_SetSize((laWidget*)ScanLabelWidget0, 80, 44);
    laWidget_SetEnabled((laWidget*)ScanLabelWidget0, LA_FALSE);
    laWidget_SetScheme((laWidget*)ScanLabelWidget0, &OverlayGreen);
    laWidget_SetBackgroundType((laWidget*)ScanLabelWidget0, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ScanLabelWidget0, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)ScanLabelWidget0, 0, 0, 4, 2);
    laLabelWidget_SetText(ScanLabelWidget0, laString_CreateFromID(string_ScanCountString));
    laLabelWidget_SetHAlignment(ScanLabelWidget0, LA_HALIGN_LEFT);
    laLabelWidget_SetVAlignment(ScanLabelWidget0, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)MeasurementWidget0, (laWidget*)ScanLabelWidget0);

    MeasurementWidget1 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)MeasurementWidget1, 0, 540);
    laWidget_SetSize((laWidget*)MeasurementWidget1, 340, 56);
    laWidget_SetEnabled((laWidget*)MeasurementWidget1, LA_FALSE);
    laWidget_SetVisible((laWidget*)MeasurementWidget1, LA_FALSE);
    laWidget_SetScheme((laWidget*)MeasurementWidget1, &OverlayGreen);
    laWidget_SetBackgroundType((laWidget*)MeasurementWidget1, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MeasurementWidget1, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)MeasurementWidget1, 4, 0, 4, 0);
    laWidget_SetAlphaEnable((laWidget*)MeasurementWidget1, GFX_TRUE);
    laWidget_SetAlphaAmount((laWidget*)MeasurementWidget1, 255);
    laLabelWidget_SetText(MeasurementWidget1, laString_CreateFromID(string_MeasurementString));
    laLabelWidget_SetVAlignment(MeasurementWidget1, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)MainGuiPanelWidget, (laWidget*)MeasurementWidget1);

    StdevWidget1 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)StdevWidget1, 220, 2);
    laWidget_SetSize((laWidget*)StdevWidget1, 80, 44);
    laWidget_SetEnabled((laWidget*)StdevWidget1, LA_FALSE);
    laWidget_SetScheme((laWidget*)StdevWidget1, &OverlayGreen);
    laWidget_SetBackgroundType((laWidget*)StdevWidget1, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)StdevWidget1, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)StdevWidget1, 0, 0, 4, 2);
    laLabelWidget_SetText(StdevWidget1, laString_CreateFromID(string_StdevString));
    laLabelWidget_SetHAlignment(StdevWidget1, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)MeasurementWidget1, (laWidget*)StdevWidget1);

    ScanLabelWidget1 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)ScanLabelWidget1, 0, 2);
    laWidget_SetSize((laWidget*)ScanLabelWidget1, 80, 44);
    laWidget_SetEnabled((laWidget*)ScanLabelWidget1, LA_FALSE);
    laWidget_SetScheme((laWidget*)ScanLabelWidget1, &OverlayGreen);
    laWidget_SetBackgroundType((laWidget*)ScanLabelWidget1, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ScanLabelWidget1, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)ScanLabelWidget1, 0, 0, 4, 2);
    laLabelWidget_SetText(ScanLabelWidget1, laString_CreateFromID(string_ScanCountString));
    laLabelWidget_SetHAlignment(ScanLabelWidget1, LA_HALIGN_LEFT);
    laLabelWidget_SetVAlignment(ScanLabelWidget1, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)MeasurementWidget1, (laWidget*)ScanLabelWidget1);

    MeasurementWidget2 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)MeasurementWidget2, 0, 590);
    laWidget_SetSize((laWidget*)MeasurementWidget2, 340, 56);
    laWidget_SetEnabled((laWidget*)MeasurementWidget2, LA_FALSE);
    laWidget_SetVisible((laWidget*)MeasurementWidget2, LA_FALSE);
    laWidget_SetScheme((laWidget*)MeasurementWidget2, &OverlayGreen);
    laWidget_SetBackgroundType((laWidget*)MeasurementWidget2, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MeasurementWidget2, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)MeasurementWidget2, 4, 0, 4, 0);
    laWidget_SetAlphaEnable((laWidget*)MeasurementWidget2, GFX_TRUE);
    laWidget_SetAlphaAmount((laWidget*)MeasurementWidget2, 255);
    laLabelWidget_SetText(MeasurementWidget2, laString_CreateFromID(string_MeasurementString));
    laLabelWidget_SetVAlignment(MeasurementWidget2, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)MainGuiPanelWidget, (laWidget*)MeasurementWidget2);

    StdevWidget2 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)StdevWidget2, 220, 2);
    laWidget_SetSize((laWidget*)StdevWidget2, 80, 44);
    laWidget_SetEnabled((laWidget*)StdevWidget2, LA_FALSE);
    laWidget_SetScheme((laWidget*)StdevWidget2, &OverlayGreen);
    laWidget_SetBackgroundType((laWidget*)StdevWidget2, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)StdevWidget2, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)StdevWidget2, 0, 0, 4, 2);
    laLabelWidget_SetText(StdevWidget2, laString_CreateFromID(string_StdevString));
    laLabelWidget_SetHAlignment(StdevWidget2, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)MeasurementWidget2, (laWidget*)StdevWidget2);

    ScanLabelWidget2 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)ScanLabelWidget2, 0, 2);
    laWidget_SetSize((laWidget*)ScanLabelWidget2, 80, 44);
    laWidget_SetEnabled((laWidget*)ScanLabelWidget2, LA_FALSE);
    laWidget_SetScheme((laWidget*)ScanLabelWidget2, &OverlayGreen);
    laWidget_SetBackgroundType((laWidget*)ScanLabelWidget2, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ScanLabelWidget2, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)ScanLabelWidget2, 0, 0, 4, 2);
    laLabelWidget_SetText(ScanLabelWidget2, laString_CreateFromID(string_ScanCountString));
    laLabelWidget_SetHAlignment(ScanLabelWidget2, LA_HALIGN_LEFT);
    laLabelWidget_SetVAlignment(ScanLabelWidget2, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)MeasurementWidget2, (laWidget*)ScanLabelWidget2);

    MeasurementWidget3 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)MeasurementWidget3, 0, 654);
    laWidget_SetSize((laWidget*)MeasurementWidget3, 340, 56);
    laWidget_SetEnabled((laWidget*)MeasurementWidget3, LA_FALSE);
    laWidget_SetVisible((laWidget*)MeasurementWidget3, LA_FALSE);
    laWidget_SetScheme((laWidget*)MeasurementWidget3, &OverlayGreen);
    laWidget_SetBackgroundType((laWidget*)MeasurementWidget3, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MeasurementWidget3, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)MeasurementWidget3, 4, 0, 4, 0);
    laLabelWidget_SetText(MeasurementWidget3, laString_CreateFromID(string_MeasurementString));
    laLabelWidget_SetVAlignment(MeasurementWidget3, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)MainGuiPanelWidget, (laWidget*)MeasurementWidget3);

    StdevWidget3 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)StdevWidget3, 220, 2);
    laWidget_SetSize((laWidget*)StdevWidget3, 80, 44);
    laWidget_SetEnabled((laWidget*)StdevWidget3, LA_FALSE);
    laWidget_SetScheme((laWidget*)StdevWidget3, &OverlayGreen);
    laWidget_SetBackgroundType((laWidget*)StdevWidget3, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)StdevWidget3, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)StdevWidget3, 0, 0, 4, 2);
    laLabelWidget_SetText(StdevWidget3, laString_CreateFromID(string_StdevString));
    laLabelWidget_SetHAlignment(StdevWidget3, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)MeasurementWidget3, (laWidget*)StdevWidget3);

    ScanLabelWidget3 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)ScanLabelWidget3, 0, 2);
    laWidget_SetSize((laWidget*)ScanLabelWidget3, 80, 44);
    laWidget_SetEnabled((laWidget*)ScanLabelWidget3, LA_FALSE);
    laWidget_SetScheme((laWidget*)ScanLabelWidget3, &OverlayGreen);
    laWidget_SetBackgroundType((laWidget*)ScanLabelWidget3, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ScanLabelWidget3, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)ScanLabelWidget3, 0, 0, 4, 2);
    laLabelWidget_SetText(ScanLabelWidget3, laString_CreateFromID(string_ScanCountString));
    laLabelWidget_SetHAlignment(ScanLabelWidget3, LA_HALIGN_LEFT);
    laLabelWidget_SetVAlignment(ScanLabelWidget3, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)MeasurementWidget3, (laWidget*)ScanLabelWidget3);

    MenuPanelWidget = laWidget_New();
    laWidget_SetPosition((laWidget*)MenuPanelWidget, 0, 510);
    laWidget_SetSize((laWidget*)MenuPanelWidget, 173, 202);
    laWidget_SetVisible((laWidget*)MenuPanelWidget, LA_FALSE);
    laWidget_SetBackgroundType((laWidget*)MenuPanelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)MenuPanelWidget, LA_WIDGET_BORDER_NONE);
    laWidget_AddChild((laWidget*)MainGuiPanelWidget, MenuPanelWidget);

    CameraSettingsMenuButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)CameraSettingsMenuButtonWidget, 2, 54);
    laWidget_SetSize((laWidget*)CameraSettingsMenuButtonWidget, 170, 50);
    laWidget_SetScheme((laWidget*)CameraSettingsMenuButtonWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)CameraSettingsMenuButtonWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)CameraSettingsMenuButtonWidget, LA_WIDGET_BORDER_LINE);
    laWidget_SetMargins((laWidget*)CameraSettingsMenuButtonWidget, 8, 4, 4, 9);
    laButtonWidget_SetText(CameraSettingsMenuButtonWidget, laString_CreateFromID(string_CameraSettingsString));
    laButtonWidget_SetHAlignment(CameraSettingsMenuButtonWidget, LA_HALIGN_LEFT);
    laButtonWidget_SetPressedImage(CameraSettingsMenuButtonWidget, &camera_menu);
    laButtonWidget_SetReleasedImage(CameraSettingsMenuButtonWidget, &camera_menu);
    laButtonWidget_SetImageMargin(CameraSettingsMenuButtonWidget, 0);
    laButtonWidget_SetPressedEventCallback(CameraSettingsMenuButtonWidget, &CameraSettingsMenuButtonWidget_PressedEvent);

    laWidget_AddChild((laWidget*)MenuPanelWidget, (laWidget*)CameraSettingsMenuButtonWidget);

    DeviceSettingsMenuButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)DeviceSettingsMenuButtonWidget, 2, 104);
    laWidget_SetSize((laWidget*)DeviceSettingsMenuButtonWidget, 170, 50);
    laWidget_SetScheme((laWidget*)DeviceSettingsMenuButtonWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)DeviceSettingsMenuButtonWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)DeviceSettingsMenuButtonWidget, LA_WIDGET_BORDER_LINE);
    laWidget_SetMargins((laWidget*)DeviceSettingsMenuButtonWidget, 4, 4, 4, 9);
    laButtonWidget_SetText(DeviceSettingsMenuButtonWidget, laString_CreateFromID(string_DeviceSettingsMenuString));
    laButtonWidget_SetHAlignment(DeviceSettingsMenuButtonWidget, LA_HALIGN_LEFT);
    laButtonWidget_SetPressedImage(DeviceSettingsMenuButtonWidget, &Spanner_menu);
    laButtonWidget_SetReleasedImage(DeviceSettingsMenuButtonWidget, &Spanner_menu);
    laButtonWidget_SetImageMargin(DeviceSettingsMenuButtonWidget, 4);
    laButtonWidget_SetPressedEventCallback(DeviceSettingsMenuButtonWidget, &DeviceSettingsMenuButtonWidget_PressedEvent);

    laWidget_AddChild((laWidget*)MenuPanelWidget, (laWidget*)DeviceSettingsMenuButtonWidget);

    DisplaySettingsMenuButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)DisplaySettingsMenuButtonWidget, 2, 154);
    laWidget_SetSize((laWidget*)DisplaySettingsMenuButtonWidget, 170, 50);
    laWidget_SetScheme((laWidget*)DisplaySettingsMenuButtonWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)DisplaySettingsMenuButtonWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)DisplaySettingsMenuButtonWidget, LA_WIDGET_BORDER_LINE);
    laWidget_SetMargins((laWidget*)DisplaySettingsMenuButtonWidget, 4, 4, 4, 7);
    laButtonWidget_SetText(DisplaySettingsMenuButtonWidget, laString_CreateFromID(string_DisplaySettingsMenuString));
    laButtonWidget_SetHAlignment(DisplaySettingsMenuButtonWidget, LA_HALIGN_LEFT);
    laButtonWidget_SetPressedImage(DisplaySettingsMenuButtonWidget, &display_menu);
    laButtonWidget_SetReleasedImage(DisplaySettingsMenuButtonWidget, &display_menu);
    laButtonWidget_SetImageMargin(DisplaySettingsMenuButtonWidget, 11);
    laButtonWidget_SetPressedEventCallback(DisplaySettingsMenuButtonWidget, &DisplaySettingsMenuButtonWidget_PressedEvent);

    laWidget_AddChild((laWidget*)MenuPanelWidget, (laWidget*)DisplaySettingsMenuButtonWidget);

    CameraSettingsPanelWidget = laWidget_New();
    laWidget_SetPosition((laWidget*)CameraSettingsPanelWidget, -1, 3);
    laWidget_SetSize((laWidget*)CameraSettingsPanelWidget, 340, 710);
    laWidget_SetEnabled((laWidget*)CameraSettingsPanelWidget, LA_FALSE);
    laWidget_SetVisible((laWidget*)CameraSettingsPanelWidget, LA_FALSE);
    laWidget_SetScheme((laWidget*)CameraSettingsPanelWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)CameraSettingsPanelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CameraSettingsPanelWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)CameraSettingsPanelWidget, 0, 0, 0, 0);
    laWidget_AddChild((laWidget*)layer0, CameraSettingsPanelWidget);

    CameraLeftButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)CameraLeftButtonWidget, 40, 555);
    laWidget_SetSize((laWidget*)CameraLeftButtonWidget, 80, 50);
    laWidget_SetScheme((laWidget*)CameraLeftButtonWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)CameraLeftButtonWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CameraLeftButtonWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)CameraLeftButtonWidget, 8, 8, 8, 8);
    laButtonWidget_SetHAlignment(CameraLeftButtonWidget, LA_HALIGN_LEFT);
    laButtonWidget_SetPressedImage(CameraLeftButtonWidget, &arrow_left_2);
    laButtonWidget_SetReleasedImage(CameraLeftButtonWidget, &arrow_left_2);
    laButtonWidget_SetImagePosition(CameraLeftButtonWidget, LA_RELATIVE_POSITION_BEHIND);
    laButtonWidget_SetPressedEventCallback(CameraLeftButtonWidget, &CameraLeftButtonWidget_PressedEvent);
    laButtonWidget_SetReleasedEventCallback(CameraLeftButtonWidget, &CameraLeftButtonWidget_ReleasedEvent);

    laWidget_AddChild((laWidget*)CameraSettingsPanelWidget, (laWidget*)CameraLeftButtonWidget);

    CameraUpButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)CameraUpButtonWidget, 145, 455);
    laWidget_SetSize((laWidget*)CameraUpButtonWidget, 50, 80);
    laWidget_SetScheme((laWidget*)CameraUpButtonWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)CameraUpButtonWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CameraUpButtonWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)CameraUpButtonWidget, 8, 8, 8, 8);
    laButtonWidget_SetVAlignment(CameraUpButtonWidget, LA_VALIGN_TOP);
    laButtonWidget_SetPressedImage(CameraUpButtonWidget, &arrow_up_2);
    laButtonWidget_SetReleasedImage(CameraUpButtonWidget, &arrow_up_2);
    laButtonWidget_SetImagePosition(CameraUpButtonWidget, LA_RELATIVE_POSITION_BEHIND);
    laButtonWidget_SetPressedEventCallback(CameraUpButtonWidget, &CameraUpButtonWidget_PressedEvent);
    laButtonWidget_SetReleasedEventCallback(CameraUpButtonWidget, &CameraUpButtonWidget_ReleasedEvent);

    laWidget_AddChild((laWidget*)CameraSettingsPanelWidget, (laWidget*)CameraUpButtonWidget);

    CameraRightButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)CameraRightButtonWidget, 220, 555);
    laWidget_SetSize((laWidget*)CameraRightButtonWidget, 80, 50);
    laWidget_SetScheme((laWidget*)CameraRightButtonWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)CameraRightButtonWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CameraRightButtonWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)CameraRightButtonWidget, 8, 8, 8, 8);
    laButtonWidget_SetHAlignment(CameraRightButtonWidget, LA_HALIGN_RIGHT);
    laButtonWidget_SetPressedImage(CameraRightButtonWidget, &arrow_right_2);
    laButtonWidget_SetReleasedImage(CameraRightButtonWidget, &arrow_right_2);
    laButtonWidget_SetImagePosition(CameraRightButtonWidget, LA_RELATIVE_POSITION_BEHIND);
    laButtonWidget_SetPressedEventCallback(CameraRightButtonWidget, &CameraRightButtonWidget_PressedEvent);
    laButtonWidget_SetReleasedEventCallback(CameraRightButtonWidget, &CameraRightButtonWidget_ReleasedEvent);

    laWidget_AddChild((laWidget*)CameraSettingsPanelWidget, (laWidget*)CameraRightButtonWidget);

    CameraDownButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)CameraDownButtonWidget, 145, 627);
    laWidget_SetSize((laWidget*)CameraDownButtonWidget, 50, 80);
    laWidget_SetScheme((laWidget*)CameraDownButtonWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)CameraDownButtonWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CameraDownButtonWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)CameraDownButtonWidget, 8, 8, 8, 8);
    laButtonWidget_SetVAlignment(CameraDownButtonWidget, LA_VALIGN_BOTTOM);
    laButtonWidget_SetPressedImage(CameraDownButtonWidget, &arrow_down_2);
    laButtonWidget_SetReleasedImage(CameraDownButtonWidget, &arrow_down_2);
    laButtonWidget_SetImagePosition(CameraDownButtonWidget, LA_RELATIVE_POSITION_BEHIND);
    laButtonWidget_SetPressedEventCallback(CameraDownButtonWidget, &CameraDownButtonWidget_PressedEvent);
    laButtonWidget_SetReleasedEventCallback(CameraDownButtonWidget, &CameraDownButtonWidget_ReleasedEvent);

    laWidget_AddChild((laWidget*)CameraSettingsPanelWidget, (laWidget*)CameraDownButtonWidget);

    CameraHSTARTLabelWidget = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)CameraHSTARTLabelWidget, 10, 330);
    laWidget_SetSize((laWidget*)CameraHSTARTLabelWidget, 58, 25);
    laWidget_SetScheme((laWidget*)CameraHSTARTLabelWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)CameraHSTARTLabelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CameraHSTARTLabelWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)CameraHSTARTLabelWidget, 5, 0, 0, 0);
    laLabelWidget_SetText(CameraHSTARTLabelWidget, laString_CreateFromID(string_CameraHSTARTString));
    laLabelWidget_SetHAlignment(CameraHSTARTLabelWidget, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)CameraSettingsPanelWidget, (laWidget*)CameraHSTARTLabelWidget);

    CameraHSTARTValueLabelWidget = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)CameraHSTARTValueLabelWidget, 78, 330);
    laWidget_SetSize((laWidget*)CameraHSTARTValueLabelWidget, 40, 25);
    laWidget_SetScheme((laWidget*)CameraHSTARTValueLabelWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)CameraHSTARTValueLabelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CameraHSTARTValueLabelWidget, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(CameraHSTARTValueLabelWidget, laString_CreateFromID(string_ZeroString));
    laLabelWidget_SetHAlignment(CameraHSTARTValueLabelWidget, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)CameraSettingsPanelWidget, (laWidget*)CameraHSTARTValueLabelWidget);

    CameraVSTARTLabelWidget = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)CameraVSTARTLabelWidget, 122, 330);
    laWidget_SetSize((laWidget*)CameraVSTARTLabelWidget, 57, 25);
    laWidget_SetScheme((laWidget*)CameraVSTARTLabelWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)CameraVSTARTLabelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CameraVSTARTLabelWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)CameraVSTARTLabelWidget, 5, 0, 0, 0);
    laLabelWidget_SetText(CameraVSTARTLabelWidget, laString_CreateFromID(string_CameraVSTARTString));
    laLabelWidget_SetHAlignment(CameraVSTARTLabelWidget, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)CameraSettingsPanelWidget, (laWidget*)CameraVSTARTLabelWidget);

    CameraVSTARTValueLabelWidget = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)CameraVSTARTValueLabelWidget, 195, 330);
    laWidget_SetSize((laWidget*)CameraVSTARTValueLabelWidget, 40, 25);
    laWidget_SetScheme((laWidget*)CameraVSTARTValueLabelWidget, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)CameraVSTARTValueLabelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CameraVSTARTValueLabelWidget, LA_WIDGET_BORDER_NONE);
    laLabelWidget_SetText(CameraVSTARTValueLabelWidget, laString_CreateFromID(string_ZeroString));
    laLabelWidget_SetHAlignment(CameraVSTARTValueLabelWidget, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)CameraSettingsPanelWidget, (laWidget*)CameraVSTARTValueLabelWidget);

    CameraCancelButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)CameraCancelButtonWidget, 170, 365);
    laWidget_SetSize((laWidget*)CameraCancelButtonWidget, 170, 60);
    laWidget_SetScheme((laWidget*)CameraCancelButtonWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)CameraCancelButtonWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)CameraCancelButtonWidget, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetText(CameraCancelButtonWidget, laString_CreateFromID(string_CancelString));
    laButtonWidget_SetVAlignment(CameraCancelButtonWidget, LA_VALIGN_TOP);
    laButtonWidget_SetPressedEventCallback(CameraCancelButtonWidget, &CameraCancelButtonWidget_PressedEvent);

    laWidget_AddChild((laWidget*)CameraSettingsPanelWidget, (laWidget*)CameraCancelButtonWidget);

    CameraApplyButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)CameraApplyButtonWidget, 0, 365);
    laWidget_SetSize((laWidget*)CameraApplyButtonWidget, 170, 60);
    laWidget_SetScheme((laWidget*)CameraApplyButtonWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)CameraApplyButtonWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)CameraApplyButtonWidget, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetText(CameraApplyButtonWidget, laString_CreateFromID(string_ApplyString));
    laButtonWidget_SetVAlignment(CameraApplyButtonWidget, LA_VALIGN_TOP);
    laButtonWidget_SetPressedEventCallback(CameraApplyButtonWidget, &CameraApplyButtonWidget_PressedEvent);

    laWidget_AddChild((laWidget*)CameraSettingsPanelWidget, (laWidget*)CameraApplyButtonWidget);

    CameraAlinmentCircleWidget = laCircleWidget_New();
    laWidget_SetPosition((laWidget*)CameraAlinmentCircleWidget, 121, 111);
    laWidget_SetSize((laWidget*)CameraAlinmentCircleWidget, 100, 100);
    laWidget_SetOptimizationFlags((laWidget*)CameraAlinmentCircleWidget, LA_WIDGET_OPT_LOCAL_REDRAW);
    laWidget_SetScheme((laWidget*)CameraAlinmentCircleWidget, &OverlayRed);
    laWidget_SetBackgroundType((laWidget*)CameraAlinmentCircleWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)CameraAlinmentCircleWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetAlphaEnable((laWidget*)CameraAlinmentCircleWidget, GFX_TRUE);
    laWidget_SetAlphaAmount((laWidget*)CameraAlinmentCircleWidget, 180);
    laCircleWidget_SetRadius(CameraAlinmentCircleWidget, 44);
    laCircleWidget_SetThickness(CameraAlinmentCircleWidget, 3);
    laWidget_AddChild((laWidget*)CameraSettingsPanelWidget, (laWidget*)CameraAlinmentCircleWidget);

    mainscreen_cover = laRectangleWidget_New();
    laWidget_SetSize((laWidget*)mainscreen_cover, 340, 800);
    laWidget_SetVisible((laWidget*)mainscreen_cover, LA_FALSE);
    laWidget_SetScheme((laWidget*)mainscreen_cover, &BlackBackground);
    laWidget_SetBackgroundType((laWidget*)mainscreen_cover, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)mainscreen_cover, LA_WIDGET_BORDER_NONE);
    laRectangleWidget_SetThickness(mainscreen_cover, 0);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)mainscreen_cover);

}

static void ScreenCreate_DeviceSettings(laScreen* screen)
{
    laLayer* layer0;

    laScreen_SetShowEventCallback(screen, &DeviceSettings_ShowEvent);

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 344, 800);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetScheme((laWidget*)layer0, &WhiteBackground);
    laLayer_SetBufferCount(layer0, 2);

    laScreen_SetLayer(screen, 0, layer0);

    DeviceSettingsLabelWidget = laLabelWidget_New();
    laWidget_SetSize((laWidget*)DeviceSettingsLabelWidget, 240, 37);
    laWidget_SetScheme((laWidget*)DeviceSettingsLabelWidget, &TitleText);
    laWidget_SetBackgroundType((laWidget*)DeviceSettingsLabelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)DeviceSettingsLabelWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)DeviceSettingsLabelWidget, 5, 0, 0, 0);
    laLabelWidget_SetText(DeviceSettingsLabelWidget, laString_CreateFromID(string_DeviceSettingsString));
    laLabelWidget_SetHAlignment(DeviceSettingsLabelWidget, LA_HALIGN_LEFT);
    laLabelWidget_SetVAlignment(DeviceSettingsLabelWidget, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)DeviceSettingsLabelWidget);

    DeviceSettingsLcdBrtLabelWidget = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)DeviceSettingsLcdBrtLabelWidget, 0, 66);
    laWidget_SetSize((laWidget*)DeviceSettingsLcdBrtLabelWidget, 100, 52);
    laWidget_SetScheme((laWidget*)DeviceSettingsLcdBrtLabelWidget, &GeneralText);
    laWidget_SetBackgroundType((laWidget*)DeviceSettingsLcdBrtLabelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)DeviceSettingsLcdBrtLabelWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)DeviceSettingsLcdBrtLabelWidget, 5, 0, 0, 0);
    laLabelWidget_SetText(DeviceSettingsLcdBrtLabelWidget, laString_CreateFromID(string_LCDBrightnessString));
    laLabelWidget_SetHAlignment(DeviceSettingsLcdBrtLabelWidget, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)DeviceSettingsLcdBrtLabelWidget);

    DeviceSettingsLcdSliderWidget = laSliderWidget_New();
    laWidget_SetPosition((laWidget*)DeviceSettingsLcdSliderWidget, 110, 77);
    laWidget_SetSize((laWidget*)DeviceSettingsLcdSliderWidget, 220, 40);
    laWidget_SetScheme((laWidget*)DeviceSettingsLcdSliderWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)DeviceSettingsLcdSliderWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)DeviceSettingsLcdSliderWidget, LA_WIDGET_BORDER_BEVEL);
    laSliderWidget_SetOrientation(DeviceSettingsLcdSliderWidget, LA_SLIDER_ORIENT_HORIZONTAL, LA_FALSE);
    laSliderWidget_SetMaximumValue(DeviceSettingsLcdSliderWidget, 70);
    laSliderWidget_SetSliderValue(DeviceSettingsLcdSliderWidget, 20);
    laSliderWidget_SetGripSize(DeviceSettingsLcdSliderWidget, 20);
    laSliderWidget_SetValueChangedEventCallback(DeviceSettingsLcdSliderWidget, &DeviceSettingsLcdSliderWidget_ValueChangedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)DeviceSettingsLcdSliderWidget);

    DeviceSettingsApplyButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)DeviceSettingsApplyButtonWidget, 0, 730);
    laWidget_SetSize((laWidget*)DeviceSettingsApplyButtonWidget, 170, 60);
    laWidget_SetScheme((laWidget*)DeviceSettingsApplyButtonWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)DeviceSettingsApplyButtonWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)DeviceSettingsApplyButtonWidget, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetText(DeviceSettingsApplyButtonWidget, laString_CreateFromID(string_ApplyString));
    laButtonWidget_SetPressedEventCallback(DeviceSettingsApplyButtonWidget, &DeviceSettingsApplyButtonWidget_PressedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)DeviceSettingsApplyButtonWidget);

    DeviceSettingsCancelButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)DeviceSettingsCancelButtonWidget, 170, 730);
    laWidget_SetSize((laWidget*)DeviceSettingsCancelButtonWidget, 170, 60);
    laWidget_SetScheme((laWidget*)DeviceSettingsCancelButtonWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)DeviceSettingsCancelButtonWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)DeviceSettingsCancelButtonWidget, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetText(DeviceSettingsCancelButtonWidget, laString_CreateFromID(string_CancelString));
    laButtonWidget_SetPressedEventCallback(DeviceSettingsCancelButtonWidget, &DeviceSettingsCancelButtonWidget_PressedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)DeviceSettingsCancelButtonWidget);

}

static void ScreenCreate_DisplaySettings(laScreen* screen)
{
    laLayer* layer0;

    laScreen_SetShowEventCallback(screen, &DisplaySettings_ShowEvent);

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 344, 800);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laLayer_SetBufferCount(layer0, 2);
    laLayer_SetAlphaEnable(layer0, LA_TRUE);
    laLayer_SetAlphaAmount(layer0, 0xFF);

    laScreen_SetLayer(screen, 0, layer0);

    DisplaySettingsLabelWidget = laLabelWidget_New();
    laWidget_SetSize((laWidget*)DisplaySettingsLabelWidget, 240, 36);
    laWidget_SetScheme((laWidget*)DisplaySettingsLabelWidget, &TitleText);
    laWidget_SetBackgroundType((laWidget*)DisplaySettingsLabelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)DisplaySettingsLabelWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)DisplaySettingsLabelWidget, 5, 0, 0, 0);
    laLabelWidget_SetText(DisplaySettingsLabelWidget, laString_CreateFromID(string_DisplaySettingsString));
    laLabelWidget_SetHAlignment(DisplaySettingsLabelWidget, LA_HALIGN_LEFT);
    laLabelWidget_SetVAlignment(DisplaySettingsLabelWidget, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)DisplaySettingsLabelWidget);

    DisplaySettingsApplyButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)DisplaySettingsApplyButtonWidget, 0, 730);
    laWidget_SetSize((laWidget*)DisplaySettingsApplyButtonWidget, 170, 60);
    laWidget_SetScheme((laWidget*)DisplaySettingsApplyButtonWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)DisplaySettingsApplyButtonWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)DisplaySettingsApplyButtonWidget, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetText(DisplaySettingsApplyButtonWidget, laString_CreateFromID(string_ApplyString));
    laButtonWidget_SetPressedEventCallback(DisplaySettingsApplyButtonWidget, &DisplaySettingsApplyButtonWidget_PressedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)DisplaySettingsApplyButtonWidget);

    DisplaySettingsCancelButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)DisplaySettingsCancelButtonWidget, 170, 730);
    laWidget_SetSize((laWidget*)DisplaySettingsCancelButtonWidget, 170, 60);
    laWidget_SetScheme((laWidget*)DisplaySettingsCancelButtonWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)DisplaySettingsCancelButtonWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)DisplaySettingsCancelButtonWidget, LA_WIDGET_BORDER_NONE);
    laButtonWidget_SetText(DisplaySettingsCancelButtonWidget, laString_CreateFromID(string_CancelString));
    laButtonWidget_SetPressedEventCallback(DisplaySettingsCancelButtonWidget, &DisplaySettingsCancelButtonWidget_PressedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)DisplaySettingsCancelButtonWidget);

    LabelWidget1 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget1, 0, 240);
    laWidget_SetSize((laWidget*)LabelWidget1, 97, 41);
    laWidget_SetScheme((laWidget*)LabelWidget1, &GeneralText);
    laWidget_SetBackgroundType((laWidget*)LabelWidget1, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget1, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)LabelWidget1, 5, 0, 0, 0);
    laLabelWidget_SetText(LabelWidget1, laString_CreateFromID(string_LedbrightnessString));
    laLabelWidget_SetHAlignment(LabelWidget1, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget1);

    DeviceSettingsLEDSliderWidget = laSliderWidget_New();
    laWidget_SetPosition((laWidget*)DeviceSettingsLEDSliderWidget, 110, 245);
    laWidget_SetSize((laWidget*)DeviceSettingsLEDSliderWidget, 220, 40);
    laWidget_SetScheme((laWidget*)DeviceSettingsLEDSliderWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)DeviceSettingsLEDSliderWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)DeviceSettingsLEDSliderWidget, LA_WIDGET_BORDER_BEVEL);
    laSliderWidget_SetOrientation(DeviceSettingsLEDSliderWidget, LA_SLIDER_ORIENT_HORIZONTAL, LA_FALSE);
    laSliderWidget_SetMinimumValue(DeviceSettingsLEDSliderWidget, 10);
    laSliderWidget_SetMaximumValue(DeviceSettingsLEDSliderWidget, 255);
    laSliderWidget_SetSliderValue(DeviceSettingsLEDSliderWidget, 100);
    laSliderWidget_SetGripSize(DeviceSettingsLEDSliderWidget, 20);
    laSliderWidget_SetValueChangedEventCallback(DeviceSettingsLEDSliderWidget, &DeviceSettingsLEDSliderWidget_ValueChangedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)DeviceSettingsLEDSliderWidget);

    DevSettingsPeak2AmplitudeValueLabelWidget = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)DevSettingsPeak2AmplitudeValueLabelWidget, 79, 165);
    laWidget_SetSize((laWidget*)DevSettingsPeak2AmplitudeValueLabelWidget, 40, 42);
    laWidget_SetScheme((laWidget*)DevSettingsPeak2AmplitudeValueLabelWidget, &GeneralText);
    laWidget_SetBackgroundType((laWidget*)DevSettingsPeak2AmplitudeValueLabelWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)DevSettingsPeak2AmplitudeValueLabelWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)DevSettingsPeak2AmplitudeValueLabelWidget, 5, 0, 0, 0);
    laLabelWidget_SetText(DevSettingsPeak2AmplitudeValueLabelWidget, laString_CreateFromID(string_ValueString));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)DevSettingsPeak2AmplitudeValueLabelWidget);

    LabelWidget2 = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)LabelWidget2, 3, 184);
    laWidget_SetSize((laWidget*)LabelWidget2, 84, 41);
    laWidget_SetScheme((laWidget*)LabelWidget2, &GeneralText);
    laWidget_SetBackgroundType((laWidget*)LabelWidget2, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)LabelWidget2, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)LabelWidget2, 5, 0, 0, 0);
    laLabelWidget_SetText(LabelWidget2, laString_CreateFromID(string_AmpGainString));
    laLabelWidget_SetHAlignment(LabelWidget2, LA_HALIGN_LEFT);
    laWidget_AddChild((laWidget*)layer0, (laWidget*)LabelWidget2);

    DeviceSettingsPeak2AmplitudeSliderWidget = laSliderWidget_New();
    laWidget_SetPosition((laWidget*)DeviceSettingsPeak2AmplitudeSliderWidget, 113, 192);
    laWidget_SetSize((laWidget*)DeviceSettingsPeak2AmplitudeSliderWidget, 220, 40);
    laWidget_SetScheme((laWidget*)DeviceSettingsPeak2AmplitudeSliderWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)DeviceSettingsPeak2AmplitudeSliderWidget, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)DeviceSettingsPeak2AmplitudeSliderWidget, LA_WIDGET_BORDER_BEVEL);
    laWidget_SetMargins((laWidget*)DeviceSettingsPeak2AmplitudeSliderWidget, 14, 14, 14, 14);
    laSliderWidget_SetOrientation(DeviceSettingsPeak2AmplitudeSliderWidget, LA_SLIDER_ORIENT_HORIZONTAL, LA_FALSE);
    laSliderWidget_SetMaximumValue(DeviceSettingsPeak2AmplitudeSliderWidget, 56);
    laSliderWidget_SetGripSize(DeviceSettingsPeak2AmplitudeSliderWidget, 20);
    laSliderWidget_SetValueChangedEventCallback(DeviceSettingsPeak2AmplitudeSliderWidget, &DeviceSettingsPeak2AmplitudeSliderWidget_ValueChangedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)DeviceSettingsPeak2AmplitudeSliderWidget);

    AutoScanButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)AutoScanButtonWidget, 10, 670);
    laWidget_SetSize((laWidget*)AutoScanButtonWidget, 160, 50);
    laWidget_SetScheme((laWidget*)AutoScanButtonWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)AutoScanButtonWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)AutoScanButtonWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)AutoScanButtonWidget, 4, 6, 4, 4);
    laButtonWidget_SetToggleable(AutoScanButtonWidget, LA_TRUE);
    laButtonWidget_SetText(AutoScanButtonWidget, laString_CreateFromID(string_AutomaticScanString));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)AutoScanButtonWidget);

    LaserCheckButtonWidget = laButtonWidget_New();
    laWidget_SetPosition((laWidget*)LaserCheckButtonWidget, 170, 670);
    laWidget_SetSize((laWidget*)LaserCheckButtonWidget, 160, 50);
    laWidget_SetScheme((laWidget*)LaserCheckButtonWidget, &MainButtons);
    laWidget_SetBackgroundType((laWidget*)LaserCheckButtonWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)LaserCheckButtonWidget, LA_WIDGET_BORDER_NONE);
    laWidget_SetMargins((laWidget*)LaserCheckButtonWidget, 4, 6, 4, 4);
    laButtonWidget_SetText(LaserCheckButtonWidget, laString_CreateFromID(string_LaserCheckString));
    laButtonWidget_SetPressedEventCallback(LaserCheckButtonWidget, &LaserCheckButtonWidget_PressedEvent);

    laWidget_AddChild((laWidget*)layer0, (laWidget*)LaserCheckButtonWidget);

}

static void ScreenCreate_ErrorScreen(laScreen* screen)
{
    laLayer* layer0;

    layer0 = laLayer_New();
    laWidget_SetPosition((laWidget*)layer0, 0, 0);
    laWidget_SetSize((laWidget*)layer0, 344, 800);
    laWidget_SetBackgroundType((laWidget*)layer0, LA_WIDGET_BACKGROUND_FILL);
    laLayer_SetBufferCount(layer0, 2);

    laScreen_SetLayer(screen, 0, layer0);

    GroupBoxWidget4 = laGroupBoxWidget_New();
    laWidget_SetSize((laWidget*)GroupBoxWidget4, 340, 800);
    laWidget_SetScheme((laWidget*)GroupBoxWidget4, &GreyBackground);
    laWidget_SetBackgroundType((laWidget*)GroupBoxWidget4, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)GroupBoxWidget4, LA_WIDGET_BORDER_BEVEL);
    laWidget_SetMargins((laWidget*)GroupBoxWidget4, 8, 4, 8, 4);
    laGroupBoxWidget_SetText(GroupBoxWidget4, laString_CreateFromID(string_ErrorDialogString));
    laWidget_AddChild((laWidget*)layer0, (laWidget*)GroupBoxWidget4);

    ImageWidget5 = laImageWidget_New();
    laWidget_SetPosition((laWidget*)ImageWidget5, 1, 31);
    laWidget_SetSize((laWidget*)ImageWidget5, 123, 105);
    laWidget_SetScheme((laWidget*)ImageWidget5, &GreyBackground);
    laWidget_SetBackgroundType((laWidget*)ImageWidget5, LA_WIDGET_BACKGROUND_NONE);
    laWidget_SetBorderType((laWidget*)ImageWidget5, LA_WIDGET_BORDER_NONE);
    laImageWidget_SetImage(ImageWidget5, &warning_icon);
    laWidget_AddChild((laWidget*)GroupBoxWidget4, (laWidget*)ImageWidget5);

    ErrorLabelWidget = laLabelWidget_New();
    laWidget_SetPosition((laWidget*)ErrorLabelWidget, 11, 136);
    laWidget_SetSize((laWidget*)ErrorLabelWidget, 318, 653);
    laWidget_SetScheme((laWidget*)ErrorLabelWidget, &WhiteBackground);
    laWidget_SetBackgroundType((laWidget*)ErrorLabelWidget, LA_WIDGET_BACKGROUND_FILL);
    laWidget_SetBorderType((laWidget*)ErrorLabelWidget, LA_WIDGET_BORDER_BEVEL);
    laLabelWidget_SetText(ErrorLabelWidget, laString_CreateFromID(string_ErrorString));
    laLabelWidget_SetHAlignment(ErrorLabelWidget, LA_HALIGN_LEFT);
    laLabelWidget_SetVAlignment(ErrorLabelWidget, LA_VALIGN_TOP);
    laWidget_AddChild((laWidget*)GroupBoxWidget4, (laWidget*)ErrorLabelWidget);

}




