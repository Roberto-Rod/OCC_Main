/*******************************************************************************
  OVM7692 Camera Driver Local Data Structures

  Company:
    Microchip Technology Inc.

  File Name:
    drv_camera_OVM7692.h

  Summary:
    OVM7692 Camera Driver local data structures.

  Description:
    This header file provides the local data structures for the OVM7692 Camera
	Driver Library.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 ******************************************************************************/
// DOM-IGNORE-END

#ifndef _DRV_CAMERA_OVM7692_H
#define _DRV_CAMERA_OVM7692_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "configuration.h"
#include "definitions.h"
#include "drv_camera.h"
#include "drv_camera_sccb.h"
#include "system/time/sys_time.h"
#include "system/system.h"
#include "system/int/sys_int.h"
#include "system/dma/sys_dma.h"
#include "system/ports/sys_ports.h"
#include <sys/kmem.h>
#include "gfx/utils/gfx_utils.h"

#ifdef __cplusplus
    extern "C" {
#endif
        
// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* OVM7692 Camera Driver Module Index

  Summary:
    OVM7692 driver index definitions.

  Description:
    These constants provide OVM7692 Camera Driver index definitions.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.
    These values should be passed into the DRV_CAMERA_OVM7692_Initialize and
    DRV_CAMERA_OVM7692_Open routines to identify the driver instance in use.
*/
        
//#define DEV_BOARD
//#define PAN_DEFAULT        

#define DRV_CAMERA_OVM7692_INDEX_0        0
#define DRV_CAMERA_OVM7692_INDEX_1        1
        
//#define DRV_USE_DDR         
        
#define  DRV_FRAME_BUFFER_1         0xA8000000
#define  DRV_FRAME_BUFFER_2         0xA8084D00        
        
/**************************** Register Definitions ****************************/
/***** CLKRC ******/  
#define CLKRC_XCLK_DPLLEN           0b10000000        
#define CLKRC_XCLK_NOSCALE          0b01000000
#define CLKRC_XCLK_PRESCALE_1       0b00000000        
#define CLKRC_XCLK_PRESCALE_2       0b00000001
#define CLKRC_XCLK_PRESCALE_4       0b00000010
#define CLKRC_XCLK_PRESCALE_8       0b00000100
#define CLKRC_XCLK_PRESCALE_16      0b00001000
#define CLKRC_XCLK_PRESCALE_32      0b00010000        
        
#define CLKRC_DEFAULT               CLKRC_XCLK_PRESCALE_1
        
/***** REG13 ******/      
#define REG13_FAST_AGC              0b10000000      // Enable Fast AGC/AEC        
#define REG13_AEC_LIMIT             0b01000000      // Limit AEC step size    
#define REG13_BF_EN                 0b00100000      // Enable Banding filter 
#define REG13_AEC_BANDING           0b00010000      // Enabl AEC Banding  
#define REG13_TP_EXP_EN             0b00001000      // Enable TP Exposure       
#define REG13_AGC_AUTO              0b00000100      // Enable AGC 
#define REG13_AWB_AUTO              0b00000010      // Enable AWB  
#define REG13_EXP_AUTO              0b00000001      // Enable Auto Exposure  

#define REG13_DEFAULT               REG13_FAST_AGC | REG13_AEC_LIMIT | REG13_BF_EN | REG13_AEC_BANDING | REG13_TP_EXP_EN | REG13_AGC_AUTO | REG13_AWB_AUTO | REG13_EXP_AUTO        
            
/***** REG14 ******/      
#define REG14_FIELD_SAME            0b10000000      // Field 0 and 1 have same frame length        
#define REG14_AGC_LIM_2             0b00000000      // Limit AGC limit 2x
#define REG14_AGC_LIM_4             0b00010000      // Limit AGC limit 4x
#define REG14_AGC_LIM_8             0b0100000       // Limit AGC limit 8x
#define REG14_AGC_LIM_16            0b00110000      // Limit AGC limit 16x        
#define REG14_AGC_LIM_32            0b01000000      // Limit AGC limit 32x 
#define REG14_AGC_LIM_64            0b01010000      // Limit AGC limit 64x 
#define REG14_AGC_LIM_128           0b01100000      // Limit AGC limit 128x         
        
#define REG14_RESERVED              0b00001000      // Reserved 
#define REG14_DROP_VS               0b00000100      // Drop Vsync of corrupt frames  
#define REG14_B_FILT_MAN            0b00000010      // Banding filter in manual mode       
#define REG14_B_FILT_50             0b00000001      // Banding filter 50Hz
  
#define REG14_DEFAULT               REG14_AGC_LIM_4 | REG14_RESERVED  |  REG14_B_FILT_MAN | REG14_B_FILT_50         
//#define REG14_DEFAULT               0x3B            // Panther Default        
      
            
/***** REG16 ******/      
#define REG16_DEF_HSIZE             0b01000000      // LSB       
#define REG16_HOFF                  0b00010000      // Horizontal Offset    
#define REG16_VOFF                  0b00100000      // Vertical offset 
#define REG16_LOW_PCLK              0b00000010      // PCLK Slowed  
#define REG16_RESERVED              0b00000101             
        
#define REG16_DEFAULT               REG16_RESERVED       
/***** HSIZE ******/       
#define HSIZE_640                   160 
#define HSIZE_480                   120   
#define HSIZE_360                   90        
#define HSIZE_320                   80
#define HSIZE_240                   60        
        
//#define HSIZE_DEFAULT               DRV_CAMERA_FRAME_WIDTH >> 2
#define HSIZE_DEFAULT               HSIZE_480
/***** VSIZE ******/   
#define VSIZE_480                   240   
#define VSIZE_440                   220        
#define VSIZE_320                   160
#define VSIZE_240                   120          
        
//#define VSIZE_DEFAULT               DRV_CAMERA_FRAME_HEIGHT >> 1    
#define VSIZE_DEFAULT                VSIZE_440
        
/***** REG0C ******/        
#define REG0C_VFLIP                 0b10000000
#define REG0C_HFLIP                 0b01000000
#define REG0C_BRFLIP                0b00100000
#define REG0C_YUV_SWAP              0b00010000
#define REG0C_DVP_REVERSE           0b00001000        
#define REG0C_CLK_OUTPUT            0b00000100
#define REG0C_CLK_TRISTATE          0b00000000
#define REG0C_VHP_OUTPUT            0b00000010        
#define REG0C_VHP_TRISTATE          0b00000000       
#define REG0C_COL_BAR               0b00000001         
        
#define REG0C_DEFAULT               REG0C_CLK_OUTPUT | REG0C_VHP_OUTPUT | REG0C_VFLIP | REG0C_HFLIP
/***** REG0E ******/        

#define REG0E_RESERVED              0b11110000        
#define REG0E_SLEEP_MODE            0b00001000
#define REG0E_NORMAL_MODE           0b00000000         
#define REG0E_OUTPUT_RANGE_FULL     0b00000000
#define REG0E_OUTPUT_RANGE_8MSB     0b00000100
#define REG0E_OUTPUT_CURRENT_1X     0b00000000        
#define REG0E_OUTPUT_CURRENT_2X     0b00000001      
#define REG0E_OUTPUT_CURRENT_3X     0b00000010    
#define REG0E_OUTPUT_CURRENT_4X     0b00000011

#ifdef DEV_BOARD        
#define REG0E_DEFAULT               REG0E_NORMAL_MODE | REG0E_OUTPUT_RANGE_FULL | REG0E_OUTPUT_CURRENT_1X     
#else
#define REG0E_DEFAULT               REG0E_NORMAL_MODE | REG0E_OUTPUT_RANGE_FULL | REG0E_OUTPUT_CURRENT_1X        
#endif
//#define REG0E_DEFAULT               0x00            // Panther Default
        
/***** REG12 ******/
#define REG12_SOFT_RESET            0b10000000
#define REG12_FORMAT_RGB565         0b00000110
#define REG12_FORMAT_RAW            0b00000111
#define REG12_FORMAT_YUV            0b00000100
#define REG12_SKIP_MODE_EN          0b01000000
#define REG12_ITU656_ENABLE         0b00100000  
#define REG12_RAW_DATA_OUT          0b00010000        
       
#define REG12_DEFAULT               REG12_FORMAT_RGB565
//#define REG12_DEFAULT               0x46            // Panther Default
        
/***** REG15 ******/        
#define REG15_AUTO_FRAME_RATE_ON    0b10000000
#define REG15_AUTO_FRAME_RATE_OFF   0b00000000        
#define REG15_AUTO_FRATE_OFF        0b01000000
#define REG15_AUTO_FRATE_50         0b00010000      // Percent
#define REG15_AUTO_FRATE_33         0b01010000
#define REG15_AUTO_FRATE_25         0b00111000        
#define REG15_AUTO_FRATE_12         0b01000000
#define REG15_AUTO_FRATE_AGC1       0b00000000
#define REG15_AUTO_FRATE_AGC2       0b00000100  
#define REG15_AUTO_FRATE_AGC3       0b00001000    
#define REG15_AUTO_FRATE_AGC4       0b00001100 
#define REG15_DIGITAL_GAIN_OFF      0b00000000  
#define REG15_DIGITAL_GAIN_2X       0b00000001
#define REG15_DIGITAL_GAIN_4X       0b00000011
        
        
#ifdef DEV_BOARD        
#define REG15_DEFAULT               REG15_AUTO_FRAME_RATE_OFF | REG15_DIGITAL_GAIN_OFF   
#else
#define REG15_DEFAULT               REG15_AUTO_FRAME_RATE_OFF | REG15_DIGITAL_GAIN_2X        
#endif        
     
   
        
/***** REG28 ******/        
#define REG28_INVERSE_IMAGE         0b10000000
#define REG28_HREF_TO_HSYNC         0b01000000
#define REG28_HSYNC_REVERESE        0b00100000
#define REG28_HREF_REVERSE          0b00010000
#define REG28_VSYNC_ACTIVE_FALL     0b00000000        
#define REG28_VSYNC_ACTIVE_RISE     0b00000100
#define REG28_VSYNC_NEGATIVE        0b00000010   
        
#define REG28_DEFAULT               REG28_HREF_REVERSE | REG28_VSYNC_ACTIVE_FALL 
        
/***** REG3E ******/        
#define REG3E_PCLK_GATED_BY_HREF    0b01000000
#define REG3E_PCLK_FREE_RUNNING     0b00000000
#define REG3E_PCLK_DIV              0b00000000
        
#define REG3E_DEFAULT               REG3E_PCLK_GATED_BY_HREF

/***** REG61 ******/            
#define REG61_TP_OFF                0b00000000      
#define REG61_TP_ON                 0b01000000  
#define REG61_TP_10BIT_1            0b00000000          
#define REG61_TP_10BIT_2            0b00010000         
#define REG61_TP_8BIT_1             0b00100000 
#define REG61_TP_8BIT_2             0b00110000 

#define REG61_DEFAULT               REG61_TP_OFF | REG61_TP_8BIT_1
        
/***** REG80 ******/      
#define REG80_VARIO_EN              0b10000000      // Enable Vario Pixel        
#define REG80_CIP_EN                0b01000000      // Enable CIP    
#define REG80_BC_EN                 0b00100000      // Enable BC 
#define REG80_WC_EN                 0b00010000      // Enable WC  
#define REG80_GAMMA_EN              0b00001000      // Enable Gamma Correction       
#define REG80_AWB_GAIN_EN           0b00000100      // Enable White Balance Gain
#define REG80_AWB_EN                0b00000010      // Enable White Balance Control  
#define REG80_LENC_EN               0b00000001      // Enable Lens Correction  


#ifdef DEV_BOARD        
#define REG80_DEFAULT               REG80_CIP_EN |  REG80_BC_EN | REG80_WC_EN | REG80_GAMMA_EN | REG80_AWB_GAIN_EN | REG80_AWB_EN | REG80_LENC_EN  
#else
#define REG80_DEFAULT               REG80_VARIO_EN | REG80_CIP_EN |  REG80_BC_EN | REG80_WC_EN | REG80_GAMMA_EN | REG80_AWB_GAIN_EN | REG80_AWB_EN | REG80_LENC_EN      
#endif           
//#define REG80_DEFAULT               0x7F            // Panther Default
         
/***** REG81 ******/      
#define REG81_RESERVED              0b11000000      // Reserved           
#define REG81_SDE_EN                0b00100000      // Enable SDE 
#define REG81_UV_ADJ_EN             0b00010000      // Enable UV Adjustement  
#define REG81_SCALE_V_EN            0b00001000      // Enable Vertical Scaling       
#define REG81_SCALE_H_EN            0b00000100      // Enable Horizontal Scaling
#define REG81_UV_AVG_EN             0b00000010      // Enable UV Averaging
#define REG81_CMX_EN                0b00000001      // Enable CMX  
        
#define REG81_DEFAULT               REG81_RESERVED | REG81_SDE_EN | REG81_UV_ADJ_EN | REG81_SCALE_V_EN  | REG81_SCALE_H_EN | REG81_UV_AVG_EN | REG81_CMX_EN         
//#define REG81_DEFAULT               0x3F            // Panther Definition
        
/***** REGD2 ******/      
#define REGD2_FIXY_EN               0b10000000      //            
#define REGD2_NEG_EN                0b01000000      // Enable Negative Image 
#define REGD2_GRAY_EN               0b00100000      // Enable Grayscale  
#define REGD2_FIXV_EN               0b00010000      //        
#define REGD2_FIXU_EN               0b00001000      // 
#define REGD2_CONT_EN               0b00000100      // 
#define REGD2_SAT_EN                0b00000010      // Enable Saturation 
#define REGD2_HUE_EN                0b00000001      // Enable Hue        
#define REGD2_NO_CORR               0b00000000      // Disable all color correction       
        
#ifdef DEV_BOARD        
#define REGD2_DEFAULT               REGD2_NO_CORR
#else
#define REGD2_DEFAULT               REGD2_NO_CORR    
#endif           

//#define REGD2_DEFAULT               0x00            // Panther Default
        
/***** REGD3 ******/      
       
#define REGD3_DEFAULT               0b00000000          
        
/***** MIPI_BANK ******/    
#define MIPI_BANK_SEL               0b00000001        
#define MIPI_SCR_SEL                0b00000000        
        
/***** MIPI_COM0 ******/            
#define MIPI_COM0_ENA               0b10000000      
#define MIPI_COM0_DIS               0b00000000  
#define MIPI_COM0_8BIT              0b10000000          
#define MIPI_COM0_10BIT             0b00000000         
#define MIPI_COM0_TEST              0b00010000 
#define MIPI_COM0_CLK_1             0b00000000 
#define MIPI_COM0_CLK_2             0b00000001 
#define MIPI_COM0_CLK_3             0b00000010 
#define MIPI_COM0_CLK_4             0b00000011

#define MIPI_COM0_DEFAULT           MIPI_COM0_DIS | MIPI_COM0_8BIT                        
                          
// *****************************************************************************
/* OVM7692 Camera Driver SCCB Write ID

  Summary:
    OVM7692 Camera SCCB Interface device Write Slave ID.

  Description:
    This macro provides a definition of the OVM7692 Camera SCCB Interface device Write 
    Slave ID.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.
    These values should be passed into the DRV_CAMERA_OVM7692_RegisterSet 
    function to identify the OVM7692 Camera SCCB Interface device Write Slave ID.
   
*/

#define DRV_CAMERA_OVM7692_SCCB_ID /*DOM-IGNORE-BEGIN*/ 0x3C /*DOM-IGNORE-END*/

// *****************************************************************************
/* OVM7692 Camera Driver Soft reset flag.

  Summary:
    OVM7692 Camera Driver Register 0x12 Soft reset flag.

  Description:
    This macro provides a definition of the OVM7692 Camera Register 0x12 Soft reset 
    flag.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.
*/

#define DRV_CAMERA_OVM7692_REG12_SOFT_RESET /*DOM-IGNORE-BEGIN*/ 0x80 /*DOM-IGNORE-END*/

// *****************************************************************************
/* OVM7692 Camera Error flag

  Summary:
    Identifies OVM7692 Camera possible errors.

  Description:
    This enumeration defines possible OVM7692 Camera errors.

  Remarks:
    This enumeration values are returned by driver interfaces in case of errors.
*/
typedef enum
{
    /* OVM7692 Camera Driver Invalid Handle */
    DRV_CAMERA_OVM7692_ERROR_INVALID_HANDLE = 0,

    /* OVM7692 Camera Driver Invalid Handle */
    DRV_CAMERA_OVM7692_ERROR_INVALID_INDEX,
            
    /* OVM7692 Camera Driver error none */
    DRV_CAMERA_OVM7692_ERROR_NONE,
    
} DRV_CAMERA_OVM7692_ERROR;

// *****************************************************************************
/* OVM7692 Camera Client Status.

  Summary:
    Identifies OVM7692 Camera possible client status.

  Description:
    This enumeration defines possible OVM7692 Camera Client Status.

  Remarks:
    This enumeration values are set by driver interfaces:
    DRV_CAMERA_OVM7692_Open and DRV_CAMERA_OVM7692_Close.
*/
typedef enum
{
    /* An error has occurred.*/
    DRV_CAMERA_OVM7692_CLIENT_STATUS_ERROR    = DRV_CLIENT_STATUS_ERROR,

    /* The driver is closed, no operations for this client are ongoing,
    and/or the given handle is invalid. */
    DRV_CAMERA_OVM7692_CLIENT_STATUS_CLOSED   = DRV_CLIENT_STATUS_CLOSED,

    /* The driver is currently busy and cannot start additional operations. */
    DRV_CAMERA_OVM7692_CLIENT_STATUS_BUSY     = DRV_CLIENT_STATUS_BUSY,

    /* The module is running and ready for additional operations */
    DRV_CAMERA_OVM7692_CLIENT_STATUS_READY    = DRV_CLIENT_STATUS_READY

} DRV_CAMERA_OVM7692_CLIENT_STATUS;

// *****************************************************************************
/* OVM7692 Camera Device Register Addresses.

  Summary:
    Lists OVM7692 Camera device register addresses.
 
  Description:
    This enumeration defines the list of device register addresses.

  Remarks:
    These constants should be used in place of hard-coded numeric literals. 
    These values should be passed into the DRV_CAMERA_OVM7692_RegisterSet 
    function. Refer to the specific device data sheet for more information.
*/typedef enum
{
    /* AGC Gain Control */
    DRV_CAMERA_OVM7692_GAIN_REG_ADDR   /*DOM-IGNORE-BEGIN*/  = 0x00, /*DOM-IGNORE-END*/
    
    /* AWB Blue Gain Control */
    DRV_CAMERA_OVM7692_BGAIN_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x01, /*DOM-IGNORE-END*/
    
    /* AWB Red Gain Control */
    DRV_CAMERA_OVM7692_RGAIN_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x02, /*DOM-IGNORE-END*/
         
    /* AWB Green Gain Control */
    DRV_CAMERA_OVM7692_GGAIN_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x03, /*DOM-IGNORE-END*/
    
    /* Frame Average Level */
    DRV_CAMERA_OVM7692_YAVG_REG_ADDR   /*DOM-IGNORE-BEGIN*/ = 0x04, /*DOM-IGNORE-END*/
    
    /* B Pixel Average */
    DRV_CAMERA_OVM7692_BAVG_REG_ADDR   /*DOM-IGNORE-BEGIN*/ = 0x05, /*DOM-IGNORE-END*/
    
    /* R Pixel Average */
    DRV_CAMERA_OVM7692_RAVG_REG_ADDR   /*DOM-IGNORE-BEGIN*/ = 0x06, /*DOM-IGNORE-END*/
    
    /* G Pixel Average */
    DRV_CAMERA_OVM7692_GAVG_REG_ADDR   /*DOM-IGNORE-BEGIN*/ = 0x07, /*DOM-IGNORE-END*/
            
    /* Register 0x09 */
    DRV_CAMERA_OVM7692_REG09_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x09, /*DOM-IGNORE-END*/            
    
    /* Product ID Number MSB */
    DRV_CAMERA_PIDH_REG_ADDR   /*DOM-IGNORE-BEGIN*/ = 0x0A, /*DOM-IGNORE-END*/
    
    /* Product ID Number LSB */
    DRV_CAMERA_PIDL_REG_ADDR   /*DOM-IGNORE-BEGIN*/ = 0x0B, /*DOM-IGNORE-END*/
    
    /* Register 0x0C */
    DRV_CAMERA_OVM7692_REG0C_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x0C, /*DOM-IGNORE-END*/
    
    /* Register 0x0D */
    DRV_CAMERA_OVM7692_REG0D_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x0D, /*DOM-IGNORE-END*/
    
    /* Register 0x0E */
    DRV_CAMERA_OVM7692_REG0E_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x0E, /*DOM-IGNORE-END*/
    
    /* Automatic Exposure Control MSBs */
    DRV_CAMERA_OVM7692_AECH_REG_ADDR   /*DOM-IGNORE-BEGIN*/ = 0x0F, /*DOM-IGNORE-END*/
            
    /* Automatic Exposure Control LSBs */
    DRV_CAMERA_OVM7692_AECL_REG_ADDR   /*DOM-IGNORE-BEGIN*/ = 0x10, /*DOM-IGNORE-END*/
            
    /* Clock Control Register */
    DRV_CAMERA_OVM7692_CLKRC_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x11, /*DOM-IGNORE-END*/
            
    /* Register 0x12 */
    DRV_CAMERA_OVM7692_REG12_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x12, /*DOM-IGNORE-END*/
            
    /* Register 0x13 */
    DRV_CAMERA_OVM7692_REG13_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x13, /*DOM-IGNORE-END*/
            
    /* Register 0x14 */
    DRV_CAMERA_OVM7692_REG14_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x14, /*DOM-IGNORE-END*/
            
    /* Register 0x15 */
    DRV_CAMERA_OVM7692_REG15_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x15, /*DOM-IGNORE-END*/
            
    /* Register 0x16 */
    DRV_CAMERA_OVM7692_REG16_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x16, /*DOM-IGNORE-END*/
            
    /* Horizontal Window start point control */
    DRV_CAMERA_OVM7692_HSTART_REG_ADDR /*DOM-IGNORE-BEGIN*/ = 0x17, /*DOM-IGNORE-END*/
            
    /* Horizontal Sensor Size */
    DRV_CAMERA_OVM7692_HSIZE_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x18, /*DOM-IGNORE-END*/
            
    /* Vertical Window start Line control */
    DRV_CAMERA_OVM7692_VSTART_REG_ADDR /*DOM-IGNORE-BEGIN*/ = 0x19, /*DOM-IGNORE-END*/
            
    /* Vertical sensor size */
    DRV_CAMERA_OVM7692_VSIZE_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x1A, /*DOM-IGNORE-END*/
            
    /* Pixel Shift */
    DRV_CAMERA_OVM7692_SHFT_REG_ADDR   /*DOM-IGNORE-BEGIN*/ = 0x1B, /*DOM-IGNORE-END*/
            
    /* Manufacturer ID Byte - High */
    DRV_CAMERA_MIDH_REG_ADDR   /*DOM-IGNORE-BEGIN*/ = 0x1C, /*DOM-IGNORE-END*/
            
    /* Manufacturer ID Byte - Low */
    DRV_CAMERA_MIDL_REG_ADDR   /*DOM-IGNORE-BEGIN*/ = 0x1D, /*DOM-IGNORE-END*/
                    
    /* Register 0x1E */
    DRV_CAMERA_OVM7692_REG1E_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x1E, /*DOM-IGNORE-END*/
      
    /* Register LAEC */
    DRV_CAMERA_OVM7692_LAEC_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x1F, /*DOM-IGNORE-END*/            
            
    /* Register 0x20 */
    DRV_CAMERA_OVM7692_REG20_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x20, /*DOM-IGNORE-END*/

    /* Register AECGM */
    DRV_CAMERA_OVM7692_AECGM_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x21, /*DOM-IGNORE-END*/            
            
    /* Register WPT */
    DRV_CAMERA_OVM7692_WPT_REG_ADDR    /*DOM-IGNORE-BEGIN*/ = 0x24, /*DOM-IGNORE-END*/  
            
        /* Register BPT */
    DRV_CAMERA_OVM7692_BPT_REG_ADDR    /*DOM-IGNORE-BEGIN*/ = 0x25, /*DOM-IGNORE-END*/ 
            
       /* Register VPT */
    DRV_CAMERA_OVM7692_VPT_REG_ADDR    /*DOM-IGNORE-BEGIN*/ = 0x26, /*DOM-IGNORE-END*/          
     
    /* Register 0x27 */
    DRV_CAMERA_OVM7692_REG27_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x27, /*DOM-IGNORE-END*/            
            
    /* Register 0x28 */
    DRV_CAMERA_OVM7692_REG28_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x28, /*DOM-IGNORE-END*/
            
    /* Register EXHCL */
    DRV_CAMERA_OVM7692_EXHCL_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x2A, /*DOM-IGNORE-END*/   
            
    /* Register EXHCH */
    DRV_CAMERA_OVM7692_EXHCH_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x2B, /*DOM-IGNORE-END*/ 
            
    /* Register DM_LN */
    DRV_CAMERA_OVM7692_DM_LN_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x2C, /*DOM-IGNORE-END*/   
            
    /* Register ADVFL */
    DRV_CAMERA_OVM7692_ADVFL_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x2D, /*DOM-IGNORE-END*/             
   
    /* Register ADVFH */
    DRV_CAMERA_OVM7692_ADVFH_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x2E, /*DOM-IGNORE-END*/ 
            
    /* Register R_PLL0*/
    DRV_CAMERA_OVM7692_R_PLL0_REG_ADDR /*DOM-IGNORE-BEGIN*/ = 0x30, /*DOM-IGNORE-END*/            

    /* Register R_PLL1*/
    DRV_CAMERA_OVM7692_R_PLL1_REG_ADDR /*DOM-IGNORE-BEGIN*/ = 0x31, /*DOM-IGNORE-END*/            
            
    /* Register 0x36 */
    DRV_CAMERA_OVM7692_REG36_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x36, /*DOM-IGNORE-END*/            
            
    /* Register 0x37 */
    DRV_CAMERA_OVM7692_REG37_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x37, /*DOM-IGNORE-END*/

    /* Register 0x38 */
    DRV_CAMERA_OVM7692_REG38_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x38, /*DOM-IGNORE-END*/

    /* Register 0x39 */
    DRV_CAMERA_OVM7692_REG39_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x39, /*DOM-IGNORE-END*/            
            
    /* Register 0x3E */
    DRV_CAMERA_OVM7692_REG3E_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x3E, /*DOM-IGNORE-END*/
            
    /* Register 0x3F */
    DRV_CAMERA_OVM7692_REG3F_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x3F, /*DOM-IGNORE-END*/ 
            
    /* Register BD50ST */
    DRV_CAMERA_OVM7692_BD50ST_REG_ADDR /*DOM-IGNORE-BEGIN*/ = 0x50, /*DOM-IGNORE-END*/             
            
    /* Register BD60ST */
    DRV_CAMERA_OVM7692_BD60ST_REG_ADDR /*DOM-IGNORE-BEGIN*/ = 0x51, /*DOM-IGNORE-END*/             
          
    /* Register UV_CTR0 */
    DRV_CAMERA_OVM7692_UV_CTR0_REG_ADDR/*DOM-IGNORE-BEGIN*/ = 0x5A, /*DOM-IGNORE-END*/ 
            
    /* Register UV_CTR1 */
    DRV_CAMERA_OVM7692_UV_CTR1_REG_ADDR/*DOM-IGNORE-BEGIN*/ = 0x5B, /*DOM-IGNORE-END*/

    /* Register UV_CTR2 */
    DRV_CAMERA_OVM7692_UV_CTR2_REG_ADDR/*DOM-IGNORE-BEGIN*/ = 0x5C, /*DOM-IGNORE-END*/

    /* Register UV_CTR3 */
    DRV_CAMERA_OVM7692_UV_CTR3_REG_ADDR/*DOM-IGNORE-BEGIN*/ = 0x5D, /*DOM-IGNORE-END*/            
            
        /* Register UV_CTR3 */
    DRV_CAMERA_OVM7692_REG61_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0x61, /*DOM-IGNORE-END*/        
            
    /* Register 0xB4 */
    DRV_CAMERA_OVM7692_REGB4_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xB4, /*DOM-IGNORE-END*/
            
    /* Register 0xB5 */
    DRV_CAMERA_OVM7692_REGB5_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xB5, /*DOM-IGNORE-END*/
            
    /* Register 0xB6 */
    DRV_CAMERA_OVM7692_REGB6_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xB6, /*DOM-IGNORE-END*/
            
    /* Register 0xB7 */
    DRV_CAMERA_OVM7692_REGB7_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xB7, /*DOM-IGNORE-END*/
            
    /* Register 0xB8 */
    DRV_CAMERA_OVM7692_REGB8_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xB8, /*DOM-IGNORE-END*/
            
    /* Register 0xB9 */
    DRV_CAMERA_OVM7692_REGB9_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xB9, /*DOM-IGNORE-END*/
            
    /* Register 0xBA */
    DRV_CAMERA_OVM7692_REGBA_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xBA, /*DOM-IGNORE-END*/
            
    /* Register 0xBB */
    DRV_CAMERA_OVM7692_REGBB_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xBB, /*DOM-IGNORE-END*/
            
    /* Register 0xBC */
    DRV_CAMERA_OVM7692_REGBC_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xBC, /*DOM-IGNORE-END*/
            
    /* Register 0xBD */
    DRV_CAMERA_OVM7692_REGBD_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xBD, /*DOM-IGNORE-END*/
            
    /* Register 0xBE */
    DRV_CAMERA_OVM7692_REGBE_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xBE, /*DOM-IGNORE-END*/
            
    /* Register 0xBF */
    DRV_CAMERA_OVM7692_REGBF_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xBF, /*DOM-IGNORE-END*/
            
    /* Register 0xC0 */
    DRV_CAMERA_OVM7692_REGC0_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xC0, /*DOM-IGNORE-END*/
            
    /* Register 0xC1 */
    DRV_CAMERA_OVM7692_REGC1_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xC1, /*DOM-IGNORE-END*/
            
    /* Register 0xC2 */
    DRV_CAMERA_OVM7692_REGC2_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xC2, /*DOM-IGNORE-END*/
            
    /* Register 0xC3 */
    DRV_CAMERA_OVM7692_REGC3_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xC3, /*DOM-IGNORE-END*/
            
    /* Register 0xC4 */
    DRV_CAMERA_OVM7692_REGC4_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xC4, /*DOM-IGNORE-END*/
            
    /* Register 0xC5 */
    DRV_CAMERA_OVM7692_REGC5_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xC5, /*DOM-IGNORE-END*/
            
    /* Register 0xC6 */
    DRV_CAMERA_OVM7692_REGC6_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xC6, /*DOM-IGNORE-END*/
            
    /* Register 0xC7 */
    DRV_CAMERA_OVM7692_REGC7_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xC7, /*DOM-IGNORE-END*/
            
    /* Register 0xC8 */
    DRV_CAMERA_OVM7692_REGC8_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xC8, /*DOM-IGNORE-END*/
            
    /* Register 0xC9 */
    DRV_CAMERA_OVM7692_REGC9_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xC9, /*DOM-IGNORE-END*/
            
    /* Register 0xCA */
    DRV_CAMERA_OVM7692_REGCA_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xCA, /*DOM-IGNORE-END*/
            
    /* Register 0xCB */
    DRV_CAMERA_OVM7692_REGCB_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xCB, /*DOM-IGNORE-END*/
            
    /* Register 0xCC */
    DRV_CAMERA_OVM7692_REGCC_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xCC, /*DOM-IGNORE-END*/
            
    /* Register 0xCD */
    DRV_CAMERA_OVM7692_REGCD_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xCD, /*DOM-IGNORE-END*/
            
    /* Register 0xCE */
    DRV_CAMERA_OVM7692_REGCE_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xCE, /*DOM-IGNORE-END*/        
            
    /* Register 0xCF */
    DRV_CAMERA_OVM7692_REGCF_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xCF, /*DOM-IGNORE-END*/
            
    /* Register 0xD0 */
    DRV_CAMERA_OVM7692_REGD0_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xD0, /*DOM-IGNORE-END*/
            
    /* Register 0xD1 */
    DRV_CAMERA_OVM7692_REGD1_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xD1, /*DOM-IGNORE-END*/
            
    /* Register 0xD2 */
    DRV_CAMERA_OVM7692_REGD2_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xD2, /*DOM-IGNORE-END*/
            
    /* Register 0xD3 */
    DRV_CAMERA_OVM7692_REGD3_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xD3, /*DOM-IGNORE-END*/
            
    /* Register 0xD4 */
    DRV_CAMERA_OVM7692_REGD4_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xD4, /*DOM-IGNORE-END*/
            
    /* Register 0xD5 */
    DRV_CAMERA_OVM7692_REGD5_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xD5, /*DOM-IGNORE-END*/
            
    /* Register 0xD6 */
    DRV_CAMERA_OVM7692_REGD6_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xD6, /*DOM-IGNORE-END*/
            
    /* Register 0xD7 */
    DRV_CAMERA_OVM7692_REGD7_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xD7, /*DOM-IGNORE-END*/
            
    /* Register 0xD8 */
    DRV_CAMERA_OVM7692_REGD8_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xD8, /*DOM-IGNORE-END*/
            
    /* Register 0xD9 */
    DRV_CAMERA_OVM7692_REGD9_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xD9, /*DOM-IGNORE-END*/
            
    /* Register 0xDA */
    DRV_CAMERA_OVM7692_REGDA_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xDA, /*DOM-IGNORE-END*/
            
    /* Register 0xDB */
    DRV_CAMERA_OVM7692_REGDB_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xDB, /*DOM-IGNORE-END*/
            
    /* Register 0xDC */
    DRV_CAMERA_OVM7692_REGDC_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xDC, /*DOM-IGNORE-END*/
            
    /* Register 0xDD */
    DRV_CAMERA_OVM7692_REGDD_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xDD, /*DOM-IGNORE-END*/
            
    /* Register 0xDE */
    DRV_CAMERA_OVM7692_REGDE_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xDE, /*DOM-IGNORE-END*/        
            
    /* Register 0xDF */
    DRV_CAMERA_OVM7692_REGDF_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xDF, /*DOM-IGNORE-END*/
            
    /* Register 0xE0 */
    DRV_CAMERA_OVM7692_REGE0_REG_ADDR  /*DOM-IGNORE-BEGIN*/ = 0xE0, /*DOM-IGNORE-END*/
            
    /* Register MIPI_BANK */
    DRV_CAMERA_OVM7692_MIPI_BANK_REG_ADDR /*DOM-IGNORE-BEGIN*/ = 0xFF, /*DOM-IGNORE-END*/            
            
    /* Register MIPI_COM0 */
    DRV_CAMERA_OVM7692_MIPI_COM0_REG_ADDR /*DOM-IGNORE-BEGIN*/ = 0xB4, /*DOM-IGNORE-END*/
            
} DRV_CAMERA_OVM7692_REGISTER_ADDRESS;


// *****************************************************************************
/* OVM7692 Camera Initialization parameters

  Summary:
    OVM7692 Camera Driver initialization parameters.

  Description:
    This structure defines OVM7692 Camera Driver initialization parameters.

  Remarks:
    These values should be passed into the DRV_CAMERA_OVM7692_Initialize 
    function.
*/

typedef struct
{
    /* Camera module ID */
    CAMERA_MODULE_ID        cameraID;  
    
    /* Source Port Address */
    void *                  sourcePort;

    /* PWDN pin */
    SYS_PORT_PIN            pwdnPin;    
    
    /* LDO SHDN pin */
    SYS_PORT_PIN            shdnPin;     
    
    /* HSYNC Interrupt Source */
    INT_SOURCE              hsyncInterruptSource;
    
    /* VSYNC Interrupt Source */
    INT_SOURCE              vsyncInterruptSource;
    
    /* PCLK Interrupt Source */
    INT_SOURCE              pclkInterruptSource;    

    /* DMA channel */
    SYS_DMA_CHANNEL         dmaChannel1;
    SYS_DMA_CHANNEL         dmaChannel2;
    SYS_DMA_CHANNEL         dmaChannel3;
    SYS_DMA_CHANNEL         dmaChannel4;
    
    /* Frame vertical size */
    uint32_t                frameVerticalSize;
    
    /* Frame horizontal size */
    uint32_t                frameHorizontalSize;    
    
    /* Bits per pixel */
    uint16_t                bytesPerPixel;
     
} DRV_CAMERA_OVM7692_INIT;

// *****************************************************************************
/* OVM7692 Camera Driver Instance Object 

  Summary:
    OVM7692 Camera Driver instance object.

  Description:
    This structure provides a definition of the OVM7692 Camera Driver instance 
	object.

  Remarks:
    These values are been updated into the DRV_CAMERA_OVM7692_Initialize 
    function.
*/

typedef struct
{
    /* The module index associated with the object*/
    CAMERA_MODULE_ID moduleId;
    
    /* Manufacturer ID */
    uint8_t manufacturerID[2];  

    /* Product ID */
    uint8_t productID[2];    
    
    /* The status of the driver */
    SYS_STATUS status;
    
    /* Camera SM state */
    DRV_CAMERA_STATE state;
    DRV_CAMERA_STATE prevstate;
    
    /* Camera SM Sub State */
    DRV_CAMERA_SUB_STATE substate;
    DRV_CAMERA_SUB_STATE nextsubstate;
    DRV_CAMERA_SUB_STATE prevsubstate;
    
    /* Flag to indicate this object is in use  */
    bool inUse;

    /* Flag to indicate that driver has been opened exclusively. */
    bool isExclusive;

    /* Keeps track of the number of clients
     * that have opened this driver */
    size_t nClients;
    
    /* Source Port Address */
    void * sourcePort;    

    /* HSYNC pin */
    SYS_PORT_PIN hsyncPin;
           
    /* VSYNC pin */
    SYS_PORT_PIN vsyncPin;
    
    /* PWDN pin */
    SYS_PORT_PIN pwdnPin;    
    
    /* LDO SHDN pin */
    SYS_PORT_PIN shdnPin;    
  
    /* HSYNC Interrupt Source */
    INT_SOURCE hsyncInterruptSource;
    
    /* VSYNC Interrupt Source */
    INT_SOURCE vsyncInterruptSource;
    
    /* VSYNC Interrupt Source */
    INT_SOURCE pclkInterruptSource;
    
    /* Read DMA channel  */
    SYS_DMA_CHANNEL dmaChannel1;
    SYS_DMA_CHANNEL dmaChannel2;
    SYS_DMA_CHANNEL dmaChannel3;
    SYS_DMA_CHANNEL dmaChannel4;
      
    /* Frame complete */
    bool frameComplete;
       
    /* Frame Count */
    uint32_t frameCount;    
    
    /* Frame buffers */    
    GFXU_ImageAsset frameBuffer[DRV_CAMERA_FRAME_BUFFERS];
    
    /* DMA Pointers */
    uint32_t dmaPtr[DRV_CAMERA_FRAME_BUFFERS][DRV_DMA_TRANSFERS_PER_BUFFER];
    
    /* Framebuffer Index */
    uint8_t frameBufferIndex;  
    
    /* Last Framebuffer Index */
    uint8_t lastFrameBufferIndex;     
    
    /* Frame vertical size */
    uint32_t frameVerticalSize;
    
    /* Frame horizontal size */
    uint32_t frameHorizontalSize;    

    /* Bytes per pixel */
    uint16_t bytesPerPixel;    
      
    /* Timer handle */
    SYS_TIME_HANDLE sysDelayHandle;
    
    /* Paused flag */
    bool paused;
    GFXU_ImageAsset* lastFrame;
    
} DRV_CAMERA_OVM7692_OBJ;

// *****************************************************************************
/* OVM7692 Camera Driver Client Object.

  Summary:
    OVM7692 Camera Driver client object.
    
  Description:
    This structure provides a definition of the OVM7692 Camera Driver client 
	object. 

  Remarks:
    These values are been updated into the DRV_CAMERA_OVM7692_Open 
    function.
*/

typedef struct
{
    /* The hardware instance object associated with the client */
    DRV_CAMERA_OVM7692_OBJ * hDriver;

    /* The I/O intent with which the client was opened */
    DRV_IO_INTENT   ioIntent;

    /* This flags indicates if the object is in use or is available */
    bool inUse;
    
    /* Driver Error */
    DRV_CAMERA_OVM7692_ERROR  error;
    
    /* Client status */
    DRV_CAMERA_OVM7692_CLIENT_STATUS status;

} DRV_CAMERA_OVM7692_CLIENT_OBJ;

// *****************************************************************************
// Section: Interface Headers for the driver
// *****************************************************************************

SYS_MODULE_OBJ DRV_CAMERA_OVM7692_Initialize( const SYS_MODULE_INDEX drvIndex, const SYS_MODULE_INIT * const init );

void DRV_CAMERA_OVM7692_DeInitialize(SYS_MODULE_OBJ object);

DRV_HANDLE DRV_CAMERA_OVM7692_Open( const SYS_MODULE_INDEX drvIndex, const DRV_IO_INTENT ioIntent );

void DRV_CAMERA_OVM7692_Close ( DRV_HANDLE handle );

DRV_CAMERA_OVM7692_ERROR DRV_CAMERA_OVM7692_ConfigureBuffer( DRV_HANDLE handle, void * frameBuffer, uint8_t frameBufferIndex );

int16_t DRV_CAMERA_OVM7692_GetStatus( DRV_HANDLE handle );

DRV_CAMERA_OVM7692_ERROR DRV_CAMERA_OVM7692_Start( DRV_HANDLE handle );

void _DRV_CAMERA_OVM7692_Start( SYS_MODULE_OBJ object);

DRV_CAMERA_OVM7692_ERROR DRV_CAMERA_OVM7692_Stop( DRV_HANDLE handle );

SCCB_STATUS DRV_CAMERA_OVM7692_RegisterSet( SYS_MODULE_OBJ object, DRV_CAMERA_OVM7692_REGISTER_ADDRESS regIndex, const uint8_t regValue );

SCCB_STATUS DRV_CAMERA_OVM7692_RegisterGet( SYS_MODULE_OBJ object, DRV_CAMERA_OVM7692_REGISTER_ADDRESS regIndex, uint8_t* const regValue );

void _DRV_CAMERA_OVM7692_UpdateSubstate( DRV_CAMERA_OVM7692_OBJ *dObj, bool wait );

void DRV_CAMERA_OVM7692_HsyncEventHandler(SYS_MODULE_OBJ object);

GFXU_ImageAsset* DRV_CAMERA_OVM7692_VsyncEventHandler(SYS_MODULE_OBJ object);

void DRV_CAMERA_OVM7692_Tasks(SYS_MODULE_OBJ object);

void DRV_CAMERA_OVM7692_SubTasks(SYS_MODULE_OBJ object);

void DRV_CAMERA_OVM7692_Pause(SYS_MODULE_OBJ object);

void DRV_CAMERA_OVM7692_Resume(SYS_MODULE_OBJ object);

uint16_t DRV_CAMERA_OVM7692_GetCameraParameter( char* str, DRV_CAMERA_PARAMETERS param, DRV_HANDLE handle );

void _DRV_CAMERA_OVM7692_PeripheralSetup( SYS_MODULE_OBJ object );

void _DRV_CAMERA_OVM7692_DMAEventHandler( SYS_DMA_TRANSFER_EVENT event, uintptr_t contextHandle );

uint8_t DRV_CAMERA_OVM7692_getFrameIndex( DRV_HANDLE handle );

bool DRV_CAMERA_OVM7692_isFrameComplete( DRV_HANDLE handle );

uint32_t _DRV_CAMERA_OVM7692_isFrameComplete( SYS_MODULE_OBJ object );

bool DRV_CAMERA_OVM7692_InitRegisters(SYS_MODULE_OBJ object);

void DRV_CAMERA_OVM7692_Configure(SYS_MODULE_OBJ object);

void DRV_CAMERA_OVM7692_Set_Position(SYS_MODULE_OBJ object, uint8_t hstart, uint8_t vstart);
void DRV_CAMERA_OVM7692_Get_Position(SYS_MODULE_OBJ object, uint8_t * hstart, uint8_t * vstart);

bool DRV_CAMERA_OVM7692_Is_Paused(SYS_MODULE_OBJ object);
GFXU_ImageAsset* DRV_CAMERA_OVM7692_Get_Last_Frame(SYS_MODULE_OBJ object);

bool DRV_CAMERA_test_comms(void);

#ifdef __cplusplus
    }
#endif
    
#endif // #ifndef _DRV_CAMERA_OVM7692_H

/*******************************************************************************
 End of File
*/