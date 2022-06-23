/*****************************************************************************/
/**
 * @file 
 *   tx_api.c
 * @brief 
 *   ThreadX Application Interface
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

#include "tx_api.h"
#include "debug.h"
#include "video.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

#define BYTE_POOL_SIZE                  (9120u)
#define BLOCK_POOL_SIZE                 (100ul)

/* Video thread parameters */
#define VIDEO_THREAD_STACK_SIZE         (1024ul)
#define VIDEO_THREAD_PRIORITY           (1u)
#define VIDEO_THREAD_PREEMPT_THRESHOLD  (1u)

/* Debug thread parameters */
#define DEBUG_THREAD_STACK_SIZE         (1024ul)
#define DEBUG_THREAD_PRIORITY           (2u)
#define DEBUG_THREAD_PREEMPT_THRESHOLD  (2u)

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

/* Define the ThreadX object control blocks */
static TX_BYTE_POOL byte_pool;
static TX_BLOCK_POOL block_pool;
static TX_THREAD debug_thread;
static TX_THREAD video_thread;

static UCHAR gp_memory_pool[BYTE_POOL_SIZE];

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

static UINT create_debug_thread(VOID **pp_pool);
static UINT create_video_thread(VOID **pp_pool);

/**
 * @brief
 *   Allocate memory and create debug thread
 * @param[in,out]
 *   pp_pool Pointer to address of memory pool
 * @return
 *   TX_SUCCESS or error code
 */
static UINT create_debug_thread(VOID **pp_pool)
{
    /* Allocate the stack for this thread */
    UINT status = tx_byte_allocate(
        &byte_pool, 
        pp_pool, 
        DEBUG_THREAD_STACK_SIZE, 
        TX_NO_WAIT);
    
    if (TX_SUCCESS == status)
    {
        /* Create the thread */
        status = tx_thread_create(
            &debug_thread, 
            "debug thread", 
            DEBUG_thread, 
            NULL,  
            *pp_pool, 
            DEBUG_THREAD_STACK_SIZE, 
            DEBUG_THREAD_PRIORITY, 
            DEBUG_THREAD_PREEMPT_THRESHOLD, 
            TX_NO_TIME_SLICE, 
            TX_AUTO_START);
    }

    return status;
}

/**
 * @brief
 *   Allocate memory and create video thread
 * @param[in,out]
 *   pp_pool Pointer to address of memory pool
 * @return
 *   TX_SUCCESS or error code
 */
static UINT create_video_thread(VOID **pp_pool)
{
    /* Allocate the stack for this thread */
    UINT status = tx_byte_allocate(
        &byte_pool, 
        pp_pool, 
        VIDEO_THREAD_STACK_SIZE, 
        TX_NO_WAIT);
    
    if (TX_SUCCESS == status)
    {
        /* Create the thread */
        status = tx_thread_create(
            &video_thread, 
            "video thread", 
            VIDEO_thread, 
            NULL,  
            *pp_pool, 
            VIDEO_THREAD_STACK_SIZE, 
            VIDEO_THREAD_PRIORITY, 
            VIDEO_THREAD_PREEMPT_THRESHOLD, 
            TX_NO_TIME_SLICE, 
            TX_AUTO_START);
    }

    return status;
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Define the initial system application
 * @param[in,out]
 *   p_first_unused_memory Not used
 */
void tx_application_define(void *p_first_unused_memory)
{
    CHAR *p_pool = TX_NULL;

    TX_THREAD_NOT_USED(p_first_unused_memory);

    /* Create a byte memory pool from which to allocate the thread stacks */
    UINT status = tx_byte_pool_create(
        &byte_pool, "byte pool", gp_memory_pool, BYTE_POOL_SIZE);

    if (TX_SUCCESS == status)
    {
        status = create_debug_thread((VOID **)&p_pool);
    }
    
    if (TX_SUCCESS == status)
    {
        status = create_video_thread((VOID **)&p_pool);
    }
    
    if (TX_SUCCESS == status)
    {
        /* Allocate the memory for a small block pool */
        status = tx_byte_allocate(
            &byte_pool, (VOID **)&p_pool, BLOCK_POOL_SIZE, TX_NO_WAIT);
    }

    if (TX_SUCCESS == status)
    {
        /* Create a block memory pool to allocate a message buffer from */
        status = tx_block_pool_create(
            &block_pool, "block pool", sizeof(ULONG), p_pool, BLOCK_POOL_SIZE);
    }
    
    if (TX_SUCCESS == status)
    {
        /* Allocate a block and release the block memory.  */
        status = tx_block_allocate(&block_pool, (VOID **)&p_pool, TX_NO_WAIT);
    }

    if (TX_SUCCESS == status)
    {
        /* Release the block back to the pool.  */
        status = tx_block_release(p_pool);
    }
    
    if (TX_SUCCESS != status)
    {
        DEBUG_printf("ThreadX application failure (error: %d)\r\n", status);
    }
}


/*** end of file ***/
