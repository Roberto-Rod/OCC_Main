/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_LIS2DS12.c

  @Summary
    Driver for the LIS2DS12 accelerometer chip (motion sensor) file.

  @Description
     LIS2DE12 driver file.
 */
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
//TODO: The work has been abandoned for now
//The code is not used. The file is only left for future 

#include "drv_LIS2DS12.h"
#include "debug.h"
#include "i2c_bit_bang.h"
#define PROPERTY_DISABLE                (0U)
#define PROPERTY_ENABLE                 (1U)

    
typedef struct {
  uint8_t bit0       : 1;
  uint8_t bit1       : 1;
  uint8_t bit2       : 1;
  uint8_t bit3       : 1;
  uint8_t bit4       : 1;
  uint8_t bit5       : 1;
  uint8_t bit6       : 1;
  uint8_t bit7       : 1;
} bitwise_t;

/** I2C Device Address 8 bit format (SA0=1) **/
#define LIS2DS12_I2C_ADDRESS            0b00111010 
/** Device Identification (Who am I) **/
#define LIS2DS12_ID                    0x43U
/**Device Registers **/
#define LIS2DS12_MODULE_8BIT           0x0CU
#define LIS2DS12_WHO_AM_I              0x0FU
#define LIS2DS12_CTRL1                 0x20U
typedef struct {
  uint8_t bdu                 : 1;
  uint8_t hf_odr              : 1;
  uint8_t fs                  : 2;
  uint8_t odr                 : 4;
} lis2ds12_ctrl1_t;

#define LIS2DS12_CTRL2                 0x21U
typedef struct {
  uint8_t sim                 : 1;
  uint8_t i2c_disable         : 1;
  uint8_t if_add_inc          : 1;
  uint8_t fds_slope           : 1;
  uint8_t func_cfg_en         : 1;
  uint8_t not_used_01         : 1;
  uint8_t soft_reset          : 1;
  uint8_t boot                : 1;
} lis2ds12_ctrl2_t;

#define LIS2DS12_CTRL3                 0x22U
typedef struct {
  uint8_t pp_od               : 1;
  uint8_t h_lactive           : 1;
  uint8_t lir                 : 1;
  uint8_t tap_z_en            : 1;
  uint8_t tap_y_en            : 1;
  uint8_t tap_x_en            : 1;
  uint8_t st                  : 2;
} lis2ds12_ctrl3_t;

#define LIS2DS12_CTRL4                 0x23U
typedef struct {
  uint8_t int1_drdy           : 1;
  uint8_t int1_fth            : 1;
  uint8_t int1_6d             : 1;
  uint8_t int1_tap            : 1;
  uint8_t int1_ff             : 1;
  uint8_t int1_wu             : 1;
  uint8_t int1_s_tap          : 1;
  uint8_t int1_master_drdy    : 1;
} lis2ds12_ctrl4_t;

#define LIS2DS12_CTRL5                 0x24U
typedef struct {
  uint8_t int2_drdy           : 1;
  uint8_t int2_fth            : 1;
  uint8_t int2_step_det       : 1;
  uint8_t int2_sig_mot        : 1;
  uint8_t int2_tilt           : 1;
  uint8_t int2_on_int1        : 1;
  uint8_t int2_boot           : 1;
  uint8_t drdy_pulsed         : 1;
} lis2ds12_ctrl5_t;

#define LIS2DS12_FIFO_CTRL             0x25U
typedef struct {
  uint8_t if_cs_pu_dis        : 1;
  uint8_t not_used_01         : 2;
  uint8_t module_to_fifo      : 1;
  uint8_t int2_step_count_ov  : 1;
  uint8_t fmode               : 3;
} lis2ds12_fifo_ctrl_t;

#define LIS2DS12_OUT_T                 0x26U
#define LIS2DS12_STATUS                0x27U
typedef struct {
  uint8_t drdy                : 1;
  uint8_t ff_ia               : 1;
  uint8_t _6d_ia              : 1;
  uint8_t single_tap          : 1;
  uint8_t double_tap          : 1;
  uint8_t sleep_state         : 1;
  uint8_t wu_ia               : 1;
  uint8_t fifo_ths            : 1;
} lis2ds12_status_t;

#define LIS2DS12_OUT_X_L               0x28U
#define LIS2DS12_OUT_X_H               0x29U
#define LIS2DS12_OUT_Y_L               0x2AU
#define LIS2DS12_OUT_Y_H               0x2BU
#define LIS2DS12_OUT_Z_L               0x2CU
#define LIS2DS12_OUT_Z_H               0x2DU
#define LIS2DS12_FIFO_THS              0x2EU
typedef struct {
  uint8_t fth                 : 8;
} lis2ds12_fifo_ths_t;

#define LIS2DS12_FIFO_SRC              0x2FU
typedef struct {
  uint8_t not_used_01         : 5;
  uint8_t diff                : 1;
  uint8_t fifo_ovr            : 1;
  uint8_t fth                 : 1;
} lis2ds12_fifo_src_t;

#define LIS2DS12_FIFO_SAMPLES          0x30U
#define LIS2DS12_TAP_6D_THS            0x31U
typedef struct {
  uint8_t tap_ths             : 5;
  uint8_t _6d_ths             : 2;
  uint8_t _4d_en              : 1;
} lis2ds12_tap_6d_ths_t;

#define LIS2DS12_INT_DUR               0x32U
typedef struct {
  uint8_t shock               : 2;
  uint8_t quiet               : 2;
  uint8_t lat                 : 4;
} lis2ds12_int_dur_t;

#define LIS2DS12_WAKE_UP_THS           0x33U
typedef struct {
  uint8_t wu_ths              : 6;
  uint8_t sleep_on            : 1;
  uint8_t single_double_tap   : 1;
} lis2ds12_wake_up_ths_t;

#define LIS2DS12_WAKE_UP_DUR           0x34U
typedef struct {
  uint8_t sleep_dur           : 4;
  uint8_t int1_fss7           : 1;
  uint8_t wu_dur              : 2;
  uint8_t ff_dur              : 1;
} lis2ds12_wake_up_dur_t;

#define LIS2DS12_FREE_FALL             0x35U
typedef struct {
  uint8_t ff_ths              : 3;
  uint8_t ff_dur              : 5;
} lis2ds12_free_fall_t;

#define LIS2DS12_STATUS_DUP            0x36U
typedef struct {
  uint8_t drdy                : 1;
  uint8_t ff_ia               : 1;
  uint8_t _6d_ia              : 1;
  uint8_t single_tap          : 1;
  uint8_t double_tap          : 1;
  uint8_t sleep_state         : 1;
  uint8_t wu_ia               : 1;
  uint8_t ovr                 : 1;
} lis2ds12_status_dup_t;

#define LIS2DS12_WAKE_UP_SRC           0x37U
typedef struct {
  uint8_t z_wu                : 1;
  uint8_t y_wu                : 1;
  uint8_t x_wu                : 1;
  uint8_t wu_ia               : 1;
  uint8_t sleep_state_ia      : 1;
  uint8_t ff_ia               : 1;
  uint8_t not_used_01         : 2;
} lis2ds12_wake_up_src_t;

#define LIS2DS12_TAP_SRC               0x38U
typedef struct {
  uint8_t z_tap               : 1;
  uint8_t y_tap               : 1;
  uint8_t x_tap               : 1;
  uint8_t tap_sign            : 1;
  uint8_t double_tap          : 1;
  uint8_t single_tap          : 1;
  uint8_t tap_ia              : 1;
  uint8_t not_used_01         : 1;
} lis2ds12_tap_src_t;

#define LIS2DS12_6D_SRC                0x39U
typedef struct {
  uint8_t xl                  : 1;
  uint8_t xh                  : 1;
  uint8_t yl                  : 1;
  uint8_t yh                  : 1;
  uint8_t zl                  : 1;
  uint8_t zh                  : 1;
  uint8_t _6d_ia              : 1;
  uint8_t not_used_01         : 1;
} lis2ds12_6d_src_t;

#define LIS2DS12_STEP_COUNTER_MINTHS   0x3AU
typedef struct {
  uint8_t sc_mths             : 6;
  uint8_t pedo4g              : 1;
  uint8_t rst_nstep           : 1;
} lis2ds12_step_counter_minths_t;

#define LIS2DS12_STEP_COUNTER_L        0x3BU
#define LIS2DS12_STEP_COUNTER_H        0x3CU
#define LIS2DS12_FUNC_CK_GATE          0x3DU
typedef struct {
  uint8_t ck_gate_func        : 1;
  uint8_t step_detect         : 1;
  uint8_t rst_pedo            : 1;
  uint8_t rst_sign_mot        : 1;
  uint8_t sig_mot_detect      : 1;
  uint8_t fs_src              : 2;
  uint8_t tilt_int            : 1;
} lis2ds12_func_ck_gate_t;

#define LIS2DS12_FUNC_SRC              0x3EU
typedef struct {
  uint8_t sensorhub_end_op    : 1;
  uint8_t module_ready        : 1;
  uint8_t rst_tilt            : 1;
  uint8_t not_used_01         : 5;
} lis2ds12_func_src_t;

#define LIS2DS12_FUNC_CTRL             0x3FU
typedef struct {
  uint8_t step_cnt_on         : 1;
  uint8_t sign_mot_on         : 1;
  uint8_t master_on           : 1;
  uint8_t tud_en              : 1;
  uint8_t tilt_on             : 1;
  uint8_t module_on           : 1;
  uint8_t not_used_01         : 2;
} lis2ds12_func_ctrl_t;

#define LIS2DS12_PEDO_DEB_REG          0x2BU
typedef struct {
  uint8_t deb_step            : 3;
  uint8_t deb_time            : 5;
} lis2ds12_pedo_deb_reg_t;

#define LIS2DS12_SLV0_ADD              0x30U
typedef struct {
  uint8_t rw_0                : 1;
  uint8_t slave0_add          : 7;
} lis2ds12_slv0_add_t;

#define LIS2DS12_SLV0_SUBADD           0x31U
typedef struct {
  uint8_t slave0_reg          : 8;
} lis2ds12_slv0_subadd_t;

#define LIS2DS12_SLV0_CONFIG           0x32U
typedef struct {
  uint8_t slave0_numop        : 3;
  uint8_t not_used_01         : 5;
} lis2ds12_slv0_config_t;

#define LIS2DS12_DATAWRITE_SLV0        0x33U
typedef struct {
  uint8_t slave_dataw         : 8;
} lis2ds12_datawrite_slv0_t;

#define LIS2DS12_SM_THS                0x34U
typedef struct {
  uint8_t sm_ths              : 8;
} lis2ds12_sm_ths_t;

#define LIS2DS12_STEP_COUNT_DELTA      0x3AU
typedef struct {
  uint8_t step_count_d        : 8;
} lis2ds12_step_count_delta_t;

#define LIS2DS12_CTRL2_ADV             0x3FU
typedef struct {
  uint8_t sim                 : 1;
  uint8_t i2c_disable         : 1;
  uint8_t if_add_inc          : 1;
  uint8_t fds_slope           : 1;
  uint8_t func_cfg_en         : 1;
  uint8_t not_used_01         : 1;
  uint8_t soft_reset          : 1;
  uint8_t boot                : 1;
} lis2ds12_ctrl2_adv_t;
/**
  * @defgroup LIS2DS12_Register_Union
  * @brief    This union group all the registers that has a bit-field
  *           description.
  *           This union is useful but not need by the driver.
  *
  *           REMOVING this union you are compliant with:
  *           MISRA-C 2012 [Rule 19.2] -> " Union are not allowed "
  *
  * @{
  *
  */
typedef union {
  lis2ds12_ctrl1_t                     ctrl1;
  lis2ds12_ctrl2_t                     ctrl2;
  lis2ds12_ctrl3_t                     ctrl3;
  lis2ds12_ctrl4_t                     ctrl4;
  lis2ds12_ctrl5_t                     ctrl5;
  lis2ds12_fifo_ctrl_t                 fifo_ctrl;
  lis2ds12_status_t                    status;
  lis2ds12_fifo_src_t                  fifo_src;
  lis2ds12_tap_6d_ths_t                tap_6d_ths;
  lis2ds12_int_dur_t                   int_dur;
  lis2ds12_wake_up_ths_t               wake_up_ths;
  lis2ds12_wake_up_dur_t               wake_up_dur;
  lis2ds12_free_fall_t                 free_fall;
  lis2ds12_status_dup_t                status_dup;
  lis2ds12_wake_up_src_t               wake_up_src;
  lis2ds12_tap_src_t                   tap_src;
  lis2ds12_6d_src_t                    _6d_src;
  lis2ds12_step_counter_minths_t       step_counter_minths;
  lis2ds12_func_ck_gate_t              func_ck_gate;
  lis2ds12_func_src_t                  func_src;
  lis2ds12_func_ctrl_t                 func_ctrl;
  lis2ds12_pedo_deb_reg_t              pedo_deb_reg;
  lis2ds12_slv0_add_t                  slv0_add;
  lis2ds12_slv0_subadd_t               slv0_subadd;
  lis2ds12_slv0_config_t               slv0_config;
  lis2ds12_datawrite_slv0_t            datawrite_slv0;
  lis2ds12_sm_ths_t                    sm_ths;
  lis2ds12_step_count_delta_t          step_count_delta;
  lis2ds12_ctrl2_adv_t                 ctrl2_adv;
  bitwise_t                            bitwise;
  uint8_t                              byte;
} lis2ds12_reg_t;

typedef enum {
  LIS2DS12_2g = 0,
  LIS2DS12_16g = 1,
  LIS2DS12_4g = 2,
  LIS2DS12_8g = 3,
} lis2ds12_fs_t;

typedef enum {
  LIS2DS12_XL_ODR_OFF         = 0x00,
  LIS2DS12_XL_ODR_1Hz_LP      = 0x08,
  LIS2DS12_XL_ODR_12Hz5_LP    = 0x09,
  LIS2DS12_XL_ODR_25Hz_LP     = 0x0A,
  LIS2DS12_XL_ODR_50Hz_LP     = 0x0B,
  LIS2DS12_XL_ODR_100Hz_LP    = 0x0C,
  LIS2DS12_XL_ODR_200Hz_LP    = 0x0D,
  LIS2DS12_XL_ODR_400Hz_LP    = 0x0E,
  LIS2DS12_XL_ODR_800Hz_LP    = 0x0F,
  LIS2DS12_XL_ODR_12Hz5_HR    = 0x01,
  LIS2DS12_XL_ODR_25Hz_HR     = 0x02,
  LIS2DS12_XL_ODR_50Hz_HR     = 0x03,
  LIS2DS12_XL_ODR_100Hz_HR    = 0x04,
  LIS2DS12_XL_ODR_200Hz_HR    = 0x05,
  LIS2DS12_XL_ODR_400Hz_HR    = 0x06,
  LIS2DS12_XL_ODR_800Hz_HR    = 0x07,
  LIS2DS12_XL_ODR_1k6Hz_HF    = 0x15,
  LIS2DS12_XL_ODR_3k2Hz_HF    = 0x16,
  LIS2DS12_XL_ODR_6k4Hz_HF    = 0x17,
} lis2ds12_odr_t;

   
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
static void lis2ds12_reset_set(void);
static void lis2ds12_reset_get(uint8_t *val);
static void lis2ds12_block_data_update_set(uint8_t val);
static void lis2ds12_xl_full_scale_set(lis2ds12_fs_t val);
static void lis2ds12_xl_data_rate_set(lis2ds12_odr_t val);
static void lis2ds12_status_reg_get(lis2ds12_status_t *val);
static void lis2ds12_acceleration_raw_get(int16_t *val);
static float lis2ds12_from_fs2g_to_mg(int16_t lsb);
static void lis2ds12_device_id_get( uint8_t *buff);
static void lis2ds12_access_advanced_conf_registers(uint8_t val);

static void lis2ds12_reset_set(void)
{
  lis2ds12_ctrl2_t ctrl2;
  i2c_read_register_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_CTRL2, (uint8_t *)&ctrl2, 1);
  if (ctrl2.soft_reset != 1)
  {
    ctrl2.soft_reset = 1;
    i2c_write_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_CTRL2, (uint8_t *)&ctrl2, 1);
 //   dprintf_colour("[YELLOW]ctr12 reset set: 0x%02x[WHITE]\r\n", ctrl2);
  }
}
static void lis2ds12_reset_get(uint8_t *val)
{
  lis2ds12_ctrl2_t ctrl2;
  i2c_read_register_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_CTRL2, (uint8_t *)&ctrl2, 1);
  *val = ctrl2.soft_reset;
}
static void lis2ds12_block_data_update_set(uint8_t val)
{
  lis2ds12_ctrl1_t ctrl1;
  i2c_read_register_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_CTRL1, (uint8_t *)&ctrl1, 1);

  if (ctrl1.bdu != val)
  {
    ctrl1.bdu = val;
    i2c_write_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_CTRL1, (uint8_t *)&ctrl1, 1);
 //   dprintf_colour("[YELLOW]ctr11 update set: 0x%02x[WHITE]\r\n", ctrl1);
  }
}

static void lis2ds12_xl_full_scale_set(lis2ds12_fs_t val)
{
  lis2ds12_ctrl1_t ctrl1;
  i2c_read_register_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_CTRL1, (uint8_t *)&ctrl1, 1);

  if (ctrl1.fs != (uint8_t)val)
  {
    ctrl1.fs = (uint8_t)val;
    i2c_write_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_CTRL1, (uint8_t *)&ctrl1, 1);
  //  dprintf_colour("[YELLOW]ctr11 scale set: 0x%02x[WHITE]\r\n", ctrl1);
  }
}

static void lis2ds12_xl_data_rate_set(lis2ds12_odr_t val)
{
   lis2ds12_ctrl1_t ctrl1;
   i2c_read_register_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_CTRL1, (uint8_t *)&ctrl1, 1);

//TODO: Have to think about inverse logic   
//  if ((ctrl1.odr != ((uint8_t)val & 0x0FU) )&& (ctrl1.hf_odr != ((uint8_t)val & 0x10U) << 4))
//  {
    ctrl1.odr = ((uint8_t)val & 0x0FU);
    ctrl1.hf_odr = ((uint8_t)val & 0x10U) >> 4 ; 
    i2c_write_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_CTRL1, (uint8_t *)&ctrl1, 1);
//    dprintf_colour("[YELLOW]ctr11 rate set: 0x%02x[WHITE]\r\n", ctrl1);
//  }
}
//test purpose //check if it work // dont use the pin it does not work

static void lis2ds12_access_advanced_conf_registers(uint8_t val)
{
  lis2ds12_ctrl2_t ctrl2;
  i2c_read_register_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_CTRL2, (uint8_t *)&ctrl2, 1);

  if (ctrl2.func_cfg_en != val)
  {
    ctrl2.func_cfg_en = val;
    i2c_write_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_CTRL2, (uint8_t *)&ctrl2, 1);
  }
}
static void lis2ds12_SA0_pull_up_set(uint8_t val)
{
  lis2ds12_func_ctrl_t func_ctrl;
  i2c_read_register_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_CTRL1, (uint8_t *)&func_ctrl, 1);

  if (func_ctrl.tud_en != val)
  {
    func_ctrl.tud_en = val;
    i2c_write_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_CTRL1, (uint8_t *)&func_ctrl, 1);
 //   dprintf_colour("[YELLOW]ctr11 update set: 0x%02x[WHITE]\r\n", ctrl1);
  }
}
//end test function - setting pull up 

static void lis2ds12_status_reg_get(lis2ds12_status_t *val)
{
  i2c_read_register_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_STATUS, (uint8_t *) val, 1);
}

static void lis2ds12_acceleration_raw_get(int16_t *val)
{
  uint8_t buff[6];
  i2c_read_register_bytes(LIS2DS12_I2C_ADDRESS, LIS2DS12_OUT_X_L, buff, 6);
  val[0] = (int16_t)buff[1];
  val[0] = (val[0] * 256) +  (int16_t)buff[0];
  val[1] = (int16_t)buff[3];
  val[1] = (val[1] * 256) +  (int16_t)buff[2];
  val[2] = (int16_t)buff[5];
  val[2] = (val[2] * 256) +  (int16_t)buff[4];
}

static float lis2ds12_from_fs2g_to_mg(int16_t lsb)
{
  return ((float)lsb * 0.061f);
}

static void lis2ds12_device_id_get( uint8_t *buff)
{
  i2c_read_register_bytes(LIS2DS12_I2C_ADDRESS,  LIS2DS12_WHO_AM_I, buff, 1);
}

/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

void lis2ds12_read_data_simple_set_up(void)
{

  static uint8_t rst;
  /* Restore default configuration */
  lis2ds12_reset_set();
  //stay till reset valid
  do 
  {
    lis2ds12_reset_get(&rst);
  } while (rst);

  /* Enable Block Data Update. */
  lis2ds12_block_data_update_set(PROPERTY_ENABLE);
    /* Set full scale. */
  lis2ds12_xl_full_scale_set(LIS2DS12_2g);
  /* Set Output Data Rate. */
  lis2ds12_xl_data_rate_set( LIS2DS12_XL_ODR_100Hz_LP);
  //test pupose// only check it // dont use the pin -  it does not work
  lis2ds12_access_advanced_conf_registers(PROPERTY_ENABLE);
  lis2ds12_SA0_pull_up_set(PROPERTY_ENABLE);
}
  
/* Read samples in polling mode (no int). */
void lis2ds12_read_data_simple(void)
{
    /* Read output only if new value is available. */
    lis2ds12_reg_t reg;
    lis2ds12_reg_t whoamI;
    static int16_t data_raw_acceleration[3];
    static float acceleration_mg[3];
    lis2ds12_status_reg_get(&reg.status);
    
  //  dprintf_colour("[YELLOW]reg.status: 0x%02x[WHITE]\r\n", reg.status);
    
    if (reg.status.drdy) {
      /* Read acceleration data. */
      lis2ds12_acceleration_raw_get(data_raw_acceleration);
      acceleration_mg[0] = lis2ds12_from_fs2g_to_mg(
                             data_raw_acceleration[0]);
      acceleration_mg[1] = lis2ds12_from_fs2g_to_mg(
                             data_raw_acceleration[1]);
      acceleration_mg[2] = lis2ds12_from_fs2g_to_mg(
                             data_raw_acceleration[2]);
      dprintf_colour("[YELLOW]Acceleration [mg]:%4.2f\t%4.2f\t%4.2f\r\n",
              acceleration_mg[0], acceleration_mg[1], acceleration_mg[2]);
      //test purpose // compare with who am i register -> is it read properly
      lis2ds12_device_id_get((uint8_t *)&whoamI);
      dprintf_colour("[YELLOW]Who am I: 0x%02x[WHITE]\r\n", whoamI);
    }
}
