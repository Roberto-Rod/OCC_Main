/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_display_ST7701S.h

  @Summary
    Driver for the ST7701 LCD drive.

  @Description
    Initialises the ST7701 LCD drive chip.
 */
/* ************************************************************************** */

#ifndef _DRV_DISPLAY_ST7701_H    /* Guard against multiple inclusion */
#define _DRV_DISPLAY_ST7701_H


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

void ST7701S_Init(void);
void drv_display_set_enable(void);
void drv_display_set_disable(void);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DRV_DISPLAY_ST7701_H */

/* *****************************************************************************
 End of File
 */
