/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    dar_comms.h

  @Summary
    Message communications between with the LSC and PDAB header file.

  @Description
    Message communications with the PIC32 EFH using UART2.
 */
/* ************************************************************************** */

#ifndef _PDAB_COMMS_H    /* Guard against multiple inclusion */
#define _PDAB_COMMS_H 


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
//#define DAR_COMMS_TEST

// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void pic_communications_init(void);
void pic_communications_test(void);
void transmit_timer(void);

bool pic_comms_queue_message(const uint8_t *data, uint32_t length, bool acknowledgment_required);
bool pic_comms_task(void);

void UART2_TX_InterruptHandler(void);
void UART2_RX_InterruptHandler(void);
void UART2_FAULT_InterruptHandler(void);


/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif	/* _PDAB_COMMS_H */

