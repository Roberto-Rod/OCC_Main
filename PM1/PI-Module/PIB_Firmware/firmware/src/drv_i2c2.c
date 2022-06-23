/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_i2c2.c

  @Summary
    I2C driver for channel 2.

  @Description
    Driver.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "definitions.h"
#include "drv_i2c2.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*******************************************************************************
*    Function Name:  DRV_I2C2_Initialize
*    Description:    
*    Parameters:     
*    Return Value: 
*******************************************************************************/
void DRV_I2C2_Initialize(void)
{
    PMD5bits.I2C2MD = 0;
    /* Disable the I2C Master interrupt */
    IEC4bits.I2C2MIE = 0;

    /* Disable the I2C Bus collision interrupt */
    IEC4bits.I2C2BIE = 0;
   
    //I2C2BRG = 118;      // 400000 kHz //118 - averages @ 342kHz measured
    I2C2BRG = 98; // 98 - averages @ 396kHz measured
    
    I2C2CON = 0;
    I2C2CONbits.SIDL = 0;
    I2C2CONbits.DISSLW = 1;
    I2C2CONbits.SMEN = 1;

    /* Initialise master interrupt */
    IFS4bits.I2C2MIF = 0;
    IEC4bits.I2C2MIE = 0;

    /* Initialise fault interrupt */
    IFS4bits.I2C2BIF = 0;
    IEC4bits.I2C2BIE = 0;

    /* Turn on the I2C module */
    I2C2CONbits.ON = 1;  
}

/*******************************************************************************
*    Function Name:  TOUCH_Write_Byte
*    Description:    This routine is used to write a byte to the I2C bus.
*                    The input parameter data_out is written to the
*                    I2CTRN register. If IWCOL bit is set,write collision
*                    has occurred and -1 is returned, else 0 is returned.
*    Parameters:     uint8_t : data_out
*    Return Value:   char
*******************************************************************************/
DRV_I2C2_STATUS DRV_I2C2_Write_Byte(uint8_t data)
{
    I2C2TRN = data;

    if (1 == I2C2STATbits.IWCOL)        /* If write collision occurs, return -1 */
    {
        return (DRV_I2C2_BUS_COLLISION);
    }

    while (1 == I2C2STATbits.TRSTAT);   // wait until write cycle is complete         

	if (1 == I2C2STATbits.ACKSTAT)      // test for ACK condition received
    {
        return (DRV_I2C2_ACK_ERROR);
    }

    return (DRV_I2C2_WRITE_COMPLETE);
}

/************************************************************************
*    Function Name:  DRV_I2C2_Idle
*    Description:    This routine generates wait condition until I2C
*                    bus is Idle.
*    Parameters:     void
*    Return Value:   void
*************************************************************************/
void DRV_I2C2_Idle(void)
{
    /* Wait until I2C Bus is Inactive */
    while (I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RSEN || I2C2CONbits.RCEN || I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT);
}

/******************************************************************************
*    Function Name:  DRV_I2C2_Read_Byte
*    Description:    This routine reads a single byte from the I2C Bus.
*                    To enable master receive, RCEN bit is set.
*                    The RCEN bit is checked until it is cleared. When cleared,
*                    the receive register is full and it's contents are returned.
*    Parameters:     void
*    Return Value:   uint8_t
********************************************************************************/

DRV_I2C2_STATUS DRV_I2C2_Read_Byte(uint8_t* data, bool ack)
{
    I2C2CONbits.RCEN = 1;
    while (I2C2CONbits.RCEN);
    I2C2STATbits.I2COV = 0;
    *data = I2C2RCV;

    I2C2CONbits.ACKDT = ack;
    I2C2CONbits.ACKEN = 1;    
    DRV_I2C2_Idle();

    return (DRV_I2C2_READ_COMPLETE);
}

/******************************************************************************
*    Function Name:  DRV_I2C2_Start
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
DRV_I2C2_STATUS DRV_I2C2_Start(void)
{
    I2C2CONbits.SEN = 1;
    DRV_I2C2_Idle();
    
    // Check for collisions
	if (I2C2STATbits.BCL)
    {
		return (DRV_I2C2_BUS_COLLISION);
    }

    return (DRV_I2C2_START_COMPLETE);
}

/******************************************************************************
*    Function Name:  DRV_I2C2_Start
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
DRV_I2C2_STATUS DRV_I2C2_Restart(void)
{
    I2C2CONbits.RSEN = 1;
    DRV_I2C2_Idle();
    
    // Check for collisions
	if (I2C2STATbits.BCL)
    {
	    return (DRV_I2C2_BUS_COLLISION);
    }

    return (DRV_I2C2_START_COMPLETE);
}

/******************************************************************************
*    Function Name:  DRV_I2C2_Stop
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
DRV_I2C2_STATUS DRV_I2C2_Stop(void)
{
    I2C2CONbits.PEN = 1;
    DRV_I2C2_Idle();
    
    return (DRV_I2C2_STOP_COMPLETE);
}

/*******************************************************************************
*    Function Name:  DRV_I2C2_Write
*    Description:   
*    Parameters:     
*    Return Value:  
*******************************************************************************/
DRV_I2C2_STATUS DRV_I2C2_Write(uint8_t addr, uint8_t reg, uint8_t byte)
{
    DRV_I2C2_Idle();
    DRV_I2C2_Start();

    if (DRV_I2C2_Write_Byte((addr << 1 ) | 0x00) == DRV_I2C2_WRITE_COMPLETE)
    {
        if (DRV_I2C2_Write_Byte(reg) == DRV_I2C2_WRITE_COMPLETE)
        {
            if (DRV_I2C2_Write_Byte(byte) == DRV_I2C2_WRITE_COMPLETE)
            {
                DRV_I2C2_Stop();
                return (DRV_I2C2_WRITE_COMPLETE);
            }            
        }
    }

    DRV_I2C2_Stop();    
    return (DRV_I2C2_WRITE_ERROR);
}

DRV_I2C2_STATUS DRV_I2C2_Write_Bytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t length)
{
    uint8_t i;

    DRV_I2C2_Idle();
    DRV_I2C2_Start();

    if (DRV_I2C2_Write_Byte((addr << 1 ) | 0x00) == DRV_I2C2_WRITE_COMPLETE)
    {
        if (DRV_I2C2_Write_Byte(reg) == DRV_I2C2_WRITE_COMPLETE)
        {
            for (i = 0; i < length; i++)
            {
                if (DRV_I2C2_Write_Byte(data[i]) != DRV_I2C2_WRITE_COMPLETE)
                {
                    DRV_I2C2_Stop();
                    return (DRV_I2C2_WRITE_ERROR);
                }
            }

            DRV_I2C2_Stop();
            return (DRV_I2C2_WRITE_COMPLETE);
        }
    }

    DRV_I2C2_Stop();
    return (DRV_I2C2_WRITE_ERROR);
}

/*******************************************************************************
*    Function Name:  DRV_I2C2_Read
*    Description:   
*    Parameters:     
*    Return Value:  
*******************************************************************************/
DRV_I2C2_STATUS DRV_I2C2_Read(uint8_t addr, uint8_t reg, uint8_t* byte)
{
    DRV_I2C2_Idle();
    DRV_I2C2_Start();

    if (DRV_I2C2_Write_Byte((addr << 1) | 0x00) == DRV_I2C2_WRITE_COMPLETE)
    {
        if (DRV_I2C2_Write_Byte(reg) == DRV_I2C2_WRITE_COMPLETE)
        {
            DRV_I2C2_Restart(); 

            if (DRV_I2C2_Write_Byte((addr << 1) | 0x01) == DRV_I2C2_WRITE_COMPLETE)
            {    
                if (DRV_I2C2_Read_Byte(byte, 1) == DRV_I2C2_READ_COMPLETE)
                {
                    DRV_I2C2_Stop();                
                    return (DRV_I2C2_READ_COMPLETE);
                }      
            }
        }
    }

    DRV_I2C2_Stop();    
    return (DRV_I2C2_READ_ERROR);
}

DRV_I2C2_STATUS DRV_I2C2_Read_Bytes(uint8_t addr, uint8_t reg, uint8_t* data, uint8_t length)
{
    uint8_t i;

    DRV_I2C2_Idle();
    DRV_I2C2_Start();

    if (DRV_I2C2_Write_Byte((addr << 1) | 0x00) == DRV_I2C2_WRITE_COMPLETE)
    {
        if (DRV_I2C2_Write_Byte(reg) == DRV_I2C2_WRITE_COMPLETE)
        {
            DRV_I2C2_Restart();

            if (DRV_I2C2_Write_Byte((addr << 1) | 0x01) == DRV_I2C2_WRITE_COMPLETE)
            {
                for (i = 0; i < length; i++)
                {
                    if (DRV_I2C2_Read_Byte(&data[i], i == (length - 1)) != DRV_I2C2_READ_COMPLETE)
                    {
                        DRV_I2C2_Stop();
                        return (DRV_I2C2_READ_ERROR);
                    }
                }

                DRV_I2C2_Stop();
                return (DRV_I2C2_READ_COMPLETE);
            }
        }
    }

    DRV_I2C2_Stop();
    return (DRV_I2C2_READ_ERROR);
}

void DRV_I2C2_WriteReadTransferAdd(const DRV_HANDLE handle, const uint16_t address, uint8_t * const writeBuffer, const size_t writeSize, uint8_t * const readBuffer, const size_t readSize, DRV_I2C_TRANSFER_HANDLE* const transferHandle)
{
    DRV_I2C2_Read((uint8_t) address, (uint8_t) writeBuffer[0], readBuffer);
}
