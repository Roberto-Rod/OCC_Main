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


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "pdab_comms.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */

typedef enum
{
    LSC_VERSION = 1,
    LSC_STATUS = 2,
    LSC_REQUEST_SHUTDOWN = 4,
} LSC_COMMAND;

typedef enum
{
    GET_LSC_STATUS = 1,
    GET_LSC_VERSION = 2,
    REQUEST_DEFINE_LIMITS = 4,
    REQUEST_START_SCANNING = 8,
    REQUEST_STOP_SCANNING = 16,        
    LSC_IS_SHUDTOWN_SAFE = 32,
} PDAB_COMMAND;

// *****************************************************************************
// Section: Data Types
// *****************************************************************************

// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
uint16_t SYS_version(void);
void message_exchange_millisecond_timer_interrupt(void);
void send_command(LSC_COMMAND, uint8_t*, uint16_t);
void process_request_status_message(uint8_t*, int32_t);
void process_request_version_message(uint8_t*, int32_t);
void process_request_define_limits_message(uint8_t *message, int32_t length);
void process_request_start_scanning_message(uint8_t *message, int32_t length);
void process_request_stop_scanning_message(uint8_t *message, int32_t length);
void deb_send_get_LSC_version_message(void);
void process_PDAB_is_safe_to_shutdown_message(uint8_t *message, int32_t length);
void process_pdab_request_reset_message(uint8_t *message, int32_t length);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MESSAGE_EXCHANGE_H */
