/*****************************************************************************/
/**
 * @file 
 *   cmd.c
 * @brief 
 *   Debug command processor
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

#include "cmd.h"
#include "debug.h"
#include "qdc.h"

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

#define MAX_DATA_LENGTH         (10u)

#define RX_HEAD_1               (0xAFu)
#define RX_HEAD_2               (0x45u)
#define RX_TAIL_1               (0xE1u)
#define RX_TAIL_2               (0xE2u)

#define CMD_PING                (0x01u) 
#define CMD_PWR_ON              (0x02u)
#define CMD_PWR_OFF             (0x03u)
#define CMD_SIM_BTN             (0x04u)
#define CMD_GET_POS             (0x05u)

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

typedef union
{
    struct part{
        uint8_t cmd;
        uint8_t len; 
        char data[MAX_DATA_LENGTH]; 
    }part;
    uint8_t full[MAX_DATA_LENGTH+2u];
} rx_pack_t;

/*****************************************************************************/
/* Private (file scope only) variables                                       */
/*****************************************************************************/

TESTABLE_STATIC uint8_t g_state = 0;
TESTABLE_STATIC uint8_t g_data_index = 0;  
TESTABLE_STATIC rx_pack_t g_pack; 

TESTABLE_STATIC const char gp_ping_message[] = \
    "Got Message id 0x%02X, len %u, data(0x): %02X, %02X, %02X, %02X\r\n";
TESTABLE_STATIC const char gp_pwr_on_message[] = \
    "DBG turn on\r\n";
TESTABLE_STATIC const char gp_forced_off_message[] = \
    "DBG Forced turn off\r\n";
TESTABLE_STATIC const char gp_delayed_off_message[] = \
    "DBG Delayed turn off\r\n";
TESTABLE_STATIC const char gp_button_press_message[] = \
    "DBG button press\r\n";
TESTABLE_STATIC const char gp_position_message[] = \
    "Current position: %d\r\n";

TESTABLE_STATIC const char gp_on[] =            "ON";
TESTABLE_STATIC const char gp_forced_off[] =    "OFF_F";
TESTABLE_STATIC const char gp_delayed_off[] =   "OFF_D"; 
TESTABLE_STATIC const char gp_button[] =        "BTN"; 

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

static uint8_t checksum_u8 (
    const uint8_t* const p_buffer, 
    const uint16_t offset, 
    const uint16_t len);
static void process_rx_pack (const rx_pack_t* const pack);

/**
 * @brief
 *   Calculate checksum of buffer contents
 * @param[in]
 *   p_buffer Address of data buffer 
 * @param[in]
 *   offset Start position of data in buffer to be summed
 * @param[in]
 *   len Number of data bytes to be summed
 * @return 
 *   Calculated 8-bit checksum
 */
static uint8_t checksum_u8 (
    const uint8_t* const p_buffer, 
    const uint16_t offset, 
    const uint16_t len)
{
    uint8_t sum = 0;
    
    for (uint16_t idx = 0; idx < len; idx++)
    {
        sum += p_buffer[idx + offset];
    }
    
    return ~sum;
}

/**
 * @brief
 *   Process the received pack and the command contained therein
 * @param[in]
 *   p_pack Pointer to received pack structure
 */
static void process_rx_pack (const rx_pack_t* const p_pack)
{
    switch (p_pack->part.cmd)
    {
        case CMD_PING:
            DEBUG_printf(
                gp_ping_message, 
                p_pack->part.cmd, 
                p_pack->part.len, 
                p_pack->part.data[0], 
                p_pack->part.data[1], 
                p_pack->part.data[2], 
                p_pack->part.data[3]);
            break; 
 
        case CMD_PWR_ON:
            if (strlen(gp_on) == p_pack->part.len)
            {
                if (!strcmp(p_pack->part.data, gp_on))
                {
                    DEBUG_printf(gp_pwr_on_message);
                }
            }
            break; 
            
        case CMD_PWR_OFF:
            if (strlen(gp_forced_off) == p_pack->part.len)
            {
                if (!strcmp(p_pack->part.data, gp_forced_off))
                {
                    DEBUG_printf(gp_forced_off_message);
                    //turn_off_device();
                }
            }
            if (strlen(gp_delayed_off) == p_pack->part.len)
            {
                if (!strcmp(p_pack->part.data, gp_delayed_off))
                {
                    DEBUG_printf(gp_delayed_off_message);
                    //delayed_turn_off(); 
                }
            }
            break;
            
        case CMD_SIM_BTN:
            if ((strlen(gp_button) + sizeof(uint16_t)) == p_pack->part.len)
            {
                if (!strncmp(p_pack->part.data, gp_button, strlen(gp_button)))
                {
                    DEBUG_printf(gp_button_press_message);
                    //uint16_t temp_u16 = ((uint16_t)p_pack->part.data[3]<<8) | (uint16_t)p_pack->part.data[4];
                    //sim_button_press(temp_u16); 
                }
            }
            break; 
            
        case CMD_GET_POS:
            DEBUG_printf(
                gp_position_message, 
                QDC_GetPositionValue());
            break; 
 
            break;
        
        default:
            break; 
    }
}

/*****************************************************************************/
/* External interface functions                                              */
/*****************************************************************************/

/**
 * @brief
 *   Handler for received command pack 
 * @param
 *   data Received data byte to be processed 
 * @return 
 *   true if received data consumed as part of a command pack, otherwise false
 */
bool CMD_data_handler(const uint8_t data)
{
    bool b_error = true;
    
    uint8_t checksum;
    
    switch (g_state)
    {
        case 0: 
            if (RX_HEAD_1 == data)
            {
                g_state++;
            }
            b_error = false;
            break;
                
        case 1:
            if (RX_HEAD_2 == data)
            {
                g_state++;  
                b_error = false;
            }
            break; 
        
        case 2:
            if ((data >= CMD_PING) && (data <= CMD_GET_POS))
            {
                g_pack.part.cmd = data;
                g_state++;
                b_error = false;
            }
            break;

        case 3:
            if (data <= MAX_DATA_LENGTH)
            {
                g_pack.part.len = data; 
                g_state++;
                g_data_index = 0; 
                b_error = false;
            }
            break; 
                
         case 4:
            if (g_data_index == g_pack.part.len)
            {
                if (RX_TAIL_1 == data)
                {
                    g_state++; 
                    b_error = false;
                }
            }
            else
            {
                g_pack.part.data[g_data_index] = data; 
                g_data_index++; 
                b_error = false;
            }
            break; 
                
        case 5:
            if (RX_TAIL_2 == data)
            {
                g_state++;  
                b_error = false;
            }
            break; 
                
        case 6:
            checksum = checksum_u8(g_pack.full, 0, g_pack.part.len + 2u);
          
            if (checksum == data)
            {
                process_rx_pack(&g_pack); 
                    
                g_state++;
                b_error = false;
            }
            break; 
 
        default:
            break;
    }   

    if (g_state > 0)
    {
        if (b_error)
        {
            DEBUG_printf("DBG command RX parse error at state %u\r\n", g_state);
            if (6 == g_state)
            {
                DEBUG_printf("Checksum received: %u, expected %u\r\n", data, checksum); 
            }
            g_state = 0;
        }

        if (7 == g_state)
        {
            g_state = 0;
        }
        
        return true;
    }
    
    return false;
}

/*** end of file ***/
