/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_lsc.c

  @Summary
    Driver for Linear Scanning Controller

  @Description
    Uses UART 2 to communicate with the LSC (dsPIC33)
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "drv_lsc.h"
#include "debug.h"
#include "message_exchange.h"

/*******************************************************************************
                             Definitions
*******************************************************************************/

#define DRV_LSC_SPI_INDEX               0

#define LSC_INIT_TIMEOUT                30000
#define LSC_TIMEOUT_MS                  10000
#define LSC_WAIT_LSC_POWER_UP           200

/*******************************************************************************
                             Typedefs
*******************************************************************************/


typedef enum
{
    DRV_LSC_STATE_INIT = 0U,
    DRV_LSC_STATE_WAIT_LSC_POWER_UP = 1,
    DRV_LSC_STATE_INIT_WAIT_READY = 2,
    DRV_LSC_STATE_INIT_WAIT_LIMITS_COMMAND = 3,
    DRV_LSC_STATE_INIT_WAIT_READY_STATUS_SEND = 4,      
    DRV_LSC_STATE_INIT_WAIT_READY_STATUS_READ =5,

    DRV_LSC_STATE_IDLE = 6,
    DRV_LSC_STATE_WAIT_FOR_NOT_BUSY = 7,
    DRV_LSC_STATE_WAIT_GET_VERSION= 8,
    DRV_LSC_STATE_WAIT_GET_STATUS =9,
 
    DRV_LSC_STATE_ERROR = 10,
    DRV_LSC_STATE_INIT_ERROR= 11,
    DRV_LSC_STATE_INIT_RETRY = 12, 
    DRV_LSC_STATE_WAIT_RESET = 13
} DRV_LSC_STATE;

typedef enum
{
    DRV_LSC_GET_VERSION = 1,
    DRV_LSC_DEFINE_LIMITS = 2,
    DRV_LSC_START_SCANNING = 4,
    DRV_LSC_STOP_SCANNING = 8,
    DRV_LSC_GET_STATUS = 16,            
    DRV_LSC_RESET = 32, 
    DRV_LSC_IS_SHUTDOWN_SAFE = 64,
} DRV_LSC_COMMAND;

typedef struct
{
    DRV_LSC_STATE state;
    DRV_LSC_STATE previous_state;
    DRV_LSC_ERRORS error;

    /* data for get status */
    uint8_t get_status_command;
    LSC_STATUS_t status;
    
    DRV_LSC_COMMAND command_mask;           /* "queue" of up to 4 commands */
    
    bool initialised;
    bool scanning;
    
    uint8_t next_command;
    uint8_t restart_count; 
} DRV_LSC_OBJ;

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

static DRV_LSC_OBJ drv_lsc = 
{
    .state = DRV_LSC_STATE_INIT,
    .previous_state = DRV_LSC_STATE_INIT,
    .initialised = false,
    .status.Version = 0U,
    .status.flags.Short = 0, 
    .command_mask = 0U,                      /* no commands queued */
    .error = LSC_ERROR_NONE,
    .restart_count = 0u,
};

typedef enum{
    
    IDLE = 0, 
    RUNNING  = 1, 
    ELAPSED = 2,
    LOCKED = 3,
    
}timeout_state_t;


static volatile struct{
    
    volatile int32_t durn; 
    volatile timeout_state_t state; 
}drv_lsc_timeout = { .durn = -1, .state = IDLE};

/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

/* start system timer */
static void start_timer(uint32_t delay_ms)
{
    if(delay_ms > INT32_MAX){
        
        delay_ms = INT32_MAX; 
    }
    
    drv_lsc_timeout.state = LOCKED;
    
    drv_lsc_timeout.durn = delay_ms; 
    
    drv_lsc_timeout.state = RUNNING; 
}

static bool check_timer()
{
    
    
    if(drv_lsc_timeout.state == ELAPSED){
        
        drv_lsc_timeout.state =IDLE; 
        
        return true; 
    }else if(drv_lsc_timeout.state == RUNNING){
        
        return false; 
    }else{
       
        dputs("drv_lsc timer warning check when idle\r\n");
       return false;  
    }
    
}

static uint32_t bytes_to_u32_t(uint8_t * status){
    
    uint32_t val = ((uint32_t)*status) | (((uint32_t)*(status+1))<<8) | (((uint32_t)*(status+2))<<16) | (((uint32_t)*(status+3))<<24);

    return val; 
}

typedef union{
    float f;
    uint32_t u32; 
    
}float_uint32_t;

static float bytes_to_float(uint8_t * status){
    
    float_uint32_t val;
    
    val.u32= bytes_to_u32_t(status); 
    
    
    return val.f;
}

static uint16_t bytes_to_u16_t(uint8_t * status){
    
    uint16_t val = *status;
    val |= ((uint16_t)*(status+1))<<8; 
    
    return val;
}

void drv_lsc_set_error_flag (DRV_LSC_ERRORS err);

void drv_lsc_clear_errors(void);

void drv_lsc_clear_error_flag(DRV_LSC_ERRORS err);

/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/*******************************************************************************
 * Function:        void send_lsc_command(LSC_COMMANDS command)
 * Precondition:    None
 * Input:           LSC_COMMANDS command: Commend that PDAB wants to send to LSC
 * Output:          None
 * Returns:         None
 * Side Effects:    None
 * Overview:        Decide what message send to LSC 
 * Notes:           None
*******************************************************************************/ 
void send_lsc_command(LSC_COMMANDS command)
{
    switch (command)
    {        
        case LSC_NONE:
            break;
        case LSC_GET_VERSION:
        {    
            send_get_LSC_version_message();
            break;
        }
        case LSC_GET_STATUS:
        {
            send_get_LSC_status_message();
            break;
        }
        case LSC_DEFINE_LIMITS:
        {    
            send_request_LSC_define_limits_message();
            break;
        }    
        case LSC_START_SCANNING:
        {    
            send_request_LSC_start_scanning_message();  
            break;
        }    
        case LSC_STOP_SCANNING:
        {    
            send_request_LSC_stop_scanning_message();
            break;
        }    
        case LSC_RESET:
        {    
            send_request_reset_message();
            break;
        }
        case LSC_IS_SHUTDOWN_SAFE:
        {
            send_command_LSC_is_shutdown_safe_message();
            break;
        }
        default:
            break;
    }        
}
/* End of function send_lsc_command  */ 



void drv_lsc_millisecond_tick(){
    if(drv_lsc_timeout.state == RUNNING){
        if(drv_lsc_timeout.durn > 0){

            drv_lsc_timeout.durn--; 
        }else if(drv_lsc_timeout.durn == 0){

            drv_lsc_timeout.state = ELAPSED; 
            drv_lsc_timeout.durn = -1; 
        }
    }
}


/* ************************************************************************** */
/* Function: drv_lsc_controller_task                                          */
/* Called in the main task idle loop to send updates to the LSC               */
/* ************************************************************************** */
bool drv_lsc_controller_task(void)
{
    switch (drv_lsc.state)
    {
        case DRV_LSC_STATE_INIT:
        {                          
            LSC_DIR_InputEnable(); 
            LSC_BUSY_InputEnable();
            EVIC_SourceDisable(LSC_BUSY_INTERRUPT);   
            EVIC_SourceStatusClear(LSC_BUSY_INTERRUPT); 
            #ifdef DEBUG_LSC
            dputs_colour("[YELLOW]DRV_LSC_STATE_INIT - initialising LSC driver[WHITE]\r\n");
            #endif
            drv_lsc.state = DRV_LSC_STATE_WAIT_LSC_POWER_UP;
            start_timer(LSC_WAIT_LSC_POWER_UP);
            break;
        }

        /* short wait to ensure that the LSC is up an running before we try to do anything with it */
        case DRV_LSC_STATE_WAIT_LSC_POWER_UP:
        {
            if (check_timer())
            {
                #ifdef DEBUG_LSC
                dputs_colour("[YELLOW]Wait LSC power up complete[WHITE]\r\n");
                #endif
                drv_lsc.state = DRV_LSC_STATE_INIT_WAIT_READY;
                start_timer(LSC_INIT_TIMEOUT);
            }
            break;
        }

        // Initialisation sequence:
        // 1) Wait for ready
        // 2) WriteLSCCommand(LSC_DEFINE_LIMITS, 0, 0)
        // 3) Wait 1 second
        // 4) Read LSC status till tuning ends 
        // 5) LSC ready

        /* wait for the LSC to be ready */
        case DRV_LSC_STATE_INIT_WAIT_READY:
        {
            if ( true == drv_lsc_is_scanning() )
            {
                /* check for timeout */
                if (check_timer())
                {
                    dputs_colour("[RED]TIMEOUT waiting for LSC ready[WHITE]\r\n");
                    drv_lsc.state = DRV_LSC_STATE_ERROR;
                }

                break;
            }
            
            #ifdef DEBUG_LSC
            dputs_colour("[YELLOW]LSC driver: sending define limits command[WHITE]\r\n");
            #endif
            drv_lsc.initialised = false;
            send_lsc_command(LSC_DEFINE_LIMITS);
            start_timer(100);
            drv_lsc.state = DRV_LSC_STATE_INIT_WAIT_LIMITS_COMMAND;
            break;
        }
        
        /* wait after sending the define limits command */
        case DRV_LSC_STATE_INIT_WAIT_LIMITS_COMMAND:
        {
            if (check_timer())
            {
                #ifdef DEBUG_LSC
                dputs_colour("[YELLOW]LSC driver: Finished waiting for define limits command[WHITE]\r\n");
                #endif
                drv_lsc.state = DRV_LSC_STATE_INIT_WAIT_READY_STATUS_SEND;
                start_timer(1000);
            }
            break;
        }

        /* wait for the LSC to be ready - tuning ends by checking the status */
        case DRV_LSC_STATE_INIT_WAIT_READY_STATUS_SEND:
        {
            if (check_timer())
            {
                #ifdef DEBUG_LSC
                dputs_colour("[YELLOW]LSC driver: Sending get status command[WHITE]\r\n");
                #endif


                drv_lsc.state = DRV_LSC_STATE_INIT_WAIT_READY_STATUS_READ;
                send_lsc_command(LSC_GET_STATUS);
                start_timer(1000);
            }
            break;
        }

        case DRV_LSC_STATE_INIT_WAIT_READY_STATUS_READ:
        {
            // do nothing, wait for the UART callback and check if the timeout delay has expired
            if (check_timer())
            {
                dputs_colour("[RED]TIMEOUT waiting for LSC status. LSC driver initialisation error[WHITE]\r\n");
                drv_lsc.state = DRV_LSC_STATE_INIT_ERROR;
            }
            break;
            
        }

        /* waiting for a new command to be issued (via an incoming API function call) */
        case DRV_LSC_STATE_IDLE:
        {

            /* no command is queued - nothing to do */
            if (0 == drv_lsc.command_mask)
            {
                break;
            }

            /* process the next command in the queue */
            
            if ((drv_lsc.command_mask & DRV_LSC_GET_VERSION) > 0)
            {
                #ifdef DEBUG_LSC
                dputs_colour("[MAGENTA]DRV_LSC_GET_VERSION[WHITE]\r\n");
                #endif
                drv_lsc.command_mask &= ~DRV_LSC_GET_VERSION;
                drv_lsc.state = DRV_LSC_STATE_WAIT_FOR_NOT_BUSY;    
                send_lsc_command(LSC_GET_VERSION);
                start_timer(LSC_TIMEOUT_MS);
                break;
            }                

            if ((drv_lsc.command_mask & DRV_LSC_GET_STATUS) > 0)
            {
                #ifdef DEBUG_LSC
                dputs_colour("[MAGENTA]DRV_LSC_GET_STATUS[WHITE]\r\n");
                #endif
                drv_lsc.command_mask &= ~DRV_LSC_GET_STATUS;

                /* send the SPI read command to get the status block and then set the state to wait for the SPI callback */
                drv_lsc.state = DRV_LSC_STATE_WAIT_GET_STATUS;
                send_lsc_command(LSC_GET_STATUS);
                start_timer(LSC_TIMEOUT_MS);
                break;
            }        

            if ((drv_lsc.command_mask & DRV_LSC_DEFINE_LIMITS) > 0)
            {
                drv_lsc.command_mask &= ~DRV_LSC_DEFINE_LIMITS;
                drv_lsc.state = DRV_LSC_STATE_WAIT_FOR_NOT_BUSY;
                drv_lsc.next_command = LSC_DEFINE_LIMITS;
                
                start_timer(LSC_TIMEOUT_MS);
                break;
            }

            if ((drv_lsc.command_mask & DRV_LSC_START_SCANNING) > 0)
            {
                drv_lsc.scanning = true;
                drv_lsc.command_mask &= ~DRV_LSC_START_SCANNING;
                drv_lsc.state = DRV_LSC_STATE_WAIT_FOR_NOT_BUSY;
                drv_lsc.next_command = LSC_START_SCANNING;

                start_timer(LSC_TIMEOUT_MS);
                break;
            }

            if ((drv_lsc.command_mask & DRV_LSC_STOP_SCANNING) > 0)
            {
                drv_lsc.scanning = false;
                drv_lsc.command_mask &= ~DRV_LSC_STOP_SCANNING;
                drv_lsc.state = DRV_LSC_STATE_WAIT_FOR_NOT_BUSY;
                drv_lsc.next_command = LSC_STOP_SCANNING;

                start_timer(LSC_TIMEOUT_MS);
                break;
            }
            if ((drv_lsc.command_mask & DRV_LSC_IS_SHUTDOWN_SAFE) > 0)
            {
                drv_lsc.command_mask &= ~DRV_LSC_IS_SHUTDOWN_SAFE;
                drv_lsc.state = DRV_LSC_STATE_WAIT_FOR_NOT_BUSY;
                drv_lsc.next_command = LSC_IS_SHUTDOWN_SAFE;

                start_timer(LSC_TIMEOUT_MS);
                break;
            }

            break;
        }

        case DRV_LSC_STATE_WAIT_FOR_NOT_BUSY:
        {
            /* check for LSC timeout */
            if( check_timer() )
            {
                dputs_colour("[RED]DRV_LSC TIMEOUT 1[WHITE]\r\n");
                drv_lsc.state = DRV_LSC_STATE_ERROR;
                break;
            }

            /* is the LSC still busy?- Removed as LSC uses DMA for scanning so commmands can be send at anytime*/ 
            //if (drv_lsc_is_scanning())
            //{
            //    dputs_colour("[RED]Still scanning...[WHITE]\r\n");
            //    break;
            //}
                
            /* send the next command */
            send_lsc_command(drv_lsc.next_command);
            
            drv_lsc.next_command = LSC_NONE;
            drv_lsc.state = DRV_LSC_STATE_IDLE;
            break;
        }

        case DRV_LSC_STATE_WAIT_GET_STATUS:
        {
            // do nothing, wait for the UART callback and check if the timeout delay has expired
            if (check_timer())
            {
                dputs_colour("[RED]DRV_LSC TIMEOUT 2[WHITE]\r\n");
                drv_lsc.state = DRV_LSC_STATE_ERROR;
            }
            break;
        }
        
        case DRV_LSC_STATE_WAIT_GET_VERSION:
        {
            // do nothing, wait for the UART callback and check if the timeout delay has expired
            if (check_timer())
            {
                dputs_colour("[RED]DRV_LSC TIMEOUT 3[WHITE]\r\n");
                drv_lsc.state = DRV_LSC_STATE_ERROR;
            }
            break;
        }        

        case DRV_LSC_STATE_ERROR:
        default:
        {
            drv_lsc.state = DRV_LSC_STATE_IDLE;
            break;
        }

        /* can't do anything if the LSC failed to initialise */
        case DRV_LSC_STATE_INIT_ERROR:
        {
            
            if(drv_lsc.previous_state != drv_lsc.state){
                
                dputs_colour("[RED]LSC init fail: gave up resetting[WHITE]\r\n");
                
                drv_lsc.previous_state = drv_lsc.state; 
            }
            
            
            break;
        }
        
        case DRV_LSC_STATE_INIT_RETRY:
            
            if (drv_lsc.restart_count < 2){
                
                drv_lsc.state = DRV_LSC_STATE_WAIT_RESET;      
                drv_lsc.restart_count++;
                
                send_lsc_command(LSC_RESET); 
                
                dputs_colour("[YELLOW]DRV_LSC LSC init fail: reseting LSC[WHITE]\r\n");
                
            }else{
                drv_lsc.previous_state = DRV_LSC_STATE_INIT_RETRY; 
                drv_lsc.state = DRV_LSC_STATE_INIT_ERROR; 
            }
            
            
            break; 
            
        case DRV_LSC_STATE_WAIT_RESET:
            
            if( drv_lsc.previous_state != DRV_LSC_STATE_WAIT_RESET){
                start_timer(200);
                
                drv_lsc.previous_state = DRV_LSC_STATE_WAIT_RESET; 
            }
            
            if(check_timer()){
                
                drv_lsc_clear_errors(); 
                drv_lsc.state = DRV_LSC_STATE_INIT; 
            }
            break; 
    }

    return (((drv_lsc.state != DRV_LSC_STATE_IDLE) && (drv_lsc.state != DRV_LSC_STATE_INIT_ERROR)) || (0 != drv_lsc.command_mask));
}
/* End of function drv_lsc_controller_task                                    */

/*******************************************************************************
 * Function:        void drv_lsc_call_get_status(void))
 * Precondition:    None
 * Input:           None
 * Output:          None
 * Returns:         None
 * Side Effects:    None
 * Overview:        Request the LSC status
 * Notes:           None
*******************************************************************************/ 
void drv_lsc_call_get_status(void)
{
    if (drv_lsc.state > DRV_LSC_STATE_INIT_WAIT_READY_STATUS_READ)
    {    
        if ((drv_lsc.command_mask & DRV_LSC_GET_STATUS) == 0)
        {    
            drv_lsc.command_mask |= DRV_LSC_GET_STATUS;
            #ifdef DEBUG_LSC
            dputs_colour("[MAGENTA]LSC Get status[WHITE]\r\n");
            #endif
        }
        else
        {
            #ifdef DEBUG_LSC
            dputs_colour("[MAGENTA]LSC Get status command already queued[WHITE]\r\n");
            #endif        
        }
    }
}
/*******************************************************************************
 * Function:        void drv_lsc_get_last_status( LSC_STATUS_t * status )
 * Precondition:    None
 * Input:           Pointer to structure containing last received LSC status
 * Output:          None
 * Returns:         None
 * Side Effects:    None
 * Overview:        Retrieves the last received LSC status
 * Notes:           None
*******************************************************************************/ 
void drv_lsc_get_last_status(LSC_STATUS_t * status )
{
    if( status != NULL )
    {
        memcpy(status, &drv_lsc.status, sizeof(LSC_STATUS_t));
    }  
}
/*******************************************************************************
 * Function:        void read_lsc_status( uint8_t * status )
 * Precondition:    None
 * Input:           Reading LSC status 
 * Output:          None
 * Returns:         None
 * Side Effects:    None
 * Overview:        Read last received LSC status and copy value to drv_lsc
 * Notes:           None
*******************************************************************************/ 
void read_lsc_status( uint8_t * status )
{
    
    //dputs("lsc status read\r\n"); 
    //if ((drv_lsc.command_mask & DRV_LSC_GET_STATUS) == 0) //
    //{  

        
        #ifdef DEBUG_LSC
        dputs_colour("[GREEN]LSC status received[WHITE]\r\n");
        dprintf_colour("[GREEN]LSC status is %2d bytes[WHITE]\r\n", sizeof(LSC_STATUS_t));
       
        #endif
        
        drv_lsc.status.Version = bytes_to_u16_t(status);
        uint8_t * var_pos = status + 2;
        drv_lsc.status.flags.Short = bytes_to_u16_t(var_pos);
        var_pos += 2;
        
        drv_lsc.status.Range = bytes_to_u32_t(var_pos);
        var_pos += sizeof(drv_lsc.status.Range); 
        
        drv_lsc.status.Length = bytes_to_u32_t(var_pos );
        var_pos += sizeof(drv_lsc.status.Length);
        
        drv_lsc.status.Frequency = bytes_to_float(var_pos);
        var_pos += sizeof(drv_lsc.status.Frequency);
        
        drv_lsc.status.Position = (int32_t)bytes_to_u32_t(var_pos );
        var_pos += sizeof(drv_lsc.status.Position);
        
        drv_lsc.status.RefPositions[0] = (int32_t)bytes_to_u32_t(var_pos ); 
        var_pos += sizeof(drv_lsc.status.RefPositions[0]);
        drv_lsc.status.RefPositions[1] = (int32_t)bytes_to_u32_t(var_pos );
        
       
        //memcpy(&drv_lsc.status, status, sizeof(LSC_STATUS_t));
        if (drv_lsc.state != DRV_LSC_STATE_INIT_WAIT_READY_STATUS_READ && drv_lsc.state != DRV_LSC_STATE_WAIT_GET_STATUS)
        {
            #ifdef DEBUG_LSC
            dputs_colour("[RED]LSC status received while not waiting for it[WHITE]\r\n");
            #endif
            return;
        }
        #ifdef DEBUG_LSC
        int i = 0;
        for ( i = 0; i < sizeof(LSC_STATUS_t) ; i ++ )
        {
            dprintf_colour("[MAGENTA]%x\r\n",(uint16_t) status[i]);
        }
        dprintf_colour("[MAGENTA]LSC status received, drv_lsc.status.Header.Version is %u[WHITE]\r\n", drv_lsc.status.Version);
        dprintf_colour("[MAGENTA]drv_lsc.status.Scan.Range is %u[WHITE]\r\n", (uint16_t)drv_lsc.status.Range);
        dprintf_colour("[MAGENTA]drv_lsc.status.Scan.Freq is %.1f[WHITE]\r\n", drv_lsc.status.Frequency);
        #endif

        if (drv_lsc.state == DRV_LSC_STATE_INIT_WAIT_READY_STATUS_READ)
        {
            if (drv_lsc.status.flags.TUNE_ERROR == true)
            {
                dputs_colour("[RED]LSC tuning error[WHITE]\r\n");
                
                drv_lsc_set_error_flag(LSC_ERROR_TUNING); 
                
                drv_lsc.state = DRV_LSC_STATE_INIT_RETRY;
            }
            else if (drv_lsc.status.flags.TUNE_FINISHED == true)
            {  
                if ((drv_lsc.status.Range < LRS_RANGE_MIN) || (drv_lsc.status.Range > LRS_RANGE_MAX))
                {
                    // initialisation failed
                    dputs_colour("[RED]LSC scan range outside bounds[WHITE]\r\n");
                    drv_lsc_set_error_flag(LSC_ERROR_TUNING); 
                    drv_lsc_set_error_flag(LSC_ERROR_SCAN_RANGE);
                    drv_lsc.state = DRV_LSC_STATE_INIT_RETRY;
                }
                else
                {    
                    #ifdef DEBUG_LSC
                    dputs_colour("[GREEN]LSC tuning finished successfully[WHITE]\r\n");
                    #endif
                    
                    drv_lsc.initialised = true;
                    drv_lsc.state = DRV_LSC_STATE_IDLE;
                }
            }
            else 
            {
                #ifdef DEBUG_LSC
                dputs_colour("[GREEN]LSC tuning still on [WHITE]\r\n");
                #endif
                drv_lsc.state = DRV_LSC_STATE_INIT_WAIT_READY_STATUS_SEND;
                start_timer(2000);
            }
        }
        else 
        {
            // initialisation succeeded
            // wait for commands
            #ifdef DEBUG_LSC
                dputs_colour("[GREEN]LSC driver initialised successfully[WHITE]\r\n");
            #endif

            //drv_lsc.initialised = true;
            drv_lsc.state = DRV_LSC_STATE_IDLE;
        }
    //}   
}

/*******************************************************************************
 * Function:        void drv_lsc_define_limits(void)
 * Precondition:    None
 * Input:           None
 * Output:          None
 * Returns:         None
 * Side Effects:    None
 * Overview:        Queues define limits command to be executed when the LSC is
 *                  not busy
 * Notes:           None
*******************************************************************************/ 
void drv_lsc_define_limits(void)
{
    drv_lsc.command_mask |= DRV_LSC_DEFINE_LIMITS;
}

/*******************************************************************************
 * Function:        void drv_lsc_start_scanning(void)
 * Precondition:    None
 * Input:           None
 * Output:          None
 * Returns:         None
 * Side Effects:    None
 * Overview:        Queues start scanning command to be executed when the LSC is
 *                  not busy
 * Notes:           None
*******************************************************************************/ 
void drv_lsc_start_scanning(void)
{
    drv_lsc.command_mask |= DRV_LSC_START_SCANNING;
}

/*******************************************************************************
 * Function:        void drv_lsc_stop_scanning(void)
 * Precondition:    None
 * Input:           None
 * Output:          None
 * Returns:         None
 * Side Effects:    None
 * Overview:        Queues stop scanning command to be executed when the LSC is
 *                  not busy
 * Notes:           None
*******************************************************************************/ 
void drv_lsc_stop_scanning(void)
{
    drv_lsc.command_mask |= DRV_LSC_STOP_SCANNING;
}

/*******************************************************************************
 * Function:        void drv_lsc_reset(void)
 * Precondition:    None
 * Input:           None
 * Output:          None
 * Returns:         None
 * Side Effects:    None
 * Overview:        Immediately sends reset command to the LSC
 * Notes:           None
*******************************************************************************/ 
void drv_lsc_reset(void)
{
    drv_lsc.command_mask |= DRV_LSC_RESET;    
}
/*******************************************************************************
 * Function:        void drv_lsc_is_shutdown_safe(void)
 * Precondition:    None
 * Input:           None
 * Output:          None
 * Returns:         None
 * Side Effects:    None
 * Overview:        Queues is shutdown safe message to be executed when the LSC is
 *                  not busy
 * Notes:           None
*******************************************************************************/ 
void drv_lsc_is_shutdown_safe(void)
{
    drv_lsc.command_mask |= DRV_LSC_IS_SHUTDOWN_SAFE;
}
/*******************************************************************************
 * Function:        bool drv_lsc_is_scanning(void)
 * Precondition:    None
 * Input:           None
 * Output:          None
 * Returns:         True if scanning, false if idle
 * Side Effects:    None
 * Overview:        Returns the state of the LSC_BUSY pin
 * Notes:           None
*******************************************************************************/ 
bool drv_lsc_is_scanning(void)
{
    return (!SYS_PORT_PinRead(LSC_BUSY));       // LSC is active low so logic is inverted    
}

/*******************************************************************************
 * Function:        bool drv_lsc_current_version(void)
 * Precondition:    None
 * Input:           None
 * Output:          None
 * Returns:         LSC firmware version number
 * Side Effects:    None
 * Overview:        Returns LSC firmware version number
 * Notes:           None
*******************************************************************************/ 
uint32_t drv_lsc_current_version(void)
{
    return (drv_lsc.status.Version);       // Return version number
}
/*******************************************************************************
 * Function:        bool drv_lsc_is_scanning(void)
 * Precondition:    None
 * Input:           None
 * Output:          None
 * Returns:         True if busy, false if idle
 * Side Effects:    None
 * Overview:        Check if the LSC driver is busy
 * Notes:           None
*******************************************************************************/ 
bool drv_lsc_is_busy(void)
{
    if ( (0U == drv_lsc.command_mask) && ( drv_lsc.scanning == false ) && ( false == drv_lsc_is_scanning() ) )
    {
        return (false);
    }

    return (true);
}

/*******************************************************************************
 * Function:        bool drv_lsc_is_initialised(void)
 * Precondition:    None
 * Input:           None
 * Output:          None
 * Returns:         True if initialised, false if idle
 * Side Effects:    None
 * Overview:        Check if the LSC has been initialised
 * Notes:           None
*******************************************************************************/ 
bool drv_lsc_is_initialised(void)
{
    return drv_lsc.initialised;
}
/*******************************************************************************
 * Function:        bool drv_lsc_awaiting_status(void)
 * Precondition:    None
 * Input:           None
 * Output:          None
 * Returns:         True status callback is active
 * Side Effects:    None
 * Overview:        Check if the LSC has been initialised
 * Notes:           None
*******************************************************************************/ 
//bool drv_lsc_awaiting_status(void)
//{
//    if( drv_lsc.get_status_complete_callback == NULL )
//        return false;
//    else
//        return true;
//}

/*******************************************************************************
 * Function:        bool drv_lsc_initialise(void)
 * Precondition:    None
 * Input:           None
 * Output:          None
 * Returns:         True if initialised, false if idle
 * Side Effects:    None
 * Overview:        Check if the LSC has been initialised
 * Notes:           None
*******************************************************************************/ 
void drv_lsc_initialise(void)
{
    drv_lsc.state = DRV_LSC_STATE_INIT;
}
/*******************************************************************************
 * Function:        LSC_ERRORS drv_lsc_get_error(void)
 * Precondition:    None
 * Input:           None
 * Output:          None
 * Returns:         LSC error code
 * Side Effects:    None
 * Overview:        Retrieve the LSC error code
 * Notes:           None
*******************************************************************************/ 
DRV_LSC_ERRORS drv_lsc_get_error(void)
{
    return drv_lsc.error;
}

void drv_lsc_set_error_flag (DRV_LSC_ERRORS err){

     drv_lsc.error =drv_lsc.error | err; 
}

void drv_lsc_clear_errors(){
   drv_lsc.error = LSC_ERROR_NONE; 
}

void drv_lsc_error_clear_flag(DRV_LSC_ERRORS err){
    drv_lsc.error = drv_lsc.error & (~err);
}

/******************************************************************************/ 
/*                                  EOF                                       */
/******************************************************************************/ 
