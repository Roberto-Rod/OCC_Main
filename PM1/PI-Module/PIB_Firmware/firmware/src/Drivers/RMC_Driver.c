/******************************************************************************

 Company:   Lein Applied Diagnostics Limited
 Project:   ISCAN
 File Name: RMC_Driver.c   
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


/*******************************************************************************
                            Includes Files
*******************************************************************************/
#include "RMC_Driver.h"

/*******************************************************************************
                            Global Variables
*******************************************************************************/

/*******************************************************************************
 * Function:        bool WriteRMCCommand( uint8_t command, uint16_t len, uint8_t *buffer )
 *
 * Precondition:    None
 *
 * Input:           uint8_t command 
 *                  uint16_t len 
 *                  uint8_t *buffer
 *
 * Output:          none
 *
 * Returns:         false if successful
 *
 * Side Effects:    None.
 *
 * Overview:        This function writes the respective command to the RMC device 
 *                  on the SPI bus
 *
 * Notes:           None
 ******************************************************************************/    
uint16_t WriteRMCCommand( uint8_t command, uint16_t len, uint8_t *buffer )
{
    uint16_t rmc_error = RMC_NO_ERROR;    
    RMC_SS = false;    // Enable slave select pin
    
    if( ( len > 0U ) && ( buffer == NULL ) )
    {
        rmc_error = RMC_POINTER_ERROR;
    }
    else
    {
        // Write the command to the RMC device on SPI bus
        if( !SPI_WriteBytes( RMC_PORT, &command, 1U, true) )
        {
            rmc_error = RMC_WRITE_ERROR;
        }
        else if( len > 0U )
        {
            uint16_t i;

            for( i = 0U; i < len; i++ )
            {  
                // Write the buffer values
                if( !SPI_WriteBytes( RMC_PORT, buffer++, 1U, true ) )
                {
                    rmc_error = RMC_WRITE_ERROR;
                    break;
                }         
            }     
        }        
    }

    RMC_SS = true;         // Disable slave select   
    return rmc_error;      
}
/*******************************************************************************
 * Function:        bool ReadRMCData( uint8_t command, uint16_t len, uint8_t *buffer )
 *
 * Precondition:    None
 *
 * Input:           uint8_t command 
 *                  uint16_t len 
 *                  uint8_t *buffer
 *
 * Output:          None
 *
 * Returns:         true if successful and false otherwise
 *
 * Side Effects:    Incorrect position read can lead to errors in scan positions
 *
 * Overview:        Reads the data from RMC device on SPI bus
 *
 * Notes:           None
 ******************************************************************************/    
uint16_t ReadRMCData( uint8_t command, uint16_t len, uint8_t *buffer )
{
    uint16_t rmc_error = RMC_NO_ERROR;
    RMC_SS = false;    // Enable slave select

    if( ( len > 0U ) && ( buffer == NULL ) )
    {
        rmc_error = RMC_POINTER_ERROR;
    }
    else
    {    
        // Write the respective command to the RMC device on SPI bus
        if( !SPI_WriteBytes( RMC_PORT, &command, 1U, true ) )
        {
            rmc_error = RMC_WRITE_ERROR;
        }
        else if( len > 0U )
        {
            uint16_t i;

            for( i = 0U; i < len; i++ )
            {
                // Read the respective RMC registers 
                if( !SPI_ReadBytes( RMC_PORT, buffer++, 1U, true ) )
                {
                    rmc_error = RMC_READ_ERROR;                // If unsuccessful return false
                    break;
                }             
            }
        }    
    }

    RMC_SS = true;         // Disable slave select   
    return rmc_error;
}
/*******************************************************************************
 * Function:        uint16_t RMC_Initialise( void )
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         Non-zero value if an error occured
 *
 * Side Effects:    Call the RMC initialisation sequence
 *
 * Overview:        Call the RMC initialisation sequence
 *
 * Notes:           None
*******************************************************************************/ 
uint16_t InitialiseRMC( void )
{
    uint16_t rmc_error = RMC_NO_ERROR;
    uint32_t rmc_range = 0L;
    
    if( WaitRMC() > RMC_NO_ERROR )                                              // Wait for RMC to initialise
    {
        rmc_error = RMC_INIT_TIMEOUT;
    }
    else
    {
        // Initialise the RMC
        if( WriteRMCCommand(RMC_DEFINE_LIMITS, 0, 0 ) )
        {
            rmc_error = RMC_WRITE_ERROR;  
        }
        else
        {
            DelayMs(1000);
            
            if( WaitRMC() > RMC_NO_ERROR )
            {
                rmc_error = RMC_INIT_TIMEOUT;
            }

            if( rmc_error == RMC_NO_ERROR )
            {   
                if( ReadRMCData( RMC_GET_RANGE, 4, (uint8_t*) &rmc_range ) ){
                    rmc_error = RMC_READ_ERROR;        
                }
                else
                {
                    if( ( rmc_range < RMS_RANGE_MIN ) || ( rmc_range > RMS_RANGE_MAX ) )
                        rmc_error = RMC_SCAN_RANGE_ERROR;
                }
            }
        }
    }
        
    return rmc_error;
}
/*******************************************************************************
* Function:        bool WaitRMC( void )
*
* Precondition:    None
*
* Input:           None
*
* Output:          None
*
* Returns:         Non zero value returned if an error occured
*
* Side Effects:    None
*
* Overview:        Wait for RMC to complete current task.
*
* Notes:           None
*******************************************************************************/ 
uint16_t WaitRMC( void )
{
    uint16_t rmc_timeout = RMC_TIMEOUT;  
    uint16_t rmc_error = RMC_NO_ERROR;
    
    while( IsRMCBusy() )
    {
        rmc_timeout = rmc_timeout - 1;

        if( rmc_timeout <= 0U )
        {
            rmc_error = RMC_TIMEOUT;
            break;
        }

        DelayMs( 1 );
    }    
    
    return rmc_error;
}
/*******************************************************************************
* Function:        bool IsRMCBusy( void )
*
* Precondition:    None
*
* Input:           None
*
* Output:          None
*
* Returns:         True if busy, false if idle. 
*
* Side Effects:    None
*
* Overview:        Returns the state of the RMC_BUSY pin.
*
* Notes:           None
*******************************************************************************/ 
bool IsRMCBusy( void )
{
    return !RMC_BUSY;
}
/*******************************************************************************
 End of File
 */
	
 
