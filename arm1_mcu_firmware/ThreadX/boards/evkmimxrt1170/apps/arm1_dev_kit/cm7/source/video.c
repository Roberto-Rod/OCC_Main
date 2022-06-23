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

#define THREAD_V_EVENT_FLAG_FRAME_READY      (1ul << 0)
#define THREAD_V_EVENT_FLAG_DISPLAY_READY    (1ul << 1)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

static TX_EVENT_FLAGS_GROUP video_event_flags;

static uint32_t g_display_buffer;

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

static void compliance_test(uint32_t frame_addres);
static void frame_ready_callback(status_t status);
static void inactive_buffer_callback(void *p_buffer);

/**
 * @brief
 *   Function called from camera receiver when a new frame is ready
 * @param
 *   status kStatus_Success expected
 */
static void frame_ready_callback(status_t status)
{
    if (kStatus_Success == status)
    {
        const UINT tx_status = tx_event_flags_set(
            &video_event_flags, THREAD_V_EVENT_FLAG_FRAME_READY, TX_OR);

        if (TX_SUCCESS != tx_status)
        {
            /// @todo Handle error
        }
    }
}

/**
 * @brief
 *   Function to be called when buffer has been shown
 * @param[in]
 *   p_buffer Pointer to inactive buffer
 */
static void inactive_buffer_callback(void *p_buffer)
{
    if (NULL != p_buffer)
    {
        const UINT tx_status = tx_event_flags_set(
            &video_event_flags, THREAD_V_EVENT_FLAG_DISPLAY_READY, TX_OR);

        if (TX_SUCCESS != tx_status)
        {
            /// @todo Handle error
        }
        
        g_display_buffer = (uint32_t)p_buffer;
    }
}

/**
 * @brief
 *   Send test pattern to the display
 * @param
 *   frame_address Address of test pattern buffer 
 */
static void compliance_test(uint32_t frame_address)
{
    g_display_buffer = DISPLAY_get_buffer_address();
    
    PXP_rgb888_to_rgb565(frame_address, g_display_buffer);
    DISPLAY_show_new_frame();
}

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
    CAMERA_initialise(frame_ready_callback);
    DISPLAY_initialise(inactive_buffer_callback);
    PXP_initialise();
    
    CAMERA_RECEIVER_Start(&cameraReceiver);
}

/**
 * @brief
 *   Handle frames received from the camera and pass them to the display
 * @param
 *   input Unused
 */
void VIDEO_thread(ULONG input)
{
    uint32_t rx_frame_addr = CAMERA_create_test_pattern();
    
    TX_THREAD_NOT_USED(input);

    /* Create the video event flags group */
    UINT tx_status = tx_event_flags_create(
        &video_event_flags, "video event flags");

    if (TX_SUCCESS != tx_status) 
    {
        return;
    }
    
    /* Compliance test (send test pattern to display) */
    compliance_test(rx_frame_addr);
    
    while (TX_LOOP_FOREVER)
    {
        ULONG actual_flags;

        /* Wait for frame ready event flag */
        tx_status = tx_event_flags_get(
            &video_event_flags, 
            THREAD_V_EVENT_FLAG_FRAME_READY, 
            TX_OR_CLEAR, 
            &actual_flags, 
            TX_WAIT_FOREVER);
    
        if (TX_SUCCESS == tx_status) 
        {
            /* Receive frame from camera */
            CAMERA_rx_frame(&rx_frame_addr);
    
            /* Wait for display buffer to become free (timeout at frame rate) */
            tx_status = tx_event_flags_get(
                &video_event_flags, 
                THREAD_V_EVENT_FLAG_DISPLAY_READY, 
                TX_OR_CLEAR, 
                &actual_flags, 
                CLOCK_GetFreq(kCLOCK_CoreSysClk) / (CAMERA_FRAME_RATE-1u));
            
            if (TX_SUCCESS == tx_status)
            {
                /* Convert the frame format and display it */
                PXP_rgb888_to_rgb565(rx_frame_addr, g_display_buffer);
                DISPLAY_show_new_frame();
            }

            /* Return the camera buffer to camera receiver handle */
            CAMERA_RECEIVER_SubmitEmptyBuffer(
                &cameraReceiver, (uint32_t)rx_frame_addr);
        }
    }
}


/*** end of file ***/
