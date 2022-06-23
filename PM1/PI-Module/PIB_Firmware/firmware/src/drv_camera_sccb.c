
/*******************************************************************************
 OVM7692 Camera Driver Implementation.

  File Name:
    drv_camera_sccb.c

  Summary:
    OVM7692 camera sccb bus driver.

  Description:
    
 ******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2019 released Occuity Limited.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 ******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "drv_camera_sccb.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Local prototypes
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Camera SCCB Driver Interface Implementations
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
*    Function Name:  SCCB_Initialize
*    Description:    
*    Parameters:     
*    Return Value: 
*******************************************************************************/

void SCCB_Initialize(void)
{
    PMD5bits.I2C1MD = 0;
    /* Disable the I2C Master interrupt */
    IEC3bits.I2C1MIE = false;
            
    /* Disable the I2C Bus collision interrupt */
    IEC3bits.I2C1BIE = false;
   
    //I2C1BRG = 118;      // 400000 kHz
    I2C1BRG = 98; // 98 - averages @ 396kHz measured
    
    I2C1CON = 0;
    I2C1CONbits.SIDL = false;
    I2C1CONbits.DISSLW = true;
    I2C1CONbits.SMEN = true;

    /* Initialize master interrupt */
    IFS3bits.I2C1MIF = false;
    IEC3bits.I2C1MIE = false;

    /* Initialize fault interrupt */
    IFS3bits.I2C1BIF = false;
    IEC3bits.I2C1BIE = false;

    /* Turn on the I2C module */
    I2C1CONbits.ON = true;  
}
/*******************************************************************************
*    Function Name:  SCCB_Write_Byte
*    Description:    This routine is used to write a byte to the I2C bus.
*                    The input parameter data_out is written to the
*                    I2CTRN register. If IWCOL bit is set,write collision
*                    has occured and -1 is returned, else 0 is returned.
*    Parameters:     uint8_t : data_out
*    Return Value:   char
*******************************************************************************/

SCCB_STATUS SCCB_Write_Byte( uint8_t data )
{
    I2C1TRN = data;

    if(I2C1STATbits.IWCOL)        /* If write collision occurs,return -1 */
        return SCCB_BUS_COLLISION;
    else
	{
		while( I2C1STATbits.TRSTAT );   // wait until write cycle is complete         

		if ( I2C1STATbits.ACKSTAT ) // test for ACK condition received
             return ( SCCB_ACK_ERROR );
        else 
			return SCCB_WRITE_COMPLETE;              
    }
}
/************************************************************************
*    Function Name:  SCCB_Idle
*    Description:    This routine generates wait condition intil I2C
*                    bus is Idle.
*    Parameters:     void
*    Return Value:   void
*************************************************************************/

void SCCB_Idle(void)
{
    /* Wait until I2C Bus is Inactive */
    while( I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RSEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT );
}

/******************************************************************************
*    Function Name:  SCCB_Read_Byte
*    Description:    This routine reads a single byte from the I2C Bus.
*                    To enable master receive,RCEN bit is set.
*                    The RCEN bit is checked until it is cleared.When cleared,
*                    the receive register is full and it's contents are returned.
*    Parameters:     void
*    Return Value:   uint8_t
********************************************************************************/

SCCB_STATUS SCCB_Read_Byte( uint8_t* data )
{
    I2C1CONbits.RCEN = 1;
    while(I2C1CONbits.RCEN);
    I2C1STATbits.I2COV = 0;
    *data = I2C1RCV;
    
    I2C1CONbits.ACKDT = true;
    I2C1CONbits.ACKEN = true;    
    SCCB_Idle();
    
    return SCCB_READ_COMPLETE;
}

/******************************************************************************
*    Function Name:  SCCB_Start
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
SCCB_STATUS SCCB_Start( void )
{
    I2C1CONbits.SEN = true;
    SCCB_Idle();
    
    // Check for collisions
	if(I2C1STATbits.BCL)
    {
		return SCCB_BUS_COLLISION; 
    }
	else
    {
		return SCCB_START_COMPLETE;
    }
}
/******************************************************************************
*    Function Name:  SCCB_Start
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
SCCB_STATUS SCCB_Restart( void )
{
    I2C1CONbits.RSEN = true;
    SCCB_Idle();
    
    // Check for collisions
	if(I2C1STATbits.BCL)
    {
		return SCCB_BUS_COLLISION; 
    }
	else
    {
		return SCCB_START_COMPLETE;
    }	
}
/******************************************************************************
*    Function Name:  SCCB_Stop
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
SCCB_STATUS  SCCB_Stop( void )
{
    I2C1CONbits.PEN = true;
    SCCB_Idle();
    
    return SCCB_STOP_COMPLETE;
}

/*******************************************************************************
*    Function Name:  SCCB_Write
*    Description:   
*    Parameters:     
*    Return Value:  
*******************************************************************************/

SCCB_STATUS SCCB_Write( uint8_t addr, uint8_t reg, uint8_t byte )
{
    SCCB_Idle();
    SCCB_Start();
    
    if( SCCB_Write_Byte( ( addr << 1 ) | 0x00 ) == SCCB_WRITE_COMPLETE )
    {
        if( SCCB_Write_Byte( reg ) == SCCB_WRITE_COMPLETE )   
        {
            if( SCCB_Write_Byte( byte ) == SCCB_WRITE_COMPLETE )   
            {
                SCCB_Stop();
                return SCCB_WRITE_COMPLETE;
            }            
        }
    }

    SCCB_Stop();    
    return SCCB_WRITE_ERROR;
}

/*******************************************************************************
*    Function Name:  SCCB_Read
*    Description:   
*    Parameters:     
*    Return Value:  
*******************************************************************************/

SCCB_STATUS SCCB_Read( uint8_t addr, uint8_t reg, uint8_t* byte )
{
    SCCB_Idle();
    SCCB_Start();
    
    if( SCCB_Write_Byte( ( addr << 1 ) | 0x00 ) == SCCB_WRITE_COMPLETE )
    {
        if( SCCB_Write_Byte( reg ) == SCCB_WRITE_COMPLETE )   
        {
            SCCB_Restart(); 
            
            if( SCCB_Write_Byte( ( addr << 1 ) | 0x01 ) == SCCB_WRITE_COMPLETE )
            {    
                if( SCCB_Read_Byte( byte ) == SCCB_READ_COMPLETE )   
                {
                    SCCB_Stop();                
                    return SCCB_READ_COMPLETE;
                }      
            }
        }
    }

    SCCB_Stop();    
    return SCCB_READ_ERROR;
}