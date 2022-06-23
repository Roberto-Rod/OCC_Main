/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "drv_laser.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

static LASER_DATA laserData =
{
    .state = LASER_OFF,
    .previous_state = LASER_OFF,
    .error = LASER_ERROR_NONE,       
    .timeout = DRV_LASER_TIMOUT,
};
/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

static void drv_laser_off_callback(uintptr_t context);

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */





static uint drv_laser_timer_counter = -1;

static void drv_laser_start_timer(uint32_t delays)
{
    drv_laser_timer_counter = delays;
}
/* End of function start_timeout                                              */

/**************************************************************************** */
/* Function Name: cancel_timeout                                              */
/*                cancel timer for timeout of ACK message reception           */
/* ************************************************************************** */
static void cancel_timeout(void)
{
    drv_laser_timer_counter = -1;
}
/* End of function cancel_timeout                                             */

/**************************************************************************** */
/* Function Name: dspic_transmit_timer                                              */
/*                called on 1KHz interrupt timer to decrement the transmit    */
/*                timer                                                       */
/* ************************************************************************** */
void drv_laser_timer(void)
{
    static bool armed = false;
    if (drv_laser_timer_counter > 0)
    {
        drv_laser_timer_counter--;
        armed = true;
    }
    
    if(drv_laser_timer_counter == 0 && armed)
    {
        armed = false;
        drv_laser_off_callback(0);
    }
    
}
/* End of function adc_ext_timer    */







/*******************************************************************************
 * Function:        void drv_laser_init(void)
 *                  Initialise the laser driver
 ******************************************************************************/
LASER_ERRORS drv_laser_init( void )
{
    laserData.state = LASER_INIT,                                                // Configure the laser data
    laserData.previous_state = LASER_OFF,
    laserData.error = LASER_ERROR_NONE,       
    laserData.timeout = DRV_LASER_TIMOUT,
            
    SYS_PORT_PinOutputEnable( LASER_ENABLE_PIN );                                   // Configure the control pins
    SYS_PORT_PinWrite(LASER_ENABLE_PIN, (bool)LASER_OFF);
    SYS_PORT_PinInputEnable( LASER_STATE_PIN );
    

    
    /* Check the laser control line is low and the laser is OFF */
    if( ( SYS_PORT_PinRead(LASER_STATE_PIN) == (bool)LASER_ON ) || ( SYS_PORT_PinLatchRead(LASER_ENABLE_PIN) == (bool)LASER_ON ) )
    {
        dputs_colour("[RED]ERROR: Laser initialisation failed.[WHITE]\r\n");
        laserData.error = LASER_FAIL_INIT;
        laserData.previous_state = laserData.state;
        laserData.state = LASER_ERROR;         
    }
    else
    {
        #ifdef DEBUG_LASER 
        dputs_colour("[YELLOW]Laser driver initialised.[WHITE]\r\n");  
        #endif

        laserData.previous_state = laserData.state;
        laserData.state = LASER_OFF;           
    }
    
    return laserData.error;
}
/*******************************************************************************
 * Function:        void drv_laser_off(void)
 *                  Turn off the LASER
 ******************************************************************************/
LASER_ERRORS drv_laser_off(void)
{
#ifdef DISABLE_LASER_SWITCHING
    return  LASER_ERROR_NONE;  
#endif    
    
    /* turn off the LASER */
    SYS_PORT_PinWrite(LASER_ENABLE_PIN, (bool)LASER_OFF);

    /* wait for the safety circuit to stabilise */
    blocking_delay(30);

    if (false == SYS_PORT_PinRead(LASER_STATE_PIN))
    {
        laserData.previous_state = laserData.state;
        laserData.state = LASER_OFF;
        #ifdef DEBUG_LASER 
        dputs_colour("[GREEN]LASER successfully turned off[WHITE]\r\n");
        #endif
    }
    else
    {
        laserData.previous_state = laserData.state;
        laserData.state = LASER_ERROR;            
        laserData.error = LASER_FAIL_OFF;
        #ifdef DEBUG_LASER 
        dputs_colour("[RED]The LASER is still ON, the safety circuit may be disabled.[WHITE]\r\n");        
        #endif
    }

    cancel_timeout();
    
    return laserData.error;
}

/*******************************************************************************
 * Function:        void drv_laser_on(void)
 *                  Turn on the LASER and check for an error
 ******************************************************************************/
LASER_ERRORS drv_laser_on( bool enable  )
{
    
#ifdef DISABLE_LASER_SWITCHING
    /* turn on the LASER */
    SYS_PORT_PinWrite(LASER_ENABLE_PIN, (bool)LASER_ON);    
    return  LASER_ERROR_NONE;  
#endif      
    
    drv_laser_start_timer(10000);
    

    if( laserData.error == LASER_ERROR_NONE )                                   // If no error occurred turn on the laser
    {
        #ifdef DEBUG_LASER
        dputs_colour("[YELLOW]Turning the LASER on ...[WHITE]\r\n");
        #endif

        /* turn on the LASER */
        SYS_PORT_PinWrite(LASER_ENABLE_PIN, (bool)LASER_ON);
        
        #ifdef DISABLE_LASER_CHECK
        laserData.previous_state = laserData.state;
        laserData.state = LASER_ON;        
        dputs_colour("[YELLOW]Turning the LASER on (Laser check disabled)[WHITE]\r\n");
        return (laserData.error);
        #else           

        /* wait for the safety circuit to stabilise */
        blocking_delay(30);

        
        /* check the safety circuit to ensure the laser is on*/
        if ( true == SYS_PORT_PinRead(LASER_STATE_PIN) )
        {
            laserData.previous_state = laserData.state;
            laserData.state = LASER_ON;
            #ifdef DEBUG_LASER 
            dputs_colour("[GREEN]LASER successfully turned on.[WHITE]\r\n");
            #endif
        }
        else
        {
            laserData.previous_state = laserData.state;
            laserData.state = LASER_ERROR;            
            laserData.error = LASER_FAIL_ON;
            #ifdef DEBUG_LASER 
            dputs_colour("[RED]The LASER safety circuit has tripped.[WHITE]\r\n");        
            #endif
        }
        #endif 
    }
    
    return (laserData.error);
}
/*******************************************************************************
 * Function:        LASER_ERRORS drv_laser_get_error( void  )
 *                  Retrieve the laser error code
 ******************************************************************************/
LASER_ERRORS drv_laser_get_error( void  )
{
    return (laserData.error);    
}

static void drv_laser_off_callback(uintptr_t context)
{
    #ifdef DEBUG_LASER
    dputs_colour("[RED]Laser timer timeout[WHITE]\r\n");
    #endif

    /* turn off the LASER */
    drv_laser_off();
    Stop_Scanning();
    
    #ifdef DEBUG_LASER
    dputs_colour("[YELLOW]Laser timer elapsed [WHITE]\r\n");
    #endif
}
/* *****************************************************************************
 End of File
 */
