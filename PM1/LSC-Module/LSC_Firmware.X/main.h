/* ************************************************************************** */
/** @file main.h
 *
 *  @brief main header file
 *
 *  @copyright Occuity Limited (c) 2020
 */
/* ************************************************************************** */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifndef FCY
#define FCY 100000000L
#endif
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include <xc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h> 
//#include <string.h>
    
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/delay.h"   
    
#include "pdab_comms.h"  
#include "message_exchange.h"
    
#include "NVM_Driver.h"
  
    
//#define DEBUG_PIC_COMMS
//#define DEBUG_MESSAGE_EXCHANGE
//****************************************************************************//
//                           Typedefs
//****************************************************************************//
/** @brief define macro encoder scale pole pitch */
#define LRS_POLE_PERIOD         2U    
    
#define LRS_POLE_PERIOD_MM      2000
    
#define LRS_POLE_VAL_MM         1800
/** @brief define macro scan range rounded UP to the nearest mm */
#define LRS_MAX_SCAN_RANGE      6U      
/** @brief define macro maximum number of pole boundaries withing the scan rang */
#define LRS_POLE_BOUNDARIES     2U   
    
#define LRS_POLE_BUF_NUM        (LRS_POLE_BOUNDARIES +1)
    
/** @brief typdef LSC status flag  */
typedef 
    union {	
        uint16_t    Short;
        struct {
            unsigned TUNE_FINISHED:1;
            unsigned TUNE_ERROR:1;
            unsigned TUNE_INPROG:1;
            unsigned :1;
            unsigned :1;
            unsigned :1;
            unsigned :1;
            unsigned :1;
        };

}LSC_Status_flags;    
/******************************************************************************/

//Ensure that variables in LSC_struct allign to 32bit boundaries to prevent padding on 32bit system. 
typedef union
{
    struct{
    /** @brief LSC firmware version  */
        uint16_t Version;                                   // 2 bytes
        LSC_Status_flags flags;                             // 2 bytes

        uint32_t    Range;                              // LSC maximum scan range
        uint32_t    Length;                             // LSC data acquisition length    
        float       Frequency;                          // Drive frequency
   

        int32_t    Position;                                // Current stage position
                                                            // 4 bytes
        int32_t    RefPositions[LRS_POLE_BOUNDARIES];       // Encoder Index Positions
                                                            // 8 bytes
    };                                                      // 28 bytes 
    uint8_t bytes[28]; 
} LSC_STATUS_t;   
 
/** @brief type buffer enum defining type of the buffer  */
typedef union {
    /** @brief buffer of double size */
    double      Double;
    /** @brief buffer of float size */
    float       Float[2];
    /** @brief buffer of int32_t size */
    int32_t 	Long[2];
    /** @brief buffer of int16_t size */
    int16_t     Short[4];
    /** @brief buffer of int8_t size */
    int8_t      Byte[8];
    } _TYPE_BUFFER;

/** @brief status flag union defining bit field of status flag*/
typedef union {	
    uint16_t    Short;
   /** @brief status flag bit field object */ 
    struct {	
            /** @brief status flag initialisation, set indicates that initialisation process is done */
            unsigned INIT:1;
            /** @brief status flag configuration routine went successfully */
            unsigned CFG:1;
            /** @brief status flag define limits (start tuning process, re-initialise motion controller) */        
            unsigned DLIM:1; 
            /** @brief interface enable flag Quadrature Encoder Interface output, set indicate interface is enabled */
            unsigned QOE:1;
            /** @brief status flag direction to forward movement (0 - backward movement)*/
            unsigned DIR:1;
            /** @brief status flag start scanning */
            unsigned START:1;
            /** @brief status flag stop scanning */
            unsigned STOP:1;
            unsigned FLASH:1;
            /** @brief status flag indicating error */
            unsigned ERR:1;
            /** @brief status flag save resonant frequency data */
            unsigned SAVE:1;
            /** @brief status shutdown, set when shutdown procedure began. Prevent writing to NVM during shutdown */            
            unsigned ROFF:1;
            unsigned LS:1;
            unsigned REF:1;
            /** @brief status flag perform quick tuning instead of fine tuning */
            unsigned QTUN:1;
            /** @brief status flag to indicate when encoder has met or exceeded +/- encoder limits  */
            unsigned HIT_LIMIT:1;
            /** @brief status flag to indicate if z based reference has been set */
            unsigned REF_SET:1;
        };
    } _STATUS_FLAGS;
    
/** @brief LRA tuning state machine phase */
typedef enum
{
    /** @brief LRA initialization tuning phase */
    TUNING_PHASE_INIT = 0,
    /** @brief LRA coarse sweep tuning phase */
    TUNING_PHASE_COARSE_SWEEP = 1,
    /** @brief LRA move along edge phase */
    TUNING_PHASE_MOVE_ALONG_EDGE = 2,
    /** @brief LRA find resonance frequency tuning phase */
    TUNING_PHASE_FIND_RESONANCE_FREQUENCY = 3,
    /** @brief LRA start quick tuning phase */        
    TUNING_PHASE_QUICK_TUNING = 4,
    /** @brief LRA update data tuning phase */           
    TUNING_PHASE_UPDATE_DATA = 5,
    /** @brief LRA collect data tuning phase */           
    TUNING_PHASE_COLLECT_DATA = 6,        
    /** @brief LRA idle phase */          
    TUNING_PHASE_IDLE = 7, 
    /** @brief LRA decide what tuning phase to chose */
    TUNING_PHASE_DECIDE = 8,
    /** @brief LRA clear data structure phase */
    TUNING_PHASE_CLEAR_DATA = 9,
    /** @brief LRA delay between consecutive scan set */
    TUNING_DELAY = 10,
    /** @brief LRA re-initialization tuning phase */        
    TUNING_PHASE_REINIT = 11, 
            
}_TUNING_PHASE;

/** @brief LRA tuning edge met flag */
typedef enum
{
    /** @brief LRA tuning edge is not met */
    EDGE_NOT_MET = 0,
    /** @brief LRA tuning edge is met */
    EDGE_MET = 1,
}_EDGE_MET_REQ_STATE;

/** @brief LRA tuning process finished flag */
typedef enum
{
    TUNING_NOT_DONE = 0,
    /** @brief LRA tuning process not finished */
    TUNING_IN_PROG = 1,
    /** @brief LRA tuning process not finished */
    TUNING_FINISHED = 2,
}TUNE_STATE_t;

/** @brief LRA delay process  */
typedef enum
{
    /** @brief start delay */
    START_DELAY,
    /** @brief wait */
    WAIT,
    /** @brief end delay */        
    END_DELAY,        
}_DELAY_STATE;

/** @brief scan parameters union presents 4 ways of access dependent of the data type */     
typedef union
{
    uint16_t Buffer[128];
    
    /** @brief scan parameters object 32 bit type elements */  
    struct 
    {
        /** @brief current frequency during resonance tuning process */
        float   LRADriveFreq;           // 2 words: 2
        /** @brief current LRA amplitude during resonance tuning process */    
        uint32_t LRADriveAMP;           // 2 words: 4
        /** @brief LRA resonance frequency */       
        float   LRAResonantFreq;        // 2 words: 6 
        /** @brief LRA resonance amplitude */ 
        uint32_t LRAResonantAMP;        // 2 words: 8
        int32_t ScanOffset;             // 2 words: 10 
        int32_t ScanMin;                // 2 words: 12 
        int32_t ScanMax;                // 2 words: 14
        int32_t ScanRange;              // 2 words: 16
        int32_t ScanStart;              // 2 words: 18
        int32_t ScanStop;               // 2 words: 20 
        int32_t ScanCount;              // 2 Words: 22
        int32_t Position;               // 2 words: 24
        int32_t MeanScanOffset;         // 2 words: 26
        int32_t MeanScanMin;            // 2 words: 28
        int32_t MeanScanMax;            // 2 words: 30  
        int32_t MeanScanRange;          // 2 words: 32
        int32_t MeanMinSD;              // 2 words: 34
        int32_t MeanMaxSD;              // 2 words: 36
        int16_t LRAWaveForm;            // 1 words: 37        
        _STATUS_FLAGS StatusFlags;      // 1 word : 38  
        int32_t LsPosition;             // 2 words: 40  
        int32_t RefPosition;            // 2 words: 42
        /** @brief start frequency used when looking for resonance frequency */       
        float   FreqStart;              // 2 words: 44 
        /** @brief limit frequency used when looking for resonance frequency */       
        float   FreqLimit;              // 2 words: 46 
        
        int32_t ScanMinSDLow;           // 2 words: 48
        int32_t ScanMaxSDLow;           // 2 words: 50
        
        int32_t OriginalZOff;           // 2 words: 52
        int32_t CurrentZOff;            // 2 words: 54
        int16_t ZOff_diff_dir;          // 1 words: 55
        int16_t Dummy16;                // 1 words: 56
        int32_t Dummy32[35];            // 70words: 126 

        uint32_t crc32;                 // 2 words: 128
    };

    /** @brief scan parameters object 16 bit type elements */   
    struct
    {
        int16_t LRADriveFreq[2];     // 2 words
        uint16_t LRADriveAMP[2];     // 2 words
        int16_t LRAResonantFreq[2];  // 2 words
        uint16_t LRAResonantAMP[2];  // 2 words
        int16_t ScanOffset[2];       // 2 words
        int16_t ScanMin[2];          // 2 words
        int16_t ScanMax[2];          // 2 words
        int16_t ScanRange[2];        // 2 words
        int16_t ScanStart[2];        // 2 words
        int16_t ScanStop[2];         // 2 words
        int16_t ScanCount[2];        // 2 words
        int16_t Position[2];         // 2 words
        int16_t MeanScanOffset[2];     //2 words
        int16_t MeanScanMin[2];   // 2 words
        int16_t MeanScanMax[2];    // 2 words
        int16_t MeanScanRange[2];        // 2 words
        int16_t MeanMinSD[2];         //2 words
        int16_t MeanMaxSD[2];         //2 words
        int16_t LRAWaveForm;         // 1 word       
        int16_t StatusFlags;         // 1 word 
        int16_t LsPosition[2];       // 2 words
        int16_t RefPosition[2];      // 2 words
        int16_t FreqStart[2];     // 2 words
        int16_t FreqLimit[2];     // 2 words
        int16_t ScanMinSDLow[2];// 2 words
        int16_t ScanMaxSDLow[2]; // 2 words
        
        int16_t OriginalZOff[2];           // 2 words: 52
        int16_t CurrentZOff[2];            // 2 words: 54
        int16_t ZOff_diff_dir;             // 1 words: 55
        int16_t Dummy16[71];            // 71words: 126


        uint32_t crc32;
    } Words;

    /** @brief scan parameters object byte type elements */
    struct 
    {
        int8_t LRADriveFreq[4];      // 4 bytes (2 words)
        uint8_t LRADriveAMP[4];      // 4 bytes (2 words)
        uint8_t LRAResonantAMP[4];   // 4 bytes (2 words)
        int8_t ScanOffset[4];        // 4 bytes (2 words)
        int8_t ScanMin[4];           // 4 bytes (2 words)
        int8_t ScanMax[4];           // 4 bytes (2 words)
        int8_t ScanRange[4];         // 4 bytes (2 words)
        int8_t ScanStart[4];         // 4 bytes (2 words)
        int8_t ScanStop[4];          // 4 bytes (2 words)
        int8_t ScanCount[4];         // 4 bytes (2 words)
        int8_t Position[4];          // 4 bytes (2 words)
        int8_t MeanScanOffset[4];    // 4 bytes (2 words)
        int8_t MeanScanMin[4];    // 4 bytes (2 words)
        int8_t MeanScanMax[4];     // 4 bytes (2 words)
        int8_t MeanScanRange[4];        // 4 bytes (2 words)
        int8_t MeanMinSD[4];         //4 bytes (2 words)
        int8_t MeanMaxSD[4];         //4 bytes (2 words)
        int8_t LRAWaveForm[2];       // 2 bytes (1 word)
        int8_t StatusFlags[2];       // 2 bytes (1 word)
        int8_t LsPosition[4];        // 4 bytes (2 words)
        int8_t RefPosition[4];       // 4 bytes (2 words)
        int8_t FreqStart[4];         // 4 bytes (2 words)
        int8_t FreqLimit[4];         // 4 bytes (2 words)
        int8_t  ScanMinSDLow[4];// 2 words
        int8_t  ScanMaxSDLow[4]; // 2 words
        int8_t OriginalZOff[4];           // 2 words: 52
        int8_t CurrentZOff[4];            // 2 words: 54
        int8_t  ZOff_diff[2];              // 1 words: 55
        int8_t  OriginalZDir[2];           // 1 words: 56
        int8_t ZOff_diff_dir[2];             // 1 words: 55
        int8_t Dummy8[142];            // 72words: 126

        uint32_t crc32;              // 4 bytes (2 words)
    } Bytes;       
} _LSC_DATA;                        // 128 words total          

/** @brief LRA motor input waveform enum defining type of the waveform  */
typedef enum
{
    /** @brief LRA sinusoidal waveform  */
    LRA_SINUSOID = 1, 
    /** @brief LRA squarewave waveform  */        
    LRA_SQUAREWAVE,
    /** @brief LRA sawtooth waveform */        
    LRA_SAWTOOTH
} _LRA_WAVEFORMS;

/** @brief LSC commands object defining current state of the LSC process, coming from pic32 efh  */
typedef enum
{
/** @brief send version command */ 
    LSC_GET_VERSION = 1,
/** @brief status flag start tuning process, re-initialise motion controller */     
    LSC_DEFINE_LIMITS = 2,
/** @brief status flag start scanning */            
    LSC_START_SCANNING = 3,
/** @brief status flag stop scanning */              
    LSC_STOP_SCANNING = 4,
/** @brief send device status to pic32 efh */            
    LSC_GET_STATUS = 5,
/** @brief soft MCU reset */             
    LSC_RESET = 255
} _LSC_COMMANDS;

/** @brief   */
typedef enum
{
    /** @brief */
    WAIT_FOR_FIRST_CYCLE = 0, 
    /** @brief */        
    NEW_SCAN_NOT_PRESENT,
    /** @brief */        
    NEW_SCAN_PRESENT,
} _SCAN_STATE;

/** @brief state of motor  */
typedef enum
{
    /** @brief motor stopped */
    MOTOR_STOPPED, 
    /** @brief motor started */        
    MOTOR_STARTED,
   /** @brief motor not specified state */        
    MOTOR_NOT_SPEC,         
} _MOTOR_STATE;

typedef struct
{
    /** @brief define minimum position of one interaction */
    int minpos;
    /** @brief define maximum position of one interaction */
    int maxpos;
    _SCAN_STATE new_scan_found;
    bool direction; // false = increasing; true = decreasing
    /** @brief set previous amplitude to 0 */
    TUNE_STATE_t tuning_process_flag;
    int32_t last_encoder_pos;    
    /** @brief define tuning phase*/
    _TUNING_PHASE tuning_phase;
    _EDGE_MET_REQ_STATE is_edge_met;
    /** @brief define frequency of the apex */
    float apex_freq;
    /** @brief define counter of last scan set with sd within limit */
    uint8_t last_scan_set_sd_count;
    /** @brief define counter of last scan below threshold */
    uint8_t last_scan_set_below_threshold_count;
    /** @brief define number of cycle */
    int32_t cycles;
    /* @brief define variables used for mean max, min ranges and mean max, min range standard deviation */
    double maxpos_avg;
    double minpos_avg;
    double maxpos_sd;
    double minpos_sd;
    int old_pos;
    /** @brief define previous tuning phase */
    _TUNING_PHASE prev_tuning_phase;
    /** @brief define previous frequency */
    float prev_freq;
    /** @brief define previous amplitude */
    uint32_t prev_amp;
    /** @brief define motor movement delay */
    _DELAY_STATE motor_movement_delay;
    /** @brief define state of motor */
    _MOTOR_STATE motor_state;
    /** @brief incremented whenever the monitor interrupt has no change in position */
    uint16_t enc_diff_zero_cnt;
    /** @brief count of number of time it has tried to get scans */
    uint16_t retry; 
    /** @brief quick tune retry count*/
    uint16_t qtune_retry_cnt; 
    /** @brief zpos failure retry count*/
    uint16_t zpos_retry_cnt; 
    
    uint8_t zpos_dir;
    
    uint8_t zpos_cur_dir; 
    
    int8_t zpos_diff; 
    
}_LSC_TUNING_OBJ;
//************************************************************************//  
// ISR
//************************************************************************//
///////** @brief ISR interrupt of quadrature encoder */
//////void 	__attribute__ ((interrupt, auto_psv)) _QEI1Interrupt(void);

//************************************************************************// 
// Function Prototypes
//************************************************************************//
int16_t main(void);
void Initialisation(void);
void  SetupDMA(void);
int32_t GetPosition(void);
void send_status( void );
bool CfgCount(bool dir);
bool ScnCount(bool dir);
int32_t AutoCentre(int32_t min, int32_t max);
void wake_up_call(void);
bool millisecond_elapsed(void); 
void reset_enc_move_wdt(void);
///////////////////////////////
/////for message exchange 
uint16_t SYS_version( void );
LSC_STATUS_t update_lsc_status_data( void );
//****************************************************************************// 
// Variable Definitions
//****************************************************************************//
 /** @brief LSC firmware version Major <0-9>.Minor <00-99*/
#define VERSION                     (uint16_t)((VERSION_MAJOR *100) + VERSION_MINOR)    

#define VERSION_MAJOR               1U
#define VERSION_MINOR               6U 

#define BUILD                       ((uint16_t)(00u))

 /** @brief auto centre global variable setting */
#define AUTO_CENTRE
 /** @brief wait until the desired number of full scans has been reached before starting data acquisition global variable setting */
//#define WAIT
 /** @brief LSC sinusoidal waveform global variable setting */
#define SINUSOID
 /** @brief define macro always re-tune */
//#define ALWAYS_RETUNE

 /** @brief Direct Memory Access global variable setting */
#define   DMA
//??
#define   NVM
 /** @brief define macro setting DAC electromagnetic motor maximum frequency */
#define DAC_MAX_FREQUENCY           500000U
 /** @brief define macro setting DAC electromagnetic motor maximum period */
#define DAC_MAX_PERIOD              300U

 /** @brief if def macro setting sinusoidal waveform define DAC electromagnetic motor parameters */
#ifdef SINUSOID
/** @brief define macro digital to analogue converter used is differential DAC */
#define DAC_DIFFERENTIAL        
#define DAC_WAVEFORM                LRA_SINUSOID
#define DAC_VOLTAGE_MIN 			205U
#define DAC_VOLTAGE_START 			1900U   
#define DAC_VOLTAGE_LIMIT 			3895U
#define DAC_SAMPLES                 ( DAC_MAX_FREQUENCY / DAC_MAX_PERIOD )  // Note: Must be a even number
 /** @brief if not def macro setting sinusoidal waveform define LRA squarewave waveform and DAC electromagnetic motor parameters */
#else
#define DAC_WAVEFORM                LRA_SQUAREWAVE
#define DAC_VOLTAGE_MIN 			205U
#define DAC_VOLTAGE_START 			3890U
#define DAC_SAMPLES                 2U
#endif
 /** @brief define macoro pi value */
#define PI                          3.14159265f
 /** @brief  define macro setting offset limit of */
#define LIMIT_OFFSET                100L
 /** @brief define macro setting count limit of scan start points and scan endpoints reaching for checking symmetry (checking if system resonates) */
#define LIMIT_COUNT                 20L
 /** @brief define macro setting time limit of waiting in ms for one scan finding trail to end */
#define LOOP_LIMIT                  250L 
 /** @brief define macro setting time limit of waiting */
#define WAIT_LIMIT                  50L
/** @brief define macro setting start frequency looking for resonance frequency tuning process */
#define FREQ_START                  195.000f        
 /** @brief define  macro setting limit frequency looking for resonance frequency tuning process */
#define FREQ_LIMIT                  225.000f        
/** @brief define macro setting large stepping up increment of frequency during frequency tuning process */
#define FREQ_INCREMENT_LARGE        2.0f
/** @brief define macro setting medium stepping up increment of frequency during frequency tuning process */
#define FREQ_INCREMENT_MEDIUM       0.5f
/** @brief define macro setting small stepping up and downc increment of frequency during frequency tuning process */
#define FREQ_INCREMENT_SMALL        0.1f
/** @brief define macro setting find true frequency offset during tuning process */
#define FREQ_FIND_TRUE_OFFSET       2.00f
/** @brief define macro setting frequency start offset during tuning process */
#define FREQ_START_OFFSET           0.00f
/** @brief define macro setting frequency start offset from apex during tuning process */
#define FREQ_START_APEX_OFFSET      8.0f
/** @brief define macro setting frequency limit offset from apex during tuning process */
#define FREQ_LIMIT_APEX_OFFSET      1.0f
/** @brief define macro setting AMPLITUDE start offset during tuning process */
#define AMP_START_OFFSET            0L
/** @brief define macro setting scan range condition to meet during frequency tuning process */
#define SCAN_RANGE                  5000L
/** @brief define macro setting max variation of the scan range condition to meet during frequency tuning process */
#define MAX_RANGE_DIFF              100L
/** @brief define macro setting large increment of amplitude during frequency-amplitude tuning process */
#define VOLTAGE_INCREMENT_LARGE     200U
/** @brief define macro setting move to find freq increment of amplitude during frequency-amplitude tuning process */
#define VOLTAGE_INCREMENT_MOVE_TO_FIND_FREQ     120U
/** @brief define macro setting small increment of amplitude during frequency-amplitude tuning process */
#define VOLTAGE_INCREMENT_SMALL     20U
/** @brief define macro setting long tuning increment of amplitude during frequency-amplitude tuning process */
#define VOLTAGE_INCREMENT_LONG_TUNING     80U
/** @brief define macro mean scan range requirement i.e. threshold for Leslay's forbiden heights */ 
#define MEAN_SCAN_RANGE_REQ         5500L
/** @brief define macro last scan set number requirement */
#define LAST_SCAN_SET_NUM_REQ        3L
/** @brief define macro standard deviation threshold for stable scan */
#define STABLE_SCAN_SD_THRESHOLD     66L
/** @brief define macro scan range long tuning distribution requirement */
#define SCAN_RANGE_DIST_LONG_TUNING_REQ     2550L
/** @brief define macro scan range short tuning distribution requirement */
#define SCAN_RANGE_DIST_SHORT_TUNING_REQ   2500L
/** @brief define macro scan range move along edge condition */
#define SCAN_RANGE_START_MOVE_ALONG_EDGE_COND 5100L

#define SCAN_RANGE_FREQ_FAIL_COND   4600L

#define SCAN_RANGE_QTUN_FAIL_COND   4800L
/** @brief define macro tuning data delay */
#define COLLECT_DATA_DELAY             15U
/** @brief define motor delay */
#define MOTOR_DELAY                    40000U
/** @brief if def macro setting auto centre option set the position offset to 0 */
#ifndef AUTO_CENTRE
#define POSITION_OFFSET             0L       //  #3
#else
 /** @brief if not def macro setting auto centre option set the position of carrige offset to 0 position of scan range */
#define POSITION_OFFSET             0L       //  Auto Centre enabled
#endif
 /** @brief if def macro setting debug set scan limit to 1000 */
#ifdef DEBUG
#define SCAN_LIMIT  				1000L
 /** @brief if not def macro setting debug set scan limit to 1000000 */
#else
#define SCAN_LIMIT  				1000000L    
#endif
 /** @brief forward movement */
#define FWD 						1
 /** @brief backward movement */
#define BCK 						0
/** @brief define macro state of latch 1 port C of RC1 pin*/
#define LSC_BUSY LATCbits.LATC1
/** @brief define macro state of latch 2 port C of RC2 pin*/
#define LSC_DIR LATCbits.LATC2

/** @brief define macro reading state of  RB2 */
#define CHA PORTBbits.RB2
/** @brief define macro reading state of RB1 */
#define CHB PORTBbits.RB1
/** @brief define macro reading state of RB5 */
#define Z   PORTBbits.RB5

/** @brief define macro reading state of latch 4 */	
#define LED1  LATAbits.LATA4 

/** @brief quadrature encoder interface control register QEI1IOC and status control register QEI1STAT setting for enabling interface */
/** @brief QEI1IOCbits.OUTFNC - Module Output Function disabled, 
 *         QEI1STATbits.PCHEQIRQ - Position Counter Greater Than Compare Status bit:  POSxCNT < QEIxGEC,
 *         QEI1STATbits.PCLEQIRQ - Position Counter Less Than Compare Status bit: POSxCNT > QEIxLEC, 
 *         QEI1STATbits.POSOVIRQ - Position Counter Overflow Status bit: No overflow has occurred,
 *         QEI1STATbits.PCHEQIEN - Position Counter Overflow Interrupt Enable bit: Interrupt is enabled, 
 *         QEI1STATbits.PCLEQIEN - Position Counter Greater Than Compare Interrupt Enable bit: Interrupt is enabled,
 *         IFS3bits.QEI1IF - Interrupt flag for QEI Position Counter Compare: cleaned,
 *         IEC3bits.QEI1IE - Interrupt QEI Position Counter Compare: enabled  */
#define m_EnablePMInts() {  QEI1IOCbits.OUTFNC = 0b00;      \
                            QEI1STATbits.PCHEQIRQ = false;  \
                            QEI1STATbits.PCLEQIRQ = false;  \
                            QEI1STATbits.POSOVIRQ = false;  \
                            QEI1STATbits.POSOVIEN = false;  \
                            QEI1STATbits.PCHEQIEN = true;   \
                            QEI1STATbits.PCLEQIEN = true;   \
                            IFS3bits.QEI1IF = false;        \
                            IEC3bits.QEI1IE = true;         }
/** @brief quadrature encoder interface control register QEI1IOC and status control register QEI1STAT setting for disabling interface */
/** @brief QEI1IOCbits.OUTFNC - Module Output Function disabled, 
 *         QEI1STATbits.PCHEQIRQ - Position Counter Greater Than Compare Status bit:  POSxCNT < QEIxGEC,
 *         QEI1STATbits.PCLEQIRQ - Position Counter Less Than Compare Status bit: POSxCNT > QEIxLEC, 
 *         QEI1STATbits.POSOVIRQ - Position Counter Overflow Status bit: No overflow has occurred,
 *         QEI1STATbits.PCHEQIEN - Position Counter Overflow Interrupt Enable bit: Interrupt is disabled, 
 *         QEI1STATbits.PCLEQIEN - Position Counter Greater Than Compare Interrupt Enable bit: Interrupt is disabled,
 *         IFS3bits.QEI1IF - Interrupt flag for QEI Position Counter Compare: cleaned,
 *         IEC3bits.QEI1IE - Interrupt QEI Position Counter Compare: disabled  */
#define m_DisablePMInts() { QEI1IOCbits.OUTFNC = 0b00;      \
                            QEI1STATbits.POSOVIEN = false;  \
                            QEI1STATbits.PCHEQIEN = false;  \
                            QEI1STATbits.PCLEQIEN = false;  \
                            QEI1STATbits.PCHEQIRQ = false;  \
                            QEI1STATbits.PCLEQIRQ = false;  \
                            QEI1STATbits.POSOVIRQ = false;  \
                            IEC3bits.QEI1IE = false;        \
                            IFS3bits.QEI1IF = false;        }

/** @brief define macro Interrupt QEI Position Counter Compare enabled */
#define m_EnableQEIInt()  { IFS3bits.QEI1IF = false; IEC3bits.QEI1IE = true;  }
/** @brief define macro Interrupt QEI Position Counter Compare disabled */
#define m_DisableQEIInt() { IEC3bits.QEI1IE = false; IFS3bits.QEI1IF = false; }
 
/** @brief define macro LED1 on */
#define m_LED1_On()         LED1  = 0;
/** @brief define macro LED1 off */
#define m_LED1_Off()        LED1  = 1;
/** @brief define macro LED1 toggle */
#define m_LED1_Toggle()     LED1  = !LED1;


       		      
//****************************************************************************//
// WHAT IS THE PURPOUSE ??
 /** @brief if def macro setting Direct Memory Access option set the power supply voltage to motor index to 0 */
#ifndef DMA
static uint16_t VM_INDEX = 0U;
#endif       
//****************************************************************************//


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

