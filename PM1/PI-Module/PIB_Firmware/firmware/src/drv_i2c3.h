/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_i2c3.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DRV_I2C3_H    /* Guard against multiple inclusion */
#define _DRV_I2C3_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

typedef enum
{
    DRV_I2C3_WRITE_ERROR    = -5,
    DRV_I2C3_READ_ERROR     = -4,
    DRV_I2C3_ACK_ERROR      = -3,
    DRV_I2C3_NACK_ERROR     = -2,
    DRV_I2C3_BUS_COLLISION  = -1,
            
    DRV_I2C3_WRITE_COMPLETE = 1,
    DRV_I2C3_READ_COMPLETE  = 2,
    DRV_I2C3_START_COMPLETE = 3,
    DRV_I2C3_STOP_COMPLETE  = 4
} DRV_I2C3_STATUS;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

typedef uintptr_t DRV_I2C_TRANSFER_HANDLE;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

void DRV_I2C3_Initialize(void);
DRV_I2C3_STATUS DRV_I2C3_Write_Byte(uint8_t data);
void DRV_I2C3_Idle(void);
DRV_I2C3_STATUS DRV_I2C3_Read_Byte(uint8_t* data, bool ack);
DRV_I2C3_STATUS DRV_I2C3_Start(void);
DRV_I2C3_STATUS DRV_I2C3_Restart(void);
DRV_I2C3_STATUS DRV_I2C3_Stop(void);
DRV_I2C3_STATUS DRV_I2C3_Write(uint8_t addr, uint8_t reg, uint8_t byte);
DRV_I2C3_STATUS DRV_I2C3_Read(uint8_t addr, uint8_t reg, uint8_t* byte);
DRV_I2C3_STATUS DRV_I2C3_Write_Bytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t length);
DRV_I2C3_STATUS DRV_I2C3_Read_Bytes(uint8_t addr, uint8_t reg, uint8_t* data, uint8_t length);
DRV_I2C3_STATUS DRV_I2C3_Read_Bytes_Word_Register(uint8_t addr, uint16_t reg, uint8_t* data, uint8_t length);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DRV_I2C3_H */
