/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_i2c4.c

  @Summary
    Discrete driver for I2C channel 4.

  @Description
    Blocking I2C driver.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "drv_i2c4.h"

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
void DRV_I2C4_Initialize(void)
{
    /* Disable the I2C Master interrupt */
    IEC5bits.I2C4MIE = 0;

    /* Disable the I2C Bus collision interrupt */
    IEC5bits.I2C4BIE = 0;
   
    I2C4BRG = 118;      // 400000 kHz

    I2C4CON = 0;
    I2C4CONbits.SIDL = 0;
    I2C4CONbits.DISSLW = 1;
    I2C4CONbits.SMEN = 1;

    /* Initialise master interrupt */
    IFS5bits.I2C4MIF = 0;
    IEC5bits.I2C4MIE = 0;

    /* Initialise fault interrupt */
    IFS5bits.I2C4BIF = 0;
    IEC5bits.I2C4BIE = 0;

    /* Turn on the I2C module */
    I2C4CONbits.ON = 1;  
}

/*******************************************************************************
*    Function Name:  DRV_I2C4_Write_Byte
*    Description:    This routine is used to write a byte to the I2C bus.
*                    The input parameter data_out is written to the
*                    I2CTRN register. If IWCOL bit is set,write collision
*                    has occurred and -1 is returned, else 0 is returned.
*    Parameters:     uint8_t : data_out
*    Return Value:   char
*******************************************************************************/
DRV_I2C4_STATUS DRV_I2C4_Write_Byte(uint8_t data)
{
    I2C4TRN = data;

    if (1 == I2C4STATbits.IWCOL)        /* If write collision occurs, return -1 */
    {
        return (DRV_I2C4_BUS_COLLISION);
    }

    while (1 == I2C4STATbits.TRSTAT);   // wait until write cycle is complete         

	if (1 == I2C4STATbits.ACKSTAT)      // test for ACK condition received
    {
        return (DRV_I2C4_ACK_ERROR);
    }

    return (DRV_I2C4_WRITE_COMPLETE);
}

/************************************************************************
*    Function Name:  DRV_I2C4_Idle
*    Description:    This routine generates wait condition until I2C
*                    bus is Idle.
*    Parameters:     void
*    Return Value:   void
*************************************************************************/
void DRV_I2C4_Idle(void)
{
    /* Wait until I2C Bus is Inactive */
    while (I2C4CONbits.SEN || I2C4CONbits.PEN || I2C4CONbits.RSEN || I2C4CONbits.RCEN || I2C4CONbits.ACKEN || I2C4STATbits.TRSTAT);
}

/******************************************************************************
*    Function Name:  DRV_I2C4_Read_Byte
*    Description:    This routine reads a single byte from the I2C Bus.
*                    To enable master receive, RCEN bit is set.
*                    The RCEN bit is checked until it is cleared. When cleared,
*                    the receive register is full and it's contents are returned.
*    Parameters:     void
*    Return Value:   uint8_t
********************************************************************************/

DRV_I2C4_STATUS DRV_I2C4_Read_Byte(uint8_t* data, bool ack)
{
    I2C4CONbits.RCEN = 1;
    while (I2C4CONbits.RCEN);
    I2C4STATbits.I2COV = 0;
    *data = I2C4RCV;

    I2C4CONbits.ACKDT = ack;
    I2C4CONbits.ACKEN = 1;    
    DRV_I2C4_Idle();

    return (DRV_I2C4_READ_COMPLETE);
}

/******************************************************************************
*    Function Name:  DRV_I2C4_Start
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
DRV_I2C4_STATUS DRV_I2C4_Start(void)
{
    I2C4CONbits.SEN = 1;
    DRV_I2C4_Idle();
    
    // Check for collisions
	if (I2C4STATbits.BCL)
    {
		return (DRV_I2C4_BUS_COLLISION);
    }

    return (DRV_I2C4_START_COMPLETE);
}

/******************************************************************************
*    Function Name:  DRV_I2C4_Restart
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
DRV_I2C4_STATUS DRV_I2C4_Restart(void)
{
    I2C4CONbits.RSEN = 1;
    DRV_I2C4_Idle();
    
    // Check for collisions
	if (I2C4STATbits.BCL)
    {
	    return (DRV_I2C4_BUS_COLLISION);
    }

    return (DRV_I2C4_START_COMPLETE);
}

/******************************************************************************
*    Function Name:  DRV_I2C4_Stop
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
DRV_I2C4_STATUS DRV_I2C4_Stop(void)
{
    I2C4CONbits.PEN = 1;
    DRV_I2C4_Idle();
    
    return (DRV_I2C4_STOP_COMPLETE);
}

/*******************************************************************************
*    Function Name:  DRV_I2C4_Write
*    Description:   
*    Parameters:     
*    Return Value:  
*******************************************************************************/
DRV_I2C4_STATUS DRV_I2C4_Write(uint8_t addr, uint8_t reg, uint8_t byte)
{
    DRV_I2C4_Idle();
    DRV_I2C4_Start();

    if (DRV_I2C4_Write_Byte((addr << 1 ) | 0x00) == DRV_I2C4_WRITE_COMPLETE)
    {
        if (DRV_I2C4_Write_Byte(reg) == DRV_I2C4_WRITE_COMPLETE)
        {
            if (DRV_I2C4_Write_Byte(byte) == DRV_I2C4_WRITE_COMPLETE)
            {
                DRV_I2C4_Stop();
                return (DRV_I2C4_WRITE_COMPLETE);
            }
        }
    }

    DRV_I2C4_Stop();    
    return (DRV_I2C4_WRITE_ERROR);
}

/*******************************************************************************
*    Function Name:  DRV_I2C4_Write_Single_Byte
*    Description:   
*    Parameters:     
*    Return Value:  
*******************************************************************************/
DRV_I2C4_STATUS DRV_I2C4_Write_Single_Byte(uint8_t addr, uint8_t byte)
{
    DRV_I2C4_Idle();
    DRV_I2C4_Start();

    if (DRV_I2C4_Write_Byte((addr << 1 ) | 0x00) == DRV_I2C4_WRITE_COMPLETE)
    {
        if (DRV_I2C4_Write_Byte(byte) == DRV_I2C4_WRITE_COMPLETE)
        {
            DRV_I2C4_Stop();
            return (DRV_I2C4_WRITE_COMPLETE);
        }
    }

    DRV_I2C4_Stop();    
    return (DRV_I2C4_WRITE_ERROR);
}

DRV_I2C4_STATUS DRV_I2C4_Write_Bytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t length)
{
    uint8_t i;

    DRV_I2C4_Idle();
    DRV_I2C4_Start();

    if (DRV_I2C4_Write_Byte((addr << 1 ) | 0x00) == DRV_I2C4_WRITE_COMPLETE)
    {
        if (DRV_I2C4_Write_Byte(reg) == DRV_I2C4_WRITE_COMPLETE)
        {
            for (i = 0; i < length; i++)
            {
                if (DRV_I2C4_Write_Byte(data[i]) != DRV_I2C4_WRITE_COMPLETE)
                {
                    DRV_I2C4_Stop();
                    return (DRV_I2C4_WRITE_ERROR);
                }
            }

            DRV_I2C4_Stop();
            return (DRV_I2C4_WRITE_COMPLETE);
        }
    }

    DRV_I2C4_Stop();
    return (DRV_I2C4_WRITE_ERROR);
}

/*******************************************************************************
*    Function Name:  DRV_I2C4_Read
*    Description:   
*    Parameters:     
*    Return Value:  
*******************************************************************************/
DRV_I2C4_STATUS DRV_I2C4_Read(uint8_t addr, uint8_t reg, uint8_t* byte)
{
    DRV_I2C4_Idle();
    DRV_I2C4_Start();

    if (DRV_I2C4_Write_Byte((addr << 1) | 0x00) == DRV_I2C4_WRITE_COMPLETE)
    {
        if (DRV_I2C4_Write_Byte(reg) == DRV_I2C4_WRITE_COMPLETE)
        {
            DRV_I2C4_Restart(); 

            if (DRV_I2C4_Write_Byte((addr << 1) | 0x01) == DRV_I2C4_WRITE_COMPLETE)
            {    
                if (DRV_I2C4_Read_Byte(byte, 1) == DRV_I2C4_READ_COMPLETE)
                {
                    DRV_I2C4_Stop();                
                    return (DRV_I2C4_READ_COMPLETE);
                }      
            }
        }
    }

    DRV_I2C4_Stop();    
    return (DRV_I2C4_READ_ERROR);
}

/*******************************************************************************
*    Function Name:  DRV_I2C4_Read_Single_Byte
*    Description:   
*    Parameters:     
*    Return Value:  
*******************************************************************************/
DRV_I2C4_STATUS DRV_I2C4_Read_Single_Byte(uint8_t addr, uint8_t* byte)
{
    DRV_I2C4_Idle();
    DRV_I2C4_Start();

    //if (DRV_I2C4_Write_Byte((addr << 1) | 0x00) == DRV_I2C4_WRITE_COMPLETE)
    //{
        //if (DRV_I2C4_Write_Byte(reg) == DRV_I2C4_WRITE_COMPLETE)
        //{
        //    DRV_I2C4_Restart(); 

            if (DRV_I2C4_Write_Byte((addr << 1) | 0x01) == DRV_I2C4_WRITE_COMPLETE)
            {    
                if (DRV_I2C4_Read_Byte(byte, 1) == DRV_I2C4_READ_COMPLETE)
                {
                    DRV_I2C4_Stop();                
                    return (DRV_I2C4_READ_COMPLETE);
                }      
            }
        //}
    //}

    DRV_I2C4_Stop();    
    return (DRV_I2C4_READ_ERROR);
}

DRV_I2C4_STATUS DRV_I2C4_Read_Bytes(uint8_t addr, uint8_t reg, uint8_t* data, uint8_t length)
{
    uint8_t i;

    DRV_I2C4_Idle();
    DRV_I2C4_Start();

    if (DRV_I2C4_Write_Byte((addr << 1) | 0x00) == DRV_I2C4_WRITE_COMPLETE)
    {
        if (DRV_I2C4_Write_Byte(reg) == DRV_I2C4_WRITE_COMPLETE)
        {
            DRV_I2C4_Restart();

            if (DRV_I2C4_Write_Byte((addr << 1) | 0x01) == DRV_I2C4_WRITE_COMPLETE)
            {
                for (i = 0; i < length; i++)
                {
                    if (DRV_I2C4_Read_Byte(&data[i], i == (length - 1)) != DRV_I2C4_READ_COMPLETE)
                    {
                        DRV_I2C4_Stop();
                        return (DRV_I2C4_READ_ERROR);
                    }
                }

                DRV_I2C4_Stop();
                return (DRV_I2C4_READ_COMPLETE);
            }
        }
    }

    DRV_I2C4_Stop();
    return (DRV_I2C4_READ_ERROR);
}

void DRV_I2C4_WriteReadTransferAdd(const DRV_HANDLE handle, const uint16_t address, uint8_t * const writeBuffer, const size_t writeSize, uint8_t * const readBuffer, const size_t readSize, DRV_I2C_TRANSFER_HANDLE* const transferHandle)
{
    DRV_I2C4_Read((uint8_t) address, (uint8_t) writeBuffer[0], readBuffer);
}
