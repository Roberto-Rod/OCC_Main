/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_i2c2.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DRV_I2C2_H    /* Guard against multiple inclusion */
#define _DRV_I2C2_H


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
    DRV_I2C2_WRITE_ERROR    = -5,
    DRV_I2C2_READ_ERROR     = -4,
    DRV_I2C2_ACK_ERROR      = -3,
    DRV_I2C2_NACK_ERROR     = -2,
    DRV_I2C2_BUS_COLLISION  = -1,
            
    DRV_I2C2_WRITE_COMPLETE = 1,
    DRV_I2C2_READ_COMPLETE  = 2,
    DRV_I2C2_START_COMPLETE = 3,
    DRV_I2C2_STOP_COMPLETE  = 4
} DRV_I2C2_STATUS;

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

typedef uintptr_t DRV_I2C_TRANSFER_HANDLE;

typedef enum
{
    /* Transfer request is pending */
    DRV_I2C_TRANSFER_EVENT_PENDING = 0,

    /* All data from or to the buffer was transferred successfully. */
    DRV_I2C_TRANSFER_EVENT_COMPLETE = 1,

    /* Transfer Handle given is expired. It means transfer
    is completed but with or without error is not known. */
    DRV_I2C_TRANSFER_EVENT_HANDLE_EXPIRED = 2,

    /* There was an error while processing the buffer transfer request. */
    DRV_I2C_TRANSFER_EVENT_ERROR = -1,

    DRV_I2C_TRANSFER_EVENT_HANDLE_INVALID = -2

} DRV_I2C_TRANSFER_EVENT;
// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

void DRV_I2C2_Initialize(void);
DRV_I2C2_STATUS DRV_I2C2_Write_Byte(uint8_t data);
void DRV_I2C2_Idle(void);
DRV_I2C2_STATUS DRV_I2C2_Read_Byte(uint8_t* data, bool ack);
DRV_I2C2_STATUS DRV_I2C2_Start(void);
DRV_I2C2_STATUS DRV_I2C2_Restart(void);
DRV_I2C2_STATUS DRV_I2C2_Stop(void);
DRV_I2C2_STATUS DRV_I2C2_Write(uint8_t addr, uint8_t reg, uint8_t byte);
DRV_I2C2_STATUS DRV_I2C2_Read(uint8_t addr, uint8_t reg, uint8_t* byte);
DRV_I2C2_STATUS DRV_I2C2_Write_Bytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t length);
DRV_I2C2_STATUS DRV_I2C2_Read_Bytes(uint8_t addr, uint8_t reg, uint8_t* data, uint8_t length);
void DRV_I2C2_WriteReadTransferAdd(const DRV_HANDLE handle, const uint16_t address, uint8_t * const writeBuffer, const size_t writeSize, uint8_t * const readBuffer, const size_t readSize, DRV_I2C_TRANSFER_HANDLE* const transferHandle);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DRV_I2C2_H */
