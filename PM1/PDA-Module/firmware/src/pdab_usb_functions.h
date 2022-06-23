/******************************************************************************

 Company:   Lein Applied Diagnostics Limited
 Project:   pdab
 File Name: USB_Functions.h   
 Processor: PIC32MZ
 Hardware:  pdab Digital Board
 Assembler: XC32-gcc
 Linker:    XC32-ld
 
 Description: 
 
 Functions: 
 
*******************************************************************************/

/*********************** Revision History **************************************
SI.NO   VER     AUTHOR                  CHANGE DESCRIPTION
1.      1.0     RPT                     Initial Version
*******************************************************************************/

#ifndef USB_DRIVER_H
#define USB_DRIVER_H

/*******************************************************************************
                            Includes Files
*******************************************************************************/
#include "definitions.h"
/******************************************************************************
                            Typedefs
 ******************************************************************************/
typedef enum
{
	/* USB state machine's initial state. */
	USB_STATE_INIT = 0U,

    /* USB waiting for configuration */        
    USB_STATE_WAIT_FOR_CONFIGURATION,        

    /* USB tasks */
    USB_STATE_USB_TASKS,             
            
    /* USB error occurred */
    USB_STATE_ERROR,
            
    /* USB is idle */        
    USB_STATE_SUSPEND,              
            
    /* USB is idle */        
    USB_STATE_IDLE,        

} USB_STATES;
/******************************************************************************
                        Global Definitions
 ******************************************************************************/
#if defined (__PIC32MZ__) || defined (_SAMD21J18A_H_) || defined (_SAME54P20A_H_)
#define USB_EP_BULK_OUT 1
#define USB_EP_BULK_IN  1
#else
#define USB_EP_BULK_OUT 1
#define USB_EP_BULK_IN  2
#endif 

#define USB_READ_BUFFER_SIZE 512L
#define USB_TOTAL_READ_BUFFERS 1U
#define USB_TOTAL_WRITE_BUFFERS 1U

/*******************************************************************************
                            Macros
*******************************************************************************/

/*******************************************************************************
                            Global Variables
*******************************************************************************/

/*******************************************************************************
                            Function Prototypes 
 ******************************************************************************/
void     USB_Event_Handler( USB_DEVICE_EVENT event, void * eventData, uintptr_t context );
void     USB_Tasks( void );
void USB_Init( void );
void USB_deInit( void );
bool USB_is_device_attached( void );
bool USB_is_buffer_overrun( void );
USB_DEVICE_RESULT USB_Clear_Endpoints( void );
USB_DEVICE_RESULT USB_Return_Data( const void* data, const uint32_t length, USB_DEVICE_TRANSFER_FLAGS flag );
#endif /* _USB_FUNCTIONS_H */
/*******************************************************************************
 End of File
 */
