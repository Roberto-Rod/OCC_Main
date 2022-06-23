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

#include "time.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */

typedef enum
{
    COMMAND_NONE = 0,
    COMMAND_ZERO_OFFSET = 1,
    COMMAND_RESET = 2,
    COMMAND_START_SCAN = 3,
    COMMAND_GET_STATUS = 4,
    COMMAND_STOP_SCAN = 5,
    COMMAND_IS_SHUTDOWN_SAFE = 6,
    COMMAND_LASER_CHECK = 7,
    COMMAND_REQUEST_SETTINGS = 8,
    COMMAND_UPDATE_SETTINGS = 9,
} PIB_COMMAND_t;

typedef enum
{
    PIC24_COMMAND_GET_STATUS = 1,
    PIC24_COMMAND_UPDATE_DATE_TIME = 2,//obsolete
    PIC24_COMMAND_REQUEST_SHUTDOWN = 4,
    PIC24_COMMAND_REQUEST_VERSION = 8,
} PIC24_COMMAND;

// *****************************************************************************
// Section: Data Types
// *****************************************************************************
/* grabbed from PDAB project */
/* need to be in a shared file ultimately */

#define LRS_POLE_BOUNDARIES        2U      // Maximu number of pole boundaries withing the scan range
#define PDAB_ADC_CHANNELS          2U      // Number of ADC channels
#define PDAB_DAC_CHANNELS          2U      // Number of DAC channels present (See AD_DAC_Drver.h))
#define PDAB_DPOT_CHANNELS         2U      // Number of DPOT channels present (See AD_DPOT_Drver.h))

#define PDAB_STATUS_LENGTH_8       128U    // Length device status buffer (in bytes)

#define PDAB_MAX_PEAKS             4
#define PDAB_MAX_SEPARATIONS       (PDAB_MAX_PEAKS - 1U)
#define PDAB_HEADER_LENGTH_8       148U                     // Length of scan status buffer (in bytes))

typedef union
{
    uint8_t      Byte[2];
    uint16_t     Word;
    struct
    {
        uint16_t Initialised:1;
        uint16_t LBAT:1;
        uint16_t LED1:1;
        uint16_t LED2:1;
        uint16_t ILED:1;
        uint16_t LON:1;
        uint16_t LPON:1;
        uint16_t Channel:1;
        uint16_t Direction:1;
        uint16_t Zero:1;
        uint16_t USB:1;
        uint16_t Triggered:1;
        uint16_t Scanning:1;
        uint16_t Saturated:1;
        uint16_t IPValid:1;
        uint16_t USB_Overrun:1;
    };
} _STATUS_FLAGS;

/** @brief typdef LSC status flag  */
typedef
    union {
        uint16_t    Short;
        struct {
            unsigned TUNE_FINISHED:1;
            unsigned TUNE_ERROR:1;
            unsigned TUNE_INPROG:1;
            unsigned :1;
            unsigned :1;
            unsigned :1;
            unsigned :1;
            unsigned :1;
        };

}LSC_Status_flags;
/******************************************************************************/

//Ensure that variables in LSC_struct allign to 32bit boundaries to prevent padding on 32bit system.
typedef union
{
    struct{
    /** @brief LSC firmware version  */
        uint16_t Version;                                   // 2 bytes
        LSC_Status_flags flags;                             // 2 bytes

        uint32_t    Range;                              // LSC maximum scan range
        uint32_t    Length;                             // LSC data acquisition length
        float       Frequency;                          // Drive frequency


        int32_t    Position;                                // Current stage position
                                                            // 4 bytes
        int32_t    RefPositions[LRS_POLE_BOUNDARIES];       // Encoder Index Positions
                                                            // 8 bytes
    };                                                      // 28 bytes
    uint8_t bytes[28];
} LSC_STATUS_t;                                            // 32 Bytes

typedef struct
{
    struct
    {
        uint16_t    Offset;                             // ADC offset
        uint16_t    Voltage;                            // ADC Voltage
    } ADC[PDAB_ADC_CHANNELS];                           // 4 Bytes per channel

    struct
    {
        uint16_t    Voltage[PDAB_DAC_CHANNELS];         // DAC voltages
    } DAC[PDAB_ADC_CHANNELS];                           // 4 Bytes per channel

    struct
    {
        uint8_t     Resistance[PDAB_DPOT_CHANNELS];    // Pot resistance
    } DPOT[PDAB_ADC_CHANNELS];                         // 2 Bytes per channel

} _LDA_STATUS;                                          // 20 Bytes

typedef struct
{
    union
    {
        uint8_t         Bytes[PDAB_STATUS_LENGTH_8];
        struct
        {
            uint8_t         Command;                        // 1 Bytes
            uint8_t         Length;                         // 1 Bytes
            union                                           // 6 Bytes
            {
                uint8_t     Data[6];
                uint16_t    Words[3];
                uint32_t    U32;
                float       F32;
            };

            struct
            {

                uint16_t    Version;
                 _STATUS_FLAGS    Flags;                    // 2 Bytes
                uint8_t     Device;
                uint8_t     Error;
            } DAB;                                          // 2 Bytes

            LSC_STATUS_t     LSC;                            // 32 Bytes
            _LDA_STATUS     LDA;                            // 20 Bytes
            uint16_t status_id;
            uint16_t status_sub_id;
        };
    };
} _STATUS_BUFFER;

/* scan status */

typedef struct
{
    uint16_t Position;
    uint16_t Amplitude;
    uint16_t FWHM;
    uint16_t Minimum[2];
} _PEAK;

typedef struct
{
    uint16_t        Scans;                                          // 2 Bytes
    uint16_t        Count;                                          // 2 Bytes
    _PEAK           Peak[PDAB_MAX_PEAKS];                           // 16 Bytes
    float           Separation[PDAB_MAX_SEPARATIONS];               // 12 Bytes
    float           Thickness[PDAB_MAX_SEPARATIONS];                // 12 Bytes
    float           Precision[PDAB_MAX_SEPARATIONS];                // 12 Bytes
}_MEASUREMENT;                                                      // 56 Bytes

typedef struct
{
    _STATUS_FLAGS   Flags;
    uint32_t        Length;
    uint32_t        Count;
    uint8_t         Gain;
    uint8_t         Power;
    uint16_t        Offset;
    uint16_t        Zero[2];
    float           Duration;
    float           Rate;
    uint16_t        Error;
} _SCAN_STATUS;                                                      // 30 Bytes

typedef struct
{
    union       // Header
    {
        uint8_t Bytes[PDAB_HEADER_LENGTH_8];
        struct
        {
            _SCAN_STATUS Status;
            _MEASUREMENT Measurement;

            uint16_t            Offset;
            uint16_t            DC_Level;
            uint16_t            Blocks;
            bool                valid;                                          // 1 Byte
            bool                complete;
        };
    };
} _SCAN_HEADER;

typedef struct
{
    float    refractive_index;
    uint16_t peak_thresholds[2];
    uint16_t separation_limits[2];
    uint16_t fwhm_limits[2];

    uint8_t  comparator_reference_voltage;          // scan settings
    uint8_t  laser_power;                            // device settings
    uint8_t  amplifier_gain;
    uint8_t  boost_gain;
    uint16_t total_scans;
} _SCAN_SETTINGS;

/* grabbed from pic24 project, the file should be shared eventually */

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
        //battery 'state of cahrge' in %
        uint8_t battery_soc_per;        //1 byte    17
        uint8_t last_reset_id;            //1 byte    18
    } PE_STATUS_t;

// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void message_exchange_task(void);
void send_command_to_PDAB(PIB_COMMAND_t command, uint8_t *data, uint16_t data_length);
void process_PDAB_status_message(uint8_t *message, int32_t length);
void process_scan_status_message(uint8_t *message, int32_t length);
void process_scan_data_message(uint8_t *message, int32_t length);
void process_request_shutdown_message(uint8_t *message, int32_t length);
void process_request_settings_message(uint8_t *message, int32_t length);
void update_settings_on_PDAB(void);
void register_event(uint8_t unit_id,uint8_t event_id,uint8_t sub_id);

void pic24_send_command(PIC24_COMMAND command, uint8_t *data, uint16_t data_length);
void process_pic24_status_message(uint8_t*, int32_t);
void process_pic24_is_safe_to_shutdown_message(uint8_t*, int32_t);
void process_pic24_wakeup_message(uint8_t*, int32_t);
void process_pic24_version_message(uint8_t *message, int32_t length);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MESSAGE_EXCHANGE_H */
