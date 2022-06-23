/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    scan_settings_screen.h

  @Summary
    Scan settings.

  @Description
    Configures scan settings.
 */
/* ************************************************************************** */

#ifndef _SCAN_SETTINGS_SCREEN_H    /* Guard against multiple inclusion */
#define _SCAN_SETTINGS_SCREEN_H


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
//#define DEBUG_SETTINGS   
    
#define VALUE_FIELD_FONT        Apertura_14    
    
#define TOTAL_SCANS_SCALE       10U
#define P1_SCALE_FACTOR         1310U
#define P2_SCALE_FACTOR         131U
#define VOLTAGE_SCALE           13107U                                          // Scale 16 bit value to 5V
#define MIN_SCANS               1U
#define FWHM_MIN_START          25U
#define FWHM_MAX_START          45U
#define MIN_SEPARATION_START    100U
#define MAX_SEPARATION_START    600U    
#define MAX_GAIN                127U


// *****************************************************************************
// Section: Data Types
// *****************************************************************************



// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void App_ScanSettings_ShowEvent(laScreen* scr);
void App_ScanSettingsCancelButtonWidget_PressedEvent(laButtonWidget* btn);
void App_ScanSettingsApplyButtonWidget_PressedEvent(laButtonWidget* btn);

void App_ComparatorRefSliderWidget_ValueChangedEvent(laSliderWidget* sld);
void App_Peak1ThresholdSliderWidget_ValueChangedEvent(laSliderWidget* sld);
void App_Peak2ThresholdSliderWidget_ValueChangedEvent(laSliderWidget* sld);
void App_MinSeparationSliderWidget_ValueChangedEvent(laSliderWidget* sld);
void App_MaxSeparationSliderWidget_ValueChangedEvent(laSliderWidget* sld);  
void App_TotalScansSliderWidget_ValueChangedEvent(laSliderWidget* sld);
void App_BoostGainSliderWidget_ValueChangedEvent(laSliderWidget* sld);
void App_MinFwhmSliderWidget_ValueChangedEvent(laSliderWidget* sld);
void App_MaxFwhmSliderWidget_ValueChangedEvent(laSliderWidget* sld);

void App_DSPScanSelectionButtonWidget_PressedEvent(laButtonWidget* btn);
void App_DSPScanSelectionButtonWidget_ReleasedEvent(laButtonWidget* btn);    
void App_IPScanSelectionButtonWidget_PressedEvent(laButtonWidget* btn);      
void App_IPScanSelectionButtonWidget_ReleasedEvent(laButtonWidget* btn);

void App_ScanSettingsButtonWidget_PressedEvent( laButtonWidget* btn );
void App_PupilFindingButtonWidget_PressedEvent(laButtonWidget* btn);
void App_PupilFindingButtonWidget_ReleasedEvent(laButtonWidget* btn);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _SCAN_SETTINGS_SCREEN_H */

/* *****************************************************************************
 End of File
 */
