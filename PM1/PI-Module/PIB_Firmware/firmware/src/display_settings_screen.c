/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    display_settings_screen.c

  @Summary
    Display settings.

  @Description
    Configures display settings.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "display_settings_screen.h"

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

#define VALUE_FONT                  Apertura_14

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

static void displaySettings_Update(void);;
//static void update_value(laLabelWidget * LabelWidget, uint8_t value);
//static void update_radius_value(laLabelWidget * LabelWidget, uint8_t radius, uint8_t tolerance);

/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
static void update_label_value_widget_value(laLabelWidget *label_widget, double value)
{
    char percentage_string[10];
    laString la_percent_string;

    sprintf(percentage_string, "%.2f", value);

    la_percent_string = laString_CreateFromCharBuffer(percentage_string, &VALUE_FONT);
    laLabelWidget_SetText(label_widget, la_percent_string);
    laString_Destroy(&la_percent_string);
}

// DisplaySettings - ShowEvent
void App_DisplaySettings_ShowEvent(laScreen* scr)
{
    displaySettings_Update();
}

static void displaySettings_Update(void)
{
    laSliderWidget_SetSliderValue(DeviceSettingsPeak2AmplitudeSliderWidget, settings_get_peak_2_threshold_voltage() / P2_SCALE_FACTOR);
    //laSliderWidget_SetSliderValue(DeviceSettingsPeak2AmplitudeSliderWidget, settings_get_peak_2_threshold_voltage() / P2_SCALE_FACTOR);
    update_label_value_widget_value(DevSettingsPeak2AmplitudeValueLabelWidget, (double) settings_get_peak_2_threshold_voltage() / (double)VOLTAGE_SCALE);
    laButtonWidget_SetPressed(AutoScanButtonWidget, settings_get_wait_for_alignment() ? LA_TRUE : LA_FALSE);

//    pk1_target_radius = settings_get_pk1_target_radius();
//    pk1_target_radius_tolerance = settings_get_pk1_radius_tolerance();
//
//    /* PK1 target radius */
//    laSliderWidget_SetSliderValue(PK1TargetRadiusSliderWidget, settings_get_pk1_target_radius() - TARGET_RADIUS_MIN);
//
//    /* PK1 radius tolerance */
//    laSliderWidget_SetSliderValue(PK1RadiusToleranceSliderWidget, settings_get_pk1_radius_tolerance() - RADIUS_TOLERANCE_MIN);
//
//    update_radius_value(PK1TargetRadiusValueLabelWidget, pk1_target_radius, pk1_target_radius_tolerance);
//
//    /* PK1 alignment tolerance */
//    laSliderWidget_SetSliderValue(PK1AlignmentToleranceSliderWidget, settings_get_pk1_alignment_tolerance() - ALIGNMENT_TOLERANCE_MIN);
//    update_value(PK1AlignmentToleranceValueLabelWidget, settings_get_pk1_alignment_tolerance());    
    
    laSliderWidget_SetSliderValue(DeviceSettingsLEDSliderWidget, device_settings.LED_BRIGHTNESS);
}

//static void update_value(laLabelWidget * LabelWidget, uint8_t value)
//{
//    laString la_string;
//    char value_string[10];
//
//    sprintf(value_string, "%d", value);
//
//    la_string = laString_CreateFromCharBuffer(value_string, &VALUE_FIELD_FONT);
//    laLabelWidget_SetText(LabelWidget, la_string);
//    laString_Destroy(&la_string);
//}
//
//static void update_radius_value(laLabelWidget * LabelWidget, uint8_t radius, uint8_t tolerance)
//{
//    laString la_string;
//    char value_string[10];
//
//    sprintf(value_string, "%d ± %d", radius, tolerance);
//
//    la_string = laString_CreateFromCharBuffer(value_string, &VALUE_FIELD_FONT);
//    laLabelWidget_SetText(LabelWidget, la_string);
//    laString_Destroy(&la_string);
//}

// App_DisplaySettingsCancelButtonWidget - PressedEvent
void App_DisplaySettingsCancelButtonWidget_PressedEvent(laButtonWidget* btn)
{
    app_exit_configure();
}

// App_DisplaySettingsApplyButtonWidget - PressedEvent
void App_DisplaySettingsApplyButtonWidget_PressedEvent(laButtonWidget* btn)
{
    settings_set_peak_2_threshold_voltage(laSliderWidget_GetSliderValue(DeviceSettingsPeak2AmplitudeSliderWidget) * P2_SCALE_FACTOR);    
    //settings_set_laser_power(127U - laSliderWidget_GetSliderValue(DeviceSettingsLaserPowerSliderWidget));    
    //settings_set_lcd_brightness(laSliderWidget_GetSliderValue(DeviceSettingsLcdSliderWidget) + 20U);
    //settings_set_led_brightness(laSliderWidget_GetSliderValue(DeviceSettingsLEDSliderWidget)  );    
    settings_set_wait_for_alignment((bool) laButtonWidget_GetPressed(AutoScanButtonWidget));
    
    laButtonWidget_SetPressed(LaserCheckButtonWidget, LA_FALSE);
    
    
    settings_set_led_brightness(laSliderWidget_GetSliderValue(DeviceSettingsLEDSliderWidget));

    save_settings();

    app_exit_configure();
//    #ifndef DISABLE_AUDIO
//    piezo_two_tone(DRV_PIEZO_TONE_1, 100U, 100U,DRV_PIEZO_TONE_2, 100U); 
//    #endif 
}

// App_DeviceSettingsLEDSliderWidget - ValueChangedEvent
void App_DeviceSettingsLEDSliderWidget_ValueChangedEvent(laSliderWidget* sld)
{
    uint8_t led_brightness = laSliderWidget_GetSliderValue(sld);
    dprintf_colour("[GREEN]LED slider value = %d[WHITE]\r\n", led_brightness);
    
    app_set_led_brightness(led_brightness, true);
}

// App_DeviceSettingsLaserCheckButtonWidget - PressedEvent
void App_DeviceSettingsLaserCheckButtonWidget_PressedEvent(laButtonWidget* btn)
{
    if( laButtonWidget_GetPressed( btn ) )
    {
        app_send_laser_check_command();
    }
}

// App_DeviceSettingsAmpGainSliderWidget - ValueChangedEvent
void App_DeviceSettingsPeak2AmplitudeSliderWidget_ValueChangedEvent(laSliderWidget* sld)
{
    uint16_t voltage = laSliderWidget_GetSliderValue(sld);
    dprintf_colour("[GREEN]PK2 threshold slider value = %d[WHITE]\r\n", voltage);
    update_label_value_widget_value(DevSettingsPeak2AmplitudeValueLabelWidget, ((double)voltage * (double)P2_SCALE_FACTOR) / (double)VOLTAGE_SCALE);
}

/* *****************************************************************************
 End of File
 */
