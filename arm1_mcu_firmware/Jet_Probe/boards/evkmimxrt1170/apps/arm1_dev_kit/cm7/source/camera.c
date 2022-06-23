/*****************************************************************************/
/**
 * @file 
 *   camera.c
 * @brief 
 *   Top-level camera API
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

#include "camera.h"
#include "debug.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/* Number of buffer layers */
#define CAMERA_BUFFER_COUNT     (3u)

#define RED                     (2u)
#define GREEN                   (1u)
#define BLUE                    (0)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

#ifdef USE_SDRAM

AT_NONCACHEABLE_SECTION_ALIGN(
    static uint8_t gp_camera_buffer[CAMERA_BUFFER_COUNT][CAMERA_HEIGHT]
                                   [CAMERA_WIDTH * CAMERA_BUFFER_BPP],
    CAMERA_BUFFER_ALIGN
);

#else

#pragma default_variable_attributes = @ "IMAGES"
static uint8_t gp_camera_buffer[CAMERA_BUFFER_COUNT][CAMERA_HEIGHT]
                                   [CAMERA_WIDTH * CAMERA_BUFFER_BPP];
#pragma default_variable_attributes =

#endif

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
 *   Reset camera for debugging (to be called before pin inits)
 */
void CAMERA_reset(void)
{
    BOARD_EarlyInitCamera();
}

/**
 * @brief
 *   Initialise camera
 */
void CAMERA_initialise(void)
{
    camera_config_t cfg;

    memset(gp_camera_buffer, 0, sizeof(gp_camera_buffer));
    memset(&cfg, 0, sizeof(cfg));

    BOARD_InitCameraResource();

    /* CSI input data bus is 24-bit, and save as XRGB8888.. */
    cfg.pixelFormat                = kVIDEO_PixelFormatXRGB8888;
    cfg.bytesPerPixel              = CAMERA_BUFFER_BPP;
    cfg.resolution                 = FSL_VIDEO_RESOLUTION(CAMERA_WIDTH, CAMERA_HEIGHT);
    cfg.frameBufferLinePitch_Bytes = CAMERA_WIDTH * CAMERA_BUFFER_BPP;
    cfg.interface                  = kCAMERA_InterfaceGatedClock;
    cfg.controlFlags               = CAMERA_CONTROL_FLAGS;
    cfg.framePerSec                = CAMERA_FRAME_RATE;

    CAMERA_RECEIVER_Init(&cameraReceiver, &cfg, NULL, NULL);

    BOARD_InitMipiCsi();

    cfg.pixelFormat   = kVIDEO_PixelFormatRGB565;
    cfg.bytesPerPixel = 2;
    cfg.resolution    = FSL_VIDEO_RESOLUTION(CAMERA_WIDTH, CAMERA_HEIGHT);
    cfg.interface     = kCAMERA_InterfaceMIPI;
    cfg.controlFlags  = CAMERA_CONTROL_FLAGS;
    cfg.framePerSec   = CAMERA_FRAME_RATE;
    cfg.csiLanes      = CAMERA_MIPI_CSI_LANE;
    CAMERA_DEVICE_Init(&cameraDevice, &cfg);

    CAMERA_DEVICE_Start(&cameraDevice);

    /* Submit the empty frame buffers to buffer queue. */
    for (uint32_t i = 0; i < CAMERA_BUFFER_COUNT; i++)
    {
        CAMERA_RECEIVER_SubmitEmptyBuffer(
            &cameraReceiver, 
            (uint32_t)(gp_camera_buffer[i]));
    }
}

/**
 * @brief
 *   Receive camera frame (blocks until full frame received)
 * @param[out]
 *   p_frame_addr Address of frame received 
 */
void CAMERA_rx_frame(uint32_t* p_frame_addr)
{
    status_t status;
  
    do
    {
        status = CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, p_frame_addr);
    } while (kStatus_Success != status);
}

/**
 * @brief
 *   Create a test pattern and send it to the display
 *   Format of pattern: R G B
 *                      G B R
 *                      B R G
 * @return
 *   Address of buffer containing the test pattern
 */
uint32_t CAMERA_create_test_pattern(void)
{
    uint32_t i;
    uint32_t j;

    for (i = 0; i < CAMERA_HEIGHT; i++)
    {
        for (j = 0; j < CAMERA_WIDTH * CAMERA_BUFFER_BPP; j+=CAMERA_BUFFER_BPP)
        {
            uint8_t colour = 0;

            if (i < CAMERA_HEIGHT / 3u)
            {
                if (j < CAMERA_WIDTH * CAMERA_BUFFER_BPP / 3u)
                {
                    colour = RED;
                }
                else if (j < CAMERA_WIDTH * CAMERA_BUFFER_BPP  * 2u / 3u)
                {
                    colour = GREEN;
                }
                else
                {
                    colour = BLUE;
                }
            }
            else if (i < CAMERA_HEIGHT * 2u / 3u)
            {
                if (j < CAMERA_WIDTH * CAMERA_BUFFER_BPP / 3u)
                {
                    colour = GREEN;
                }
                else if (j < CAMERA_WIDTH * CAMERA_BUFFER_BPP  * 2u / 3u)
                {
                    colour = BLUE;
                }
                else
                {
                    colour = RED;
                }
            }
            else
            {
                if (j < CAMERA_WIDTH * CAMERA_BUFFER_BPP / 3u)
                {
                    colour = BLUE;
                }
                else if (j < CAMERA_WIDTH * CAMERA_BUFFER_BPP  * 2u / 3u)
                {
                    colour = RED;
                }
                else
                {
                    colour = GREEN;
                }
            }
          
            gp_camera_buffer[0][i][j+colour] = 0xFFu;
        }
    }

    return (uint32_t)gp_camera_buffer;
}


/*** end of file ***/
