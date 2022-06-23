/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_i2c4.h

  @Summary
    Discrete driver for I2C channel 4.

  @Description
    Blocking I2C driver.
 */
/* ************************************************************************** */

#ifndef _DRV_I2C4_H    /* Guard against multiple inclusion */
#define _DRV_I2C4_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "definitions.h"
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
    DRV_I2C4_WRITE_ERROR    = -5,
    DRV_I2C4_READ_ERROR     = -4,
    DRV_I2C4_ACK_ERROR      = -3,
    DRV_I2C4_NACK_ERROR     = -2,
    DRV_I2C4_BUS_COLLISION  = -1,
            
    DRV_I2C4_WRITE_COMPLETE = 1,
    DRV_I2C4_READ_COMPLETE  = 2,
    DRV_I2C4_START_COMPLETE = 3,
    DRV_I2C4_STOP_COMPLETE  = 4
} DRV_I2C4_STATUS;

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

typedef uintptr_t DRV_HANDLE;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

void DRV_I2C4_Initialize(void);
DRV_I2C4_STATUS DRV_I2C4_Write_Byte(uint8_t data);
void DRV_I2C4_Idle(void);
DRV_I2C4_STATUS DRV_I2C4_Read_Byte(uint8_t* data, bool ack);
DRV_I2C4_STATUS DRV_I2C4_Start(void);
DRV_I2C4_STATUS DRV_I2C4_Restart(void);
DRV_I2C4_STATUS DRV_I2C4_Stop(void);
DRV_I2C4_STATUS DRV_I2C4_Write_Single_Byte(uint8_t addr, uint8_t byte);
DRV_I2C4_STATUS DRV_I2C4_Write(uint8_t addr, uint8_t reg, uint8_t byte);
DRV_I2C4_STATUS DRV_I2C4_Read_Single_Byte(uint8_t addr, uint8_t* byte);
DRV_I2C4_STATUS DRV_I2C4_Read(uint8_t addr, uint8_t reg, uint8_t* byte);
DRV_I2C4_STATUS DRV_I2C4_Write_Bytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t length);
DRV_I2C4_STATUS DRV_I2C4_Read_Bytes(uint8_t addr, uint8_t reg, uint8_t* data, uint8_t length);
void DRV_I2C4_WriteReadTransferAdd(const DRV_HANDLE handle, const uint16_t address, uint8_t * const writeBuffer, const size_t writeSize, uint8_t * const readBuffer, const size_t readSize, DRV_I2C_TRANSFER_HANDLE* const transferHandle);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DRV_I2C4_H */
