/*****************************************************************************/
/**
 * @file 
 *   semc.c
 * @brief 
 *   Smart External Memory Controller (SEMC) API layer
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

#include "semc.h"
#include "fsl_semc.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

#define SEMC_CLK_FREQ           (CLOCK_GetRootClockFreq(kCLOCK_Root_Semc))

#define SEMC_START_ADDRESS      (0x80000000u)
#define SEMC_END_ADDRESS        (0x81FFFFFFu)

#define SEMC_TEST_PATTERN       (0x55555555u)

#define SEMC_NCACHE_START       ((uint32_t)__NCACHE_REGION_START)
#define SEMC_NCACHE_SIZE        ((uint32_t)__NCACHE_REGION_SIZE)

/* PRECHARGE to ACTIVE/REFRESH command wait time (tRP) */
#define SEMC_PRE2ACT_NS         (15u)

/* ACTIVE to READ/WRITE delay (tRCD) */
#define SEMC_ACT2RW_NS          (15u)

/* REFRESH recovery time (Use the maximum of Trfc, Txsr) */
#define SEMC_RFRC_NS            (70u)

/* WRITE recovery time (tWR) */
#define SEMC_WRC_NS             (2u)

/* CKE off minimum time (CKE is off in self refresh at a minimum period tRAS) */
#define SEMC_CKEOFF_NS          (42u)

/* ACTIVE to PRECHARGE minimum time (tRAS) */
#define SEMC_ACT2PRE_NS         (40u)

/* SELF REFRESH recovery time */
#define SEMC_SRRC_NS            (70u)

/* REFRESH to REFRESH delay */
#define SEMC_REF2REF_NS         (60u)

/* ACTIVE to ACTIVE delay (tRC/tRDD) */
#define SEMC_ACT2ACT_NS         (2u)

/* Prescaler period */
#define SEMC_PRESCALE_NS        (160u * (1000000000u / SEMC_CLK_FREQ))

/* Refresh timer period (64ms/8192) */
#define SEMC_RT_NS              (64u * 1000000u / 8192u)

/* Urgent refresh threshold */
#define SEMC_UT_NS              (SEMC_RT_NS)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

static volatile uint32_t *gp_ncache = (uint32_t*)__NCACHE_REGION_START;

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
 *   Initialise the SEMC
 * @return
 *   kStatus_Success or kStatus_Fail
 */
status_t SEMC_initialise(void)
{
    semc_config_t config;
    semc_sdram_config_t sdram_config;

    /* Initializes the MAC configure structure to zero */
    memset(&config, 0, sizeof(semc_config_t));
    memset(&sdram_config, 0, sizeof(semc_sdram_config_t));

    /* Initialize SEMC */
    SEMC_GetDefaultConfig(&config);
    config.dqsMode = kSEMC_Loopbackdqspad; // For more accurate timing
    SEMC_Init(SEMC, &config);

    /* Configure SDRAM */
    sdram_config.csxPinMux              = kSEMC_MUXCSX0;
    sdram_config.address                = SEMC_START_ADDRESS;
    sdram_config.memsize_kbytes         = SEMC_SDRAM_SIZE / 1024u;
    sdram_config.portSize               = kSEMC_PortSize32Bit;
    sdram_config.burstLen               = kSEMC_Sdram_BurstLen8;
    sdram_config.columnAddrBitNum       = kSEMC_SdramColunm_9bit;
    sdram_config.casLatency             = kSEMC_LatencyThree;
    sdram_config.tPrecharge2Act_Ns      = SEMC_PRE2ACT_NS;
    sdram_config.tAct2ReadWrite_Ns      = SEMC_ACT2RW_NS;
    sdram_config.tRefreshRecovery_Ns    = SEMC_RFRC_NS;
    sdram_config.tWriteRecovery_Ns      = SEMC_WRC_NS;
    sdram_config.tCkeOff_Ns             = SEMC_CKEOFF_NS;
    sdram_config.tAct2Prechage_Ns       = SEMC_ACT2PRE_NS;
    sdram_config.tSelfRefRecovery_Ns    = SEMC_SRRC_NS;
    sdram_config.tRefresh2Refresh_Ns    = SEMC_REF2REF_NS;
    sdram_config.tAct2Act_Ns            = SEMC_ACT2ACT_NS;
    sdram_config.tPrescalePeriod_Ns     = SEMC_PRESCALE_NS;
    sdram_config.refreshPeriod_nsPerRow = SEMC_RT_NS;
    sdram_config.refreshUrgThreshold    = SEMC_UT_NS;
    sdram_config.refreshBurstLen        = 1u;
    sdram_config.delayChain             = 2u;
    
    status_t status = SEMC_ConfigureSDRAM(
        SEMC, 
        kSEMC_SDRAM_CS0, 
        &sdram_config, 
        SEMC_CLK_FREQ);

    return status;
}

/**
 * @brief
 *   Perform a self-test on the non-cachable region in external SDRAM
 * @return
 *   kStatus_Success or kStatus_Fail
 */
status_t SEMC_self_test(void)
{
    status_t status = kStatus_Success;
    
    for (uint32_t idx = 0; 
         (idx < (SEMC_NCACHE_SIZE/sizeof(uint32_t))) && 
           (kStatus_Success == status); 
         idx++)
    {
        register uint32_t temp = gp_ncache[idx];
      
        gp_ncache[idx] = SEMC_TEST_PATTERN;
    
        if (SEMC_TEST_PATTERN != gp_ncache[idx])
        {
            status = kStatus_Fail;
        }
        
        gp_ncache[idx] = temp;
    }
  
    return status;
}


/*** end of file ***/
