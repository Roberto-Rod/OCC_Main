/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_dpot_ad5247.c

  @Summary
    AD5667R DPOT chip driver

  @Description
    This AD5667 driver translates non-blocking API function calls to I2C
    commands that are queued and sent to the AD5667 DPOT chip.
 */
/* ************************************************************************** */

/*******************************************************************************
                            Includes Files
*******************************************************************************/

#include "drv_dpot_ad5247.h"

/*******************************************************************************
                            Definitions
*******************************************************************************/

//#define DEBUG_DPOT
//#define USE_HARMONY_DRIVER

/* Following macro specifies the wiper resistance when code 0x00 is input.
   This should be kept by practical observation when appropriate. This value is 
   expected Rwb as specified by data sheet approximated for 5V operation */
#define DRV_DPOT_I2C_INDEX              0
#define DRV_DPOT_1_I2C_SLAVE_ADDRESS    0x2E       // AD5246BKSZ10-2RL7
#define DRV_DPOT_2_I2C_SLAVE_ADDRESS   	0x2F       // MCP4017-E/LT 

#define DRV_DPOT_COUNT                  2U
#define DRV_DPOT_CHANNELS               1U

#define DRV_DPOT_1_RW                   50U
#define DRV_DPOT_1_RAB                  10000U
#define DRV_DPOT_1_R2                   10000U
#define	DRV_DPOT_1_POS                  127U

#define DRV_DPOT_1_RES_DEF              63U

#define DRV_DPOT_2_RW                   50U
#define DRV_DPOT_2_RAB                  100000U
#define DRV_DPOT_2_R2                   100000U
#define	DRV_DPOT_2_POS                  127U

#define TIMEOUT_DELAY_MS                1000

typedef enum
{
    DRV_DPOT_STATE_INIT = 0U,
    DRV_DPOT_STATE_IDLE,
    DRV_DPOT_STATE_WAIT,            
 
    DRV_DPOT_STATE_ERROR
} DRV_DPOT_STATE;

typedef enum
{
    DRV_DPOT_ERROR_NONE,    
    DRV_DPOT_ERROR_I2C,
    DRV_DPOT_ERROR_I2C_WRITE,
    DRV_DPOT_ERROR_I2C_READ,
    DRV_DPOT_ERROR_I2C_INVALID_STATE,
    DRV_DPOT_ERROR_I2C_INVALID_HANDLE,
} DRV_DPOT_ERROR;

typedef enum
{
    DRV_DPOT_CMD_1_SET_RES        = 0x01,     
    DRV_DPOT_CMD_2_SET_RES        = 0x02,
    DRV_DPOT_CMD_1_GET_RES        = 0x04,
    DRV_DPOT_CMD_2_GET_RES        = 0x08
} DRV_DPOT_COMMAND;

typedef struct
{
    DRV_DPOT_STATE state;
    DRV_DPOT_STATE previous_state;
    DRV_HANDLE i2c_drv_handle;
    DRV_I2C_TRANSFER_HANDLE i2c_transfer_handle;
    DRV_DPOT_ERROR error;

    uint8_t resistance[DRV_DPOT_COUNT * DRV_DPOT_CHANNELS];
    uint8_t resistance_read[DRV_DPOT_COUNT * DRV_DPOT_CHANNELS];
    
    uint8_t command_mask;                   /* "queue" of up to 6 commands */
    uint8_t last_command;
    
} DRV_DPOT_OBJ;

/*******************************************************************************
                             Global Variables
*******************************************************************************/

static DRV_DPOT_OBJ drv_dpot = 
{
    .state = DRV_DPOT_STATE_INIT,
    .previous_state = DRV_DPOT_STATE_INIT,
    
    .resistance[0] = DRV_DPOT1_DEFAULT,
    .resistance[1] = DRV_DPOT2_DEFAULT,
    
    
    .command_mask = 0,                      /* no commands queued */
    .last_command = 0,                      /* no last command */
};


static void drv_dpot_push(DRV_DPOT_COMMAND command)
{
    drv_dpot.command_mask |= command;
}

/* ************************************************************************** */
/* Function: drv_dpot_ad5247_i2c_callback                                     */
/* This function is called on the completion of every I2C read or write       */
/* operation, and moves the state machine on to the next operation.           */
/* ************************************************************************** */
void drv_dpot_ad5247_i2c_callback(DRV_I2C_TRANSFER_EVENT event, DRV_I2C_TRANSFER_HANDLE transferHandle, uintptr_t context)
{
    (void) context;

    if (transferHandle != drv_dpot.i2c_transfer_handle)
    {
        // invalid handle, throw error
        drv_dpot.state = DRV_DPOT_STATE_ERROR;
        drv_dpot.error = DRV_DPOT_ERROR_I2C_INVALID_HANDLE;
        return;
    }

    switch (event)
    {
        case DRV_I2C_TRANSFER_EVENT_COMPLETE:
        {
            #ifdef DEBUG_DPOT
            dputs_colour("[GREEN]drv_dpot_ad5247_i2c_callback() DRV_I2C_TRANSFER_EVENT_COMPLETE[WHITE]\r\n");
            #endif

            switch (drv_dpot.previous_state)
            {
                case DRV_DPOT_STATE_IDLE:
                {
                    drv_dpot.state = drv_dpot.previous_state;

                    if (DRV_DPOT_CMD_1_GET_RES == drv_dpot.last_command)
                    {
                        #ifdef DEBUG_DPOT
                        dprintf_colour("[MAGENTA]Got POT value %d for Pot 1[WHITE]\r\n", drv_dpot.resistance_read[DRV_DPOT_1]);
                        #endif
                        drv_dpot.last_command = 0;
                    }

                    if (DRV_DPOT_CMD_2_GET_RES == drv_dpot.last_command)
                    {
                        #ifdef DEBUG_DPOT
                        dprintf_colour("[MAGENTA]Got POT value %d for Pot 2[WHITE]\r\n", drv_dpot.resistance_read[DRV_DPOT_2]);
                        #endif
                        drv_dpot.last_command = 0;
                    }

                    break;
                }

                default:
                {
                    #ifdef DEBUG_DPOT
                    dputs_colour("[RED]What's going on?[WHITE]\r\n");
                    #endif
                    // invalid condition, throw error
                    drv_dpot.state = DRV_DPOT_STATE_ERROR;
                    drv_dpot.error = DRV_DPOT_ERROR_I2C_INVALID_STATE;
                    break;
                }
            }
            break;
        }

        case DRV_I2C_TRANSFER_EVENT_ERROR:
        {
            #ifdef DEBUG_DPOT
            dputs_colour("[RED]drv_dpot_ad5247_i2c_callback() DRV_I2C_TRANSFER_EVENT_ERROR[WHITE]\r\n");
            #endif
            drv_dpot.state = DRV_DPOT_STATE_ERROR;
            drv_dpot.error = DRV_DPOT_ERROR_I2C_WRITE;
            break;
        }

        default:
            break;
    }
}
/* End of function drv_dpot_ad5247_i2c_callback                               */

/* ************************************************************************** */
/* Function: drv_dpot_ad5247_controller_task                                  */
/* Called in the main task idle loop to send register updates to the LED      */
/* driver chip                                                                */
/* ************************************************************************** */
bool drv_dpot_ad5247_controller_task(void)
{
    switch (drv_dpot.state)
    {
        case DRV_DPOT_STATE_INIT:
        {
            /* open the I2C driver */
            

            drv_dpot.state = DRV_DPOT_STATE_IDLE;
            break;
        }

        /* waiting for a new command to be issued (via an incoming API function call) */
        case DRV_DPOT_STATE_IDLE:
        {
            /* no command is queued - nothing to do */
            if (0 == drv_dpot.command_mask)
            {
                break;
            }
            
            /* process the next command in the queue */

            /* write pot 1 */
            if ((drv_dpot.command_mask & DRV_DPOT_CMD_1_SET_RES) > 0)
            {
                /* update the resistance register */
                drv_dpot.command_mask &= ~DRV_DPOT_CMD_1_SET_RES;
                #ifdef DEBUG_DPOT
                dprintf_colour("[YELLOW]DRV_I2C_WriteTransferAdd(): setting POT value %d for Pot 1[WHITE]\r\n", drv_dpot.resistance[DRV_DPOT_1]);
                #endif
                
                DRV_I2C4_Write_Single_Byte(DRV_DPOT_1_I2C_SLAVE_ADDRESS, drv_dpot.resistance[DRV_DPOT_1]);
                break;
            }

            /* write pot 2 */
            if ((drv_dpot.command_mask & DRV_DPOT_CMD_2_SET_RES) > 0)
            {
                /* update the resistance register */
                drv_dpot.command_mask &= ~DRV_DPOT_CMD_2_SET_RES;
                #ifdef DEBUG_DPOT
                dprintf_colour("[YELLOW]DRV_I2C_WriteTransferAdd(): setting POT value %d for Pot 2[WHITE]\r\n", drv_dpot.resistance[DRV_DPOT_2]);
                #endif
                
                DRV_I2C4_Write_Single_Byte(DRV_DPOT_2_I2C_SLAVE_ADDRESS, drv_dpot.resistance[DRV_DPOT_2]);
                
                break;
            }

            /* read pot 1 */
            if ((drv_dpot.command_mask & DRV_DPOT_CMD_1_GET_RES) > 0)
            {
                /* update the resistance register */
                drv_dpot.command_mask &= ~DRV_DPOT_CMD_1_GET_RES;
                drv_dpot.last_command = DRV_DPOT_CMD_1_GET_RES;
                #ifdef DEBUG_DPOT
                dputs_colour("[YELLOW]DRV_I2C_ReadTransferAdd(): getting POT value for Pot 1[WHITE]\r\n");
                #endif
                
                DRV_I2C4_Read_Single_Byte(DRV_DPOT_1_I2C_SLAVE_ADDRESS, &drv_dpot.resistance_read[DRV_DPOT_1]);
                #ifdef DEBUG_DPOT
                dprintf_colour("[MAGENTA]Got POT value %d for Pot 1[WHITE]\r\n", drv_dpot.resistance_read[DRV_DPOT_1]);
                #endif
                
                break;
            }

            /* read pot 2 */
            if ((drv_dpot.command_mask & DRV_DPOT_CMD_2_GET_RES) > 0)
            {
                /* update the resistance register */
                drv_dpot.command_mask &= ~DRV_DPOT_CMD_2_GET_RES;
                drv_dpot.last_command = DRV_DPOT_CMD_2_GET_RES;
                #ifdef DEBUG_DPOT
                dputs_colour("[YELLOW]DRV_I2C_ReadTransferAdd(): getting POT value for Pot 2[WHITE]\r\n");
                #endif
                
                DRV_I2C4_Read_Single_Byte(DRV_DPOT_2_I2C_SLAVE_ADDRESS, &drv_dpot.resistance_read[DRV_DPOT_2]);
                #ifdef DEBUG_DPOT
                dprintf_colour("[MAGENTA]Got POT value %d for Pot 2[WHITE]\r\n", drv_dpot.resistance_read[DRV_DPOT_2]);
                #endif
                
                break;
            }
        }

        case DRV_DPOT_STATE_WAIT:
        {
            // do nothing, wait for callback
            break;
        }

        case DRV_DPOT_STATE_ERROR:
        default:
            drv_dpot.state = DRV_DPOT_STATE_IDLE;
            break;
    }

    return ((DRV_DPOT_STATE_IDLE != drv_dpot.state) || (0 != drv_dpot.command_mask));
}
/* End of function drv_dpot_ad5247_controller_task                            */

/*******************************************************************************
                            External Functions
*******************************************************************************/

/* set the resistance value  */
void drv_dpot_set_resistance(DRV_DPOT_INDEX dpot, uint8_t value)
{
    #ifdef DEBUG_DPOT
    dprintf_colour("[YELLOW]drv_dpot_set_resistance() pot %d, value %d[WHITE]\r\n", dpot + 1, value);
    #endif

    if (DRV_DPOT_1 == dpot)
    {
        if (value > DRV_DPOT_1_POS)
        {
            value = DRV_DPOT_1_POS;
        }

        drv_dpot.resistance[dpot] = value;
        drv_dpot_push(DRV_DPOT_CMD_1_SET_RES);
        return;
    }
    else if (DRV_DPOT_2 == dpot)
    {
        if (value > DRV_DPOT_2_POS)
        {
            value = DRV_DPOT_2_POS;
        }        

        drv_dpot.resistance[dpot] = value;
        drv_dpot_push(DRV_DPOT_CMD_2_SET_RES);
        return;
    }
}

/* Read the resistance value  */
void drv_dpot_read_resistance(DRV_DPOT_INDEX dpot)
{
    if (DRV_DPOT_1 == dpot)
    {
        drv_dpot_push(DRV_DPOT_CMD_1_GET_RES);
    }
    else if (DRV_DPOT_2 == dpot)
    {
        drv_dpot_push(DRV_DPOT_CMD_2_GET_RES);
    }
}

/* Return the resistance value  */
uint8_t drv_dpot_get_resistance(DRV_DPOT_INDEX dpot)
{
    return  drv_dpot.resistance[dpot];
}
    
/* Check if the driver is busy  */
bool drv_dpot_busy(void)
{
    if( drv_dpot.command_mask == 0U )
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* Check if the driver is idling = command has finished sending */
bool drv_dpot_idling(void)
{
    if(drv_dpot.state == DRV_DPOT_STATE_IDLE && drv_dpot.command_mask == 0U)
    {
        return true;
    }
    return false;
}

bool drv_dpot_set_resistance_realtime(DRV_DPOT_INDEX dpot, uint8_t value) 
{
    bool success = false;
    
    if( dpot == DRV_DPOT_1)
    {       
        if( DRV_I2C4_WRITE_COMPLETE == DRV_I2C4_Write_Single_Byte(DRV_DPOT_1_I2C_SLAVE_ADDRESS, value))
        {
            success = true;
            drv_dpot.resistance[DRV_DPOT_1] = value; 
        }
    }
    else if( dpot == DRV_DPOT_2)
    {
        if( DRV_I2C4_WRITE_COMPLETE == DRV_I2C4_Write_Single_Byte(DRV_DPOT_2_I2C_SLAVE_ADDRESS, value))
        {
            success = true;
            drv_dpot.resistance[DRV_DPOT_2] = value; 
        }
    }
    
    return success;
}
/** drv_dpot_ad5247.c *********************************************************/  
/********************************  EOF  ***************************************/
/******************************************************************************/
