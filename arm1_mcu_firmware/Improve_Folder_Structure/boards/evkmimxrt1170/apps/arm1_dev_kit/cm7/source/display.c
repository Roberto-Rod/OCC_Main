/*****************************************************************************/
/**
 * @file 
 *   display.c
 * @brief 
 *   Top-level LCD display API
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

#include "display.h"
#include "debug.h"
#include "fsl_soc_src.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

#define DISPLAY_BUFFER_COUNT    (2u)
#define DISPLAY_PIXEL_FORMAT    (kVIDEO_PixelFormatRGB565)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/* XRGB8888 pixel definition. */
typedef struct pixel
{
    uint8_t B;
    uint8_t G;
    uint8_t R;
    uint8_t X;
} pixel_t;

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

/*
 * When new frame buffer sent to display, it might not be shown immediately.
 * Application could use callback to get new frame shown notification, at the
 * same time, when this flag is set, application could write to the older
 * frame buffer.
 */
static volatile bool gb_frame_shown = false;

static volatile uint8_t g_fb_index;

static dc_fb_info_t g_fb_info;

AT_NONCACHEABLE_SECTION_ALIGN(
    static uint8_t gp_display_buffer[DISPLAY_BUFFER_COUNT][DISPLAY_BUFFER_HEIGHT]
                                    [DISPLAY_BUFFER_WIDTH * DISPLAY_BUFFER_BPP],
    DISPLAY_BUFFER_ALIGN
);

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

static void inactive_buffer_callback(void *p_param, void *p_buffer);
static void init_display(void);
static void init_frame_buffer(void);

/**
 * @brief
 *   Function to be called when buffer has been shown
 * @param[in]
 *   p_param Pointer to parameters
 * @param[in]
 *   p_buffer Pointer to inactive buffer
 */
static void inactive_buffer_callback(void *p_param, void *p_buffer)
{
    gb_frame_shown = true;
    g_fb_index ^= 1;
}

/**
 * @brief
 *   Initialize the display
 */
static void init_display(void)
{
    status_t status;

    BOARD_PrepareDisplayController();

    /* Initialize the display controller */
    status = g_dc.ops->init(&g_dc);
    if (kStatus_Success != status)
    {
        DEBUG_printf("Display initialization failed\r\n");
        assert(0);
    }
    
    g_dc.ops->getLayerDefaultConfig(&g_dc, 0, &g_fb_info);
    g_fb_info.pixelFormat = DISPLAY_PIXEL_FORMAT;
    g_fb_info.width       = DISPLAY_BUFFER_WIDTH;
    g_fb_info.height      = DISPLAY_BUFFER_HEIGHT;
    g_fb_info.startX      = DISPLAY_BUFFER_START_X;
    g_fb_info.startY      = DISPLAY_BUFFER_START_Y;
    g_fb_info.strideBytes = DISPLAY_BUFFER_WIDTH * DISPLAY_BUFFER_BPP;
    g_dc.ops->setLayerConfig(&g_dc, 0, &g_fb_info);

    g_dc.ops->setCallback(&g_dc, 0, inactive_buffer_callback, NULL);

    g_fb_index = 0;
    gb_frame_shown  = false;
    g_dc.ops->setFrameBuffer(&g_dc, 0, gp_display_buffer[g_fb_index]);

    /* For the DBI interface display, application must wait for the first
     * frame buffer sent to the panel.
     */
    if ((g_dc.ops->getProperty(&g_dc) & kDC_FB_ReserveFrameBuffer) == 0)
    {
        while (gb_frame_shown == false)
        {
        }
    }

    gb_frame_shown = true;

    g_dc.ops->enableLayer(&g_dc, 0);
}

/**
 * @brief
 *   Initialize the frame buffer
 */
static void init_frame_buffer(void)
{
    memset(gp_display_buffer, 0, sizeof(gp_display_buffer));
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Reset display for debugging (to be called before pin inits)
 */
void DISPLAY_reset(void)
{
    /*
     * Reset the displaymix, otherwise during debugging, the
     * debugger may not reset the display, then the behavior
     * is not right.
     */
    SRC_AssertSliceSoftwareReset(SRC, kSRC_DisplaySlice);
    while (kSRC_SliceResetInProcess == SRC_GetSliceResetState(SRC, kSRC_DisplaySlice))
    {
    }
}

/**
 * @brief
 *   Initialise the display and frame buffers
 */
void DISPLAY_initialise(void)
{
    init_frame_buffer();
    init_display();
}

/**
 * @brief
 *   Wait for previous frame buffer to be displayed & inactive buffer available
 * @return
 *   Address of available frame buffer
 */
uint32_t DISPLAY_wait_for_buffer(void)
{
    while (gb_frame_shown == false)
    {
    }

    return (uint32_t) gp_display_buffer[g_fb_index^1];
}

/**
 * @brief
 *   Send frame buffer contents to the display
 */
void DISPLAY_show_new_frame(void)
{
    gb_frame_shown = false;
    g_dc.ops->setFrameBuffer(&g_dc, 0, gp_display_buffer[g_fb_index^1]);
}

/*** end of file ***/
