/* ************************************************************************** */
/** @file LRS_tuning.c
 *
 *  @brief LRS tuning file.
 *
 *  @copyright Occuity Limited (c) 2021
 */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include <xc.h>
#include "LRS_tuning.h"
#include "motor_drv.h"
#include "encoder_drv.h"
#include "main.h"
#include "debug.h"
#include "mcc_generated_files/dma.h"
#include "mcc_generated_files/sccp7_tmr.h"

#define SD_MIN_SAT  10
#define SD_RANGE_QTUN    4.5f
#define SD_RANGE_HYST    0.0f   

#define QTUN_RETRY_CNT  5


/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Global Variables                                                  */
/* ************************************************************************** */
/** @brief power supply voltage to motor table consisting dac samples  */
extern uint16_t VM[DAC_SAMPLES];
/** @brief LSC data object defining set LSC parameters and firmware */
extern volatile _LSC_DATA lscData;
/** @brief lsc tuning object consisitng data reqiired for tuning process */
extern volatile _LSC_TUNING_OBJ lsc_tuning;

extern bool scanning; 

#define WAIT_FOR_SCANS_TIMEOUT_MS 100

static volatile uint16_t waiting_for_scans_TO  = WAIT_FOR_SCANS_TIMEOUT_MS; 

static float SD_confidence = SD_RANGE_QTUN; 
static int32_t conf_thresh  =  SCAN_RANGE_DIST_LONG_TUNING_REQ; 

#define Z_BUFF_LEN 8

static z_poles_t z_buff[Z_BUFF_LEN];
static uint16_t z_buff_idx = 0; 
static uint16_t z_buff_cnt = 0; 

static bool z_pos_error = false; 

/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */

inline void clear_z_buffer(void){
    uint16_t i = 0; 
    
    for (i = 0; i < Z_BUFF_LEN; i++){
        
        memset((void*)&z_buff[i], 0, sizeof(z_poles_t));
        
    }
    z_buff_idx = 0; 
    z_buff_cnt = 0; 
    z_pos_error = false; 
}

int32_t  s_abs_32(int32_t val){

    if(val == INT32_MIN){
        return INT32_MAX;
    }
    else{

        return (val<0) ? -val:val;
    }
}


void AdjustPos(int32_t adjust){
    
    if(scanning == false){
        
        _TYPE_BUFFER position;
        position.Short[1] = POS1CNTH;            
        position.Short[0] = POS1CNTL;
        position.Long[0]+= adjust; 
        POS1CNTL = position.Short[0];
        POS1CNTH = position.Short[1];
    }
    
    
    
}

void Check_Make_Z_adjust(void){
    
    if ((lscData.StatusFlags.REF_SET == false) && (lscData.OriginalZOff != INT32_MAX) &&(lscData.MeanScanRange >= SCAN_RANGE)){
        int32_t adjust = lscData.OriginalZOff - lscData.CurrentZOff; 
                   
        AdjustPos(adjust); 
        
        lscData.ScanMaxSDLow +=adjust;
        lscData.ScanMinSDLow +=adjust;

        dprintf("Positions adj(Orig, Curr): %ld (%ld, %ld)\r\n", adjust, lscData.OriginalZOff, lscData.CurrentZOff );
        
        lscData.StatusFlags.REF_SET = true; 
    }
    
}

/* ************************************************************************** */
/** 
 * @brief   Calculate Z offset 
 *
 * @note    Uses the positions sampled in buff if 3 poles present it 
 *          averages the postions, 2 poles it selects the one which is nearest the centre
 * @param   buff    pointer to first element of position sample struct array 
 * @param   buff_len    sample buffer array length 
 * @param   scan_min    average minimum position for scan 
 * @param   scan_max    average maximum position for scan 
 * 
 * @return offset from z pole
 */
/* ************************************************************************** */


#define Z_RANGE_THRESH 10

#define Z_POS_0_OK  0x1
#define Z_POS_1_OK  0x2
#define Z_POS_ERR_NO_POLES -1
#define Z_POS_ERR_HIGH_VAR -2 

int16_t z_pos_offset(z_poles_t* buff, uint16_t buff_len,int32_t scan_min, int32_t scan_max, int32_t* off_dir0 ,int32_t* off_dir1 ){
    
    
    uint16_t i;
    
    z_poles_t* cur;
    //
    uint16_t dir0_val_cnt = 0; ///< Number of valid z pole locations determined in direction 0
    uint16_t dir1_val_cnt = 0; ///< Number of valid z pole locations determined in direction 1
    
    int32_t dir0_val_off[Z_BUFF_LEN] = {0}; ///< Valid Z pole locations looking at samples taken in direction 0 
    int32_t dir1_val_off[Z_BUFF_LEN] = {0}; ///< Valid Z pole locations looking at samples taken in direction 1
    
    int32_t scan_centre = (scan_max +scan_min)/2; 
    
    *off_dir0 = 0; 
    *off_dir1 = 0; 
    
    for(i = 0; i <  buff_len; i++){
        uint16_t j = 0; 
        bool valid_check = true; ///< Valid set of samples
        
        cur = (buff+i); 
        
        if((cur->dir_cnt[0] > 1)&&(dir0_val_cnt < Z_BUFF_LEN)){ //Check if there are at least 2 samples
            // Loop over samples and check they have correct spacing
            int32_t prev_pos = cur->positions[0][0]; 
            for(j = 1; j < cur->dir_cnt[0]; j++){  

                if((prev_pos+LRS_POLE_VAL_MM ) > cur->positions[0][j] ){
                    valid_check = false; 
                    break; 
                }

                prev_pos = cur->positions[0][j]; 
            }
            
        }else{
            
            valid_check = false; 
            
        }
        // If the sampling is valid
        if(valid_check){
            
            if(cur->dir_cnt[0] == 3){
                // Has 3 pole locations so just average 
                dir0_val_off[dir0_val_cnt ] = 0; 
                for(j  = 0; j <cur->dir_cnt[0]; j++ ){
                    
                    dir0_val_off[dir0_val_cnt ] +=cur->positions[0][j]; 
                    
                }
                dir0_val_off[dir0_val_cnt] = dir0_val_off[dir0_val_cnt]/3; 
                dir0_val_cnt = dir0_val_cnt + 1;
            }else{
                // Has 2 pole locations so select the pole closest to the centre of oscillation
                
                
                int32_t pos0_diff = s_abs_32(cur->positions[0][0]-scan_centre); 
                int32_t pos1_diff = s_abs_32(cur->positions[0][1]-scan_centre);

                if(pos0_diff < pos1_diff){

                    dir0_val_off[dir0_val_cnt ] = cur->positions[0][0]; 
                    dir0_val_cnt = dir0_val_cnt + 1;
                    
                }else if(pos0_diff >= pos1_diff){

                    dir0_val_off[dir0_val_cnt ] = cur->positions[0][1]; 
                    dir0_val_cnt = dir0_val_cnt + 1;
                }
                
            }

        }
        // perform similar processing for sampling in direction 1, checks are changed due to position decreasing
        valid_check = true; 
        if((cur->dir_cnt[1] > 1) && (dir1_val_cnt < Z_BUFF_LEN)){
            
            int32_t prev_pos = cur->positions[1][0]; 
            for(j = 1; j < cur->dir_cnt[1]; j++){
                
                // position check adjusted for decreasing position 
                if(prev_pos < (cur->positions[1][j]+LRS_POLE_VAL_MM ) ){
                    valid_check = false; 
                    break; 
                }

                prev_pos = cur->positions[1][j]; 
            }
            
            
        }else{
            
            valid_check = false; 
            
        }
        
        if(valid_check){
            
            if(cur->dir_cnt[1] == 3){
                
                dir1_val_off[dir1_val_cnt ] = 0; 
                for(j  = 0; j <cur->dir_cnt[1]; j++ ){
                    
                    dir1_val_off[dir1_val_cnt ] +=cur->positions[1][j]; 
                    
                }
                dir1_val_off[dir1_val_cnt] = dir1_val_off[dir1_val_cnt]/3; 
                
                dir1_val_cnt = dir1_val_cnt + 1;
            }else{
                // 
                
                
                int32_t pos0_diff = s_abs_32(cur->positions[1][0]-scan_centre); 
                int32_t pos1_diff = s_abs_32(cur->positions[1][1]-scan_centre);

                if(pos0_diff <= pos1_diff){

                    dir1_val_off[dir1_val_cnt ] = cur->positions[1][0]; 
                    dir1_val_cnt = dir1_val_cnt + 1;
                    
                }else if(pos0_diff > pos1_diff){

                    dir1_val_off[dir1_val_cnt ] = cur->positions[1][1]; 
                    dir1_val_cnt = dir1_val_cnt + 1;
                }
                
            }

        }

        dprintf("Buffer %d: %5ld,%5ld,%5ld,%5ld,%5ld,%5ld\r\n",i ,cur->positions[0][0],
                                                    cur->positions[0][1],
                                                    cur->positions[0][2],
                                                    cur->positions[1][0],
                                                    cur->positions[1][1],
                                                    cur->positions[1][2]); 
        
    }
    
    dprintf("Num val z offsets: %d , %d \r\n",dir0_val_cnt, dir1_val_cnt);
    
    
    int32_t dir0_mean = 0; 
    
    int32_t dir1_mean = 0; 

    if((dir0_val_cnt + dir1_val_cnt) < 4 ){
        
        return Z_POS_ERR_NO_POLES; 
    }
    
    for(i  = 0; i < Z_BUFF_LEN; i++){
        
        dprintf("z off: %ld / %ld \r\n",dir0_val_off[i],  dir1_val_off[i]);
        
        if( i < dir0_val_cnt){

            dir0_mean += dir0_val_off[i]; 
        }
        
        if(i < dir1_val_cnt){

            dir1_mean += dir1_val_off[i]; 
            
        }
        
    }
    
    uint32_t dir0_range = UINT32_MAX; 
    uint32_t dir1_range = UINT32_MAX; 
    
    int16_t ret_val = 0; 
    if(dir0_val_cnt > 0){

        dir0_mean = dir0_mean/dir0_val_cnt; 
        *off_dir0  = dir0_mean; 
        dir0_range = 0; 
        for(i  = 0; i< dir0_val_cnt; i++){
            
             dir0_range += s_abs_32(dir0_val_off[i] -dir0_mean); 
        }
        dir0_range = dir0_range/dir0_val_cnt; 
        
        if(dir0_range < Z_RANGE_THRESH){
            
            ret_val = ret_val|Z_POS_0_OK; 
            
        }
    }
    
    if(dir1_val_cnt > 0){
        
        dir1_mean = dir1_mean/dir1_val_cnt;
        *off_dir1  = dir1_mean; 
        dir1_range = 0; 
        for(i  = 0; i< dir1_val_cnt; i++){
            
             dir1_range += s_abs_32(dir1_val_off[i] -dir1_mean); 
        }
        dir1_range = dir1_range/dir1_val_cnt; 
        
        if(dir1_range < Z_RANGE_THRESH){
            
            ret_val = ret_val|Z_POS_1_OK; 
            
        }
        
    }
    dprintf( "Mean Z off(AD): %ld(%lu) / %ld(%lu)\r\n", dir0_mean, dir0_range,dir1_mean ,dir1_range); 

    
    if (ret_val == 0){
        return Z_POS_ERR_HIGH_VAR; 
    }else{
        
        return ret_val; 
        
    }
 
}

/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/** 
 * @brief            Auto Centre. Adjusts the position register such that 0 is 
 *                   the nominal centre of the scan range
 *
 * @note             Called by void DefineLimits(void) if AUTO_CENTRE global variable set
 *
 * @param[in/out]    int32_t min, int32_t max
 *
 * @return           int32_t offset 
 */
/* ************************************************************************** */
int32_t AutoCentre(int32_t min, int32_t max)
{ 
    int32_t offset = 0L;
    
    if ((min != 0L) && (max != 0L))
    {  
        offset = ((min + max) / 2L);

        /** @brief if there is a difference between min and max, read encoder position counter value, move by the offset and set */
        if (abs(offset) > 0L)
        {
            _TYPE_BUFFER position;
            position.Short[1] = POS1CNTH;            
            position.Short[0] = POS1CNTL;
            position.Long[0] -= offset;
            POS1CNTL = position.Short[0];
            POS1CNTH = position.Short[1];   
        }   
    }

    return (offset);
}

/* ************************************************************************** */
/** 
 * @brief            display Define Limits Data Scan Parameters 
 *
 * @note             Called by Tuning_Update_Data and Tuning_Clear_Data
 * 
 * 
 * @return           Scan range 
 */
/* ************************************************************************** */
void log_scan_settings(const char *colour, double prev_freq, double prev_amp)
{ 
    dprintf_colour("[YELLOW]Scan Range: %d\r\n[WHITE]", (int16_t) lscData.MeanScanRange);
    dprintf_colour("[YELLOW]Scan Min/Max (avg): %d/%d\r\n[WHITE]", (int16_t)lscData.MeanScanMin, (int16_t)lscData.MeanScanMax);
    dprintf_colour("[YELLOW]Scan Min/Max (SD): %d/%d\r\n[WHITE]", (int16_t)lscData.MeanMinSD, (int16_t)lscData.MeanMaxSD);
    dprintf_colour("[YELLOW]Scan Confidence bounds(%.2f SDs)Min/Max: %d/%d\r\n[WHITE]", SD_confidence, (int16_t)lscData.ScanMinSDLow, (int16_t)lscData.ScanMaxSDLow);
    dprintf_colour("[YELLOW]Scan Confidence threshold: %ld[WHITE]\r\n", conf_thresh); 
    dprintf_colour("[YELLOW]Scan Offset: %d\r\n[WHITE]", (int16_t) lscData.MeanScanOffset);
    dprintf_colour("%sScan Start/End Limit: %d/%d\r\n[WHITE]", colour, (int16_t) lscData.ScanStart, (int16_t) lscData.ScanStop);
    dprintf_colour("%sMax Scan Range: %d\r\n[WHITE]", colour, (int16_t) lscData.ScanRange);
    dprintf_colour("%sScan Min: %d\r\n[WHITE]", colour, (int16_t) lscData.ScanMin);
    dprintf_colour("%sScan Max: %d\r\n[WHITE]", colour, (int16_t) lscData.ScanMax);
    dprintf_colour("%sCurrent drive frequency: %3.3f\r\n[WHITE]", colour, prev_freq);
    dprintf_colour("%sCurrent drive amplitude: %3.3f\r\n[WHITE]", colour, prev_amp);
}
/* ************************************************************************** */
/** 
 * @brief            Calculation of low bounds of scan range based on scan sample mean and standard deviations 
 *
 * @note             Called by DefineLimits
 * 
 * 
 * @return            
 */
/* ************************************************************************** */
void ScanRangeDistribiutionCalc()
{
    SD_confidence = SD_RANGE_QTUN; 
    if(lscData.StatusFlags.QTUN == false){
        
        SD_confidence = SD_RANGE_QTUN + SD_RANGE_HYST; 
    }
    
    int32_t MaxSD = lscData.MeanMaxSD; 
    
    if( MaxSD  < SD_MIN_SAT){
        
        MaxSD  = SD_MIN_SAT; 
    }
    
    lscData.ScanMaxSDLow =((lscData.MeanScanRange/2) - (SD_confidence*(float) MaxSD )); 
    
    int32_t MinSD = lscData.MeanMinSD; 
    
    if(MinSD < SD_MIN_SAT){
        
        MinSD = SD_MIN_SAT; 
        
    }
    
    lscData.ScanMinSDLow = ((lscData.MeanScanRange/2) - (SD_confidence*(float) MinSD )); 
}

inline bool Adjust_drive_amp(volatile uint32_t* max_amp){
    
    bool ret_val = true; 
    
    if(*max_amp > DAC_VOLTAGE_LIMIT){
        
        *max_amp = DAC_VOLTAGE_LIMIT; 
        
        ret_val = false; 
    }
    
    GenerateDACProfile(lscData.LRAWaveForm, VM, DAC_SAMPLES, DAC_VOLTAGE_MIN, *max_amp ); 
    
    return ret_val; 
}

inline void start_tune_scan_motion(){
    
    lsc_tuning.enc_diff_zero_cnt =0; 
    StartMotion(SCAN_LIMIT, false);
    
}
/* ************************************************************************** */
/** 
 * @brief            Initialisation tuning phase
 *
 * @note             Called by TUNING_PHASE_INIT state of void DefineLimits_task (void)
 *                   state machine
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Tuning_Init(bool complete_reset )
{
    
    waiting_for_scans_TO = 0;
    if(complete_reset == true){

        lsc_tuning.retry =0; 
    }

    /** @brief set minimum position of one interaction to 0 */
    lsc_tuning.minpos = 0;
    /** @brief set maximum position of one interaction to 0 */
    lsc_tuning.maxpos = 0;
    lsc_tuning.new_scan_found = false;
    lsc_tuning.direction = false; // false = increasing; true = decreasing
    /** @brief set previous amplitude to 0 */
    lsc_tuning.tuning_process_flag = TUNING_IN_PROG;
    lsc_tuning.last_encoder_pos = 0;
    lsc_tuning.is_edge_met = EDGE_NOT_MET;
    /** @brief set frequency of the apex of unexpected amplitude to 0 */
    lsc_tuning.apex_freq = 0.0f;
    /** @brief set counter of last scan set with sd within limit to 0 */
    lsc_tuning.last_scan_set_sd_count = 0;
    /** @brief set counter of last scan below threshold 0 */
    lsc_tuning.last_scan_set_below_threshold_count = 0;
    /** @brief set number of cycle to 0 */
    lsc_tuning.cycles=0;
    /* @brief set variables used for mean max, min ranges and mean max, min range standard deviation */
    lsc_tuning.maxpos_avg=0;
    lsc_tuning.minpos_avg=0;
    lsc_tuning.maxpos_sd=0;
    lsc_tuning.minpos_sd=0;
    lsc_tuning.old_pos = 0;
    /** @brief set previous tuning phase to */
    lsc_tuning.prev_tuning_phase = TUNING_PHASE_IDLE;
    /** @brief set previous frequency to 0 */
    lsc_tuning.prev_freq = 0.0f;
    /** @brief set previous amplitude to 0 */
    lsc_tuning.prev_amp = 0L;  
    
    /** @brief clear the configuration, QOE and SLIM flags, set direction flag to forward movement, set scanning parameters to 0*/    
    lscData.StatusFlags.CFG = false;						
    lscData.StatusFlags.DIR = true;
    lscData.StatusFlags.QOE = false;
    lscData.StatusFlags.REF_SET = false; 
    lscData.ScanOffset = 0L;
    lscData.ScanMin = 0L;
    lscData.ScanMax = 0L;
    lscData.ScanRange = 0L; 
    lscData.MeanScanMin = 0L;
    lscData.MeanScanMax = 0L; 
    lscData.MeanScanOffset = 0L;
    lscData.MeanScanRange = 0L;
    lscData.MeanMinSD = 0.0f;
    lscData.MeanMaxSD = 0.0f;
    lscData.CurrentZOff = 0L;

    lscData.LRADriveAMP = lscData.LRAResonantAMP;
    lscData.LRADriveFreq = lscData.LRAResonantFreq;

    /* @brief Set lower limit. Set limit of backward movement. Set triggering encoder interrupt backward movement count */
    lscData.ScanStart -= LIMIT_OFFSET;
    QEI1LECH = lscData.Words.ScanStart[1];                 
    QEI1LECL = lscData.Words.ScanStart[0];

    /** @brief Set upper limit. Set limit of forward movement. Set triggering encoder interrupt forward movement count */
    lscData.ScanStop += LIMIT_OFFSET;   
    QEI1GECH = lscData.Words.ScanStop[1];                   
    QEI1GECL = lscData.Words.ScanStop[0]; 
    
    clear_z_buffer(); 
    lsc_tuning.zpos_retry_cnt = 0; 
    
    lsc_tuning.zpos_dir =   (uint8_t)((lscData.ZOff_diff_dir >>8) & 0x3); 
    lsc_tuning.zpos_cur_dir = 0; 
    lsc_tuning.zpos_diff =  (int8_t)(lscData.ZOff_diff_dir & 0xFF); 
    
    dprintf_colour("Initial drive frequency: %3.3f\r\n", (double)lscData.LRADriveFreq );
    dprintf_colour("Initial drive amplitude: %3.3f\r\n", (double) lscData.LRADriveAMP);
    dprintf_colour("Loaded  Z: Off: %ld, Dir: %u, Diff0-1: %i\r\n[WHITE]", lscData.OriginalZOff,lsc_tuning.zpos_dir-1,lsc_tuning.zpos_diff ); 
    
    lsc_tuning.qtune_retry_cnt = QTUN_RETRY_CNT; 

    
    /** @brief generate DAC motor power profile */

    Adjust_drive_amp(&lscData.LRADriveAMP ); 
#ifdef  DEBUG_TUNING
    dprintf_colour("VM Start/Mid/End: %d / %d / %d\r\n", VM[1], VM[DAC_SAMPLES/2], VM[DAC_SAMPLES -2] ); 
#endif  
    
    enable_z_INT(); 
    /** @brief start motion with set scanning limits and set QEI enabled flag */
    start_tune_scan_motion();
    
    /** @brief get position */
    lsc_tuning.old_pos = GetPosition();
    lsc_tuning.tuning_phase = TUNING_DELAY;
    lsc_tuning.motor_movement_delay = START_DELAY;
    lsc_tuning.motor_state = MOTOR_STARTED; 
}
/* ************************************************************************** */
/** 
 * @brief            Collect Data tuning phase
 *
 * @note             Called by TUNING_PHASE_COLLECT_DATA state of 
 *                   void DefineLimits_task state(void) machine
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Tuning_Collect_Data(void)
{
    /** @brief update Scan Min if current position is smaller */
    if (lsc_tuning.minpos < lscData.ScanMin)
    {
        lscData.ScanMin = lsc_tuning.minpos; 
    }
    /** @brief update Scan Max if current position is bigger */
    else if (lsc_tuning.maxpos  > lscData.ScanMax)
    {
        lscData.ScanMax = lsc_tuning.maxpos;       
    }
    lsc_tuning.cycles++;
    if(lsc_tuning.cycles > 1)
    {
        lsc_tuning.maxpos_sd += ((double)lsc_tuning.maxpos) * ((double)lsc_tuning.maxpos);
        lsc_tuning.maxpos_avg += (double)lsc_tuning.maxpos;
        lsc_tuning.minpos_sd += ((double)lsc_tuning.minpos) * ((double)lsc_tuning.minpos);
        lsc_tuning.minpos_avg += (double)lsc_tuning.minpos;
        
        
                
        if(get_z_positions(&z_buff[z_buff_idx])){
#ifdef DEBUG_Z_POS
           
            dprintf("Got Z: %5ld,%5ld,%5ld,%5ld,%5ld,%5ld\r\n", z_buff[z_buff_idx].positions[0][0],
                                                                z_buff[z_buff_idx].positions[0][1],
                                                                z_buff[z_buff_idx].positions[0][2],
                                                                z_buff[z_buff_idx].positions[1][0],
                                                                z_buff[z_buff_idx].positions[1][1],
                                                                z_buff[z_buff_idx].positions[1][2]); 
            
#endif           
            if(z_buff_cnt < Z_BUFF_LEN){
                
                z_buff_cnt++;
            }
            
            z_buff_idx++;
            
            if(z_buff_idx == Z_BUFF_LEN){
                
                z_buff_idx = 0; 
            }
        }
        
        
    }
//    dprintf_colour("%d/%d\r\n", lsc_tuning.minpos, lsc_tuning.maxpos);              
}

/* ************************************************************************** */
/** 
 * @brief            Calculate mean of tuning scan min position, max position, scan min 
 *                   position standard deviation and scan max position standard deviation
 *
 * @note             Called by TUNING_PHASE_COLLECT_DATA state of 
 *                   void DefineLimits_task(void) state machine
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Calculate_Tuning_Data_Mean(void)
{
    /** @brief update previous frequency data before modification */
    lsc_tuning.prev_freq = lscData.LRADriveFreq;            
    /** @brief update previous amplitude data before modification */
    lsc_tuning.prev_amp = lscData.LRADriveAMP;
    /** @brief Calculation of SD in one pass, from https://www.strchr.com/standard_deviation_in_one_pass */
    lsc_tuning.maxpos_avg /= (double)(lsc_tuning.cycles-1);
    lsc_tuning.maxpos_sd = sqrt((lsc_tuning.maxpos_sd/(double)(lsc_tuning.cycles-1)) - lsc_tuning.maxpos_avg*lsc_tuning.maxpos_avg);

    lsc_tuning.minpos_avg /= (double)(lsc_tuning.cycles-1);
    lsc_tuning.minpos_sd = sqrt((lsc_tuning.minpos_sd/(double)(lsc_tuning.cycles-1)) - lsc_tuning.minpos_avg*lsc_tuning.minpos_avg);

    lscData.MeanScanMax = lsc_tuning.maxpos_avg;
    lscData.MeanMaxSD = lsc_tuning.maxpos_sd;
    lscData.MeanScanMin = lsc_tuning.minpos_avg;
    lscData.MeanMinSD =  lsc_tuning.minpos_sd;
    
    lscData.ScanRange = lscData.ScanMax - lscData.ScanMin;  
    lscData.MeanScanRange = lscData.MeanScanMax - lscData.MeanScanMin ; 
    

    #ifdef AUTO_CENTRE
    /** @brief update Scan offset with use of auto centre function, which adjusts the encoder position register such that 0 is the nominal centre of the scan range */           
    int32_t offset = 0; 
    if(lscData.StatusFlags.REF_SET == false){
        offset = AutoCentre( lscData.MeanScanMin , lscData.MeanScanMax  );
        lscData.MeanScanOffset +=  offset; 
    }
    int32_t temp_z_dir0 = 0; 
    int32_t temp_z_dir1 = 0; 
    int16_t z_ret = z_pos_offset(&z_buff[0], Z_BUFF_LEN, lscData.MeanScanMin, lscData.MeanScanMax, &temp_z_dir0, &temp_z_dir1); 
    switch (z_ret){
        
        
        case Z_POS_ERR_NO_POLES:
            
            if(lscData.MeanScanRange > ((LRS_POLE_PERIOD_MM* LRS_POLE_BOUNDARIES)+100)){
                dprintf_colour("[RED]Error: No Valid Z Poles found\r\n[WHITE]");
                StopMotion(); 
                Tuning_Failed(); 
            }
            break;
            
            
        case Z_POS_ERR_HIGH_VAR:
            dprintf_colour("[RED]Warning: Z pole position high SD\r\n[WHITE]");
            z_pos_error  = true; 
            
            break; 
            
        default:
            if(((z_ret & Z_POS_0_OK) > 0) || ((z_ret & Z_POS_1_OK)> 0 )){ // Check if either z offset postion is valid
                z_pos_error = false; 
              
                if(((z_ret & Z_POS_0_OK) > 0) && ((z_ret & Z_POS_1_OK)> 0 )){ // If both are valid update the different between the two
                    
                    lsc_tuning.zpos_diff = temp_z_dir0 - temp_z_dir1; 
                }
                
                if(lsc_tuning.zpos_dir  == 3u){ // if the preferred position reference direction is unset (3)

                    if((z_ret & Z_POS_0_OK) > 0){ // if direction 0 z pos ok use as the current, else use direction 1
                        
                        lscData.CurrentZOff = temp_z_dir0; 
                        lsc_tuning.zpos_cur_dir = 1;
                        
                    }else{
                        
                        lscData.CurrentZOff = temp_z_dir1; 
                        lsc_tuning.zpos_cur_dir = 2; 
                        
                    }

                }
                else if(lsc_tuning.zpos_dir == 2){ // preferred position reference direction is dir 2
                    
                    if((z_ret & Z_POS_1_OK) > 0){
                        
                        lscData.CurrentZOff = temp_z_dir1; 
                        lsc_tuning.zpos_cur_dir = 2; 
                    }else{
                        
                        lscData.CurrentZOff = temp_z_dir0 + (int32_t)lsc_tuning.zpos_diff ; 
                        lsc_tuning.zpos_cur_dir = 1;
                    }
                    

                }
                else{// preferred position reference direction is dir 1
                    
                    if((z_ret & Z_POS_0_OK) > 0){
                        
                        lscData.CurrentZOff = temp_z_dir0; 
                        lsc_tuning.zpos_cur_dir = 1;
                    }else{
                        
                        lscData.CurrentZOff = temp_z_dir1 - (int32_t)lsc_tuning.zpos_diff ; 
                        lsc_tuning.zpos_cur_dir = 2; 
                    }
                    
                }
                
                lscData.CurrentZOff = lscData.CurrentZOff - offset; // Update the z offset by the calculated scan offset used in Autocentring
            }
            
            
            break; 
        
    }
    
    dprintf( "Offset change:%ld , Cur Z off: %ld, Dir: %u\r\n", offset, lscData.CurrentZOff,lsc_tuning.zpos_cur_dir-1 ); 
   
    #endif   
#ifdef DEBUG_TUNING
    dputs("Stop Scanning: Mean Calc\r\n");
#endif
    StopMotion(); 

    lsc_tuning.tuning_phase = TUNING_DELAY;
    lsc_tuning.motor_movement_delay = START_DELAY;
    lsc_tuning.motor_state = MOTOR_STOPPED;   
}
/* ************************************************************************** */
/** 
 * @brief            Indicate Define Limits Tuning failure  
 *
 * @note             Called by void Tuning_Decision(void), void Tuning_Coarse_Sweep(void),
 *                   void Tuning_Find_Resonance_Frequency(void), void DefineLimits_task(void)
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Tuning_Failed(void)
{
    lscData.StatusFlags.ERR = true;
    dprintf_colour("[RED]Tuning failed\r\n[WHITE]");
    lsc_tuning.tuning_phase = TUNING_PHASE_UPDATE_DATA;   
    lsc_tuning.tuning_process_flag = TUNING_NOT_DONE; 
}   
/* ************************************************************************** */
/** 
 * @brief            Decision what tuning phase to chose
 *
 * @note             Called by TUNING_PHASE_DECIDE state of 
 *                   void DefineLimits_task(void) state machine
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Tuning_Decision(void)
{
    if ( lsc_tuning.prev_tuning_phase == TUNING_PHASE_IDLE && lscData.StatusFlags.QTUN == false )
    {
        lsc_tuning.tuning_phase = TUNING_PHASE_COARSE_SWEEP;
    }
    else if ( lsc_tuning.prev_tuning_phase == TUNING_PHASE_IDLE && lscData.StatusFlags.QTUN == true )
    {
        lsc_tuning.tuning_phase = TUNING_PHASE_QUICK_TUNING;
    }
    else if ( lsc_tuning.prev_tuning_phase == TUNING_PHASE_COARSE_SWEEP || lsc_tuning.prev_tuning_phase == TUNING_PHASE_QUICK_TUNING )
    {
        lsc_tuning.tuning_phase = TUNING_PHASE_MOVE_ALONG_EDGE;
    }
    else if ( lsc_tuning.prev_tuning_phase == TUNING_PHASE_MOVE_ALONG_EDGE )
    {
        lsc_tuning.tuning_phase = TUNING_PHASE_FIND_RESONANCE_FREQUENCY;
    }
    else 
    {
        Tuning_Failed();
    }  
}
/* ************************************************************************** */
/** 
 * @brief            Move to TUNING_PHASE_MOVE_ALONG_EDGE state of void DefineLimits_task(void)
 *                   state machine from TUNING_PHASE_COARSE_SWEEP state
 *
 * @note             Called by void Tuning_Coarse_Sweep(void)
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Move_To_Move_Along_Edge(void)
{
    lsc_tuning.tuning_phase = TUNING_PHASE_MOVE_ALONG_EDGE;            
    lscData.LRADriveFreq  -= FREQ_INCREMENT_LARGE;
    lsc_tuning.is_edge_met = EDGE_NOT_MET;
    lsc_tuning.prev_tuning_phase = TUNING_PHASE_COARSE_SWEEP;
    lsc_tuning.tuning_phase = TUNING_PHASE_MOVE_ALONG_EDGE;   
}
/* ************************************************************************** */
/** 
 * @brief            Increase amplitude of the motor waveform profile by a large 
 *                   increment
 *
 * @note             Called by void Tuning_Coarse_Sweep(void) and void Move_To_Coarse_Sweep (void) 
 * @return           None.
 */
/* ************************************************************************** */
bool Increase_Amplitude_by_Large_Step(void)
{
    lscData.LRADriveFreq = lscData.FreqStart;
    int32_t increment_val = VOLTAGE_INCREMENT_LARGE; 
    
 
    if(lscData.LRADriveAMP < DAC_VOLTAGE_LIMIT ){
        
        increment_val = DAC_VOLTAGE_LIMIT - lscData.LRADriveAMP; 
        
        if (increment_val > VOLTAGE_INCREMENT_LARGE){

            increment_val = VOLTAGE_INCREMENT_LARGE; 
        }

        lscData.LRADriveAMP += increment_val;
        Adjust_drive_amp(&lscData.LRADriveAMP);
        lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA;
        
        return true; 
        
        
    }else{
        return false; 
    }
    
}
/* ************************************************************************** */
/** 
 * @brief            Increase amplitude of the motor waveform profile by a long tuning 
 *                   increment
 *
 * @note             Called by void Move_Long_Tuning(void)
 * @return           None.
 */
/* ************************************************************************** */
void Increase_Amplitude_by_Long_Tuning_Step(void)
{
    lscData.LRADriveFreq = lscData.FreqStart;
    lscData.LRADriveAMP += VOLTAGE_INCREMENT_LONG_TUNING;
    Adjust_drive_amp(&lscData.LRADriveAMP);
    lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA;
}
/* ************************************************************************** */
/** 
 * @brief            Coarse sweep tuning phase 
 *
 * @note             Called by TUNING_PHASE_COARSE_SWEEP state of 
 *                   void DefineLimits_task(void) state machine
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Tuning_Coarse_Sweep(void)
{
    
    static int32_t previous_meanscan = 0; 
    
    if(lscData.MeanScanRange > MEAN_SCAN_RANGE_REQ )
    {
        Move_To_Move_Along_Edge();
        
        
    }
    else if(lscData.LRADriveFreq >= lscData.FreqLimit)
    {
        if(Increase_Amplitude_by_Large_Step()== false)
        {
            Tuning_Failed();                   
        }
        previous_meanscan = 0; 
    }
    else
    {
        
        if((previous_meanscan > (lscData.MeanScanRange + 5))&& (lscData.MeanScanRange < SCAN_RANGE_FREQ_FAIL_COND)){
            
            if(Increase_Amplitude_by_Large_Step() == false){
                
                Tuning_Failed(); 
            }
            previous_meanscan = 0; 
            
        }else{
            
            lscData.LRADriveFreq += FREQ_INCREMENT_LARGE;
            lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA;
            previous_meanscan = lscData.MeanScanRange; 
        }
        
        
        
    }
} 
/* ************************************************************************** */
/** 
 * @brief            Decrease amplitude of the motor waveform profile by a small 
 *                   increment
 *
 * @note             Called by void Move_Further_Along_Edge(void) and void Tuning_Quick(void) 
 * @return           None.
 */
/* ************************************************************************** */
void Decrease_Amplitude(void)
{
    lscData.LRADriveAMP -= VOLTAGE_INCREMENT_SMALL;
    Adjust_drive_amp(&lscData.LRADriveAMP);
    lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA;
}
/* ************************************************************************** */
/** 
 * @brief            Keep moving along the high threshold scan range edge
 *
 * @note             Called by void Tuning_Move_Along_Edge(void)
 * @return           None.
 */
/* ************************************************************************** */
void Move_Further_Along_Edge(void)
{
    lsc_tuning.is_edge_met  = EDGE_MET; 
    lsc_tuning.apex_freq = lscData.LRADriveFreq;
    lscData.FreqStart = lsc_tuning.apex_freq - FREQ_START_APEX_OFFSET;
    lscData.FreqLimit = lsc_tuning.apex_freq + FREQ_LIMIT_APEX_OFFSET; 
    Decrease_Amplitude();
}
/* ************************************************************************** */
/** 
 * @brief            Move to TUNING_PHASE_MOVE_ALONG_EDGE state of void DefineLimits_task(void)
 *                   state machine from TUNING_PHASE_MOVE_ALONG_EDGE state
 *
 * @note             Called by TUNING_PHASE_MOVE_ALONG_EDGE
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Move_To_Find_Res_Freq(void)
{
    lsc_tuning.prev_tuning_phase = TUNING_PHASE_MOVE_ALONG_EDGE;
    lscData.LRADriveFreq = lsc_tuning.apex_freq - (2*FREQ_INCREMENT_LARGE);
    lscData.LRADriveAMP += VOLTAGE_INCREMENT_MOVE_TO_FIND_FREQ;
    lsc_tuning.last_scan_set_sd_count = LAST_SCAN_SET_NUM_REQ;
    lsc_tuning.last_scan_set_below_threshold_count = 0; 
    
    Adjust_drive_amp(&lscData.LRADriveAMP);
    lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA;
}    
/* ************************************************************************** */
/** 
 * @brief            Move to TUNING_PHASE_COARSE_SWEEP state of void DefineLimits_task(void)
 *                   state machine from Tuning_Move_Along_Edge state
 *
 * @note             Called in Tuning_Move_Along_Edge state of void DefineLimits_task(void)
 *                   state machine
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Move_To_Coarse_Sweep(void)
{
    lsc_tuning.prev_tuning_phase = TUNING_PHASE_IDLE;
    lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA;
    Increase_Amplitude_by_Large_Step();
}
/* ************************************************************************** */
/** 
 * @brief            Move along edge tuning phase 
 *
 * @note             Called by TUNING_PHASE_MOVE_ALONG_EDGE state of 
 *                   void DefineLimits_task(void) state machine
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Tuning_Move_Along_Edge(void)
{
    if(lscData.MeanScanRange > MEAN_SCAN_RANGE_REQ )
    {
        Move_Further_Along_Edge();
    }
    else if (lscData.LRADriveFreq >= lscData.FreqLimit)
    {
        if (lsc_tuning.is_edge_met == EDGE_MET )
        {
            Move_To_Find_Res_Freq();
        }
        else
        {
            Move_To_Coarse_Sweep();
        }
    }
    else
    {
        lscData.LRADriveFreq += FREQ_INCREMENT_MEDIUM;
        lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA;
    } 
}
/* ************************************************************************** */
/** 
 * @brief            Update Resonance Tuning parameters and end the tuning  
 *
 * @note             Called by void Tuning_Find_Resonance_Frequency(void) and void Tuning_Quick(void)
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Resonace_Freq_Found(void)
{
    lscData.LRAResonantFreq = lscData.LRADriveFreq;
    lscData.LRAResonantAMP = lscData.LRADriveAMP;
    lscData.StatusFlags.CFG = true;
    lsc_tuning.tuning_phase = TUNING_PHASE_UPDATE_DATA;
}
/* ************************************************************************** */
/** 
 * @brief            Register that scan range of last set is below the threshold
 *                   Checking if reached the Niagara fall 
 *
 * @note             Called by void Tuning_Find_Resonance_Frequency(void)
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Scan_Set_Below_Threshold(void)
{
    lscData.LRADriveFreq = lsc_tuning.apex_freq - (3*FREQ_INCREMENT_LARGE);
    lscData.LRADriveAMP += VOLTAGE_INCREMENT_SMALL;
    lsc_tuning.last_scan_set_below_threshold_count ++;
    Adjust_drive_amp(&lscData.LRADriveAMP);
    lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA;
}
/* ************************************************************************** */
/** 
 * @brief            Keep looking for resonance frequency  
 *
 * @note             Called by void Tuning_Find_Resonance_Frequency(void)
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Keep_Looking_Res_Freq(void)
{
    lscData.LRADriveFreq += FREQ_INCREMENT_SMALL;
    lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA;
    if( lscData.MeanMaxSD < STABLE_SCAN_SD_THRESHOLD && lscData.MeanMinSD < STABLE_SCAN_SD_THRESHOLD )
    {    
        lsc_tuning.last_scan_set_sd_count ++;
    }    
    else{
        
        lsc_tuning.last_scan_set_sd_count = 0; 
    }
    lsc_tuning.last_scan_set_below_threshold_count = 0; 
}
/* ************************************************************************** */
/** 
 * @brief            Find Resonance Frequency tuning phase 
 *
 * @note             Called by TUNING_PHASE_FIND_RESONANCE_FREQUENCY state of 
 *                   void DefineLimits_task(void) state machine
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Tuning_Find_Resonance_Frequency(void)
{
    conf_thresh = SCAN_RANGE_DIST_LONG_TUNING_REQ; 
    ScanRangeDistribiutionCalc(); 
    Check_Make_Z_adjust(); 
    if(lscData.MeanScanRange > MEAN_SCAN_RANGE_REQ )
    {
        if(lscData.LRADriveFreq > lscData.FreqStart){
            
            lscData.LRADriveFreq = lscData.LRADriveFreq -(1.0f*FREQ_INCREMENT_SMALL); 
        }
        Decrease_Amplitude();
        Keep_Looking_Res_Freq(); 
    }
    else if((lscData.ScanMaxSDLow> conf_thresh)\
            &&  (lscData.ScanMinSDLow> conf_thresh)\
            && (lsc_tuning.last_scan_set_sd_count >= LAST_SCAN_SET_NUM_REQ ))
    {
        Resonace_Freq_Found();
    }
    else if((lscData.LRADriveFreq > lsc_tuning.apex_freq &&  lsc_tuning.last_scan_set_below_threshold_count >= LAST_SCAN_SET_NUM_REQ) || lscData.LRADriveFreq  > (lscData.FreqLimit + FREQ_INCREMENT_MEDIUM))
    {
        Tuning_Failed();            
    }
    else if (lscData.MeanScanRange < 0.7*MEAN_SCAN_RANGE_REQ)
    {
        Scan_Set_Below_Threshold();
    }
    else
    {
        Keep_Looking_Res_Freq();
    }
}               
/* ************************************************************************** */
/** 
 * @brief            Move to TUNING_PHASE_COARSE_SWEEP state of void DefineLimits_task(void)
 *                   state machine from  TUNING_PHASE_QUICK_TUNING state
 *
 * @note             Called in TUNING_PHASE_QUICK_TUNING state of void DefineLimits_task(void)
 *                   state machine
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Move_Long_Tuning(void)
{
    lsc_tuning.prev_tuning_phase = TUNING_PHASE_IDLE;
    lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA;
    Increase_Amplitude_by_Long_Tuning_Step();
    lscData.StatusFlags.QTUN = false;
}
/* ************************************************************************** */
/** 
 * @brief            Quick tuning 
 *
 * @note             Called by TUNING_PHASE_QUICK_TUNING state of void DefineLimits_task(void)
 *                   state machine
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Tuning_Quick(void)
{
    ScanRangeDistribiutionCalc(); 
    conf_thresh = SCAN_RANGE_DIST_SHORT_TUNING_REQ; 
    
    Check_Make_Z_adjust(); 
    
    if((lscData.MeanScanRange <= MEAN_SCAN_RANGE_REQ )\
        &&  (lscData.ScanMaxSDLow> conf_thresh)\
        &&  (lscData.ScanMinSDLow> conf_thresh)){
        Resonace_Freq_Found(); 
    }
    else if(lsc_tuning.qtune_retry_cnt == QTUN_RETRY_CNT){

        lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA;
    
    }
    else if(lscData.MeanScanRange > MEAN_SCAN_RANGE_REQ ){
        Decrease_Amplitude();
    }
    else if (((lsc_tuning.qtune_retry_cnt== 0) || (lscData.MeanScanRange < SCAN_RANGE_QTUN_FAIL_COND))
                && (lscData.MeanScanRange < SCAN_RANGE_START_MOVE_ALONG_EDGE_COND) ){
        Move_Long_Tuning(); 
    }    
    else{
        lscData.LRADriveFreq += FREQ_INCREMENT_SMALL; 
        lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA;
    }
    
    if(lsc_tuning.qtune_retry_cnt > 0){
        
        lsc_tuning.qtune_retry_cnt--;
    }
     
 }
/* ************************************************************************** */
/** 
 * @brief            Update lscData structure and encoder zero offset after 
 *                   collecting new set of samples
 *
 * @note             Called by TUNING_PHASE_UPDATE_DATA state of void DefineLimits_task(void)
 *                   state machine
 * 
 * @return           None.
 */
/* ************************************************************************** */
void Tuning_Update_Data(void)
{
    log_scan_settings(GREEN, lsc_tuning.prev_freq, lsc_tuning.prev_amp);
    /** @brief configuration routine went successfully flag is set, assign last drive frequency to resonant frequency to store the resonant frequency */
    if (lscData.StatusFlags.CFG)
    {
        
        if((true == z_pos_error)||(lsc_tuning.zpos_cur_dir == 0)){
            
            if(lsc_tuning.zpos_retry_cnt ==0){
                dprintf_colour("[RED]Warning: Retrying scan due Z pole position high SD\r\n[WHITE]");
                lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA;  
                lsc_tuning.zpos_retry_cnt++;
            }else{
                dprintf_colour("[RED]Error: Z pole position high SD on retry\r\n[WHITE]");
                StopMotion(); 
                lscData.StatusFlags.CFG = 0; 
                Tuning_Failed(); 
                
            }
            
        }else if ((lscData.OriginalZOff == INT32_MAX)){ // Original Z off is not set so update
                lscData.OriginalZOff =  lscData.CurrentZOff;
                lsc_tuning.zpos_dir = lsc_tuning.zpos_cur_dir; 
                lscData.ZOff_diff_dir = (((int16_t)(lsc_tuning.zpos_cur_dir & 0x3)) <<8) & 0xFF00; 
                lscData.ZOff_diff_dir = lscData.ZOff_diff_dir | (((int16_t)lsc_tuning.zpos_diff) & 0x00FF);  
                lscData.StatusFlags.REF_SET = true; 
                dprintf_colour("[GREEN]Setting Z: Off: %ld, Dir: %u, Diff0-1: %i\r\n[WHITE]", lscData.OriginalZOff,lsc_tuning.zpos_dir-1,lsc_tuning.zpos_diff ); 
        }
        
        
        lscData.LRAResonantFreq = lscData.LRADriveFreq;  
        
        
        dprintf_colour("[GREEN]Resonant frequency: %3.3f\r\n[WHITE]",lscData.LRADriveFreq);
        dprintf_colour("[GREEN]Resonant Amp: %ld\r\n[WHITE]",lscData.LRAResonantAMP);
        dprintf_colour("[GREEN]Z offset current: %ld, Original %ld\r\n[WHITE]",lscData.CurrentZOff, lscData.OriginalZOff );
        //lscData.LRAResonantFreq = lscData.LRAResonantFreq - (4.0f*FREQ_INCREMENT_SMALL); 
        //dprintf_colour("[YELLOW] Test freq saved: %3.3f\r\n[WHITE]", lscData.LRAResonantFreq); 
        /** @brief set resonant frequency is saved flag */
        lscData.StatusFlags.SAVE = true;
        /** @brief set flag perform quick tuning instead of fine tuning */
        lscData.StatusFlags.QTUN = true;
        DSP_BUSY_SetHigh();
        lsc_tuning.tuning_process_flag = TUNING_FINISHED;
    }
    else
    {
        lsc_tuning.tuning_process_flag = TUNING_NOT_DONE;
        lscData.StatusFlags.ERR = true;
    }

    // Configure output (EMC-BUSY) pin: Pin goes high when POS1CNT <= QEI1LEC or POS1CNT >= QEI1GEC)

    /** @brief Scan Start to Scan Stop equals to SCAN_RANGE macro */
    lscData.ScanStart = POSITION_OFFSET - (SCAN_RANGE / 2L);
    lscData.ScanStop = POSITION_OFFSET + (SCAN_RANGE / 2L);     

    /** @brief adjust encoder count limits according to scan start and stop parameters got after tuning process */

    /** @brief set lower encoder limit */
    QEI1LECH = lscData.Words.ScanStart[1];               
    QEI1LECL = lscData.Words.ScanStart[0];

    /** @brief set upper encoder limit */
    QEI1GECH = lscData.Words.ScanStop[1];                
    QEI1GECL = lscData.Words.ScanStop[0];  
    disable_z_INT(); 
    lsc_tuning.tuning_phase = TUNING_PHASE_IDLE;
}  
/* ************************************************************************** */
/** 
 * @brief            Clear the Tuning Data structure between sets of samples
 *
 * @note             Called by TUNING_PHASE_CLEAR_DATA state of void DefineLimits_task(void)
 *                   state machine
 * 
 * @return           None.
 */
/* ************************************************************************** */

void Tuning_Clear_Data(void)
{
    if (!StartDACOutput(lscData.LRADriveFreq, false)) // Try set new drive frequency(start = false), returns false if out of limits
    {
        lsc_tuning.tuning_phase = TUNING_PHASE_UPDATE_DATA; 
       /** @brief stop the scan cycle and disables all related interrupts */
        dputs("Stop Scanning: Invalid Frequency\r\n");
        StopMotion(); 
        //CHECK: there may be a step missing here as code continues and does a scan any way if the frequency can not be set
    }
    start_tune_scan_motion(); // Start motion at lscData.LRADriveFreq frequency
    log_scan_settings(YELLOW,  lsc_tuning.prev_freq, lsc_tuning.prev_amp);

    /** @brief set scanning parameters to 0 and try different frequency */  
    lscData.ScanMin = 0L;       
    lscData.ScanMax = 0L;               
    lscData.MeanScanMin = 0L;          
    lscData.MeanScanMax = 0L;
    lscData.MeanMinSD = 0.0f;
    lscData.MeanMaxSD = 0.0f;
    lsc_tuning.maxpos_sd=0;
    lsc_tuning.minpos_sd=0;
    lsc_tuning.maxpos_avg=0;
    lsc_tuning.minpos_avg=0;;  
    lsc_tuning.cycles=0;
    clear_z_buffer(); 
    lsc_tuning.zpos_cur_dir = 0; 
    lsc_tuning.tuning_phase = TUNING_DELAY;
    lsc_tuning.motor_movement_delay = START_DELAY;
    lsc_tuning.motor_state = MOTOR_STARTED;
}


void Tuning_tick(void){ // temporary until debug timeouts are sorted
    
    if(waiting_for_scans_TO > 0){
        waiting_for_scans_TO --; 
    }
    
}

/* ************************************************************************** */
/** 
 * @brief            Delay after turning motor off and on
 *
 * @note             Called by TUNING_DELAY state of void DefineLimits_task(void)
 *                   state machine
 * 
 * @return           None.
 */
/* ************************************************************************** */

void Tuning_Delay(void)
{
    static uint32_t delay = 0;
    delay ++;
    if (lsc_tuning.motor_movement_delay == START_DELAY)
    {
#ifdef  DEBUG_TUNING
        dputs_colour("[CYAN]Delay start\r\n[WHITE]"); 
#endif
        delay = 0; 
        lsc_tuning.motor_movement_delay = WAIT;
    }
    if ( delay >= MOTOR_DELAY )
    {
#ifdef  DEBUG_TUNING
        dputs_colour("[WHITE]Delay End\r\n[WHITE]");
#endif
        lsc_tuning.motor_movement_delay = END_DELAY;
        if (lsc_tuning.motor_state == MOTOR_STOPPED )
        {
            lsc_tuning.tuning_phase = TUNING_PHASE_DECIDE;
            lsc_tuning.motor_state = MOTOR_NOT_SPEC;
        }    
        else if (lsc_tuning.motor_state == MOTOR_STARTED)
        {
            
            
            waiting_for_scans_TO  = WAIT_FOR_SCANS_TIMEOUT_MS; 
            lsc_tuning.tuning_phase = TUNING_PHASE_COLLECT_DATA;
            lsc_tuning.motor_state = MOTOR_NOT_SPEC;
            
            if(CCP7CON1Lbits.CCPON == true ){
        
                dputs("DAC timer EN\r\n");
            }else{

                dputs("DAC timer not EN\r\n");

            }
            
        } 
        else
        {
            Tuning_Failed();
        }
    }  
}    
/* ************************************************************************** */
/** 
 * @brief            Find true amplitude and frequency State machine.Defines the 
 *                   limits of the linear motion based on the min/max positions 
 *                   from a number of open loop revolutions
 *
 * @note             Called by static bool processing_task(void)
 * 
 * @return           None.
 */
/* ************************************************************************** */
void DefineLimits_task(void)
{
    
    static _TUNING_PHASE prev_phase = TUNING_PHASE_IDLE; 
    
    if(prev_phase != lsc_tuning.tuning_phase){
        prev_phase= lsc_tuning.tuning_phase;
 #ifdef              DEBUG_TUNING
        dprintf_colour("[WHITE]New phase: %d\r\n[WHITE]", prev_phase );
#endif     
    }
        
    switch(lsc_tuning.tuning_phase) 
 
    {
        case TUNING_PHASE_REINIT:
            Tuning_Init(false);
            break; 
        
        case TUNING_PHASE_INIT:
        {
            Tuning_Init(true);
            break;
        } 
        case TUNING_PHASE_COLLECT_DATA:
        {
            
            
            if(lsc_tuning.enc_diff_zero_cnt > 50){
                
                dputs_colour("[RED] No movement detected\r\n[WHITE]"); 
                lsc_tuning.enc_diff_zero_cnt = 0; 
                //debug_output_pulse(1);
            }

            if( lsc_tuning.new_scan_found == NEW_SCAN_PRESENT )
            {  
                


                Tuning_Collect_Data();                 
                lsc_tuning.new_scan_found = NEW_SCAN_NOT_PRESENT;
                waiting_for_scans_TO = WAIT_FOR_SCANS_TIMEOUT_MS; 
                lsc_tuning.retry = 0; 
            }else if(waiting_for_scans_TO == 0){
                
                dputs_colour("[RED] No new scans found\r\n[WHITE]"); 
                
                debug_output_pulse(2); 
                lsc_tuning.retry++;
                StopMotion(); 
                if (lsc_tuning.retry ==1){
                    
                    lsc_tuning.tuning_phase = TUNING_PHASE_CLEAR_DATA; 
                    dputs_colour("[RED] Retrying: Clear Data \r\n[WHITE]"); 
                    
                }else if (lsc_tuning.retry == 2){
                    
                    lsc_tuning.tuning_phase = TUNING_PHASE_REINIT; 
                    dputs_colour("[RED] Retrying: Re-init \r\n[WHITE]"); 
                }else if (lsc_tuning.retry == 3){
                    
                    SCCP7_TMR_Initialize();
                    DMA_Initialize();
                    lsc_tuning.tuning_phase = TUNING_PHASE_REINIT; 
                    dputs_colour("[RED] Retrying: DAC & Timer init \r\n[WHITE]"); 
                }else {
                    
                    
                    Tuning_Failed(); 
                }
                
                
            }
            if (lsc_tuning.cycles > LOOP_LIMIT)
            {
                Calculate_Tuning_Data_Mean();               
            }    
            break; 
        } 
        case TUNING_PHASE_DECIDE:
        { 
            Tuning_Decision();         
            break; 
        }
        
        case TUNING_PHASE_COARSE_SWEEP:
        {
            Tuning_Coarse_Sweep();           
            break; 
        } 
        
        case TUNING_PHASE_MOVE_ALONG_EDGE:
        {
            Tuning_Move_Along_Edge();
            break; 
        } 
        
        case TUNING_PHASE_FIND_RESONANCE_FREQUENCY:
        {
            Tuning_Find_Resonance_Frequency();
            break; 
        } 
        
        case TUNING_PHASE_QUICK_TUNING:
        {
            Tuning_Quick();
            break; 
        } 
        
        case TUNING_PHASE_UPDATE_DATA:
        {
            Tuning_Update_Data();
            break; 
        }
        
        case TUNING_PHASE_IDLE:
        {
            lsc_tuning.prev_tuning_phase = TUNING_PHASE_IDLE;            
            
            DSP_BUSY_SetHigh(); 
            break; 
        }
        
        case TUNING_PHASE_CLEAR_DATA:
        {
            Tuning_Clear_Data();
            break;
        }
        
        case TUNING_DELAY:
        {
            Tuning_Delay();             
            break;
        }
        
        default : 
        { 
            Tuning_Failed();
            break;
        }    
    }   
}
///////////////////////////////

