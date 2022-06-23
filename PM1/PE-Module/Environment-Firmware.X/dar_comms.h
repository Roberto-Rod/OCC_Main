/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    dar_comms.h

  @Summary
    Message communications between with the PIC32 DAR.

  @Description
    Message communications with the PIC32 DAR using UART1.
 */
/* ************************************************************************** */

#ifndef _DAR_COMMS_H    /* Guard against multiple inclusion */
#define _DAR_COMMS_H


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

void pic_communications_init(void);
void pic_communications_test(void);
void transmit_timer(void);

uint8_t pic_comms_queue_message(const uint8_t *data, uint32_t length, bool acknowledgment_required);
void pic_comms_task(void);

void UART1_TX_InterruptHandler(void);
void UART1_RX_InterruptHandler(void);
void UART1_FAULT_InterruptHandler(void);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DAR_COMMS_H */
