/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_i2c1.c

  @Summary
    I2C driver for channel 1.

  @Description
    Driver.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

//#include "definitions.h"
#include "drv_i2c1.h"
#include <xc.h>
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
*    Function Name:  DRV_I2C1_Initialize
*    Description:    
*    Parameters:     
*    Return Value: 
*******************************************************************************/
//#define SDA_WR     (_LATB5)
//#define SCLK_WR    (_LATB6)
//
//#define SDA_TRIS   (_TRISB5)
//#define SCLK_TRIS  (_TRISB6)
//
//    SDA_TRIS = 1;
//    SCLK_TRIS = 1;
//    SDA_WR = 1;
//    SCLK_WR = 1;
void DRV_I2C1_Initialize(void)
{
    /* Disable the I2C Master interrupt */
    IEC1bits.MI2C1IE = 0;

    /* Disable the I2C Bus collision interrupt */
    IEC1bits.SI2C1IE = 0;
   
    I2C1BRG = 118;      // 400000 kHz

    I2C1CONL = 0;
    I2C1CONH = 0;
    I2C1CONLbits.I2CSIDL = 0;
    I2C1CONLbits.DISSLW = 1;
    I2C1CONLbits.SMEN = 1;

    /* Initialise master interrupt */
    IFS1bits.MI2C1IF = 0;
    IEC1bits.MI2C1IE = 0;

//    /* Initialise fault interrupt */
//    IFS1bits.I2C1BIF = 0;
//    IEC4bits.I2C1BIE = 0;

    /* Turn on the I2C module */
    I2C1CONLbits.I2CEN = 1;  
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
DRV_I2C1_STATUS DRV_I2C1_Write_Byte(uint8_t data)
{
    I2C1TRN = data;

    if (1 == I2C1STATbits.IWCOL)        /* If write collision occurs, return -1 */
    {
        return (DRV_I2C1_BUS_COLLISION);
    }

    while (1 == I2C1STATbits.TRSTAT);   // wait until write cycle is complete         

	if (1 == I2C1STATbits.ACKSTAT)      // test for ACK condition received
    {
        return (DRV_I2C1_ACK_ERROR);
    }

    return (DRV_I2C1_WRITE_COMPLETE);
}

/************************************************************************
*    Function Name:  DRV_I2C1_Idle
*    Description:    This routine generates wait condition until I2C
*                    bus is Idle.
*    Parameters:     void
*    Return Value:   void
*************************************************************************/
void DRV_I2C1_Idle(void)
{
    /* Wait until I2C Bus is Inactive */
    while (I2C1CONLbits.SEN || I2C1CONLbits.PEN || I2C1CONLbits.RSEN || I2C1CONLbits.RCEN || I2C1CONLbits.ACKEN || I2C1STATbits.TRSTAT);
}

/******************************************************************************
*    Function Name:  DRV_I2C1_Read_Byte
*    Description:    This routine reads a single byte from the I2C Bus.
*                    To enable master receive, RCEN bit is set.
*                    The RCEN bit is checked until it is cleared. When cleared,
*                    the receive register is full and it's contents are returned.
*    Parameters:     void
*    Return Value:   uint8_t
********************************************************************************/
DRV_I2C1_STATUS DRV_I2C1_Read_Byte(uint8_t* data, bool ack)
{
    I2C1CONLbits.RCEN = 1;
    while (I2C1CONLbits.RCEN);
    I2C2STATbits.I2COV = 0;
    *data = I2C1RCV;

    I2C1CONLbits.ACKDT = ack;
    I2C1CONLbits.ACKEN = 1;    
    DRV_I2C1_Idle();

    return (DRV_I2C1_READ_COMPLETE);
}

/******************************************************************************
*    Function Name:  DRV_I2C1_Start
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
DRV_I2C1_STATUS DRV_I2C1_Start(void)
{
    I2C1CONLbits.SEN = 1;
    DRV_I2C1_Idle();
    
    // Check for collisions
	if (I2C1STATbits.BCL)
    {
		return (DRV_I2C1_BUS_COLLISION);
    }

    return (DRV_I2C1_START_COMPLETE);
}

/******************************************************************************
*    Function Name:  DRV_I2C1_Start
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
DRV_I2C1_STATUS DRV_I2C1_Restart(void)
{
    I2C1CONLbits.RSEN = 1;
    DRV_I2C1_Idle();
    
    // Check for collisions
	if (I2C1STATbits.BCL)
    {
	    return (DRV_I2C1_BUS_COLLISION);
    }

    return (DRV_I2C1_START_COMPLETE);
}

/******************************************************************************
*    Function Name:  DRV_I2C1_Stop
*    Description:    
*    Parameters:     
*    Return Value:  
********************************************************************************/
DRV_I2C1_STATUS DRV_I2C1_Stop(void)
{
    I2C1CONLbits.PEN = 1;
    DRV_I2C1_Idle();
    
    return (DRV_I2C1_STOP_COMPLETE);
}
/*******************************************************************************
*    Function Name:  DRV_I2C1_Write
*    Description:   
*    Parameters:     
*    Return Value:  
*******************************************************************************/
DRV_I2C1_STATUS DRV_I2C2_Write(uint8_t addr, uint8_t reg, uint8_t byte)
{
    DRV_I2C1_Idle();
    DRV_I2C1_Start();

    if (DRV_I2C1_Write_Byte((addr << 1 ) | 0x00) == DRV_I2C1_WRITE_COMPLETE)
    {
        if (DRV_I2C1_Write_Byte(reg) == DRV_I2C1_WRITE_COMPLETE)
        {
            if (DRV_I2C1_Write_Byte(byte) == DRV_I2C1_WRITE_COMPLETE)
            {
                DRV_I2C1_Stop();
                return (DRV_I2C1_WRITE_COMPLETE);
            }            
        }
    }

    DRV_I2C1_Stop();    
    return (DRV_I2C1_WRITE_ERROR);
}

DRV_I2C1_STATUS DRV_I2C1_Write_Bytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t length)
{
    uint8_t i;

    DRV_I2C1_Idle();
    DRV_I2C1_Start();

    if (DRV_I2C1_Write_Byte((addr << 1 ) | 0x00) == DRV_I2C1_WRITE_COMPLETE)
    {
        if (DRV_I2C1_Write_Byte(reg) == DRV_I2C1_WRITE_COMPLETE)
        {
            for (i = 0; i < length; i++)
            {
                if (DRV_I2C1_Write_Byte(data[i]) != DRV_I2C1_WRITE_COMPLETE)
                {
                    DRV_I2C1_Stop();
                    return (DRV_I2C1_WRITE_ERROR);
                }
            }

            DRV_I2C1_Stop();
            return (DRV_I2C1_WRITE_COMPLETE);
        }
    }

    DRV_I2C1_Stop();
    return (DRV_I2C1_WRITE_ERROR);
}

/*******************************************************************************
*    Function Name:  DRV_I2C1_Read
*    Description:   
*    Parameters:     
*    Return Value:  
*******************************************************************************/
DRV_I2C1_STATUS DRV_I2C1_Read(uint8_t addr, uint8_t reg, uint8_t* byte)
{
    DRV_I2C1_Idle();
    DRV_I2C1_Start();

    if (DRV_I2C1_Write_Byte((addr << 1) | 0x00) == DRV_I2C1_WRITE_COMPLETE)
    {
        if (DRV_I2C1_Write_Byte(reg) == DRV_I2C1_WRITE_COMPLETE)
        {
            DRV_I2C1_Restart(); 

            if (DRV_I2C1_Write_Byte((addr << 1) | 0x01) == DRV_I2C1_WRITE_COMPLETE)
            {    
                if (DRV_I2C1_Read_Byte(byte, 1) == DRV_I2C1_READ_COMPLETE)
                {
                    DRV_I2C1_Stop();                
                    return (DRV_I2C1_READ_COMPLETE);
                }      
            }
        }
    }

    DRV_I2C1_Stop();    
    return (DRV_I2C1_READ_ERROR);
}

DRV_I2C1_STATUS DRV_I2C1_Read_Bytes(uint8_t addr, uint8_t reg, uint8_t* data, uint8_t length)
{
    uint8_t i;

    DRV_I2C1_Idle();
    DRV_I2C1_Start();

    if (DRV_I2C1_Write_Byte((addr << 1) | 0x00) == DRV_I2C1_WRITE_COMPLETE)
    {
        if (DRV_I2C1_Write_Byte(reg) == DRV_I2C1_WRITE_COMPLETE)
        {
            DRV_I2C1_Restart();

            if (DRV_I2C1_Write_Byte((addr << 1) | 0x01) == DRV_I2C1_WRITE_COMPLETE)
            {
                for (i = 0; i < length; i++)
                {
                    if (DRV_I2C1_Read_Byte(&data[i], i == (length - 1)) != DRV_I2C1_READ_COMPLETE)
                    {
                        DRV_I2C1_Stop();
                        return (DRV_I2C1_READ_ERROR);
                    }
                }

                DRV_I2C1_Stop();
                return (DRV_I2C1_READ_COMPLETE);
            }
        }
    }

    DRV_I2C1_Stop();
    return (DRV_I2C1_READ_ERROR);
}

void DRV_I2C1_WriteReadTransferAdd(const DRV_HANDLE handle, const uint16_t address, uint8_t * const writeBuffer, const size_t writeSize, uint8_t * const readBuffer, const size_t readSize, DRV_I2C_TRANSFER_HANDLE* const transferHandle)
{
    DRV_I2C1_Read((uint8_t) address, (uint8_t) writeBuffer[0], readBuffer);
}
