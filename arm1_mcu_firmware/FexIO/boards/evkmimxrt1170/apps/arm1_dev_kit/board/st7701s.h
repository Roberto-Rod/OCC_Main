/*****************************************************************************/
/**
 * @file 
 *   st7701s.h
 * @brief 
 *   API for Sitronix ST7701S LCD display driver IC
 *
 *****************************************************************************/

/*
 * Copyright (c) 2022 Occuity Ltd. All rights reserved.
 */

#if !defined(ST7701S_H)
#define ST7701S_H

/*****************************************************************************/
/* Included Files                                                            */
/*****************************************************************************/

#include "fsl_display.h"
#include "fsl_mipi_dsi_cmd.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

typedef struct st7701s_resource
{
    mipi_dsi_device_t *dsiDevice;      /*!< MIPI DSI device. */
    void (*pullResetPin)(bool pullUp); /*!< Function to pull reset pin high or low. */
    void (*pullPowerPin)(bool pullUp); /*!< Function to pull power pin high or low. */
} st7701s_resource_t;

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

extern const display_operations_t st7701s_ops;

/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/

status_t ST7701S_initialise(
    display_handle_t *ph_handle, 
    const display_config_t *p_config);
status_t ST7701S_deinitialise(
    display_handle_t *ph_handle);
status_t ST7701S_start(
    display_handle_t *ph_handle);
status_t ST7701S_stop(
    display_handle_t *ph_handle);

#endif // defined(ST7701S_H)


/*** end of file ***/
