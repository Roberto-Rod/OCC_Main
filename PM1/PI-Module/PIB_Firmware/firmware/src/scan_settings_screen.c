/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    scan_settings_screen.c

  @Summary
    Scan settings.

  @Description
    Configures scan settings.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "scan_settings_screen.h"

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

static void update_voltage_value(laLabelWidget* LabelWidget, uint16_t voltage);
static void update_cmp_voltage_value(laLabelWidget* LabelWidget, uint16_t voltage);
static void update_value(laLabelWidget* LabelWidget, uint16_t value);
static void ScanSettings_Update(void);;

/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */


static void update_voltage_value(laLabelWidget* LabelWidget, uint16_t voltage)
{
    laString la_string;
    char voltage_string[10];

    sprintf(voltage_string, "%1.2fV", (float) voltage / VOLTAGE_SCALE );

    la_string = laString_CreateFromCharBuffer(voltage_string, &VALUE_FIELD_FONT);
    laLabelWidget_SetText(LabelWidget, la_string);
    laString_Destroy(&la_string);
}

static void update_cmp_voltage_value(laLabelWidget* LabelWidget, uint16_t voltage)
{
    laString la_string;
    char voltage_string[10];
    
    float voltagef = (3.33f / 4U) + (((float) voltage / 32U) * 3.33f);

    sprintf(voltage_string, "%1.3fV", voltagef);

    la_string = laString_CreateFromCharBuffer(voltage_string, &VALUE_FIELD_FONT);
    laLabelWidget_SetText(LabelWidget, la_string);
    laString_Destroy(&la_string);
}

static void update_value(laLabelWidget* LabelWidget, uint16_t value)
{
    laString la_string;
    char value_string[10];

    sprintf(value_string, "%dµm", value);

    la_string = laString_CreateFromCharBuffer(value_string, &VALUE_FIELD_FONT);
    laLabelWidget_SetText(LabelWidget, la_string);
    laString_Destroy(&la_string);
}

static void update_scans_value(laLabelWidget* LabelWidget, uint16_t value)
{
    laString la_string;
    char value_string[10];

    sprintf(value_string, "%d", value);

    la_string = laString_CreateFromCharBuffer(value_string, &VALUE_FIELD_FONT);
    laLabelWidget_SetText(LabelWidget, la_string);
    laString_Destroy(&la_string);
}

// scanSettings - ShowEvent
void App_ScanSettings_ShowEvent(laScreen* scr)
{
    ScanSettings_Update();
}

static void ScanSettings_Update(void)
{
#ifdef DEBUG_SETTINGS        
    dputs_colour("[YELLOW]scanSettings_ShowEvent[WHITE]\r\n");
    dprintf_colour("[PINK]settings_get_comparator_reference_voltage() is %d[WHITE]\r\n", settings_get_comparator_reference_voltage());
    dprintf_colour("[PINK]settings_get_peak_1_threshold_voltage() is %d[WHITE]\r\n", settings_get_peak_1_threshold_voltage());
    dprintf_colour("[PINK]settings_get_peak_2_threshold_voltage() is %d[WHITE]\r\n", settings_get_peak_2_threshold_voltage());
    dprintf_colour("[PINK]settings_get_minimum_separation() is %d[WHITE]\r\n", settings_get_minimum_separation());
    dprintf_colour("[PINK]settings_get_maximum_separation() is %d[WHITE]\r\n", settings_get_maximum_separation());
    dprintf_colour("[PINK]settings_get_total_scans() is %d[WHITE]\r\n", settings_get_total_scans());
    dprintf_colour("[PINK]settings_get_boost_gain() is %d[WHITE]\r\n", settings_get_boost_gain());
    dprintf_colour("[PINK]settings_get_minimum_fwhm() is %d[WHITE]\r\n", settings_get_minimum_fwhm());
    dprintf_colour("[PINK]settings_get_maximum_fwhm() is %d[WHITE]\r\n", settings_get_maximum_fwhm());    
#endif    
    /* set the values for the UI elements */

}

// App_ScanSettingsCancelButtonWidget - PressedEvent
void App_ScanSettingsCancelButtonWidget_PressedEvent(laButtonWidget* btn)
{
    app_exit_configure();
}

// App_ScanSettingsApplyButtonWidget - PressedEvent
void App_ScanSettingsApplyButtonWidget_PressedEvent(laButtonWidget* btn)
{
    _SCAN_SETTINGS scan_settings;

    /* get the values selected */    

    /* check for invalid settings */
    if (scan_settings.separation_limits[0] >= scan_settings.separation_limits[1])
    {
        #ifndef DISABLE_AUDIO
        piezo_two_tone(DRV_PIEZO_TONE_2, 100U, 100U, DRV_PIEZO_TONE_3, 100U);
        #endif
        return;
    }
    /* apply the settings and save to FRAM */
    settings_set_comparator_reference_voltage(scan_settings.comparator_reference_voltage);
    settings_set_peak_1_threshold_voltage(scan_settings.peak_thresholds[0]);
    settings_set_peak_2_threshold_voltage(scan_settings.peak_thresholds[1]);
    settings_set_minimum_separation(scan_settings.separation_limits[0]);
    settings_set_maximum_separation(scan_settings.separation_limits[1]);
    //settings_set_total_scans(scan_settings.total_scans);
    settings_set_minimum_fwhm(scan_settings.fwhm_limits[0]);
    settings_set_maximum_fwhm(scan_settings.fwhm_limits[1]);
    
#ifdef DEBUG_SETTINGS
    dputs_colour("[YELLOW]applylButtonWidget_PressedEvent[WHITE]\r\n");
    dprintf_colour("[PINK]settings_get_comparator_reference_voltage() is %d[WHITE]\r\n", settings_get_comparator_reference_voltage());
    dprintf_colour("[PINK]settings_get_peak_1_threshold_voltage() is %d[WHITE]\r\n", settings_get_peak_1_threshold_voltage());
    dprintf_colour("[PINK]settings_get_peak_2_threshold_voltage() is %d[WHITE]\r\n", settings_get_peak_2_threshold_voltage());
    dprintf_colour("[PINK]settings_get_minimum_separation() is %d[WHITE]\r\n", settings_get_minimum_separation());
    dprintf_colour("[PINK]settings_get_maximum_separation() is %d[WHITE]\r\n", settings_get_maximum_separation());    
    dprintf_colour("[PINK]settings_get_total_scans() is %d[WHITE]\r\n", settings_get_total_scans());
    dprintf_colour("[PINK]settings_get_boost_gain() is %d[WHITE]\r\n", settings_get_boost_gain());
    dprintf_colour("[PINK]settings_get_minimum_fwhm() is %d[WHITE]\r\n", settings_get_minimum_fwhm());
    dprintf_colour("[PINK]settings_get_maximum_fwhm() is %d[WHITE]\r\n", settings_get_maximum_fwhm());
#endif  
    
    save_settings();
    
    app_exit_configure();
}



void App_DSPScanSelectionButtonWidget_PressedEvent(laButtonWidget* btn)
{  
} 

void App_DSPScanSelectionButtonWidget_ReleasedEvent(laButtonWidget* btn)
{ 
} 
        
void App_IPScanSelectionButtonWidget_PressedEvent(laButtonWidget* btn)
{  
} 
        
void App_IPScanSelectionButtonWidget_ReleasedEvent(laButtonWidget* btn)
{
} 

void App_PupilFindingButtonWidget_PressedEvent(laButtonWidget* btn)
{  
} 
        
void App_PupilFindingButtonWidget_ReleasedEvent(laButtonWidget* btn)
{
} 

/* *****************************************************************************
 End of File
 */
