/*****************************************************************************/
/**
 * @file 
 *   qdc.c
 * @brief 
 *   Quadrature decoder
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

#include "qdc.h"
#include "fsl_enc.h"
#include "fsl_xbara.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

#define ENC_BASEADDR            (ENC1)
#define ENC_IRQn                (ENC1_IRQn)
#define ENC_IRQHandler          (ENC1_IRQHandler)

#define EXAMPLE_TARGET_POS      (4u)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

static enc_config_t g_enc_config;
static volatile uint32_t g_enc_index_count = 0;

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

/**
 * @brief
 *   Interrupt handler for Quadrature decoder module
 */
void ENC_IRQHandler(void)
{
    const uint32_t status_flags = ENC_GetStatusFlags(ENC_BASEADDR);
    
    if (status_flags & kENC_INDEXPulseFlag)
    {
        g_enc_index_count++;
        ENC_ClearStatusFlags(ENC_BASEADDR, kENC_INDEXPulseFlag);
    }
    
    if (status_flags & kENC_PositionCompareFlag)
    {
        /** @todo This is probably not what we want to do, but otherwise we will
         *        keep receiving the interrupt as long as the position matches 
         *        the compare value 
         */
        ENC_SetInitialPositionValue(ENC_BASEADDR, 0);
        ENC_ClearStatusFlags(ENC_BASEADDR, kENC_PositionCompareFlag);
    }
    
    SDK_ISR_EXIT_BARRIER;
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Initialisation of Quadrature decoder pins and module
 */
void QDC_initialise(void)
{
    XBARA_Init(XBARA1);
    
    /* Phase A pin initialisation */
    XBARA_SetSignalsConnection(
        XBARA1, 
        kXBARA1_InputIomuxXbarInout35, 
        kXBARA1_OutputDec1Phasea);

    /* Phase B pin initialisation */
    XBARA_SetSignalsConnection(
        XBARA1, 
        kXBARA1_InputIomuxXbarInout34, 
        kXBARA1_OutputDec1Phaseb);

    /* Index pin initialisation */
    XBARA_SetSignalsConnection(
        XBARA1, 
        kXBARA1_InputIomuxXbarInout32, 
        kXBARA1_OutputDec1Index);

    /* Get the ENC module default configuration */
    ENC_GetDefaultConfig(&g_enc_config);
    
    /* Configure the INDEX action */
    g_enc_config.INDEXTriggerMode = kENC_INDEXTriggerOnRisingEdge;
    g_enc_config.positionCompareValue = EXAMPLE_TARGET_POS;
    
    /* Initialize the ENC module and initial position value */
    ENC_Init(ENC_BASEADDR, &g_enc_config);
    ENC_DoSoftwareLoadInitialPositionValue(ENC_BASEADDR);

    /* Interrupts */
    ENC_ClearStatusFlags(
        ENC_BASEADDR, 
        kENC_INDEXPulseFlag | kENC_PositionCompareFlag);
    ENC_EnableInterrupts(
        ENC_BASEADDR, 
        kENC_INDEXPulseInterruptEnable | kENC_PositionCompareInerruptEnable);
    EnableIRQ(ENC_IRQn);
}

/**
 * @brief
 *   Read the current position counter
 * @note
 *   The read operation also captures all the position counters to corresponding
 *   hold registers 
 * @return 
 *   32-bit position count
 */
uint32_t QDC_GetPositionValue(void)
{
    return ENC_GetPositionValue(ENC_BASEADDR);
}


/*** end of file ***/
