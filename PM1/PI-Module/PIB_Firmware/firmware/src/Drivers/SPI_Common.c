/******************************************************************************

 Company:   Lein Applied Diagnostics Limited
 Project:   
 File Name: SPI_Common.c   
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

/*******************************************************************************
                            Includes Files
*******************************************************************************/

#include "SPI_Common.h"
/*******************************************************************************
                            Global Variables
*******************************************************************************/
SPIHandles     spiHandles;
SPIBuffer      spiBuffer;
/******************************************************************************
 * Function:        bool SPIInit( void )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:      	
 *
 * Note:            None
 *****************************************************************************/
bool SPI_Initialise( uint8_t instance )
{
    spiHandles.drvSPIHandle[instance] = DRV_SPI_Open( instance, DRV_IO_INTENT_READWRITE );

    if(spiHandles.drvSPIHandle[instance] != DRV_HANDLE_INVALID)
        return true;
    else
        return false;
}
/******************************************************************************
 * Function:        bool WriteBytes( uint8_t address, uint8_t* data, uint8_t len )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:      	
 *
 * Note:            None
 *****************************************************************************/
 bool SPI_WriteBytes( uint8_t instance, void* odata, uint32_t olen, bool wait )
 {  
    spiHandles.drvSPITxRxBufferHandle[instance] = DRV_SPI_BufferAddWrite(  spiHandles.drvSPIHandle[instance], odata, olen, 0, 0 );

    spiHandles.drvSPIStatus[instance] = DRV_SPI_BUFFER_EVENT_PENDING;
    
    if( wait )
    {    
        uint32_t timeout = 0;

        while( timeout++ < 1000 )
        {
            spiHandles.drvSPIStatus[instance] = SPI_Check_Transfer_Status(spiHandles.drvSPIHandle[instance], spiHandles.drvSPITxRxBufferHandle[instance]);

            if( spiHandles.drvSPIStatus[instance] == DRV_SPI_BUFFER_EVENT_ERROR )
                return false;
            else if( spiHandles.drvSPIStatus[instance] == DRV_SPI_BUFFER_EVENT_COMPLETE )
                return true;

            DelayUs( 1 );
        } 
    }
    else
        return true;
    
    return false;
 }
 /******************************************************************************
 * Function:        bool ReadBytes( uint8_t address, uint8_t* data, uint8_t len )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:      	
 *
 * Note:            None
 *****************************************************************************/
 bool SPI_ReadBytes( uint8_t instance, void* idata, uint32_t ilen, bool wait )
 {	
    spiHandles.drvSPITxRxBufferHandle[instance] = DRV_SPI_BufferAddRead(  spiHandles.drvSPIHandle[instance], idata, ilen, 0, 0 );  

    spiHandles.drvSPIStatus[instance] = DRV_SPI_BUFFER_EVENT_PENDING;
    
    if( wait )
    {
        uint32_t timeout = 0;

        while( timeout++ < 1000 )
        {
            spiHandles.drvSPIStatus[instance] = SPI_Check_Transfer_Status(spiHandles.drvSPIHandle[instance], spiHandles.drvSPITxRxBufferHandle[instance]);

            if( spiHandles.drvSPIStatus[instance] == DRV_SPI_BUFFER_EVENT_ERROR )
                return false;
            else if( spiHandles.drvSPIStatus[instance] == DRV_SPI_BUFFER_EVENT_COMPLETE )
                return true;       

            DelayUs( 1 );    
        } 
    }
    else
        return true;
        
    return false;   
 } 
 /******************************************************************************
 * Function:        bool SPI_WriteReadBytes( uint8_t instance, uint8_t address, uint8_t* odata, uint8_t olen, uint8_t* idata, uint8_t ilen )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:      	
 *
 * Note:            None
 *****************************************************************************/
 bool SPI_WriteReadBytes( uint8_t instance, void* odata, uint32_t olen, void* idata, uint32_t ilen )
 {	
    spiHandles.drvSPITxRxBufferHandle[instance] = DRV_SPI_BufferAddWriteRead(  spiHandles.drvSPIHandle[instance], odata, olen,  idata, ilen, 0, 0 );  

    spiHandles.drvSPIStatus[instance] = DRV_SPI_BUFFER_EVENT_PENDING;
    
    uint32_t timeout = 0;
        
    while( timeout++ < 1000 )
    {
        spiHandles.drvSPIStatus[instance] = SPI_Check_Transfer_Status(spiHandles.drvSPIHandle[instance], spiHandles.drvSPITxRxBufferHandle[instance]);
        
        if( spiHandles.drvSPIStatus[instance] == DRV_SPI_BUFFER_EVENT_ERROR )
            return false;
        else if( spiHandles.drvSPIStatus[instance] == DRV_SPI_BUFFER_EVENT_COMPLETE )
            return true;
        
        DelayUs( 1 );         
    } 
    
    return false;   
 } 
 /******************************************************************************
 * Function:        SPI_Check_Transfer_Status( SPI_DRIVER_HANDLE drvHandle, DRV_SPI_BUFFER_HANDLE bufferHandle )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          DRV_SPI_BUFFER_EVENT
 *
 * Side Effects:    None
 *
 * Overview:      	SPI_Check_Transfer_Status 
 *
 * Note:            Returns the status of Buffer operation from the driver; The spi can probe this function to see if the status of a particular SPI
 *                  transfer is in its execution
 *****************************************************************************/  
DRV_SPI_BUFFER_EVENT SPI_Check_Transfer_Status( SPI_DRIVER_HANDLE drvHandle, DRV_SPI_BUFFER_HANDLE bufferHandle )
{
    switch( drvHandle )
    {
        case DRV_SPI_INDEX_0:
            return ( DRV_SPI0_BufferStatus( bufferHandle ) );
            break;
            
//        case DRV_SPI_INDEX_1:
//            return ( DRV_SPI1_BufferStatus( bufferHandle ) );
//            break;
            
        default:
            return DRV_SPI_BUFFER_EVENT_ERROR;
            break;
    }
}
/** EOF SPI_Common.c ***************************************************************/  
