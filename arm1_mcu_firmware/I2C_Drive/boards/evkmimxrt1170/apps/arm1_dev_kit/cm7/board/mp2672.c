/*****************************************************************************/
/**
 * @file 
 *   mp2672.c
 * @brief 
 *   API for MPS MP2672 battery charger
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

#include "mp2672.h"
#include "i2c.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/* I2C slave address */
#define MP2672_I2C_ID                   (0x4Bu)

/* Register mapping */
#define MP2672_CONFIG1                  (0x00u)
#define MP2672_CONFIG2                  (0x01u)
#define MP2672_TIMER                    (0x02u)
#define MP2672_STATUS                   (0x03u)
#define MP2672_FAULT                    (0x04u)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

typedef struct {
  uint8_t cell_ovp_hys          : 1;
  uint8_t vbatt_pre             : 3;
  uint8_t chg_config            : 1;
  uint8_t vbatt_reg             : 3;
} mp2672_config1_t;

typedef struct {
  uint8_t lcc                   : 4;
  uint8_t balance_threshold_h2l : 1;
  uint8_t balance_threshold_l2h : 1;
  uint8_t vcell_bal             : 1;
  uint8_t ntc_type              : 1;
} mp2672_config2_t;

typedef struct {
  uint8_t en_susp               : 1;
  uint8_t chg_timer             : 2;
  uint8_t register_reset        : 1;
  uint8_t wd_timer              : 2;
  uint8_t i2c_wd_timer_reset    : 1;
  uint8_t fsw                   : 1;
} mp2672_timer_t;

typedef struct {
  uint8_t vsys                  : 1;
  uint8_t therm                 : 1;
  uint8_t battfloat             : 1;
  uint8_t ppm                   : 1;
  uint8_t chg                   : 2;
  uint8_t _reserved             : 2;
} mp2672_status_t;

typedef struct {
  uint8_t ntc                   : 3;
  uint8_t batt                  : 1;
  uint8_t timer                 : 1;
  uint8_t therm_sd              : 1;
  uint8_t input                 : 1;
  uint8_t wd                    : 1;
} mp2672_fault_t;

typedef struct {
  uint8_t bit0                  : 1;
  uint8_t bit1                  : 1;
  uint8_t bit2                  : 1;
  uint8_t bit3                  : 1;
  uint8_t bit4                  : 1;
  uint8_t bit5                  : 1;
  uint8_t bit6                  : 1;
  uint8_t bit7                  : 1;
} bitwise_t;

typedef union {
  mp2672_config1_t              config1;
  mp2672_config2_t              config2;
  mp2672_timer_t                timer;
  mp2672_status_t               status;
  mp2672_fault_t                fault;
  bitwise_t                     bitwise;
  uint8_t                       byte;
} mp2672_reg_t;

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
 *   Initialise the MP2672 battery charger
 */
void MP2672_initialise(void)
{
}

/*** end of file ***/
