/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    configure_time_and_date_screen.c

  @Summary
    Configuration screen for setting the time and date.

  @Description
    Allows the user to set the current time and date.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "gfx/libaria/libaria_events.h"
#include "app.h"

#define EDIT_FIELD_FONT     NotoSans_Bold_16

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */


void App_TimeSettingsupdate_gui( RTCCFORM* time )
{
    char str[26];
    laString lastr;   
    

    sprintf(str, "%02d", time->hour);
    lastr = laString_CreateFromCharBuffer(str, &EDIT_FIELD_FONT);
    laTextFieldWidget_SetText(TimeSettingsHourTextFieldWidget, lastr);
    

    sprintf(str, "%02d", time->minute);
    lastr = laString_CreateFromCharBuffer(str, &EDIT_FIELD_FONT);
    laTextFieldWidget_SetText(TimeSettingsMinuteTextFieldWidget, lastr);


    sprintf(str, "%02d", time->minute);
    lastr = laString_CreateFromCharBuffer(str, &EDIT_FIELD_FONT);
    laTextFieldWidget_SetText(TimeSettingsSecondTextFieldWidget, lastr);
  

    sprintf(str, "%02d", time->date);
    lastr = laString_CreateFromCharBuffer(str, &EDIT_FIELD_FONT);
    laTextFieldWidget_SetText(TimeSettingsDayTextFieldWidget, lastr);


    sprintf(str, "%02d", time->month);
    lastr = laString_CreateFromCharBuffer(str, &EDIT_FIELD_FONT);
    laTextFieldWidget_SetText(TimeSettingsMonthTextFieldWidget, lastr);


    sprintf(str, "%02d", time->year % 100);
    lastr = laString_CreateFromCharBuffer(str, &EDIT_FIELD_FONT);
    laTextFieldWidget_SetText(TimeSettingsYearTextFieldWidget, lastr);
    
    /* destroy the string */
    laString_Destroy(&lastr);      
}


// App_TimeSettingsKeyPadWidget - KeyClickEvent
void App_TimeSettingsKeyPadWidget_KeyClickEvent(laKeyPadWidget* pad, laButtonWidget* btn, uint32_t row, uint32_t col)
{
    (void) pad;
    (void) btn;

    const char key[12] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'C', '0', 'D'};

    char key_pressed = key[(row * 3) + col];

    // Custom Action
    dprintf_colour("[YELLOW]Keypad pressed - row %d, column %d character is '%c'[WHITE]\r\n", row, col, key_pressed);
}

// App_TimeSettingsHourTextFieldWidget - TextChangedEvent
void App_TimeSettingsHourTextFieldWidget_TextChangedEvent(laTextFieldWidget* txt)
{
    static laString str;
    uint32_t length;

    dputs("App_TimeSettingsHourTextFieldWidget_TextChangedEvent() in\r\n");

    /* get the text */
    laTextFieldWidget_GetText(txt, &str);

    length = laString_Length(&str);

    /* move the focus to minutes */
    if (length == 2)
    {
        laWidget_SetFocus((laWidget *) TimeSettingsMinuteTextFieldWidget);
    }

    /* truncate to 2 characters if longer */
    if (length > 2)
    {
        laString_ReduceLength(&str, 2);

        /* set the new text */
        laTextFieldWidget_SetText(txt, str);
    }

    /* destroy the string */
    laString_Destroy(&str);

    dputs("App_TimeSettingsHourTextFieldWidget_TextChangedEvent() out\r\n");    
}

// App_TimeSettingsMinuteTextFieldWidget - TextChangedEvent
void App_TimeSettingsMinuteTextFieldWidget_TextChangedEvent(laTextFieldWidget* txt)
{
    static laString str;
    uint32_t length;

    dputs("App_TimeSettingsMinuteTextFieldWidget_TextChangedEvent() in\r\n");

    /* get the text */
    laTextFieldWidget_GetText(txt, &str);

    length = laString_Length(&str);

    /* move the focus to seconds */
    if (length == 2)
    {
        laWidget_SetFocus((laWidget *) TimeSettingsSecondTextFieldWidget);
    }

    /* truncate to 2 characters if longer */
    if (length > 2)
    {
        laString_ReduceLength(&str, 2);

        /* set the new text */
        laTextFieldWidget_SetText(txt, str);
    }

    /* destroy the string */
    laString_Destroy(&str);

    dputs("App_TimeSettingsMinuteTextFieldWidget_TextChangedEvent() out\r\n");
}

// App_TimeSettingsSecondTextFieldWidget_TextChangedEvent
void App_TimeSettingsSecondTextFieldWidget_TextChangedEvent(laTextFieldWidget* txt)
{
    static laString str;
    uint32_t length;

    dputs("App_TimeSettingsSecondTextFieldWidget_TextChangedEvent() in\r\n");

    /* get the text */
    laTextFieldWidget_GetText(txt, &str);

    length = laString_Length(&str);

    /* truncate to 2 characters if longer */
    if (length > 2)
    {
        laString_ReduceLength(&str, 2);

        /* set the new text */
        laTextFieldWidget_SetText(txt, str);
    }

    /* destroy the string */
    laString_Destroy(&str);

    dputs("App_TimeSettingsSecondTextFieldWidget_TextChangedEvent() out\r\n");
}

// App_TimeSettingsDayTextFieldWidget - TextChangedEvent
void App_TimeSettingsDayTextFieldWidget_TextChangedEvent(laTextFieldWidget* txt)
{
    static laString str;
    uint32_t length;

    dputs("App_TimeSettingsDayTextFieldWidget_TextChangedEvent() in\r\n");
    
    /* get the text */
    laTextFieldWidget_GetText(txt, &str);

    length = laString_Length(&str);

    /* move the focus to month */
    if (length == 2)
    {
        laWidget_SetFocus((laWidget *) TimeSettingsMonthTextFieldWidget);
    }

    /* truncate to 2 characters if longer */
    if (length > 2)
    {
        laString_ReduceLength(&str, 2);

        /* set the new text */
        laTextFieldWidget_SetText(txt, str);
    }

    /* destroy the string */
    laString_Destroy(&str);

    dputs("App_TimeSettingsDayTextFieldWidget_TextChangedEvent() out\r\n");
}

// App_TimeSettingsMonthTextFieldWidget - TextChangedEvent
void App_TimeSettingsMonthTextFieldWidget_TextChangedEvent(laTextFieldWidget* txt)
{
    static laString str;
    uint32_t length;

    dputs("App_TimeSettingsMonthTextFieldWidget_TextChangedEvent() in\r\n");

    /* get the text */
    laTextFieldWidget_GetText(txt, &str);

    length = laString_Length(&str);

    /* move the focus to year */
    if (length == 2)
    {
        laWidget_SetFocus((laWidget *) TimeSettingsYearTextFieldWidget);
    }

    /* truncate to 2 characters if longer */
    if (length > 2)
    {
        laString_ReduceLength(&str, 2);

        /* set the new text */
        laTextFieldWidget_SetText(txt, str);
    }

    /* destroy the string */
    laString_Destroy(&str);

    dputs("App_TimeSettingsMonthTextFieldWidget_TextChangedEvent() out\r\n");    
}

// App_TimeSettingsYearTextFieldWidget - TextChangedEvent
void App_TimeSettingsYearTextFieldWidget_TextChangedEvent(laTextFieldWidget* txt)
{
    static laString str;
    uint32_t length;

    dputs("App_TimeSettingsYearTextFieldWidget_TextChangedEvent() in\r\n");

    /* get the text */
    laTextFieldWidget_GetText(txt, &str);

    length = laString_Length(&str);

    /* truncate to 2 characters if longer */
    if (length > 2)
    {
        laString_ReduceLength(&str, 2);

        /* set the new text */
        laTextFieldWidget_SetText(txt, str);
    }

    /* destroy the string */
    laString_Destroy(&str);

    dputs("App_TimeSettingsYearTextFieldWidget_TextChangedEvent() out\r\n");    
}

// App_TimeSettingsCancelButtonWidget - PressedEvent
void App_TimeSettingsCancelButtonWidget_PressedEvent(laButtonWidget* btn)
{
    (void) btn;

    dputs_colour("[YELLOW]cancel button pressed[WHITE]\r\n");
    app_exit_configure();
}

/* get the numeric text string from a text field widget and convert it to an integer */
uint32_t get_text_field_integer_value(laTextFieldWidget * textFieldWidget, uint8_t max_length)
{
    static laString text_string;
    uint32_t length;
    GFXU_CHAR buffer[max_length + 1];
    char char_buffer[max_length + 1];
    uint32_t value;
    uint8_t i;

    /* get the text from the widget */
    laTextFieldWidget_GetText(textFieldWidget, &text_string);

    /* if there is no text then return zero */
    if (0 == laString_Length(&text_string))
    {
        return (0);
    }

    /* convert to GFXU_CHAR array */
    length = laString_ToCharBuffer(&text_string, &buffer[0], max_length);
    laString_Destroy(&text_string);

    /* length should always be greater than zero now */
    if (length > 0)
    {
        /* copy the GFXU_CHAR array to a standard C char array for atoi() */
        for (i = 0; i < length; i++)
        {
            char_buffer[i] = buffer[i];
        }

        /* make sure that there is a null on the end */
        char_buffer[i] = '\0';
        value = atoi(char_buffer);
    }
    else
    {
        value = 0;
    }

    return (value);
}

// App_TimeSettingsSetButtonWidget - PressedEvent
void App_TimeSettingsSetButtonWidget_PressedEvent(laButtonWidget* btn)
{
    (void) btn;


    RTCCFORM time;

    dputs_colour("[YELLOW]Set the time![WHITE]\r\n");

    /* get the number values from each of the text field widgets */
    time.hour = get_text_field_integer_value(TimeSettingsHourTextFieldWidget, 2);
    time.minute = get_text_field_integer_value(TimeSettingsMinuteTextFieldWidget, 2);
    time.second = get_text_field_integer_value(TimeSettingsSecondTextFieldWidget, 2);
    time.date = get_text_field_integer_value(TimeSettingsDayTextFieldWidget, 2);
    time.month = get_text_field_integer_value(TimeSettingsMonthTextFieldWidget, 2);

    time.year = get_text_field_integer_value(TimeSettingsYearTextFieldWidget, 2);

    dprintf_colour("[CYAN]Date & time value: %02d:%02d:%02d %02d/%02d/%02d[WHITE]\r\n", time.hour, time.minute, time.second, time.date, time.month, time.year);

    /* validate the fields */
    if ((time.hour <= 23) && (time.minute <= 59) && (time.second <= 59) && (time.date >= 1) && (time.date <= 31) && (time.month >= 1) && (time.month <= 12))
    {
        /* set the new time */
        app_set_time(&time);
        app_exit_configure();
        return;
    }

    dputs_colour("[RED]Date and time failed validation[WHITE]\r\n");

    /* alert the user to invalid time entered */
    #ifndef DISABLE_AUDIO
    piezo_two_tone(DRV_PIEZO_TONE_1, 100U, 100U,DRV_PIEZO_TONE_2, 100U); 
    #endif
}
