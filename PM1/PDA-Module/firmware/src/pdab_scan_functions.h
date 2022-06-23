/******************************************************************************

 Company:   Occuity Limited
 Project:   pdab
 File Name: pdab_scan_functions.h
 Processor: PIC32MZ
 Hardware:  pdab Digital Board
 Assembler: XC32-gcc
 Linker:    XC32-ld
 
 Description: 
 
 Functions: 
 
*******************************************************************************/

/*********************** Revision History **************************************
SI.NO   VER     AUTHOR                  CHANGE DESCRIPTION
1.      1.0     RPT                     Initial Version
*******************************************************************************/

#ifndef _SCAN_FUNCTIONS_H
#define _SCAN_FUNCTIONS_H

/*******************************************************************************
                            Includes Files
*******************************************************************************/
#include "definitions.h"
#include "maths_library.h"
#include "scan_processing.h"
#include "pic_comms.h"
#include "debug.h"


#include <math.h>
/*******************************************************************************
                            Typedefs
*******************************************************************************/
typedef enum
{
	SCAN_IDLE=0,
    SCAN_INITIALISE, 
    SCAN_WAIT_FOR_ZERO,
    SCAN_START_SCANNING,        
    SCAN_SCANNING,  
    SCAN_PROCESS_DATA,       
    SCAN_TRANSMIT_DATA_UART,     //6 
    SCAN_TRANSMIT_DATA_USB, //7
    SCAN_SETUP_BUFFER,        
    SCAN_STOP_SCANNING,  
    SCAN_WAIT_FOR_STOP, //10
    SCAN_PROCESS_MEASUREMENT,    //11        
    SCAN_COMPLETE,
    SCAN_ERROR,
    SCAN_RECOVER_USB
} SCAN_STATES;



typedef struct
{
//*********************** State Machine Section ******************************//   
    
    /* Application states*/
    SCAN_STATES state;
    SCAN_STATES previous_state;
 
     /* Error code should an error occur*/
    uint16_t error;   
    
    uint32_t    data_length;   
    uint32_t    scan_length;   
    
    uint32_t    dma_length; 
    void*       dma_source;
    void*       dma_destination;
    
    _SCAN_BUFFER* scan_processing_buffer;
    _SCAN_BUFFER* scan_buffer;
    _NPDA_SCAN_BUFFER* npda_scan_buffer;
    
    _SCAN_SETTINGS scan_settings;   
    
    uint8_t       scan_buffer_index;   
    bool          scan_buffer_initialised;    
//*************************** Data Section ************************************//   
    bool        scanning;
    bool        stop_scanning;
    bool        acquisition_complete;
    
    bool        collect_block;
    uint16_t    block_count;
    uint16_t    block_scan_count;
    uint16_t    npda_scan_count;
    
    uint16_t    scan_count; 
    uint16_t    scan_valid_count;
    uint16_t    scans_to_collect;
    
    double      scanRate;

    double      measurement_time;
    double      average_scan_time;
    uint32_t    scan_time;
    uint32_t    scan_start_time;
    uint32_t    scan_stop_time;
    
    COMM_STATES comm_interface;

    uint16_t cmp_index;
    uint8_t auto_gain_scan_count;
    double auto_gain_current_gain;
    bool skip_scan;

    _NPDA_SCAN* preselection_scan;
} SCAN_DATA;

/*******************************************************************************
                        Global Definitions
*******************************************************************************/

/*******************************************************************************
                            Macros
*******************************************************************************/
#define MAKE_BUFFER_DMA_READY  __attribute__((coherent)) __attribute__((aligned(16))) 
/*******************************************************************************
                            Global Variables
*******************************************************************************/

/*******************************************************************************
                            Function Prototypes 
*******************************************************************************/
uint8_t* get_npda_buffer_ptr( void );

void Scan_Initialise(void);
void Scan_CMP1_Interrupt_Handler(uintptr_t context);
void Scan_CN_Interrupt_Handler(GPIO_PIN pin, uintptr_t context);
void Scan_DMA_Interrupt_Handler(SYS_DMA_TRANSFER_EVENT event, uintptr_t context);
void Scan_Timer_Initialise(void);
void Scan_Timer_Start(void);
void Scan_Timer_Stop(void);
void Scan_Timer_Report(void);
void Scan_Buffer_Setup(void);
void Scan_Start(void);
void Scan_Stop(void);
bool Scan_Busy(void);
bool Scan_Check_DMA(void);
void Scan_Append_Measurement(_MEASUREMENT * measurement);
void Scan_Append_Status(_SCAN_STATUS* status);
SCAN_STATES Scan_Tasks(void);
void Scan_Set_Dac_Zero_For_Gain(uint16_t, uint8_t);
double Scan_Idx_To_Gain(uint8_t);
void update_scan_settings(void);

bool Start_Scanning(COMM_STATES interface);
void Stop_Scanning(void);

void Process_Valid_Measurement( _MEASUREMENT* measurement,  _SCAN_SETTINGS* settings );

#endif /* _SCAN_FUNCTIONS_H */
/*******************************************************************************
 End of File
 */
