/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    drv_dac_ad5667r.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DRV_DAC_AD5667R_H    /* Guard against multiple inclusion */
#define _DRV_DAC_AD5667R_H

/*******************************************************************************
                            Includes Files
*******************************************************************************/
#include "definitions.h"

/*******************************************************************************
                            Macros
*******************************************************************************/
#define DRV_DAC_LDAC_ENABLED			 0x00
#define DRV_DAC_LDAC_DISABLED            0x03
#define DRV_DAC_INTERNAL_REF_OFF		 0x00
#define DRV_DAC_INTERNAL_REF_ON			 0x01
#define	DRV_DAC_RESET_DAC				 0x00
#define DRV_DAC_RESET_ALL	 		     0x01
#define DRV_DAC_PDM_NORMAL				 0x00
#define DRV_DAC_PDM_1K					 0x10
#define DRV_DAC_PDM_100K				 0x20
#define DRV_DAC_PDM_TSHI				 0x30

#define DRV_DAC1_DEFAULT                 32768U
#define DRV_DAC2_DEFAULT                 32768U

typedef enum
{
    DRV_DAC_1 = 0x00,     
    DRV_DAC_2,
    DRV_DAC_3,
    DRV_DAC_4, 
    DRV_DAC_ALL = 0xFF,        
} DRV_DAC_INDEX;

typedef enum
{
    DRV_DAC_ERROR_UNINITIALISED,    
    DRV_DAC_ERROR_NONE,    
    DRV_DAC_ERROR_I2C,
    DRV_DAC_ERROR_I2C_WRITE,
    DRV_DAC_ERROR_I2C_READ,
    DRV_DAC_ERROR_I2C_INVALID_STATE,
    DRV_DAC_ERROR_I2C_INVALID_HANDLE,
} DRV_DAC_ERROR;
/* ************************************************************************** */



/* Provide C++ Compatibility */
#ifdef __cplusplus
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

bool drv_dac_ad5667r_controller_task(void);

void drv_dac_reset(void);
void drv_dac_set_ldac(uint8_t ldac);
void drv_dac_set_reference(uint8_t ref);
void drv_dac_set_power_mode(uint8_t pmode);
void drv_dac_set_value(DRV_DAC_INDEX dac, uint16_t value);
uint16_t drv_dac_get_value(DRV_DAC_INDEX dac);
bool drv_dac_busy(void);
DRV_DAC_ERROR drv_dac_get_last_error(void);
void drv_dac_clear_error(void);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DRV_DAC_AD5667R_H */
