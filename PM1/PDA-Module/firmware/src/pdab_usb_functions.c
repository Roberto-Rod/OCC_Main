 /******************************************************************************

 Company:   Lein Applied Diagnostics Limited
 Project:   pdab
 File Name: USB_Functions.c   
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


/*******************************************************************************
                            Includes Files
*******************************************************************************/
#include "pdab_usb_functions.h"
/******************************************************************************
                            Typedefs
 ******************************************************************************/
typedef struct
{
//*********************** State Machine Section ******************************//   
    
    /* Application states*/
    USB_STATES state;
    USB_STATES previous_state;
    
     /* Error code should an error occur*/
    uint16_t error;   
    
//*************************** USB Section ************************************//    
    
   /* Device layer handle returned by device layer open function */
    USB_DEVICE_HANDLE usbDevHandle;

    /* Configuration value */
    uint8_t configValue;

    /* speed */
    USB_SPEED speed;
    
    /* Track device configuration */
    bool deviceIsConfigured;
    
    /* ep data sent */
    uint8_t epDataWritePending;

    /* ep data received */
    bool epDataReadPending;

    /* Transfer handle */
    USB_DEVICE_TRANSFER_HANDLE writeTransferHandle;
    
    /* Write index to link with each transfer handle */
    uint8_t writeTransferIndex;    

    /* Transfer handle */
    USB_DEVICE_TRANSFER_HANDLE readTransferHandle;

    /* The transmit endpoint address */
    USB_ENDPOINT_ADDRESS endpointTx;

    /* The receive endpoint address */
    USB_ENDPOINT_ADDRESS endpointRx;
    
    /* The endpoint size is 64 for FS and 512 for HS */
    uint16_t endpointSize;    

    /* Tracks the alternate setting */
    uint8_t altSetting;

    /* Flag determines SOF event occurrence */
    bool sofEventHasOccurred;   
    
    bool usb_buffer_overrun;
    
//*************************** Data Section ************************************//     
    
    uint8_t*  usbReceiveBuffer;    
    
} USB_DATA_OBJ;
/*******************************************************************************
                            Global variables
*******************************************************************************/
uint8_t  MAKE_BUFFER_DMA_READY _usbReceiveBuffer[USB_READ_BUFFER_SIZE];

static USB_DATA_OBJ usbData = 
{
    /* Place the App state machine in its initial state. */
    .state = USB_STATE_INIT,
    .previous_state = USB_STATE_IDLE,
    .usbDevHandle = USB_DEVICE_HANDLE_INVALID,
    .readTransferHandle = USB_DEVICE_TRANSFER_HANDLE_INVALID,
    .writeTransferIndex = 0U,
    .deviceIsConfigured = false,
    .endpointRx = (USB_EP_BULK_OUT | USB_EP_DIRECTION_OUT),
    .endpointTx = (USB_EP_BULK_IN | USB_EP_DIRECTION_IN),
    .epDataReadPending = false,
    .epDataWritePending = false,
    .altSetting = 0U,    
    .error = NO_ERRORS,
    .usbReceiveBuffer = _usbReceiveBuffer,
};


/*******************************************************************************
 * Function:        uint16_t USB_Self_Test( uint8_t* data )
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Notes:           None
 ******************************************************************************/ 
void USB_Tasks( void )
{
    switch(usbData.state)
    {   
        case USB_STATE_IDLE:
            
            break;
        
        case USB_STATE_INIT:
            /* Open the device layer */
            usbData.usbDevHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0, DRV_IO_INTENT_READWRITE );

            if(usbData.usbDevHandle != USB_DEVICE_HANDLE_INVALID)
            {
                /* Register a callback with device layer to get event notification (for end point 0) */
                USB_DEVICE_EventHandlerSet(usbData.usbDevHandle,  (const USB_DEVICE_EVENT_HANDLER)USB_Event_Handler, (uintptr_t)&usbData );

                usbData.state = USB_STATE_WAIT_FOR_CONFIGURATION;
            }
            else
            {
                /* The Device Layer is not ready to be opened. We should try
                 * again later. */
            }

            break;

        case USB_STATE_WAIT_FOR_CONFIGURATION:

            /* Check if the device is configured */
            if(usbData.deviceIsConfigured == true)
            {
                if (USB_DEVICE_ActiveSpeedGet(usbData.usbDevHandle) == USB_SPEED_FULL )
                {
                    usbData.endpointSize = 64;
                }
                else if (USB_DEVICE_ActiveSpeedGet(usbData.usbDevHandle) == USB_SPEED_HIGH )
                {
                    usbData.endpointSize = 512;
                }
                if (USB_DEVICE_EndpointIsEnabled(usbData.usbDevHandle, usbData.endpointRx) == false )
                {
                    /* Enable Read Endpoint */
                    USB_DEVICE_EndpointEnable(usbData.usbDevHandle, 0, usbData.endpointRx, USB_TRANSFER_TYPE_BULK, usbData.endpointSize);
                }
                if (USB_DEVICE_EndpointIsEnabled(usbData.usbDevHandle, usbData.endpointTx) == false )
                {
                    /* Enable Write Endpoint */
                    USB_DEVICE_EndpointEnable(usbData.usbDevHandle, 0, usbData.endpointTx, USB_TRANSFER_TYPE_BULK, usbData.endpointSize);
                }
                /* Indicate that we are waiting for read */
                usbData.epDataReadPending = true;

                /* Place a new read request. */
                USB_DEVICE_EndpointRead(    usbData.usbDevHandle, &usbData.readTransferHandle,
                                            usbData.endpointRx, usbData.usbReceiveBuffer, 
                                            USB_READ_BUFFER_SIZE );

                /* Device is ready to run the main task */
                usbData.state = USB_STATE_USB_TASKS;
            }
            break;

        case USB_STATE_USB_TASKS:

            if( !usbData.deviceIsConfigured )
            {
                /* This means the device got deconfigured. Change the
                 * application state back to waiting for configuration. */
                usbData.state = USB_STATE_WAIT_FOR_CONFIGURATION;

                /* Disable the endpoint*/
                USB_DEVICE_EndpointDisable(usbData.usbDevHandle, usbData.endpointRx);
                USB_DEVICE_EndpointDisable(usbData.usbDevHandle, usbData.endpointTx);
                usbData.epDataReadPending = false;
                usbData.epDataWritePending = false;
            }
            else if (usbData.epDataReadPending == false)
            {
               // Execute command functionality
                
                PDAB_Command_Received( (PDAB_COMMANDS) usbData.usbReceiveBuffer[0],
                                                       usbData.usbReceiveBuffer[1], 
                                                       &usbData.usbReceiveBuffer[2],
                                                       COMM_USB );

                usbData.epDataReadPending = true ;

                /* Place a new read request. */
                USB_DEVICE_EndpointRead ( usbData.usbDevHandle, &usbData.readTransferHandle,
                        usbData.endpointRx, usbData.usbReceiveBuffer, USB_READ_BUFFER_SIZE );
            }
            break;

        case USB_STATE_ERROR:
            break;

        default:
            break;
    }
}
/*******************************************************************************
 * Function:        uint16_t USB_Self_Test( uint8_t* data )
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         None
 *
 * Side Effects:    None
 *
 * Overview:        Application USB Device Layer Event Handler
 *
 * Notes:           None
 ******************************************************************************/ 
void USB_Event_Handler(USB_DEVICE_EVENT event, void * eventData, uintptr_t context)
{
    uint8_t * configurationValue;
    USB_SETUP_PACKET * setupPacket;
    switch(event)
    {
        case USB_DEVICE_EVENT_RESET:
            
            /* Device is reset or deconfigured. */  
            usbData.deviceIsConfigured = false; 
            
            break;
            
        case USB_DEVICE_EVENT_DECONFIGURED:

            /* Device is reset or deconfigured. */  
            usbData.deviceIsConfigured = false;

            break;

        case USB_DEVICE_EVENT_CONFIGURED:

            /* Check the configuration */
            configurationValue = (uint8_t *)eventData;
            if(*configurationValue == 1 )
            {
                /* Reset endpoint data send & receive flag  */
                usbData.deviceIsConfigured = true;
            }
            break;

        case USB_DEVICE_EVENT_SUSPENDED:

            /* Device is suspended. */ 
            break;


        case USB_DEVICE_EVENT_POWER_DETECTED:

            /* VBUS is detected. Attach the device */
            USB_DEVICE_Attach(usbData.usbDevHandle);
            break;

        case USB_DEVICE_EVENT_POWER_REMOVED:

            /* VBUS is removed. Detach the device */
            usbData.deviceIsConfigured = false;
            USB_DEVICE_Detach (usbData.usbDevHandle);
            break;

        case USB_DEVICE_EVENT_CONTROL_TRANSFER_SETUP_REQUEST:
            /* This means we have received a setup packet */
            setupPacket = (USB_SETUP_PACKET *)eventData;
            if(setupPacket->bRequest == USB_REQUEST_SET_INTERFACE)
            {
                /* If we have got the SET_INTERFACE request, we just acknowledge
                 for now. This demo has only one alternate setting which is already
                 active. */
                USB_DEVICE_ControlStatus(usbData.usbDevHandle,USB_DEVICE_CONTROL_STATUS_OK);
            }
            else if(setupPacket->bRequest == USB_REQUEST_GET_INTERFACE)
            {
                /* We have only one alternate setting and this setting 0. So
                 * we send this information to the host. */

                USB_DEVICE_ControlSend(usbData.usbDevHandle, &usbData.altSetting, 1);
            }
            else
            {
                /* We have received a request that we cannot handle. Stall it*/
                USB_DEVICE_ControlStatus(usbData.usbDevHandle, USB_DEVICE_CONTROL_STATUS_ERROR);
            }
            break;

        case USB_DEVICE_EVENT_ENDPOINT_READ_COMPLETE:
           /* Endpoint read is complete */
            usbData.epDataReadPending = false;
            break;

        case USB_DEVICE_EVENT_ENDPOINT_WRITE_COMPLETE:
            /* Endpoint write is complete */
            usbData.epDataWritePending = false; 
            break;

        /* These events are not used in this demo. */
        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_ERROR:
        default:
            break;
    }
}
/*******************************************************************************
 * Function:        USB_Return_Status( uint8_t power )
 *
 * Precondition:    None
 *
 * Input:           uint8_t buffer:     USB buffer index (default 0)
 *                  uint8_t command:    Command Byte
 *                  bool update:        Update flag, if true values are read from hardware
 *
 * Output:          None
 *
 * Returns:         Error code, non-zero if an error occurred before or after status request
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the device status after a USB 
 *                  command is executed.
 *
 * Notes:           None
 ******************************************************************************/  
USB_DEVICE_RESULT USB_Return_Data( const void* data, const uint32_t length, USB_DEVICE_TRANSFER_FLAGS flag )
{
    USB_DEVICE_RESULT result = USB_DEVICE_RESULT_ERROR_TRANSFER_QUEUE_FULL;
    
    if( usbData.epDataWritePending == false )
    {         
        usbData.epDataWritePending = true; 
        usbData.usb_buffer_overrun = false;
        
        result = USB_DEVICE_EndpointWrite (  usbData.usbDevHandle, &usbData.writeTransferHandle,
                                             usbData.endpointTx, data,
                                             length, flag );        
    }
    else
    {
        usbData.usb_buffer_overrun = true;
        dprintf("USB write buffer full.\r\n");        
    }
    
    return result;
}
/*******************************************************************************
 * Function:        void Scan_Clear_Endpoints( void )
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Notes:           None
 ******************************************************************************/ 
USB_DEVICE_RESULT USB_Clear_Endpoints( void )
{
    USB_DEVICE_RESULT result = USB_DEVICE_RESULT_ERROR;
    
    if( usbData.epDataWritePending == true )
    {     
        if( usbData.writeTransferHandle != USB_DEVICE_TRANSFER_HANDLE_INVALID )
        {

            result = USB_DEVICE_EndpointTransferCancel( usbData.usbDevHandle,
                                                        usbData.endpointTx,
                                                        usbData.writeTransferHandle );
        }
            
        usbData.epDataWritePending = false;           
    }
    
    return result;
}
/*******************************************************************************
 * Function:        void Scan_Clear_Endpoints( void )
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Notes:           None
 ******************************************************************************/ 
bool USB_is_device_attached( void )
{
    return usbData.deviceIsConfigured;
//    if( USBOTGbits.VBUS > USBHS_VBUS_SESSION_END )
//        return true;
//    else
//        return false;
}
/*******************************************************************************
 * Function:        void Scan_Clear_Endpoints( void )
 *
 * Precondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Returns:         None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Notes:           None
 ******************************************************************************/ 
void USB_Init( void )
{
    USB_DEVICE_Attach(usbData.usbDevHandle);
}
void USB_deInit( void )
{
    USB_DEVICE_Detach(usbData.usbDevHandle);
}
/*******************************************************************************
 End of File
 */
bool USB_is_buffer_overrun(void){
    return usbData.usb_buffer_overrun;
}
	
 
