/* ************************************************************************** */
/** @file motor_drv.h
 *
 *  @brief Motor driver header file.
 *
 *  @copyright Occuity Limited (c) 2021
 */
/* ************************************************************************** */
/* ************************************************************************** */


#ifndef MOTOR_DRIVER_H
#define	MOTOR_DRIVER_H
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
void DMA_Channel0_CallBack(void);
void GenerateDACProfile(_LRA_WAVEFORMS waveform, uint16_t * profile, uint16_t len, uint16_t vmin, uint16_t vmax);
bool StartDACOutput(float frequency, bool start);
void StartMotion(uint32_t scans, bool enqei);
void StopMotion(void);


#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_DRIVER_H */
