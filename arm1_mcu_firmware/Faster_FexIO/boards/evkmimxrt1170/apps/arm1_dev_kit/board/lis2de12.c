/*****************************************************************************/
/**
 * @file 
 *   lis2de12.c
 * @brief 
 *   API for ST LIS2DE12 digital output motion sensor
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

#include "lis2de12.h"
#include "i2c.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/* I2C slave address */
#define LIS2DE12_I2C_ID                 (0x32u)

/* Device Identification (Who am I) */
#define LIS2DS12_ID                     (0x43u)

#define LIS2DE12_REG_SIZE               (sizeof(uint8_t))

/* Register mapping */
#define LIS2DE12_MODULE_8BIT            (0x0Cu)
#define LIS2DE12_WHO_AM_I               (0x0Fu)
#define LIS2DE12_CTRL1                  (0x20u)
#define LIS2DE12_CTRL2                  (0x21u)
#define LIS2DE12_CTRL3                  (0x22u)
#define LIS2DE12_CTRL4                  (0x23u)
#define LIS2DE12_CTRL5                  (0x24u)
#define LIS2DE12_FIFO_CTRL              (0x25u)
#define LIS2DE12_OUT_T                  (0x26u)
#define LIS2DE12_STATUS                 (0x27u)
#define LIS2DE12_OUT_X_L                (0x28u)
#define LIS2DE12_OUT_X_H                (0x29u)
#define LIS2DE12_OUT_Y_L                (0x2Au)
#define LIS2DE12_OUT_Y_H                (0x2Bu)
#define LIS2DE12_OUT_Z_L                (0x2Cu)
#define LIS2DE12_OUT_Z_H                (0x2Du)
#define LIS2DE12_FIFO_THS               (0x2Eu)
#define LIS2DE12_FIFO_SRC               (0x2Fu)
#define LIS2DE12_FIFO_SAMPLES           (0x30u)
#define LIS2DE12_TAP_6D_THS             (0x31u)
#define LIS2DE12_INT_DUR                (0x32u)
#define LIS2DE12_WAKE_UP_THS            (0x33u)
#define LIS2DE12_WAKE_UP_DUR            (0x34u)
#define LIS2DE12_FREE_FALL              (0x35u)
#define LIS2DE12_STATUS_DUP             (0x36u)
#define LIS2DE12_WAKE_UP_SRC            (0x37u)
#define LIS2DE12_TAP_SRC                (0x38u)
#define LIS2DE12_6D_SRC                 (0x39u)
#define LIS2DE12_STEP_COUNTER_MINTHS    (0x3Au)
#define LIS2DE12_STEP_COUNTER_L         (0x3Bu)
#define LIS2DE12_STEP_COUNTER_H         (0x3Cu)
#define LIS2DE12_FUNC_CK_GATE           (0x3Du)
#define LIS2DE12_FUNC_SRC               (0x3Eu)
#define LIS2DE12_FUNC_CTRL              (0x3Fu)
#define LIS2DE12_PEDO_DEB_REG           (0x2Bu)
#define LIS2DE12_SLV0_ADD               (0x30u)
#define LIS2DE12_SLV0_SUBADD            (0x31u)
#define LIS2DE12_SLV0_CONFIG            (0x32u)
#define LIS2DE12_DATAWRITE_SLV0         (0x33u)
#define LIS2DE12_SM_THS                 (0x34u)
#define LIS2DE12_STEP_COUNT_DELTA       (0x3Au)
#define LIS2DE12_CTRL2_ADV              (0x3Fu)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

typedef struct {
  uint8_t bdu                 : 1;
  uint8_t hf_odr              : 1;
  uint8_t fs                  : 2;
  uint8_t odr                 : 4;
} lis2de12_ctrl1_t;

typedef struct {
  uint8_t sim                 : 1;
  uint8_t i2c_disable         : 1;
  uint8_t if_add_inc          : 1;
  uint8_t fds_slope           : 1;
  uint8_t func_cfg_en         : 1;
  uint8_t not_used_01         : 1;
  uint8_t soft_reset          : 1;
  uint8_t boot                : 1;
} lis2de12_ctrl2_t;

typedef struct {
  uint8_t pp_od               : 1;
  uint8_t h_lactive           : 1;
  uint8_t lir                 : 1;
  uint8_t tap_z_en            : 1;
  uint8_t tap_y_en            : 1;
  uint8_t tap_x_en            : 1;
  uint8_t st                  : 2;
} lis2de12_ctrl3_t;

typedef struct {
  uint8_t int1_drdy           : 1;
  uint8_t int1_fth            : 1;
  uint8_t int1_6d             : 1;
  uint8_t int1_tap            : 1;
  uint8_t int1_ff             : 1;
  uint8_t int1_wu             : 1;
  uint8_t int1_s_tap          : 1;
  uint8_t int1_master_drdy    : 1;
} lis2de12_ctrl4_t;

typedef struct {
  uint8_t int2_drdy           : 1;
  uint8_t int2_fth            : 1;
  uint8_t int2_step_det       : 1;
  uint8_t int2_sig_mot        : 1;
  uint8_t int2_tilt           : 1;
  uint8_t int2_on_int1        : 1;
  uint8_t int2_boot           : 1;
  uint8_t drdy_pulsed         : 1;
} lis2de12_ctrl5_t;

typedef struct {
  uint8_t if_cs_pu_dis        : 1;
  uint8_t not_used_01         : 2;
  uint8_t module_to_fifo      : 1;
  uint8_t int2_step_count_ov  : 1;
  uint8_t fmode               : 3;
} lis2de12_fifo_ctrl_t;

typedef struct {
  uint8_t drdy                : 1;
  uint8_t ff_ia               : 1;
  uint8_t _6d_ia              : 1;
  uint8_t single_tap          : 1;
  uint8_t double_tap          : 1;
  uint8_t sleep_state         : 1;
  uint8_t wu_ia               : 1;
  uint8_t fifo_ths            : 1;
} lis2de12_status_t;

typedef struct {
  uint8_t fth                 : 8;
} lis2de12_fifo_ths_t;

typedef struct {
  uint8_t not_used_01         : 5;
  uint8_t diff                : 1;
  uint8_t fifo_ovr            : 1;
  uint8_t fth                 : 1;
} lis2de12_fifo_src_t;

typedef struct {
  uint8_t tap_ths             : 5;
  uint8_t _6d_ths             : 2;
  uint8_t _4d_en              : 1;
} lis2de12_tap_6d_ths_t;

typedef struct {
  uint8_t shock               : 2;
  uint8_t quiet               : 2;
  uint8_t lat                 : 4;
} lis2de12_int_dur_t;

typedef struct {
  uint8_t wu_ths              : 6;
  uint8_t sleep_on            : 1;
  uint8_t single_double_tap   : 1;
} lis2de12_wake_up_ths_t;

typedef struct {
  uint8_t sleep_dur           : 4;
  uint8_t int1_fss7           : 1;
  uint8_t wu_dur              : 2;
  uint8_t ff_dur              : 1;
} lis2de12_wake_up_dur_t;

typedef struct {
  uint8_t ff_ths              : 3;
  uint8_t ff_dur              : 5;
} lis2de12_free_fall_t;

typedef struct {
  uint8_t drdy                : 1;
  uint8_t ff_ia               : 1;
  uint8_t _6d_ia              : 1;
  uint8_t single_tap          : 1;
  uint8_t double_tap          : 1;
  uint8_t sleep_state         : 1;
  uint8_t wu_ia               : 1;
  uint8_t ovr                 : 1;
} lis2de12_status_dup_t;

typedef struct {
  uint8_t z_wu                : 1;
  uint8_t y_wu                : 1;
  uint8_t x_wu                : 1;
  uint8_t wu_ia               : 1;
  uint8_t sleep_state_ia      : 1;
  uint8_t ff_ia               : 1;
  uint8_t not_used_01         : 2;
} lis2de12_wake_up_src_t;

typedef struct {
  uint8_t z_tap               : 1;
  uint8_t y_tap               : 1;
  uint8_t x_tap               : 1;
  uint8_t tap_sign            : 1;
  uint8_t double_tap          : 1;
  uint8_t single_tap          : 1;
  uint8_t tap_ia              : 1;
  uint8_t not_used_01         : 1;
} lis2de12_tap_src_t;

typedef struct {
  uint8_t xl                  : 1;
  uint8_t xh                  : 1;
  uint8_t yl                  : 1;
  uint8_t yh                  : 1;
  uint8_t zl                  : 1;
  uint8_t zh                  : 1;
  uint8_t _6d_ia              : 1;
  uint8_t not_used_01         : 1;
} lis2de12_6d_src_t;

typedef struct {
  uint8_t sc_mths             : 6;
  uint8_t pedo4g              : 1;
  uint8_t rst_nstep           : 1;
} lis2de12_step_counter_minths_t;

typedef struct {
  uint8_t ck_gate_func        : 1;
  uint8_t step_detect         : 1;
  uint8_t rst_pedo            : 1;
  uint8_t rst_sign_mot        : 1;
  uint8_t sig_mot_detect      : 1;
  uint8_t fs_src              : 2;
  uint8_t tilt_int            : 1;
} lis2de12_func_ck_gate_t;

typedef struct {
  uint8_t sensorhub_end_op    : 1;
  uint8_t module_ready        : 1;
  uint8_t rst_tilt            : 1;
  uint8_t not_used_01         : 5;
} lis2de12_func_src_t;

typedef struct {
  uint8_t step_cnt_on         : 1;
  uint8_t sign_mot_on         : 1;
  uint8_t master_on           : 1;
  uint8_t tud_en              : 1;
  uint8_t tilt_on             : 1;
  uint8_t module_on           : 1;
  uint8_t not_used_01         : 2;
} lis2de12_func_ctrl_t;

typedef struct {
  uint8_t deb_step            : 3;
  uint8_t deb_time            : 5;
} lis2de12_pedo_deb_reg_t;

typedef struct {
  uint8_t rw_0                : 1;
  uint8_t slave0_add          : 7;
} lis2de12_slv0_add_t;

typedef struct {
  uint8_t slave0_reg          : 8;
} lis2de12_slv0_subadd_t;

typedef struct {
  uint8_t slave0_numop        : 3;
  uint8_t not_used_01         : 5;
} lis2de12_slv0_config_t;

typedef struct {
  uint8_t slave_dataw         : 8;
} lis2de12_datawrite_slv0_t;

typedef struct {
  uint8_t sm_ths              : 8;
} lis2de12_sm_ths_t;

typedef struct {
  uint8_t step_count_d        : 8;
} lis2de12_step_count_delta_t;

typedef struct {
  uint8_t sim                 : 1;
  uint8_t i2c_disable         : 1;
  uint8_t if_add_inc          : 1;
  uint8_t fds_slope           : 1;
  uint8_t func_cfg_en         : 1;
  uint8_t not_used_01         : 1;
  uint8_t soft_reset          : 1;
  uint8_t boot                : 1;
} lis2de12_ctrl2_adv_t;

typedef struct {
  uint8_t bit0                : 1;
  uint8_t bit1                : 1;
  uint8_t bit2                : 1;
  uint8_t bit3                : 1;
  uint8_t bit4                : 1;
  uint8_t bit5                : 1;
  uint8_t bit6                : 1;
  uint8_t bit7                : 1;
} bitwise_t;

typedef union {
  lis2de12_ctrl1_t                     ctrl1;
  lis2de12_ctrl2_t                     ctrl2;
  lis2de12_ctrl3_t                     ctrl3;
  lis2de12_ctrl4_t                     ctrl4;
  lis2de12_ctrl5_t                     ctrl5;
  lis2de12_fifo_ctrl_t                 fifo_ctrl;
  lis2de12_status_t                    status;
  lis2de12_fifo_src_t                  fifo_src;
  lis2de12_tap_6d_ths_t                tap_6d_ths;
  lis2de12_int_dur_t                   int_dur;
  lis2de12_wake_up_ths_t               wake_up_ths;
  lis2de12_wake_up_dur_t               wake_up_dur;
  lis2de12_free_fall_t                 free_fall;
  lis2de12_status_dup_t                status_dup;
  lis2de12_wake_up_src_t               wake_up_src;
  lis2de12_tap_src_t                   tap_src;
  lis2de12_6d_src_t                    _6d_src;
  lis2de12_step_counter_minths_t       step_counter_minths;
  lis2de12_func_ck_gate_t              func_ck_gate;
  lis2de12_func_src_t                  func_src;
  lis2de12_func_ctrl_t                 func_ctrl;
  lis2de12_pedo_deb_reg_t              pedo_deb_reg;
  lis2de12_slv0_add_t                  slv0_add;
  lis2de12_slv0_subadd_t               slv0_subadd;
  lis2de12_slv0_config_t               slv0_config;
  lis2de12_datawrite_slv0_t            datawrite_slv0;
  lis2de12_sm_ths_t                    sm_ths;
  lis2de12_step_count_delta_t          step_count_delta;
  lis2de12_ctrl2_adv_t                 ctrl2_adv;
  bitwise_t                            bitwise;
  uint8_t                              byte;
} lis2de12_reg_t;

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

/**
 * @brief
 *   Write to a LIS2DE12 motion sensor register
 * @param
 *   reg 8-bit register address 
 * @param
 *   value 8-bit value to be written 
 * @return
 *   Status
 */
static status_t write_register(uint32_t reg, uint8_t value)
{
    status_t status = I2C3_send(
        LIS2DE12_I2C_ID >> 1u, 
        reg,
        LIS2DE12_REG_SIZE,
        &value,
        sizeof(value));
  
    return status;
}

/**
 * @brief
 *   Read from a LIS2ES12 motion sensor register
 * @param
 *   reg 8-bit register address 
 * @param
 *   p_value Address where 8-bit value is to be returned 
 * @return
 *   Status
 */
static status_t read_register(uint32_t reg, uint8_t *p_value)
{
    status_t status = I2C3_receive(
        LIS2DE12_I2C_ID >> 1u, 
        reg, 
        LIS2DE12_REG_SIZE,
        p_value,
        sizeof(uint8_t));
  
    return status;
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Initialise the LIS2DE12 motion sensor
 * @return
 *   Status
 */
status_t LIS2DE12_initialise(void)
{
    I2C_initialise();
  
    /** @todo 
     *   Initialise ST7701S display using the following for reference:
     *   - data sheet
     *   - fsl_rm68200.c from SDK
     *   - drv_LIS2DS12.c from PE module
     */
    
    lis2de12_reg_t who_am_i;
    
    status_t status = read_register(LIS2DE12_WHO_AM_I, &who_am_i.byte);
    
    if (kStatus_Success == status)
    {
        if (LIS2DS12_ID != who_am_i.byte)
        {
            status = kStatus_Fail;
        }
    }

    return status;
}


/*** end of file ***/
