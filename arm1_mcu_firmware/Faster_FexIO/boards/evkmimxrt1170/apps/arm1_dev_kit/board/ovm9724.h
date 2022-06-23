/*****************************************************************************/
/**
 * @file 
 *   ovm9724.h
 * @brief 
 *   Driver for Omnivision OVM9724 camera cube
 *
 *****************************************************************************/

/*
 * Copyright (c) 2022 Occuity Ltd. All rights reserved.
 */

#if !defined(OVM9724_H)
#define OVM9724_H

/*****************************************************************************/
/* Included Files                                                            */
/*****************************************************************************/

#include "fsl_video_common.h"
#include "fsl_camera.h"
#include "fsl_camera_device.h"

/** @todo 
 * We may want to keep this driver drom the SDK as it contains generic typedefs
 */
#include "fsl_ov5640.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

extern const camera_device_operations_t ovm9724_ops;

/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/

status_t OVM9724_initialise(
    camera_device_handle_t *ph_handle, 
    const camera_config_t *p_config);
status_t OVM9724_deinitialise(
    camera_device_handle_t *ph_handle);
status_t OVM9724_deinitialise(
    camera_device_handle_t *ph_handle);
status_t OVM9724_start(
    camera_device_handle_t *ph_handle);
status_t OVM9724_stop(
    camera_device_handle_t *ph_handle);
status_t OVM9724_control(
    camera_device_handle_t *ph_handle, 
    camera_device_cmd_t cmd, 
    int32_t arg);
status_t OVM9724_initialise_ext(
    camera_device_handle_t *ph_handle, 
    const camera_config_t *p_config, 
    const void *p_special_config);

#endif // defined(OVM9724_H)


/*** end of file ***/
