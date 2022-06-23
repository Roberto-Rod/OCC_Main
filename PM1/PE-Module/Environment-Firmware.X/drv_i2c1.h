/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_i2c1.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DRV_I2C1_H    /* Guard against multiple inclusion */
#define _DRV_I2C1_H


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
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
    
typedef	unsigned int	      __uintptr_t;    
typedef	__uintptr_t	uintptr_t;
#define	uintptr_t	__uintptr_t
typedef uintptr_t DRV_HANDLE;

typedef enum
{
    DRV_I2C1_WRITE_ERROR    = -5,
    DRV_I2C1_READ_ERROR     = -4,
    DRV_I2C1_ACK_ERROR      = -3,
    DRV_I2C1_NACK_ERROR     = -2,
    DRV_I2C1_BUS_COLLISION  = -1,
            
    DRV_I2C1_WRITE_COMPLETE = 1,
    DRV_I2C1_READ_COMPLETE  = 2,
    DRV_I2C1_START_COMPLETE = 3,
    DRV_I2C1_STOP_COMPLETE  = 4
} DRV_I2C1_STATUS;

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

void DRV_I2C1_Initialize(void);
DRV_I2C1_STATUS DRV_I2C1_Write_Byte(uint8_t data);
void DRV_I2C1_Idle(void);
DRV_I2C1_STATUS DRV_I2C1_Read_Byte(uint8_t* data, bool ack);
DRV_I2C1_STATUS DRV_I2C1_Start(void);
DRV_I2C1_STATUS DRV_I2C1_Restart(void);
DRV_I2C1_STATUS DRV_I2C1_Stop(void);
DRV_I2C1_STATUS DRV_I2C1_Write(uint8_t addr, uint8_t reg, uint8_t byte);
DRV_I2C1_STATUS DRV_I2C1_Read(uint8_t addr, uint8_t reg, uint8_t* byte);
DRV_I2C1_STATUS DRV_I2C1_Write_Bytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t length);
DRV_I2C1_STATUS DRV_I2C1_Read_Bytes(uint8_t addr, uint8_t reg, uint8_t* data, uint8_t length);
void DRV_I2C2_WriteReadTransferAdd(const DRV_HANDLE handle, const uint16_t address, uint8_t * const writeBuffer, const size_t writeSize, uint8_t * const readBuffer, const size_t readSize, DRV_I2C_TRANSFER_HANDLE* const transferHandle);

#define I2C_CHECK_OP_SUCCESS(x) ( (x) > 0 )

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DRV_I2C2_H */
