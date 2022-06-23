/* ************************************************************************** */
/** @file LRS_tuning.h
 *
 *  @brief LRS tuning header file.
 *
 *  @copyright Occuity Limited (c) 2021
 */
/* ************************************************************************** */
/* ************************************************************************** */

#ifndef LRS_TUNING_H
#define	LRS_TUNING_H
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <xc.h>
#include "main.h"
#ifdef	__cplusplus
extern "C" {
#endif

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

    
// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
    
// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

int32_t AutoCentre(int32_t min, int32_t max);
void log_scan_settings(const char *colour, double prev_freq, double prev_amp);
void Tuning_Init(bool);
void Tuning_Collect_Data(void);
void Calculate_Tuning_Data_Mean(void);
void Tuning_Failed(void);
void Tuning_Decision(void);
void Move_To_Move_Along_Edge(void);
bool Increase_Amplitude_by_Large_Step(void);
void Tuning_Coarse_Sweep(void);
void Decrease_Amplitude(void);
void Move_Further_Along_Edge(void);
void Move_To_Find_Res_Freq(void);
void Move_To_Coarse_Sweep(void);
void Tuning_Move_Along_Edge(void);
void Resonace_Freq_Found(void);
void Scan_Set_Below_Threshold(void);
void Keep_Looking_Res_Freq(void);
void Tuning_Find_Resonance_Frequency(void);
void Move_Long_Tuning(void);
void Tuning_Quick(void);
void Tuning_Update_Data(void);
void Tuning_Clear_Data(void);
void Tuning_Delay(void);
void DefineLimits_task(void);

void Tuning_tick(void); 


    
/* Provide C++ Compatibility */    
#ifdef	__cplusplus
}
#endif

#endif	/* LRS_TUNING_H */

