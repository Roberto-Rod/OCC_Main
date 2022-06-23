/*****************************************************************************/
/**
 * @file 
 *   video.c
 * @brief 
 *   Top level layer for camera/display image buffering and processing
 *
 *****************************************************************************/

/*
 * Copyright (c) 2022 Occuity Ltd. All rights reserved.
 */

/*****************************************************************************/
/* Included Files                                                            */
/*****************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "video.h"
#include "camera.h"
#include "display.h"
#include "pxp.h"
#include "debug.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Reset camera and display for debugging (to be called before pin inits)
 */
void VIDEO_reset(void)
{
    DISPLAY_reset();
    CAMERA_reset();
}

/**
 * @brief
 *   Initialise camera, display and PXP
 */
void VIDEO_initialise(void)
{
    CAMERA_initialise();
    DISPLAY_initialise();
    PXP_initialise();
    
    CAMERA_RECEIVER_Start(&cameraReceiver);
}

/**
 * @brief
 *   Handle frames received from the camera and pass them to the display
 */
void VIDEO_frame_handler(void)
{
    uint32_t rx_frame_addr;
    uint32_t tx_frame_addr;
    
    /* Receive frame from camera */
    CAMERA_rx_frame(&rx_frame_addr);
    
    /* Wait for display buffer to become free */
    tx_frame_addr = DISPLAY_wait_for_buffer();

    PXP_rgb888_to_rgb565(rx_frame_addr, tx_frame_addr);

    /* Return the camera buffer to camera receiver handle. */
    CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, (uint32_t)rx_frame_addr);

    /* Show the new frame. */
    DISPLAY_show_new_frame();
}

/**
 * @brief
 *   Create a test pattern and send it to the display
 */
void VIDEO_compliance_test(void)
{
    uint32_t rx_frame_addr = CAMERA_create_test_pattern();
    uint32_t tx_frame_addr;

    /* Wait for display buffer to become free */
    tx_frame_addr = DISPLAY_wait_for_buffer();

    PXP_rgb888_to_rgb565(rx_frame_addr, tx_frame_addr);
  
    DISPLAY_show_new_frame();
}

/*** end of file ***/
