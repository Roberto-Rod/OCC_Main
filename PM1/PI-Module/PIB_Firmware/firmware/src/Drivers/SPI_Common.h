/******************************************************************************

 Company:   Lein Applied Diagnostics Limited
 Project:   
 File Name: SPI_Common.h   
 Processor: PIC32MZ (Harmony V1.07)
 Hardware:  N/A
 Assembler: XC32-gcc
 Linker:    XC32-ld
 
 Description: 
 
 Functions: 
 
*******************************************************************************/

/*********************** Revision History **************************************
SI.NO   VER     AUTHOR                  CHANGE DESCRIPTION
1.      1.0     RPT                     Initial Version
*******************************************************************************/

#ifndef SPI_COMMON_H
#define SPI_COMMON_H

/*******************************************************************************
                            Includes Files
*******************************************************************************/
#include <xc.h>
#include <stddef.h>
#include <stdlib.h>
#include "driver/spi/drv_spi.h"
#include "driver/spi/static/drv_spi_static.h"
#include "Delay.h"
/*******************************************************************************
                            Macros
*******************************************************************************/
#define MAX_SPI_INSTANCES   2
#define SPI_FIFO_SIZE       8

typedef uintptr_t SPI_DRIVER_HANDLE;
typedef uintptr_t SPI_BUFFER_HANDLE;

typedef union SPIBuffer 	
{
    uint8_t 	Byte[10];
    uint16_t 	Short[5];	
    
}SPIBuffer;  
        
typedef struct
{  
    SPI_DRIVER_HANDLE               drvSPIHandle[MAX_SPI_INSTANCES];   
    SPI_BUFFER_HANDLE               drvSPITxRxBufferHandle[MAX_SPI_INSTANCES];     
    DRV_SPI_BUFFER_EVENT            drvSPIStatus[MAX_SPI_INSTANCES];
    
}SPIHandles;
/*******************************************************************************
                              Variables
*******************************************************************************/

/*******************************************************************************
                           Function Prototypes
*******************************************************************************/
bool SPI_Initialise( uint8_t instance ); 
bool SPI_WriteBytes( uint8_t instance, void* odata, uint32_t olen, bool wait );
bool SPI_ReadBytes( uint8_t instance, void* idata, uint32_t ilen, bool wait );
bool SPI_WriteReadBytes( uint8_t instance, void* odata, uint32_t olen, void* idata, uint32_t ilen );

//*****SPI Callback function prototypes*****//
DRV_SPI_BUFFER_EVENT SPI_Check_Transfer_Status( SPI_DRIVER_HANDLE drvHandle, DRV_SPI_BUFFER_HANDLE bufferHandle );

#endif
/** EOF SPI_Common.h ***************************************************************/