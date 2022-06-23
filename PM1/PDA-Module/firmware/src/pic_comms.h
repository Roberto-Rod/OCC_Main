/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    pic_comms.h

  @Summary
    Message communications between PICs.

  @Description
    Message communications between PICs.
 */
/* ************************************************************************** */

#ifndef _PIC_COMMS_H    /* Guard against multiple inclusion */
#define _PIC_COMMS_H


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

bool pic_communications_send_message(const uint8_t *data, uint32_t length, bool acknowledgement_required);
bool pic_comms_task(void);

void UART6_TX_InterruptHandler(void);
void UART5_RX_InterruptHandler(void);
void UART5_FAULT_InterruptHandler(void);

void pic_transmit_timer(void);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _PIC_COMMS_H */
