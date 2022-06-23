/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    scan.c

  @Summary
    Scan functions.

  @Description
    Scanning.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "scan.h"

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

extern APP_DATA appData;

static _SCAN_DATA  scanData =
{
    .measurement_index = 0U,    
    .scan_progress = 0U,
    .scanning = false,
    .status_received = false,
    .status_timer_elapsed = false,
    .total_blocks = 0,
    .valid_blocks = 0,
    .z_position = 0U,
    .scan_timer = SYS_TIME_HANDLE_INVALID
};

#ifdef LOG_SCAN_TIMING
static uint32_t find_pupil_total = 0;
static uint32_t find_pupil_count = 0;
static uint32_t find_pupil_max = 0;

static uint32_t find_pk1_image_total = 0;
static uint32_t find_pk1_image_count = 0;
static uint32_t find_pk1_image_max = 0;
#endif

const char *npda_error_strings[] = {"Successful Measurement",               // 0  
                                        "Error: Calibration",                   // 1
                                        "Error: Unspecified Failure",           // 2 
                                        "Warning: Low Block Count",             // 3    
                                        "Warning: Low PC peaks",                // 4 
                                        "Warning: Low PC Peaks and Block Count",// 5      
                                        "Warning: High Standard Deviation",     // 6
                                        "Error: Insufficient Block Count",      // 7
                                        "Error: Poor or Missing PC Peaks",      // 8    
                                        "Error: High Standard Deviation" };     // 9
    
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

static bool app_find_pk2_image(bool enable, _CIRCLE* circle);

/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */


usability_metrics_t usability_metrics;

uint32_t scan_time = 0;
uint32_t press_to_scan_time = 0;
uint32_t avg_Z = 0;
static laString scan_dur_Str;
static laString p_to_s_dur_Str;
static laString Z_Str;
static laString avgT_Str;

static char scan_dur_string[50];
static char p_to_s_dur_string[50];
static char Z_string[50];
static char avg_scan_time_string[50];

void show_scan_duration(void){
    uint32_t scan_duration = _CP0_GET_COUNT() - scan_time; 
    float scan_duration_s = scan_duration / 100000000.0;
    usability_metrics.scan_time = scan_duration_s;
    
    usability_metrics.number_of_started_scans = appData.scan_start_btn_press_counter;
    
    usability_metrics.number_of_stopped_scans = appData.scan_start_btn_press_counter - appData.scan_stop_btn_press_counter;
    
//    
//    usability_metrics.number_of_started_scans = appData.scan_start_btn_press_counter - usability_metrics.last_number_of_presses_start;
//    usability_metrics.last_number_of_presses_start = appData.scan_start_btn_press_counter;
//    
//    usability_metrics.number_of_stopped_scans = appData.scan_stop_btn_press_counter - usability_metrics.last_number_of_presses_stop;
//    usability_metrics.last_number_of_presses_stop = appData.scan_stop_btn_press_counter;
    
    sprintf(p_to_s_dur_string, "Scan D1: %.1f, Press To Scan D2: %.1f", usability_metrics.scan_time, usability_metrics.press_to_scan_time );
    sprintf(scan_dur_string, "Position Z1: %d, Gain G1: %.1f", usability_metrics.avg_Z, usability_metrics.avg_gain );
    
    sprintf(Z_string, "Temperature T1: %.0f, T2: %.0f, T3: %.0f",
            usability_metrics.temperature, usability_metrics.temperature_high_peak, usability_metrics.temperature_low_peak);
    sprintf(avg_scan_time_string, "Button B1: %d, B2: %d", usability_metrics.number_of_started_scans, usability_metrics.number_of_stopped_scans);
    
    scan_dur_Str = laString_CreateFromCharBuffer(scan_dur_string, &Apertura_14);
    p_to_s_dur_Str = laString_CreateFromCharBuffer(p_to_s_dur_string, &Apertura_14);
    Z_Str = laString_CreateFromCharBuffer(Z_string, &Apertura_14 );
    avgT_Str = laString_CreateFromCharBuffer(avg_scan_time_string, &Apertura_14);
    
    laLabelWidget_SetText((laLabelWidget*)TimeScanningTookLW, scan_dur_Str);
    laLabelWidget_SetText((laLabelWidget*)TimeToScanLW, p_to_s_dur_Str);
    laLabelWidget_SetText((laLabelWidget*)AverageZInScanLW, Z_Str);
    laLabelWidget_SetText((laLabelWidget*)AverageTempInScanLW, avgT_Str);
    
    laString_Destroy(&scan_dur_Str);
    laString_Destroy(&p_to_s_dur_Str);
    laString_Destroy(&Z_Str);
    laString_Destroy(&avgT_Str);
    
    
    //dprintf_colour("[RED]-> scan duration: %.2f[WHITE]\r\n",scan_duration_s);
    //dprintf_colour("[RED]-> AVG Z: %d[WHITE]\r\n",avg_Z);
}
void press_to_scan_duration(void){
    uint32_t duration = _CP0_GET_COUNT() - appData.press_to_scan_timer; 
    float durationF = duration / 100000000.0;
    usability_metrics.press_to_scan_time = durationF;
    //dprintf_colour("[RED]-> press-to-scan duration: %.2f[WHITE]\r\n",durationF);
}
void calc_avg_z(int32_t z){
    static float average;
    if(z == -99){
        average=0;
        return;
    }
    average += (z - average) / 5.0f;
    usability_metrics.avg_Z = (uint32_t)average;
}
void calc_avg_g(int32_t g){
    static float average;
    if(g == -99){
        average=0;
        return;
    }
    average += (g - average) / 5.0f;
    usability_metrics.avg_gain = (float)average;
}

/* get the stored scan settings */
void read_scan_settings(_SCAN_SETTINGS *scan_settings)
{  
    scan_settings->comparator_reference_voltage = settings_get_comparator_reference_voltage();
    scan_settings->peak_thresholds[0] = settings_get_peak_1_threshold_voltage();
    scan_settings->peak_thresholds[1] = settings_get_peak_2_threshold_voltage();
    scan_settings->separation_limits[0] = settings_get_minimum_separation();
    scan_settings->separation_limits[1] = settings_get_maximum_separation();
    scan_settings->fwhm_limits[0] = settings_get_minimum_fwhm();
    scan_settings->fwhm_limits[1] = settings_get_maximum_fwhm();
    scan_settings->laser_power = settings_get_laser_power();
    scan_settings->amplifier_gain = settings_get_amplifier_gain();
    scan_settings->total_scans = settings_get_total_scans();
}

/*******************************************************************************
  Function:
    

  Remarks:
    start a scan
*******************************************************************************/
void scan_reset(void)
{
    scanData.scan_progress = 0U;
    scanData.total_blocks = 0U;
    scanData.valid_blocks = 0U;
    scanData.scanning = false;
    scanData.status_received = false;
    scanData.status_timer_elapsed = false;
    scanData.z_position = 0U;
    scan_update_progress(1);
}
/*******************************************************************************
  Function:
    

  Remarks:
    start a scan
*******************************************************************************/
bool scan_start(void)
{
    if( !SYS_TIME_DelayIsComplete(scanData.scan_timer)  )
    {
        #ifdef DEBUG_SCAN
        dputs_colour("[GREEN]Destroying scan timer[WHITE]\r\n");
        #endif        
        
        SYS_TIME_TimerDestroy( scanData.scan_timer );
    }   
      
    /* read the settings */
    read_scan_settings(&scanData.scan_settings);

    if( scanData.measurement_index == 0U )
    {
        memset((void*)&scanData.measurements[0], 0, sizeof(_NPDA_MEASUREMNT)); 
        memset((void*)&scanData.measurements[1], 0, sizeof(_NPDA_MEASUREMNT));
        memset((void*)&scanData.measurements[2], 0, sizeof(_NPDA_MEASUREMNT));
        memset((void*)&scanData.measurements[3], 0, sizeof(_NPDA_MEASUREMNT));
    }                        

    /* Reset scan progress parameters */
    scan_reset();        

    /* limit to 10 seconds */
    scanData.scan_timer =  SYS_TIME_CallbackRegisterMS ( (SYS_TIME_CALLBACK) &scan_status_check, NULL, SCANNING_STATUS_TIMEOUT, SYS_TIME_SINGLE );        

    if( scanData.scan_timer == SYS_TIME_HANDLE_INVALID  )
    {
        #ifdef DEBUG_SCAN
        dputs_colour("[RED]Scan timer error[WHITE]\r\n");
        #endif                

        appData.prevstate = appData.state;
        appData.state = APP_STATE_ERROR;
        sprintf(appData.error_string, "Scanning timer error\n" );    

        return false;
    }
    else
    {
        scanData.scanning = true;

        #ifdef DEBUG_SCAN
        dputs_colour("[PINK]Sending scan command[WHITE]\r\n");
        #endif              

  
        scan_time = _CP0_GET_COUNT();
        press_to_scan_duration();
        calc_avg_z(-99);//reseting average
        calc_avg_g(-99);//reseting average
        /* send the command to trigger a scan */
        send_command_to_PDAB(COMMAND_START_SCAN, NULL, 0);
    }

    return true;
}
/*******************************************************************************
  Function:
    

  Remarks:
    stop scanning
*******************************************************************************/
bool scan_status_check(void)
{  
    if( scanData.status_received == true )
    {
        #ifdef DEBUG_SCAN
        dputs_colour("[GREEN]Scan status received[WHITE]\r\n");
        #endif           
        
        scanData.status_timer_elapsed = true;
        
        SYS_TIME_DelayIsComplete(scanData.scan_timer);
        
        scanData.scan_timer =  SYS_TIME_CallbackRegisterMS ( (SYS_TIME_CALLBACK) &scan_stop, NULL, SCANNING_TIMEOUT, SYS_TIME_SINGLE );
        return true;
    }
    else
    {
        appData.prevstate = appData.state;
        appData.state = APP_STATE_ERROR;
        sprintf(appData.error_string, "Scanning failed to initiate\n" );    
        scan_stop();
        return false;
    }
}
/*******************************************************************************
  Function:
    

  Remarks:
    stop scanning
*******************************************************************************/
void scan_stop(void)
{ 
    /* Reset scan progress parameters */
    scan_update_progress(2);
    scan_reset();

    #ifdef DEBUG_SCAN
    dputs_colour("[GREEN]Sending stop scanning command to LSC[WHITE]\r\n");
    #endif

    send_command_to_PDAB(COMMAND_STOP_SCAN, NULL, 0U); 
    
    if(  SYS_TIME_DelayIsComplete( scanData.scan_timer )  )
    {
        #ifdef DEBUG_SCAN
        dputs_colour("[YELLOW]Scan timer elapsed[WHITE]\r\n");;
        #endif        
    }
    else if( scanData.scan_timer != SYS_TIME_HANDLE_INVALID )
    {
        #ifdef DEBUG_SCAN
        dputs_colour("[GREEN]Destroying scan timer[WHITE]\r\n");
        #endif        
        
        SYS_TIME_TimerDestroy( scanData.scan_timer );
    }
    
    scanData.scan_timer = SYS_TIME_HANDLE_INVALID;    
    
    app_set_scan_state(false);
    
    #ifdef DEBUG_SCAN
    dputs_colour("[GREEN]Stop scanning[WHITE]\r\n");
    #endif    
}
/*******************************************************************************
  Function:
    

  Remarks:
    process a packet of received scan data
*******************************************************************************/
void scan_header_received(_SCAN_HEADER* header)
{ 
    if( header != NULL )
    {
        app_set_laser_state(header->Status.Flags.LON, header->Status.Flags.LPON);//update laser icon
        if(header->Status.Count > 0)
        {
            scanData.z_position = header->Measurement.Peak[0].Position;             // Update Z position for the alignment UI
            app_update_alignment_ui();
        }
        
        calc_avg_z((int32_t)header->Measurement.Peak[0].Position);
        calc_avg_g((int32_t)header->Status.Gain);
        #ifdef DEBUG_SCAN        
        dprintf_colour("[GREEN]Z Position: %d[WHITE]\r\n", scanData.z_position );    
        #endif
        
        appData.status.DAB.Flags.Word = header->Status.Flags.Word;              // Update status
        appData.status_updated = true;  
        scanData.status_received = true;    
        
        #ifdef DEBUG_SCAN
        dputs_colour("[GREEN]Scan status received[WHITE]\r\n");
        #endif 

        if( ( scanData.measurement_index <= 2 ) && ( true == header->complete ) )                                            // Check the measurement complete flag
        {       
            scanData.measurements[scanData.measurement_index].thickness = header->Measurement.Thickness[0];
            scanData.measurements[scanData.measurement_index].std = header->Measurement.Precision[0]; 
            scanData.measurements[scanData.measurement_index].valid_blocks = header->Blocks;
            scanData.measurements[scanData.measurement_index].total_blocks = header->Measurement.Count;
            scanData.measurements[scanData.measurement_index].error = (NPDA_RETVAL) header->Status.Error;      

            scanData.scanning = false;

            if(  SYS_TIME_DelayIsComplete( scanData.scan_timer )  )
            {
                #ifdef DEBUG_SCAN
                dputs_colour("[YELLOW]Scan timer elapsed[WHITE]\r\n");
                #endif
            }
            else if( scanData.scan_timer != SYS_TIME_HANDLE_INVALID )
            {
                SYS_TIME_TimerDestroy( scanData.scan_timer ); 
            }
#ifdef PAUSE_CAMERA
            DRV_CAMERA_OVM7692_Pause(sysObj.drvOVM7692);             
#endif
                       
//            app_set_scan_state(false);   

            scan_process_measurements( scanData.measurements[scanData.measurement_index].valid_blocks );  

            set_pca9530_leds_off();            
            
            #ifdef DEBUG_SCAN
            dprintf_colour("[GREEN]Refractive Index: %3.4f[WHITE]\r\n", settings_get_refractive_index() );
            dprintf_colour("[GREEN]Separation: %3.3f[WHITE]\r\n", header->Measurement.Separation[0] );
            dprintf_colour("[GREEN]Thickness: %3.3f[WHITE]\r\n", header->Measurement.Thickness[0] );
            dprintf_colour("[GREEN]SD: %3.3f[WHITE]\r\n", header->Measurement.Precision[0] ); 
            #endif        
            return;
        }         
    } 
    else
    {
        return;
    }
    
    if( true == scanData.scanning )                                       // Check header is valid or ignore any data received once we've stopped scanning  
    {
        #ifdef DEBUG_SCAN
        if(!header->valid)
            dprintf_colour("[ORANGE]Scan: %d[WHITE]\r\n", header->Status.Count );
        else
            dprintf_colour("[GREEN]Scan: %d[WHITE]\r\n", header->Status.Count );       

        dprintf_colour("[BROWN]Direction: %d[WHITE]\r\n", header->Status.Flags.Direction );
  
        float p1_position = 0.00f;      
        float p1_amplitude = 0.00f;
        float p1_fwhm = 0.00f;      
        float p2_position = 0.00f;
        float p2_amplitude = 0.00f; 
        float p2_fwhm = 0.00f;    

        p1_position = (float)header->Measurement.Peak[0].Position * SCAN_RESOLUTION;
        p1_fwhm = (float)header->Measurement.Peak[0].FWHM * SCAN_RESOLUTION;       
        p2_position = (float)header->Measurement.Peak[1].Position * SCAN_RESOLUTION;
        p2_amplitude = (float)header->Measurement.Peak[1].Amplitude * SCAN_ADC_CONVERSION;  
        p2_fwhm = (float)header->Measurement.Peak[1].FWHM * SCAN_RESOLUTION; 

        dprintf_colour("[BROWN]Peak 1: Position: %1.3f um Amplitude: %1.3f V FWHM: %1.3f[WHITE]\r\n", p1_position, p1_amplitude, p1_fwhm );
        dprintf_colour("[BROWN]Peak 2: Position: %1.3f um Amplitude: %1.3f V FWHM: %1.3f [WHITE]\r\n", p2_position, p2_amplitude, p2_fwhm );
        #endif         

        if (header->valid)
        { 
            scanData.valid_blocks++;

            #ifndef DISABLE_AUDIO                      
            play_notification(play_SCAN);
            #endif    
        }
    }
}

/*******************************************************************************
  Function:
    

  Remarks:

*******************************************************************************/
void scan_process_measurements( uint16_t scans )
{         
    /* display for n seconds */
    if(scanData.measurement_index == 2U)
    {
        if( ( scanData.measurements[2].thickness > SCAN_MIN_SEPARATION ) && ( scanData.measurements[2].std < THICKNESS_STD_MAX ) )
        { 
            float temp[3];
            temp[0] = scanData.measurements[0].thickness;
            temp[1] = scanData.measurements[1].thickness;
            temp[2] = scanData.measurements[2].thickness;

            scanData.measurements[3].thickness = calculate_mean(temp, 3, 0);
            scanData.measurements[3].std = calculate_stdev(temp, scanData.measurements[3].thickness, 3, 0);
            scanData.measurements[3].total_blocks = 3;
            scanData.measurements[3].valid_blocks = 3;          
            
            if( scanData.measurements[3].std <= THICKNESS_STD_TARGET)
            {
                scanData.measurements[3].error = SUCCESS;                
                scanData.measurement_index = 0U;
            }
            else
            {
                scanData.measurements[3].error = ERROR_SPREAD_TOO_HIGH;
                scanData.measurement_index = 0U;
            }
            
            show_scan_duration();
            app_update_measurement_value( &scanData.measurements[1], 1, 128, true );                     
            app_update_measurement_value( &scanData.measurements[2], 2, 128, true ); 
            app_update_measurement_value( &scanData.measurements[3], 3, 255, true );
            
            app_start_measurement_display_timer( MEASUREMENT_DISPLAY_TIMEOUT );
            dprintf_colour("[MAGENTA]Measurement %d. %.1f/%.1f[WHITE]\r\n", 2, scanData.measurements[2].thickness, scanData.measurements[2].std); 
            dprintf_colour("[MAGENTA]Measurement completed. %.1f/%.1f[WHITE]\r\n", scanData.measurements[3].thickness, scanData.measurements[3].std);  
            return;
        }
        else
        {
            show_scan_duration();
            app_update_measurement_value( &scanData.measurements[1], 1, 128, true );                     
            app_update_measurement_value( &scanData.measurements[2], 2, 255, true );           
            dprintf_colour("[RED]Measurement out of range or too high SD.[WHITE]\r\n"); 
        }
    }
    else if(scanData.measurement_index == 1U)
    {               
        if( ( scanData.measurements[1].thickness > SCAN_MIN_SEPARATION ) && ( scanData.measurements[1].std < THICKNESS_STD_MAX ) )
        {    
            scanData.measurement_index++;
        }
        else
        {
            dprintf_colour("[RED]Measurement out of range or too high SD.[WHITE]\r\n"); 
        }     
        show_scan_duration();
        app_update_measurement_value( &scanData.measurements[0], 0, 128, true ); 
        app_update_measurement_value( &scanData.measurements[1], 1, 255, true );         
        dprintf_colour("[MAGENTA]Measurement %d. %.1f/%.1f[WHITE]\r\n", 1, scanData.measurements[1].thickness, scanData.measurements[1].std); 
    }
    else if(scanData.measurement_index == 0U)
    {
        if( ( scanData.measurements[0].thickness > SCAN_MIN_SEPARATION ) && ( scanData.measurements[0].std < THICKNESS_STD_MAX ) )
        {                               
            scanData.measurement_index++;
        }
        else
        {
            dprintf_colour("[RED]Measurement out of range or too high SD.[WHITE]\r\n"); 
        }
        
        show_scan_duration();
        app_update_measurement_value( &scanData.measurements[0], 0, 255, true );    
        dprintf_colour("[MAGENTA]Measurement %d. %.1f/%.1f[WHITE]\r\n", 0, scanData.measurements[0].thickness, scanData.measurements[0].std);      
    }

    app_start_measurement_display_timer( MEASUREMENT_DISPLAY_TIMEOUT_MIN );
    dprintf_colour("[MAGENTA]Measurement processed.[WHITE]\r\n");        
    
    return;
}
/*******************************************************************************
  Function:
    

  Remarks:
    show / hide the scanning progress bar and set its value.
*******************************************************************************/
void scan_update_progress(int clear)
{
    static uint16_t progress = 0;
    static uint16_t prev_progress = 0;
    
    if(clear == 1){
        progress = 0;
        prev_progress = 0;
        return;
    }
    
    uint16_t cur_progress = (scanData.valid_blocks * 100U) / BLOCKS_PER_MEASURMENT;
    
    if(progress == cur_progress){
        return;
    }
    
    if( scanData.valid_blocks == 10U )
    {
        scanData.scan_progress = 100;
    }
    else if( scanData.valid_blocks > 0U )  
    {
        progress += (cur_progress - progress)/5;
        scanData.scan_progress = progress;//(uint16_t)((scanData.valid_blocks * 100U) / BLOCKS_PER_MEASURMENT);
    }
    else
        scanData.scan_progress = 0U;  
    prev_progress = cur_progress;
}
/*******************************************************************************
  Function:
    

  Remarks:
    Retrieve the measurement progress 
*******************************************************************************/
uint16_t scan_get_progress( void )
{ 
    return scanData.scan_progress;
}
/*******************************************************************************
  Function:
    

  Remarks:
    Retrieve the measurement progress 
*******************************************************************************/
uint32_t scan_get_elapsed_time( void )
{ 
    uint32_t counter = 0U;
    
    if( scanData.scan_timer != SYS_TIME_HANDLE_INVALID )    
    {
        if( SYS_TIME_TimerPeriodHasExpired ( scanData.scan_timer ) )
        {
            counter = 0U;
        }
        else
        {
            if( SYS_TIME_SUCCESS != SYS_TIME_TimerCounterGet( scanData.scan_timer, &counter ) )
            {
                counter = 0U;
            }
        }
    }
    
    if( scanData.status_timer_elapsed == true )
    {
        return SYS_TIME_CountToMS( counter ) + SCANNING_STATUS_TIMEOUT;
    }
    else
    {
        return SYS_TIME_CountToMS( counter );
    }
}
/*******************************************************************************
  Function:
    

  Remarks:
    Retrieve the measurement progress 
*******************************************************************************/
uint8_t scan_get_remaining_time_percentage( void )
{ 
    uint32_t counter = scan_get_elapsed_time();
    
    return ( ( counter * 100U ) / ( SCANNING_TIMEOUT + SCANNING_STATUS_TIMEOUT ) );
}
/*******************************************************************************
  Function:
    

  Remarks:
    Retrieve the measurement progress 
*******************************************************************************/
uint16_t scan_get_z_position( void )
{ 
    
    return scanData.z_position;
}
/*******************************************************************************
  Function:
    

  Remarks:
    Retrieve the measurement progress 
*******************************************************************************/
uint32_t scan_get_measurement_index( void )
{ 
    return scanData.measurement_index;
}
/*******************************************************************************
  Function:
    

  Remarks:
    Retrieve the measurement progress 
*******************************************************************************/
void scan_reset_measurement_index( void )
{ 
    scanData.measurement_index = 0U;
}
/*******************************************************************************
  Function:
    

  Remarks:
    Retrieve the measurement progress 
*******************************************************************************/
_NPDA_MEASUREMNT* scan_get_measurement( uint8_t index )
{ 
    if( index >= MAX_MEASUREMENT_COUNT )
    {
        return NULL;
    }
    else
    {
        return &scanData.measurements[index];        
    }
}
/*******************************************************************************
  Function:
    

  Remarks:

*******************************************************************************/

bool app_process_frame( bool en, _CIRCLE* circle )
{ 
    bool valid = false;
    
    if (APP_SCREEN_MAIN == laContext_GetActiveScreenIndex())
    {
        #define NEW_IMAGEPROCESSING
        #ifdef NEW_IMAGEPROCESSING
        valid = app_find_pk2_image( en, circle );
        #else
        valid = app_find_pk1_image( en, circle );
        #endif
        
        if(drv_pca9530_fading_active())
        {
            valid = false;//override valid if still fading LEDs
        }
        
        if(valid)
        {
            SYS_PORT_PinWrite(IP_VALID_PIN, valid);
        }
    }    
    
    scan_update_progress(0);
    return ( valid );
}
static inline void draw_pixel(DRV_CAMERA_FRAME* frameptr, int16_t x, int16_t y, int16_t value)
{
    frameptr->Line[y].Pixel[x] = value;
}
static uint16_t find_circle(uint16_t* image, uint16_t width, _WINDOW* window, uint16_t threshold, _CIRCLE* circle) 
{
    #ifndef STRUCTURE_AND_INITS
    //defining struct to have all variables in static memory
    typedef struct {
        int16_t i, j, k, l, x1, y1;//loops indexes:
        uint16_t startx;//really
        uint16_t starty;
        bool good_alignment;
        bool scanning_prev;
        bool once;
        int16_t global_y_offset;
        int16_t lut_x[6];
        int16_t lut_x1[2];
        int16_t lut_x2[2];
        int16_t lut_x3[2];
        
        int16_t count_y_series[3];
        int16_t start_y_series[3];
        int16_t offsets_y_series[3];

        int16_t lut_y1[32];
        int16_t lut_y2[32];
        int16_t lut_y3[32];

        int16_t count_y;
        int16_t start_y;
        
        int16_t tresholds[3];
        int16_t tresholds_def[3];
        
        int16_t brightness_mid_avg;
        
        int16_t inner_sum, middle_sum, outer_sum;
    }Image_Processing_t;
    
    static Image_Processing_t IP = {
        .once = false,
        .global_y_offset = -15,
        .lut_x = {-7,7,-18,18,-29,29},
        .count_y_series = {6,16,16},
        .start_y_series = {25,18,-10},
        .offsets_y_series = {5,2,4},
        .tresholds = {0,0,0},
        .tresholds_def = {70,80,80}
    };
    
    
    
    if(IP.once == false){
        IP.once = true;
        IP.startx = window->start_x + (window->width / 2U);
        IP.starty = window->start_y + (window->height / 2U);
        for(IP.i=0;IP.i<2;IP.i++){
            IP.lut_x1[IP.i] = IP.lut_x[IP.i];
            IP.lut_x2[IP.i] = IP.lut_x[IP.i+2];
            IP.lut_x3[IP.i] = IP.lut_x[IP.i+4];
        }
        IP.i=0;
        IP.count_y = IP.count_y_series[IP.i];
        IP.start_y = IP.start_y_series[IP.i];
        for(IP.j=0; IP.j < IP.count_y;IP.j++){
            IP.lut_y1[IP.j] = IP.start_y + IP.j * IP.offsets_y_series[IP.i];
            IP.lut_y1[IP.j + IP.count_y] = IP.lut_y1[IP.j];
        }
        IP.i=1;
        IP.count_y = IP.count_y_series[IP.i];
        IP.start_y = IP.start_y_series[IP.i];
        for(IP.j=0; IP.j < IP.count_y;IP.j++){
            IP.lut_y2[IP.j] = IP.start_y + IP.j * IP.offsets_y_series[IP.i];
            IP.lut_y2[IP.j + IP.count_y] = IP.lut_y2[IP.j];
        }
        IP.i=2;
        IP.count_y = IP.count_y_series[IP.i];
        IP.start_y = IP.start_y_series[IP.i];
        for(IP.j=0; IP.j < IP.count_y;IP.j++){
            IP.lut_y3[IP.j] = IP.start_y + IP.j * IP.offsets_y_series[IP.i];
            IP.lut_y3[IP.j + IP.count_y] = IP.lut_y3[IP.j];
        }
    }
    #endif
    
    IP.good_alignment = false;
    IP.inner_sum = 0;
    IP.middle_sum = 0;
    IP.outer_sum = 0;

    DRV_CAMERA_FRAME* frameptr = (DRV_CAMERA_FRAME*) image;

    if (IP.scanning_prev == false && scanData.scanning == true) {
        circle->radius = 10;
    }
    IP.scanning_prev = scanData.scanning;
    //#define IP_VISUAL_DEBUG
    #ifdef IP_VISUAL_DEBUG
    uint16_t rangex = 75, rangey = 75;
    
    _RGB_565_PIXEL _pixel;
    _RGB_565_PIXEL _pixel_red;
    _RGB_565_PIXEL _pixel_b;

    _pixel.red = 0; //blue
    _pixel.green = 0b11111; //green/yelowish
    _pixel.blue = 0;

    _pixel_red.red = 0; //good blue
    _pixel_red.green = 0;
    _pixel_red.blue = 0b11111; //good red

    _pixel_b.red = 0b11111; //blue
    _pixel_b.green = 0;
    _pixel_b.blue = 0;
    #endif
    

    
    int16_t inner_sum = 0, middle_sum = 0, outer_sum = 0;
    uint16_t pixels_intensity_sum = 0;
    int16_t corrective_treshold = 0;
    for (IP.l = 0; IP.l < 2; IP.l++) {
        IP.i=1;
        
        for (IP.k = 0; IP.k < IP.count_y_series[IP.i]*2; IP.k++) {
            IP.x1 = IP.lut_x2[IP.l];
            IP.y1 = IP.lut_y2[IP.k] + IP.global_y_offset;
            pixels_intensity_sum += rgb_565_to_gs_approximation(frameptr->Line[IP.starty + (int16_t) IP.y1].Pixel[IP.startx + (int16_t) IP.x1]);
        }
        
        corrective_treshold = 40 - pixels_intensity_sum / 150;
    }
    
    IP.tresholds[0] = IP.tresholds_def[0] - corrective_treshold;
    IP.tresholds[1] = IP.tresholds_def[1] - corrective_treshold;
    IP.tresholds[2] = IP.tresholds_def[2] - corrective_treshold;
    
    //dprintf_colour("[RED]PI: %d, CT: %d[WHITE]\r\n", pixels_intensity_sum, corrective_treshold );
    
    
    for (IP.l = 0; IP.l < 2; IP.l++) {
        IP.i=0;
        for (IP.k = 0; IP.k < IP.count_y_series[IP.i]*2; IP.k++) {
            IP.x1 = IP.lut_x1[IP.l];
            IP.y1 = IP.lut_y1[IP.k] + IP.global_y_offset;
            if (rgb_565_to_gs_approximation(frameptr->Line[IP.starty + (int16_t) IP.y1].Pixel[IP.startx + (int16_t) IP.x1]) > IP.tresholds[IP.i]) {
                inner_sum++;
            }
            #ifdef IP_VISUAL_DEBUG
            draw_pixel(frameptr, IP.startx + (int16_t) IP.x1, IP.starty + (int16_t) IP.y1, _pixel_red.word);
            #endif
        }
        IP.i=1;
        for (IP.k = 0; IP.k < IP.count_y_series[IP.i]*2; IP.k++) {
            IP.x1 = IP.lut_x2[IP.l];
            IP.y1 = IP.lut_y2[IP.k] + IP.global_y_offset;
            if (rgb_565_to_gs_approximation(frameptr->Line[IP.starty + (int16_t) IP.y1].Pixel[IP.startx + (int16_t) IP.x1]) > IP.tresholds[IP.i]) {
                middle_sum++;
            }
            #ifdef IP_VISUAL_DEBUG
            draw_pixel(frameptr, IP.startx + (int16_t) IP.x1, IP.starty + (int16_t) IP.y1, _pixel_red.word);
            #endif
        }
        IP.i=2;
        for (IP.k = 0; IP.k < IP.count_y_series[IP.i]*2; IP.k++) {
            IP.x1 = IP.lut_x3[IP.l];
            IP.y1 = IP.lut_y3[IP.k] + IP.global_y_offset;
            if (rgb_565_to_gs_approximation(frameptr->Line[IP.starty + (int16_t) IP.y1].Pixel[IP.startx + (int16_t) IP.x1]) > IP.tresholds[IP.i]) {
                outer_sum++;
            }
            #ifdef IP_VISUAL_DEBUG
            draw_pixel(frameptr, IP.startx + (int16_t) IP.x1, IP.starty + (int16_t) IP.y1, _pixel_red.word);
            #endif
        }
    }

    #ifdef IP_VISUAL_DEBUG
    static int latching = 0;
    #endif
    
    if (middle_sum > 24 && inner_sum < 2 && outer_sum < 2) {
        
        IP.good_alignment = true;
        
        
        #ifdef IP_VISUAL_DEBUG
        if(latching == 0)
        {
            latching = 1;
        }
        
        for (IP.i = -(rangex + 40); IP.i < -(rangex + 20); IP.i++) {
            for (IP.j = -rangey; IP.j < rangey; IP.j++) {
                frameptr->Line[IP.starty + IP.j].Pixel[IP.startx + IP.i] = _pixel_b.word;
            }
        }
        #endif
    }
    #ifdef IP_VISUAL_DEBUG
    else
    {
        latching = 0;
    }
    
    int full_range = rangey*2;
    int rangeO = (int)((full_range * ((float)outer_sum/64.0f))/2.0f);
    int rangeM = (int)((full_range * ((float)middle_sum/64.0f))/2.0f);
    int rangeI = (int)((full_range * ((float)inner_sum/64.0f))/2.0f);
    
    for (IP.i = +(rangex + 10); IP.i < +(rangex + 15);IP. i++) {
        for (IP.j = -rangeO; IP.j < rangeO; IP.j++) {
            frameptr->Line[IP.starty + IP.j].Pixel[IP.startx + IP.i] = _pixel_b.word;
        }
    }
    for (IP.i = +(rangex + 16); IP.i < +(rangex + 21); IP.i++) {
        for (IP.j = -rangeM; IP.j < rangeM; IP.j++) {
            frameptr->Line[IP.starty + IP.j].Pixel[IP.startx + IP.i] = _pixel_red.word;
        }
    }
    for (IP.i = +(rangex + 22); IP.i < +(rangex + 27); IP.i++) {
        for (IP.j = -rangeI; IP.j < rangeI; IP.j++) {
            frameptr->Line[IP.starty + IP.j].Pixel[IP.startx + IP.i] = _pixel_b.word;
        }
    }
    #endif
    
    if (IP.good_alignment == true) {
        return 1;
    }
    return 0;
}

/*******************************************************************************
  Function:
    

  Remarks:

*******************************************************************************/
bool app_find_pk1_image( bool enable, _CIRCLE* circle )
{
    //
#ifdef LOG_SCAN_TIMING       
    uint32_t time_taken;
    uint32_t mean_time_taken;
    logging_start_timer();    
#endif
    
    circle->valid = false;
    circle->visible = false;
    circle->color = (void*) &OverlayRed;
    
    if (enable)
    { 
        uint16_t dx = 0U, dy = 0U;
        uint16_t x[FIND_CIRCLE_MAX_POINTS];
        uint16_t y[FIND_CIRCLE_MAX_POINTS]; 
        uint16_t points;    
        
        points = find_circle_points( (uint16_t*)appData.image->header.dataAddress, DRV_CAMERA_FRAME_WIDTH, &appData.p1_window, PK1_THRESHOLD, x, y ); 

        if( points > CIRCLE_FIT_MIN_POINTS )                                    // Only fit a circle if more than 8 points are found
        {
            if( fit_circle_float( points, x, y, circle ) )                      // Fit a circle to the points found            
            {
                dx = abs( circle->x - CAMERA_CENTRE_X );
                dy = abs( circle->y - CAMERA_CENTRE_Y );
                
                if( dy < PK1_MAX_DECENTRE )     // Check the image is central in the frame
                {
                    if( dx < PK1_MAX_DECENTRE )
                    {                    
                        circle->radius += PK1_LINE_OFFSET;                      // Offset for the fact we detect the edge of the PK image 
                        circle->visible = true;   
                       
                        if( ( circle->radius > PK1_MIN_RADIUS ) && ( circle->radius < PK1_MAX_RADIUS ) )       // If the radius is between 8 and 32 pixels, show fitted circle
                        {
#ifndef DISABLE_IP_RADIUS                             
                            if (abs(circle->radius - settings_get_pk1_target_radius()) < settings_get_pk1_radius_tolerance())
                            {
#endif
                                if( dx < settings_get_pk1_alignment_tolerance() ) 
                                {
                                    if( dy < settings_get_pk1_alignment_tolerance() )
                                    {
                                        circle->color = (void*) &OverlayGreen;
                                        circle->valid = true;
                                    }     
                                }   
#ifndef DISABLE_IP_RADIUS                         
                            }
#endif
                        }                        
                    }
                }
            }
        }     
    }
#ifdef LOG_SCAN_TIMING   
    if (scanData.scanning)
    {
        log_elapsed_time("[PINK]app_find_pk1_image() time taken: ");
        time_taken = log_elapsed_time("[CYAN]app_find_pk1_image() time taken: ");
        find_pk1_image_total += time_taken;
        find_pk1_image_count++;

        if (time_taken > find_pk1_image_max)
        {
            find_pk1_image_max = time_taken;
        }

        mean_time_taken = find_pk1_image_total / find_pk1_image_count;
        dprintf_colour("app_find_pk1_image() mean time taken %d.%02dus\x1B[97m\r\n", mean_time_taken / 100, mean_time_taken % 100);
        dprintf_colour("app_find_pk1_image() max time taken %d.%02dus\x1B[97m\r\n", find_pk1_image_max / 100, find_pk1_image_max % 100);        
    }

//    dprintf_colour("[CYAN]app_find_pk1_image() returning %d[WHITE]\r\n", circle->valid);
#endif
    
    return circle->valid;
}
static bool app_find_pk2_image(bool enable, _CIRCLE* circle) 
{
    circle->valid = true;
    circle->visible = true;
    circle->color = (void*) &OverlayRed;

    if (enable) {
        if (find_circle((uint16_t*) appData.image->header.dataAddress, DRV_CAMERA_FRAME_WIDTH, &appData.p1_window, PK1_THRESHOLD, circle) == 1) {
            return true;
        }
    }
    return false;
}

/* *****************************************************************************
 End of File
 */
