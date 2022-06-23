/*****************************************************************************
 *   File        : PowerControl.c
 *
 *   Description : Source Code for implementation of maximum power tracking of
 * PWM for pump
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018 - 2021 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#include "PowerControl.h"
#include "DeviceStatus.h"
#include "StateMachineTherapyDelivery.h"
#include "mcc.h"
#include "tmr1.h"

// The following line is Commented out to avoid PC-lint (750) issue. local macro 'PWM_EN' (Location) not referenced.
//#define PWM_EN  (0x80)
#define FVR_EN  (0x80)
#define AD_FVR  (0x01)
#define TS_EN  (0x20) //Temperature indicator enable bit
// The following line is Commented out to avoid PC-lint (750) issue. local macro 'OSC_SUPPLY_MASK' (Location) not referenced.
//#define OSC_SUPPLY_MASK (0x20)  //RB5
#define I2C_TX_MASK     (0xD0)  //RB4, 6, 7
static uint8_t initBoostDemand = VBOOST_REF;
static uint8_t boostDemand = VBOOST_REF;


/************************************************
 *  @brief   Disable peripherals for power saving purpose. All pins
 *           are set to output except the following: RA0, RA1, RA4, RA5,
 *  @param   None
 *  @return  None
 *
 *************************************************/
void MP_DisablePeripheral(void)
{
    MP_DisablePumpPWM();

    // Turn off ADC unit
    ADCON0bits.ADON = 0;

    // Turn off DAC
    DACCON0 = 0x10;

    // Turn off NCO
    NCO1CONbits.N1EN = 0;

    LATA   = 0x00;
    TRISA  = 0x2B; //keep uC_SW, ICSPDAT, ICSPCLK configured as input to listen to ext interrupt
    ANSELA = 0x00;
    WPUA   = 0x00;

    // Make I2C and spare UART line output zero in sleep
    LATB  &= ~I2C_TX_MASK;
    TRISB &= ~I2C_TX_MASK;
    ANSELB = 0x00;
    WPUB   = 0x00;

    // Make ADC lines as zero output in sleep
    LATC   = 0x00;
    TRISC  = 0x00;
    ANSELC = 0x00;

    CM1CON0 = 0x00;
    CM2CON0 = 0x00;

    FVRCON  = 0;
}

void MP_SleepUntilWokenByRelaxationOscillator(void)
{
    // Enable oscillator so we get woken up every tick
    MP_EnableRelaxationOscillator();
  
    // Halt CPU
    asm ("sleep");
}

/************************************************
 *  @brief   Apply power to main circuit (needed
 *           to power LED's and Boost Converter)
 *  @param   None
 *  @return  None
 *
 *************************************************/
void MP_EnableMainCircuitPower(void)
{
    LATC4   = 1;
    FVRCON |= (FVR_EN | AD_FVR | TS_EN); //0xA1
}

/************************************************
 *  @brief   Enables the FVR for the  ADC
 *           operations
 *  @param   None
 *  @return  None
 *
 *************************************************/
void MP_EnableFvr(void)
{
    FVRCON |= (FVR_EN | AD_FVR);
}

/************************************************
 *  @brief   Enables the Temperature Indicator
 *           sensor integrated with the chip
 *  @param   None
 *  @return  None
 *
 *************************************************/
void MP_EnableTemperatureIndicator(void)
{
    FVRCON |= (TS_EN);
}

/************************************************
 *  @brief   Remove power from main circuit (needed
 *           to power LED's and Boost Converter)
 *  @param   None
 *  @return  None
 *
 *************************************************/
void MP_DisableMainCircuitPower(void)
{
    LATC4   = 0;
    FVRCON &= ~(FVR_EN | AD_FVR | TS_EN); //0x25
}

/***********************************************
 *  @brief   Return main circuit status (needed
 *           to power LED's and Boost Converter)
 *  @param   None
 *  @return  TRUE or FALSE
 *
 *************************************************/
bool_t isMainCircuitPowerEnabled(void)
{
    return ((bool_t) ((1 == LATC4) && (FVRCON & FVR_EN) && (FVRCON & AD_FVR)));
}

/************************************************
 *  @brief   Set Boost reference Voltage
 *  @param   Voltage in mV
 *  @return  None
 *
 *************************************************/
void MP_SetReferenceVoltageBoost(uint8_t demand)
{
    DACCON0 = 0x90;
    DAC_SetOutput((uint8_t) ((demand > VBOOST_REF_MAX) ? VBOOST_REF_MAX : demand));
}

/************************************************
 *  @brief   Get the initial Boost Demand value
 *  @param   None
 *  @return  None
 *
 *************************************************/
uint8_t MP_GetInitBoostDemand(void)
{
    return initBoostDemand;
}

/************************************************
 *  @brief   Set the initial Boost Demand value
 *  @param   None
 *  @return  None
 *
 *************************************************/
void MP_SetInitBoostDemand(uint8_t demand)
{
    initBoostDemand = demand;
}

/************************************************
 *  @brief   Get latest boost demand value
 *  @param   None
 *  @return  Voltage not in mV but DAC value
 *
 *************************************************/
uint8_t MP_GetBoostDemand(void)
{
    return boostDemand;
}

/************************************************
 *  @brief   Set latest boost demand value
 *  @param   Voltage not in mV but DAC value
 *  @return  None
 *
 *************************************************/
void MP_SetBoostDemand(uint8_t demand)
{
    boostDemand = demand;
}


/************************************************
 *  @brief   Activate PWM on pump
 *  @param   None
 *  @return  None
 *
 *************************************************/
void MP_EnablePumpPWM(void)
{
    // Enable the NCO module
    NCO1CONbits.N1EN = 1;
    // Clearing IF flag before enabling the interrupt.
    PIR2bits.NCO1IF = 0;

    LATC3 = 1;
}

/************************************************
 *  @brief   Return Pump PWM status
 *  @param   None
 *  @return  TRUE or FALSE
 *
 *************************************************/
bool_t isPumpPwmEnabled(void)
{
    return ((bool_t) ((1 == NCO1CONbits.N1EN) && (0 == PIR2bits.NCO1IF) && (1 == LATC3)));
}

/************************************************
 *  @brief   Deactivate PWM on pump
 *  @param   None
 *  @return  None
 *
 *************************************************/
void MP_DisablePumpPWM(void)
{
    // Disable the NCO module
    NCO1CONbits.N1EN = 0;
    // Clearing IF flag before enabling the interrupt.
    PIR2bits.NCO1IF = 0;

    LATC3 = 0;
}

/************************************************
 *  @brief   Apply power to external peripherals
 *           (Pump current measurements, Pressure
 *           Sensors, Memory device, Accelerometer)
 *  @param   None
 *  @return  None 
 *************************************************/
void MP_EnableExternalPeripheralsSupply(void)
{
    LATC2 = 1;
}

/************************************************
 *  @brief   Remove power from external peripherals
 *           (Pump current measurements, Pressure
 *           Sensors, Memory device, Accelerometer)
 *  @param   None
 *  @return  None 
 *************************************************/
void MP_DisableExternalPeripheralsSupply(void)
{
    LATC2 = 0;
}

void MP_EnableRelaxationOscillator()
{
    //Enable the interrupt that listens to the oscillator
    IOCAN4 = 1;
    //Enable oscillator supply
    LATB5 = 1;
}


void MP_DeepSleep(void)
{ 
    // Halt CPU
    asm ("sleep");
    
    // Get out of deep sleep and start TMR1
    TMR1_StartTimer();
}
