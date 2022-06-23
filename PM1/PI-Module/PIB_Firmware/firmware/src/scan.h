/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    scan.h

  @Summary
    Scan functions.

  @Description
    Scanning.
 */
/* ************************************************************************** */

#ifndef _SCAN_H    /* Guard against multiple inclusion */
#define _SCAN_H


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "app.h"
#include "npda.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
//#define LOG_SCAN_TIMING    
//#define DEBUG_SCAN
    
#define MIN_SCAN_RANGE                  0U    
#define MAX_SCAN_RANGE                  5000U
#define TARGET_RANGE_MIN                1000U    
#define TARGET_RANGE_MAX                4000U    
    
#define SCAN_RESOLUTION                 1.000F
#define SCAN_ADC_CONVERSION             0.0000764F 
#define SCAN_REFRACTIVE_INDEX           1.3874F 
    
#define SCAN_FWD                        0U
#define SCAN_BCK                        1U

#define SCANS_PER_MEASUREMENT           100U                                    // Desired number of scans that make a measurement 
#define SCANS_PER_BLOCK                 10U                                     // Scans per block for NPDA processing
#define BLOCKS_PER_MEASURMENT           10U
    
#define SCAN_P1_THRESHOLD               2.000f 
#define SCAN_P2_THRESHOLD               0.200f       
#define SCAN_P3_THRESHOLD               0.200f 
#define SCAN_P4_THRESHOLD               0.200f 
    
#define SCAN_P1_MINIMUM                 1.000f 
#define SCAN_P2_MINIMUM                 0.100f    
    
#define SCAN_MIN_FWHM                   40.0f
#define SCAN_MAX_FWHM                   65.0f   

#define SCAN_MIN_SEPARATION             300.0f 
#define SCAN_MAX_SEPARATION             1000.0f       
    
#define CAMERA_CENTRE_X                 120U
#define CAMERA_CENTRE_Y                 120U    
#define CAMERA_ALIGNMENT_TOL            3U 
#define CAMERA_X_ALIGNMENT_MIN          CAMERA_CENTRE_X - CAMERA_ALIGNMENT_TOL       
#define CAMERA_X_ALIGNMENT_MAX          CAMERA_CENTRE_X + CAMERA_ALIGNMENT_TOL  
#define CAMERA_Y_ALIGNMENT_MIN          CAMERA_CENTRE_Y - CAMERA_ALIGNMENT_TOL       
#define CAMERA_Y_ALIGNMENT_MAX          CAMERA_CENTRE_Y + CAMERA_ALIGNMENT_TOL    
    
#define MAX_MEASUREMENT_COUNT           4U    
    
#define MEASUREMENT_DISPLAY_TIMEOUT_MIN 100U    
#define MEASUREMENT_DISPLAY_TIMEOUT     1000U     
#define MEASUREMENT_DISPLAY_TIMEOUT_MAX 6000U      
#define SCANNING_TIMEOUT                8000U 
#define SCANNING_STATUS_TIMEOUT         ( 10000U - SCANNING_TIMEOUT )
    
#define THICKNESS_MIN                   0.000f     
#define THICKNESS_STD_TARGET            5.000f    
#define THICKNESS_STD_MAX               10.000f      
#define THICKNESS_UM_SCALE              1U
    
#define PK1_THRESHOLD                   50U 
#define PK1_MIN_RADIUS                  10U
#define PK1_MAX_RADIUS                  60U  
#define PK1_MAX_DECENTRE                20U     
#define PK1_LINE_OFFSET                 4U 
#define PK1_TARGET_RADIUS               20U
#define PK1_RADIUS_TOLERANCE            2U     
    
#define PUPIL_ALIGNMENT_TOLERANCE       2U
#define PUPIL_ALIGNMENT_Y_OFFSET        -2L    
    
#define CIRCLE_FIT_MIN_POINTS           8U    
    
    
    
// *****************************************************************************
// Section: Data Types
// *****************************************************************************

    typedef struct
    {
        _NPDA_MEASUREMNT measurements[MAX_MEASUREMENT_COUNT];
        uint16_t measurement_index;
        
        uint16_t valid_blocks;
        uint16_t total_blocks;
        uint16_t z_position;
        
        uint16_t scan_progress;
        
        bool scanning;
        bool status_received;
        bool status_timer_elapsed;
        
        _SCAN_SETTINGS scan_settings;
        
        SYS_TIME_HANDLE scan_timer;
    
    } _SCAN_DATA;

typedef struct {
    bool fist_scan;
    float scan_time;
    float press_to_scan_time;
    uint32_t avg_Z;
    float avg_gain;
    float temperature;
    float temperature_high_peak;
    float temperature_low_peak;
    
    uint32_t number_of_stopped_scans;
    uint32_t number_of_started_scans;
    uint32_t last_number_of_presses_start;
    uint32_t last_number_of_presses_stop;
    uint32_t sum_scan_time;
    uint32_t sum_press_to_scan_time;
    uint32_t sum_avg_Z;
}usability_metrics_t;

extern usability_metrics_t usability_metrics;

// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void read_scan_settings(_SCAN_SETTINGS *scan_settings);    
    
void scan_reset(void);
bool scan_start(void);
void scan_stop(void);

void scan_update_progress(int clear);
uint16_t  scan_get_progress(void);
uint16_t scan_get_z_position(void);
uint32_t scan_get_elapsed_time(void);
uint8_t scan_get_remaining_time_percentage( void );
void scan_reset_measurement_index( void );
uint32_t scan_get_measurement_index( void );
_NPDA_MEASUREMNT* scan_get_measurement( uint8_t index );

bool scan_status_check(void);
void scan_header_received(_SCAN_HEADER* header);
void scan_process_measurements( uint16_t scans );

bool app_process_frame( bool en, _CIRCLE* circle );
bool app_find_pk1_image( bool enable, _CIRCLE* circle );
bool app_find_pupil( bool enable, _RECTANGLE* rectangle, _WINDOW* inner_boundary, _WINDOW* outer_boundary );

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _SCAN_H */

/* *****************************************************************************
 End of File
 */
