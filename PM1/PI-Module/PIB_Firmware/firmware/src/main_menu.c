/* ************************************************************************** */

#include "gfx/libaria/inc/libaria_common.h"

/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    main_menu.c

  @Summary
    Main menu implementation.

  @Description
    Show / hide main menu.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "definitions.h"

typedef enum
{
    MENU_INIT = 0,
    MENU_IDLE,
    MENU_RESUME_CAMERA,
    MENU_OFF,
    MENU_DELAY,   
} MENU_STATE;

typedef enum
{
    DEVICE_SETUP,
    CAMERA_SETUP,
    DISPLAY_SETUP
} MENU_ITEM;

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

static bool menu_visible;

static MENU_STATE menu_state = MENU_INIT;
static SYS_TIME_HANDLE delay_handle;
static MENU_ITEM item_selected;

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

static void show_main_menu(laBool show);
static void process_option(MENU_ITEM item);
static void menu_item_pressed(MENU_ITEM item);

/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

void main_menu_init(void)
{
    menu_visible = false;
    show_main_menu(LA_FALSE);
    menu_state = MENU_IDLE;
    delay_handle = SYS_TIME_HANDLE_INVALID;
}

// main menu task called in main task loop
void main_menu_task(void)
{                
    switch (menu_state)
    {
        case MENU_INIT:
        {
            main_menu_init();
            break;
        }
        case MENU_IDLE:
        {
            break;
        }
        case MENU_RESUME_CAMERA:
        {
            if (SYS_TIME_DelayIsComplete(delay_handle))
            {
                delay_handle = SYS_TIME_HANDLE_INVALID;
                menu_state = MENU_IDLE;
#ifdef PAUSE_CAMERA        
                DRV_CAMERA_OVM7692_Resume(sysObj.drvOVM7692); 
#endif      
            }
            break;
        }
        case MENU_DELAY:
        {
            if (SYS_TIME_DelayIsComplete(delay_handle))
            {
                delay_handle = SYS_TIME_HANDLE_INVALID;
                menu_visible = false;
                show_main_menu(menu_visible);
                menu_state = MENU_IDLE;
                process_option(item_selected);
            }
            break;
        }
        case MENU_OFF:
            menu_state = MENU_IDLE;
            break;
        default:
            break;
    }
}

// execute the selected menu option
static void process_option(MENU_ITEM item)
{
    switch (item)
    {
        case DEVICE_SETUP:
        {
            app_begin_configure(APP_SCREEN_DEVICE_SETUP);
            break;
        }
        case CAMERA_SETUP:
        {
            app_begin_configure(APP_SCREEN_CAMERA_SETUP);
            break;
        }
        case DISPLAY_SETUP:
        {
            app_begin_configure(APP_SCREEN_DISPLAY_SETUP);
            break;
        }   
        
        default:
            break;
    }
}

// show / hide main menu
static void show_main_menu(laBool show)
{
    laWidget_SetVisible((laWidget *) MenuPanelWidget, show);  
    dprintf_colour("[WHITE]Show main menu %d[WHITE]\r\n", show);
}

// menuButtonWidget - PressedEvent
void App_MenuButtonWidget_PressedEvent(laButtonWidget* btn)
{
    if(device_settings.MENU_LOCKED != 0){
        return;
    }
    
    menu_visible = !menu_visible;
    show_main_menu(menu_visible);

    /* make sure that none of the buttons is pressed when the menu is shown */
    if (menu_visible)
    {
        laButtonWidget_SetPressed(DeviceSettingsMenuButtonWidget, LA_FALSE);
        laButtonWidget_SetPressed(CameraSettingsMenuButtonWidget, LA_FALSE);        
    }
}

// process a pressed menu option
static void menu_item_pressed(MENU_ITEM item)
{
    /* a delay allows the button animation to be seen */
    menu_state = MENU_DELAY;
    SYS_TIME_DelayMS(200, &delay_handle);
    item_selected = item;
}

// App_DeviceSettingsMenuButtonWidget - PressedEvent
void App_DeviceSettingsMenuButtonWidget_PressedEvent(laButtonWidget* btn)
{
    menu_item_pressed(DEVICE_SETUP);
}

// App_CameraSettingsMenuButtonWidget - PressedEvent
void App_CameraSettingsMenuButtonWidget_PressedEvent(laButtonWidget* btn)
{
    menu_item_pressed(CAMERA_SETUP);
}

// App_DisplaySettingsMenuButtonWidget - PressedEvent
void App_DisplaySettingsMenuButtonWidget_PressedEvent(laButtonWidget* btn)
{
    menu_item_pressed(DISPLAY_SETUP);
}

/* *****************************************************************************
 End of File
 */
