/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _CAMERA_SUPPORT_H_
#define _CAMERA_SUPPORT_H_

#include "fsl_camera.h"
#include "fsl_camera_receiver.h"
#include "fsl_camera_device.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define CAMERA_HEIGHT           (720u)
#define CAMERA_WIDTH            (1280u)
#define CAMERA_FRAME_RATE       (30u)
#define CAMERA_CONTROL_FLAGS    (kCAMERA_HrefActiveHigh | kCAMERA_DataLatchOnRisingEdge)
#define CAMERA_BUFFER_ALIGN     (64u)
#define CAMERA_MIPI_CSI_LANE    (2u)

extern camera_device_handle_t cameraDevice;
extern camera_receiver_handle_t cameraReceiver;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* This function should be called before camera pins initialization */
void BOARD_EarlyInitCamera(void);

void BOARD_InitCameraResource(void);

void BOARD_InitMipiCsi(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _CAMERA_SUPPORT_H_ */
