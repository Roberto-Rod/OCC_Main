/******************************************************************************

 Company:   Lein Applied Diagnostics Limited
 Project:   ISCAN
 File Name: RMC_Driver.h   
 Processor: PIC32MZ
 Hardware:  ISCAN Digital Board
 Assembler: XC32-gcc
 Linker:    XC32-ld
 
 Description: 
 
 Functions: 
 
*******************************************************************************/

/*********************** Revision History **************************************
SI.NO   VER     AUTHOR                  CHANGE DESCRIPTION
1.      1.0     RPT                     Initial Version
*******************************************************************************/

#ifndef RMC_DRIVER_H
#define RMC_DRIVER_H

/*******************************************************************************
                            Includes Files
*******************************************************************************/

#include <xc.h>
#include <stddef.h>
#include <stdlib.h>

#include "Delay.h"
#include "SPI_Common.h"

/******************************************************************************
                            Typedefs
 ******************************************************************************/
typedef enum
{
    RMC_GET_VERSION = 1,    
    RMC_INITIALISE,   
    RMC_NSCANS,
    RMC_GET_START_VOLT, // Not used for LRA
    RMC_SET_VEL,        // Not used for LRA			
    RMC_GET_VEL,        // Not used for LRA					
    RMC_GET_POSITION,	 			 		
    RMC_SET_V_KP,	    // Not used for LRA	 			
    RMC_SET_V_KI,       // Not used for LRA		 			
    RMC_SET_V_KD,       // Not used for LRA		 		
    RMC_SET_V_IL,       // Not used for LRA	
    RMC_SET_P_KP,       // Not used for LRA		 			
    RMC_SET_P_KI,       // Not used for LRA		 			
    RMC_SET_P_KD,       // Not used for LRA		 		
    RMC_SET_P_IL,       // Not used for LRA            
    RMC_START_SCANNING,
    RMC_STOP_SCANNING,
    RMC_GET_RANGE,
    RMC_DEFINE_LIMITS,            
    RMC_SET_FREQ,       // Not used for RMC
    RMC_GET_FREQ,       // Not used for RMC        
    RMC_GET_OFFSET,     // Not used for RMC 
    RMC_GET_REF_POS,
    RMC_TEST = 254,     // Debug Only
    RMC_RESET = 255   
} RMC_COMMANDS;

typedef enum
{
    RMC_NO_ERROR = 0,
    RMC_IDLE,
    RMC_BUSY,
    RMC_POINTER_ERROR,        
    RMC_GENERAL_ERROR,                
    RMC_READ_ERROR,          
    RMC_WRITE_ERROR,         
    RMC_CAM_RADIUS_ERROR,        
    RMC_SCAN_RANGE_ERROR,   
    RMC_INIT_TIMEOUT,  
    RMC_TIMEOUT
} RMC_STATES;

/******************************************************************************
                        Global Definitions
 ******************************************************************************/
// DSPIC I/O Lines
#define RMC_SCK     LATDbits.LATD15    
#define RMC_SDI     LATDbits.LATD9
#define RMC_SDO     PORTGbits.RG9    
#define RMC_SS      LATBbits.LATB8
    
#define RMC_BUSY    PORTBbits.RB12
#define RMC_DIR     PORTDbits.RD14 

#define RMC_PORT    DRV_SPI_INDEX_0

/******************************************************************************/
#define NO_MAX_LIMIT

#define RMC_TIMEOUT 60000L

#define RMS_RANGE 5200L
#define RMS_RANGE_TOL 200L

#define RMS_RANGE_MIN ( RMS_RANGE - RMS_RANGE_TOL )

#ifdef NO_MAX_LIMIT
#define RMS_RANGE_MAX 10000L
#else
#define RMS_RANGE_MAX ( RMS_RANGE + RMS_RANGE_TOL )
#endif

#define RMS_RADIUS 41000L
#define RMS_RADIUS_TOL 1000L

#define RMS_RADIUS_MIN ( RMS_RADIUS - RMS_RADIUS_TOL )
#define RMS_RADIUS_MAX ( RMS_RADIUS + RMS_RADIUS_TOL )
/*******************************************************************************
                            Macros
*******************************************************************************/

/*******************************************************************************
                            Global Variables
*******************************************************************************/

/*******************************************************************************
                            Function Prototypes 
 ******************************************************************************/
uint16_t WriteRMCCommand( uint8_t command, uint16_t len, uint8_t *buffer );
uint16_t ReadRMCData( uint8_t command, uint16_t len, uint8_t *buffer );
uint16_t InitialiseRMC( void ); 
uint16_t WaitRMC( void );
bool     IsRMCBusy( void );

#endif /* _RMC_DRIVER_H */
/*******************************************************************************
 End of File
 */
