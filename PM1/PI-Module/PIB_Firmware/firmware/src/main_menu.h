/* ************************************************************************** */
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

#ifndef _MAIN_MENU_H    /* Guard against multiple inclusion */
#define _MAIN_MENU_H


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */



/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */




// *****************************************************************************
// Section: Data Types
// *****************************************************************************




// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void main_menu_init(void);
void main_menu_task(void);
void show_main_menu_button(laBool show);

void App_MenuButtonWidget_PressedEvent(laButtonWidget* btn);
void App_DeviceSettingsMenuButtonWidget_PressedEvent(laButtonWidget* btn);
void App_CameraSettingsMenuButtonWidget_PressedEvent(laButtonWidget* btn);
void App_DisplaySettingsMenuButtonWidget_PressedEvent(laButtonWidget* btn);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MAIN_MENU_H */

/* *****************************************************************************
 End of File
 */
