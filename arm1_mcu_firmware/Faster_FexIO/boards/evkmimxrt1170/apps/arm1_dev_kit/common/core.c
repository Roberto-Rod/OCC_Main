/*****************************************************************************/
/**
 * @file 
 *   core.c
 * @brief 
 *   Top level layer for multicore management
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

#include "core.h"
#include "mcmgr.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/* Address of memory, from which the secondary core will boot */
#define CORE1_BOOT_ADDRESS          ((void*)0x20200000)

#define CORE1_IMAGE_START           (core1_image_start)

/* Data that is sent to secondary core when started */
#define CORE1_STARTUP_DATA          (2u)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

static volatile uint16_t g_remote_event = 0;

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

extern unsigned char core1_image_start[];

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

static uint32_t get_image_size(void);
static void remote_event_handler(uint16_t data, void *p_context);

/*!
 * @brief 
 *   Application-specific implementation of the SystemInitHook() weak function
 */
void SystemInitHook(void)
{
    /* Initialize MCMGR - low level multicore management library. Call this
       function as close to the reset entry as possible to allow CoreUp event
       triggering. The SystemInitHook() weak function overloading is used in this
       application. */
    (void)MCMGR_EarlyInit();
}

/*!
 * @brief 
 *   Get size of secondary core image
 * @return
 *   Size of image in bytes
 */
uint32_t get_image_size(void)
{
#pragma section = "__core1_image"
    const uint32_t image_size = 
        (uint32_t)__section_end("__core1_image") - (uint32_t)&CORE1_IMAGE_START;
    
    return image_size;
}

/*!
 * @brief 
 *   Handler for events passed back from the remote core
 * @param
 *   data Event data
 * @param
 *   p_context Pointer to event context (ignored)
 */
static void remote_event_handler(uint16_t data, void *p_context)
{
    g_remote_event = data;
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Initialise the multicore manager
 * @return
 *   kStatus_Success or kStatus_Fail
 */
status_t CORE_initialise(void)
{
    status_t status = kStatus_Fail;
  
    /* Initialize MCMGR, install generic event handlers */
    const mcmgr_status_t mcmgr_status = MCMGR_Init();
    
    if (kStatus_MCMGR_Success == mcmgr_status)
    {
        status = kStatus_Success;
    }
      
    return status; 
}

/**
 * @brief
 *   Copy the secondary core image from flash location to the target RAM memory
 *   and register handlers 
 * @return
 *   kStatus_Success or kStatus_Fail
 */
status_t CORE_load_remote(void)
{
    status_t status = kStatus_Fail;

    const uint32_t image_size = get_image_size();

    (void)memcpy(
        (void*)(char*)CORE1_BOOT_ADDRESS, 
        (void*)CORE1_IMAGE_START, 
        image_size);

#ifdef APP_INVALIDATE_CACHE_FOR_SECONDARY_CORE_IMAGE_MEMORY
    /* Invalidate cache for memory range that image has been copied to 
       (optional for some platforms/cases) */
    if (LMEM_PSCCR_ENCACHE_MASK == (LMEM_PSCCR_ENCACHE_MASK & LMEM->PSCCR))
    {
        L1CACHE_CleanInvalidateSystemCacheByRange(
            (uint32_t)CORE1_BOOT_ADDRESS, 
            image_size);
    }
#endif /* APP_INVALIDATE_CACHE_FOR_SECONDARY_CORE_IMAGE_MEMORY*/

    /* Register the application events before starting the secondary core */
    const mcmgr_status_t mcmgr_status = MCMGR_RegisterEvent(
        kMCMGR_RemoteApplicationEvent, 
        remote_event_handler, 
        ((void *)0));

    if (kStatus_MCMGR_Success == mcmgr_status)
    {
        status = kStatus_Success;
    }
      
    return status; 
}

/**
 * @brief
 *   Start the secondary core application
 * @return
 *   kStatus_Success or kStatus_Fail
 */
status_t CORE_start_remote(void)
{
    status_t status = kStatus_Fail;
  
    const mcmgr_status_t mcmgr_status = MCMGR_StartCore(
        kMCMGR_Core1, 
        (void*)(char*)CORE1_BOOT_ADDRESS, 
        CORE1_STARTUP_DATA, 
        kMCMGR_Start_Synchronous);
    
    if (kStatus_MCMGR_Success == mcmgr_status)
    {
        status = kStatus_Success;

        /* Wait until secondary core app signals that it has been started */
        while (CORE_EVENT_REMOTE_READY != g_remote_event)
        {
        }
    }
      
    return status; 
}

/**
 * @brief
 *   Get data that was received from primary core application during start-up
 * @return
 *   Start-up data
 */
uint32_t CORE_get_startup_data(void)
{
    uint32_t data;
    mcmgr_status_t mcmgr_status;
    
    /* Get the startup data */
    do
    {
        mcmgr_status = MCMGR_GetStartupData(&data);
    } while (kStatus_MCMGR_Success != mcmgr_status);
    
    return data;
}

/**
 * @brief
 *   Trigger an event from the secondary core application
 * @param
 *   event Event data to be sent to primary core
 * @return
 *   kStatus_Success or kStatus_Fail
 */
status_t CORE_trigger_event(uint16_t event)
{
    status_t status = kStatus_Fail;

    /* Signal the other core we are ready by triggering the event and passing the event */
    const mcmgr_status_t mcmgr_status = MCMGR_TriggerEvent(
        kMCMGR_RemoteApplicationEvent, 
        event);

    if (kStatus_MCMGR_Success == mcmgr_status)
    {
        status = kStatus_Success;
    }
      
    return status; 
}


/*** end of file ***/
