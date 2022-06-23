/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_dac_ad5667r.c

  @Summary
    AD5667R DAC chip driver

  @Description
    This AD5667 driver translates non-blocking API function calls to I2C
    commands that are queued and sent to the AD5667 DAC chip.
 */
/* ************************************************************************** */

/*******************************************************************************
                            Includes Files
*******************************************************************************/

#include "drv_dac_ad5667r.h"

/*******************************************************************************
                             Definitions
*******************************************************************************/

//#define DEBUG_DAC

//#define USE_HARMONY_DRIVER

#define DRV_DAC_I2C_INDEX               1
#define DRV_DAC_I2C_SLAVE_ADDRESS       0x0F

#define DRV_DAC_REG                     0x18           
#define DRV_PMODE_REG                   0x20
#define DRV_RESET_REG                   0x28
#define DRV_LDAC_REG                    0x30
#define DRV_REF_REG                     0x38

#define TIMEOUT_DELAY_MS                1000

typedef enum
{
    DRV_DAC_STATE_INIT = 0U,
    DRV_DAC_STATE_IDLE,
    DRV_DAC_STATE_WAIT,            
 
    DRV_DAC_STATE_ERROR
} DRV_DAC_STATE;

typedef enum
{
    DRV_DAC_CMD_SET_DAC1        = 0x01,     
    DRV_DAC_CMD_SET_DAC2        = 0x02,
    DRV_DAC_CMD_SET_DACS        = 0x04,
    DRV_DAC_CMD_SET_PMODE       = 0x08,
    DRV_DAC_CMD_SET_LDAC        = 0x10,
    DRV_DAC_CMD_SET_REF         = 0x20,
    DRV_DAC_CMD_RESET           = 0x80
} DRV_DAC_COMMAND;

typedef struct
{
    DRV_DAC_STATE state;
    DRV_DAC_STATE previous_state;
    DRV_HANDLE i2c_drv_handle;
    DRV_I2C_TRANSFER_HANDLE i2c_transfer_handle;
    DRV_DAC_ERROR error;

    uint8_t cmd_buffer[3];

    uint16_t dac[2];
    uint8_t pmode;
    uint8_t intref;
    uint8_t ldac;
    
    uint8_t command_mask;                   /* "queue" of up to 6 commands */
} DRV_DAC_OBJ;

/*******************************************************************************
                             Global Variables
*******************************************************************************/

static DRV_DAC_OBJ drv_dac = 
{
    .state = DRV_DAC_STATE_INIT,
    .previous_state = DRV_DAC_STATE_INIT,
    .error = DRV_DAC_ERROR_UNINITIALISED,
    .dac = { DRV_DAC1_DEFAULT, DRV_DAC2_DEFAULT },
    .pmode =  DRV_DAC_PDM_NORMAL,
    .ldac  = DRV_DAC_LDAC_DISABLED,
    .intref = DRV_DAC_INTERNAL_REF_ON,

    .command_mask = 0U,                      /* no commands queued */
};

/*******************************************************************************
                             Local Functions
*******************************************************************************/

static void drv_dac_push(uint8_t command)
{
    drv_dac.command_mask |= command;
}

/* ************************************************************************** */
/* Function: drv_dac_ad5667r_i2c_callback                                     */
/* This function is called on the completion of every I2C read or write       */
/* operation, and moves the state machine on to the next operation.           */
/* ************************************************************************** */
void drv_dac_ad5667r_i2c_callback(DRV_I2C_TRANSFER_EVENT event, DRV_I2C_TRANSFER_HANDLE transferHandle, uintptr_t context)
{
    (void) context;

    if (transferHandle != drv_dac.i2c_transfer_handle)
    {
        // invalid handle, throw error
        drv_dac.state = DRV_DAC_STATE_ERROR;
        drv_dac.error = DRV_DAC_ERROR_I2C_INVALID_HANDLE;
        return;
    }

    switch (event)
    {
        case DRV_I2C_TRANSFER_EVENT_COMPLETE:
        {
            #ifdef DEBUG_DAC
            dputs_colour("[GREEN]drv_dac_ad5667r_i2c_callback() DRV_I2C_TRANSFER_EVENT_COMPLETE[WHITE]\r\n");
            #endif

            switch (drv_dac.previous_state)
            {
                case DRV_DAC_STATE_IDLE:
                {
                    drv_dac.state = drv_dac.previous_state;
                    break;
                }

                default:
                {
                    // invalid condition, throw error
                    drv_dac.state = DRV_DAC_STATE_ERROR;
                    drv_dac.error = DRV_DAC_ERROR_I2C_INVALID_STATE;
                    break;
                }
            }
            break;
        }

        case DRV_I2C_TRANSFER_EVENT_ERROR:
        {
            #ifdef DEBUG_DAC
            dputs_colour("[RED]drv_dac_ad5667r_i2c_callback() DRV_I2C_TRANSFER_EVENT_ERROR[WHITE]\r\n");
            #endif
            drv_dac.state = DRV_DAC_STATE_ERROR;
            drv_dac.error = DRV_DAC_ERROR_I2C_WRITE;
            break;
        }

        default:
            break;
    }
}
/* End of function drv_dac_ad5667r_i2c_callback                               */

/* ************************************************************************** */
/* Function: drv_dac_ad5667r_controller_task                                  */
/* Called in the main task idle loop to send register updates to the DAC      */
/* ************************************************************************** */
bool drv_dac_ad5667r_controller_task(void)
{
    switch (drv_dac.state)
    {
        case DRV_DAC_STATE_INIT:
        {

            drv_dac.state = DRV_DAC_STATE_IDLE;
            break;
        }

        /* waiting for a new command to be issued (via an incoming API function call) */
        case DRV_DAC_STATE_IDLE:
        {
            /* no command is queued - nothing to do */
            if (0 == drv_dac.command_mask)
            {
                break;
            }

            /* process the next command in the queue */

            if ((drv_dac.command_mask & DRV_DAC_CMD_SET_DAC1) > 0)
            {
                drv_dac.command_mask &= ~DRV_DAC_CMD_SET_DAC1;
                drv_dac.cmd_buffer[0] = DRV_DAC_REG | DRV_DAC_1;
                drv_dac.cmd_buffer[1] = drv_dac.dac[0] >> 8;
                drv_dac.cmd_buffer[2] = drv_dac.dac[0];
                //dprintf_colour("[YELLOW]DRV_I2C_WriteTransferAdd(): setting DAC value %d[WHITE]\r\n", drv_dac.dac[0]);
                
                if( DRV_I2C4_Write_Bytes(DRV_DAC_I2C_SLAVE_ADDRESS, drv_dac.cmd_buffer[0], &drv_dac.cmd_buffer[1], 2) != DRV_I2C4_WRITE_COMPLETE)
                {
                    drv_dac.error = DRV_DAC_ERROR_I2C_WRITE;
                }
                break;
            }

            if ((drv_dac.command_mask & DRV_DAC_CMD_SET_DAC2) > 0)
            {
                drv_dac.command_mask &= ~DRV_DAC_CMD_SET_DAC2;
                drv_dac.cmd_buffer[0] = DRV_DAC_REG | DRV_DAC_2;
                drv_dac.cmd_buffer[1] = drv_dac.dac[1] >> 8;
                drv_dac.cmd_buffer[2] = drv_dac.dac[1];
                
                if( DRV_I2C4_Write_Bytes(DRV_DAC_I2C_SLAVE_ADDRESS, drv_dac.cmd_buffer[0], &drv_dac.cmd_buffer[1], 2) != DRV_I2C4_WRITE_COMPLETE)
                {
                    drv_dac.error = DRV_DAC_ERROR_I2C_WRITE;
                }
                break;
            }

            if ((drv_dac.command_mask & DRV_DAC_CMD_SET_DACS) > 0)
            {
                drv_dac.command_mask &= ~DRV_DAC_CMD_SET_DACS;
                drv_dac.cmd_buffer[0] = DRV_DAC_REG | DRV_DAC_ALL;
                drv_dac.cmd_buffer[1] = drv_dac.dac[0] >> 8;
                drv_dac.cmd_buffer[2] = drv_dac.dac[0];
                
                if( DRV_I2C4_Write_Bytes(DRV_DAC_I2C_SLAVE_ADDRESS, drv_dac.cmd_buffer[0], &drv_dac.cmd_buffer[1], 2) != DRV_I2C4_WRITE_COMPLETE)
                {
                    drv_dac.error = DRV_DAC_ERROR_I2C_WRITE;
                }
                break;
            }              
            
            if ((drv_dac.command_mask & DRV_DAC_CMD_SET_PMODE) > 0)
            {
                drv_dac.command_mask &= ~DRV_DAC_CMD_SET_PMODE;
                drv_dac.cmd_buffer[0] = DRV_PMODE_REG;
                drv_dac.cmd_buffer[1] = 0;
                drv_dac.cmd_buffer[2] = drv_dac.pmode;
                
                if( DRV_I2C4_Write_Bytes(DRV_DAC_I2C_SLAVE_ADDRESS, drv_dac.cmd_buffer[0], &drv_dac.cmd_buffer[1], 2) != DRV_I2C4_WRITE_COMPLETE)
                {
                    drv_dac.error = DRV_DAC_ERROR_I2C_WRITE;
                }
                break;
            }           
            
            if ((drv_dac.command_mask & DRV_DAC_CMD_SET_LDAC) > 0)
            {
                drv_dac.command_mask &= ~DRV_DAC_CMD_SET_LDAC;
                drv_dac.cmd_buffer[0] = DRV_LDAC_REG;
                drv_dac.cmd_buffer[1] = 0;
                drv_dac.cmd_buffer[2] = drv_dac.ldac;
                
                if( DRV_I2C4_Write_Bytes(DRV_DAC_I2C_SLAVE_ADDRESS, drv_dac.cmd_buffer[0], &drv_dac.cmd_buffer[1], 2) != DRV_I2C4_WRITE_COMPLETE)
                {
                    drv_dac.error = DRV_DAC_ERROR_I2C_WRITE;
                }
                break;
            }          
     
            if ((drv_dac.command_mask & DRV_DAC_CMD_SET_REF) > 0)
            {
                drv_dac.command_mask &= ~DRV_DAC_CMD_SET_REF;
                drv_dac.cmd_buffer[0] = DRV_REF_REG;
                drv_dac.cmd_buffer[1] = 0;
                drv_dac.cmd_buffer[2] = drv_dac.intref;
                
                if( DRV_I2C4_Write_Bytes(DRV_DAC_I2C_SLAVE_ADDRESS, drv_dac.cmd_buffer[0], &drv_dac.cmd_buffer[1], 2) != DRV_I2C4_WRITE_COMPLETE)
                {
                    drv_dac.error = DRV_DAC_ERROR_I2C_WRITE;
                }
                break;
            }

            if ((drv_dac.command_mask & DRV_DAC_CMD_RESET) > 0)
            {
                drv_dac.command_mask &= ~DRV_DAC_CMD_RESET;
                drv_dac.cmd_buffer[0] = DRV_RESET_REG;
                drv_dac.cmd_buffer[1] = 0;
                drv_dac.cmd_buffer[2] = DRV_DAC_RESET_ALL;
                
                if( DRV_I2C4_Write_Bytes(DRV_DAC_I2C_SLAVE_ADDRESS, drv_dac.cmd_buffer[0], &drv_dac.cmd_buffer[1], 2) != DRV_I2C4_WRITE_COMPLETE)
                {
                    drv_dac.error = DRV_DAC_ERROR_I2C_WRITE;
                }
                break;
            }

            break;
        }

        case DRV_DAC_STATE_WAIT:
        {
            // do nothing, wait for callback                  
            break;
        }

        case DRV_DAC_STATE_ERROR:
        default:
            drv_dac.state = DRV_DAC_STATE_IDLE;
            break;
    }

    return ((DRV_DAC_STATE_IDLE != drv_dac.state) || (0 != drv_dac.command_mask));
}
/* End of function drv_dac_ad5667r_controller_task                            */

/*******************************************************************************
                            External Functions
*******************************************************************************/

/* reset the DAC */
void drv_dac_reset( void )
{
    drv_dac_push(DRV_DAC_CMD_RESET);
}

/* set LDAC */
void drv_dac_set_ldac(uint8_t ldac)
{
    drv_dac.ldac = ldac;
    drv_dac_push(DRV_DAC_CMD_SET_LDAC);
}

/* set the internal reference */
void drv_dac_set_reference(uint8_t ref)
{
    drv_dac.intref = ref;
    drv_dac_push(DRV_DAC_CMD_SET_REF);
}

/* set the power mode  */
void drv_dac_set_power_mode(uint8_t pmode)
{
    drv_dac.pmode = pmode;
    drv_dac_push(DRV_DAC_CMD_SET_PMODE);
}

/* set the DAC value  */
void drv_dac_set_value(DRV_DAC_INDEX dac, uint16_t value)
{
    #ifdef DEBUG_DAC
    dprintf_colour("[YELLOW]drv_dac_set_value() DAC %d, value %d[WHITE]\r\n", dac, value);
    #endif

    if (dac == DRV_DAC_1)
    {
        drv_dac.dac[0] = value;
        drv_dac_push(DRV_DAC_CMD_SET_DAC1);        
    }
    else if (dac == DRV_DAC_2)
    {
        drv_dac.dac[1] = value;
        drv_dac_push(DRV_DAC_CMD_SET_DAC2);
    }
    else
    {
        drv_dac.dac[0] = value;
        drv_dac.dac[1] = value;
        drv_dac_push(DRV_DAC_CMD_SET_DACS);        
    }
}

/* Get the DAC value  */
uint16_t drv_dac_get_value(DRV_DAC_INDEX dac)
{
    return drv_dac.dac[dac];
}

/* Check if the driver is busy  */
bool drv_dac_busy(void)
{
    if( drv_dac.command_mask == 0U )
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* Check if the error occurred */
DRV_DAC_ERROR drv_dac_get_last_error(void)
{
    return drv_dac.error;
}

/* Clear error */
void drv_dac_clear_error(void)
{
    drv_dac.error = DRV_DAC_ERROR_NONE;
}

/** drv_dac_ad5667r.c ***************************************************************/  
