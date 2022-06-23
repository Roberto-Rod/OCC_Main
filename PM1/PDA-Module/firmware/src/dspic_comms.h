/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    dspic_comms.h

  @Summary
    Message communications between with the dspic DAR.

  @Description
    Message communications with the PIC32 dspic using UART2.
 */
/* ************************************************************************** */

#ifndef _DSPIC_COMMS_H    /* Guard against multiple inclusion */
#define _DSPIC_COMMS_H


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

void dspic_pic_communications_init(void);
void dspic_communications_test(void);
void dspic_transmit_timer(void);

bool dspic_pic_comms_queue_message(const uint8_t *data, uint32_t length, bool acknowledgment_required);
bool dspic_pic_comms_task(void);

void UART2_TX_InterruptHandler(void);
void UART2_RX_InterruptHandler(void);
void UART2_FAULT_InterruptHandler(void);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DAR_COMMS_H */

