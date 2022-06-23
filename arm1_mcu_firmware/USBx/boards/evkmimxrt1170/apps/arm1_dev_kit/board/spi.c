/*****************************************************************************/
/**
 * @file 
 *   spi.c
 * @brief 
 *   SPI bus API layer
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

#include "spi.h"
#include "fsl_lpspi.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

typedef struct
{
    LPSPI_Type *p_base;
    clock_root_t clock_root;
    clock_root_config_t clock_root_config;
    uint32_t baud_rate;
} spi_config_t;

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

static bool gb_spi_initialised = false;

static const spi_config_t g_config[] = 
{
    {
        /* LPSPI1 (unused) */
        .p_base = LPSPI1,
        .clock_root = kCLOCK_Root_Lpspi1
    },
    {
        /* LPSPI2 (unused) */
        .p_base = LPSPI2,
        .clock_root = kCLOCK_Root_Lpspi2
    },
    {
        /* LPSPI3 clock frequency = 400MHz / 20 = 20MHz; baud rate = 10MHz */
        .p_base = LPSPI3,
        .clock_root = kCLOCK_Root_Lpspi3,
        .clock_root_config.clockOff = false,
        .clock_root_config.mux = kCLOCK_M7_ClockRoot_MuxOscRc400M,
        .clock_root_config.div = 20u,
        .baud_rate = 10000000ul
    },
    {
        /* LPSPI4 (unused) */
        .p_base = LPSPI4,
        .clock_root = kCLOCK_Root_Lpspi4
    },
    {
        /* LPSPI5 (unused) */
        .p_base = LPSPI5,
        .clock_root = kCLOCK_Root_Lpspi5
    },
    {
        /* LPI2C6 (unused) */
        .p_base = LPSPI6,
        .clock_root = kCLOCK_Root_Lpspi6
    }
};

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

static void master_init(spi_bus_t bus);

/**
 * @brief
 *   Initialise the specified SPI bus
 * @param
 *   bus SPI bus index
 */
static void master_init(spi_bus_t bus)
{
    clock_root_t root = g_config[bus].clock_root;
    
    lpspi_master_config_t config;

    LPSPI_MasterGetDefaultConfig(&config);
    config.baudRate = g_config[bus].baud_rate;
    
    CLOCK_SetRootClock(root, &g_config[bus].clock_root_config);
    
    LPSPI_MasterInit(
        g_config[bus].p_base, &config, CLOCK_GetRootClockFreq(root));
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Initialise the SPI buses
 */
void SPI_initialise(void)
{
    if (false == gb_spi_initialised)
    {
        master_init(SPI3);
        gb_spi_initialised = true;
    }
}

/**
 * @brief
 *   Send data on specifide SPI bus
 * @param
 *   bus SPI bus index
 * @param
 *   pcs Chip Select index
 * @param[in]
 *   p_data Pointer to data to be written
 * @param
 *   size Number of bytes to be written
 * @return
 *   Status
 */
status_t SPI_send(
    spi_bus_t bus, 
    spi_pcs_t pcs, 
    const uint8_t *p_data, 
    uint8_t size)
{
    LPSPI_Type *p_base;
    
    lpspi_transfer_t xfer = 
    {
        .configFlags    = kLPSPI_MasterPcsContinuous,
        .txData         = (uint8_t*)p_data,
        .rxData         = NULL,
        .dataSize       = size
    };
    
    switch (bus)
    {
        default:
        case SPI1:      p_base = LPSPI1;    break;
        case SPI2:      p_base = LPSPI2;    break;
        case SPI3:      p_base = LPSPI3;    break;
        case SPI4:      p_base = LPSPI4;    break;
        case SPI5:      p_base = LPSPI5;    break;
        case SPI6:      p_base = LPSPI6;    break;
    }
  
    switch (pcs)
    {
        default:
        case SPI_CS0:   xfer.configFlags |= kLPSPI_MasterPcs0;  break;
        case SPI_CS1:   xfer.configFlags |= kLPSPI_MasterPcs1;  break;
        case SPI_CS2:   xfer.configFlags |= kLPSPI_MasterPcs2;  break;
        case SPI_CS3:   xfer.configFlags |= kLPSPI_MasterPcs3;  break;
    }
  
    return LPSPI_MasterTransferBlocking(p_base, &xfer);
}


/*** end of file ***/
