/******************************************************************************

 Company:   Lein Applied Diagnostics Limited
 Project:   ISCAN
 File Name: nvm.h   
 Processor: dsPIC33E
 Hardware:  EMC board
 Assembler: XC16-gcc
 Linker:    XC16-ld
 
 Description: 
 
 Functions: 
 
*******************************************************************************/

/*********************** Revision History **************************************
SI.NO   VER     AUTHOR                  CHANGE DESCRIPTION
1.      1.0     RPT                     Initial Version
*******************************************************************************/

#ifndef NVM_DRIVER_H
#define	NVM_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

/*******************************************************************************
                            Includes Files
*******************************************************************************/

#include <xc.h>
#include <libpic30.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
    
#include "mcc_generated_files/memory/flash.h"
/******************************************************************************
                            Typedefs
 ******************************************************************************/    
typedef enum {
    NVM_INITIALISE = 0,
    NVM_ERASE_PAGE,
    NVM_READ,
    NVM_WRITE            
} NVM_COMMANDS;

typedef enum {
    NVM_RTSP_ERROR = -1,
    NVM_NO_ERROR = 0,
    NVM_READ_ERROR,
    NVM_WRITE_ERROR,
    NVM_ERASE_ERROR,
    NVM_ADDR_ERROR,
    NVM_CMD_ERROR,        
    NVM_INIT_ERROR          
} NVM_ERRORS;

typedef struct {
   bool             nvmInitialised;                            // NVM initialisation flag 
   bool             nvmError;                                  // NVM error flag  
   uint32_t         nvmAdr;                                    // Selects the location to read in program flash memory
   uint32_t         nvmSize;                                   // holds the memory size  
   NVM_ERRORS       nvmErrorCode;                              // NVM error code    
   NVM_COMMANDS     nvmCommand;
   NVM_COMMANDS     nvmlastCommand;
} __NVM_DATA;
/******************************************************************************
                        Global Definitions
 ******************************************************************************/
#define NVM

#define FLASH_INIT_VALUE        0x0000

#define FLASH_ROWS_PER_PAGE     FLASH_ERASE_PAGE_SIZE_IN_INSTRUCTIONS / FLASH_WRITE_ROW_SIZE_IN_INSTRUCTIONS


/*******************************************************************************
                            Macros
*******************************************************************************/
#define PM_ROW __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)))
/*******************************************************************************
                            Global Variables
*******************************************************************************/

/*******************************************************************************
                            Function Prototypes 
 ******************************************************************************/
bool __attribute__((noinline)) nvmCtl( uint16_t nvmcmd, uint16_t* srcptr, uint16_t* destptr );
int16_t nvmGetError( void );
/******************************************************************************/
#ifdef __cplusplus  // Provide C++ Compatibility
}
#endif

#endif	/* NVM_DRIVER_H */
/*******************************************************************************
 End of File
 */
