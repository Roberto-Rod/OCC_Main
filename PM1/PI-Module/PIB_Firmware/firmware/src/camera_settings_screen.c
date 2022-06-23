/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    camera_settings_screen.c

  @Summary
    Screen for configuring camera settings.

  @Description
    Allows camera settings to be viewed and changed.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "gfx/libaria/libaria_events.h"
#include "app.h"
#include "settings.h"
#include "gfx/libaria/inc/libaria_utils.h"

/* HSTART is register 0x17, default value is 0x69 */
/* VSTART is register 0x19, default value is 0x0C */

#define CAMERA_HSTART_MINIMUM   1
#define CAMERA_HSTART_MAXIMUM   0xff
#define CAMERA_VSTART_MINIMUM   0
#define CAMERA_VSTART_MAXIMUM   0xff

#define INITIAL_REPEAT_DELAY    300
#define REPEAT_DELAY            100

typedef enum
{
    H_DECREMENT,
    H_INCREMENT,
    V_DECREMENT,
    V_INCREMENT
} camera_settings_operation;

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

static uint8_t camera_hstart;
static uint8_t camera_vstart;
static uint8_t initial_camera_hstart;
static uint8_t initial_camera_vstart;
static SYS_TIME_HANDLE sys_time_handle = SYS_TIME_HANDLE_INVALID;

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

static void update_camera_main_hstart_value(void);
static void update_camera_main_vstart_value(void);
static void camera_settings_callback_main(uintptr_t context);


/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

static void destroy_timer(void)
{
    if (SYS_TIME_HANDLE_INVALID != sys_time_handle)
    {
        SYS_TIME_TimerDestroy(sys_time_handle);
        sys_time_handle = SYS_TIME_HANDLE_INVALID;
    }
}

/* Camera settings on the main screen */

void show_camera_settings_dialog(void)
{
    DRV_CAMERA_OVM7692_Get_Position(sysObj.drvOVM7692, &initial_camera_hstart, &initial_camera_vstart);
    
    camera_hstart = initial_camera_hstart;
    camera_vstart = initial_camera_vstart;

    show_or_hide_camera_settings_dialog(LA_TRUE);
    
    update_camera_main_hstart_value();
    update_camera_main_vstart_value();
    
    set_pca9530_leds_on();
    power_management_suspend(true);
    
    laWidget_SetVisible((laWidget*)GroupScanStats, LA_FALSE);
    
    
}

static void update_camera_main_hstart_value(void)
{
    laString la_string;
    char value_string[10];

    /* create the string */
    sprintf(value_string, "%d", camera_hstart);
    la_string = laString_CreateFromCharBuffer(value_string, &Apertura_14);

    laLabelWidget_SetText(CameraHSTARTValueLabelWidget, la_string);
    
    /* destroy the string */
    laString_Destroy(&la_string);        
}

static void update_camera_main_vstart_value(void)
{
    laString la_string;
    char value_string[10];

    /* create the string */
    sprintf(value_string, "%d", camera_vstart);
    la_string = laString_CreateFromCharBuffer(value_string, &Apertura_14);

    laLabelWidget_SetText(CameraVSTARTValueLabelWidget, la_string);
    
    /* destroy the string */
    laString_Destroy(&la_string);        
}

static void camera_settings_callback_main(uintptr_t context)
{
    /* do nothing if the timer handle has been closed */
    if (SYS_TIME_HANDLE_INVALID == sys_time_handle)
    {
        return;
    }

    SYS_TIME_TimerDestroy(sys_time_handle);
    sys_time_handle = SYS_TIME_HANDLE_INVALID;

    /* ensure that camera_hstart is odd */
    if ((camera_hstart & 1) == 0)
    {
        camera_hstart++;
    }

    //dprintf_colour("[GREEN]camera_hstart = %d[WHITE]\r\n", camera_hstart);

    switch (context)
    {
        case H_DECREMENT:
        {
            /* don't do anything if the button is no longer pressed */
            if (laButtonWidget_GetPressed(CameraRightButtonWidget) == LA_FALSE)
            {
                break;
            }

            if (camera_hstart > CAMERA_HSTART_MINIMUM)
            {
                camera_hstart -= 2;
                update_camera_main_hstart_value();
                DRV_CAMERA_OVM7692_Set_Position(sysObj.drvOVM7692, camera_hstart, camera_vstart);

                if (camera_hstart > CAMERA_HSTART_MINIMUM)
                {
                    sys_time_handle = SYS_TIME_CallbackRegisterMS(camera_settings_callback_main, H_DECREMENT, REPEAT_DELAY, SYS_TIME_SINGLE);
                }
            }
            break;
        }

        case H_INCREMENT:
        {
            /* don't do anything if the button is no longer pressed */
            if (laButtonWidget_GetPressed(CameraLeftButtonWidget) == LA_FALSE)
            {
                break;
            }

            if (camera_hstart < CAMERA_HSTART_MAXIMUM)
            {
                camera_hstart += 2;
                update_camera_main_hstart_value();
                DRV_CAMERA_OVM7692_Set_Position(sysObj.drvOVM7692, camera_hstart, camera_vstart);

                if (camera_hstart < CAMERA_HSTART_MAXIMUM)
                {
                    sys_time_handle = SYS_TIME_CallbackRegisterMS(camera_settings_callback_main, H_INCREMENT, REPEAT_DELAY, SYS_TIME_SINGLE);
                }
            }
            break;
        }

        case V_DECREMENT:
        {
            /* don't do anything if the button is no longer pressed */
            if (laButtonWidget_GetPressed(CameraDownButtonWidget) == LA_FALSE)
            {
                break;
            }

            if (camera_vstart > CAMERA_VSTART_MINIMUM)
            {
                camera_vstart--;
                update_camera_main_vstart_value();
                DRV_CAMERA_OVM7692_Set_Position(sysObj.drvOVM7692, camera_hstart, camera_vstart);

                if (camera_vstart > CAMERA_VSTART_MINIMUM)
                {
                    sys_time_handle = SYS_TIME_CallbackRegisterMS(camera_settings_callback_main, V_DECREMENT, REPEAT_DELAY, SYS_TIME_SINGLE);
                }
            }
            break;
        }

        case V_INCREMENT:
        {
            /* don't do anything if the button is no longer pressed */
            if (laButtonWidget_GetPressed(CameraUpButtonWidget) == LA_FALSE)
            {
                break;
            }

            if (camera_vstart < CAMERA_VSTART_MAXIMUM)
            {
                camera_vstart++;
                update_camera_main_vstart_value();
                DRV_CAMERA_OVM7692_Set_Position(sysObj.drvOVM7692, camera_hstart, camera_vstart);

                if (camera_vstart < CAMERA_VSTART_MAXIMUM)
                {
                    sys_time_handle = SYS_TIME_CallbackRegisterMS(camera_settings_callback_main, V_INCREMENT, REPEAT_DELAY, SYS_TIME_SINGLE);
                }
            }
            break;
        }
    }
}

// App_CameraLeftButtonWidget - PressedEvent
void App_CameraLeftButtonWidget_PressedEvent(laButtonWidget* btn)
{
    dputs_colour("[BLUE]cameraLeftButtonWidget_PressedEvent[WHITE]\r\n");

    if (camera_hstart < CAMERA_HSTART_MAXIMUM)
    {
        camera_hstart += 2;
        update_camera_main_hstart_value();
        DRV_CAMERA_OVM7692_Set_Position(sysObj.drvOVM7692, camera_hstart, camera_vstart);

        if (camera_hstart < CAMERA_HSTART_MAXIMUM)
        {
            sys_time_handle = SYS_TIME_CallbackRegisterMS(camera_settings_callback_main, H_INCREMENT, INITIAL_REPEAT_DELAY, SYS_TIME_SINGLE);
        }
    }
}

// App_CameraLeftButtonWidget - ReleasedEvent
void App_CameraLeftButtonWidget_ReleasedEvent(laButtonWidget* btn)
{
    dputs_colour("[YELLOW]cameraLeftButtonWidget_ReleasedEvent[WHITE]\r\n");
    destroy_timer();
}

// App_CameraUpButtonWidget - PressedEvent
void App_CameraUpButtonWidget_PressedEvent(laButtonWidget* btn)
{
    dputs_colour("[BLUE]cameraUpButtonWidget_PressedEvent[WHITE]\r\n");

    if (camera_vstart < CAMERA_VSTART_MAXIMUM)
    {
        camera_vstart++;
        update_camera_main_vstart_value();
        DRV_CAMERA_OVM7692_Set_Position(sysObj.drvOVM7692, camera_hstart, camera_vstart);

        if (camera_vstart < CAMERA_VSTART_MAXIMUM)
        {
            sys_time_handle = SYS_TIME_CallbackRegisterMS(camera_settings_callback_main, V_INCREMENT, INITIAL_REPEAT_DELAY, SYS_TIME_SINGLE);
        }
    }
}

// App_CameraUpButtonWidget - ReleasedEvent
void App_CameraUpButtonWidget_ReleasedEvent(laButtonWidget* btn)
{
    dputs_colour("[YELLOW]cameraUpButtonWidget_ReleasedEvent[WHITE]\r\n");
    destroy_timer();
}

// App_CameraRightButtonWidget - PressedEvent
void App_CameraRightButtonWidget_PressedEvent(laButtonWidget* btn)
{
    dputs_colour("[BLUE]cameraRightButtonWidget_PressedEvent[WHITE]\r\n");    

    if (camera_hstart > CAMERA_HSTART_MINIMUM)
    {
        camera_hstart -= 2;
        update_camera_main_hstart_value();
        DRV_CAMERA_OVM7692_Set_Position(sysObj.drvOVM7692, camera_hstart, camera_vstart);

        if (camera_hstart > CAMERA_HSTART_MINIMUM)
        {
            sys_time_handle = SYS_TIME_CallbackRegisterMS(camera_settings_callback_main, H_DECREMENT, INITIAL_REPEAT_DELAY, SYS_TIME_SINGLE);
        }
    }
}

// App_CameraRightButtonWidget - ReleasedEvent
void App_CameraRightButtonWidget_ReleasedEvent(laButtonWidget* btn)
{
    dputs_colour("[YELLOW]cameraRightButtonWidget_ReleasedEvent[WHITE]\r\n");
    destroy_timer();
}

// App_CameraDownButtonWidget - PressedEvent
void App_CameraDownButtonWidget_PressedEvent(laButtonWidget* btn)
{
    dputs_colour("[BLUE]cameraDownButtonWidget_PressedEvent[WHITE]\r\n");

    if (camera_vstart > CAMERA_VSTART_MINIMUM)
    {
        camera_vstart--;
        update_camera_main_vstart_value();
        DRV_CAMERA_OVM7692_Set_Position(sysObj.drvOVM7692, camera_hstart, camera_vstart);

        if (camera_vstart > CAMERA_VSTART_MINIMUM)
        {
            sys_time_handle = SYS_TIME_CallbackRegisterMS(camera_settings_callback_main, V_DECREMENT, INITIAL_REPEAT_DELAY, SYS_TIME_SINGLE);
        }
    }
}

// App_CameraDownButtonWidget - ReleasedEvent
void App_CameraDownButtonWidget_ReleasedEvent(laButtonWidget* btn)
{
    dputs_colour("[YELLOW]cameraDownButtonWidget_ReleasedEvent[WHITE]\r\n");
    destroy_timer();
}

void show_or_hide_camera_settings_dialog(laBool show)
{
    laWidget_SetEnabled((laWidget*) CameraSettingsPanelWidget, show);
    laWidget_SetVisible((laWidget*) CameraSettingsPanelWidget, show);
}

// App_CameraCancelButtonWidget - PressedEvent
void App_CameraCancelButtonWidget_PressedEvent(laButtonWidget* btn)
{
    dputs_colour("[YELLOW]Camera settings Cancel button pressed[WHITE]\r\n");    

    /* restore the original settings */
    DRV_CAMERA_OVM7692_Set_Position(sysObj.drvOVM7692, initial_camera_hstart, initial_camera_vstart);

    show_or_hide_camera_settings_dialog(LA_FALSE);
    
    set_pca9530_leds_off();
    power_management_suspend(false);
    
    laWidget_SetVisible((laWidget*)GroupScanStats, LA_TRUE);
    
    app_exit_configure();
}

// App_CameraApplyButtonWidget - PressedEvent
void App_CameraApplyButtonWidget_PressedEvent(laButtonWidget* btn)
{
    dputs_colour("[YELLOW]Camera settings Apply button pressed[WHITE]\r\n");

    /* update the saved settings */
    settings_set_camera_hstart(camera_hstart);
    settings_set_camera_vstart(camera_vstart);
    save_settings();
    DRV_CAMERA_OVM7692_Set_Position(sysObj.drvOVM7692, camera_hstart, camera_vstart);

    show_or_hide_camera_settings_dialog(LA_FALSE);
    
    set_pca9530_leds_off();
    power_management_suspend(false);
    
    laWidget_SetVisible((laWidget*)GroupScanStats, LA_TRUE);
    
    app_exit_configure();
}

/* *****************************************************************************
 End of File
 */
