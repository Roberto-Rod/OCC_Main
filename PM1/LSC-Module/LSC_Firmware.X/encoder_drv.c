/* ************************************************************************** */
/** @file @file encoder_drv.c
 *
 *  @brief Encoder driver file.
 *
 *  @copyright Occuity Limited (c) 2021
 */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include <xc.h>
#include "encoder_drv.h"
#include "main.h"
#include "debug.h"

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */


volatile z_poles_t z_poles; 

volatile bool z_update = false; 

/* ************************************************************************** */
/* Section: Global Variables                                                  */
/* ************************************************************************** */
/** @brief LSC data object defining set LSC parameters and firmware */
extern volatile _LSC_DATA lscData;
/** @brief lsc tuning object consisitng data reqiired for tuning process */
extern volatile _LSC_TUNING_OBJ lsc_tuning;

/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */

#define ENC_HIT_ENDS_TO (50*10)

static volatile int16_t enc_move_wdt = -1;
static volatile bool enc_move_wdt_exp = false; 


/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */

void enc_move_wdt_reset(){
    
    enc_move_wdt = ENC_HIT_ENDS_TO; 
} 

bool enc_move_wdt_check_clear(void){
    
    bool state = enc_move_wdt_exp; 
    
    if(state == true){
        
        enc_move_wdt_exp = false;
    }
    
    return state; 
}

void enc_move_wdt_start(void){
    
     enc_move_wdt = ENC_HIT_ENDS_TO; 
     enc_move_wdt_exp = false;
}

void enc_move_wdt_stop(void){
    
    enc_move_wdt = -1; 
}

bool get_z_positions(z_poles_t* cpy){ // Gets z pole positions, returns true when z potions have been successfully copied 
    
    
    if(z_update == false){
        
        memcpy(&cpy->dir_cnt, &z_poles.dir_cnt, sizeof(z_poles.dir_cnt));
        memcpy(&cpy->positions, &z_poles.positions, sizeof(z_poles.positions));
        
        memset((void*)&z_poles, 0, sizeof(z_poles_t));
        return true; 
        
    }else{
        
        return false; 
    }
    
}

void enable_z_INT(void){
    
    
    if (CNEN0Bbits.CNEN0B5 == 0){
        
        CNEN0Bbits.CNEN0B5 = 1; 
        CNEN1Bbits.CNEN1B5 = 1;        

        (void)PORTBbits.RB5; 
        CNFBbits.CNFB5 = 0; 
        
        IFS0bits.CNBIF = 0; 
        
        CNCONB = 0x8800; 
        
        IEC0bits.CNBIE = 1;
    }
    
    
}

void disable_z_INT(void){
    
    IEC0bits.CNBIE = 0; 
    IFS0bits.CNBIF = 0; 
    
    CNEN0Bbits.CNEN0B5 = 0; 
    CNEN1Bbits.CNEN1B5 = 0;      
    
    CNCONB = 0x0000; 
    
}



/* ************************************************************************** */
/** 
 * @brief            Encoder interrupt routine
 *
 * @note             Called by the change of the status encoder A and B lines.
 *
 * @return           None.
 */
/* ************************************************************************** */
void __attribute__((interrupt, no_auto_psv)) _QEI1Interrupt(void)
{
/** @brief  if Position Counter less Than Compare Status bit is true: POS1CNT < QEI1LEC (Is smaller than ScanStart - scanning backword from zero offset position). 
 * lscData.ScanStart to lscData.ScanStop defines the data acquisition region within a scan */
    if (QEI1STATbits.PCLEQIRQ == 1)                 
    {
/** @brief set status flag direction to forward movement */    
        lscData.StatusFlags.DIR = true;    
/** @brief  clear Position Counter less Than Compare Status flag: POS1CNT > QEI1LEC */        
        QEI1STATbits.PCLEQIRQ = false;        
    }
/** @brief  else if Position Counter Greater Than Compare Status bit is true:  POS1CNT > QEI1GEC (Is bigger than ScanStop - scanning forward from zero offset position) */
    else if (QEI1STATbits.PCHEQIRQ == 1)
    { 
/** @brief set status flag direction to backward movement */         
        lscData.StatusFlags.DIR = false;    
/** @brief  clear Position Counter Greater Than Compare Status bit:  POS1CNT < QEI1GEC  */           
        QEI1STATbits.PCHEQIRQ = false;        
    }     
/** @brief set status flag configuration routine went successfully */    
    if (lscData.StatusFlags.CFG == 1)              
    {
        /** @brief if Scan Count reaches zero */        
        if (ScnCount(lscData.StatusFlags.DIR))
        {
            /** @brief set state of latch 1 to true. Enable QEI position match output */
            LSC_BUSY = true;
            QEI1IOCbits.OUTFNC = 0b11;                        
        }
        else
        {
            /** @brief disable QEI position match output */
            QEI1IOCbits.OUTFNC = 0b00;                           
            /** @brief set state of latch 1 to true */
            LSC_BUSY = true;
        }
    }
    /** @brief set state of latch 2 to true */         
    LSC_DIR = lscData.StatusFlags.DIR;
    lscData.StatusFlags.HIT_LIMIT =1; 
    /** @brief Clear QEI interrupt flag */
    enc_move_wdt_reset(); 
    IFS3bits.QEI1IF = 0;                                        
}

/* ************************************************************************** */
/** 
 * @brief            encoder module interrupt 
 *
 * @note             Called by timer interrupt with 50kHz frequency. Checks
 *                   if carriage position has changed and update scan max/min ranges  
 *
 * @return           None.
 */
/* ************************************************************************** */
void encoder_interrupt (void)
{
//    DBG_LEDG_SetLow();
    if (lsc_tuning.tuning_phase == TUNING_PHASE_COLLECT_DATA)
    {  
        int32_t current_pos = GetPosition(); 
        uint32_t abs_diff = 0; 
        
        if(lsc_tuning.direction) // if encoder is decreasing
        {
            if( current_pos > lsc_tuning.last_encoder_pos) // now is moving to max 
            {
                lsc_tuning.minpos = lsc_tuning.last_encoder_pos; // the last value was the lowest value
                lsc_tuning.direction = false;
                
                abs_diff = current_pos - lsc_tuning.last_encoder_pos; 
            }
            else
            {
                abs_diff = lsc_tuning.last_encoder_pos - current_pos; 
            }
        }
        else
        {
            if(current_pos < lsc_tuning.last_encoder_pos) // is now moving to min 
            {
                lsc_tuning.maxpos = lsc_tuning.last_encoder_pos; // the last value was the largest value
                lsc_tuning.direction = true;
                if(lsc_tuning.new_scan_found == WAIT_FOR_FIRST_CYCLE)
                {
                    z_poles.dir_cnt[0] = 0; 
                    z_poles.dir_cnt[1] = 0; 
                    
                    z_update = true; 
                    lsc_tuning.new_scan_found = NEW_SCAN_NOT_PRESENT;
                }
                else
                {
                    if(z_update){
                        
                        z_update = false;
                        
                    }else{
                        z_poles.dir_cnt[0] = 0; 
                        z_poles.dir_cnt[1] = 0; 
                        z_update = true; 
                    }
                   
                    lsc_tuning.new_scan_found = NEW_SCAN_PRESENT;

                }
                
                
                abs_diff = lsc_tuning.last_encoder_pos - current_pos;    
            }
            else
            {
                
                abs_diff = current_pos - lsc_tuning.last_encoder_pos; 
            }
        }
        
        if(abs_diff < 1)
        {
            
            if (lsc_tuning.enc_diff_zero_cnt < 0xFFFFu){
                lsc_tuning.enc_diff_zero_cnt++;  
            }
            
        }
        else
        {
            
            lsc_tuning.enc_diff_zero_cnt = 0; 
        }
        
        lsc_tuning.last_encoder_pos = GetPosition();
    }else{
        
        if(enc_move_wdt > 0){
            
            enc_move_wdt --; 
            
        }else if(enc_move_wdt == 0){
            
            enc_move_wdt_exp = true; 
            
            enc_move_wdt = -1; 
            
        }
        
        
    } 
//    DBG_LEDG_SetHigh();
}



void z_INT_callback(void)
{
    int32_t pos = GetPosition(); 
    static int32_t prev = 0; 
    
    if(z_update){
        uint8_t dir = 0; 
        if(lsc_tuning.direction){
            dir =  1; 
        }

        switch(z_poles.dir_cnt[dir]){
            
            case 2:
                
                if(((prev >= (pos+LRS_POLE_VAL_MM )) && (dir == 1))||(((prev+LRS_POLE_VAL_MM ) <= pos ) && (dir == 0))){
                    
                   prev = pos;
                    z_poles.positions[dir][z_poles.dir_cnt[dir]] = pos; 
                    z_poles.dir_cnt[dir]++; 
                
                }
                break; 
            

            case 1:

                if((prev < (pos+1800)) && (dir == 1)){ // Check that pos 1 is expected distance from prev, if not overwrite prev

                    z_poles.dir_cnt[dir] = 0; 
                    
                }else if(((prev+1800) > pos ) && (dir == 0)){
                        
                    z_poles.dir_cnt[dir] = 0;
                }
        
            case 0:
                prev = pos;

                z_poles.positions[dir][z_poles.dir_cnt[dir]] = pos; 
                z_poles.dir_cnt[dir]++; 
                break; 
            default:

                break; 
        }


    }
    
}








