/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    message_exchange.h

  @Summary
    Exchange messages with the data acquisition board.

  @Description
    Sends commands to the data acquisition board and receives messages back.
 */
/* ************************************************************************** */

#ifndef _MESSAGE_EXCHANGE_H    /* Guard against multiple inclusion */
#define _MESSAGE_EXCHANGE_H

#define NO_DEBUG_COMMS

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "dar_comms.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */

typedef enum
{
    PIC24_WAKEUP = 1,
    PIC24_STATUS = 2,
    PIC24_VERSION = 4,
    PIC24_IS_SHUDTOWN_SAFE = 8
} PIC24_COMMAND;

// *****************************************************************************
// Section: Data Types
// *****************************************************************************

// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void message_exchange_millisecond_timer_interrupt(void);
void send_command(PIC24_COMMAND, uint8_t*, uint16_t);
void process_get_status_message(uint8_t*, int32_t);
void process_set_time_date_message(uint8_t*, int32_t);
void process_power_down_message(uint8_t*, int32_t);
void process_request_version_message(uint8_t*, int32_t);
void process_reset_error_message(uint8_t *message, int32_t length); 
void process_reset_message(uint8_t *message, int32_t length); 
void process_reset_temp_message(uint8_t *message, int32_t length);
void send_is_shutdown_safe_message(void);
void send_wakeup_message(void);
void wakeup_task(void);
void wakeup_dar(void);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MESSAGE_EXCHANGE_H */
