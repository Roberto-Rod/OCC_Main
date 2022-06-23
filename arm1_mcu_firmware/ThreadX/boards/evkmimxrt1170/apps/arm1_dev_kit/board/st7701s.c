/*****************************************************************************/
/**
 * @file 
 *   st7701s.c
 * @brief 
 *   API for Sitronix ST7701S LCD display driver IC
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

#include "st7701s.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/* System function commands */
#define NOP                     (0x00u)
#define SWRESET                 (0x01u)
#define RDDID                   (0x04u)
#define RDNUMED                 (0x05u)
#define RDRED                   (0x06u)
#define RDGREEN                 (0x07u)
#define RDBLUE                  (0x08u)
#define RDDPM                   (0x0Au)
#define RDDMADCTL               (0x0Bu)
#define RDDCOLMOD               (0x0Cu)
#define RDDIM                   (0x0Du)
#define RDDSM                   (0x0Eu)
#define RDDSDR                  (0x0Fu)
#define SLPIN                   (0x10u)
#define SLPOUT                  (0x11u)
#define PTLON                   (0x12u)
#define NORON                   (0x13u)
#define INVOFF                  (0x20u)
#define INVON                   (0x21u)
#define ALLPOFF                 (0x22u)
#define ALLPON                  (0x23u)
#define GAMSET                  (0x26u)
#define DISPOFF                 (0x28u)
#define DISPON                  (0x29u)
#define TEOFF                   (0x34u)
#define TEON                    (0x35u)
#define MADCTL                  (0x36u)
#define IDMOFF                  (0x38u)
#define IDMON                   (0x39u)
#define COLMOD                  (0x3Au)
#define GSL                     (0x45u)
#define WRDIBV                  (0x51u)
#define RDDISBV                 (0x52u)
#define WRCTRLD                 (0x53u)
#define RRCTRLD                 (0x54u)
#define WRCABC                  (0x55u)
#define RRCABC                  (0x56u)
#define WRCABCMB                (0x5Eu)
#define RRCABCMB                (0x5Fu)
#define RDABCSD                 (0x68u)
#define RDBWLB                  (0x70u)
#define RDBkx                   (0x71u)
#define RDBky                   (0x72u)
#define RDWx                    (0x73u)
#define RDWy                    (0x74u)
#define RDRGLB                  (0x75u)
#define RDRx                    (0x76u)
#define RDRy                    (0x77u)
#define RDGx                    (0x78u)
#define RDGy                    (0x79u)
#define RDBALB                  (0x7Au)
#define RDBx                    (0x7Bu)
#define RDBy                    (0x7Cu)
#define RDAx                    (0x7Du)
#define RDAy                    (0x7Eu)
#define RDDDBS_CHKSUM           (0xA1u)
#define RDDDBC                  (0xA8u)
#define RDFCS                   (0xAAu)
#define RDCCS                   (0xAFu)
#define PVGAMCTRL               (0xB0u)
#define NVGAMCTRL               (0xB1u)
#define DGMEN                   (0xB8u)
#define DGMLUTR                 (0xB9u)
#define DGMLUTB                 (0xBAu)
#define LNESET                  (0xC0u)
#define PORCTRL                 (0xC1u)
#define INVSEL                  (0xC2u)
#define RGBCTRL                 (0xC3u)
#define PARCTRL                 (0xC5u)
#define SDIR                    (0xC7u)
#define PDOTSET                 (0xC8u)
#define COLCTRL                 (0xCDu)
#define RDID1                   (0xDAu)
#define RDID2                   (0xDBu)
#define RDID3                   (0xDCu)
#define SRECTRL                 (0xE0u)
#define NRCTRL                  (0xE1u)
#define SECTRL                  (0xE2u)
#define CCCTRL                  (0xE3u)
#define SKCTRL                  (0xE4u)
#define NVMSETE                 (0xEAu)
#define CABCCTRL                (0xEEu)
#define CN2BKxSEL               (0xFFu)

/* Command2_BK1 addresses */
#define VRHS                    (0xB0u)
#define VCOMS                   (0xB1u)
#define VGHSS                   (0xB2u)
#define TESCMD                  (0xB3u)
#define VGLS                    (0xB5u)
#define VRHDV                   (0xB6u)
#define PWCTRL1                 (0xB7u)
#define PWCTRL2                 (0xB8u)
#define PWCTRL3                 (0xB9u)
#define PCLKS1                  (0xBAu)
#define PCLKS2                  (0xBBu)
#define PCLKS3                  (0xBCu)
#define PDR1                    (0xC1u)
#define PDR2                    (0xC2u)
#define MIPISET1                (0xD0u)
#define MIPISET2                (0xD1u)
#define MIPISET3                (0xD2u)
#define MIPISET4                (0xD3u)

/* Command2_BK3 addresses */
#define NVMEN                   (0xC8u)
#define NVMSET                  (0xCAu)
#define PROMACT                 (0xCCu)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

const display_operations_t st7701s_ops = {
    .init   = ST7701S_initialise,
    .deinit = ST7701S_deinitialise,
    .start  = ST7701S_start,
    .stop   = ST7701S_stop,
};

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Initialise the ST7701S display driver
 * @param[in]
 *   ph_handle Address of display device handle
 * @param[in]
 *   p_config Address of configuration structure
 * @return
 *   Status
 */
status_t ST7701S_initialise(
    display_handle_t *ph_handle, 
    const display_config_t *p_config)
{
    /** @todo 
     *   Initialise ST7701S display using data sheet & fsl_rm68200.c for reference
     */  
  
    return kStatus_Success;
}

/**
 * @brief
 *   Deinitialise the ST7701S display driver
 * @param[in]
 *   ph_handle Address of display device handle
 * @param[in]
 *   p_config Address of configuration structure
 * @return
 *   Status
 */
status_t ST7701S_deinitialise(
    display_handle_t *ph_handle)
{
    const st7701s_resource_t *resource = 
        (const st7701s_resource_t*)(ph_handle->resource);

    (void)MIPI_DSI_DCS_EnterSleepMode(resource->dsiDevice, true);

    resource->pullResetPin(false);
    resource->pullPowerPin(false);

    return kStatus_Success;
}

/**
 * @brief
 *   Start the ST7701S display driver
 * @param[in]
 *   ph_handle Address of camera device handle
 * @return
 *   Status
 */
status_t ST7701S_start(
    display_handle_t *ph_handle)
{
    const st7701s_resource_t *resource = 
        (const st7701s_resource_t*)(ph_handle->resource);

    return MIPI_DSI_DCS_SetDisplayOn(resource->dsiDevice, true);
}

/**
 * @brief
 *   Stop the ST7701S display driver
 * @param[in]
 *   ph_handle Address of camera device handle
 * @return
 *   Status
 */
status_t ST7701S_stop(
    display_handle_t *ph_handle)
{
    const st7701s_resource_t *resource = 
        (const st7701s_resource_t*)(ph_handle->resource);

    return MIPI_DSI_DCS_SetDisplayOn(resource->dsiDevice, false);
}


/*** end of file ***/
