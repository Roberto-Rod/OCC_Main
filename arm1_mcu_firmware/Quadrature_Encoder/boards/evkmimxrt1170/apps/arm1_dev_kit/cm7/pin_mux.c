/*
 * Copyright 2021 Embedded Artists AB
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* GPIO_EMC */
#define EMC_ODE       (1<<4) /* open drain enabled */
#define EMC_PULL_UP   (1<<2) /* weak pull up + enable pull */
#define EMC_PULL_DOWN (2<<2) /* weak pull down + enable pull */
#define EMC_PULL_NONE (3<<2) /* pull disabled */
#define EMC_DRV_HI    (0<<1) /* high drive strength */
#define EMC_DRV_NORM  (1<<1) /* normal drive strength */

/* GPIO_SD */
#define SD_ODE       (1<<4) /* open drain enabled */
#define SD_PULL_UP   (1<<2) /* weak pull up + enable pull */
#define SD_PULL_DOWN (2<<2) /* weak pull down + enable pull */
#define SD_PULL_NONE (3<<2) /* pull disabled */
#define SD_DRV_HI    (0<<1) /* high drive strength */
#define SD_DRV_NORM  (1<<1) /* normal drive strength */

/* GPIO_DISP_B1 */
#define DISP_B1_ODE       (1<<4) /* open drain enabled */
#define DISP_B1_PULL_UP   (1<<2) /* weak pull up + enable pull */
#define DISP_B1_PULL_DOWN (2<<2) /* weak pull down + enable pull */
#define DISP_B1_PULL_NONE (3<<2) /* pull disabled */
#define DISP_B1_DRV_HI    (0<<1) /* high drive strength */
#define DISP_B1_DRV_NORM  (1<<1) /* normal drive strength */

/* GPIO_DISP_B2 */
#define DISP_B2_ODE       (1<<4) /* open drain enabled */
#define DISP_B2_PULL_UP   (3<<2) /* weak pull up + enable pull */
#define DISP_B2_PULL_DOWN (1<<2) /* weak pull down + enable pull */
#define DISP_B2_PULL_NONE (0<<2) /* pull disabled */
#define DISP_B2_DRV_HI    (1<<1) /* high drive strength */
#define DISP_B2_DRV_NORM  (0<<1) /* normal drive strength */
#define DISP_B2_SLEW_FAST (1<<0) /* fast slew rate */
#define DISP_B2_SLEW_SLOW (0<<0) /* slow slew rate */

/* GPIO_AD */
#define AD_ODE       (1<<4) /* open drain enabled */
#define AD_PULL_UP   (3<<2) /* weak pull up + enable pull */
#define AD_PULL_DOWN (1<<2) /* weak pull down + enable pull */
#define AD_PULL_NONE (0<<2) /* pull disabled */
#define AD_DRV_HI    (1<<1) /* high drive strength */
#define AD_DRV_NORM  (0<<1) /* normal drive strength */
#define AD_SLEW_FAST (1<<0) /* fast slew rate */
#define AD_SLEW_SLOW (0<<0) /* slow slew rate */

/* GPIO_LPSR */
#define LPSR_ODE       (1<<5) /* open drain enabled */
#define LPSR_PULL_UP   (3<<2) /* weak pull up + enable pull */
#define LPSR_PULL_DOWN (1<<2) /* weak pull down + enable pull */
#define LPSR_PULL_NONE (0<<2) /* pull disabled */
#define LPSR_DRV_HI    (1<<1) /* high drive strength */
#define LPSR_DRV_NORM  (0<<1) /* normal drive strength */
#define LPSR_SLEW_FAST (1<<0) /* fast slew rate */
#define LPSR_SLEW_SLOW (0<<0) /* slow slew rate */

/* GPIO_SNVS */
#define SNVS_ODE       (1<<6) /* open drain enabled */
#define SNVS_PULL_UP   (3<<2) /* weak pull up + enable pull */
#define SNVS_PULL_DOWN (1<<2) /* weak pull down + enable pull */
#define SNVS_PULL_NONE (0<<2) /* pull disabled */
#define SNVS_DRV_HI    (1<<1) /* high drive strength */
#define SNVS_DRV_NORM  (0<<1) /* normal drive strength */
#define SNVS_SLEW_FAST (1<<0) /* fast slew rate */
#define SNVS_SLEW_SLOW (0<<0) /* slow slew rate */

#define MUST_FIX_THIS  (-1)

typedef enum {
    input, out_high, out_low,
} gpio_type_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Guard to prevent multiple initialization of pins in cases where main()
 * calls multiple BOARD_Init* functions, like for example both
 * BOARD_InitPins() and BOARD_InitLpuartPins().
 */
static bool first_time_calling = true;

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Convenience function so that both calls to SetPinMux and SetPinConfig can
 * be done on one line without repetition
 */
static void SETUP(uint32_t muxRegister,
                  uint32_t muxMode,
                  uint32_t inputRegister,
                  uint32_t inputDaisy,
                  uint32_t configRegister,
                  uint32_t inputOnfield,
                  uint32_t configValue) {

    *((volatile uint32_t*) muxRegister) =
            IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(muxMode) | IOMUXC_SW_MUX_CTL_PAD_SION(inputOnfield);

    if (inputRegister != 0UL) {
        *((volatile uint32_t*) inputRegister) = inputDaisy;
    }
    if (configRegister != 0UL) {
        *((volatile uint32_t*) configRegister) = configValue;
    }
}

/* Same as SETUP() but also configures GPIO for pin
 */
static void SETUPG(uint32_t muxRegister,
                   uint32_t muxMode,
                   uint32_t inputRegister,
                   uint32_t inputDaisy,
                   uint32_t configRegister,
                   uint32_t inputOnfield,
                   uint32_t configValue,
                   GPIO_Type *port,
                   uint32_t pin,
                   gpio_type_t type) {

    *((volatile uint32_t*) muxRegister) =
            IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(muxMode) | IOMUXC_SW_MUX_CTL_PAD_SION(inputOnfield);

    if (inputRegister != 0UL) {
        *((volatile uint32_t*) inputRegister) = inputDaisy;
    }
    if (configRegister != 0UL) {
        *((volatile uint32_t*) configRegister) = configValue;
    }
    gpio_pin_config_t cfg = {
        .direction     = (type == input) ? kGPIO_DigitalInput : kGPIO_DigitalOutput,
        .interruptMode = kGPIO_NoIntmode,
        .outputLogic   = (type == out_high) ? 1 : 0,
    };
    GPIO_PinInit(port, pin, &cfg);
}


/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins_uCOM_Board
 * Description   : Initializes pins available on the iMXRT1176 uCOM Board
 *
 * END ****************************************************************************************************************/
static void BOARD_InitPins_uCOM_Board(void) {
    CLOCK_EnableClock(kCLOCK_Iomuxc);
    CLOCK_EnableClock(kCLOCK_Iomuxc_Lpsr);

    /* UART-A, Main console UART */
    SETUP(IOMUXC_GPIO_AD_24_LPUART1_TXD, 0, AD_PULL_NONE + AD_DRV_HI + AD_SLEW_SLOW);
    SETUP(IOMUXC_GPIO_AD_25_LPUART1_RXD, 1, AD_PULL_NONE + AD_DRV_HI + AD_SLEW_SLOW);

    /* UART-B, Console UART for Cortex-M4 */
    SETUP(IOMUXC_GPIO_EMC_B1_40_LPUART6_TXD, 0, EMC_PULL_NONE + EMC_DRV_HI);
    SETUP(IOMUXC_GPIO_EMC_B1_41_LPUART6_RXD, 1, EMC_PULL_NONE + EMC_DRV_HI);

    /* UART-C, Used by Microbus and M.2 Bluetooth */
    SETUP(IOMUXC_GPIO_AD_00_LPUART7_TXD,   0, AD_PULL_NONE + AD_DRV_HI + AD_SLEW_SLOW);
    SETUP(IOMUXC_GPIO_AD_01_LPUART7_RXD,   1, AD_PULL_NONE + AD_DRV_HI + AD_SLEW_SLOW);
    SETUP(IOMUXC_GPIO_AD_02_LPUART7_CTS_B, 0, AD_PULL_NONE + AD_DRV_HI + AD_SLEW_SLOW);
    SETUP(IOMUXC_GPIO_AD_03_LPUART7_RTS_B, 1, AD_PULL_NONE + AD_DRV_HI + AD_SLEW_SLOW);

    /* SD1_VSELECT: NVCC_SD fixed at 1.8V (by setting this signal high)
     * This pin is used as an GPIO for Wi-Fi examples but must be switched to SD1_VSELECT
     * when using SDCARD examples, see BOARD_InitSDCardPins() below. */
    SETUPG(IOMUXC_GPIO_AD_34_GPIO10_IO01, 0, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW, GPIO10, 1, out_high);

    /* WDOG */
    SETUPG(IOMUXC_GPIO_AD_04_GPIO9_IO03, 0, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW, GPIO9, 3, out_low);

    /* BOOT */
    SETUPG(IOMUXC_GPIO_LPSR_02_GPIO12_IO02, 0, LPSR_PULL_NONE + LPSR_DRV_HI + LPSR_SLEW_SLOW, GPIO12, 2, input);
    SETUPG(IOMUXC_GPIO_LPSR_03_GPIO12_IO03, 0, LPSR_PULL_NONE + LPSR_DRV_HI + LPSR_SLEW_SLOW, GPIO12, 3, input);

    /* I2C-A */
    SETUP(IOMUXC_GPIO_LPSR_04_LPI2C5_SDA, 1, LPSR_ODE + LPSR_PULL_NONE + LPSR_DRV_NORM + LPSR_SLEW_SLOW);
    SETUP(IOMUXC_GPIO_LPSR_05_LPI2C5_SCL, 1, LPSR_ODE + LPSR_PULL_NONE + LPSR_DRV_NORM + LPSR_SLEW_SLOW);

    /* QSPI */
    SETUP(IOMUXC_GPIO_SD_B2_05_FLEXSPI1_A_DQS,    1, SD_PULL_UP + SD_DRV_HI);
    SETUP(IOMUXC_GPIO_SD_B2_06_FLEXSPI1_A_SS0_B,  0, SD_PULL_DOWN + SD_DRV_NORM);
    SETUP(IOMUXC_GPIO_SD_B2_07_FLEXSPI1_A_SCLK,   0, SD_PULL_DOWN + SD_DRV_NORM);
    SETUP(IOMUXC_GPIO_SD_B2_08_FLEXSPI1_A_DATA00, 0, SD_PULL_DOWN + SD_DRV_NORM);
    SETUP(IOMUXC_GPIO_SD_B2_09_FLEXSPI1_A_DATA01, 0, SD_PULL_DOWN + SD_DRV_NORM);
    SETUP(IOMUXC_GPIO_SD_B2_10_FLEXSPI1_A_DATA02, 0, SD_PULL_DOWN + SD_DRV_NORM);
    SETUP(IOMUXC_GPIO_SD_B2_11_FLEXSPI1_A_DATA03, 0, SD_PULL_DOWN + SD_DRV_NORM);

    /* SDRAM */
    // Skip as it is done either by debug script or DCD. See BOARD_InitSEMCPins() below.

    /* ENET (100/10Mbit Ethernet-PHY Adapter)
     *
     * ENET_INT: GPIO3.25
     * ENET_RST: GPIO9.26
     */
    SETUPG(IOMUXC_GPIO_AD_26_GPIO_MUX3_IO25,     0, AD_PULL_NONE + AD_DRV_NORM + AD_SLEW_SLOW, GPIO3, 25, input);    /* BOARD_MIPI_PANEL_TOUCH_INT */
    SETUPG(IOMUXC_GPIO_AD_27_GPIO9_IO26,         0, AD_PULL_NONE + AD_DRV_NORM + AD_SLEW_SLOW, GPIO9, 26, out_high); /* BOARD_MIPI_PANEL_TOUCH_RST */
    SETUP(IOMUXC_GPIO_AD_32_ENET_MDC,            0, AD_PULL_DOWN + AD_DRV_HI + AD_SLEW_FAST);
    SETUP(IOMUXC_GPIO_AD_33_ENET_MDIO,           0, AD_PULL_DOWN + AD_DRV_HI + AD_SLEW_FAST);
    SETUP(IOMUXC_GPIO_DISP_B2_02_ENET_TX_DATA00, 0, DISP_B2_PULL_NONE + DISP_B2_DRV_HI + DISP_B2_SLEW_FAST);
    SETUP(IOMUXC_GPIO_DISP_B2_03_ENET_TX_DATA01, 0, DISP_B2_PULL_NONE + DISP_B2_DRV_HI + DISP_B2_SLEW_FAST);
    SETUP(IOMUXC_GPIO_DISP_B2_04_ENET_TX_EN,     0, DISP_B2_PULL_NONE + DISP_B2_DRV_HI + DISP_B2_SLEW_FAST);
    SETUP(IOMUXC_GPIO_DISP_B2_05_ENET_REF_CLK,   1, DISP_B2_PULL_NONE + DISP_B2_DRV_HI + DISP_B2_SLEW_FAST);
    SETUP(IOMUXC_GPIO_DISP_B2_06_ENET_RX_DATA00, 0, DISP_B2_PULL_DOWN + DISP_B2_DRV_HI + DISP_B2_SLEW_SLOW);
    SETUP(IOMUXC_GPIO_DISP_B2_07_ENET_RX_DATA01, 0, DISP_B2_PULL_DOWN + DISP_B2_DRV_HI + DISP_B2_SLEW_SLOW);
    SETUP(IOMUXC_GPIO_DISP_B2_08_ENET_RX_EN,     0, DISP_B2_PULL_DOWN + DISP_B2_DRV_HI + DISP_B2_SLEW_SLOW);
    SETUP(IOMUXC_GPIO_DISP_B2_09_ENET_RX_ER,     0, DISP_B2_PULL_DOWN + DISP_B2_DRV_HI + DISP_B2_SLEW_SLOW);
    IOMUXC_GPR->GPR4 = ((IOMUXC_GPR->GPR4
            & (~(IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR_MASK))) /* Mask bits to zero which are setting */
            | IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR(0x01U) /* ENET_REF_CLK direction control: 0x01U */
    );

    /* ENET 1G (Onboard PHY)
     *
     * ENET_INT: GPIO13.9
     * ENET_RST: GPIO13.10
     * ENET_WOL: GPIO13.11  (never used but declared)
     */
    SETUP(IOMUXC_GPIO_DISP_B1_00_ENET_1G_RX_EN,     0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_01_ENET_1G_RX_CLK,    0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_02_ENET_1G_RX_DATA00, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_03_ENET_1G_RX_DATA01, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_04_ENET_1G_RX_DATA02, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_05_ENET_1G_RX_DATA03, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_06_ENET_1G_TX_DATA03, 0U, DISP_B1_PULL_NONE + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_07_ENET_1G_TX_DATA02, 0U, DISP_B1_PULL_NONE + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_08_ENET_1G_TX_DATA01, 0U, DISP_B1_PULL_NONE + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_09_ENET_1G_TX_DATA00, 0U, DISP_B1_PULL_NONE + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_10_ENET_1G_TX_EN,     0U, DISP_B1_PULL_NONE + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_11_ENET_1G_TX_CLK_IO, 0U, DISP_B1_PULL_NONE + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_EMC_B2_19_ENET_1G_MDC,        0U, EMC_PULL_DOWN + EMC_DRV_HI);
    SETUP(IOMUXC_GPIO_EMC_B2_20_ENET_1G_MDIO,       0U, EMC_PULL_DOWN + EMC_DRV_HI);
    SETUPG(IOMUXC_GPIO_SNVS_06_DIG_GPIO13_IO09, 1, SNVS_PULL_UP   + SNVS_DRV_NORM + SNVS_SLEW_SLOW, GPIO13,  9, input);   /* RGMII_PHY_INTB */
    SETUPG(IOMUXC_GPIO_SNVS_07_DIG_GPIO13_IO10, 1, SNVS_PULL_NONE + SNVS_DRV_NORM + SNVS_SLEW_SLOW, GPIO13, 10, out_high);/* ETHPHY_RST_B */
    SETUPG(IOMUXC_GPIO_SNVS_08_DIG_GPIO13_IO11, 1, SNVS_PULL_UP   + SNVS_DRV_NORM + SNVS_SLEW_SLOW, GPIO13, 11, input);   /* ENET_RGMII_WOL */

    /* MIPI */
    //SETUP(IOMUXC_GPIO_AD_02_GPIO9_IO01,       0U, 0x04U); // Was BOARD_MIPI_PANEL_RST_GPIO but is now controlled with PCA6416 (PCA_LCD_DISP_MIPI_RST)
    //SETUP(IOMUXC_GPIO_AD_30_GPIO9_IO29,       0U, 0x04U); // Was BOARD_MIPI_PANEL_BL_GPIO but is now controlled with PCA6416 (PCA9530_LED0)
    //SETUP(IOMUXC_GPIO_DISP_B2_15_GPIO11_IO16, 0U, 0x04U); // Was BOARD_MIPI_PANEL_POWER_GPIO but is now controlled with PCA6416 (PCA_LCD_BL_PWR)

    /* SPI */
    SETUP(IOMUXC_GPIO_AD_28_LPSPI1_SCK,       0U, AD_DRV_HI + AD_PULL_NONE + AD_SLEW_SLOW);
    SETUP(IOMUXC_GPIO_AD_29_LPSPI1_PCS0,      0U, AD_DRV_HI + AD_PULL_NONE + AD_SLEW_SLOW);
    SETUP(IOMUXC_GPIO_AD_30_LPSPI1_SOUT,      0U, AD_DRV_HI + AD_PULL_NONE + AD_SLEW_SLOW);
    SETUP(IOMUXC_GPIO_AD_31_LPSPI1_SIN,       0U, AD_DRV_HI + AD_PULL_NONE + AD_SLEW_SLOW);

    /* From Hello World */
    SETUP(IOMUXC_GPIO_LPSR_11_ARM_TRACE_SWO, 0, LPSR_PULL_NONE + LPSR_DRV_HI + LPSR_SLEW_SLOW); // Was IOMUXC_GPIO_DISP_B2_07_ARM_TRACE_SWO
}

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins_uCOM_Carrier_Board
 * Description   : Initializes pins available on the uCOM Carrier Board
 *
 * END ****************************************************************************************************************/
static void BOARD_InitPins_uCOM_Carrier_Board(void) {
    if (first_time_calling) {
        first_time_calling = false;
        BOARD_InitPins_uCOM_Board();

        /* SW5/WAKEUP button */
        SETUPG(IOMUXC_WAKEUP_DIG_GPIO13_IO00, 1, SNVS_PULL_UP + SNVS_DRV_HI + SNVS_SLEW_SLOW, GPIO13, 0, input);

        /* I2C-B */
        SETUP(IOMUXC_GPIO_LPSR_06_LPI2C6_SDA, 1, LPSR_ODE + LPSR_PULL_NONE + LPSR_DRV_NORM + LPSR_SLEW_SLOW);
        SETUP(IOMUXC_GPIO_LPSR_07_LPI2C6_SCL, 1, LPSR_ODE + LPSR_PULL_NONE + LPSR_DRV_NORM + LPSR_SLEW_SLOW);

        /* I2C-C */
        //SETUP(IOMUXC_GPIO_AD_33_LPI2C1_SDA, 1, AD_ODE + AD_PULL_NONE + AD_DRV_NORM + AD_SLEW_SLOW); // In conflict with IOMUXC_GPIO_AD_33_ENET_MDIO
        //SETUP(IOMUXC_GPIO_AD_32_LPI2C1_SCL, 1, AD_ODE + AD_PULL_NONE + AD_DRV_NORM + AD_SLEW_SLOW); // In conflict with IOMUXC_GPIO_AD_32_ENET_MDC

        /* M.2 Wi-Fi */
        //SETUP(IOMUXC_GPIO_AD_32_GPIO_MUX3_IO31,  0, 0x02U); /* Was SD1_CD (not used now) */
        //SETUP(IOMUXC_GPIO_AD_34_GPIO10_IO01,     0, 0x0EU); /* SD1_VSELECT */
        //SETUP(IOMUXC_GPIO_AD_35_GPIO10_IO02,     0, 0x02U); /* Was SD_PWREN */
        SETUP(IOMUXC_GPIO_SD_B1_00_USDHC1_CMD,   1, SD_PULL_UP   + SD_DRV_HI);
        SETUP(IOMUXC_GPIO_SD_B1_01_USDHC1_CLK,   1, SD_PULL_NONE + SD_DRV_HI);
        SETUP(IOMUXC_GPIO_SD_B1_02_USDHC1_DATA0, 1, SD_PULL_UP   + SD_DRV_HI);
        SETUP(IOMUXC_GPIO_SD_B1_03_USDHC1_DATA1, 1, SD_PULL_UP   + SD_DRV_HI);
        SETUP(IOMUXC_GPIO_SD_B1_04_USDHC1_DATA2, 1, SD_PULL_UP   + SD_DRV_HI);
        SETUP(IOMUXC_GPIO_SD_B1_05_USDHC1_DATA3, 1, SD_PULL_UP   + SD_DRV_HI);
//      IOMUXC_GPR->GPR43 = ((IOMUXC_GPR->GPR43 &
//        (~(IOMUXC_GPR_GPR43_GPIO_MUX3_GPIO_SEL_HIGH_MASK))) /* Mask bits to zero which are setting */
//          | IOMUXC_GPR_GPR43_GPIO_MUX3_GPIO_SEL_HIGH(0x8000U) /* GPIO3 and CM7_GPIO3 share same IO MUX function, GPIO_MUX3 selects one GPIO function: 0x8000U */
//        );

        /* SAI - This interface is connected to the E-key M.2 connector (J33) */
        SETUP(IOMUXC_GPIO_AD_17_SAI1_MCLK,      1, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW);
        SETUP(IOMUXC_GPIO_AD_18_SAI1_RX_SYNC,   1, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW);
        SETUP(IOMUXC_GPIO_AD_19_SAI1_RX_BCLK,   1, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW);
        SETUP(IOMUXC_GPIO_AD_20_SAI1_RX_DATA00, 1, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW);
        SETUP(IOMUXC_GPIO_AD_21_SAI1_TX_DATA00, 1, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW);
        SETUP(IOMUXC_GPIO_AD_22_SAI1_TX_BCLK,   1, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW);
        SETUP(IOMUXC_GPIO_AD_23_SAI1_TX_SYNC,   1, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW);
        IOMUXC_GPR->GPR0 = ((IOMUXC_GPR->GPR0 &
               (~(IOMUXC_GPR_GPR0_SAI1_MCLK_DIR_MASK)))  /* Mask bits to zero which are setting */
               | IOMUXC_GPR_GPR0_SAI1_MCLK_DIR(0x01U)  /* SAI1_MCLK signal direction control: 0x01U */
        );

        /* Bluetooth UART 1V8 */
        SETUP(IOMUXC_GPIO_SD_B2_00_LPUART9_TXD,   1, SD_PULL_DOWN + SD_DRV_HI);
        SETUP(IOMUXC_GPIO_SD_B2_01_LPUART9_RXD,   1, SD_PULL_DOWN + SD_DRV_HI);
        SETUP(IOMUXC_GPIO_SD_B2_02_LPUART9_CTS_B, 1, SD_PULL_DOWN + SD_DRV_HI);
        SETUP(IOMUXC_GPIO_SD_B2_03_LPUART9_RTS_B, 1, SD_PULL_DOWN + SD_DRV_HI);

        /* BT/WL
         *
         * BT_REG_ON:        GPIO13.4
         * BT_DEV_WAKE:      GPIO13.5
         * BT_HOST_WAKE:     GPIO13.6
         * WL_REG_ON:        GPIO13.7
         * WL_DEV_WAKE:      GPIO13.8
         * WL_HOST_WAKE_1V8: GPIO10.13
         */
        SETUPG(IOMUXC_GPIO_SNVS_01_DIG_GPIO13_IO04, 1, SNVS_PULL_DOWN + SNVS_DRV_NORM + SNVS_SLEW_SLOW, GPIO13, 4, out_low);
        SETUPG(IOMUXC_GPIO_SNVS_02_DIG_GPIO13_IO05, 1, SNVS_PULL_DOWN + SNVS_DRV_NORM + SNVS_SLEW_SLOW, GPIO13, 5, out_high);
        SETUPG(IOMUXC_GPIO_SNVS_03_DIG_GPIO13_IO06, 1, SNVS_PULL_DOWN + SNVS_DRV_NORM + SNVS_SLEW_SLOW, GPIO13, 6, input);
        SETUPG(IOMUXC_GPIO_SNVS_04_DIG_GPIO13_IO07, 1, SNVS_PULL_DOWN + SNVS_DRV_NORM + SNVS_SLEW_SLOW, GPIO13, 7, out_low);
        SETUPG(IOMUXC_GPIO_SNVS_05_DIG_GPIO13_IO08, 1, SNVS_PULL_DOWN + SNVS_DRV_NORM + SNVS_SLEW_SLOW, GPIO13, 8, out_low);
        SETUPG(IOMUXC_GPIO_SD_B2_04_GPIO10_IO13,    1, SD_PULL_UP + SD_DRV_NORM, GPIO10, 13, input);

        /* USB1 */
        SETUP(IOMUXC_GPIO_AD_09_USBPHY1_OTG_ID, 1, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW);
        SETUP(IOMUXC_GPIO_AD_10_USB_OTG1_PWR,   1, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW);
        SETUP(IOMUXC_GPIO_AD_11_USB_OTG1_OC,    1, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW);

        /* USB2 */
        SETUP(IOMUXC_GPIO_AD_06_USB_OTG2_OC,    1, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW);
        SETUP(IOMUXC_GPIO_AD_07_USB_OTG2_PWR,   1, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW);
        SETUP(IOMUXC_GPIO_AD_08_USBPHY2_OTG_ID, 1, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW);

        /* MIPI Touch
         *
         * CTP_IRQ: GPIO3.25   (initialized above when intializing the 100/10Mbit Ethernet-PHY Adapter)
         * CTP_RST: GPIO9.26   (initialized above when intializing the 100/10Mbit Ethernet-PHY Adapter)
         */
        //SETUPG(IOMUXC_GPIO_AD_26_GPIO_MUX3_IO25, 1, AD_PULL_NONE + AD_DRV_NORM + AD_SLEW_SLOW, GPIO3, 25, input);
        //SETUPG(IOMUXC_GPIO_AD_27_GPIO9_IO26,     0, AD_PULL_NONE + AD_DRV_NORM + AD_SLEW_SLOW, GPIO9, 26, out_high);

        /* CSI/Camera
         *
         * CAMERA_PWDN: GPIO9.14
         * CAMERA_RST:  GPIO9.15
         */
        SETUPG(IOMUXC_GPIO_AD_15_GPIO9_IO14, 0, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW, GPIO9, 14, out_low);
        SETUPG(IOMUXC_GPIO_AD_16_GPIO9_IO15, 0, AD_PULL_DOWN + AD_DRV_NORM + AD_SLEW_SLOW, GPIO9, 15, out_low);

        /* FLEXCAN3 - No transceiver but the pins are available on expansion connector J15-37 and J15-38 */
        SETUP(IOMUXC_GPIO_LPSR_00_FLEXCAN3_TX, 1, LPSR_PULL_NONE + LPSR_DRV_HI + LPSR_SLEW_SLOW);
        SETUP(IOMUXC_GPIO_LPSR_01_FLEXCAN3_RX, 1, LPSR_PULL_NONE + LPSR_DRV_HI + LPSR_SLEW_SLOW);
        
        /* ENC */
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_DISP_B1_09_XBAR1_INOUT35,   /* GPIO_DISP_B1_09 is configured as XBAR1_INOUT35 */
            1u);                                    /* Software Input On Field: Force input path of pad GPIO_DISP_B1_09 */
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_DISP_B1_08_XBAR1_INOUT34,   /* GPIO_DISP_B1_08 is configured as XBAR1_INOUT34 */
            1u);                                    /* Software Input On Field: Force input path of pad GPIO_DISP_B1_08 */
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_DISP_B1_06_XBAR1_INOUT32,   /* GPIO_DISP_B1_06 is configured as XBAR1_INOUT32 */
            1u);                                    /* Software Input On Field: Force input path of pad GPIO_DISP_B1_06 */
        IOMUXC_GPR->GPR21 = ((IOMUXC_GPR->GPR21 &
          (~(IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_35_MASK | IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_34_MASK | IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_32_MASK))) /* Mask bits to zero which are setting */
            | IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_35(0x00U) /* IOMUXC XBAR_INOUT35 function direction select: 0x00U */
            | IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_34(0x00U) /* IOMUXC XBAR_INOUT34 function direction select: 0x00U */
            | IOMUXC_GPR_GPR21_IOMUXC_XBAR_DIR_SEL_32(0x00U) /* IOMUXC XBAR_INOUT32 function direction select: 0x00U */
          );
    }
}

void BOARD_InitPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void BOARD_InitBootPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void BOARD_InitEnetPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void BOARD_InitEnet1GPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void BOARD_InitMipiPanelPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();

    /* I2C-C for touch */
    SETUP(IOMUXC_GPIO_AD_33_LPI2C1_SDA, 1, AD_ODE + AD_PULL_NONE + AD_DRV_NORM + AD_SLEW_SLOW); // In conflict with IOMUXC_GPIO_AD_33_ENET_MDIO
    SETUP(IOMUXC_GPIO_AD_32_LPI2C1_SCL, 1, AD_ODE + AD_PULL_NONE + AD_DRV_NORM + AD_SLEW_SLOW); // In conflict with IOMUXC_GPIO_AD_32_ENET_MDC
}
void BOARD_InitLCDPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();

    /* I2C-C for touch */
    SETUP(IOMUXC_GPIO_AD_33_LPI2C1_SDA, 1, AD_ODE + AD_PULL_NONE + AD_DRV_NORM + AD_SLEW_SLOW); // In conflict with IOMUXC_GPIO_AD_33_ENET_MDIO
    SETUP(IOMUXC_GPIO_AD_32_LPI2C1_SCL, 1, AD_ODE + AD_PULL_NONE + AD_DRV_NORM + AD_SLEW_SLOW); // In conflict with IOMUXC_GPIO_AD_32_ENET_MDC
}
void BOARD_InitMipiCameraPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void BOARD_InitCSIPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void BOARD_InitSDCardPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();

    /* This pin is used as an GPIO for Wi-Fi examples it is switched to SD1_VSELECT
     * here so that SDCARD examples will work. */
    SETUP(IOMUXC_GPIO_AD_34_USDHC1_VSELECT, 0, AD_PULL_DOWN + AD_DRV_HI + AD_SLEW_SLOW);
}
void BOARD_InitLpuartPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void BOARD_InitLedPin(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void BOARD_I2C_ConfigurePins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void LPI2C1_InitPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();

    /* I2C-C */
    SETUP(IOMUXC_GPIO_AD_33_LPI2C1_SDA, 1, AD_ODE + AD_PULL_NONE + AD_DRV_NORM + AD_SLEW_SLOW); // In conflict with IOMUXC_GPIO_AD_33_ENET_MDIO
    SETUP(IOMUXC_GPIO_AD_32_LPI2C1_SCL, 1, AD_ODE + AD_PULL_NONE + AD_DRV_NORM + AD_SLEW_SLOW); // In conflict with IOMUXC_GPIO_AD_32_ENET_MDC
}
void LPI2C1_DeinitPins(void) {
    // Implemented for CMSIS examples but never called
}
void LPSPI1_InitPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void LPSPI1_DeinitPins(void) {
    // Implemented for CMSIS examples but never called
}
void LPUART1_InitPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void LPUART1_DeinitPins(void) {
    // Implemented for CMSIS examples but never called
}
void BOARD_InitArduinoUARTPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void BOARD_InitPinsM2(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void BOARD_InitM2UARTPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}
void BOARD_InitM2CodecPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();
}

void BOARD_InitEnetQOSPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();

    /* ENET QOS - replaces the ENET 1G functionality */
    SETUP(IOMUXC_GPIO_DISP_B1_00_ENET_QOS_RX_EN,     0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_01_ENET_QOS_RX_CLK,    0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_02_ENET_QOS_RX_DATA00, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_03_ENET_QOS_RX_DATA01, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_04_ENET_QOS_RX_DATA02, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_05_ENET_QOS_RX_DATA03, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_06_ENET_QOS_TX_DATA03, 0U, DISP_B1_PULL_NONE + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_07_ENET_QOS_TX_DATA02, 0U, DISP_B1_PULL_NONE + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_08_ENET_QOS_TX_DATA01, 0U, DISP_B1_PULL_NONE + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_09_ENET_QOS_TX_DATA00, 0U, DISP_B1_PULL_NONE + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_10_ENET_QOS_TX_EN,     0U, DISP_B1_PULL_NONE + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_11_ENET_QOS_TX_CLK,    0U, DISP_B1_PULL_NONE + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_EMC_B2_19_ENET_QOS_MDC,        0U, EMC_PULL_DOWN + EMC_DRV_HI);
    SETUP(IOMUXC_GPIO_EMC_B2_20_ENET_QOS_MDIO,       0U, EMC_PULL_DOWN + EMC_DRV_HI);
}

void BOARD_InitSEMCPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();

    /*
     * The SEMC pins are normally setup by either the DCD or by the debugger's
     * initialization scripts. This function MUST NEVER be called from code
     * running in SDRAM as it will corrupt the data.
     */

    SETUP(IOMUXC_GPIO_EMC_B1_00_SEMC_DATA00, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_01_SEMC_DATA01, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_02_SEMC_DATA02, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_03_SEMC_DATA03, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_04_SEMC_DATA04, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_05_SEMC_DATA05, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_06_SEMC_DATA06, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_07_SEMC_DATA07, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_08_SEMC_DM00,   0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_09_SEMC_ADDR00, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_10_SEMC_ADDR01, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_11_SEMC_ADDR02, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_12_SEMC_ADDR03, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_13_SEMC_ADDR04, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_14_SEMC_ADDR05, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_15_SEMC_ADDR06, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_16_SEMC_ADDR07, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_17_SEMC_ADDR08, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_18_SEMC_ADDR09, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_19_SEMC_ADDR11, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_20_SEMC_ADDR12, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_21_SEMC_BA0,    0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_22_SEMC_BA1,    0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_23_SEMC_ADDR10, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_24_SEMC_CAS,    0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_25_SEMC_RAS,    0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_26_SEMC_CLK,    0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_27_SEMC_CKE,    0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_28_SEMC_WE,     0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_29_SEMC_CS0,    0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_30_SEMC_DATA08, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_31_SEMC_DATA09, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_32_SEMC_DATA10, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_33_SEMC_DATA11, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_34_SEMC_DATA12, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_35_SEMC_DATA13, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_36_SEMC_DATA14, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_37_SEMC_DATA15, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_38_SEMC_DM01,   0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B1_39_SEMC_DQS,    1U, EMC_DRV_HI + EMC_PULL_DOWN);
    //SETUP(IOMUXC_GPIO_EMC_B1_40_SEMC_RDY,    0U, EMC_DRV_HI + EMC_PULL_DOWN); // Used as LPUART6_TXD
    //SETUP(IOMUXC_GPIO_EMC_B1_41_SEMC_CSX00,  0U, EMC_DRV_HI + EMC_PULL_DOWN); // Used as LPUART6_RXD
    SETUP(IOMUXC_GPIO_EMC_B2_00_SEMC_DATA16, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_01_SEMC_DATA17, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_02_SEMC_DATA18, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_03_SEMC_DATA19, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_04_SEMC_DATA20, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_05_SEMC_DATA21, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_06_SEMC_DATA22, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_07_SEMC_DATA23, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_08_SEMC_DM02,   0U, EMC_DRV_HI + EMC_PULL_UP);
    SETUP(IOMUXC_GPIO_EMC_B2_09_SEMC_DATA24, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_10_SEMC_DATA25, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_11_SEMC_DATA26, 0U, EMC_DRV_HI + EMC_PULL_UP);
    SETUP(IOMUXC_GPIO_EMC_B2_12_SEMC_DATA27, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_13_SEMC_DATA28, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_14_SEMC_DATA29, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_15_SEMC_DATA30, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_16_SEMC_DATA31, 0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_17_SEMC_DM03,   0U, EMC_DRV_HI + EMC_PULL_DOWN);
    SETUP(IOMUXC_GPIO_EMC_B2_18_SEMC_DQS4,   0U, EMC_DRV_HI + EMC_PULL_DOWN);
    //SETUP(IOMUXC_GPIO_EMC_B2_19_SEMC_CLKX00, 0U, EMC_DRV_HI + EMC_PULL_DOWN); // Used as MDC for ENET 1G or QOS
    //SETUP(IOMUXC_GPIO_EMC_B2_20_SEMC_CLKX01, 0U, EMC_DRV_HI + EMC_PULL_DOWN); // Used as MDIO for ENET 1G or QOS
}

void BOARD_InitParallelRGBPins(void) {
    BOARD_InitPins_uCOM_Carrier_Board();

    /*
     * The parallel RGB interface pins overlap with the interface to the
     * Ethernet-Phy on the iMX RT1176 uCOM board. The RGB interface can
     * only be used on iMX RT1176 uCOM board with a special mounting option
     * where the Ethernet-Phy is not mounted.
     */

    SETUP(IOMUXC_GPIO_DISP_B1_00_VIDEO_MUX_LCDIF_CLK,    0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_01_VIDEO_MUX_LCDIF_ENABLE, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_02_VIDEO_MUX_LCDIF_HSYNC,  0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_03_VIDEO_MUX_LCDIF_VSYNC,  0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);

    SETUP(IOMUXC_GPIO_DISP_B1_04_VIDEO_MUX_LCDIF_DATA00, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_05_VIDEO_MUX_LCDIF_DATA01, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_06_VIDEO_MUX_LCDIF_DATA02, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_07_VIDEO_MUX_LCDIF_DATA03, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_08_VIDEO_MUX_LCDIF_DATA04, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_09_VIDEO_MUX_LCDIF_DATA05, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_10_VIDEO_MUX_LCDIF_DATA06, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B1_11_VIDEO_MUX_LCDIF_DATA07, 0U, DISP_B1_PULL_DOWN + DISP_B1_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B2_00_VIDEO_MUX_LCDIF_DATA08, 0U, DISP_B2_PULL_DOWN + DISP_B2_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B2_01_VIDEO_MUX_LCDIF_DATA09, 0U, DISP_B2_PULL_DOWN + DISP_B2_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B2_02_VIDEO_MUX_LCDIF_DATA10, 0U, DISP_B2_PULL_DOWN + DISP_B2_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B2_03_VIDEO_MUX_LCDIF_DATA11, 0U, DISP_B2_PULL_DOWN + DISP_B2_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B2_04_VIDEO_MUX_LCDIF_DATA12, 0U, DISP_B2_PULL_DOWN + DISP_B2_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B2_05_VIDEO_MUX_LCDIF_DATA13, 0U, DISP_B2_PULL_DOWN + DISP_B2_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B2_06_VIDEO_MUX_LCDIF_DATA14, 0U, DISP_B2_PULL_DOWN + DISP_B2_DRV_HI);
    SETUP(IOMUXC_GPIO_DISP_B2_07_VIDEO_MUX_LCDIF_DATA15, 0U, DISP_B2_PULL_DOWN + DISP_B2_DRV_HI);
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
