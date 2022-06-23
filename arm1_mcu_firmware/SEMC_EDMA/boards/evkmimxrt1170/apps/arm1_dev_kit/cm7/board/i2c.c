/*****************************************************************************/
/**
 * @file 
 *   i2c.c
 * @brief 
 *   I2C bus API layer
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

#include "i2c.h"
#include "fsl_lpi2c.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

typedef struct {
  LPI2C_Type *p_base;
  clock_root_t clock_root;
  clock_root_config_t clock_root_config;
} i2c_config_t;

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

bool gb_i2c_initialised = false;

const i2c_config_t g_config[] = 
{
    {
        /* LPI2C1 clock frequency = 24MHz / 12 = 2MHz */
        .p_base = LPI2C1,
        .clock_root = kCLOCK_Root_Lpi2c1,
        .clock_root_config.clockOff = false,
        .clock_root_config.mux = kCLOCK_M7_ClockRoot_MuxOsc24MOut,
        .clock_root_config.div = 12u  
    },
    {
        /* LPI2C2 clock frequency = 24MHz / 12 = 2MHz */
        .p_base = LPI2C2,
        .clock_root = kCLOCK_Root_Lpi2c2,
        .clock_root_config.clockOff = false,
        .clock_root_config.mux = kCLOCK_M7_ClockRoot_MuxOsc24MOut,
        .clock_root_config.div = 12u  
    },
    {
        /* LPI2C3 clock frequency = 24MHz / 12 = 2MHz */
        .p_base = LPI2C3,
        .clock_root = kCLOCK_Root_Lpi2c3,
        .clock_root_config.clockOff = false,
        .clock_root_config.mux = kCLOCK_M7_ClockRoot_MuxOsc24MOut,
        .clock_root_config.div = 12u  
    },
    {
        /* LPI2C4 clock frequency = 24MHz / 12 = 2MHz */
        .p_base = LPI2C4,
        .clock_root = kCLOCK_Root_Lpi2c4,
        .clock_root_config.clockOff = false,
        .clock_root_config.mux = kCLOCK_M7_ClockRoot_MuxOsc24MOut,
        .clock_root_config.div = 12u  
    },
    {
        /* LPI2C5 clock frequency = 24MHz / 12 = 2MHz */
        .p_base = LPI2C5,
        .clock_root = kCLOCK_Root_Lpi2c5,
        .clock_root_config.clockOff = false,
        .clock_root_config.mux = kCLOCK_M7_ClockRoot_MuxOsc24MOut,
        .clock_root_config.div = 12u  
    },
    {
        /* LPI2C6 clock frequency = 24MHz / 12 = 2MHz */
        .p_base = LPI2C6,
        .clock_root = kCLOCK_Root_Lpi2c6,
        .clock_root_config.clockOff = false,
        .clock_root_config.mux = kCLOCK_M7_ClockRoot_MuxOsc24MOut,
        .clock_root_config.div = 12u  
    }
};

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

/**
 * @brief
 *   Initialise the specified I2C bus
 * @param[in]
 *   bus I2C bus index
 */
static void master_init(i2c_bus_t bus)
{
    clock_root_t root = g_config[bus].clock_root;
    
    lpi2c_master_config_t config = {0};

    /*
     * config.debugEnable = false;
     * config.ignoreAck = false;
     * config.pinConfig = kLPI2C_2PinOpenDrain;
     * config.baudRate_Hz = 100000U;
     * config.busIdleTimeout_ns = 0;
     * config.pinLowTimeout_ns = 0;
     * config.sdaGlitchFilterWidth_ns = 0;
     * config.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&config);
        
    CLOCK_SetRootClock(root, &g_config[bus].clock_root_config);
    
    LPI2C_MasterInit(
        g_config[bus].p_base, &config, CLOCK_GetRootClockFreq(root));
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Initialise the I2C buses
 */
void I2C_initialise(void)
{
    if (false == gb_i2c_initialised)
    {
        master_init(I2C1);
        master_init(I2C2);
        master_init(I2C3);
        master_init(I2C4);
        master_init(I2C5);
        master_init(I2C6);
        gb_i2c_initialised = true;
    }
}

/**
 * @brief
 *   Send data on I2C bus 1
 * @param
 *   addr Device address
 * @param
 *   sub_addr Sub address
 * @param
 *   sub_addr_size Number of bytes in sub address
 * @param[in]
 *   p_data Pointer to data to be written
 * @param
 *   size Number of bytes to be written
 * @return
 *   Status
 */
status_t I2C1_send(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    const uint8_t *p_data, 
    uint8_t size)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = addr;
    xfer.direction      = kLPI2C_Write;
    xfer.subaddress     = sub_addr;
    xfer.subaddressSize = sub_addr_size;
    xfer.data           = (uint8_t*)p_data;
    xfer.dataSize       = size;

    return LPI2C_MasterTransferBlocking(LPI2C1, &xfer);
}


/**
 * @brief
 *   Receive data on I2C bus 1
 * @param
 *   addr Device address
 * @param
 *   sub_addr Sub address
 * @param
 *   sub_addr_size Number of bytes in sub address
 * @param[out]
 *   p_data Address of buffer where data should be returned
 * @param
 *   size Number of bytes to be read
 * @return
 *   Status
 */
status_t I2C1_receive(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = addr;
    xfer.direction      = kLPI2C_Read;
    xfer.subaddress     = sub_addr;
    xfer.subaddressSize = sub_addr_size;
    xfer.data           = p_data;
    xfer.dataSize       = size;

    return LPI2C_MasterTransferBlocking(LPI2C1, &xfer);
}

/**
 * @brief
 *   Send data on I2C bus 2
 * @param
 *   addr Device address
 * @param
 *   sub_addr Sub address
 * @param
 *   sub_addr_size Number of bytes in sub address
 * @param[in]
 *   p_data Pointer to data to be written
 * @param
 *   size Number of bytes to be written
 * @return
 *   Status
 */
status_t I2C2_send(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    const uint8_t *p_data, 
    uint8_t size)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = addr;
    xfer.direction      = kLPI2C_Write;
    xfer.subaddress     = sub_addr;
    xfer.subaddressSize = sub_addr_size;
    xfer.data           = (uint8_t*)p_data;
    xfer.dataSize       = size;

    return LPI2C_MasterTransferBlocking(LPI2C2, &xfer);
}


/**
 * @brief
 *   Receive data on I2C bus 2
 * @param
 *   addr Device address
 * @param
 *   sub_addr Sub address
 * @param
 *   sub_addr_size Number of bytes in sub address
 * @param[out]
 *   p_data Address of buffer where data should be returned
 * @param
 *   size Number of bytes to be read
 * @return
 *   Status
 */
status_t I2C2_receive(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = addr;
    xfer.direction      = kLPI2C_Read;
    xfer.subaddress     = sub_addr;
    xfer.subaddressSize = sub_addr_size;
    xfer.data           = p_data;
    xfer.dataSize       = size;

    return LPI2C_MasterTransferBlocking(LPI2C2, &xfer);
}

/**
 * @brief
 *   Send data on I2C bus 3
 * @param
 *   addr Device address
 * @param
 *   sub_addr Sub address
 * @param
 *   sub_addr_size Number of bytes in sub address
 * @param[in]
 *   p_data Pointer to data to be written
 * @param
 *   size Number of bytes to be written
 * @return
 *   Status
 */
status_t I2C3_send(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    const uint8_t *p_data, 
    uint8_t size)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = addr;
    xfer.direction      = kLPI2C_Write;
    xfer.subaddress     = sub_addr;
    xfer.subaddressSize = sub_addr_size;
    xfer.data           = (uint8_t*)p_data;
    xfer.dataSize       = size;

    return LPI2C_MasterTransferBlocking(LPI2C3, &xfer);
}


/**
 * @brief
 *   Receive data on I2C bus 3
 * @param
 *   addr Device address
 * @param
 *   sub_addr Sub address
 * @param
 *   sub_addr_size Number of bytes in sub address
 * @param[out]
 *   p_data Address of buffer where data should be returned
 * @param
 *   size Number of bytes to be read
 * @return
 *   Status
 */
status_t I2C3_receive(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = addr;
    xfer.direction      = kLPI2C_Read;
    xfer.subaddress     = sub_addr;
    xfer.subaddressSize = sub_addr_size;
    xfer.data           = p_data;
    xfer.dataSize       = size;

    return LPI2C_MasterTransferBlocking(LPI2C3, &xfer);
}

/**
 * @brief
 *   Send data on I2C bus 4
 * @param
 *   addr Device address
 * @param
 *   sub_addr Sub address
 * @param
 *   sub_addr_size Number of bytes in sub address
 * @param[in]
 *   p_data Pointer to data to be written
 * @param
 *   size Number of bytes to be written
 * @return
 *   Status
 */
status_t I2C4_send(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    const uint8_t *p_data, 
    uint8_t size)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = addr;
    xfer.direction      = kLPI2C_Write;
    xfer.subaddress     = sub_addr;
    xfer.subaddressSize = sub_addr_size;
    xfer.data           = (uint8_t*)p_data;
    xfer.dataSize       = size;

    return LPI2C_MasterTransferBlocking(LPI2C4, &xfer);
}


/**
 * @brief
 *   Receive data on I2C bus 4
 * @param
 *   addr Device address
 * @param
 *   sub_addr Sub address
 * @param
 *   sub_addr_size Number of bytes in sub address
 * @param[out]
 *   p_data Address of buffer where data should be returned
 * @param
 *   size Number of bytes to be read
 * @return
 *   Status
 */
status_t I2C4_receive(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = addr;
    xfer.direction      = kLPI2C_Read;
    xfer.subaddress     = sub_addr;
    xfer.subaddressSize = sub_addr_size;
    xfer.data           = p_data;
    xfer.dataSize       = size;

    return LPI2C_MasterTransferBlocking(LPI2C4, &xfer);
}

/**
 * @brief
 *   Send data on I2C bus 5
 * @param
 *   addr Device address
 * @param
 *   sub_addr Sub address
 * @param
 *   sub_addr_size Number of bytes in sub address
 * @param[in]
 *   p_data Pointer to data to be written
 * @param
 *   size Number of bytes to be written
 * @return
 *   Status
 */
status_t I2C5_send(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    const uint8_t *p_data, 
    uint8_t size)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = addr;
    xfer.direction      = kLPI2C_Write;
    xfer.subaddress     = sub_addr;
    xfer.subaddressSize = sub_addr_size;
    xfer.data           = (uint8_t*)p_data;
    xfer.dataSize       = size;

    return LPI2C_MasterTransferBlocking(LPI2C5, &xfer);
}


/**
 * @brief
 *   Receive data on I2C bus 5
 * @param
 *   addr Device address
 * @param
 *   sub_addr Sub address
 * @param
 *   sub_addr_size Number of bytes in sub address
 * @param[out]
 *   p_data Address of buffer where data should be returned
 * @param
 *   size Number of bytes to be read
 * @return
 *   Status
 */
status_t I2C5_receive(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = addr;
    xfer.direction      = kLPI2C_Read;
    xfer.subaddress     = sub_addr;
    xfer.subaddressSize = sub_addr_size;
    xfer.data           = p_data;
    xfer.dataSize       = size;

    return LPI2C_MasterTransferBlocking(LPI2C5, &xfer);
}

/**
 * @brief
 *   Send data on I2C bus 6
 * @param
 *   addr Device address
 * @param
 *   sub_addr Sub address
 * @param
 *   sub_addr_size Number of bytes in sub address
 * @param[in]
 *   p_data Pointer to data to be written
 * @param
 *   size Number of bytes to be written
 * @return
 *   Status
 */
status_t I2C6_send(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    const uint8_t *p_data, 
    uint8_t size)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = addr;
    xfer.direction      = kLPI2C_Write;
    xfer.subaddress     = sub_addr;
    xfer.subaddressSize = sub_addr_size;
    xfer.data           = (uint8_t*)p_data;
    xfer.dataSize       = size;

    return LPI2C_MasterTransferBlocking(LPI2C6, &xfer);
}

/**
 * @brief
 *   Receive data on I2C bus 6
 * @param
 *   addr Device address
 * @param
 *   sub_addr Sub address
 * @param
 *   sub_addr_size Number of bytes in sub address
 * @param[out]
 *   p_data Address of buffer where data should be returned
 * @param
 *   size Number of bytes to be read
 * @return
 *   Status
 */
status_t I2C6_receive(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = addr;
    xfer.direction      = kLPI2C_Read;
    xfer.subaddress     = sub_addr;
    xfer.subaddressSize = sub_addr_size;
    xfer.data           = p_data;
    xfer.dataSize       = size;

    return LPI2C_MasterTransferBlocking(LPI2C6, &xfer);
}

/**
 * @brief
 *   Receive data on I2C bus 6 using SCCB
 * @param
 *   addr Device address
 * @param
 *   sub_addr Sub address
 * @param
 *   sub_addr_size Number of bytes in sub address
 * @param[out]
 *   p_data Address of buffer where data should be returned
 * @param
 *   size Number of bytes to be read
 * @return
 *   Status
 */
status_t I2C6_receive_sccb(
    uint8_t addr, 
    uint32_t sub_addr, 
    uint8_t sub_addr_size, 
    uint8_t *p_data, 
    uint8_t size)
{
    status_t status;
    lpi2c_master_transfer_t xfer;

    xfer.flags          = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress   = addr;
    xfer.direction      = kLPI2C_Write;
    xfer.subaddress     = sub_addr;
    xfer.subaddressSize = sub_addr_size;
    xfer.data           = NULL;
    xfer.dataSize       = 0;

    status = LPI2C_MasterTransferBlocking(LPI2C6, &xfer);

    if (kStatus_Success == status)
    {
        xfer.subaddressSize = 0;
        xfer.direction      = kLPI2C_Read;
        xfer.data           = p_data;
        xfer.dataSize       = size;

        status = LPI2C_MasterTransferBlocking(LPI2C6, &xfer);
    }

    return status;
}


/*** end of file ***/
