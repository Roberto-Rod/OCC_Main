/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    pic24_comms.h

  @Summary
    Message communications between with the PIC24.

  @Description
    Message communications with the environment controller using UART5.
 */
/* ************************************************************************** */

#ifndef _PIC24_COMMS_H    /* Guard against multiple inclusion */
#define _PIC24_COMMS_H


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

void pic24_communications_init(void);
void pic24_communications_test(void);

bool pic24_comms_queue_message(const uint8_t *data, uint32_t length, bool acknowledgement_required);
void pic24_comms_task(void);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _PIC24_COMMS_H */
