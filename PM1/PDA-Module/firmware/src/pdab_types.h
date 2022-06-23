/* 
 * File:   PDAB_Types.h
 * Author: robin
 *
 * Created on 24 April 2019, 18:22
 */

#include <stdint.h>
#include <stdbool.h>

#ifndef PDAB_TYPES_H
#define	PDAB_TYPES_H

#ifdef	__cplusplus
extern "C" {
#endif
/******************************************************************************/
    
#define FWD     0U
#define BCK     1U    
    
#define LRS_POLE_PERIOD         2U      // Encoder scale pole pitch
#define LRS_SCAN_RANGE          6U      // Scan range rounded UP to the nearest mm
#define LRS_POLE_BOUNDARIES     2U      // Maximu number of pole boundaries withing the scan range    
    
/******************************************************************************/
// Only parameters in this section should be changed to match the device config   
#define PDAB_ADC_CHANNELS          2U                                                  // Number of ADC channels
#define PDAB_ADC_CHANNEL_1         0U                                                  //     
#define PDAB_DAC_CHANNEL_2         1U                                                  //    
#define PDAB_DAC_CHANNELS          2U                                                  // Number of DAC channels present (See AD_DAC_Drver.h))
#define PDAB_DPOT_CHANNELS         2U                                                  // Number of DPOT channels present (See AD_DPOT_Drver.h))
#define PDAB_LASER_CHANNELS        1U                                                  // Number of laser sources in the system
#define PDAB_AMPLIFIER_CHANNELS    1U                                                  // Number of amplifiers in the system
    
#define PDAB_SCANS_PER_TRANSFER    1U                                                  // Number of scans per USB transfer
    
#define PDAB_SCAN_LENGTH_16        5000U                                               // Number of samples per scan (in words)
#define PDAB_STATUS_LENGTH_8       128U                                                // Length device status buffer (in bytes) 
#define PDAB_HEADER_LENGTH_8       148U                                                // Length of scan status buffer (in bytes))
/******************************************************************************/
#define PDAB_TOTAL_SCAN_BUFFERS    2U
/******************************************************************************/     
#define PDAB_SCAN_LENGTH_8         ( PDAB_SCAN_LENGTH_16 * 2U )                       // Number of samples per scan (in 16 bit words)   
#define PDAB_STATUS_LENGTH_16      ( PDAB_STATUS_LENGTH_8 / 2U )                      // Length device status buffer (in 16 bit words)    
#define PDAB_HEADER_LENGTH_16      ( PDAB_HEADER_LENGTH_8 / 2U )                      // Length of scan status buffer (in 16 bit words)
#define PDAB_DATA_LENGTH_8         ( PDAB_SCAN_LENGTH_8 + PDAB_HEADER_LENGTH_8 )      // Scan Data length (in Words) of a scan from channel 1 
#define PDAB_DATA_LENGTH_16        ( PDAB_SCAN_LENGTH_16 + PDAB_HEADER_LENGTH_16 )    // Scan Data length (in Words) of a scan from channel 1                                                                                        // and channel 2. Must be divisible by 64           
/******************************************************************************/
#define PDAB_IGNORE_INIT_SCANS      20
#define PDAB_MAX_PEAKS              4
#define PDAB_MAX_SEPARATIONS        PDAB_MAX_PEAKS - 1U
/******************************************************************************/
#define PDAB_NPDA_BUFFER_LENGTH     1000U
#define PDAB_NPDA_SCANS             100U 
#define PDAB_NPDA_BLOCK_SIZE        10U     
#define PDAB_NPDA_BLOCKS            ( PDAB_NPDA_SCANS / PDAB_NPDA_BLOCK_SIZE )
   
/******************************************************************************/    
#define MAKE_BUFFER_DMA_READY  __attribute__((coherent)) __attribute__((aligned(16))) 
/******************************************************************************/    
#define TARGET_PEAK_SIZE 50000.0f
#define AUTOGAIN_SAMPLES 20
#define AUTO_GAIN_MAX 8.0f
#define AUTO_GAIN_MIN 2.0f
#define AUTO_GAIN_STEPS 15U

typedef enum
{
	COMM_NONE = 0,
    COMM_USB,
    COMM_SQI,
    COMM_UART,
} COMM_STATES;    
    
typedef enum
{
	/* Application's state machine's initial state. */
	PDAB_STATE_INIT=0,

    /* Application runs the main task */
    PDAB_STATE_MAIN_TASKS,
            
    /* Application USB tasks */
    PDAB_STATE_USB_TASKS,      
        
    /* Application runs continuous scanning mode */        
    PDAB_STATE_SCANNING,        
  
    /* Put MCU in sleep state */        
    PDAB_STATE_SLEEP,             
            
    /* Reset MCU */        
    PDAB_STATE_RESET,              
            
    /* Application error occurred */
    PDAB_STATE_ERROR,
            
    /* Application is idle */        
    PDAB_STATE_IDLE,    
            
    /* Application is waiting for zero offset process to finish */        
    PDAB_STATE_INIT_ZERO_OFF_WAIT,     

} PDAB_STATES;

/******************************************************************************/
typedef enum
{
    NO_ERRORS=0,
    COMMUNICATION_ERROR=100,        
        I2C1_ERROR,
        SPI1_ERROR,
        HSUSB_ERROR, 
    PERIPHERAL_ERROR=200,     
        ADC_ERROR,            
        DAC1_ERROR,
        DAC2_ERROR,            
        DPOT_1_ERROR,
        DPOT_2_ERROR,        
        DMA_ERROR,
            DMA_ADDRESS_ERROR,            
        LSC_ERROR,
        TIMER_ERROR,
        DISPLAY_ERROR,            
    FUNCTION_ERROR=300,        
        DAQ_ERROR,
        SET_GAIN_ERROR,
            SET_GAIN_INVALID_CHANNEL,            
        LASER_DRIVER_ERROR,
            LASER_ON_FAIL,
            LASER_OFF_FAIL,
        ADC_OFFSET_ERROR,
            ADC_INVALID_CHANNEL,            
        ZERO_OFFSET_ERROR,
            ZERO_OFFSET_NOT_SET          
} PDAB_ERROR_CODES;

/******************************************************************************/
typedef enum
{
    USB_SOFTWARE_NUL,//no software
    USB_SOFTWARE_PCC,//pcontrol confocal
    USB_SOFTWARE_DCS,//data collection software
    USB_SOFTWARE_ETS,//eeprom tool software
    USB_SOFTWARE_VCT//verification & calibration tool software
}USB_SOFTWARE_t;

typedef enum
{
    GET_NAME = 1,
    GET_ID = 2,
    GET_COUNTER = 3,
    SCAN_START = 4,
    SCAN_STOP = 5
}USB_VCT_COMMAND_t;
/******************************************************************************/
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

/******************************************************************************/
typedef union {	
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
    uint32_t u32_arr[7];
} LSC_STATUS_t;                                        
/******************************************************************************/

/******************************************************************************/
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

/******************************************************************************/
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
            } DAB;                                          // 6 Bytes    
 
            LSC_STATUS_t     LSC;                            // 32 Bytes
            _LDA_STATUS     LDA;                            // 20 Bytes
            uint16_t status_id;
            uint16_t status_sub_id;
        };
    };
} _STATUS_BUFFER;

/******************************************************************************/
typedef struct
{
    uint16_t Position;
    uint16_t Amplitude;
    uint16_t FWHM;
    uint16_t Minimum[2];
}_PEAK;

/******************************************************************************/
typedef struct
{
    uint16_t        Scans;                                          // 2 Bytes
    uint16_t        Count;                                          // 2 Bytes
    _PEAK           Peak[PDAB_MAX_PEAKS];                           // 40 Bytes (10 Bytes per peak))
    float           Separation[PDAB_MAX_SEPARATIONS];               // 12 Bytes
    float           Thickness[PDAB_MAX_SEPARATIONS];                // 12 Bytes
    float           Precision[PDAB_MAX_SEPARATIONS];                // 12 Bytes
}_MEASUREMENT;                                                      // 80 Bytes

/******************************************************************************/
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
}_SCAN_STATUS;                                                      // 28 Bytes

/******************************************************************************/
typedef struct
{

    union       // Header
    {
        uint8_t      Bytes[PDAB_HEADER_LENGTH_8];                   // 112 Bytes
        struct
        {
            _SCAN_STATUS        Status;                             // 28 Bytes
            _MEASUREMENT        Measurement;                        // 80 Bytes
            
            uint16_t            Offset;                             // 2 Bytes
            uint16_t            DC_Level;                           // 2 Bytes
            uint16_t            Blocks;                             // 2 Bytes            
            bool                Valid;                              // 1 Byte
            bool                Complete;                           // 1 Byte
            uint8_t             device_name[16];                    // 16 Byte
            uint32_t            scans_counter;                        // 4 Byte
            
            uint16_t            Scan_data_checksum;
        };
    };
}_SCAN_HEADER;                                                      // 136 Bytes

/******************************************************************************/
typedef struct
{
    union
    {
        uint8_t Buffer[PDAB_DATA_LENGTH_8];
        struct
        {
            _SCAN_HEADER    Header;   
           
            union       // Data
            {
                uint16_t    Data[PDAB_SCAN_LENGTH_16]; 
                uint16_t    Words[PDAB_SCAN_LENGTH_16]; 
                uint8_t     Bytes[PDAB_SCAN_LENGTH_8];
            };
        };
    };
} _SCAN_BUFFER;

typedef struct
{
    uint16_t Data[PDAB_NPDA_BUFFER_LENGTH];
} _NPDA_SCAN;

typedef struct
{
    _NPDA_SCAN   Scans[PDAB_NPDA_SCANS];
    uint16_t     Positions[PDAB_NPDA_SCANS];
    uint16_t     DC_Level[PDAB_NPDA_SCANS];
} _NPDA_SCAN_BUFFER;

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

#define SETTINGS_STRUCTURE_SIZE 32U
typedef struct device_settings
{

    union{
        uint8_t Bytes[SETTINGS_STRUCTURE_SIZE];
        struct{
            uint16_t LCD_BRIGHTNESS;
            uint16_t LED_BRIGHTNESS;
            uint16_t LED_FADE_RATE;
            uint16_t VOLTAGE_TRESHOLD;//VREF
            uint16_t P1_TRESHOLD;
            uint16_t P2_TRESHOLD;
            uint16_t MIN_SEPARATION;
            uint16_t MAX_SEPARATION;
            uint16_t MIN_FWHM;
            uint16_t MAX_FWHM;
            uint16_t CAMERA_HSTART;
            uint16_t CAMERA_VSTART;
            uint16_t MENU_LOCKED;
        };
    };
}DEVICE_SETTINGS_t;

typedef union {
    uint8_t Bytes[128];
    struct{
        DEVICE_SETTINGS_t settings;
        uint8_t device_name[17];
        uint8_t PDAB_build;
        uint8_t LSC_build;
        uint32_t scans_counter;
    };
}DEVICE_SETTINGS_FOR_PI_t;

typedef enum
{
    RESPONSE_NONE = 0,
    RESPONSE_PDAB_STATUS = 1,
    RESPONSE_SCAN_STATUS = 2,
    RESPONSE_SCAN = 3,
    RESPONSE_REQUEST_SHUTDOWN = 4,
    RESPONSE_SETTINGS = 5
} PDAB_RESPONSE;

//device statistic size must be below eeprom page - 1 (for CRC)
#define DEVICE_STATISTICS_SIZE 63U
typedef union
{
    uint8_t bytes[DEVICE_STATISTICS_SIZE];
    struct{
        uint32_t scans_counter;
        uint8_t filler[DEVICE_STATISTICS_SIZE-4];
    };
}DEVICE_STATISTICS_t;
extern DEVICE_STATISTICS_t device_statistics;
/******************************************************************************/




#ifdef	__cplusplus
}
#endif

#endif	/* PDAB_TYPES_H */

