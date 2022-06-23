/* 
 * File:   pe_interface.h
 *
 * Created on August 9, 2021, 4:24 PM
 */

#ifndef PE_INTERFACE_H
#define	PE_INTERFACE_H

#include <stdint.h>



//Incoming messages for PE
/** @brief define for the header message to request status from PE */
#define PE_RX_GET_STATUS_MESSAGE_HEADER         "PIC24_COMMAND_GET_STATUS"
/** @brief define macro holding length of GET_STATUS message */
#define PE_RX_GET_STATUS_MESSAGE_LENGTH         0
/** @brief define for the header message to set the time and data in PE */
#define PE_RX_SET_TIME_DATE_MESSAGE_HEADER      "PIC24_COMMAND_UPDATE_DATE_TIME:"
/** @brief define macro holding length of SET_TIME_DATE message */
#define PE_RX_SET_TIME_DATE_MESSAGE_LENGTH      8
/** @brief define for the header message to request version from PE */
#define PE_RX_GET_VERSION_MESSAGE_HEADER        "PIC24_COMMAND_REQUEST_VERSION"
/** @brief define macro holding length of PIC24_VERSION message */
#define PE_RX_GET_VERSION_MESSAGE_LENGTH        0 
/** @brief define for the header message to request PE shutdown the system*/
#define PE_RX_REQUEST_SHUTDOWN_MESSAGE_HEADER   "PIC24_COMMAND_REQUEST_SHUTDOWN"
/** @brief define macro holding length of REQUEST_SHUTDOWN message */
#define PE_RX_REQUEST_SHUTDOWN_MESSAGE_LENGTH   0

#define PE_RX_RESET_TEMPERATURE_MESSAGE_HEADER  "PIC24_COMMAND_RESET_TEMP"

#define PE_RX_RESET_TEMPERATURE_MESSAGE_LENGTH   1  // if message[0] == 'A' -> resets flags & min & max values, if message[0] == 'F' resets flags only

#define PE_RX_RESET_ERROR_MESSAGE_HEADER        "PIC24_CLEAR_ERROR_FLAG"

#define PE_RX_RESET_ERROR_MESSAGE_LENGTH         1 // Error flag ID to reset or 0xFE to reset all. 

#define PE_RX_RESET_MESSAGE_HEADER        "PIC24_RESET"

#define PE_RX_RESET_MESSAGE_LENGTH         0

//Outgoing messages for PE
/** @brief define for the header message sent from PE to query if system is safe to shutdown */
#define PE_TX_IS_SHDTWN_SAFE_MESSAGE_HEADER     "PIC24_IS_SHUDTOWN_SAFE"
/** @brief define macro holding length of PIC24_IS_SHUTDOWN_SAFE message */
#define PE_TX_IS_SHDTWN_SAFE_MESSAGE_LENGTH     0
/** @brief define for the header message sent from PE with its firmware version */
#define PE_TX_VERSION_MESSAGE_HEADER            "PIC24 Version"
/** @brief define for the header message sent from PE to wake system*/
#define PE_TX_WAKEUP_MESSAGE_HEADER             "PIC24_WAKEUP"
/** @brief define macro holding length of PIC24_WAKEUP message */
#define PE_TX_WAKEUP_MESSAGE_LENGTH             0
/** @brief define for the header message sent from PE with its status */
#define PE_TX_STATUS_MESSAGE_HEADER             "PIC24 Status"

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct
    {
        uint32_t message_start_flag;                        // message start flag
        uint32_t message_index;                             // incrementing message index
        uint32_t message_length;                            // length of the message body
        uint32_t message_crc;                               // message body CRC
        bool ack_required;                                  // true if this message needs to be acknowledged
        uint16_t header_checksum;                           // simple checksum for this header
    } PE_message_header_t;

    typedef struct {
        uint8_t year;
        uint8_t month;
        uint8_t date;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
        uint8_t tenth_second;
    } PE_RTCCFORM;

    typedef uint16_t PE_FLAGS_t;
   
#define PE_FLAGS_BITS   16u
    


    typedef enum {
        NO_FLAGS =                      0x0000u,
                
        WARNING_FLAG_DEVICE_DROPPED =   0x0001u,
        WARNING_FLAG_OVERTEMPERATURE =  0x0002u,
        WARNING_FLAG_UNDERTEMPERATURE = 0x0004u,
        // Spare flag for re-calibration 0x0008u, 
                
        FLAG_DEVICE_CHARGING =          0x0010u,
        WARNING_FLAG_BATTERY_LOW =      0x0020u,
        WARNING_FLAG_SHUTDOWN =         0x0040u,
        // Spare flag                   0x0080u, 
        
        // Spare flag                   0x0100u, // Error 8  
        // Spare flag                   0x0200u, // Error 7        
        ERROR_ACCEL_SENSOR =            0x0400u, // Error 6 
        ERROR_TEMP_SENSOR =             0x0800u, // Error 5 
        
        // Spare Error flag             0x1000u, // Error 4 
        ERROR_RTCC =                    0x2000u, // Error 3 
        ERROR_RESET =                   0x4000u, // Error 2         
        ERROR_OCCURRED =                0x8000u, // Error 1 
    } PE_FLAG;

    typedef struct {
        PE_RTCCFORM rtc_data;           //8 bytes 
        PE_FLAGS_t flags;               //2 byte    10
        int16_t temp_cur_degC_Q8;       //2 bytes   12
        int16_t temp_min_degC_Q8;       //2 bytes   14
        int16_t temp_max_degC_Q8;       //2 bytes   16
        uint8_t battery_soc_per;        //1 byte    17
        uint8_t last_reset_id;            //1 byte    18 
    } PE_STATUS;

/** @brief define for the PE status structure size*/
#define PE_TX_STATUS_MESSAGE_LENGTH_BYTES 32
    typedef union {
        
        PE_STATUS status;

        uint8_t bytes [PE_TX_STATUS_MESSAGE_LENGTH_BYTES ];
    } PE_data;

#ifdef	__cplusplus
}
#endif

#endif	/* PE_INTERFACE_H */

