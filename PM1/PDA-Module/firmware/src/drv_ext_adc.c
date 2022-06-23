/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_ext_adc.c

  @Summary
    LTC2202 ADC chip driver

  @Description
    This LTC2202 ADC driver translates non-blocking API function calls to
    commands that are queued and sent to the AD5667 DPOT chip.
 */
/* ************************************************************************** */

/*******************************************************************************
                            Includes Files
*******************************************************************************/

#include "drv_ext_adc.h"

/*******************************************************************************
                            Definitions
*******************************************************************************/

//#define ADC_ZERO_FIND_MAX_AND_MIN
#define ZERO_OFFSET_AT_CENTRE       0
#define ZERO_OFFSET_AT_BOTTOM       1
#define ZERO_OFFSET_AT_TOP          2

#define ZERO_OFFSET_MODE            ZERO_OFFSET_AT_BOTTOM

typedef enum
{
    DRV_EXT_ADC_SUBSTATE_IDLE = 0U,      
            
    DRV_EXT_ADC_OFFSET_STATE_1,
    DRV_EXT_ADC_OFFSET_STATE_2,
    DRV_EXT_ADC_OFFSET_STATE_3,
    DRV_EXT_ADC_OFFSET_STATE_4,
    DRV_EXT_ADC_OFFSET_STATE_5,
    DRV_EXT_ADC_OFFSET_STATE_6,
    DRV_EXT_ADC_OFFSET_STATE_COMPLETE,
    DRV_EXT_ADC_OFFSET_STATE_FAILED,
    
    DRV_EXT_ADC_ZERO_INIT,
    DRV_EXT_ADC_ZERO_START,
    DRV_EXT_ADC_ZERO_GET_MAX_AND_MIN,
    DRV_EXT_ADC_ZERO_COARSE_SCAN_GET_DATA,
    DRV_EXT_ADC_ZERO_COARSE_SCAN_START_ADC,
    DRV_EXT_ADC_ZERO_MEDIUM_SCAN_GET_DATA,
    DRV_EXT_ADC_ZERO_MEDIUM_SCAN_START_ADC,
    DRV_EXT_ADC_ZERO_FINE_SCAN_GET_DATA,
    DRV_EXT_ADC_ZERO_FINE_SCAN_START_ADC,
    DRV_EXT_ADC_ZERO_COMPLETE,
    DRV_EXT_ADC_ZERO_FAILED,       
            
} DRV_EXT_ADC_SUB_STATE;

typedef enum
{
    DRV_EXT_ADC_STATE_INIT = 0U,
    DRV_EXT_ADC_STATE_IDLE,
    DRV_EXT_ADC_STATE_OFFSET,
    DRV_EXT_ADC_STATE_ZERO,        
    DRV_EXT_ADC_STATE_ACQUIRING,
    DRV_EXT_ADC_STATE_ERROR        
} DRV_EXT_ADC_STATE;

typedef enum
{
    DRV_EXT_ADC_CMD_INIT            = 0x01,
    DRV_EXT_ADC_CMD_OFFSET          = 0x02,
    DRV_EXT_ADC_CMD_ZERO            = 0x04,       
    DRV_EXT_ADC_CMD_ACQUIRE = 0x08         
} DRV_EXT_ADC_COMMAND;

typedef enum
{
    DRV_EXT_ADC_ERROR_NONE,    
    DRV_EXT_ADC_ERROR_PMP,
    DRV_EXT_ADC_ERROR_DMA,        
} DRV_EXT_ADC_ERROR;


typedef struct
{
    DRV_EXT_ADC_STATE state;
    DRV_EXT_ADC_STATE previous_state;
    DRV_EXT_ADC_SUB_STATE substate;
    DRV_EXT_ADC_SUB_STATE previous_substate;    
    
    DRV_EXT_ADC_ERROR error;
    
    uint16_t* adc_dma1_buffer;
    uint16_t* adc_dma2_buffer;
    uint16_t* adc_data_buffer;
    uint16_t  adc_data_length;
    
    uint16_t adc_offset[DRV_EXT_ADC_COUNT];
    
    DRV_EXT_ADC_INDEX adc_channel;
    
    double pga_gain;
    
    bool zero_running;
    bool adc_running;
    
    DRV_EXT_ADC_COMMAND command_mask;                   /* "queue" of up to 6 commands */
    DRV_EXT_ADC_COMMAND last_command;
    
} DRV_EXT_ADC_OBJ;

/*******************************************************************************
                             Global Variables
*******************************************************************************/

uint16_t MAKE_BUFFER_DMA_READY _adc_dma1_buffer[DRV_EXT_ADC_DMA1_BUFFER_SIZE];
uint16_t MAKE_BUFFER_DMA_READY _adc_dma2_buffer[DRV_EXT_ADC_DMA2_BUFFER_SIZE];

static DRV_EXT_ADC_OBJ ext_adc_data = 
{
    .state = DRV_EXT_ADC_STATE_INIT,
    .previous_state = DRV_EXT_ADC_STATE_INIT,
    .substate = DRV_EXT_ADC_SUBSTATE_IDLE,
    .previous_substate = DRV_EXT_ADC_SUBSTATE_IDLE,
    
    .error = DRV_EXT_ADC_ERROR_NONE,
    .adc_dma1_buffer = _adc_dma1_buffer,
    .adc_dma2_buffer = _adc_dma2_buffer,
    .adc_data_buffer = NULL,
    .adc_data_length = 1U,
    .adc_channel = DRV_EXT_ADC_1,
    .adc_offset = {0},
    .pga_gain = 0,
    
    .adc_running = false,
    .zero_running = false,

    .command_mask = 0,                      /* no commands queued */
    .last_command = 0,                      /* no last command */
};

/*******************************************************************************
                             Local Functions
*******************************************************************************/

static void drv_ext_adc_push(DRV_EXT_ADC_COMMAND command)
{
    ext_adc_data.command_mask |= command;
}
/*******************************************************************************
 * Function:        drv_ext_adc_average
 *
 * Precondition:    none
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none
 *
 * Overview:        Average value of the data in the buffer
 *
 * Notes:           none
 ******************************************************************************/
uint16_t drv_ext_adc_average(uint16_t * buffer, uint16_t samples)
{
    uint16_t i;
    uint32_t temp = 0;
    
    for (i = 0; i < samples; i++)
    {
        temp += buffer[i];
    }
    
    return ((uint16_t) (temp / samples));
}

/*******************************************************************************
 * Function:        drv_ext_adc_dma_callback
 *
 * Precondition:    none
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none
 *
 * Overview:        DMA callback when transfer is complete
 *
 * Notes:           none
 ******************************************************************************/  
void drv_ext_adc_dma_callback( SYS_DMA_TRANSFER_EVENT event, uintptr_t context )
{
    DRV_EXT_ADC_OBJ* tempObj = (DRV_EXT_ADC_OBJ*)context;    

    if( event == SYS_DMA_TRANSFER_COMPLETE )
    {
        tempObj->state = tempObj->previous_state;
    }
    else
    {
        tempObj->state = DRV_EXT_ADC_STATE_ERROR;
        dputs_colour("[RED]ERROR: DMA transfer failed in drv_ext_adc_dma_callback() in drv_ext_adc.c[WHITE]\r\n");
    }
}





static volatile uint adc_timer_counter = -1;

static void drv_ext_adc_start_timer(uint32_t delays)
{
    if(delays == 1){
        //LED1_Set();
        int i;
        for(i=0;i<2500;i++)
        {Nop();}
        //LED1_Clear();
        return;
    }
    adc_timer_counter = (uint32_t)(delays);
}
/* End of function start_timeout                                              */

/**************************************************************************** */
/* Function Name: dspic_transmit_timer                                              */
/*                called on 1KHz interrupt timer to decrement the transmit    */
/*                timer                                                       */
/* ************************************************************************** */
static void adc_ext_timer(void)
{
    if (adc_timer_counter > 0)
    {
        adc_timer_counter--;
    }
    else{}
}

static bool drv_ext_adc_check_timer(void)
{
    adc_ext_timer();
    
    int32_t timer_copy;
    timer_copy = adc_timer_counter;
    if(timer_copy == 0){
        
        return false;
    }
    return true;
}
/* End of function adc_ext_timer    */







/*******************************************************************************
 * Function:        AdcInit
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none
 *
 * Overview:        This function intialises the ADC
 *
 * Notes:           None
 ******************************************************************************/  
bool drv_ext_adc_tasks(void)
{
    switch (ext_adc_data.state)
    {
        case DRV_EXT_ADC_STATE_INIT:
            
            if (drv_ext_adc_initialise())
            {
                ext_adc_data.previous_state = ext_adc_data.state;
                ext_adc_data.state = DRV_EXT_ADC_STATE_ERROR;                
                dputs_colour("[RED]ERROR: ADC initialisation failed in drv_ext_adc_tasks() drv_ext_adc.c[WHITE]\r\n");
            }
            else
            {
                ext_adc_data.previous_state = ext_adc_data.state;
                ext_adc_data.state = DRV_EXT_ADC_STATE_IDLE;   
                ext_adc_data.last_command = 0;
            }

            break;
            
        case DRV_EXT_ADC_STATE_IDLE:

            /* no command is queued - nothing to do */
            if (0U == ext_adc_data.command_mask)
            {
                break;
            }
            
            /* process the next command in the queue */

            /* Initialise ADC */
            if ((ext_adc_data.command_mask & DRV_EXT_ADC_CMD_INIT) > 0)
            {
                /* update the command register */
                ext_adc_data.command_mask &= ~DRV_EXT_ADC_CMD_INIT;
                ext_adc_data.previous_state = ext_adc_data.state;
                ext_adc_data.state = DRV_EXT_ADC_STATE_INIT;                
                break;
            }
            
            /* Determine ADC Offset */
            if ((ext_adc_data.command_mask & DRV_EXT_ADC_CMD_OFFSET) > 0)
            {
                #ifdef DEBUG_EXT_ADC
                dputs_colour("[CYAN]ADC offset command[WHITE]\r\n");
                #endif

                /* update the command register */
                ext_adc_data.command_mask &= ~DRV_EXT_ADC_CMD_OFFSET;
                ext_adc_data.previous_state = ext_adc_data.state;
                ext_adc_data.state = DRV_EXT_ADC_STATE_OFFSET;
                ext_adc_data.substate = DRV_EXT_ADC_OFFSET_STATE_1;
                break;
            }

            /* Determine Zero offset */
            if ((ext_adc_data.command_mask & DRV_EXT_ADC_CMD_ZERO) > 0)
            {
                #ifdef DEBUG_EXT_ADC
                dputs_colour("[CYAN]ADC zero command[WHITE]\r\n");
                #endif

                /* update the command register */
                ext_adc_data.command_mask &= ~DRV_EXT_ADC_CMD_ZERO;
                
                ext_adc_data.previous_state = ext_adc_data.state;
                ext_adc_data.state = DRV_EXT_ADC_STATE_ZERO;
                ext_adc_data.previous_substate = ext_adc_data.substate;
                ext_adc_data.substate = DRV_EXT_ADC_ZERO_INIT;
                drv_ext_adc_start_timer(DRV_EXT_ADC_LONG_DELAY);              
                break;
            }

            /* Acquire Data */
            if ((ext_adc_data.command_mask & DRV_EXT_ADC_CMD_ACQUIRE) > 0)
            {
                /* update the command register */
                ext_adc_data.command_mask &= ~DRV_EXT_ADC_CMD_ACQUIRE;

                drv_ext_adc_sample_start( ext_adc_data.adc_data_buffer, ext_adc_data.adc_data_length );
                break;
            }        
            
            break;
                        
        case DRV_EXT_ADC_STATE_OFFSET:

            drv_ext_adc_offset_task();  
            
            if (DRV_EXT_ADC_OFFSET_STATE_COMPLETE == ext_adc_data.substate)
            {
                ext_adc_data.state = DRV_EXT_ADC_STATE_IDLE;
            }
            else if (DRV_EXT_ADC_OFFSET_STATE_FAILED == ext_adc_data.substate)
            {
                ext_adc_data.state = DRV_EXT_ADC_STATE_IDLE;
            }            
            
            break;
                        
        case DRV_EXT_ADC_STATE_ZERO:    

            drv_ext_adc_zero_task();
            
            if (DRV_EXT_ADC_SUBSTATE_IDLE == ext_adc_data.substate)
            {
                ext_adc_data.zero_running = false;
                #ifdef DEBUG_EXT_ADC
                dputs_colour("[CYAN]ADC zero complete[WHITE]\r\n");
                #endif                
                ext_adc_data.previous_state = ext_adc_data.state;    
                ext_adc_data.state = DRV_EXT_ADC_STATE_IDLE;                
            }
            else if (DRV_EXT_ADC_ZERO_FAILED == ext_adc_data.substate)
            {
                ext_adc_data.zero_running = false;
                ext_adc_data.previous_state = ext_adc_data.state;    
                ext_adc_data.state =  DRV_EXT_ADC_STATE_ERROR;
                dputs_colour("[RED]ERROR: DRV_EXT_ADC_ZERO_FAILED in drv_ext_adc_tasks() in drv_ext_adc.c[WHITE]\r\n");
            }
            
            break;
                        
        case DRV_EXT_ADC_STATE_ACQUIRING:
            break;           
                        
        case DRV_EXT_ADC_STATE_ERROR:
            break;
                        
        default:
            break;
    }

    return ((DRV_EXT_ADC_STATE_IDLE != ext_adc_data.state) || (0 != ext_adc_data.command_mask));
}

/*******************************************************************************
 * Function:        AdcInit
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none
 *
 * Overview:        This function intialises the ADC
 *
 * Notes:           None
 ******************************************************************************/    
bool drv_ext_adc_initialise(void)
{
    #ifdef DEBUG_EXT_ADC
    dputs_colour("[CYAN]drv_ext_adc_initialise[WHITE]\r\n");
    #endif

    SYS_PORT_PinOutputEnable( DRV_EXT_ADC_SHDN );
    SYS_PORT_PinSet( DRV_EXT_ADC_SHDN );    
    
    SYS_PORT_PinOutputEnable( DRV_EXT_ADC_OEN );
    SYS_PORT_PinSet( DRV_EXT_ADC_OEN );    
    
    SYS_PORT_PinOutputEnable( DRV_EXT_ADC_AMP_EN);
    SYS_PORT_PinClear( DRV_EXT_ADC_AMP_EN );   

#ifdef DRV_EXT_EN_DITHER    
    SYS_PORT_PinOutputEnable( DRV_EXT_ADC_DITHER );
    SYS_PORT_PinClear( DRV_EXT_ADC_DITHER );
#else
    SYS_PORT_PinOutputEnable( DRV_EXT_ADC_DITHER );
    SYS_PORT_PinClear( DRV_EXT_ADC_DITHER );    
#endif
    
    SYS_PORT_PinOutputEnable( DRV_EXT_ADC_PGA );
    SYS_PORT_PinClear( DRV_EXT_ADC_PGA  );    

    SYS_INT_SourceDisable( DRV_EXT_ADC_DTR );    
    SYS_INT_SourceStatusClear( DRV_EXT_ADC_DTR );

    SYS_INT_SourceDisable( DRV_EXT_ADC_EXTERNAL_CLOCK );
    SYS_INT_SourceStatusClear( DRV_EXT_ADC_EXTERNAL_CLOCK );   

	return (false);
}
 
/*******************************************************************************
 * Function:        drv_ext_adc_start
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    Keeps system running.
 *
 * Overview:        This function retrieves a series of n samples from the ADC 
 *
 * Notes:           None
 ******************************************************************************/    
bool drv_ext_adc_start(void)
{    
    bool error = true;

    #ifdef DEBUG_EXT_ADC
    dputs_colour("[CYAN]drv_ext_adc_start()[WHITE]\r\n");
    #endif

    if ( ext_adc_data.adc_running == false )
    { 
        if (!DMAC_ChannelIsBusy(DRV_EXT_ADC_DMA_CHANNEL_1))
        {       
            
            #ifdef DEBUG_EXT_ADC
            dputs_colour("[CYAN]Starting ADC...[WHITE]\r\n");
            #endif            

            DMAC_ChannelTransfer(DRV_EXT_ADC_DMA_CHANNEL_1, 
                                 (void *) KVA_TO_PA((void *) &DRV_EXT_ADC_PORT), 
                                 DRV_EXT_ADC_DATA_WIDTH, 
                                 (void *) KVA_TO_PA((void *) ext_adc_data.adc_dma1_buffer), 
                                 DRV_EXT_ADC_DMA1_BUFFER_SIZE << 1, 
                                 DRV_EXT_ADC_DATA_WIDTH);

            SYS_PORT_PinClear(DRV_EXT_ADC_SHDN);
            SYS_PORT_PinClear(DRV_EXT_ADC_OEN);            
            SYS_PORT_PinSet(DRV_EXT_ADC_AMP_EN);
            
            ext_adc_data.adc_running = true;
            error = false;

            #ifdef DEBUG_EXT_ADC
            dputs_colour("[CYAN]Looking good![WHITE]\r\n");
            #endif
        }
    }

    return (error);
}

/*******************************************************************************
 * Function:        drv_ext_adc_start
 *
 * Precondition:    ADC must be running
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    Keeps system running.
 *
 * Overview:        This function retrieves a series of n samples from the ADC 
 *
 * Notes:           None
 ******************************************************************************/    
bool drv_ext_adc_sample_start(void * buffer, uint16_t samples)
{
    if (ext_adc_data.adc_running)
    {     
        DMAC_ChannelCallbackRegister(DRV_EXT_ADC_DMA_CHANNEL_2, (DMAC_CHANNEL_CALLBACK) drv_ext_adc_dma_callback , (uintptr_t) &ext_adc_data);

        DMAC_ChannelTransfer(DRV_EXT_ADC_DMA_CHANNEL_2, 
                             (void *) KVA_TO_PA((void *) ext_adc_data.adc_dma1_buffer),
                             DRV_EXT_ADC_DATA_WIDTH, 
                             (void *) KVA_TO_PA(buffer), 
                             samples * DRV_EXT_ADC_DATA_WIDTH, 
                             DRV_EXT_ADC_DATA_WIDTH);

        ext_adc_data.previous_state = ext_adc_data.state;    
        ext_adc_data.state = DRV_EXT_ADC_STATE_ACQUIRING; 
        return (false);
    }

    return (true);
}

/*******************************************************************************
 * Function:        drv_ext_adc_stop
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none
 *
 * Overview:        This function intialises the ADC
 *
 * Notes:           None
 ******************************************************************************/    
 
bool drv_ext_adc_stop(void)
{   
    #ifdef DEBUG_EXT_ADC
    dputs_colour("[CYAN]Stopping ADC...[WHITE]\r\n");
    #endif        
    
    SYS_PORT_PinSet(DRV_EXT_ADC_OEN);
    SYS_PORT_PinSet(DRV_EXT_ADC_SHDN);
    SYS_PORT_PinClear(DRV_EXT_ADC_AMP_EN);  
    
    if (DMAC_ChannelIsBusy(DRV_EXT_ADC_DMA_CHANNEL_1))
    {
        DMAC_ChannelDisable(DRV_EXT_ADC_DMA_CHANNEL_1);
    }
    
    if (DMAC_ChannelIsBusy(DRV_EXT_ADC_DMA_CHANNEL_2))
    {
        DMAC_ChannelDisable(DRV_EXT_ADC_DMA_CHANNEL_2);
    }

    if (DMAC_ChannelIsBusy(DRV_EXT_ADC_DMA_CHANNEL_3))
    {
        DMAC_ChannelDisable(DRV_EXT_ADC_DMA_CHANNEL_3);
    }    
     
    ext_adc_data.adc_running = false; 
    
    return (ext_adc_data.adc_running);
}
 
/*******************************************************************************
 * Function:        drv_ext_adc_zero
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none
 *
 * Overview:        This function sets the zero offset on the amplifiers
 *
 * Notes:           None
 ******************************************************************************/    
 void drv_ext_adc_zero(void)
{
    ext_adc_data.zero_running = true;
    #ifdef DEBUG_EXT_ADC
    dputs_colour("[CYAN]drv_ext_adc_zero()[WHITE]\r\n");
    #endif
    drv_ext_adc_push(DRV_EXT_ADC_CMD_ZERO);          
}

/*******************************************************************************
 * Function:        calculate_digipot_setting
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none
 *
 * Overview:        This function translates human-readable gain values to digipot values
 *
 * Notes:           None
 ******************************************************************************/    
uint16_t calculate_digipot_setting(double gain)
{
    double Rf;
    double Rg;
    double digipot_resistance;
    uint16_t digipot_setting;

    // for an op-amp, gain = 1 + (Rf / Rg) where Rf is the feedback resistor,
    // and Rg is the resistor connecting the inverting input to ground

    Rf = DRV_EXT_ADC_R2;

    Rg = (Rf / (gain - 1.0f));

    // total up the resistances that comprise Rg
    digipot_resistance = Rg - DRV_EXT_ADC_RS;

    digipot_setting = (uint16_t) ((digipot_resistance - (2 * DRV_EXT_ADC_RW)) / DRV_EXT_ADC_RAB * DRV_EXT_ADC_POS);

    return digipot_setting;
}

 // calculate the gain of the amplifier, this ranges from ~2 to ~13
 // with only 128 settings, this could be replaced by a lookup table
double calculate_amplifier_gain(uint16_t digipot_setting)
{
    double gain;
    double Rf;
    double Rg;
    double digipot_resistance;

    // for an op-amp, gain = 1 + (Rf / Rg) where Rf is the feedback resistor,
    // and Rg is the resistor connecting the inverting input to ground

    Rf = DRV_EXT_ADC_R2;
    digipot_resistance = (2 * DRV_EXT_ADC_RW) + (DRV_EXT_ADC_RAB * ((double) digipot_setting / DRV_EXT_ADC_POS));

    /* total up the resistances that comprise Rg */
    Rg = DRV_EXT_ADC_RS + digipot_resistance;

    gain = 1.0f + (Rf / Rg);

    return (gain);
}

uint16_t get_zero_offset_target_value(uint16_t min_adc, uint16_t max_adc)
{
    switch (ZERO_OFFSET_MODE)
    {
        default:
        case ZERO_OFFSET_AT_CENTRE:
        {
            return ((max_adc >> 1) + (min_adc >> 1));
        }

        case ZERO_OFFSET_AT_BOTTOM:
        {
            return (min_adc + DRV_EXT_ADC_ZERO_XINCR);
        }

        case ZERO_OFFSET_AT_TOP:
        {
            return (max_adc - DRV_EXT_ADC_ZERO_XINCR);
        }
    }
}

/* State machine task to determine the DAC value required to null out the DC offset on the first stage amplifier */
/* Algorithm: */
/* 1) Coarse scan through DAC values to determine maximum and minimum possible ADC values */
/* 2) Coarse scan through DAC values to find the approximate DAC setting where the null point can be found */
/* 3) Medium scan through DAC values found above to find more precise DAC setting where the null point is */
/* 3) Fine scan through DAC values found above to find the exact DAC setting where the null point is */
/* Run time is <200ms */
void drv_ext_adc_zero_task(void)
{   
    static bool laser_initially_on;
	uint16_t mean_adc;                      /* average adc value */
    int32_t centre_delta;                   /* difference between centre ADC value and current value */
    static int32_t min_centre_delta;        /* minimum centre delta found so far */
    static uint16_t dac_value;              /* DAC value */
    static uint16_t dac_for_min_delta;      /* DAC value for minimum centre delta */
	static uint16_t min_adc;                /* minimum found ADC value */
	static uint16_t max_adc;                /* maximum found ADC value */
	static uint16_t target_adc;             /* target "zero point" ADC value */
	static int32_t fine_scan_start;         /* DAC value for start of fine scan */
	static int32_t fine_scan_end;           /* DAC value for end of fine scan */
    
    /* return if the timer has been set and hasn't yet elapsed */
    if (drv_ext_adc_check_timer())
    {
        return;
    }

    switch (ext_adc_data.substate)
    {
        case DRV_EXT_ADC_ZERO_INIT:
        {

            /* set up the DACs */
            drv_dac_set_power_mode(DRV_DAC_PDM_NORMAL);
            drv_dac_set_ldac(DRV_DAC_LDAC_DISABLED);
            drv_dac_set_reference(DRV_DAC_INTERNAL_REF_ON);      
            
            drv_ext_adc_start();
            
            #ifndef DISABLE_LASER_SWITCHING

            if ( LASER_ERROR_NONE != drv_laser_on(true ))
            {
                dprintf_colour("[RED]ERROR: Laser failed to turn on in drv_ext_adc_zero_task() in drv_ext_adc.c.[WHITE]\r\n");
                ext_adc_data.substate = DRV_EXT_ADC_ZERO_FAILED;
                break;
            }
            #endif

            ext_adc_data.substate = DRV_EXT_ADC_ZERO_START;
            break;
        }

        case DRV_EXT_ADC_ZERO_START:
        {
            #ifdef DEBUG_EXT_ADC
            logging_start_timer();
            #endif

            /* set the PGA DAC to its nominal centre value */
            drv_dac_set_value(DRV_DAC_1, DRV_EXT_ADC_DAC_DEFAULT);
            drv_dac_set_value(DRV_DAC_2, DRV_EXT_ADC_DAC_DEFAULT);

#ifdef ADC_ZERO_FIND_MAX_AND_MIN
            /* perform a coarse sweep to find the minimum and maximum ADC values */
            dac_value = 0;
            ext_adc_data.substate = DRV_EXT_ADC_ZERO_GET_MAX_AND_MIN;
            drv_dac_set_value(DRV_DAC_1, dac_value);
            drv_ext_adc_sample_start((void *) ext_adc_data.adc_dma2_buffer, DRV_EXT_ADC_DMA2_BUFFER_SIZE);
            drv_ext_adc_start_timer(DRV_EXT_ADC_SHORT_DELAY);
            min_adc = DRV_EXT_ADC_ADC_MAX;
            max_adc = 0;
#else
            /* perform a coarse sweep to find the approximate zero offset point */
            min_adc = DRV_EXT_ADC_MIN;
            max_adc = DRV_EXT_ADC_MAX;
            target_adc = get_zero_offset_target_value(min_adc, max_adc);
            
            #ifdef DEBUG_EXT_ADC
            dprintf_colour("[GREEN]Target ADC is %d[WHITE]\r\n", target_adc);
            #endif

            /* start a coarse sweep */
            dac_value = DRV_EXT_ADC_DAC_DEFAULT;
            ext_adc_data.substate = DRV_EXT_ADC_ZERO_COARSE_SCAN_START_ADC;
            drv_dac_set_value(DRV_DAC_1, dac_value);
            drv_ext_adc_start_timer(DRV_EXT_ADC_START_DELAY);
            fine_scan_start = -1;
            fine_scan_end = -1;
#endif
            break;
        }

#ifdef ADC_ZERO_FIND_MAX_AND_MIN
        case DRV_EXT_ADC_ZERO_GET_MAX_AND_MIN:
        {
            mean_adc = drv_ext_adc_average(ext_adc_data.adc_dma2_buffer, DRV_EXT_ADC_DMA2_BUFFER_SIZE);
            #ifdef DEBUG_EXT_ADC
            dprintf_colour("[MAGENTA]DAC %5d, Av ADC value %5d[WHITE]\r\n", dac_value, mean_adc);
            #endif

            /* update max and min */
            if (mean_adc < min_adc)
            {
                min_adc = mean_adc;
            }

            if (mean_adc > max_adc)
            {
                max_adc = mean_adc;
            }

            dac_value += DRV_EXT_ADC_ZERO_XINCR;
            if (DRV_EXT_DAC_MAX_OFFSET <= dac_value)
            {
                /* max and min scan completed */
                
                target_adc = get_zero_offset_target_value(min_adc, max_adc);
                        
                #ifdef DEBUG_EXT_ADC
                dprintf_colour("[GREEN]Min ADC is %d[WHITE]\r\n", min_adc);
                dprintf_colour("[GREEN]Max ADC is %d[WHITE]\r\n", max_adc);
                dprintf_colour("[GREEN]Target ADC is %d[WHITE]\r\n", target_adc);
                #endif

                /* start a coarse scan */
                dac_value = DRV_EXT_ADC_DAC_DEFAULT;
                ext_adc_data.substate = DRV_EXT_ADC_ZERO_COARSE_SCAN;
                drv_dac_set_value(DRV_DAC_1, dac_value);
                drv_ext_adc_sample_start((void *) ext_adc_data.adc_dma2_buffer, DRV_EXT_ADC_DMA2_BUFFER_SIZE);
                drv_ext_adc_start_timer(DRV_EXT_ADC_START_DELAY);
                fine_scan_start = -1;
                fine_scan_end = -1;
                break;
            }

            /* continue with the scan */
            drv_dac_set_value(DRV_DAC_1, dac_value);
            drv_ext_adc_sample_start((void *) ext_adc_data.adc_dma2_buffer, DRV_EXT_ADC_DMA2_BUFFER_SIZE);
            drv_ext_adc_start_timer(DRV_EXT_ADC_START_DELAY);
            break;
        }
#endif
        case DRV_EXT_ADC_ZERO_COARSE_SCAN_START_ADC:
        {
            ext_adc_data.substate = DRV_EXT_ADC_ZERO_COARSE_SCAN_GET_DATA;
            drv_ext_adc_sample_start((void *) ext_adc_data.adc_dma2_buffer, DRV_EXT_ADC_DMA2_BUFFER_SIZE);
            break;
        }
        
        case DRV_EXT_ADC_ZERO_COARSE_SCAN_GET_DATA:
        {
            mean_adc = drv_ext_adc_average(ext_adc_data.adc_dma2_buffer, DRV_EXT_ADC_DMA2_BUFFER_SIZE);
            //dprintf_colour("[GREEN]DAC %5d, Av ADC value %5d[WHITE]\r\n", dac_value, mean_adc);

            /* check to see if this value should be within the fine scan range */
            if ((mean_adc > (min_adc + DRV_EXT_ADC_ZERO_XINCR)) && (mean_adc < (max_adc - DRV_EXT_ADC_ZERO_XINCR)))
            {
                if (-1 == fine_scan_start)
                {
                    fine_scan_start = dac_value;
                }
                else
                {
                    fine_scan_end = dac_value;
                }
            }

            dac_value += DRV_EXT_ADC_ZERO_LINCR;
            
            if (DRV_EXT_DAC_MAX_OFFSET <= dac_value || mean_adc == 0)
            {
                if (fine_scan_start < 0)
                {
                    dprintf_colour("[RED]ERROR: Failed to find starting point for medium sweep in DRV_EXT_ADC_ZERO_COARSE_SCAN_GET_DATA in drv_ext_adc.c.[WHITE]\r\n");
                    ext_adc_data.substate = DRV_EXT_ADC_ZERO_FAILED;
                    break;
                }

                if (fine_scan_end < 0)
                {
                    fine_scan_end = fine_scan_start;
                }

                /* widen the scan to make sure that we're covered */
                if (fine_scan_start > DRV_EXT_ADC_ZERO_XINCR)
                {
                    fine_scan_start -= DRV_EXT_ADC_ZERO_XINCR;
                }

                if (fine_scan_end < DRV_EXT_DAC_MAX_OFFSET)
                {
                    fine_scan_end += DRV_EXT_ADC_ZERO_XINCR;
                }                

                #ifdef DEBUG_EXT_ADC
                dprintf_colour("[GREEN]Medium sweep start %ld, end %ld[WHITE]\r\n", fine_scan_start, fine_scan_end);
                #endif

                /* start the medium scan */
                dac_value = fine_scan_start;
                ext_adc_data.substate = DRV_EXT_ADC_ZERO_MEDIUM_SCAN_START_ADC;
                drv_dac_set_value(DRV_DAC_1, dac_value);
                drv_ext_adc_start_timer(DRV_EXT_ADC_START_DELAY);
                min_centre_delta = DRV_EXT_ADC_MAX;
                break;
            }

            /* continue with the coarse scan */
            ext_adc_data.substate = DRV_EXT_ADC_ZERO_COARSE_SCAN_START_ADC;
            drv_dac_set_value(DRV_DAC_1, dac_value);
            drv_ext_adc_start_timer(DRV_EXT_ADC_START_DELAY);
            break;
        }

        case DRV_EXT_ADC_ZERO_MEDIUM_SCAN_START_ADC:
        {
            dac_value += DRV_EXT_ADC_ZERO_MINCR;

            /* medium scan complete? */
            if (dac_value >= fine_scan_end)
            {
                if(min_centre_delta == DRV_EXT_ADC_MAX)
                {
                    ext_adc_data.state = DRV_EXT_ADC_STATE_ERROR;                
                    dprintf_colour("[RED]ERROR: min_centre_delta=DRV_EXT_ADC_MAX in DRV_EXT_ADC_ZERO_MEDIUM_SCAN_START_ADC[WHITE]\r\n");
                }
                /* start fine scan */
                fine_scan_start = dac_for_min_delta + 50;
                fine_scan_end = dac_for_min_delta - 50;   
                #ifdef DEBUG_EXT_ADC
                dprintf_colour("[GREEN]Fine sweep start %ld, end %ld[WHITE]\r\n", fine_scan_start, fine_scan_end);
                #endif
                dac_value = fine_scan_start;
                min_centre_delta = DRV_EXT_ADC_MAX;
                ext_adc_data.substate = DRV_EXT_ADC_ZERO_FINE_SCAN_START_ADC;
                drv_dac_set_value(DRV_DAC_1, dac_value);
                drv_ext_adc_start_timer(DRV_EXT_ADC_START_DELAY);
                break;
            }

            /* continue with the medium scan */
            ext_adc_data.substate = DRV_EXT_ADC_ZERO_MEDIUM_SCAN_GET_DATA;
            drv_ext_adc_sample_start((void *) ext_adc_data.adc_dma2_buffer, DRV_EXT_ADC_DMA2_BUFFER_SIZE);
            break;
        }


        case DRV_EXT_ADC_ZERO_MEDIUM_SCAN_GET_DATA:
        {
            mean_adc = drv_ext_adc_average(ext_adc_data.adc_dma2_buffer, DRV_EXT_ADC_DMA2_BUFFER_SIZE);
            centre_delta = target_adc - mean_adc;
            
            #ifdef DEBUG_EXT_ADC
            dprintf_colour("[GREEN]Av ADC value %d[WHITE]\r\n", mean_adc);
            dprintf_colour("[GREEN]Centre delta value is %d[WHITE]\r\n", centre_delta);
            #endif

            centre_delta = abs(centre_delta);

            if (centre_delta < min_centre_delta)
            {
                min_centre_delta = centre_delta;
                dac_for_min_delta = dac_value;
            }           

            if( ( mean_adc > 0U ) && ( mean_adc < DRV_EXT_ADC_ZERO_MTHRESH ) )
            {
                if(min_centre_delta == DRV_EXT_ADC_MAX)
                {
                    ext_adc_data.state = DRV_EXT_ADC_STATE_ERROR;                
                    dprintf_colour("[RED]ERROR: min_centre_delta=DRV_EXT_ADC_MAX in DRV_EXT_ADC_ZERO_MEDIUM_SCAN_GET_DATA[WHITE]\r\n");
                }
                /* start fine scan */
                fine_scan_start = dac_for_min_delta - 50;
                fine_scan_end = dac_for_min_delta + 50;   
                #ifdef DEBUG_EXT_ADC
                dprintf_colour("[GREEN]Fine sweep start %ld, end %ld[WHITE]\r\n", fine_scan_start, fine_scan_end);
                #endif
                min_centre_delta = DRV_EXT_ADC_MAX;
                ext_adc_data.substate = DRV_EXT_ADC_ZERO_FINE_SCAN_START_ADC;
                dac_value = fine_scan_start;
                drv_dac_set_value(DRV_DAC_1, dac_value);
                drv_ext_adc_start_timer(DRV_EXT_ADC_SHORT_DELAY);
                break;
            }

            //dprintf_colour("[GREEN]Min centre delta value is %d[WHITE]\r\n", min_centre_delta);
            ext_adc_data.substate = DRV_EXT_ADC_ZERO_MEDIUM_SCAN_START_ADC;
            drv_dac_set_value(DRV_DAC_1, dac_value);
            drv_ext_adc_start_timer(DRV_EXT_ADC_SHORT_DELAY);
            
            break;
        }

        case DRV_EXT_ADC_ZERO_FINE_SCAN_START_ADC:
        {
            dac_value += DRV_EXT_ADC_ZERO_SINCR;

            /* fine scan complete? */
            if (dac_value >= fine_scan_end)
            {
                if(min_centre_delta == DRV_EXT_ADC_MAX)
                {
                    ext_adc_data.state = DRV_EXT_ADC_STATE_ERROR;                
                    dprintf_colour("[RED]ERROR: min_centre_delta=DRV_EXT_ADC_MAX in DRV_EXT_ADC_ZERO_FINE_SCAN_START_ADC[WHITE]\r\n");
                }
               /* set up DAC 1 with the value determined that nulls out the DC offset */
                drv_dac_set_value(DRV_DAC_1, dac_for_min_delta);
                #ifdef DEBUG_EXT_ADC
                dputs_colour("[GREEN]Fine scan complete[WHITE]\r\n");                  
                #endif                  
                ext_adc_data.substate = DRV_EXT_ADC_ZERO_COMPLETE;
                break;
            }

            /* continue with the fine scan */
            ext_adc_data.substate = DRV_EXT_ADC_ZERO_FINE_SCAN_GET_DATA;
            drv_ext_adc_sample_start((void *) ext_adc_data.adc_dma2_buffer, DRV_EXT_ADC_DMA2_BUFFER_SIZE);
            break;
        }

        case DRV_EXT_ADC_ZERO_FINE_SCAN_GET_DATA:
        {
            mean_adc = drv_ext_adc_average(ext_adc_data.adc_dma2_buffer, DRV_EXT_ADC_DMA2_BUFFER_SIZE);
            centre_delta = target_adc - mean_adc;
            
            #ifdef DEBUG_EXT_ADC
            dprintf_colour("[GREEN]Av ADC value %d[WHITE]\r\n", mean_adc);           
            dprintf_colour("[GREEN]Centre delta value is %d[WHITE]\r\n", centre_delta);
            #endif

            centre_delta = abs(centre_delta);
            
            if( ( mean_adc > 0U ) && ( mean_adc < DRV_EXT_ADC_ZERO_LTHRESH ) )
            {
                #ifdef DEBUG_EXT_ADC
                dputs_colour("[GREEN]Fine scan complete[WHITE]\r\n");                 
                #endif  

                ext_adc_data.substate = DRV_EXT_ADC_ZERO_COMPLETE;
                break;
            }            

            if (centre_delta < min_centre_delta)
            {
                min_centre_delta = centre_delta;
                dac_for_min_delta = dac_value;
            }

            #ifdef DEBUG_EXT_ADC
            dprintf_colour("[GREEN]Min centre delta value is %d[WHITE]\r\n", min_centre_delta);
            #endif
            ext_adc_data.substate = DRV_EXT_ADC_ZERO_FINE_SCAN_START_ADC;
            drv_dac_set_value(DRV_DAC_1, dac_value);
            drv_ext_adc_start_timer(DRV_EXT_ADC_SHORT_DELAY);
            break;
        }

        case DRV_EXT_ADC_ZERO_COMPLETE: 
        {
            #ifdef DEBUG_EXT_ADC              
            dprintf_colour("[GREEN]DAC 1 setting is %d[WHITE]\r\n", dac_for_min_delta);               
            log_elapsed_time("[PURPLE]Zero offset time taken: ");          
            #endif           

            drv_ext_adc_stop();

            #ifndef DISABLE_LASER_SWITCHING    
            if (!laser_initially_on)
            {
                drv_laser_off();
            }
            #endif                
            
            ext_adc_data.previous_substate = ext_adc_data.substate;
            ext_adc_data.substate = DRV_EXT_ADC_SUBSTATE_IDLE;
            break;
        }
        
        case DRV_EXT_ADC_ZERO_FAILED:   
        default:
        {
            drv_ext_adc_stop();
            
            #ifndef DISABLE_LASER_SWITCHING    
            drv_laser_off();
            #endif                

            break;
        }
    }
}

/*******************************************************************************
 * Function:        drv_ext_adc_set_channel
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none
 *
 * Overview:        This function sets the ADC offsets
 *
 * Notes:           None
 ******************************************************************************/
bool drv_ext_adc_set_channel(DRV_EXT_ADC_INDEX channel)
{
    bool error = true;
    
    if (channel < DRV_EXT_ADC_CHANNELS_PER_DEVICE)
    {
        if( (DRV_EXT_ADC_STATE_INIT == ext_adc_data.state) || (DRV_EXT_ADC_STATE_IDLE == ext_adc_data.state) )
        {
            ext_adc_data.adc_channel = channel;
                           
            error = false;
        }
    }
    
    return (error);
 } 
 
/*******************************************************************************
 * Function:        drv_ext_adc_offset
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none
 *
 * Overview:        This function sets the ADC offsets
 *
 * Notes:           None
 ******************************************************************************/    
void drv_ext_adc_offset(void)
{
    #ifdef DEBUG_EXT_ADC
    dputs_colour("[CYAN]drv_ext_adc_offset()[WHITE]\r\n");
    #endif
    drv_ext_adc_push(DRV_EXT_ADC_CMD_OFFSET);               
}

/*******************************************************************************
 * Function:        drv_ext_adc_offset_task
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none
 *
 * Overview:        This function sets the ADC offsets
 *
 * Notes:           None
 ******************************************************************************/ 
void drv_ext_adc_offset_task(void)
{  
    uint16_t temp_dac_1 = drv_dac_get_value(DRV_DAC_1);
    uint16_t temp_dac_2 = drv_dac_get_value(DRV_DAC_2);

    /* if we're waiting for a timer return immediately if it hasn't elapsed */
    if (drv_ext_adc_check_timer())
    {
        return;
    }

    switch (ext_adc_data.substate)
    {
        case DRV_EXT_ADC_OFFSET_STATE_1:
            
            #ifndef DISABLE_LASER_SWITCHING    
            drv_laser_on(true );
            #endif             

            drv_ext_adc_start(); 

            dputs_colour("[YELLOW]DRV_EXT_ADC_OFFSET_STATE_1[WHITE]\r\n");
            drv_dac_set_value(DRV_DAC_1, DRV_EXT_DAC_MAX_OFFSET);
            ext_adc_data.previous_substate = ext_adc_data.substate;
            ext_adc_data.substate = DRV_EXT_ADC_OFFSET_STATE_2;
            drv_ext_adc_start_timer(DRV_EXT_ADC_START_DELAY);
            break;

        case DRV_EXT_ADC_OFFSET_STATE_2:
            dputs_colour("[YELLOW]DRV_EXT_ADC_OFFSET_STATE_2[WHITE]\r\n");
            drv_dac_set_value( DRV_DAC_2, DRV_EXT_DAC_MIN_OFFSET );
            ext_adc_data.previous_substate = ext_adc_data.substate;
            ext_adc_data.substate = DRV_EXT_ADC_OFFSET_STATE_3;
            drv_ext_adc_start_timer(DRV_EXT_ADC_START_DELAY);
            break;

        case DRV_EXT_ADC_OFFSET_STATE_3:
            dputs_colour("[YELLOW]DRV_EXT_ADC_OFFSET_STATE_3[WHITE]\r\n");
            //DelayMs(1L);
            ext_adc_data.adc_offset[ext_adc_data.adc_channel] = 0L;
            ext_adc_data.previous_substate = ext_adc_data.substate;
            ext_adc_data.substate = DRV_EXT_ADC_OFFSET_STATE_4;
            drv_ext_adc_start_timer(DRV_EXT_ADC_START_DELAY);
            break;

        case DRV_EXT_ADC_OFFSET_STATE_4:
            dputs_colour("[YELLOW]DRV_EXT_ADC_OFFSET_STATE_4[WHITE]\r\n");
            drv_ext_adc_sample_start((void*) ext_adc_data.adc_dma2_buffer, DRV_EXT_ADC_DMA2_BUFFER_SIZE);
            
            ext_adc_data.previous_substate = ext_adc_data.substate;    
            ext_adc_data.substate = DRV_EXT_ADC_OFFSET_STATE_5;
            break;

        case DRV_EXT_ADC_OFFSET_STATE_5:
            dputs_colour("[YELLOW]DRV_EXT_ADC_OFFSET_STATE_5[WHITE]\r\n");
            ext_adc_data.adc_offset[ext_adc_data.adc_channel] = drv_ext_adc_average( ext_adc_data.adc_dma2_buffer, DRV_EXT_ADC_DMA2_BUFFER_SIZE );

            drv_dac_set_value( DRV_DAC_1, temp_dac_1 );
            ext_adc_data.previous_substate = ext_adc_data.substate;
            ext_adc_data.substate = DRV_EXT_ADC_OFFSET_STATE_6;
            drv_ext_adc_start_timer(DRV_EXT_ADC_START_DELAY);
            break;

        case DRV_EXT_ADC_OFFSET_STATE_6:
            dputs_colour("[YELLOW]DRV_EXT_ADC_OFFSET_STATE_6[WHITE]\r\n");
            drv_dac_set_value(DRV_DAC_2, temp_dac_2);
            ext_adc_data.previous_substate = ext_adc_data.substate;
            ext_adc_data.substate = DRV_EXT_ADC_OFFSET_STATE_COMPLETE;
            break;            

        case DRV_EXT_ADC_OFFSET_STATE_COMPLETE:
            dputs_colour("[YELLOW]DRV_EXT_ADC_OFFSET_STATE_COMPLETE[WHITE]\r\n");
            
            drv_ext_adc_stop();           

            #ifndef DISABLE_LASER_SWITCHING    
            drv_laser_off();
            #endif 

            ext_adc_data.previous_substate = ext_adc_data.substate;
            ext_adc_data.substate = DRV_EXT_ADC_SUBSTATE_IDLE;
    
            break;

        case DRV_EXT_ADC_OFFSET_STATE_FAILED:
            
            drv_ext_adc_stop();             
            
            #ifndef DISABLE_LASER_SWITCHING   
            drv_laser_off();
            #endif      
            
            dputs_colour("[YELLOW]DRV_EXT_ADC_OFFSET_STATE_FAILED[WHITE]\r\n");
            break;
            
        default:
            break;
    }
}

/*******************************************************************************
 * Function:        drv_ext_adc_triggered_samples
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    Keeps system running.
 *
  * 
 * Overview:        This function retrieves a series of n samples from the ADC 
 *
 * Notes:           None
 ******************************************************************************/    
bool drv_ext_adc_triggered_sample(void* buffer, uint16_t samples, bool sync)
{    
    bool error = true;

    if (!DMAC_ChannelIsBusy(DRV_EXT_ADC_DMA_CHANNEL_3))
    {
        ext_adc_data.adc_dma1_buffer = buffer;
        ext_adc_data.adc_data_length = samples;

        if (NULL != buffer)
        {
            if (samples < DRV_EXT_ADC_ADC_MAX_SAMPLES)
            {
                DMAC_ChannelTransfer(DRV_EXT_ADC_DMA_CHANNEL_3, 
                                     (void *) KVA_TO_PA((void *) ext_adc_data.adc_dma1_buffer), 
                                     DRV_EXT_ADC_DATA_WIDTH, 
                                     (void *) KVA_TO_PA((void *) ext_adc_data.adc_data_buffer),
                                     ext_adc_data.adc_data_length * DRV_EXT_ADC_DATA_WIDTH, 
                                     DRV_EXT_ADC_DATA_WIDTH);

                if (sync)
                {
                    DMAC_ChannelDisable(DRV_EXT_ADC_DMA_CHANNEL_3);
                }

                ext_adc_data.previous_state = ext_adc_data.state;    
                ext_adc_data.state =  DRV_EXT_ADC_STATE_ACQUIRING;

                error = false;
            }
        }
    }

    return (error);
}

/*******************************************************************************
 * Function:        drv_ext_adc_sample
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    Keeps system running.
 *
 * Overview:        This function retrieves a series of n samples from the ADC 
 *
 * Notes:           None
 ******************************************************************************/    
bool drv_ext_adc_sample(void * buffer, uint16_t samples)
{    
    bool error = true;

    if (DRV_EXT_ADC_STATE_IDLE == ext_adc_data.state)
    { 
        if (!DMAC_ChannelIsBusy(DRV_EXT_ADC_DMA_CHANNEL_2))
        {
            ext_adc_data.adc_data_buffer = (uint16_t *) buffer;
            ext_adc_data.adc_data_length = samples; 

            if (NULL != buffer)
            {
                if (samples < 65536U)
                {
                    drv_ext_adc_push(DRV_EXT_ADC_CMD_ACQUIRE);     
                    error = false;
                }
            }
        }
    }

    return (error);
}

/*******************************************************************************
 * Function:        drv_ext_adc_get_buffer
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none.
 *
 * Overview:        This function returns a pointer to the ADC DMA buffer.
 *
 * Notes:           None
 ******************************************************************************/    
void * drv_ext_adc_get_buffer(void)
{  
    return ((void *) ext_adc_data.adc_dma1_buffer);
}

/*******************************************************************************
 * Function:        drv_ext_adc_get_offset
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none.
 *
 * Overview:        This function returns a pointer to the ADC DMA buffer.
 *
 * Notes:           None
 ******************************************************************************/    
bool drv_ext_adc_get_value(uint16_t * value)
{  
    bool success = false;                 
    
    if (ext_adc_data.adc_running)
    { 
        *value = ext_adc_data.adc_dma1_buffer[0];
    }
    else
    {
        *value = 0U;
    }

    return (success);
}

/*******************************************************************************
 * Function:        drv_ext_adc_get_offset
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none.
 *
 * Overview:        This function returns a pointer to the ADC DMA buffer.
 *
 * Notes:           None
 ******************************************************************************/    
uint16_t drv_ext_adc_get_offset(DRV_EXT_ADC_INDEX channel)
{  
    return ( ext_adc_data.adc_offset[channel] );
}

/*******************************************************************************
 * Function:        drv_ext_adc_get_offset
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none.
 *
 * Overview:        This function returns a pointer to the ADC DMA buffer.
 *
 * Notes:           None
 ******************************************************************************/    
uint16_t drv_ext_adc_get_zero(DRV_EXT_ZERO_OFFSET_INDEX index)
{  
    return (  drv_dac_get_value(index) );
}

/*******************************************************************************
 * Function:        drv_ext_adc_busy
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none.
 *
 * Overview:        Check if the driver is busy.
 *
 * Notes:           None
 ******************************************************************************/  
bool drv_ext_adc_busy(void)
{
    if( ( ext_adc_data.command_mask == 0U ) && ( ext_adc_data.adc_running == 0U ) )
    {
        return false;
    }
    else
    {
        return true;
    }
}
/*******************************************************************************
 * Function:        drv_ext_adc_zero_busy
 *
 * Precondition:    None
 *
 * Input:           none
 *
 * Output:          none
 *
 * Returns:         none
 *
 * Side Effects:    none.
 *
 * Overview:        Check if the driver is busy.
 *
 * Notes:           None
 ******************************************************************************/  
bool drv_ext_adc_zero_busy(void)
{
    return ext_adc_data.zero_running;
}
/*******************************************************************************/