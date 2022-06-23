/* ************************************************************************** */
/** @file message_exchange.c
 *
 *  @brief Library to handle UART comms.
 *
 *  @copyright Occuity Limited (c) 2020
 */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include <string.h>

#include "debug.h"
#include "mcc_generated_files/pin_manager.h"
#include "message_exchange.h"
#include "app.h"
#include "power_switch_interrupt.h"

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */

/** @brief define macro holding maximum length of the command buffer */
#define MAX_COMMAND_LENGTH                      128
/** @brief define macro holding maximum value of the wakeup timer */
#define WAKEUP_TIMEOUT                          1000
/** @brief timer holding current value of the wakeup timer */
static unsigned int timer_miliseconds = WAKEUP_TIMEOUT;
/** @brief this variable holds info on whether the wakeup request was made */
static bool trigger_wakeup = false;

/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */
static uint8_t bit_to_index(uint8_t bit);

/* ************************************************************************** */
/** 
 * @brief            Converts bit in PIC24_COMMAND to index.
 *
 * @note             Called by send_command to translate enum PIC24_command to 
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
void send_command(PIC24_COMMAND command, uint8_t *data, uint16_t data_length)
{
    const char *command_strings[] = {PE_TX_WAKEUP_MESSAGE_HEADER ,
                                    PE_TX_STATUS_MESSAGE_HEADER,
                                    PE_TX_VERSION_MESSAGE_HEADER,
                                    PE_TX_IS_SHDTWN_SAFE_MESSAGE_HEADER};
    const char *command_string;
    uint32_t command_length;
    static uint8_t command_buffer[MAX_COMMAND_LENGTH];
    
    uint8_t enquene_sucess = false; 

    /* do nothing if the command is not valid */
    if ((PIC24_WAKEUP != command) && (PIC24_STATUS != command) && (PIC24_VERSION != command) && (PIC24_IS_SHUDTOWN_SAFE != command))
    {
        return;
    }

    /* send command */
    if (0 == data_length)
    {
        /* same as before to minimise chance of adding a bug */
        command_string = command_strings[bit_to_index(command) - 1];
        command_length = strlen(command_string);
        enquene_sucess = pic_comms_queue_message((uint8_t *) command_string, command_length, true);  // requires ACK
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
        enquene_sucess =  pic_comms_queue_message((uint8_t *) command_buffer, command_length, true);  // requires ACK
        
        enquene_sucess = enquene_sucess | 0x80;  
    }
    #ifndef NO_DEBUG_COMMS
    dprintf_colour("[YELLOW]Command [%s] send code: %X[WHITE]\r\n", command_string, enquene_sucess);
    #endif
}

/* ************************************************************************** */
/** 
 * @brief            Processes GET_STATUS message. This function checks if 
 *                   length of the GET_STATUS message is correct, updates app
 *                   status with latest RTC data and sends the _APP_STATUS
 *                   structure to PIB.
 * 
 * @param[in]        message Message received with the GET_STATUS command
 * @param[in]        length Length of the message received
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void process_get_status_message(uint8_t *message, int32_t length)
{
    //dprintf_colour("[BROWN]Responding with status packet[WHITE]\r\n");

    if (length != PE_RX_GET_STATUS_MESSAGE_LENGTH)
    {
        dputs_colour("[RED]Invalid length for GET_STATUS[WHITE]\r\n");
        return;
    }
    
    //update RTC
    app_update_date_time();
    //get app status
    _APP_STATUS app_status = app_get_status();
    send_command(PIC24_STATUS, (uint8_t *) &app_status, PE_TX_STATUS_MESSAGE_LENGTH_BYTES);
    
}

/* ************************************************************************** */
/** 
 * @brief            Processes SET_TIME_DATE message. This function checks if 
 *                   length of the SET_TIME_DATE message is correct, and updates
 *                   the RTC with the time/date received.
 * 
 * @param[in]        message Message received with the GET_STATUS command
 * @param[in]        length Length of the message received
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void process_set_time_date_message(uint8_t *message, int32_t length)
{
    dprintf_colour("[BROWN]Setting time on P24[WHITE]\r\n");
    RTCCFORM new_time;
    if (length != PE_RX_SET_TIME_DATE_MESSAGE_LENGTH )
    {
        dputs_colour("[RED]Invalid length for SET_TIME_DATE_LENGTH[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", sizeof(RTCCFORM));
        dprintf_colour("[RED]The length is: %d[WHITE]\r\n", length);
        return;
    }

    memcpy(&new_time, (RTCCFORM *) message, sizeof(RTCCFORM));
//    dprintf_colour("[CYAN]New year: %02d[WHITE]\r\n", new_time.year);
//    dprintf_colour("[CYAN]New month: %02d[WHITE]\r\n", new_time.month);
//    dprintf_colour("[CYAN]New date: %02d[WHITE]\r\n", new_time.date);
//    dprintf_colour("[CYAN]New hour: %02d[WHITE]\r\n", new_time.hour);
//    dprintf_colour("[CYAN]New minute: %02d[WHITE]\r\n", new_time.minute);
//    dprintf_colour("[CYAN]New second: %02d[WHITE]\r\n", new_time.second);
    set_time(&new_time);
    
}

/* ************************************************************************** */
/** 
 * @brief            Processes REQUEST_SHUTDOWN message. This function checks if 
 *                   length of the REQUEST_SHUTDOWN message is correct, and if
 *                   so turns the device off.
 * 
 * @param[in]        message Message received with the GET_STATUS command
 * @param[in]        length Length of the message received
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void process_power_down_message(uint8_t *message, int32_t length)
{    
    dprintf_colour("[BROWN]Shutting down[WHITE]\r\n");

    if (length != PE_RX_REQUEST_SHUTDOWN_MESSAGE_LENGTH)
    {
        dputs_colour("[RED]Invalid length for SET_TIME_DATE_LENGTH[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PE_RX_REQUEST_SHUTDOWN_MESSAGE_LENGTH);
        dprintf_colour("[RED]The length is: %d[WHITE]\r\n", length);
        return;
    }

    turn_off_device();
}

/* ************************************************************************** */
/** 
 * @brief            Processes REQUEST_VERSION message. This function checks if 
 *                   length of the REQUEST_VERSION message is correct, and if
 *                   so responds to PIB with the version of the P24 software.
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
    dprintf_colour("[BROWN]Sending PIC24 version[WHITE]\r\n");

    if (length != PE_RX_GET_VERSION_MESSAGE_LENGTH)
    {
        dputs_colour("[RED]Invalid length for REQUEST_VERSION[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PE_RX_GET_VERSION_MESSAGE_LENGTH);
        dprintf_colour("[RED]The length is: %d[WHITE]\r\n", length);
        return;
    }

    uint16_t version = SYS_version();
    send_command(PIC24_VERSION, (uint8_t *) &version, sizeof(uint16_t));
}

void process_reset_error_message(uint8_t *message, int32_t length)
{
    dprintf_colour("[BROWN]Request to clear error flag: %i[WHITE]\r\n", *message);

    if (length != PE_RX_RESET_ERROR_MESSAGE_LENGTH)
    {
        dputs_colour("[RED]Invalid length for CLEAR_ERROR_FLAG[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PE_RX_RESET_ERROR_MESSAGE_LENGTH);
        dprintf_colour("[RED]The length is: %d[WHITE]\r\n", length);
        return; 
    }
    
    uint8_t id = *message; 
    
    if(id == 0xFE){
        
        PE_FLAGS_t flags =0xFF00u; 
        app_clear_flag(flags); 
        
    }else if((id > 0) && (id < 9)){
        
        PE_FLAGS_t flags = 1u << (PE_FLAGS_BITS - id); 
        app_clear_flag(flags); 
        
    }

}

void process_reset_message(uint8_t *message, int32_t length)
{
    dprintf_colour("[BROWN]Request to power cycle the board.[WHITE]\r\n");

    if (length != PE_RX_RESET_MESSAGE_LENGTH)
    {
        dputs_colour("[RED]Invalid length for RESET[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PE_RX_RESET_MESSAGE_LENGTH);
        dprintf_colour("[RED]The length is: %d[WHITE]\r\n", length);
        return; 
    }
    
    uint32_t i;
    
    for(i=0;i<500000;i++){
        Nop();
    }

    dprintf_colour("[RED]POWER CUT OFF[WHITE]\r\n");

    EN_SetHigh(); //TURN_PWR_OFF;

    for(i=0;i<2500000;i++){
        Nop();
    }

    dprintf_colour("[RED]POWER ON[WHITE]\r\n");

    EN_SetLow(); //TURN_PWR_ON;
}

void process_reset_temp_message(uint8_t *message, int32_t length)
{
    dprintf_colour("[BROWN]Request to reset temperature min,max & flags[WHITE]\r\n");

    if (length != PE_RX_RESET_TEMPERATURE_MESSAGE_LENGTH)
    {
        dputs_colour("[RED]Invalid length for RESET_TEMPERATURE[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PE_RX_RESET_TEMPERATURE_MESSAGE_LENGTH);
        dprintf_colour("[RED]The length is: %d[WHITE]\r\n", length);
        return; 
    }
    
    if(*message == 'A'){
        
        app_reset_temperature_flags(true); 
        
    }else if(*message == 'F'){
        
        app_reset_temperature_flags(false); 
    }
}


/* ************************************************************************** */
/** 
 * @brief            Sends a query to PIB asking if it is safe to shutdown.
 * 
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void send_is_shutdown_safe_message(void)
{
    send_command(PIC24_IS_SHUDTOWN_SAFE, NULL, PE_RX_REQUEST_SHUTDOWN_MESSAGE_LENGTH);
}

/* ************************************************************************** */
/** 
 * @brief            This function marks that wakeup msg shall be sent to DAR.
 *
 * @note             This function is called from button press interrupt, and
 *                   hence has to be as short as possible.
 *
 * @return           None.
 */
/* ************************************************************************** */
void wakeup_dar(void)
{
    if(timer_miliseconds == WAKEUP_TIMEOUT)
    {
        timer_miliseconds = 0;
        trigger_wakeup = true;
    }
}

/* ************************************************************************** */
/** 
 * @brief            This function takes care of wakeup tasks. It executes
 *                   send_wakeup_message() if wakeup query was marked for
 *                   sending.
 *
 * @note             This function is called from button press interrupt, and
 *                   hence has to be as short as possible.
 *
 * @return           None.
 */
/* ************************************************************************** */
void wakeup_task(void)
{
    if(trigger_wakeup == true)
    {
        trigger_wakeup = false;
        send_wakeup_message();
    }
}
/* ************************************************************************** */
/** 
 * @brief            Sends a wakeup message to PIB.
 * 
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void send_wakeup_message(void)
{
    send_command(PIC24_WAKEUP, NULL, PE_TX_WAKEUP_MESSAGE_LENGTH   );
}
