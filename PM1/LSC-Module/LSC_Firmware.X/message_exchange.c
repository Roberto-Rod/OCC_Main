/* ************************************************************************** */
/** @file message_exchange.c
 *
 *  @brief Library to handle UART comms.
 *
 *  @copyright Occuity Limited (c) 2021
 */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include <string.h>

#include "debug.h"
#include "main.h"
#include "LRS_tuning.h"
#include "message_exchange.h"
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

/** @brief LSC data object defining set LSC parameters and firmware */
extern volatile _LSC_DATA lscData;
extern volatile _LSC_TUNING_OBJ lsc_tuning;

//Incoming messages
/** @brief define macro holding length of GET_LSC_STATUS message */
#define PDAB_GET_LSC_STATUS_MESSAGE_LENGTH         0
/** @brief define macro holding length GET_LSC_VERSION message */
#define PDAB_GET_LSC_VERSION_MESSAGE_LENGTH            0
/** @brief define macro holding length of REQUEST_START_SCANNING message */
#define PDAB_REQUEST_LSC_START_SCANNING_MESSAGE_LENGTH   0
/** @brief define macro holding length of REQUEST_STOP_SCANNING message */
#define PDAB_REQUEST_LSC_STOP_SCANNING_MESSAGE_LENGTH   0
/** @brief define macro holding length of REQUEST_DEFINE_LIMITS message */
#define PDAB_REQUEST_LSC_DEFINE_LIMITS_MESSAGE_LENGTH   0
/** @brief define macro holding length of LSC_IS_SHUDTOWN_SAFE message */
#define PDAB_IS_SAFE_TO_SHUTDOWN_MESSAGE_BODY_LENGTH  0
/** @brief define macro holding length of PDAB_COMMAND_REQUEST_RESET message */
#define PDAB_RESET_REQUEST_MESSAGE_BODY_LENGTH  0

//Outgoing messages
/** @brief define macro holding LSC Version message header */
#define LSC_VERSION_MESSAGE_HEADER            "LSC Version"
/** @brief define macro holding LSC Status message header */
#define LSC_STATUS_MESSAGE_HEADER             "LSC Status"
/** @brief define macro holding LSC Status message header */
#define LSC_REQUEST_SHUTDOWN_HEADER           "LSC_Request_Shutdown"

/** @brief define macro holding maximum length of the command buffer */
#define MAX_COMMAND_LENGTH                      128
/** @brief define macro holding maximum value of the wakeup timer */
#define WAKEUP_TIMEOUT                          1000
/** @brief timer holding current value of the wakeup timer */
static unsigned int timer_miliseconds = WAKEUP_TIMEOUT;

/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */
static uint8_t bit_to_index(uint8_t bit);
/* ************************************************************************** */
/** 
 * @brief            Converts bit in PDAB_COMMAND to index.
 *
 * @note             Called by send_command to translate enum PDAB_command to 
 *                   index in an array of commands.
 *
 * @return           None.
 */
/* ************************************************************************** */
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
/* Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
/** 
 * @brief            Get system version.
 *
 * @note             Called by void process_request_version_message(uint8_t *message, int32_t length)
 *
 * @return           None.
 */
/* ************************************************************************** */
uint16_t SYS_version(void)
{
    uint16_t version = VERSION;
    return version;
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
void send_command(LSC_COMMAND command, uint8_t *data, uint16_t data_length)
{
    const char *command_strings[] = {LSC_VERSION_MESSAGE_HEADER,
                                     LSC_STATUS_MESSAGE_HEADER,
                                     LSC_REQUEST_SHUTDOWN_HEADER};
    const char *command_string;
    uint32_t command_length;
    static uint8_t command_buffer[MAX_COMMAND_LENGTH];

    /* do nothing if the command is not valid */
    if ((LSC_VERSION  != command) && (LSC_STATUS != command) &&  ( LSC_REQUEST_SHUTDOWN != command) )
    {
        return;
    }
 //   dprintf_colour("[YELLOW]Command [%d] / sent [%d][WHITE]\r\n", command, LSC_STATUS);
 //   dprintf_colour("[YELLOW]Data lenght [%d] [WHITE]\r\n", data_length);
    /* send command */
    if (0 == data_length)
    {
        /* same as before to minimise chance of adding a bug */
        command_string = command_strings[bit_to_index(command) - 1];
        command_length = strlen(command_string);
        #ifdef DEBUG_MESSAGE_EXCHANGE_FULL
        dprintf_colour("[YELLOW] command_strings  length [%d] [WHITE]\r\n",(uint16_t)command_length );
        #endif
        pic_comms_queue_message((uint8_t *) command_string, command_length, true);  // requires ACK
    }
    else
    {
        /* command with data separated by a colon */
        /* copy the command to a memory buffer, and then append a colon and the data */
        command_string = command_strings[bit_to_index(command) - 1];
        command_length = strlen(command_string);
        #ifdef DEBUG_MESSAGE_EXCHANGE_FULL
        dprintf_colour("[YELLOW] command_strings  length [%d] [WHITE]\r\n", (uint16_t)command_length );
        #endif
        memcpy(command_buffer, command_string, command_length);
        command_buffer[command_length] = ':';
        command_length++;
        memcpy(&command_buffer[command_length], data, data_length);
        command_length += data_length;
        pic_comms_queue_message((uint8_t *) command_buffer, command_length, true);  // requires ACK      
//        dprintf_colour("[YELLOW] command_strings [%s] [WHITE]\r\n", command_strings[bit_to_index(command) - 1] );
//        dprintf_colour("[YELLOW] command_strings  length [%d] [WHITE]\r\n",(uint16_t)command_length );
    }
   #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[YELLOW]Command [%s] sent[WHITE]\r\n", command_string);
    #endif
}
/* ************************************************************************** */
/** 
 * @brief            Processes GET_STATUS message. This function checks if 
 *                   length of the GET_STATUS message is correct, updates LSC
 *                   status with LSC parameters to PDAB.
 * 
 * @param[in]        message Message received with the GET_STATUS command
 * @param[in]        length Length of the message received
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */

void process_request_status_message(uint8_t *message, int32_t length)
{
    LSC_STATUS_t status;

    if (length != PDAB_GET_LSC_STATUS_MESSAGE_LENGTH )
    {
        dputs_colour("[RED]Invalid length for GET_STATUS[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PDAB_GET_LSC_STATUS_MESSAGE_LENGTH);
        dprintf_colour("[RED]The length is: %d[WHITE]\r\n", length);
        return;
    }
    //#ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[BROWN]Responding with status packet[WHITE]\r\n");
    //#endif
      
    status = update_lsc_status_data();
    send_command(LSC_STATUS, (uint8_t *) &status, sizeof(LSC_STATUS_t));
}
/* ************************************************************************** */
/** 
 * @brief            Processes REQUEST_VERSION message. This function checks if 
 *                   length of the REQUEST_VERSION message is correct, and if
 *                   so responds to PDAB with the version of the LSC software.
 * 
 * @param[in]        message Message received with the GET_STATUS command
 * @param[in]        length Length of the message received
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void process_request_version_message(uint8_t *message, int32_t length)
{   
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[BROWN]Sending LSC version[WHITE]\r\n");
    #endif
    if (length != PDAB_GET_LSC_VERSION_MESSAGE_LENGTH)
    {
        dputs_colour("[RED]Invalid length for REQUEST_VERSION[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PDAB_GET_LSC_VERSION_MESSAGE_LENGTH);
        dprintf_colour("[RED]The length is: %d[WHITE]\r\n", length);
        return;
    }

    uint16_t version = SYS_version();
    send_command(LSC_VERSION, (uint8_t *) &version, sizeof(uint16_t));
}
/* ************************************************************************** */
/** 
 * @brief            Processes REQUEST_DEFINE_LIMITS message. This function checks if 
 *                   length of the REQUEST_DEFINE_LIMITS message is correct, and if
 *                   so start define limits.
 * 
 * @param[in]        message Message received with the REQUEST_DEFINE_LIMITS command
 * @param[in]        length Length of the message received
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void process_request_define_limits_message(uint8_t *message, int32_t length)
{    
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[BROWN]Received cmd Start Define limits [WHITE]\r\n");
    #endif
    if (length != PDAB_REQUEST_LSC_DEFINE_LIMITS_MESSAGE_LENGTH)
    {
        dputs_colour("[RED]Invalid length for REQUEST_DEFINE_LIMITS[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PDAB_REQUEST_LSC_DEFINE_LIMITS_MESSAGE_LENGTH);
        dprintf_colour("[RED]The length is: %d[WHITE]\r\n", length);
        return;
    }
    lscData.StatusFlags.DLIM = true;
}
/* ************************************************************************** */
/** 
 * @brief            Processes REQUEST_START_SCANNING message. This function checks if 
 *                   length of the REQUEST_START_SCANNING  message is correct, and if
 *                   so start scanning.
 * 
 * @param[in]        message Message received with the REQUEST_START_SCANNING command
 * @param[in]        length Length of the message received
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void process_request_start_scanning_message(uint8_t *message, int32_t length)
{   
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[BROWN]Received cmd Start Scanning [WHITE]\r\n");
    #endif
    if (length != PDAB_REQUEST_LSC_START_SCANNING_MESSAGE_LENGTH)
    {
        dputs_colour("[RED]Invalid length for REQUEST_START_SCANNING[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PDAB_REQUEST_LSC_START_SCANNING_MESSAGE_LENGTH);
        dprintf_colour("[RED]The length is: %d[WHITE]\r\n", length);
        return;
    }
    lscData.StatusFlags.START = true;
}
/* ************************************************************************** */
/** 
 * @brief            Processes REQUEST_STOP_SCANNING message. This function checks if 
 *                   length of the REQUEST_STOP_SCANNING  message is correct, and if
 *                   so stop scanning.
 * 
 * @param[in]        message Message received with the REQUEST_STOP_SCANNING command
 * @param[in]        length Length of the message received
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void process_request_stop_scanning_message(uint8_t *message, int32_t length)
{   
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[BROWN]Received cmd Stop Scanning [WHITE]\r\n");
    #endif
    if (length != PDAB_REQUEST_LSC_STOP_SCANNING_MESSAGE_LENGTH)
    {
        dputs_colour("[RED]Invalid length for REQUEST_STOP_SCANNING[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PDAB_REQUEST_LSC_STOP_SCANNING_MESSAGE_LENGTH);
        dprintf_colour("[RED]The length is: %d[WHITE]\r\n", length);
        return;
    }
    lscData.StatusFlags.STOP = true;
}
/* ************************************************************************** */
/** 
 * @brief            send power down request message to PDAB    
 *
 * @note             Set shutdown flag to prevent writing to NVM.
 *
 * @return           None.
 */
/* ************************************************************************** */
void send_power_down_request(void)
{
    lscData.StatusFlags.ROFF = true;
    send_command(LSC_REQUEST_SHUTDOWN, NULL, 0);
}
/* ************************************************************************** */
/** 
 * @brief            Processes is_safe_to_shutdown answer message to PDAB.      
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void process_PDAB_is_safe_to_shutdown_message(uint8_t *message, int32_t length)
{
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[BROWN]Processing PDAB is safe to shutdown query. Length: %d[WHITE]\r\n", length);
    #endif
    if (length != PDAB_IS_SAFE_TO_SHUTDOWN_MESSAGE_BODY_LENGTH)
    {
        dputs_colour("[RED]Invalid length for PDAB_IS_SHUTDWN_SAFE[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PDAB_IS_SAFE_TO_SHUTDOWN_MESSAGE_BODY_LENGTH);
        return;
    }

    send_power_down_request();
}
/* ************************************************************************** */
/** 
 * @brief            Processes process_pdab_request_reset_message.      
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void process_pdab_request_reset_message(uint8_t *message, int32_t length)
{
    #ifdef DEBUG_MESSAGE_EXCHANGE
    dprintf_colour("[BROWN]Processing PDAB reset request. Length: %d[WHITE]\r\n", length);
    #endif
    if (length != PDAB_RESET_REQUEST_MESSAGE_BODY_LENGTH)
    {
        dputs_colour("[RED]Invalid length for PDAB_COMMAND_REQUEST_RESET[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PDAB_RESET_REQUEST_MESSAGE_BODY_LENGTH);
        return;
    }
    dputs_colour("[GREEN]Reset requested[WHITE]\r\n");
    asm("RESET");
}