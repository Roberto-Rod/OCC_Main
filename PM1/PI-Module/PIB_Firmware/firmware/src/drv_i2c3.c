/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_i2c3.c

  @Summary
    I2C driver for channel 3.

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
#include "drv_i2c3.h"

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
*    Function Name:  DRV_I2C3_Initialize
*    Description:    
*    Parameters:     
*    Return Value: 
*******************************************************************************/
void DRV_I2C3_Initialize(void)
{
    PMD5bits.I2C3MD = 0;
    /* Disable the I2C Master interrupt */
    IEC5bits.I2C3MIE = 0;

    /* Disable the I2C Bus collision interrupt */
    IEC5bits.I2C3BIE = 0;
   
    //I2C3BRG = 118;      // 400000 kHz
    I2C3BRG = 98; // 98 - averages @ 396kHz measured

    I2C3CON = 0;
    I2C3CONbits.SIDL = 0;
    I2C3CONbits.DISSLW = 1;
    I2C3CONbits.SMEN = 1;

    /* Initialise master interrupt */
    IFS5bits.I2C3MIF = 0;
    IEC5bits.I2C3MIE = 0;

    /* Initialise fault interrupt */
    IFS5bits.I2C3BIF = 0;
    IEC5bits.I2C3BIE = 0;

    /* Turn on the I2C module */
    I2C3CONbits.ON = 1;  
}

/*******************************************************************************
*    Function Name:  DRV_I2C3_Write_Byte
*    Description:    This routine is used to write a byte to the I2C bus.
*                    The input parameter data_out is written to the
*                    I2CTRN register. If IWCOL bit is set,write collision
*                    has occurred and -1 is returned, else 0 is returned.
*    Parameters:     uint8_t : data_out
*    Return Value:   char
*******************************************************************************/
DRV_I2C3_STATUS DRV_I2C3_Write_Byte(uint8_t data)
{
    I2C3TRN = data;

    if (1 == I2C3STATbits.IWCOL)        /* If write collision occurs, return -1 */
    {
        return (DRV_I2C3_BUS_COLLISION);
    }

    while (1 == I2C3STATbits.TRSTAT);   // wait until write cycle is complete         

	if (1 == I2C3STATbits.ACKSTAT)      // test for ACK condition received
    {
        return (DRV_I2C3_ACK_ERROR);
    }

    return (DRV_I2C3_WRITE_COMPLETE);
}

/************************************************************************
*    Function Name:  DRV_I2C3_Idle
*    Description:    This routine generates wait condition until I2C
*                    bus is Idle.
*    Parameters:     void
*    Return Value:   void
*************************************************************************/
void DRV_I2C3_Idle(void)
{
    /* Wait until I2C Bus is Inactive */
    while (I2C3CONbits.SEN || I2C3CONbits.PEN || I2C3CONbits.RSEN || I2C3CONbits.RCEN || I2C3CONbits.ACKEN || I2C3STATbits.TRSTAT);
}

/******************************************************************************
*    Function Name:  DRV_I2C3_Read_Byte
*    Description:    This routine reads a single byte from the I2C Bus.
*                    To enable master receive, RCEN bit is set.
*                    The RCEN bit is checked until it is cleared. When cleared,
*                    the receive register is full and it's contents are returned.
*    Parameters:     void
*    Return Value:   uint8_t
********************************************************************************/

DRV_I2C3_STATUS DRV_I2C3_Read_Byte(uint8_t* data, bool ack)
{
    I2C3CONbits.RCEN = 1;
    while (I2C3CONbits.RCEN);
    I2C3STATbits.I2COV = 0;
    *data = I2C3RCV;

    I2C3CONbits.ACKDT = ack;
    I2C3CONbits.ACKEN = 1;    
    DRV_I2C3_Idle();

    return (DRV_I2C3_READ_COMPLETE);
}

/******************************************************************************
*    Function Name:  DRV_I2C3_Start
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
DRV_I2C3_STATUS DRV_I2C3_Start(void)
{
    I2C3CONbits.SEN = 1;
    DRV_I2C3_Idle();
    
    // Check for collisions
	if (I2C3STATbits.BCL)
    {
		return (DRV_I2C3_BUS_COLLISION);
    }

    return (DRV_I2C3_START_COMPLETE);
}

/******************************************************************************
*    Function Name:  DRV_I2C3_Restart
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
DRV_I2C3_STATUS DRV_I2C3_Restart(void)
{
    I2C3CONbits.RSEN = 1;
    DRV_I2C3_Idle();
    
    // Check for collisions
	if (I2C3STATbits.BCL)
    {
	    return (DRV_I2C3_BUS_COLLISION);
    }

    return (DRV_I2C3_START_COMPLETE);
}

/******************************************************************************
*    Function Name:  DRV_I2C3_Stop
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
DRV_I2C3_STATUS DRV_I2C3_Stop(void)
{
    I2C3CONbits.PEN = 1;
    DRV_I2C3_Idle();
    
    return (DRV_I2C3_STOP_COMPLETE);
}

/*******************************************************************************
*    Function Name:  DRV_I2C3_Write
*    Description:   
*    Parameters:     
*    Return Value:  
*******************************************************************************/
DRV_I2C3_STATUS DRV_I2C3_Write(uint8_t addr, uint8_t reg, uint8_t byte)
{
    DRV_I2C3_Idle();
    DRV_I2C3_Start();

    if (DRV_I2C3_Write_Byte((addr << 1 ) | 0x00) == DRV_I2C3_WRITE_COMPLETE)
    {
        if (DRV_I2C3_Write_Byte(reg) == DRV_I2C3_WRITE_COMPLETE)
        {
            if (DRV_I2C3_Write_Byte(byte) == DRV_I2C3_WRITE_COMPLETE)
            {
                DRV_I2C3_Stop();
                return (DRV_I2C3_WRITE_COMPLETE);
            }            
        }
    }

    DRV_I2C3_Stop();    
    return (DRV_I2C3_WRITE_ERROR);
}

DRV_I2C3_STATUS DRV_I2C3_Write_Bytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t length)
{
    uint8_t i;

    DRV_I2C3_Idle();
    DRV_I2C3_Start();

    if (DRV_I2C3_Write_Byte((addr << 1 ) | 0x00) == DRV_I2C3_WRITE_COMPLETE)
    {
        if (DRV_I2C3_Write_Byte(reg) == DRV_I2C3_WRITE_COMPLETE)
        {
            for (i = 0; i < length; i++)
            {
                if (DRV_I2C3_Write_Byte(data[i]) != DRV_I2C3_WRITE_COMPLETE)
                {
                    DRV_I2C3_Stop();
                    return (DRV_I2C3_WRITE_ERROR);
                }
            }

            DRV_I2C3_Stop();
            return (DRV_I2C3_WRITE_COMPLETE);
        }
    }

    DRV_I2C3_Stop();
    return (DRV_I2C3_WRITE_ERROR);
}

/*******************************************************************************
*    Function Name:  DRV_I2C3_Read
*    Description:   
*    Parameters:     
*    Return Value:  
*******************************************************************************/
DRV_I2C3_STATUS DRV_I2C3_Read(uint8_t addr, uint8_t reg, uint8_t* byte)
{
    DRV_I2C3_Idle();
    DRV_I2C3_Start();

    if (DRV_I2C3_Write_Byte((addr << 1) | 0x00) == DRV_I2C3_WRITE_COMPLETE)
    {
        if (DRV_I2C3_Write_Byte(reg) == DRV_I2C3_WRITE_COMPLETE)
        {
            DRV_I2C3_Restart(); 

            if (DRV_I2C3_Write_Byte((addr << 1) | 0x01) == DRV_I2C3_WRITE_COMPLETE)
            {    
                if (DRV_I2C3_Read_Byte(byte, 1) == DRV_I2C3_READ_COMPLETE)
                {
                    DRV_I2C3_Stop();                
                    return (DRV_I2C3_READ_COMPLETE);
                }      
            }
        }
    }

    DRV_I2C3_Stop();    
    return (DRV_I2C3_READ_ERROR);
}

/*******************************************************************************
*    Function Name:  DRV_I2C3_Read_Bytes
*    Description:    Read data from device after setting byte register value
*    Parameters:     
*    Return Value:  
*******************************************************************************/
DRV_I2C3_STATUS DRV_I2C3_Read_Bytes(uint8_t addr, uint8_t reg, uint8_t* data, uint8_t length)
{
    uint8_t i;

    DRV_I2C3_Idle();
    DRV_I2C3_Start();

    if (DRV_I2C3_Write_Byte((addr << 1) | 0x00) == DRV_I2C3_WRITE_COMPLETE)
    {
        if (DRV_I2C3_Write_Byte(reg) == DRV_I2C3_WRITE_COMPLETE)
        {
            DRV_I2C3_Restart();

            if (DRV_I2C3_Write_Byte((addr << 1) | 0x01) == DRV_I2C3_WRITE_COMPLETE)
            {
                for (i = 0; i < length; i++)
                {
                    if (DRV_I2C3_Read_Byte(&data[i], i == (length - 1)) != DRV_I2C3_READ_COMPLETE)
                    {
                        DRV_I2C3_Stop();
                        return (DRV_I2C3_READ_ERROR);
                    }
                }

                DRV_I2C3_Stop();
                return (DRV_I2C3_READ_COMPLETE);
            }
        }
    }

    DRV_I2C3_Stop();
    return (DRV_I2C3_READ_ERROR);
}

/*******************************************************************************
*    Function Name:  DRV_I2C3_Read_Bytes
*    Description:    Read data from device after setting word register value
*    Parameters:     
*    Return Value:  
*******************************************************************************/
DRV_I2C3_STATUS DRV_I2C3_Read_Bytes_Word_Register(uint8_t addr, uint16_t reg, uint8_t* data, uint8_t length)
{
    uint8_t i;

    DRV_I2C3_Idle();
    DRV_I2C3_Start();

    if (DRV_I2C3_Write_Byte((addr << 1) | 0x00) == DRV_I2C3_WRITE_COMPLETE)
    {
        if (DRV_I2C3_Write_Byte(reg >> 8) == DRV_I2C3_WRITE_COMPLETE)
        {
            if (DRV_I2C3_Write_Byte(reg) == DRV_I2C3_WRITE_COMPLETE)
            {
                DRV_I2C3_Restart();

                if (DRV_I2C3_Write_Byte((addr << 1) | 0x01) == DRV_I2C3_WRITE_COMPLETE)
                {
                    for (i = 0; i < length; i++)
                    {
                        if (DRV_I2C3_Read_Byte(&data[i], i == (length - 1)) != DRV_I2C3_READ_COMPLETE)
                        {
                            DRV_I2C3_Stop();
                            return (DRV_I2C3_READ_ERROR);
                        }
                    }

                    DRV_I2C3_Stop();
                    return (DRV_I2C3_READ_COMPLETE);
                }
            }
        }
    }

    DRV_I2C3_Stop();
    return (DRV_I2C3_READ_ERROR);
}
