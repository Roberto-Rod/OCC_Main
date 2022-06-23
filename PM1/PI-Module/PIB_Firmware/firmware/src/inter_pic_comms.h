/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    inter_pic_comms.h

  @Summary
    Uses the shared FRAM to communicate with the other board.

  @Description
    PIC to PIC communications.
 */
/* ************************************************************************** */

#ifndef _INTER_PIC_COMMS_H    /* Guard against multiple inclusion */
#define _INTER_PIC_COMMS_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */



/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */




// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

void inter_pic_comms_init(void);
bool pic_comms_send_message(uint8_t *message, uint32_t length, bool *message_sent);
bool pic_comms_get_message(uint8_t *message, uint32_t *length, bool *message_received);
bool flush_received_messages(void);
bool flush_transmitted_messages(void);
bool log_receive_buffer_slots(void);
void register_new_message_callback(void (*message_received_callback_function)(void));

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _INTER_PIC_COMMS_H */
