/* 
 * File:   drv_camera_sccb.h
 * Author: Robin Taylor
 *
 * Created on 17 November 2019, 20:35
 */

#ifndef DRV_CAMERA_SCCB_H
#define	DRV_CAMERA_SCCB_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "device.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum
{
    SCCB_WRITE_ERROR                = -5,
    SCCB_READ_ERROR                 = -4,
    SCCB_ACK_ERROR                  = -3,
    SCCB_NACK_ERROR                 = -2,
    SCCB_BUS_COLLISION              = -1,
            
    SCCB_WRITE_COMPLETE             = 1,
    SCCB_READ_COMPLETE              = 2,
    SCCB_START_COMPLETE             = 3,
    SCCB_STOP_COMPLETE              = 4
} SCCB_STATUS;

typedef uintptr_t DRV_I2C_TRANSFER_HANDLE;

void        SCCB_Initialize(void);
void        SCCB_Idle(void);
SCCB_STATUS SCCB_Write_Byte( uint8_t data );
SCCB_STATUS SCCB_Read_Byte( uint8_t* data );
SCCB_STATUS SCCB_Start( void );
SCCB_STATUS SCCB_Stop( void );
SCCB_STATUS SCCB_Restart( void );
SCCB_STATUS SCCB_Write( uint8_t addr, uint8_t reg, uint8_t byte );
SCCB_STATUS SCCB_Read( uint8_t addr, uint8_t reg, uint8_t* byte );

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_CAMERA_SCCB_H */

