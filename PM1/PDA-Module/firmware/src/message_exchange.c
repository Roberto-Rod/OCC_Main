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

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include <string.h>
#include "definitions.h"
#include "message_exchange.h"
#include "dspic_comms.h"
#include "drv_lsc.h"

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

/* PI and PIC comms defines */
//Incoming messages
#define PDAB_IS_SHUTDOWN_SAFE_MESSAGE_BODY_LENGTH 0

/* DSPIC and PIC comms defines */
//Outgoing messages
/** @brief define macro holding PDAB_LSC_COMMAND_IS_SHUTDOWN_SAFE message header */
#define PDAB_LSC_IS_SHUTDOWN_SAFE_MESSAGE_HEADER "PDAB_IS_SHUTDOWN_SAFE"
/** @brief define macro holding length of PDAB_LSC_COMMAND_IS_SHUTDOWN_SAFE message */
#define PDAB_LSC_COMMAND_IS_SHUTDOWN_SAFE_MESSAGE_LENGTH    0

#define PDAB_LSC_RESET_MESSAGE_HEADER "PDAB_COMMAND_REQUEST_RESET"

#define PDAB_LSC_RESET_MESSAGE_LENGTH 0

/** @brief define macro holding GET_LSC_STATUS message header */
#define PDAB_GET_LSC_STATUS_MESSAGE_HEADER "PDAB_COMMAND_REQUEST_STATUS"
/** @brief define macro holding length of GET_LSC_STATUS message */
#define PDAB_GET_LSC_STATUS_MESSAGE_LENGTH              0
/** @brief define macro holding GET_LSC_VERSION message header */
#define PDAB_GET_LSC_VERSION_MESSAGE_HEADER "PDAB_COMMAND_REQUEST_VERSION"
/** @brief define macro holding length of GET_LSC_VERSION message */
#define PDAB_GET_LSC_VERSION_MESSAGE_LENGTH             0
/** @brief define macro holding REQUEST_DEFINE_LIMITS message header */
#define PDAB_REQUEST_DEFINE_LIMITS_MESSAGE_HEADER "PDAB_COMMAND_REQUEST_DEFINE_LIMITS"
/** @brief define macro holding length of REQUEST_DEFINE_LIMITS message */
#define PDAB_REQUEST_LSC_DEFINE_LIMITS_MESSAGE_LENGTH             0
/** @brief define macro holding REQUEST_START_SCANNING message header */
#define PDAB_REQUEST_START_SCANNING_MESSAGE_HEADER "PDAB_COMMAND_REQUEST_START_SCANNING"
/** @brief define macro holding length of REQUEST_START_SCANNING message */
#define PDAB_REQUEST_LSC_START_SCANNING_MESSAGE_LENGTH   0
/** @brief define macro holding REQUEST_STOP_SCANNING message header */
#define PDAB_REQUEST_STOP_SCANNING_MESSAGE_HEADER "PDAB_COMMAND_REQUEST_STOP_SCANNING"
/** @brief define macro holding length of REQUEST_STOP_SCANNING message */
#define PDAB_REQUEST_LSC_STOP_SCANNING_MESSAGE_LENGTH   0
/** @brief define macro holding REQUEST_RESET message header */
#define PDAB_REQUEST_REQUEST_RESET_MESSAGE_HEADER "PDAB_COMMAND_REQUEST_RESET"
/** @brief define macro holding length of REQUEST_REQUEST_RESET message */
#define PDAB_REQUEST_LSC_REQUEST_RESET_MESSAGE_LENGTH   0

//Incoming messages
/** @brief define macro holding length of LSC_VERSION message body */
#define LSC_VERSION_MESSAGE_BODY_LENGTH            2
/** @brief define macro holding length of LSC_STATUS message */
#define LSC_STATUS_MESSAGE_BODY_LENGTH             28
/** @brief define macro holding length of LSC_REQUEST_SHUTDOWN message */
#define LSC_REQUEST_SHUTDOWN_MESSAGE_HEADER_LENGTH             0
/** @brief define macro holding length of LSC_REQUEST_SHUTDOWN message body */
#define LSC_REQUEST_SHUTDOWN_MESSAGE_BODY_LENGTH    0


/** @brief define macro holding maximum length of the command buffer */
#define MAX_COMMAND_LENGTH                      128
/** @brief define macro holding maximum value of the wakeup timer */
#define WAKEUP_TIMEOUT                          1000
/** @brief timer holding current value of the wakeup timer */

static unsigned int timer_miliseconds = WAKEUP_TIMEOUT;

extern PDAB_DATA pdabData;

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
static uint8_t bit_to_index(uint8_t);

static uint8_t bit_to_index(uint8_t bit)
{
    uint8_t index;

    index = 0;
    while (bit > 0)
    {
        bit >>= 1;
        index++;
    }

    return (index);
}

/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

// PDAB <-> PIB functions

void pdab_send_command_to_PIB(PDAB_RESPONSE command, uint8_t *data, uint16_t data_length)
{
    uint32_t command_length = 0;
    static uint8_t command_buffer[MAX_COMMAND_LENGTH];

 

    /* do nothing if the command is not valid */
    if ((NULL == command))
    {
        return;
    }

 

    /* send command */
    if (0 == data_length)
    {
        /* same as before to minimise chance of adding a bug */
        
        command_buffer[0] = (uint8_t)command;
        command_length++;
        pic_communications_send_message((uint8_t *) command_buffer, command_length, true);  // requires ACK
    }
    else
    {
        /* command with data separated by a colon */
        command_buffer[0] = (uint8_t)command;
        command_length++;
        
        command_buffer[command_length] = ':';
        command_length++;
        memcpy(&command_buffer[command_length], data, data_length);
        command_length += data_length;
        pic_communications_send_message((uint8_t *) command_buffer, command_length, true);  // requires ACK
    }

 

    dprintf_colour("[YELLOW]Command [%d] sent to PIB[WHITE]\r\n", command_buffer[0]);
}

/* ************************************************************************** */
/**
 * @brief            Processes is_safe_to_shutdown answer message to PIB.
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
/// TO DO add here check of lsc and then send it is safe to shytdown
void process_pdab_is_safe_to_shutdown_message(uint8_t *message, int32_t length)
{
    if(pdabData.usb_software == USB_SOFTWARE_VCT){
        //if the verification & calibration rig is connected and active do not let PI to shutdown the device
        return;
    }
    
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[BROWN]Processing PDAB_IS_SHUTDOWN_SAFE message. Length: %d[WHITE]\r\n", length);
    #endif
    if (length != PDAB_IS_SHUTDOWN_SAFE_MESSAGE_BODY_LENGTH)
    {
        dputs_colour("[RED]Invalid length for IS_SHUTDOWN_SAFE[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PDAB_IS_SHUTDOWN_SAFE_MESSAGE_BODY_LENGTH);
        return;
    }
    // pdab_send_command_to_PIB(PDAB_PIB_REQUEST_SHUTDOWN, NULL, 0);
    pdabData.power_off_busy = true; // after this message PDAB needs to stay awake to receive messages form LSC
    drv_lsc_is_shutdown_safe();
}

// PDAB <-> LSC functions


/* ************************************************************************** */
/**
 * @brief            Processes is_safe_to_shutdown answer message to PIB.
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void process_lsc_request_shutdown_message(uint8_t *message, int32_t length)
{
    //#ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[BROWN]Processing LSC_Request_Shutdown message.");
    //#endif
    if (length != LSC_REQUEST_SHUTDOWN_MESSAGE_BODY_LENGTH)
    {
        dputs_colour("[RED]Invalid length for LSC_REQUEST_SHUTDOWN[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", LSC_REQUEST_SHUTDOWN_MESSAGE_BODY_LENGTH);
        return;
    }
    pdab_send_command_to_PIB(RESPONSE_REQUEST_SHUTDOWN, NULL, 0);

}

/* ************************************************************************** */
/**
 * @brief            Handles timer interrupt. Gets executed every 1ms.
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void message_exchange_millisecond_timer_interrupt(void)
{
    if(timer_miliseconds < WAKEUP_TIMEOUT)
    {
        timer_miliseconds++;
    }
}

/* ************************************************************************** */
/**
 * @brief            Sends command via UART.
 *
 * @param[in]        command Command to send
 * @param[in]        data Data to send
 * @param[in]        data_length Length of the data to send
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void pdab_send_command_to_LSC(PDAB_LSC_COMMANDS command, uint8_t *data, uint16_t data_length)
{
    const char *command_strings[] = {   PDAB_GET_LSC_STATUS_MESSAGE_HEADER,
                                        PDAB_GET_LSC_VERSION_MESSAGE_HEADER,
                                        PDAB_REQUEST_DEFINE_LIMITS_MESSAGE_HEADER,
                                        PDAB_REQUEST_START_SCANNING_MESSAGE_HEADER,
                                        PDAB_REQUEST_STOP_SCANNING_MESSAGE_HEADER,
                                        PDAB_LSC_IS_SHUTDOWN_SAFE_MESSAGE_HEADER,
                                        PDAB_LSC_RESET_MESSAGE_HEADER};
    const char *command_string;
    uint32_t command_length;
    static uint8_t command_buffer[MAX_COMMAND_LENGTH];
    /* do nothing if the command is not valid */
    if ((GET_LSC_STATUS != command) && (GET_LSC_VERSION != command)  && (REQUEST_DEFINE_LIMITS != command) && (REQUEST_START_SCANNING != command) && (REQUEST_STOP_SCANNING!= command) && (PDAB_LSC_COMMAND_IS_SHUTDOWN_SAFE != command) && (REQUEST_RESET!= command))
    {
        return;
    }
    /* send command */
    if (0 == data_length)
    {
        /* same as before to minimise chance of adding a bug */
        command_string = command_strings[bit_to_index(command) - 1];
        command_length = strlen(command_string);
        dspic_pic_comms_queue_message((uint8_t *) command_string, command_length, true);  // requires ACK
    }
    else
    {
        /* command with data separated by a colon */
        /* copy the command to a memory buffer, and then append a colon and the data */
        command_string = command_strings[bit_to_index(command) - 1];
        command_length = strlen(command_string);
        memcpy(command_buffer, command_string, command_length);
        command_buffer[command_length] = ':';
        command_length++;
        memcpy(&command_buffer[command_length], data, data_length);
        command_length += data_length;
        dspic_pic_comms_queue_message((uint8_t *) command_buffer, command_length, true);  // requires ACK
    }
    #ifdef DEBUG_MESSAGE_EXCHANGE
        dprintf_colour("[YELLOW]LSC: Command [%s] sent[WHITE]\r\n", command_string);
    #endif
}
/* ************************************************************************** */
/**
 * @brief            Processes LSC_VERSION message. This function checks if
 *                   length of the LSC_VERSION message is correct.
 *
 * @param[in]        message Message received with the GET_LSC_VERSION command
 * @param[in]        length Length of the message received
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
//temporary debug functionality - print the version //todo

void process_lsc_version_message(uint8_t *message, int32_t length)
{
    //#ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[BROWN] Process lsc version [WHITE]\r\n");
    //#endif
    if (length != LSC_VERSION_MESSAGE_BODY_LENGTH)
    {
        dputs_colour("[RED]Invalid length for LSC_VERSION [WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", LSC_VERSION_MESSAGE_BODY_LENGTH);
        dprintf_colour("[RED]The length is: %d[WHITE]\r\n", length);
        return;
    }
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[RED]LSC version %s[WHITE]\r\n", message);
    #endif
    //TODO: get memcpy working - copy the version

}
/* ************************************************************************** */
/**
 * @brief            Processes LSC_STATUS message. This function checks if
 *                   length of the LSC_STATUS message is correct.
 *
 * @param[in]        message Message received with the LSC_STATUS command
 * @param[in]        length Length of the message received
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void process_lsc_status_message(uint8_t *message, int32_t length)
{
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[BROWN]Processing LSC status [WHITE]\r\n");
    #endif
    if (length != LSC_STATUS_MESSAGE_BODY_LENGTH)
    {
        dputs_colour("[RED]Invalid length for LSC_STATUS [WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", LSC_STATUS_MESSAGE_BODY_LENGTH);
        dprintf_colour("[RED]The length is: %d[WHITE]\r\n", length);
        return;
    }

    read_lsc_status( message);
}
/* ************************************************************************** */
/**
 * @brief            Sends get software version to LSC.
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void send_get_LSC_version_message(void)
{
    pdab_send_command_to_LSC(GET_LSC_VERSION, NULL, PDAB_GET_LSC_VERSION_MESSAGE_LENGTH);
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[RED] Call send_get_LSC_version_message[WHITE]\r\n");
    #endif
}
/* ************************************************************************** */
/**
 * @brief            Sends get LSC status.
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void send_get_LSC_status_message(void)
{
    pdab_send_command_to_LSC(GET_LSC_STATUS, NULL, PDAB_GET_LSC_STATUS_MESSAGE_LENGTH);
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[RED] Call send_get_LSC_status_message[WHITE]\r\n");
    #endif
}
/* ************************************************************************** */
/**
 * @brief            Sends request LSC define limits.
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void send_request_LSC_define_limits_message(void)
{
    pdab_send_command_to_LSC(REQUEST_DEFINE_LIMITS, NULL, PDAB_REQUEST_LSC_DEFINE_LIMITS_MESSAGE_LENGTH);
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[RED] Call send_request_LSC_define_limits_message[WHITE]\r\n");
    #endif
}
/* ************************************************************************** */
/**
 * @brief            Sends request LSC start scanning.
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void send_request_LSC_start_scanning_message(void)
{
    pdab_send_command_to_LSC(REQUEST_START_SCANNING, NULL, PDAB_REQUEST_LSC_START_SCANNING_MESSAGE_LENGTH);
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[RED] Call send_request_LSC_start_scanning_message[WHITE]\r\n");
    #endif
}
/* ************************************************************************** */
/**
 * @brief            Sends request LSC stop scanning.
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void send_request_LSC_stop_scanning_message(void)
{
    pdab_send_command_to_LSC(REQUEST_STOP_SCANNING, NULL, PDAB_REQUEST_LSC_STOP_SCANNING_MESSAGE_LENGTH);
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[RED] Call send_request_LSC_stop_scanning_message[WHITE]\r\n");
    #endif
}
/* ************************************************************************** */
/**
 * @brief            Sends command to LSC is shutdown safe.
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void send_command_LSC_is_shutdown_safe_message(void)
{
    pdab_send_command_to_LSC(PDAB_LSC_COMMAND_IS_SHUTDOWN_SAFE, NULL, PDAB_LSC_COMMAND_IS_SHUTDOWN_SAFE_MESSAGE_LENGTH);
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[RED] Call send_command_LSC_is_shutdown_safe_message[WHITE]\r\n");
    #endif
}
/* ************************************************************************** */
/**
 * @brief            Sends request LSC reset.
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void send_request_reset_message(void)
{
    pdab_send_command_to_LSC(REQUEST_RESET, NULL, PDAB_REQUEST_LSC_REQUEST_RESET_MESSAGE_LENGTH);
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[RED] Call send_request_LSC_reset [WHITE]\r\n");
    #endif
}
