/******************************************************************************

 Company:   Lein Applied Diagnostics Limited
 Project:   ISCAN
 File Name: nvm.c   
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


/*******************************************************************************
                            Includes Files
*******************************************************************************/
#include "NVM_Driver.h"

/*******************************************************************************
                            Global Variables
*******************************************************************************/
static __NVM_DATA nvmData;
const uint16_t PM_ROW nvmFlash[FLASH_ERASE_PAGE_SIZE_IN_INSTRUCTIONS] = { FLASH_INIT_VALUE }; // Create flash storage array and initialise all values to zero
/*******************************************************************************
 * Function:        bool Nvm( uint16_t command, uint16_t* srcptr, uint16_t* destptr, uint16_t len )
 *
 * Precondition:    None
 *
 * Input:           uint16_t    command     NVM command
 *                  uint16_t*   srcptr      Pointer to source array for nvm writes
 *                  uint16_t*   destptr     Pointer to destination array for nvm reads
 *                  uint16_t    len         Length od data to written or read
 *
 * Output:          none
 *
 * Returns:         false if successful and true if an nvmData.nvmError occured
 *
 * Side Effects:    None.
 *
 * Overview:        This function manages nvm on the dsPIC33E devices.
 *
 * Notes:           None
 ******************************************************************************/    
bool __attribute__((noinline)) nvmCtl( uint16_t nvmcmd, uint16_t* srcptr, uint16_t* destptr )
{  
    volatile uint16_t __attribute__((aligned(FLASH_WRITE_ROW_SIZE_IN_PC_UNITS))) rambuffer[FLASH_WRITE_ROW_SIZE_IN_INSTRUCTIONS] = {0};             // Ram buffer for mirroring data stored in flash memory 
    
    nvmData.nvmCommand = nvmcmd;
    
    switch( nvmData.nvmCommand )
    {
        case NVM_INITIALISE:
            
            if( nvmFlash != NULL )
            {                  
                uint16_t flash_storage_adressdress = FLASH_GetErasePageAddress((uint16_t)nvmFlash);
                nvmData.nvmAdr = FLASH_GetErasePageAddress(flash_storage_adressdress);

                FLASH_Unlock(FLASH_UNLOCK_KEY);                
                
                nvmData.nvmInitialised = true;
                nvmData.nvmErrorCode = 0L;
            }
            else
            {
                nvmData.nvmErrorCode = NVM_INIT_ERROR;
                nvmData.nvmError = true;
                nvmData.nvmInitialised = false;
            }
            
            break;              
            
        case NVM_READ:
            
            if( ( destptr != NULL ) && ( nvmData.nvmInitialised != false ) )
            {
                int i;
                
                for( i = 0; i < FLASH_WRITE_ROW_SIZE_IN_INSTRUCTIONS; i++ )
                {
                    rambuffer[i] = FLASH_ReadWord16(nvmData.nvmAdr + (i << 1) );
                }      
                
                // Read the page and place the data into pageMirrorBuf array
                memcpy( (void*)destptr, (void*)rambuffer, FLASH_WRITE_ROW_SIZE_IN_PC_UNITS ); 
            }
            else
            {
                nvmData.nvmErrorCode = NVM_READ_ERROR;
                nvmData.nvmError = true;
            }             
                        
            break;            
            
             
        case NVM_WRITE:

            if( ( srcptr != NULL ) && ( nvmData.nvmInitialised != false ) && ( nvmData.nvmlastCommand == NVM_ERASE_PAGE ) )
            {
                memcpy( (void*)rambuffer, (void*)srcptr, FLASH_WRITE_ROW_SIZE_IN_PC_UNITS );
                
                if( !FLASH_WriteRow16(nvmData.nvmAdr, (uint16_t*)rambuffer) )
                {
                    nvmData.nvmErrorCode = NVM_WRITE_ERROR;
                    nvmData.nvmError = true;    
                }           
            }
            else
            {
                nvmData.nvmErrorCode = NVM_WRITE_ERROR;
                nvmData.nvmError = true;
            }
 
            break;
            
        case NVM_ERASE_PAGE:

            if( nvmData.nvmInitialised != false )
            {
                // Erase the page of flash at this address
                if( !FLASH_ErasePage(nvmData.nvmAdr) )
                {
                   nvmData.nvmErrorCode = NVM_ERASE_ERROR;
                   nvmData.nvmError = true;
                }           
            }
            else
            {
                nvmData.nvmErrorCode = NVM_ERASE_ERROR;
                nvmData.nvmError = true;
            }
            
            break;
            
        default:        
            nvmData.nvmErrorCode = NVM_CMD_ERROR;
            nvmData.nvmError = true;
            break;
    }
    
    nvmData.nvmlastCommand = nvmData.nvmCommand;
    
    if( nvmData.nvmErrorCode != NVM_NO_ERROR )
    {
        nvmData.nvmError = true;
    }
    
    return nvmData.nvmError;
}
/*******************************************************************************
 * Function:        int16_t nvmGetError( void )
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          none
 *
 * Returns:         NVM error code
 *
 * Side Effects:    None.
 *
 * Overview:        This function return the nvm error code
 *
 * Notes:           None
 ******************************************************************************/    
int16_t nvmGetError( void )
{  
    return nvmData.nvmErrorCode;
}
/*******************************************************************************
 End of File
 */
	
 

