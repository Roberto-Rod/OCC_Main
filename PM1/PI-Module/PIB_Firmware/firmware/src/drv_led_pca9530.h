/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_led_pca9530.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DRV_LED_PCA9530_H    /* Guard against multiple inclusion */
#define _DRV_LED_PCA9530_H

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "definitions.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

#define DRV_LED_ON                              1
#define DRV_LED_OFF                             0

/* ************************************************************************** */
/** Descriptive Constant Name

  @Summary
    Brief one-line summary of the constant.

  @Description
    Full description, explaining the purpose and usage of the constant.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Remarks
    Any additional remarks
 */



// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

#define PCA9530_PWM_152HZ   0
#define PCA9530_PWM_76HZ    1  
#define PCA9530_PWM_50HZ    1    
#define PCA9530_PWM_38HZ    3
#define PCA9530_PWM_30HZ    4
#define PCA9530_PWM_19HZ    5    
    
// *****************************************************************************

/** Descriptive Data Type Name

  @Summary
    Brief one-line summary of the data type.

  @Description
    Full description, explaining the purpose and usage of the data type.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Remarks
    Any additional remarks
    <p>
    Describe enumeration elements and structure and union members above each 
    element or member.
 */


// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************
/**
  @Function
    int ExampleFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.

    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */

void drv_pca9530_led_controller_task(void);
void set_pca9530_led_pwm0_rate(uint8_t pcs0, uint8_t pwm0);
void set_pca9530_led_pwm1_rate(uint8_t pcs1, uint8_t pwm1);

bool drv_led_pca9530_fading_tasks(void);
void set_pca9530_leds_on(void);
void set_pca9530_leds_off(void);
bool drv_pca9530_fading_active(void);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DRV_LED_PCA9530_H */
