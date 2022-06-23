/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _DISPLAY_SUPPORT_H_
#define _DISPLAY_SUPPORT_H_

#include "fsl_dc_fb.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* @TEST_ANCHOR */

#define DEMO_PANEL_RK055AHD091 0 /* 720 * 1280 */
#define DEMO_PANEL_RK055IQH091 1 /* 540 * 960  */
#define DEMO_PANEL_RK055MHD091 2 /* 720 * 1280 */

#define DEMO_DISPLAY_CONTROLLER_ELCDIF  0
#define DEMO_DISPLAY_CONTROLLER_LCDIFV2 1

#ifndef DEMO_PANEL
#define DEMO_PANEL DEMO_PANEL_RK055AHD091
#endif

#ifndef DEMO_DISPLAY_CONTROLLER
/* Use LCDIFV2 by default, could use ELCDIF by changing this macro. */
#define DEMO_DISPLAY_CONTROLLER DEMO_DISPLAY_CONTROLLER_LCDIFV2
#endif

#define DISPLAY_BUFFER_FIXED_ADDRESS 0

#if DISPLAY_BUFFER_FIXED_ADDRESS
#define DISPLAY_BUFFER0_ADDR (0x80000000u)
#define DISPLAY_BUFFER1_ADDR (0x80200000u)
#endif

/*
 * Use the MIPI dumb panel
 */

/* Definitions for the frame buffer. */
#define DEMO_BUFFER_COUNT 2 /* 2 is enough for DPI interface display. */

#ifndef DEMO_USE_XRGB8888
#define DEMO_USE_XRGB8888 0
#endif

#if DEMO_USE_XRGB8888
#define DEMO_BUFFER_PIXEL_FORMAT   kVIDEO_PixelFormatXRGB8888
#define DEMO_BUFFER_BYTE_PER_PIXEL (4u)
#else
#define DEMO_BUFFER_PIXEL_FORMAT   kVIDEO_PixelFormatRGB565
#define DEMO_BUFFER_BYTE_PER_PIXEL (2u)
#endif

#if ((DEMO_PANEL_RK055AHD091 == DEMO_PANEL) || (DEMO_PANEL_RK055MHD091 == DEMO_PANEL))

#define DEMO_PANEL_WIDTH  (720u)
#define DEMO_PANEL_HEIGHT (1280u)

#elif (DEMO_PANEL_RK055IQH091 == DEMO_PANEL)

#define DEMO_PANEL_WIDTH  (540u)
#define DEMO_PANEL_HEIGHT (960u)

#endif

#define DISPLAY_BUFFER_WIDTH  DEMO_PANEL_WIDTH
#define DISPLAY_BUFFER_HEIGHT DEMO_PANEL_HEIGHT

/* Where the frame buffer is shown in the screen. */
#define DISPLAY_BUFFER_START_X (0)
#define DISPLAY_BUFFER_START_Y (0)

/* There is not frame buffer aligned requirement, consider the 64-bit AXI data
 * bus width and 32-byte cache line size, the frame buffer alignment is set to
 * 32 byte.
 */
#define DISPLAY_BUFFER_ALIGN (32u)

extern const dc_fb_t g_dc;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

status_t BOARD_PrepareDisplayController(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _DISPLAY_SUPPORT_H_ */
