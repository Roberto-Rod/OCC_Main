/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    configure_time_and_date_screen.h

  @Summary
    Configuration screen for setting the time and date.

  @Description
    Allows the user to set the current time and date.
 */
/* ************************************************************************** */

#ifndef _TIME_SETTINGS_SCREEN_H    /* Guard against multiple inclusion */
#define _TIME_SETTINGS_SCREEN_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */



/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */



// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************
    
void App_TimeSettingsupdate_gui( RTCCFORM* time );
void App_TimeSettingsKeyPadWidget_KeyClickEvent(laKeyPadWidget* pad, laButtonWidget* btn, uint32_t row, uint32_t col);
void App_TimeSettingsHourTextFieldWidget_TextChangedEvent(laTextFieldWidget* txt);
void App_TimeSettingsMinuteTextFieldWidget_TextChangedEvent(laTextFieldWidget* txt);
void App_TimeSettingsSecondTextFieldWidget_TextChangedEvent(laTextFieldWidget* txt);
void App_TimeSettingsDayTextFieldWidget_TextChangedEvent(laTextFieldWidget* txt);
void App_TimeSettingsMonthTextFieldWidget_TextChangedEvent(laTextFieldWidget* txt);
void App_TimeSettingsYearTextFieldWidget_TextChangedEvent(laTextFieldWidget* txt);
void App_TimeSettingsCancelButtonWidget_PressedEvent(laButtonWidget* btn);
void App_TimeSettingsSetButtonWidget_PressedEvent(laButtonWidget* btn);

uint32_t get_text_field_integer_value(laTextFieldWidget * textFieldWidget, uint8_t max_length);

 /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _CONFIGURE_TIME_AND_DATE_SCREEN_H */
