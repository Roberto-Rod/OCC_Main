/*****************************************************************************/
/**
 * @file 
 *   pxp.c
 * @brief 
 *   Pixel Pipeline API
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

#include "pxp.h"
#include "camera.h"
#include "display.h"
#include "fsl_pxp.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

#if (((CAMERA_WIDTH < CAMERA_HEIGHT) && (DISPLAY_BUFFER_WIDTH > DISPLAY_BUFFER_HEIGHT)) || \
     ((CAMERA_WIDTH > CAMERA_HEIGHT) && (DISPLAY_BUFFER_WIDTH < DISPLAY_BUFFER_HEIGHT)))
#define ROTATE_FRAME 1
#else
#define ROTATE_FRAME 0
#endif

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
 *   Initialise the Pixel Pipeline
 */
void PXP_initialise(void)
{
    /*
     * Configure the PXP for rotate and scale.
     */
    PXP_Init(PXP);

    PXP_SetProcessSurfaceBackGroundColor(PXP, 0);

#if ROTATE_FRAME
    PXP_SetProcessSurfacePosition(
        PXP, 0, 0, DISPLAY_BUFFER_HEIGHT - 1, DISPLAY_BUFFER_WIDTH - 1);
#else
    PXP_SetProcessSurfacePosition(
        PXP, 0, 0, DISPLAY_BUFFER_WIDTH - 1, DISPLAY_BUFFER_HEIGHT - 1);
#endif

    /* Disable AS. */
    PXP_SetAlphaSurfacePosition(PXP, 0xFFFFu, 0xFFFFu, 0, 0);

    PXP_EnableCsc1(PXP, false);

    /* Rotate and scale the camera input to fit display output. */
#if ROTATE_FRAME
    /* PS rotate & scale could not work at the same time so rotate the output */
    PXP_SetRotateConfig(
        PXP, kPXP_RotateOutputBuffer, kPXP_Rotate90, kPXP_FlipDisable);
    PXP_SetProcessSurfaceScaler(
        PXP, CAMERA_WIDTH, 
        CAMERA_HEIGHT, 
        DISPLAY_BUFFER_HEIGHT, 
        DISPLAY_BUFFER_WIDTH);
#else
    PXP_SetProcessSurfaceScaler(
        PXP, 
        CAMERA_WIDTH, 
        CAMERA_HEIGHT, 
        DISPLAY_BUFFER_WIDTH, 
        DISPLAY_BUFFER_HEIGHT);
#endif
}

/**
 * @brief
 *   Convert an image from RGB888 to RGB565 format
 * @param
 *   buff_in_addr Address of input buffer
 * @param
 *   buff_out_addr Address of output buffer
 */
void PXP_rgb888_to_rgb565(uint32_t buff_in_addr, uint32_t buff_out_addr)
{
    /* Input configuration */
    pxp_ps_buffer_config_t buffer_cfg = {
        .pixelFormat = kPXP_PsPixelFormatRGB888,
        .swapByte    = false,
        .bufferAddrU = 0,
        .bufferAddrV = 0,
        .pitchBytes  = CAMERA_WIDTH * CAMERA_BUFFER_BPP,
    };

    /* Output configuration */
    pxp_output_buffer_config_t output_buffer_cfg = {
        .pixelFormat    = kPXP_OutputPixelFormatRGB565,
        .interlacedMode = kPXP_OutputProgressive,
        .buffer1Addr    = 0,
        .pitchBytes     = DISPLAY_BUFFER_WIDTH * DISPLAY_BUFFER_BPP,
#if ROTATE_FRAME
        .width  = DISPLAY_BUFFER_HEIGHT,
        .height = DISPLAY_BUFFER_WIDTH,
#else
        .width  = DISPLAY_BUFFER_WIDTH,
        .height = DISPLAY_BUFFER_HEIGHT,
#endif
    };

    /* Convert the image in the input buffer to RGB565 format */
    buffer_cfg.bufferAddr = buff_in_addr;
    PXP_SetProcessSurfaceBufferConfig(PXP, &buffer_cfg);

    output_buffer_cfg.buffer0Addr = buff_out_addr;
    PXP_SetOutputBufferConfig(PXP, &output_buffer_cfg);

    PXP_Start(PXP);

    /* Wait for PXP process complete. */
    while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(PXP)))
    {
    }
    
    PXP_ClearStatusFlags(PXP, kPXP_CompleteFlag);
}

/*** end of file ***/
