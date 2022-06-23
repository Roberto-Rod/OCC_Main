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
#include <stdlib.h>

#include "definitions.h"
#include "message_exchange.h"

#define PDAB_STATUS_MESSAGE_HEADER              "PDAB Status: "
#define PDAB_STATUS_MESSAGE_HEADER_LENGTH       13
#define PDAB_STATUS_MESSAGE_BODY_LENGTH         128
#define PDAB_REQUEST_SHUTDOWN_MESSAGE_BODY_LENGTH 0

#define PIC24_IS_SAFE_TO_SHUTDOWN_MESSAGE_BODY_LENGTH 0
#define PIC24_VERSION_MESSAGE_BODY_LENGTH       2
#define PIC24_WAKEUP_MESSAGE_BODY_LENGTH        0

#define MAX_COMMAND_LENGTH                      128

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
APP_DATA appData;

extern usability_metrics_t usability_metrics;

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */


/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

void message_exchange_task(void)
{

}

uint16_t bit_to_index(uint16_t bit)
{
    uint16_t index;

    index = 0;
    while (bit > 0)
    {
        bit >>= 1;
        index++;
    }

    return (index);
}

void send_command_to_PDAB(PIB_COMMAND_t command, uint8_t *data, uint16_t data_length)
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
        pic_comms_queue_message((uint8_t *) command_buffer, command_length, true);  // requires ACK
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
        pic_comms_queue_message((uint8_t *) command_buffer, command_length, true);  // requires ACK
    }
    #ifdef DEBUG_COMMS
    dprintf_colour("[YELLOW]Command [%s] sent[WHITE]\r\n", command_string);
    #endif
}

/* TODO: move to different file, change parameter to status structure, etc. */
void process_PDAB_status_message(uint8_t *message, int32_t length)
{
    #ifdef DEBUG_COMMS
    dprintf_colour("[BROWN]Processing PDAB status message. Length is %d[WHITE]\r\n", length);
    #endif
    if (length != sizeof(_STATUS_BUFFER))
    {
        #ifdef DEBUG_COMMS
        dputs_colour("[RED]Invalid length for _STATUS_BUFFER[WHITE]\r\n");
        #endif
        return;
    }

    app_update_status( message );
}

void process_scan_status_message(uint8_t *message, int32_t length)
{
    static _SCAN_HEADER header;
    #ifdef DEBUG_COMMS
    dprintf_colour("[BROWN]Processing Scan status message. Length is %d[WHITE]\r\n", length);
    #endif
    if (length != sizeof(_SCAN_HEADER))
    {
        #ifdef DEBUG_COMMS
        dputs_colour("[RED]Invalid length for _SCAN_HEADER[WHITE]\r\n");
        #endif
        return;
    }

    memcpy(&header, (_SCAN_HEADER *) message, sizeof(_SCAN_HEADER));

    scan_header_received(&header);

    #ifdef DEBUG_COMMS
    dprintf_colour("[BROWN]scan_header->valid is %d[WHITE]\r\n", header.valid);
    dprintf_colour("[BROWN]Measurement.Count is %d[WHITE]\r\n", header.Measurement.Count);
    dprintf_colour("[BROWN]Status.Length is %d[WHITE]\r\n", header.Status.Length);
    dprintf_colour("[BROWN]Status.Power is %d[WHITE]\r\n", header.Status.Power);
    dprintf_colour("[BROWN]Status.Gain is %d[WHITE]\r\n", header.Status.Gain);
    #endif
}

/* scan data message is scan data header plus data */
/* length is the length of the header plus data */
void process_scan_data_message(uint8_t *message, int32_t length)
{

}

void process_request_shutdown_message(uint8_t *message, int32_t length)
{
    dprintf_colour("[YELLOW]PDA OK OFF[WHITE]\r\n");
    #ifdef DEBUG_PIC24
    dprintf_colour("[BROWN]Processing PDAB shutdown request. Length: %d[WHITE]\r\n", length);
    #endif
    
    app_set_lcd_brightness(0U);
    #ifndef DISABLE_AUDIO
    play_notification(play_POWER_DOWN);
    #endif
    
    pic24_send_command(PIC24_COMMAND_REQUEST_SHUTDOWN, NULL, 0);
}

void update_settings_on_PDAB(void)
{
    uint32_t command_length = 0;
    #define MAX_COMMAND_LENGTH 128
    static uint8_t command_buffer[MAX_COMMAND_LENGTH];
    uint32_t buffer_length = sizeof(DEVICE_SETTINGS_t);

    command_buffer[0] = (uint8_t)COMMAND_UPDATE_SETTINGS;
    command_length++;
    command_buffer[command_length] = ':';
    command_length++;
    memcpy(&command_buffer[command_length], &device_settings, buffer_length);
    command_length += buffer_length;
    pic_comms_queue_message((uint8_t *) command_buffer, command_length, true);  // requires ACK
}

void process_request_settings_message(uint8_t *message, int32_t length)
{
    appData.get_settings = false;
    memcpy(&device_settings_for_PI, (DEVICE_SETTINGS_FOR_PI_t *) message, sizeof(DEVICE_SETTINGS_FOR_PI_t));
    memcpy(&device_settings, &device_settings_for_PI, sizeof(DEVICE_SETTINGS_t));
    device_settings_for_PI.device_name[16] = 0;
    
    update_settings_from_PDAB();
}

struct {
    uint8_t bytes[64];
    union{
        uint32_t time_code;
        uint8_t module_id;
        uint8_t unit_id;
        uint8_t event_id;
        uint8_t sub_id;
    };
}system_event;

void register_event(uint8_t unit_id,uint8_t event_id,uint8_t sub_id)
{
    system_event.time_code = 3651440;
    system_event.module_id = 2;
    system_event.unit_id = unit_id;
    system_event.event_id = event_id;
    system_event.sub_id = sub_id;
}
/******************************************************************************/
/* PIC24 section */
/******************************************************************************/

void pic24_send_command(PIC24_COMMAND command, uint8_t *data, uint16_t data_length)
{
#ifndef DISABLE_PIC24
    const char *command_strings[] = {"PIC24_COMMAND_GET_STATUS", "PIC24_COMMAND_UPDATE_DATE_TIME", "PIC24_COMMAND_REQUEST_SHUTDOWN", "PIC24_COMMAND_REQUEST_VERSION"};
    const char *command_string;
    uint32_t command_length;
    static uint8_t command_buffer[MAX_COMMAND_LENGTH];

    /* do nothing if the command is not valid */
    if ((PIC24_COMMAND_GET_STATUS != command) &&
            (PIC24_COMMAND_UPDATE_DATE_TIME != command) &&
            (PIC24_COMMAND_REQUEST_SHUTDOWN != command) &&
            (PIC24_COMMAND_REQUEST_VERSION != command))
    {
        return;
    }

    /* send command */
    if (0 == data_length)
    {
        /* same as before to minimise chance of adding a bug */
        command_string = command_strings[bit_to_index(command) - 1];
        command_length = strlen(command_string);
        pic24_comms_queue_message((uint8_t *) command_string, command_length, true);  // requires ACK
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
        pic24_comms_queue_message((uint8_t *) command_buffer, command_length, true);  // requires ACK
    }

    #ifdef DEBUG_PIC24
    dprintf_colour("[YELLOW]Command [%s] sent[WHITE]\r\n", command_string);
    #endif
#endif
}

void process_pic24_status_message(uint8_t *message, int32_t length)
{
    #ifdef DEBUG_PIC24
    dprintf_colour("[BROWN]Processing PIC24 status message. Length: %d[WHITE]\r\n", length);
    #endif
    //dprintf_colour("[BROWN]PIC24 - Length: %d/%d[WHITE]\r\n", length, sizeof(PE_STATUS_t));

    PE_STATUS_t p24_status;
    if (length != 32)
    {
        #ifdef DEBUG_PIC24
        dputs_colour("[RED]Invalid length for APP_STATUS[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", sizeof(PE_STATUS_t));
        #endif
        dputs_colour("[RED]ERROR: Invalid length for PE_STATUS_t[WHITE]\r\n");
        return;
    }

    memcpy(&p24_status, (PE_STATUS_t *) message, sizeof(PE_STATUS_t));

    if(p24_status.battery_soc_per != appData.battery_percentage)
    {
        appData.battery_percentage = p24_status.battery_soc_per;
        appData.status_updated = true;
        #ifdef DEBUG_PIC24
        dprintf_colour("[CYAN]Battery_charge: %d\%[WHITE]\r\n", p24_status.battery_soc_per);
        #endif
    }
    
    if(p24_status.temp_cur_degC_Q8 != 0)
    {
        static float temperature_max_session = -100.0;
        static float temperature_min_session = 100.0;
        
        
        usability_metrics.temperature = p24_status.temp_cur_degC_Q8 / 256.0f;
        if(usability_metrics.temperature > temperature_max_session){
            temperature_max_session = usability_metrics.temperature;
        }
        if(usability_metrics.temperature < temperature_min_session){
            temperature_min_session = usability_metrics.temperature;
        }
        
        usability_metrics.temperature_low_peak = temperature_min_session;
        usability_metrics.temperature_high_peak = temperature_max_session;
        
        //dprintf_colour("[CYAN]Temperature: %.1fC / min: %.1fC / max: %.1fC [WHITE]\r\n", usability_metrics.temperature,usability_metrics.temperature_low_peak,usability_metrics.temperature_high_peak);
    }

    if((p24_status.flags & FLAG_DEVICE_CHARGING) && (appData.chargeState != true))
    {
        appData.chargeState = true;
        appData.status_updated = true;
        #ifdef DEBUG_PIC24
        dprintf_colour("[CYAN]Device charging[WHITE]\r\n");
        #endif
    }
    else if(!(p24_status.flags & FLAG_DEVICE_CHARGING) && (appData.chargeState != false))
    {
        appData.chargeState = false;
        appData.status_updated = true;
        #ifdef DEBUG_PIC24
        dprintf_colour("[CYAN]Device not charging[WHITE]\r\n");
        #endif
    }

    if((p24_status.flags & WARNING_FLAG_BATTERY_LOW) && (appData.batteryState != true))
    {
        appData.batteryState = true;
        appData.status_updated = true;
        #ifdef DEBUG_PIC24
        dprintf_colour("[CYAN]Battery low[WHITE]\r\n");
        #endif
    }
    else if(!(p24_status.flags & WARNING_FLAG_BATTERY_LOW) && (appData.batteryState != false))
    {
        appData.batteryState  = false;
        appData.status_updated = true;
        #ifdef DEBUG_PIC24
        dprintf_colour("[CYAN]Battery OK[WHITE]\r\n");
        #endif
    }
}

void process_pic24_is_safe_to_shutdown_message(uint8_t *message, int32_t length)
{
    dprintf_colour("[YELLOW]P24 WANTS OFF[WHITE]\r\n");
    #ifdef DEBUG_PIC24
    dprintf_colour("[BROWN]Processing PIC24 is safe to shutdown query. Length: %d[WHITE]\r\n", length);
    #endif
    if (length != PIC24_IS_SAFE_TO_SHUTDOWN_MESSAGE_BODY_LENGTH)
    {
        #ifdef DEBUG_PIC24
        dputs_colour("[RED]Invalid length for PIC24_IS_SHUTDWN_SAFE[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PIC24_IS_SAFE_TO_SHUTDOWN_MESSAGE_BODY_LENGTH);
        #endif
        return;
    }
    app_send_power_down_request();
}

void process_pic24_version_message(uint8_t *message, int32_t length)
{
    #ifdef DEBUG_PIC24
    dprintf_colour("[BROWN]Processing PIC24 version message. Length: %d[WHITE]\r\n", length);
    #endif
    if (length != PIC24_VERSION_MESSAGE_BODY_LENGTH)
    {
        #ifdef DEBUG_PIC24
        dputs_colour("[RED]Invalid length for PIC24_IS_SHUTDWN_SAFE[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PIC24_VERSION_MESSAGE_BODY_LENGTH);
        #endif
        return;
    }

    memcpy(&appData.PEVersion, (uint16_t *) message, sizeof(uint16_t));

    #ifdef DEBUG_PIC24
    dprintf_colour("[BROWN]PIC24 version is: %d[WHITE]\r\n", appData.PEVersion);
    #endif
}

void process_pic24_wakeup_message(uint8_t *message, int32_t length)
{
    #ifdef DEBUG_PIC24
    dprintf_colour("[BROWN]Processing PIC24 wakeup message. Length: %d[WHITE]\r\n", length);
    #endif
    if (length != PIC24_WAKEUP_MESSAGE_BODY_LENGTH)
    {
        #ifdef DEBUG_PIC24
        dputs_colour("[RED]Invalid length for PIC24_WAKEUP[WHITE]\r\n");
        dprintf_colour("[RED]The length should be: %d[WHITE]\r\n", PIC24_WAKEUP_MESSAGE_BODY_LENGTH);
        #endif
        return;
    }

    power_management_activity_trigger();

}
