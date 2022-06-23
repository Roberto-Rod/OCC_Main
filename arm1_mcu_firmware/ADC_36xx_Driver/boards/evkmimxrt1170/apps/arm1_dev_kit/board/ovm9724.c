/*****************************************************************************/
/**
 * @file 
 *   ovm9724.c
 * @brief 
 *   Driver for Omnivision OVM9724 camera cube
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

#include "ovm9724.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/**
 * @todo
 *   Check addresses and work out how to decide which camera to talk to
 */
#define SCCB_ID1                        (0x20u)
#define SCCB_ID2                        (0x6Cu)

/* General configuration registers */
#define STREAMING_MODE                  (0x0100u)
#define IMAGE_ORIENTATION               (0x0101u)
#define SOFTWARE_RESET                  (0x0103u)
#define GROUP_WRITE                     (0x0104u)
#define FRAME_DROP                      (0x0105u)
#define DATA_DEPTH_H                    (0x0112u)
#define DATA_DEPTH_L                    (0x0113u)
#define CLKRST6                         (0x301Cu)
#define GRP_ACCESS                      (0x3208u)

/* Integration time register addresses */
#define INTEGRATION_TIME_LINE_H         (0x0202u)
#define INTEGRATION_TIME_LINE_L         (0x0203u)

/* Analog gain register address */
#define ANALOG_GAIN                     (0x0205u)

/* Clock configuration register addresses */
#define PIXEL_CLK_DIVIDER_H             (0x0300u)
#define PIXEL_CLK_DIVIDER_L             (0x0301u)
#define SYSTEM_CLK_DIVIDER_H            (0x0302u)
#define SYSTEM_CLK_DIVIDER_L            (0x0303u)
#define PRE_PLL_CLK_DIVIDER_H           (0x0304u)
#define PRE_PLL_CLK_DIVIDER_L           (0x0305u)
#define PLL_MULTIPLIER_H                (0x0306u)
#define PLL_MULTIPLIER_L                (0x0307u)

/* Frame timing register addresses */
#define VERTICAL_TOTAL_LENGTH_H         (0x0340u)
#define VERTICAL_TOTAL_LENGTH_L         (0x0341u)
#define HORIZONTAL_TOTAL_LENGTH_H       (0x0342u)
#define HORIZONTAL_TOTAL_LENGTH_L       (0x0343u)

/* Image size register addresses */
#define HORIZONTAL_START_H              (0x0344u)
#define HORIZONTAL_START_L              (0x0345u)
#define VERTICAL_START_H                (0x0346u)
#define VERTICAL_START_L                (0x0347u)
#define HORIZONTAL_END_H                (0x0348u)
#define HORIZONTAL_END_L                (0x0349u)
#define VERTICAL_END_H                  (0x034Au)
#define VERTICAL_END_L                  (0x034Bu)
#define IMAGE_WIDTH_H                   (0x034Cu)
#define IMAGE_WIDTH_L                   (0x034Du)
#define IMAGE_HEIGHT_H                  (0x034Eu)
#define IMAGE_HEIGHT_L                  (0x034Fu)

/* Subsampling register addresses */
#define X_EVEN_INC_H                    (0x0380u)
#define X_EVEN_INC_L                    (0x0381u)
#define X_ODD_INC_H                     (0x0382u)
#define X_ODD_INC_L                     (0x0383u)
#define Y_EVEN_INC_H                    (0x0384u)
#define Y_EVEN_INC_L                    (0x0385u)
#define Y_ODD_INC_H                     (0x0386u)
#define Y_ODD_INC_L                     (0x0387u)

/* Test pattern register addresses */
#define TEST_PATTERN                    (0x0601u)
#define SOLID_COLOR_RED_H               (0x0602u)
#define SOLID_COLOR_RED_L               (0x0603u)
#define SOLID_COLOR_GR_H                (0x0604u)
#define SOLID_COLOR_GR_L                (0x0605u)
#define SOLID_COLOR_BLUE_H              (0x0606u)
#define SOLID_COLOR_BLUE_L              (0x0607u)
#define SOLID_COLOR_GB_H                (0x0608u)
#define SOLID_COLOR_GB_L                (0x0609u)

/* Integration time and gain limit register addresses */
#define INTEGRATION_TIME_LINE_MIN_H     (0x1004u)
#define INTEGRATION_TIME_LINE_MIN_L     (0x1005u)
#define INTEGRATION_TIME_LINE_MAX_H     (0x1006u)
#define INTEGRATION_TIME_LINE_MAX_L     (0x1007u)
#define INTEGRATION_TIME_SUBLINE_MIN_H  (0x1008u)
#define INTEGRATION_TIME_SUBLINE_MIN_L  (0x1009u)
#define INTEGRATION_TIME_SUBLINE_MAX_H  (0x100Au)
#define INTEGRATION_TIME_SUBLINE_MAX_L  (0x100Bu)

/* Frame timing parameter limit register addresses */
#define MIN_VERTICAL_TOTAL_LENGTH_H     (0x1140u)
#define MIN_VERTICAL_TOTAL_LENGTH_L     (0x1141u)
#define MAX_VERTICAL_TOTAL_LENGTH_H     (0x1142u)
#define MAX_VERTICAL_TOTAL_LENGTH_L     (0x1143u)
#define MIN_HORIZONTAL_TOTAL_LENGTH_H   (0x1144u)
#define MIN_HORIZONTAL_TOTAL_LENGTH_L   (0x1145u)
#define MAX_HORIZONTAL_TOTAL_LENGTH_H   (0x1146u)
#define MAX_HORIZONTAL_TOTAL_LENGTH_L   (0x1147u)
#define MIN_HORIZONTAL_BLANKING_H       (0x1148u)
#define MIN_HORIZONTAL_BLANKING_L       (0x1149u)

/* Image size limit register addresses */
#define HORIZONTAL_START_MIN_H          (0x1180u)
#define HORIZONTAL_START_MIN_L          (0x1181u)
#define VERTICAL_START_MIN_H            (0x1182u)
#define VERTICAL_START_MIN_L            (0x1183u)
#define HORIZONTAL_END_MIN_H            (0x1184u)
#define HORIZONTAL_END_MIN_L            (0x1185u)
#define VERTICAL_END_MIN_H              (0x1186u)
#define VERTICAL_END_MIN_L              (0x1187u)

/* IO control register addresses */
#define OUTPUT_DRIVE_CAPABILITY_CTRL    (0x3001u)
#define IO_CTRL00                       (0x3002u)
#define OUTPUT_VALUE0                   (0x3006u)
#define CHIP_ID_H                       (0x300Au)
#define CHIP_ID_L                       (0x300Bu)
#define OUTPUT_SELECT00                 (0x3024u)
#define OUTPUT_SELECT1                  (0x3025u)
#define CHIP_REVISION                   (0x302Au)
#define SCCD_ID2                        (0x302Bu)

/* Timing register addresses */
#define FORMAT1                         (0x3820u)
#define FORMAT2                         (0x3821u)
#define FSIN_CTRL                       (0x3823u)

/* LED PWM control register addresses */
#define LED_PWM_DUTY_CYCLE_H            (0x3912u)
#define LED_PWM_DUTY_CYCLE_L            (0x3912u)

/* OTP bank control register addresses */
#define LED_FREQ_DIV_CYCLE_H            (0x3D1Cu)
#define LED_FREQ_DIV_CYCLE_L            (0x3D1Du)
#define LED_DUTY_CYCLE_LOW_H            (0x3D1Eu)
#define LED_DUTY_CYCLE_LOW_L            (0x3D1Fu)
#define OTP_PGM_CTR                     (0x3D80u)
#define OTP_LOAD_CTR                    (0x3D81u)

/* BLC control register addresses */
#define BLC_START_LINE                  (0x4003u)
#define BLC_LINE_NUM                    (0x4004u)
#define R8                              (0x4008u)
#define BLC_MAN_B_H                     (0x4019u)
#define BLC_MAN_B_L                     (0x401Au)
#define BLC_MAN_GB_H                    (0x401Bu)
#define BLC_MAN_GB_L                    (0x401Cu)
#define BLC_MAN_GR_H                    (0x401Du)
#define BLC_MAN_GR_L                    (0x401Eu)
#define BLC_MAN_R_H                     (0x401Fu)
#define BLC_MAN_R_L                     (0x4020u)

/* Clipping data register addresses */
#define CLIP_MAX_H                      (0x4300u)
#define CLIP_MAX_L                      (0x4301u)
#define CLIP_MIN_H                      (0x4302u)
#define CLIP_MIN_L                      (0x4303u)

/* Strobe control register addresses */
#define STROBE_CTRL0                    (0x4400u)
#define STROBE_ADD_DUMMY_H              (0x4402u)
#define STROBE_ADD_DUMMY_L              (0x4403u)
#define STROBE_CTRL1                    (0x4404u)
#define STROBE_WIDTH                    (0x4405u)

/* MIPI control register addresses */
#define MIPI_CTRL00                     (0x4800u)
#define MIPI_CTRL01                     (0x4801u)
#define MIPI_CTRL02                     (0x4802u)
#define MIPI_CTRL03                     (0x4803u)
#define MIPI_CTRL04                     (0x4804u)
#define MIPI_CTRL05                     (0x4805u)
#define FCNT_MAX_H                      (0x4810u)
#define FCNT_MAX_L                      (0x4811u)
#define SPKT_WC_H                       (0x4812u)
#define SPKT_WC_L                       (0x4813u)
#define MIPI_CTRL14                     (0x4814u)
#define DT_SPKT                         (0x4815u)
#define HS_ZERO_MIN_H                   (0x4818u)
#define HS_ZERO_MIN_L                   (0x4819u)
#define HS_TRAIL_MIN_H                  (0x481Au)
#define HS_TRAIL_MIN_L                  (0x481Bu)
#define CLK_ZERO_MIN_H                  (0x481Cu)
#define CLK_ZERO_MIN_L                  (0x481Du)
#define CLK_PREPARE_MIN_H               (0x481Eu)
#define CLK_PREPARE_MIN_L               (0x481Fu)
#define CLK_POST_MIN_H                  (0x4820u)
#define CLK_POST_MIN_L                  (0x4821u)
#define CLK_TRAIL_MIN_H                 (0x4822u)
#define CLK_TRAIL_MIN_L                 (0x4823u)
#define LPX_P_MIN_H                     (0x4824u)
#define LPX_P_MIN_L                     (0x4825u)
#define HS_PREPARE_MIN_H                (0x4826u)
#define HS_PREPARE_MIN_L                (0x4827u)
#define HS_EXIT_MIN_H                   (0x4828u)
#define HS_EXIT_MIN_L                   (0x4829u)
#define UI_HS_ZERO_MIN                  (0x482Au)
#define UI_HS_TRAIL_MIN                 (0x482Bu)
#define UI_CLK_ZERO_MIN                 (0x482Cu)
#define UI_CLK_PREPARE_MIN              (0x482Du)
#define UI_CLK_POST_MIN                 (0x482Eu)
#define UI_CLK_TRAIL_MIN                (0x482Fu)
#define UI_LPX_P_MIN                    (0x4830u)
#define UI_HS_PREPARE_MIN               (0x4831u)
#define UI_HS_EXIT_MIN                  (0x4832u)
#define PCLK_PERIOD                     (0x4837u)
#define MIPI_LP_STATUS                  (0x4865u)

/* ISP register addresses */
#define CTRL_0                          (0x5000u)
#define CTRL_1                          (0x5001u)
#define BLC_TARGET                      (0x5003u)
#define CTRL_3                          (0x5004u)

/* Manual white balance control register addresses */
#define MANUAL_WHITE_BALANCE_R_GAIN_H   (0x5180u)
#define MANUAL_WHITE_BALANCE_R_GAIN_L   (0x5181u)
#define MANUAL_WHITE_BALANCE_G_GAIN_H   (0x5182u)
#define MANUAL_WHITE_BALANCE_G_GAIN_L   (0x5183u)
#define MANUAL_WHITE_BALANCE_B_GAIN_H   (0x5184u)
#define MANUAL_WHITE_BALANCE_B_GAIN_L   (0x5185u)

/* AVG control register addresses */
#define XSTART_H                        (0x5300u)
#define XSTART_L                        (0x5301u)
#define YSTART_H                        (0x5302u)
#define YSTART_L                        (0x5303u)
#define XWIN_H                          (0x5304u)
#define XWIN_L                          (0x5305u)
#define YWIN_H                          (0x5306u)
#define YWIN_L                          (0x5307u)
#define R_AVG_CTRL08                    (0x5308u)
#define AVG_SCCB_DONE                   (0x5309u)
#define AVG_H                           (0x530Au)
#define AVG_L                           (0x530Bu)
#define AVG                             (0x530Cu)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

const camera_device_operations_t ovm9724_ops = {
    .init     = OVM9724_initialise,
    .deinit   = OVM9724_deinitialise,
    .start    = OVM9724_start,
    .stop     = OVM9724_stop,
    .control  = OVM9724_control,
    .init_ext = OVM9724_initialise_ext
};

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

static status_t write_register(
    camera_device_handle_t *ph_handle, 
    uint32_t reg, 
    uint8_t value);

static status_t write_multiple_registers(
    camera_device_handle_t *ph_handle, 
    uint32_t reg, uint8_t *p_value, 
    uint32_t len);

static status_t read_register(
    camera_device_handle_t *ph_handle, 
    uint32_t reg, 
    uint8_t *p_value);

static status_t modify_register(
    camera_device_handle_t *ph_handle, 
    uint32_t reg, 
    uint8_t mask, 
    uint8_t value);

/**
 * @brief
 *   Write to a OVM9724 camera cube register
 * @param[in]
 *   ph_handle Address of camera device handle
 * @param
 *   reg 16-bit register address 
 * @param
 *   value 8-bit value to be written 
 * @return
 *   Status
 */
static status_t write_register(
    camera_device_handle_t *ph_handle, uint32_t reg, uint8_t value)
{
    status_t status = SCCB_WriteReg(
        SCCB_ID1 >> 1u, 
        kSCCB_RegAddr16Bit, 
        reg, 
        value,
        ((ov5640_resource_t*)((ph_handle)->resource))->i2cSendFunc);
  
    return status;
}

/**
 * @brief
 *   Write to multiple, consecutive registers in the OVM9724 camera cube
 * @param[in]
 *   ph_handle Address of camera device handle
 * @param
 *   reg 16-bit start register address 
 * @param
 *   p_value Pointer to multiple 8-bit values to be written
 *
 * @param
 *   len Number of registers to be written
 * @return
 *   Status
 */
static status_t write_multiple_registers(
    camera_device_handle_t *ph_handle, 
    uint32_t reg, uint8_t *p_value, uint32_t len)
{
    status_t status = SCCB_WriteMultiRegs(
        SCCB_ID1 >> 1u, 
        kSCCB_RegAddr16Bit, 
        reg, 
        p_value,
        len,
        ((ov5640_resource_t*)((ph_handle)->resource))->i2cSendFunc);
  
    return status;
}

/**
 * @brief
 *   Read from an OVM9724 camera cube register
 * @param[in]
 *   ph_handle Address of camera device handle
 * @param
 *   reg 16-bit register address 
 * @param
 *   p_value Address where 8-bit value is to be returned 
 * @return
 *   Status
 */
static status_t read_register(
    camera_device_handle_t *ph_handle, uint32_t reg, uint8_t *p_value)
{
    status_t status = SCCB_ReadReg(
        SCCB_ID1 >> 1u, 
        kSCCB_RegAddr16Bit, 
        reg, 
        p_value,
        ((ov5640_resource_t*)((ph_handle)->resource))->i2cReceiveFunc);
  
    return status;
}

/**
 * @brief
 *   Modify the contents of a OVM9724 camera cube register
 * @param[in]
 *   ph_handle Address of camera device handle
 * @param
 *   reg 16-bit register address 
 * @param
 *   mask 8-bit value containing bits to be cleared
 * @param
 *   value 8-bit value containing bits to be set 
 * @return
 *   Status
 */
static status_t modify_register(
    camera_device_handle_t *ph_handle, 
    uint32_t reg, 
    uint8_t mask, 
    uint8_t value)
{
    status_t status = SCCB_ModifyReg(
        SCCB_ID1 >> 1u, 
        kSCCB_RegAddr16Bit, 
        reg, 
        mask,
        value,
        ((ov5640_resource_t*)((ph_handle)->resource))->i2cReceiveFunc,
        ((ov5640_resource_t*)((ph_handle)->resource))->i2cSendFunc);

    return status;
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Initialise the OVM9724 camera cube
 * @param[in]
 *   ph_handle Address of camera device handle
 * @param[in]
 *   p_config Address of configuration structure
 * @return
 *   Status
 */
status_t OVM9724_initialise(
    camera_device_handle_t *ph_handle, const camera_config_t *p_config)
{
    /** @todo 
     *   Initialise OVM9724 camera using data sheet & fsl_ov5640.c for reference
     */  
  
    return kStatus_Success;
}

/**
 * @brief
 *   Deinitialise the OVM9724 camera cube
 * @param[in]
 *   ph_handle Address of camera device handle
 * @return
 *   Status
 */
status_t OVM9724_deinitialise(camera_device_handle_t *ph_handle)
{
    ((ov5640_resource_t *)(ph_handle->resource))->pullPowerDownPin(true);

    return kStatus_Success;
}

/**
 * @brief
 *   Start the OVM9724 camera cube
 * @param[in]
 *   ph_handle Address of camera device handle
 * @return
 *   Status
 */
status_t OVM9724_start(camera_device_handle_t *ph_handle)
{
    /** @todo 
     *    This is just an example of how to write to a register
     */  
    return write_register(ph_handle, SOFTWARE_RESET, 0x01u);
}

/**
 * @brief
 *   Stop the OVM9724 camera cube
 * @param[in]
 *   ph_handle Address of camera device handle
 * @return
 *   Status
 */
status_t OVM9724_stop(camera_device_handle_t *ph_handle)
{
    /** @todo 
     *    This is just an example of how to write to a register
     */  
    return write_register(ph_handle, SOFTWARE_RESET, 0x00u);
}

/**
 * @brief
 *   Send a control command to the OVM9724 camera cube
 * @param[in]
 *   ph_handle Address of camera device handle
 * @param
 *   cmd Command to be sent
 * @param
 *   arg Argument to be sent alongside the specified function
 * @return
 *   Status
 */
status_t OVM9724_control(
    camera_device_handle_t *ph_handle, camera_device_cmd_t cmd, int32_t arg)
{
    /** @todo 
     *    Control map array to be implemented
     */  
    return kStatus_InvalidArgument;
}

/**
 * @brief
 *   Initialise the OVM9724 camera cube, with additional external configuration
 * @param[in]
 *   ph_handle Address of camera device handle
 * @param[in]
 *   p_config Address of configuration structure
 * @param[in]
 *   p_config Address of special configuration structure
 * @return
 *   Status
 */
status_t OVM9724_initialise_ext(
    camera_device_handle_t *ph_handle, 
    const camera_config_t *p_config, 
    const void *p_special_config)
{
    return OVM9724_initialise(ph_handle, p_config);
}


/*** end of file ***/
