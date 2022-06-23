/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    scan_processing.h

  @Summary
    Scan processing functions.

  @Description
    Routines called to process the results from a scan.
 */
/* ************************************************************************** */

#ifndef _SCAN_PROCESSING_H    /* Guard against multiple inclusion */
#define _SCAN_PROCESSING_H


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "pdab.h"
#include "maths_library.h"
// #include "scan_processing.h"
#include <math.h>
#include "pdab_scan_functions.h"
/* ************************************************************************** */
/* Section: Calibration files                                                        */
/* ************************************************************************** */

extern uint8_t device_id;
extern float cal_data[PDAB_SCAN_LENGTH_16];

/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */

//#define P2_FWHM_SELECTION

#define SCAN_VOLTAGE_REF        12u

#define SCAN_PEAKS              2U
#define SCAN_PEAK_1             0U
#define SCAN_PEAK_2             1U
#define SCAN_LENGTH             5000U
#define SCAN_PF_WINDOW          200U
#define SCAN_FILTER_WINDOW      1000U
#define SCAN_PF_WINDOW_MIN      SCAN_PF_WINDOW 
#define SCAN_PF_WINDOW_MAX      (SCAN_LENGTH - SCAN_FILTER_WINDOW + SCAN_PF_WINDOW)
#define SCAN_FILTER_WIDTH       8U
#define SCAN_FILTER_PASSES      2U
#define SCAN_REFRACTIVE_INDEX   1.3989F                 // 1.000 to use compensation elsewhere, 1.3989 for the cornea, 1.4738 for false eye, 1.448 for Quartz @ 1310nm       
#define SCAN_RESOLUTION         0.001F
#define SCAN_P1_THRESH          30000U                  // Peak 1 threshold
#define SCAN_P2_THRESH          300U                    // Peak 2 threshold
#define SCAN_SATURATION_LIMIT   65500U

#define SCAN_LOW_SEP_THRESH     300U
#define SCAN_HIGH_SEP_THRESH    700U
    
#define SCAN_LOW_FWHM_THRESH    40U
#define SCAN_HIGH_FWHM_THRESH   70U    

#define SCAN_DC_AVERAGE         64U                     // Number of points to average at the begining of the scan to determine the DC offset
// *****************************************************************************
// Section: Data Types
// *****************************************************************************


// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

bool Find_Peaks_NPDA( _SCAN_HEADER* header, uint16_t* data, _SCAN_SETTINGS* settings );
bool Truncate_Data( _SCAN_BUFFER*, _NPDA_SCAN_BUFFER*, _NPDA_SCAN*, uint16_t );
uint16_t Find_FWHM( uint16_t* data, uint16_t length, uint16_t position, uint16_t amplitude );
bool MAV_Filter( uint16_t* data, uint16_t length, uint16_t width, uint16_t passes, bool direction );
bool Scan_Selection( _MEASUREMENT* measurement, _SCAN_SETTINGS* settings );


#endif /* _SCAN_PROCESSING_H */

/* *****************************************************************************
 End of File
 */
