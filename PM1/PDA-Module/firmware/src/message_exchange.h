/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    message_exchange.c

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

typedef enum
{ 
    GET_LSC_STATUS = 1,
    GET_LSC_VERSION = 2,
    REQUEST_DEFINE_LIMITS = 4,
    REQUEST_START_SCANNING = 8,
    REQUEST_STOP_SCANNING = 16,    
    PDAB_LSC_COMMAND_IS_SHUTDOWN_SAFE = 32,
    REQUEST_RESET = 64,
} PDAB_LSC_COMMANDS;

typedef enum
{
    LSC_VERSION = 1,
    LSC_STATUS = 2,
    LSC_REQUEST_SHUTDOWN = 4,
} LSC_PDAB_COMMAND;


// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void process_pdab_is_safe_to_shutdown_message(uint8_t*, int32_t);
void pdab_send_command_to_PIB(PDAB_RESPONSE, uint8_t*, uint16_t);
void pdab_send_command_to_LSC(PDAB_LSC_COMMANDS, uint8_t*, uint16_t);
void send_get_LSC_version_message(void);
void send_get_LSC_status_message(void);
void send_request_LSC_define_limits_message(void);
void send_request_LSC_start_scanning_message(void);
void send_request_LSC_stop_scanning_message(void);
void send_command_LSC_is_shutdown_safe_message(void);
void process_lsc_version_message(uint8_t *message, int32_t length);
void process_lsc_status_message(uint8_t *message, int32_t length);
void process_lsc_request_shutdown_message(uint8_t *message, int32_t length);
void send_request_reset_message(void);
/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MESSAGE_EXCHANGE_H */
