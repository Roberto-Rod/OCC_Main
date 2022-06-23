/*****************************************************************************/
/**
 * @file 
 *   adc36xx.c
 * @brief 
 *   Driver for Texas Instruments ADC36XX Analogue to Digital Converter family
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

#include "adc36xx.h"
#include "spi.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/* Chip Selects */
#define ADC3663_PCS                     (SPI_CS0)
#define ADC3664_PCS                     (SPI_CS1)

/* Number of bytes in one transfer message */
#define ADC36XX_MESSAGE_LEN             (3u)

#define ADC36XX_WR_MASK                 (0u << 8u)
#define ADC36XX_RD_MASK                 (1u << 8u)

/* Register mapping */
#define ADC36XX_REG_CUSTOM_PAT_0        (0x14u)
#define ADC36XX_REG_CUSTOM_PAT_1        (0x15u)
#define ADC36XX_REG_CUSTOM_PAT_2        (0x16u)
#define ADC36XX_REG_FCLK_PAT_0          (0x20u)
#define ADC36XX_REG_FCLK_PAT_1          (0x21u)
#define ADC36XX_REG_FCLK_PAT_2          (0x22u)
#define ADC36XX_REG_NCO_A_0             (0x2Au)
#define ADC36XX_REG_NCO_A_1             (0x2Bu)
#define ADC36XX_REG_NCO_A_2             (0x2Cu)
#define ADC36XX_REG_NCO_A_3             (0x2Du)
#define ADC36XX_REG_NCO_B_0             (0x31u)
#define ADC36XX_REG_NCO_B_1             (0x32u)
#define ADC36XX_REG_NCO_B_2             (0x33u)
#define ADC36XX_REG_NCO_B_3             (0x34u)

/* Custom pattern register values */
#define ADC36XX_CUSTOM_PAT_RAMP_18BIT   (0x00001ull)
#define ADC36XX_CUSTOM_PAT_RAMP_16BIT   (0x00100ull)
#define ADC36XX_CUSTOM_PAT_RAMP_14BIT   (0x10001ull)
#define ADC36XX_CUSTOM_PAT_USER         (0x12345ull)
#define ADC36XX_TEST_PAT_DISABLED       (0x0u)
#define ADC36XX_TEST_PAT_RAMP           (0x2u)
#define ADC36XX_TEST_PAT_CONSTANT       (0x3u)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

typedef struct 
{
    uint8_t reset             : 1;
    uint8_t _reserved         : 7;
} adc36xx_reg_00_t;

typedef struct 
{
    uint8_t op_if_sel         : 3;
    uint8_t op_if_en          : 1;
    uint8_t _reserved         : 1;
    uint8_t op_if_mapper      : 3;
} adc36xx_reg_07_t;

typedef struct 
{
    uint8_t pdn_global        : 1;
    uint8_t pdn_b             : 1;
    uint8_t pdn_a             : 1;
    uint8_t _reserved1        : 1;
    uint8_t pdn_refamp        : 1;
    uint8_t pdn_clkbuf        : 1;
    uint8_t _reserved2        : 2;
} adc36xx_reg_08_t;

typedef struct 
{
    uint8_t pdn_db0           : 1;
    uint8_t pdn_db1           : 1;
    uint8_t pdn_da0           : 1;
    uint8_t pdn_da1           : 1;
    uint8_t pdn_dclkout       : 1;
    uint8_t pdn_fclkout       : 1;
    uint8_t _reserved         : 2;
} adc36xx_reg_09_t;

typedef struct 
{
    uint8_t _reserved1        : 1;
    uint8_t mask_bg_dis       : 1;
    uint8_t mask_refamp       : 1;
    uint8_t mask_clkbuf       : 1;
    uint8_t _reserved2        : 4;
} adc36xx_reg_0d_t;

typedef struct 
{
    uint8_t se_clk_en         : 1;
    uint8_t ref_sel           : 2;
    uint8_t ref_ctrl          : 1;
    uint8_t _reserved1        : 1;
    uint8_t spi_sync_en       : 1;
    uint8_t spi_sync          : 1;
    uint8_t sync_pin_en       : 1;
} adc36xx_reg_0e_t;

typedef struct 
{
    uint8_t az_en             : 1;
    uint8_t _reserved1        : 1;
    uint8_t dll_pdn           : 1;
    uint8_t _reserved2        : 1;
    uint8_t se_b              : 1;
    uint8_t se_a              : 1;
    uint8_t _reserved3        : 2;
} adc36xx_reg_11_t;

typedef struct 
{
    uint8_t efuse_ld          : 1;
    uint8_t _reserved         : 7;
} adc36xx_reg_13_t;

typedef struct 
{
    uint8_t custom_pat_h      : 2;
    uint8_t test_pat_a        : 3;
    uint8_t test_pat_b        : 3;
} adc36xx_reg_16_t;

typedef struct 
{
    uint8_t tog_fclk          : 1;
    uint8_t _reserved1        : 3;
    uint8_t fclk_div          : 1;
    uint8_t _reserved2        : 2;
    uint8_t fclk_src          : 1;
} adc36xx_reg_19_t;

typedef struct 
{
    uint8_t _reserved1        : 6;
    uint8_t lvds_half_swing   : 1;
    uint8_t _reserved2        : 1;
} adc36xx_reg_1a_t;

typedef struct 
{
    uint8_t _reserved         : 3;
    uint8_t bit_mapper_res    : 3;
    uint8_t _20b_en           : 1;
    uint8_t mapper_en         : 1;
} adc36xx_reg_1b_t;

typedef struct 
{
    uint8_t lvds_dclk_del     : 2;
    uint8_t lvds_data_del     : 2;
    uint8_t _reserved         : 4;
} adc36xx_reg_1e_t;

typedef struct 
{
    uint8_t _reserved1        : 1;
    uint8_t ddc_en            : 1;
    uint8_t dig_byp           : 1;
    uint8_t ddc_mux           : 2;
    uint8_t ch_avg_en         : 1;
    uint8_t _reserved2        : 2;
} adc36xx_reg_24_t;

typedef struct 
{
    uint8_t mix_phase         : 1;
    uint8_t _reserved         : 2;
    uint8_t real_out          : 1;
    uint8_t decimation        : 3;
    uint8_t ddc_mux_en        : 1;
} adc36xx_reg_25_t;

typedef struct 
{
    uint8_t fs_mix_b          : 1;
    uint8_t mix_res_b         : 1;
    uint8_t mix_gain_b        : 2;
    uint8_t fs_mix_a          : 1;
    uint8_t mix_res_a         : 1;
    uint8_t mix_gain_a        : 2;
} adc36xx_reg_26_t;

typedef struct 
{
    uint8_t _reserved1        : 2;
    uint8_t fs_mix_ph_a       : 1;
    uint8_t qdel_a            : 1;
    uint8_t op_order_a        : 1;
    uint8_t _reserved2        : 3;
} adc36xx_reg_27_t;

typedef struct 
{
    uint8_t _reserved1        : 2;
    uint8_t fs_mix_ph_b       : 1;
    uint8_t qdel_b            : 1;
    uint8_t op_order_b        : 1;
    uint8_t _reserved2        : 3;
} adc36xx_reg_2e_t;

typedef struct 
{
    uint8_t _reserved1        : 1;
    uint8_t format_a          : 1;
    uint8_t _reserved2        : 6;
} adc36xx_reg_8f_t;

typedef struct 
{
    uint8_t _reserved1        : 1;
    uint8_t format_b          : 1;
    uint8_t _reserved2        : 6;
} adc36xx_reg_92_t;

typedef union 
{
    adc36xx_reg_00_t    bitmap_00;
    adc36xx_reg_07_t    bitmap_07;
    adc36xx_reg_08_t    bitmap_08;
    adc36xx_reg_09_t    bitmap_09;
    adc36xx_reg_0d_t    bitmap_0d;
    adc36xx_reg_0e_t    bitmap_0e;
    adc36xx_reg_11_t    bitmap_11;
    adc36xx_reg_13_t    bitmap_13;
    adc36xx_reg_16_t    bitmap_16;
    adc36xx_reg_19_t    bitmap_19;
    adc36xx_reg_1a_t    bitmap_1a;
    adc36xx_reg_1b_t    bitmap_1b;
    adc36xx_reg_1e_t    bitmap_1e;
    adc36xx_reg_24_t    bitmap_24;
    adc36xx_reg_25_t    bitmap_25;
    adc36xx_reg_26_t    bitmap_26;
    adc36xx_reg_27_t    bitmap_27;
    adc36xx_reg_2e_t    bitmap_2e;
    adc36xx_reg_8f_t    bitmap_8f;
    adc36xx_reg_92_t    bitmap_92;
    uint8_t             byte;
} adc36xx_register_t;

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

static status_t write_register(
    spi_pcs_t pcs, uint32_t reg, adc36xx_register_t value);

static status_t adc36xx_reset(spi_pcs_t pcs);
static status_t adc3663_configure(void);
static status_t adc3664_configure(void);

/**
 * @brief
 *   Write to an ADC36XX register
 * @param
 *   pcs Chip Select index
 * @param
 *   reg 11-bit register address 
 * @param
 *   value 8-bit value to be written 
 * @return
 *   Status
 */
static status_t write_register(
    spi_pcs_t pcs, uint32_t reg, adc36xx_register_t value)
{
    uint8_t p_data[ADC36XX_MESSAGE_LEN];
  
    p_data[0] = ADC36XX_WR_MASK | (uint8_t)((reg & 0x700u) >> 8u);
    p_data[1] = (uint8_t)(reg & 0x0FFu);
    p_data[2] = value.byte;
  
    status_t status = SPI_send(
        SPI3, 
        pcs,
        p_data,
        sizeof(p_data));
  
    return status;
}

/**
 * @brief
 *   Reset the specified ADC36XX device
 * @param
 *   pcs Chip Select index
 * @return
 *   Status
 */
static status_t adc36xx_reset(spi_pcs_t pcs)
{
    adc36xx_register_t value = 
    {
        .bitmap_00.reset = 1u
    };
    
    return write_register(pcs, 0x00u, value);
}

/**
 * @brief
 *   Configure the 16-bit ADC3663 device
 * @todo
 *   See section 8.3.5.2.1 of ADC3663 data sheet for an example configuration
 * @return
 *   Status
 */
static status_t adc3663_configure(void)
{
    status_t status;
    adc36xx_register_t value; 
  
    /* Configure a test pattern */
    value.byte = (uint8_t)(ADC36XX_CUSTOM_PAT_RAMP_16BIT & 0xFFu);
    status = write_register(ADC3663_PCS, ADC36XX_REG_CUSTOM_PAT_0, value);
      
    if (kStatus_Success == status)
    {
        value.byte = (uint8_t)((ADC36XX_CUSTOM_PAT_RAMP_16BIT >> 8u) & 0xFFu);
        status = write_register(ADC3663_PCS, ADC36XX_REG_CUSTOM_PAT_1, value);
    }
      
    if (kStatus_Success == status)
    {
        value.bitmap_16.custom_pat_h = ADC36XX_CUSTOM_PAT_RAMP_16BIT >> 16u;
        value.bitmap_16.test_pat_a = ADC36XX_TEST_PAT_RAMP;
        value.bitmap_16.test_pat_b = ADC36XX_TEST_PAT_CONSTANT;
        status = write_register(ADC3663_PCS, ADC36XX_REG_CUSTOM_PAT_2, value);
    }
    
    return status;
}

/**
 * @brief
 *   Configure the 14-bit ADC3664 device
 * @return
 *   Status
 */
static status_t adc3664_configure(void)
{
    status_t status;
    adc36xx_register_t value; 
  
    /* Configure a test pattern */
    value.byte = (uint8_t)(ADC36XX_CUSTOM_PAT_RAMP_14BIT & 0xFFu);
    status = write_register(ADC3664_PCS, ADC36XX_REG_CUSTOM_PAT_0, value);
      
    if (kStatus_Success == status)
    {
        value.byte = (uint8_t)((ADC36XX_CUSTOM_PAT_RAMP_14BIT >> 8u) & 0xFFu);
        status = write_register(ADC3664_PCS, ADC36XX_REG_CUSTOM_PAT_1, value);
    }
      
    if (kStatus_Success == status)
    {
        value.bitmap_16.custom_pat_h = ADC36XX_CUSTOM_PAT_RAMP_14BIT >> 16u;
        value.bitmap_16.test_pat_a = ADC36XX_TEST_PAT_RAMP;
        value.bitmap_16.test_pat_b = ADC36XX_TEST_PAT_CONSTANT;
        status = write_register(ADC3664_PCS, ADC36XX_REG_CUSTOM_PAT_2, value);
    }
    
    return status;
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Initialise the ADC36XX Analogue to Digital Converter(s)
 * @return
 *   Status
 */
status_t ADC36XX_initialise(void)
{
    status_t status;
  
    SPI_initialise();
    
    /** @todo Don't need to reset - just showing how it's done */
    status = adc36xx_reset(ADC3663_PCS);
    if (kStatus_Success == status)
    {
        status = adc36xx_reset(ADC3664_PCS);
    }
    
    /* Configure the ADCs */
    if (kStatus_Success == status)
    {
        status = adc3663_configure();
    }
    if (kStatus_Success == status)
    {
        status = adc3664_configure();
    }

    return status;
}

/*** end of file ***/
