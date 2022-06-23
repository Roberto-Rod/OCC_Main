/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
 * Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip software
 * and any derivatives exclusively with Microchip products. It is your
 * responsibility to comply with third party license terms applicable to your
 * use of third party software (including open source software) that may
 * accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
 * ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include <string.h>

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************


//This section is all you need to implement in your actual firmware to be able
//to reboot into bootloader

// support functionality to trigger bootloader 
#define BTL_TRIGGER_RAM_START   KVA0_TO_KVA1(0x80000000)

#define DCACHE_CLEAN_BY_ADDR(start, sz)

static inline void APP_SystemReset(void) {
    /* Perform system unlock sequence */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    RSWRSTSET = _RSWRST_SWRST_MASK;
    (void) RSWRST;
}

#define BTL_TRIGGER_PATTERN (0x5048434DUL)
static uint32_t *ramStart = (uint32_t *) BTL_TRIGGER_RAM_START;

void TriggerBootloader(void) {
    ramStart[0] = BTL_TRIGGER_PATTERN;
    ramStart[1] = BTL_TRIGGER_PATTERN;
    ramStart[2] = BTL_TRIGGER_PATTERN;
    ramStart[3] = BTL_TRIGGER_PATTERN;

    DCACHE_CLEAN_BY_ADDR(ramStart, 16);

    APP_SystemReset();
}

void ShortDelay(void) {
    int i;
    // Cheap delay. This should give at leat 2 ms delay.
    for (i = 0; i < 4000; i++) {
        asm("nop");
    }
}



// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
 */

APP_DATA appData;

#define APP_MAKE_BUFFER_DMA_READY  __attribute__((coherent, aligned(16)))


#define APP_USART_USB_DATA_WIDTH_DIFF 5

uint8_t reset_uart_buffer[APP_READ_BUFFER_SIZE] APP_MAKE_BUFFER_DMA_READY;
#define UART1_reset_retry_count 2
#define UART0_reset_retry_count 20

//read data buffers for virtual ports, these need to be DMA-Ready
uint8_t com1ReadBuffer[APP_READ_BUFFER_SIZE] APP_MAKE_BUFFER_DMA_READY;
uint8_t com2ReadBuffer[APP_READ_BUFFER_SIZE] APP_MAKE_BUFFER_DMA_READY;
uint8_t com3ReadBuffer[APP_READ_BUFFER_SIZE] APP_MAKE_BUFFER_DMA_READY;

// read data buffers for the two uart ports
uint8_t uart0ReadBuffer[APP_READ_BUFFER_SIZE] APP_MAKE_BUFFER_DMA_READY;
uint8_t uart1ReadBuffer[APP_READ_BUFFER_SIZE] APP_MAKE_BUFFER_DMA_READY;

uint8_t BootloaderBuffer[1] APP_MAKE_BUFFER_DMA_READY;

char APP_MAKE_BUFFER_DMA_READY UART0_id[] = "UART0 identified\r\n"; // string to identify apps
char APP_MAKE_BUFFER_DMA_READY UART1_id[] = "UART1 identifier\r\n"; // string to identify apps
char APP_MAKE_BUFFER_DMA_READY identifier[] = "EFH2 Bootstrap\r\n"; // string to identify apps
char APP_MAKE_BUFFER_DMA_READY restart[] = "restarting...\r\n"; // restart warning message

//friendly names for ports
#define COM1 USB_DEVICE_CDC_INDEX_0
#define COM2 USB_DEVICE_CDC_INDEX_1
#define COM3 USB_DEVICE_CDC_INDEX_2



// Callbacks for UART buffer events, used to record completion and length of read/writes

void APP_BufferEventHandler(DRV_USART_BUFFER_EVENT bufferEvent, DRV_USART_BUFFER_HANDLE bufferHandle, uintptr_t context) {

    switch (bufferEvent) {
        case DRV_USART_BUFFER_EVENT_COMPLETE:

            if (appData.USART[0].readBufferHandler == bufferHandle) {
                if (appData.USART[0].isReadComplete == false) {
                    appData.USART[0].readDataLength = DRV_USART_BufferCompletedBytesGet(bufferHandle);
                    appData.USART[0].isReadComplete = true;
                }
            }

            if (appData.USART[0].writeBufferHandler == bufferHandle) {
                if (appData.USART[0].isWriteComplete == false) {
                    appData.USART[0].isWriteComplete = true;
                }
            }

            if (appData.USART[1].readBufferHandler == bufferHandle) {
                if (appData.USART[1].isReadComplete == false) {
                    appData.USART[1].readDataLength = DRV_USART_BufferCompletedBytesGet(bufferHandle);
                    appData.USART[1].isReadComplete = true;
                }
            }

            if (appData.USART[1].writeBufferHandler == bufferHandle) {
                if (appData.USART[1].isWriteComplete == false) {
                    appData.USART[1].isWriteComplete = true;
                }
            }

            break;

        case DRV_USART_BUFFER_EVENT_ERROR:

            //TODO: Add error checking here
            appData.errorStatus = true;

            break;

        default:
            break;
    }
}

/*******************************************************
 * USB CDC Device Events - Application Event Handler
 *******************************************************/

USB_DEVICE_CDC_EVENT_RESPONSE APP_USBDeviceCDCEventHandler(USB_DEVICE_CDC_INDEX index, USB_DEVICE_CDC_EVENT event, void * pData, uintptr_t userData) {
    APP_DATA * appDataObject;
    USB_CDC_CONTROL_LINE_STATE * controlLineStateData;
    USB_DEVICE_CDC_EVENT_DATA_READ_COMPLETE * eventDataRead;

    appDataObject = (APP_DATA *) userData;

    if (index == 2) {
        appDataObject->appCOMPortObjects[index].readDataLength = 0;
    }
    switch (event) {
        case USB_DEVICE_CDC_EVENT_GET_LINE_CODING:

            /* This means the host wants to know the current line
             * coding. This is a control transfer request. Use the
             * USB_DEVICE_ControlSend() function to send the data to
             * host.  */

            USB_DEVICE_ControlSend(appDataObject->deviceHandle,
                    &appDataObject->appCOMPortObjects[index].getLineCodingData, sizeof (USB_CDC_LINE_CODING));

            break;

        case USB_DEVICE_CDC_EVENT_SET_LINE_CODING:

            /* This means the host wants to set the line coding.
             * This is a control transfer request. Use the
             * USB_DEVICE_ControlReceive() function to receive the
             * data from the host */
            appDataObject->appCOMPortObjects[index].isSetLineCodingCommandInProgress = true;
            appDataObject->appCOMPortObjects[index].isBaudrateDataReceived = false;
            USB_DEVICE_ControlReceive(appDataObject->deviceHandle,
                    &appDataObject->appCOMPortObjects[index].setLineCodingData, sizeof (USB_CDC_LINE_CODING));

            break;

        case USB_DEVICE_CDC_EVENT_SET_CONTROL_LINE_STATE:

            /* This means the host is setting the control line state.
             * Read the control line state. We will accept this request
             * for now. */

            controlLineStateData = (USB_CDC_CONTROL_LINE_STATE *) pData;
            appDataObject->appCOMPortObjects[index].controlLineStateData.dtr = controlLineStateData->dtr;
            appDataObject->appCOMPortObjects[index].controlLineStateData.carrier = controlLineStateData->carrier;

            USB_DEVICE_ControlStatus(appDataObject->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);

            break;

        case USB_DEVICE_CDC_EVENT_SEND_BREAK:

            /* This means that the host is requesting that a break of the
             * specified duration be sent. Read the break duration */

            appDataObject->appCOMPortObjects[index].breakData = ((USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK *) pData)->breakDuration;

            /* Complete the control transfer by sending a ZLP  */
            USB_DEVICE_ControlStatus(appDataObject->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);

            break;

        case USB_DEVICE_CDC_EVENT_READ_COMPLETE:

            /* This means that the host has sent some data*/
            eventDataRead = (USB_DEVICE_CDC_EVENT_DATA_READ_COMPLETE *) pData;

            if (eventDataRead->status != USB_DEVICE_CDC_RESULT_ERROR) {
                appDataObject->appCOMPortObjects[index].readDataLength = eventDataRead->length;

                appDataObject->appCOMPortObjects[index].isReadComplete = true;
            }
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:

            /* The data stage of the last control transfer is
             * complete. */
            if (appDataObject->appCOMPortObjects[index].isSetLineCodingCommandInProgress == true) {
                /* We have received set line coding command from the Host.
                 * DRV_USART_BaudSet() function is not interrupt safe and it
                 * should not be called here. It is called in APP_Tasks()
                 * function. The ACK for Status stage of the control transfer is
                 * send in the APP_Tasks() function.  */
                appDataObject->appCOMPortObjects[index].isSetLineCodingCommandInProgress = false;
                appDataObject->appCOMPortObjects[index].isBaudrateDataReceived = true;
            } else {
                /* ACK the Status stage of the Control transfer */
                USB_DEVICE_ControlStatus(appDataObject->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);
            }
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT:

            /* This means the GET LINE CODING function data is valid. We don't
             * do much with this data in this demo. */
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_ABORTED:

            /* The control transfer has been aborted */
            if (appDataObject->appCOMPortObjects[index].isSetLineCodingCommandInProgress == true) {
                appDataObject->appCOMPortObjects[index].isSetLineCodingCommandInProgress = false;
                appDataObject->appCOMPortObjects[index].isBaudrateDataReceived = false;
            }

            break;
        case USB_DEVICE_CDC_EVENT_WRITE_COMPLETE:

            /* This means that the data write got completed. We can schedule
             * the next read. */

            appDataObject->appCOMPortObjects[index].isWriteComplete = true;
            break;

        default:
            break;
    }

    return USB_DEVICE_CDC_EVENT_RESPONSE_NONE;
}

/***********************************************
 * Application USB Device Layer Event Handler.
 ***********************************************/
void APP_USBDeviceEventHandler(USB_DEVICE_EVENT event, void * eventData, uintptr_t context) {
    USB_DEVICE_EVENT_DATA_CONFIGURED *configuredEventData;

    switch (event) {
        case USB_DEVICE_EVENT_SOF:

            appData.sofEventHasOccurred = true;

            break;

        case USB_DEVICE_EVENT_RESET:

            /* Update LED to show reset state */
            LED14_Set();

            appData.isConfigured = false;

            break;

        case USB_DEVICE_EVENT_CONFIGURED:

            /* Check the configuration. We only support configuration 1 */
            configuredEventData = (USB_DEVICE_EVENT_DATA_CONFIGURED*) eventData;

            if (configuredEventData->configurationValue == 1) {
                /* Update LED to show configured state */
                LED14_Clear();

                /* Register the CDC Device application event handler here.
                 * Note how the appData object pointer is passed as the
                 * user data */
                USB_DEVICE_CDC_EventHandlerSet(COM1, APP_USBDeviceCDCEventHandler, (uintptr_t) & appData);
                USB_DEVICE_CDC_EventHandlerSet(COM2, APP_USBDeviceCDCEventHandler, (uintptr_t) & appData);
                USB_DEVICE_CDC_EventHandlerSet(COM3, APP_USBDeviceCDCEventHandler, (uintptr_t) & appData);
                /* Mark that the device is now configured */
                appData.isConfigured = true;
            }

            break;

        case USB_DEVICE_EVENT_POWER_DETECTED:

            /* VBUS was detected. We can attach the device */
            USB_DEVICE_Attach(appData.deviceHandle);

            break;

        case USB_DEVICE_EVENT_POWER_REMOVED:

            /* VBUS is not available. We can detach the device */
            USB_DEVICE_Detach(appData.deviceHandle);

            appData.isConfigured = false;

            LED14_Set();

            break;

        case USB_DEVICE_EVENT_SUSPENDED:

            /* Switch LED to show suspended state */
            LED14_Set();

            break;

        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_ERROR:
        default:

            break;
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/*****************************************************
 * This function is called in every step of the
 * application state machine.
 *****************************************************/

bool APP_StateReset(void) {
    /* This function returns true if the device
     * was reset  */
    int i = 0;
    bool retVal;

    if (appData.isConfigured == false) {
        appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;

        for (i = 0; i < NUM_EMULATED_COM_PORTS; i++) {
            appData.appCOMPortObjects[i].readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
            appData.appCOMPortObjects[i].writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
            appData.appCOMPortObjects[i].isReadComplete = false;
            appData.appCOMPortObjects[i].isWriteComplete = false;
            appData.appCOMPortObjects[i].isSetLineCodingCommandInProgress = false;
            appData.appCOMPortObjects[i].isBaudrateDataReceived = false;
        }

        retVal = true;
    } else {
        retVal = false;
    }

    return (retVal);
}
//Send ack to line coding set command

void APP_AckControlTransfer(void) {
    USB_DEVICE_ControlStatus(appData.deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);
}
//Attempt to set line coding according to USB master

void _APP_SetLineCodingHandler(int CDCPort, int USARTPort) {
    DRV_USART_SERIAL_SETUP UsartSetup;

    UsartSetup.baudRate = 214;
    //UsartSetup.baudRate = appData.appCOMPortObjects[CDCPort].setLineCodingData.dwDTERate;
    UsartSetup.parity = appData.appCOMPortObjects[CDCPort].setLineCodingData.bParityType;
    UsartSetup.stopBits = appData.appCOMPortObjects[CDCPort].setLineCodingData.bCharFormat;
    if (appData.appCOMPortObjects[CDCPort].setLineCodingData.bDataBits <= (uint8_t) DRV_USART_DATA_9_BIT) {
        UsartSetup.dataWidth = appData.appCOMPortObjects[CDCPort].setLineCodingData.bDataBits - APP_USART_USB_DATA_WIDTH_DIFF;
    } else {
        /* If it is a non-supported data width, we currently set it to 8-bit 
         * mode value. */
        UsartSetup.dataWidth = DRV_USART_DATA_8_BIT;
    }

    DRV_USART_ReadQueuePurge(appData.USART[USARTPort].handle);
    DRV_USART_WriteQueuePurge(appData.USART[USARTPort].handle);
    DRV_USART_ReadAbort(appData.USART[USARTPort].handle);

    if (true == DRV_USART_SerialSetup(appData.USART[USARTPort].handle, &UsartSetup)) {
        /* Baudrate is changed successfully. Update Baudrate info in the
         * Get line coding structure. */

        appData.appCOMPortObjects[CDCPort].getLineCodingData.dwDTERate = appData.appCOMPortObjects[CDCPort].setLineCodingData.dwDTERate;
        appData.appCOMPortObjects[CDCPort].getLineCodingData.bParityType = appData.appCOMPortObjects[CDCPort].setLineCodingData.bParityType;
        appData.appCOMPortObjects[CDCPort].getLineCodingData.bDataBits = appData.appCOMPortObjects[CDCPort].setLineCodingData.bDataBits;
        appData.appCOMPortObjects[CDCPort].getLineCodingData.bCharFormat = appData.appCOMPortObjects[CDCPort].setLineCodingData.bCharFormat;

        // Start first USART read when port is configured, as any existing reads have been aborted
        // TODO tidy this up by moving buffers into structure
        switch (USARTPort) {
            case 0:
                DRV_USART_ReadBufferAdd(appData.USART[USARTPort].handle, uart0ReadBuffer, 1, &appData.USART[USARTPort].readBufferHandler);
                break;
            case 1:
                DRV_USART_ReadBufferAdd(appData.USART[USARTPort].handle, uart1ReadBuffer, 1, &appData.USART[USARTPort].readBufferHandler);
                break;
        }

        /* Acknowledge the Status stage of the Control transfer */
        APP_AckControlTransfer();
    } else {
        /* Baudrate was not set. There are two ways that an unsupported
         * baud rate could be handled.  The first is just to ignore the
         * request and ACK the control transfer.  That is what is currently
         * implemented below. */
        APP_AckControlTransfer();


        /* The second possible method is to stall the STATUS stage of the
         * request. STALLing the STATUS stage will cause an exception to be
         * thrown in the requesting application. Some programs, like
         * HyperTerminal, handle the exception properly and give a pop-up
         * box indicating that the request settings are not valid.  Any
         * application that does not handle the exception correctly will
         * likely crash when this request fails.  For the sake of example
         * the code required to STALL the status stage of the request is
         * provided below.  It has been left out so that this demo does not
         * cause applications without the required exception handling to
         * crash.*/
        //USB_DEVICE_ControlStatus(appData.usbDevHandle, USB_DEVICE_CONTROL_STATUS_ERROR);
    }


}



// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize(void)

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize(void) {
    int i = 0;
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    /* Device Layer Handle  */
    appData.deviceHandle = USB_DEVICE_HANDLE_INVALID;

    /* Device configured status */
    appData.isConfigured = false;

    for (i = 0; i < NUM_EMULATED_COM_PORTS; i++) {
        /* Initial get line coding state */
        appData.appCOMPortObjects[i].getLineCodingData.dwDTERate = 115200;
        appData.appCOMPortObjects[i].getLineCodingData.bParityType = 0;
        appData.appCOMPortObjects[i].getLineCodingData.bParityType = 0;
        appData.appCOMPortObjects[i].getLineCodingData.bDataBits = 8;

        /* Read Transfer Handle */
        appData.appCOMPortObjects[i].readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

        /* Write Transfer Handle */
        appData.appCOMPortObjects[i].writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

        /* Initialize the read complete flag */
        appData.appCOMPortObjects[i].isReadComplete = false; //TODO: should be false?

        /*Initialize the write complete flag*/
        appData.appCOMPortObjects[i].isWriteComplete = false;
        appData.appCOMPortObjects[i].readDataLength = 1;


    }


    appData.errorStatus = false;


    /* USART Driver Handle */
    //TODO: Create structure in appdata for 2 usarts
    //appData.USART[0].uartTxCount = 0;
    appData.USART[0].handle = DRV_HANDLE_INVALID;
    appData.USART[0].readBufferHandler = DRV_USART_BUFFER_HANDLE_INVALID;
    appData.USART[0].writeBufferHandler = DRV_USART_BUFFER_HANDLE_INVALID;
    appData.USART[0].isReadComplete = false;
    appData.USART[0].isWriteComplete = false;

    //appData.USART[1].uartTxCount = 0;
    appData.USART[1].handle = DRV_HANDLE_INVALID;
    appData.USART[1].readBufferHandler = DRV_USART_BUFFER_HANDLE_INVALID;
    appData.USART[1].writeBufferHandler = DRV_USART_BUFFER_HANDLE_INVALID;
    appData.USART[1].isReadComplete = false;
    appData.USART[1].isWriteComplete = false;
    /* Reset other flags */
    appData.sofEventHasOccurred = false;
}
static void reset_all_buffers(void);

static void reset_all_buffers(void) {
    memset(com1ReadBuffer, 0, sizeof (com1ReadBuffer));
    memset(com2ReadBuffer, 0, sizeof (com1ReadBuffer));
    memset(com3ReadBuffer, 0, sizeof (com1ReadBuffer));
    memset(uart0ReadBuffer, 0, sizeof (com1ReadBuffer));
    memset(uart1ReadBuffer, 0, sizeof (com1ReadBuffer));
    memset(BootloaderBuffer, 0, sizeof (com1ReadBuffer));

    appData.appCOMPortObjects[COM1].isReadComplete = false;
    appData.appCOMPortObjects[COM2].isReadComplete = false;
    appData.appCOMPortObjects[COM3].isReadComplete = false;
    appData.USART[0].isReadComplete = false;
    appData.USART[1].isReadComplete = false;
}

void delay(uint m){
    uint i;
    for(i=0;i<1000 * m;i++)Nop();
}

/******************************************************************************
  Function:
    void APP_Tasks(void)

  Remarks:
    See prototype in app.h.
 */
void APP_Tasks(void) {
    //TODO fix this for multiple ports
    if ((appData.isConfigured) && (appData.appCOMPortObjects[COM1].isBaudrateDataReceived)) {
        appData.appCOMPortObjects[COM1].isBaudrateDataReceived = false;
        _APP_SetLineCodingHandler(COM1, 0); // COM1, UART0

    }

    if ((appData.isConfigured) && (appData.appCOMPortObjects[COM2].isBaudrateDataReceived)) {
        appData.appCOMPortObjects[COM2].isBaudrateDataReceived = false;
        _APP_SetLineCodingHandler(COM2, 1); // COM2, UART1

    }
    if ((appData.isConfigured) && (appData.appCOMPortObjects[COM3].isBaudrateDataReceived)) {
        appData.appCOMPortObjects[COM2].isBaudrateDataReceived = false;
        //not a real com port, so just ack whatever the user wants
        APP_AckControlTransfer();
    }
    /* Update the application state machine based
     * on the current state */

    bool end_before_reads = false;
    
    switch (appData.state) {
        case APP_STATE_INIT:
            //LED14_Set();    //green led is reserved for USB connectivity indicator
            LED15_Clear(); //red led on
            LED13_Set(); //all others off
            LED16_Set();
            LED17_Set();
            /* Open the device layer */
            appData.deviceHandle = USB_DEVICE_Open(USB_DEVICE_INDEX_0, DRV_IO_INTENT_READWRITE);

            if (appData.deviceHandle != USB_DEVICE_HANDLE_INVALID) {
                appData.USART[0].handle = DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_READWRITE);

                if (appData.USART[0].handle != DRV_HANDLE_INVALID) {
                    DRV_USART_BufferEventHandlerSet(appData.USART[0].handle, APP_BufferEventHandler, 0);
                } else {
                    appData.state = APP_STATE_ERROR;
                    return;
                }

                appData.USART[1].handle = DRV_USART_Open(DRV_USART_INDEX_1, DRV_IO_INTENT_READWRITE);

                if (appData.USART[1].handle != DRV_HANDLE_INVALID) {
                    DRV_USART_BufferEventHandlerSet(appData.USART[1].handle, APP_BufferEventHandler, 0);
                } else {
                    appData.state = APP_STATE_ERROR;
                    return;
                }

                /* Register a callback with device layer to get event notification (for end point 0) */
                USB_DEVICE_EventHandlerSet(appData.deviceHandle, APP_USBDeviceEventHandler, 0);


                appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            } else {
                /* The Device Layer is not ready to be opened. We should try
                 * again later. */
            }

            break;

        case APP_STATE_WAIT_FOR_CONFIGURATION:

            /* Check if the device was configured */

            if (appData.isConfigured) {
                /* If the device is configured then lets start
                 * the application */

                appData.state = APP_STATE_CHECK_IF_CONFIGURED;

                /* Schedule a read on COM1 and COM2 */
                appData.appCOMPortObjects[COM1].isReadComplete = false;
                appData.appCOMPortObjects[COM2].isReadComplete = false;
                appData.appCOMPortObjects[COM3].isReadComplete = false;

                USB_DEVICE_CDC_Read(COM1,
                        &appData.appCOMPortObjects[COM1].readTransferHandle,
                        com1ReadBuffer, APP_READ_BUFFER_SIZE);

                USB_DEVICE_CDC_Read(COM2,
                        &appData.appCOMPortObjects[COM2].readTransferHandle,
                        com2ReadBuffer, APP_READ_BUFFER_SIZE);

                USB_DEVICE_CDC_Read(COM3,
                        &appData.appCOMPortObjects[COM3].readTransferHandle,
                        com3ReadBuffer, APP_READ_BUFFER_SIZE);


                // USART reads started after port configured
                DRV_USART_ReadBufferAdd(appData.USART[0].handle, uart0ReadBuffer, 1, &appData.USART[0].readBufferHandler);
                DRV_USART_ReadBufferAdd(appData.USART[1].handle, uart1ReadBuffer, 1, &appData.USART[1].readBufferHandler);

            }
            break;

        case APP_STATE_CHECK_IF_CONFIGURED:

            if (appData.isConfigured) {
                /* This means this device is still configured */
                appData.state = APP_STATE_CHECK_FOR_READ_COMPLETE;
            } else {
                APP_StateReset();
                appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            }
            break;

        case APP_STATE_CHECK_FOR_READ_COMPLETE:


            if (appData.UART1_reseting_state > 0) {
                if (appData.UART1_reseting_state == UART1_reset_retry_count) {
                    reset_uart_buffer[0] = 'x';
                    DRV_USART_WriteBufferAdd(appData.USART[1].handle, reset_uart_buffer, 1, &appData.USART[1].writeBufferHandler);
                    LED16_Clear();
                }
                if (appData.USART[1].isReadComplete == true) {
                    // message on UART1 - looking for 'Q'
                    appData.USART[1].isReadComplete = false;
                    if (uart1ReadBuffer[0] != 0) {
                        LED16_Set();
                        appData.UART1_reseting_state = 0;
                        reset_all_buffers(); // good intention, no improvement
                    } else {
                        appData.UART1_reseting_state = UART1_reset_retry_count;
                    }
                } else {
                    appData.UART1_reseting_state--;
                }
            }
            
            if (appData.UART0_reseting_state > 0) {
                static int skip = 1000;
                
                if (appData.USART[0].isReadComplete == true) {
                    // message on UART1 - looking for response
                    appData.USART[0].isReadComplete = false;
                    //if (uart0ReadBuffer[0] != 0)
                    {
                        LED16_Set();
                        appData.UART0_reseting_state = 0;
                        end_before_reads = true;
                    }
                }
                else
                if(skip-- > 0)
                {}
                else{
                    skip = 1000;
                    {
                        appData.UART0_reseting_state--;
                        reset_uart_buffer[0] = 'a';
                        DRV_USART_WriteBufferAdd(appData.USART[0].handle, reset_uart_buffer, 1, &appData.USART[0].writeBufferHandler);
                        LED16_Clear();
                    }
                }
                end_before_reads = true;
            }

            if (appData.appCOMPortObjects[COM1].isReadComplete == true) {
                /* This means we got data on COM1. Write this data to USART0.*/
                appData.appCOMPortObjects[COM1].isReadComplete = false;

                if (appData.USART[0].handle == appData.USART[1].handle) {
                    appData.errorStatus = true;
                }
                if (appData.UARTS_identification == false) {
                    DRV_USART_WriteBufferAdd(appData.USART[0].handle, com1ReadBuffer, appData.appCOMPortObjects[COM1].readDataLength, &appData.USART[0].writeBufferHandler);
                } else {
                    if (com1ReadBuffer[0] == '?') {
                        USB_DEVICE_CDC_Write(COM1,
                                &appData.appCOMPortObjects[COM1].writeTransferHandle,
                                UART0_id, strlen(UART0_id),
                                USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
                    }
                }
            }

            if (appData.appCOMPortObjects[COM2].isReadComplete == true) {
                /* This means we got data on COM2. Write this data to USART1 */

                appData.appCOMPortObjects[COM2].isReadComplete = false;


                if (appData.UARTS_identification == false) {
                    DRV_USART_WriteBufferAdd(appData.USART[1].handle, com2ReadBuffer, appData.appCOMPortObjects[COM2].readDataLength, &appData.USART[1].writeBufferHandler);
                } else {
                    if (com1ReadBuffer[0] == '?') {
                        USB_DEVICE_CDC_Write(COM2,
                                &appData.appCOMPortObjects[COM2].writeTransferHandle,
                                UART1_id, strlen(UART1_id),
                                USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
                    }
                }
            }

            if (appData.appCOMPortObjects[COM3].isReadComplete == true) {
                // This means we got data on COM3.
                appData.appCOMPortObjects[COM3].isReadComplete = false;

                switch (com3ReadBuffer[0]) {
                    case '?':
                        USB_DEVICE_CDC_Write(COM3,
                                &appData.appCOMPortObjects[COM3].writeTransferHandle,
                                identifier, strlen(identifier),
                                USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
                        break;
                    case 'r':
                        USB_DEVICE_CDC_Write(COM3,
                                &appData.appCOMPortObjects[COM3].writeTransferHandle,
                                restart, strlen(restart),
                                USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
                        ShortDelay();
                        TriggerBootloader();
                        break;
                    case 'l':
                        LED13_Clear();
                        appData.UARTS_identification = true;
                        USB_DEVICE_CDC_Write(COM3,
                                &appData.appCOMPortObjects[COM3].writeTransferHandle,
                                identifier, strlen(identifier),
                                USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
                        break;
                    case 'u':
                        appData.UART0_reseting_state = UART0_reset_retry_count;
                        LED13_Set();
                        appData.UARTS_identification = false;
                        USB_DEVICE_CDC_Write(COM3,
                                &appData.appCOMPortObjects[COM3].writeTransferHandle,
                                identifier, strlen(identifier),
                                USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
                        break;
                    case 'h':
                        appData.UART1_reseting_state = UART1_reset_retry_count;
                        appData.UARTS_identification = false;
                        USB_DEVICE_CDC_Write(COM3,
                                &appData.appCOMPortObjects[COM3].writeTransferHandle,
                                identifier, strlen(identifier),
                                USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
                        break;
                    default:
                        //echo
                        USB_DEVICE_CDC_Write(COM3,
                                &appData.appCOMPortObjects[COM3].writeTransferHandle,
                                com3ReadBuffer, appData.appCOMPortObjects[COM3].readDataLength,
                                USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
                        break;
                }

                //re-trigger read
                USB_DEVICE_CDC_Read(COM3,
                        &appData.appCOMPortObjects[COM3].readTransferHandle,
                        com3ReadBuffer, APP_READ_BUFFER_SIZE);
            }
            
            if(end_before_reads){
                end_before_reads=false;
                appData.state = APP_STATE_CHECK_FOR_WRITE_COMPLETE;
                break;
            }

            if (appData.USART[0].isReadComplete == true) {
                // message on UART0, send to COM1
                appData.USART[0].isReadComplete = false;
                // start write process
                appData.appCOMPortObjects[COM1].isWriteComplete = false;
                USB_DEVICE_CDC_Write(COM1,
                        &appData.appCOMPortObjects[COM1].writeTransferHandle,
                        uart0ReadBuffer, appData.USART[0].readDataLength,
                        USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
            }

            if (appData.USART[1].isReadComplete == true) {
                // message on UART1, send to COM2  
                appData.USART[1].isReadComplete = false;
                // start write process
                appData.appCOMPortObjects[COM2].isWriteComplete = false;
                USB_DEVICE_CDC_Write(COM2,
                        &appData.appCOMPortObjects[COM2].writeTransferHandle,
                        uart1ReadBuffer, appData.USART[1].readDataLength,
                        USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
            }

            appData.state = APP_STATE_CHECK_FOR_WRITE_COMPLETE;
            break;

        case APP_STATE_CHECK_FOR_WRITE_COMPLETE:

            /* Check if the write is complete */

            if (appData.appCOMPortObjects[COM1].isWriteComplete) {
                appData.appCOMPortObjects[COM1].isWriteComplete = false;

                // cdc_com1 write complete, start read on UART0
                appData.USART[0].isReadComplete = false;
                DRV_USART_ReadBufferAdd(appData.USART[0].handle, uart0ReadBuffer, 1, &appData.USART[0].readBufferHandler);
            }

            if (appData.appCOMPortObjects[COM2].isWriteComplete) {
                appData.appCOMPortObjects[COM2].isWriteComplete = false;

                //swapped usart ports around
                // cdc_com2 write complete, start read on UART1
                appData.USART[1].isReadComplete = false;
                DRV_USART_ReadBufferAdd(appData.USART[1].handle, uart1ReadBuffer, 1, &appData.USART[1].readBufferHandler);
            }

            if (appData.appCOMPortObjects[COM3].isWriteComplete) {
                appData.appCOMPortObjects[COM3].isWriteComplete = false;

                // we have written response, now read again
                appData.appCOMPortObjects[COM3].isReadComplete = false;

                USB_DEVICE_CDC_Read(COM3,
                        &appData.appCOMPortObjects[COM3].readTransferHandle,
                        com3ReadBuffer, APP_READ_BUFFER_SIZE);
            }

            if (appData.USART[0].isWriteComplete) {
                ///USART0 write finished, start fresh read on CDC_COM1
                appData.USART[0].isWriteComplete = false;

                appData.appCOMPortObjects[COM1].isReadComplete = false;

                USB_DEVICE_CDC_Read(COM1,
                        &appData.appCOMPortObjects[COM1].readTransferHandle,
                        com1ReadBuffer, APP_READ_BUFFER_SIZE);
            }

            if (appData.USART[1].isWriteComplete) {
                ///USART1 write finished, start fresh read on CDC_COM2
                appData.USART[1].isWriteComplete = false;

                appData.appCOMPortObjects[COM2].isReadComplete = false;

                USB_DEVICE_CDC_Read(COM2,
                        &appData.appCOMPortObjects[COM2].readTransferHandle,
                        com2ReadBuffer, APP_READ_BUFFER_SIZE);
            }

            appData.state = APP_STATE_CHECK_IF_CONFIGURED;

            if (appData.errorStatus == true) {
                appData.state = APP_STATE_ERROR;
            }

            break;

        case APP_STATE_ERROR:
            LED14_Set();
            break;

        default:
            break;
    }
}



/*******************************************************************************
 End of File
 */

