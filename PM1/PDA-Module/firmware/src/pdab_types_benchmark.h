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
#define PDAB_HEADER_LENGTH_8       128U                                                // Length of scan status buffer (in bytes))
/******************************************************************************/
#define PDAB_TOTAL_SCAN_BUFFERS    2U
/******************************************************************************/     
#define PDAB_SCAN_LENGTH_8         ( PDAB_SCAN_LENGTH_16 * 2U )                       // Number of samples per scan (in 16 bit words)   
#define PDAB_STATUS_LENGTH_16      ( PDAB_STATUS_LENGTH_8 / 2U )                      // Length device status buffer (in 16 bit words)    
#define PDAB_HEADER_LENGTH_16      ( PDAB_HEADER_LENGTH_8 / 2U )                      // Length of scan status buffer (in 16 bit words)
#define PDAB_DATA_LENGTH_8         ( PDAB_SCAN_LENGTH_8 + PDAB_HEADER_LENGTH_8 )      // Scan Data length (in Words) of a scan from channel 1 
#define PDAB_DATA_LENGTH_16        ( PDAB_SCAN_LENGTH_16 + PDAB_HEADER_LENGTH_16 )    // Scan Data length (in Words) of a scan from channel 1                                                                                        // and channel 2. Must be divisible by 64           
/******************************************************************************/
#define PDAB_IGNORE_INIT_SCANS      10
#define PDAB_MAX_PEAKS              4
#define PDAB_MAX_SEPARATIONS        PDAB_MAX_PEAKS - 1U
/******************************************************************************/
#define PDAB_NPDA_BUFFER_LENGTH     1000U
#define PDAB_NPDA_SCANS             100U 
#define PDAB_NPDA_BLOCK_SIZE        10U     
#define PDAB_NPDA_BLOCKS            ( PDAB_NPDA_SCANS / PDAB_NPDA_BLOCK_SIZE )
   
/******************************************************************************/    
#define MAKE_BUFFER_DMA_READY  __attribute__((coherent)) __attribute__((aligned(16))) 
    
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
        SET_POWER_ERROR,
            SET_POWER_INVALID_CHANNEL,            
        ADC_OFFSET_ERROR,
            ADC_INVALID_CHANNEL,            
        ZERO_OFFSET_ERROR
} PDAB_ERROR_CODES;

/******************************************************************************/
typedef union
{
    uint8_t      Byte[2];
    uint16_t     Word;
    struct
    {           
        uint16_t CHRG:1;
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
        uint16_t :2;
    };
} _STATUS_FLAGS;                                        

/******************************************************************************/
typedef struct
{
    uint16_t    Version;                                // LSC firmware version 
    struct
    {
        uint32_t    Range;                              // LSC maximum scan range
        uint32_t    Length;                             // LSC data acquisition length    
        float       Frequency;                          // Drive frequency
    }Scan;                                              // 8 Bytes    

    int32_t    Position;                                // Current stage position
    int32_t    RefPositions[LRS_POLE_BOUNDARIES];       // Encoder Index Positions
    
} _LSC_STATUS;                                          // 32 Bytes

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
                uint8_t     Battery;
                uint8_t     Error;                
            } DAB;                                          // 2 Bytes    
 
            _LSC_STATUS     LSC;                            // 32 Bytes
            _LDA_STATUS     LDA;                            // 20 Bytes
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
        };
    };
}_SCAN_HEADER;                                                      // 116 Bytes

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
/******************************************************************************/

#ifdef	__cplusplus
}
#endif

#endif	/* PDAB_TYPES_H */

