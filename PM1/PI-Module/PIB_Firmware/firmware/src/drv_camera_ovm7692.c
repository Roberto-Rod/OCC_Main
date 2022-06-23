/*******************************************************************************
 OVM7692 Camera Driver Implementation.

  File Name:
    drv_camera_OVM7692.c

  Summary:
    OVM7692 camera driver interface declarations for the
    static single instance driver.

  Description:
    The OVM7692 camera device driver provides a simple interface to manage
    the OVM7692 camera cube interfacing to Microchip microcontrollers. This
    file defines the implementation for the OVM7692 driver.
 ******************************************************************************/

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "configuration.h"
#include "drv_camera_OVM7692.h"
#include "drv_camera_sccb.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************

/* This is the driver instance object array. */
DRV_CAMERA_OVM7692_OBJ        gDrvCameraOVM7692Obj[DRV_CAMERA_OVM7692_INSTANCES_NUMBER] ;

/* This is the client object array. */
DRV_CAMERA_OVM7692_CLIENT_OBJ gDrvCameraOVM7692ClientObj[DRV_CAMERA_OVM7692_CLIENTS_NUMBER];

/**************************** Default Register Values ****************************/     
static const uint8_t drvRegisters[] = 
{
    0x12, REG12_SOFT_RESET,     // 1     Soft Reset
    0x0E, REG0E_SLEEP_MODE,     // 2     
    0x69, 0b01010010,           // 3     
    0x1E, 0b10110011,           // 4     
    0x48, 0b01000010,           // 5     
    0xFF, MIPI_BANK_SEL,        // 6     
    0xB5, 0b00110000,           // 7     
    0xFF, MIPI_SCR_SEL,         // 8     
    0x16, REG16_DEFAULT,        // 9     
    0x62, 0b00010000,           // 10    
    0x12, REG12_DEFAULT,        // 11     RGB565 RGB Output  
    0x17, 192,                  // 12     
    0x19, 64,                   // 14          
    0x18, HSIZE_DEFAULT,        // 13     
    0x1A, VSIZE_DEFAULT,        // 15     
    0x22, 0b00000000,           // 16     
    0x37, 0b00000100,           // 17     
    0x3E, REG3E_DEFAULT,        // 18     
    0x64, 0b00100001,           // 19     
    0x5E, 0b00010000,           // 20     
    0x69, 0b00000010,           // 21     
    0x80, REG80_DEFAULT,        // 22     
    0x81, REG81_DEFAULT,        // 23     
    0xCC, 0b00000000,           // 24     Horizontal output size bit 9:8    Def: 320
    0xCD, 0b11110000,           // 25     Horizontal output size bit 7:0    
    0xCE, 0b00000000,           // 26     Vertical output size bit 8        Def: 240
    0xCF, 0b11110000,           // 27     Vertical output size bits 7:0
    0x82, 0b00000011,           // 28     
    0xC8, 0b00000001,           // 29     Horizontal input size bit 9:8     Def: 656
    0xC9, 0b11100000,           // 30     Horizontal input size bit 7:0     
    0xCA, 0b00000001,           // 31     Vertical input size bit 8         Def: 492
    //0xCB, 0b11100000,           // 32     Vertical input size bits 7:0      
    0xCB, 0b10111000,   //now 440 (was 480) PW
    0xD0, 0b00101000,           // 33     Changes Boundary Offset    
    0x0E, REG0E_DEFAULT,        // 34     
    0x70, 0b00000000,           // 35     
    0x71, 0b00110100,           // 36     
    0x74, 0b00101000,           // 37     
    0x75, 0b10011000,           // 38     
    0x76, 0b00000000,           // 39     
    0x77, 0b01100100,           // 40     
    0x78, 0b00000001,           // 41     
    0x79, 0b11000010,           // 42     
    0x7A, 0b01001110,           // 43     
    0x7B, 0b00011111,           // 44     
    0x7C, 0b00000000,           // 45     
    0x11, CLKRC_DEFAULT,        // 46     Clock Pre-Scaler 2
    0x20, 0b00000000,           // 47     
    0x21, 0b01010111,           // 48     
    0x50, 0b01001101,           // 49     
    0x51, 0b01000000,           // 50     
    0x4C, 0x7D,                 // 51     
    0x0E, REG0E_DEFAULT,        // 52     
    0x80, REG80_DEFAULT,        // 53     
    0x85, 0b00000000,           // 54     
    0x86, 0b00000000,           // 55     
    0x87, 0b00000000,           // 56     
    0x88, 0b00000000,           // 57     
    0x89, 0b00101010,           // 58     
    0x8A, 0b00100010,           // 59     
    0x8B, 0b00100000,           // 60     
    0xBB, 0b10101011,           // 61     
    0xBC, 0b10000100,           // 62     
    0xBD, 0b00100111,           // 63     
    0xBE, 0b00001110,           // 64     
    0xBF, 0b10111000,           // 65     
    0xC0, 0b11000101,           // 66     
    0xC1, 0b00011110,           // 67     
    0xB7, 0b00000101,           // 68     
    0xB8, 0b00001001,           // 69     
    0xB9, 0b00000000,           // 70     
    0xBA, 0b00011000,           // 71     
    0x5A, 0b00011111,           // 72     
    0x5B, 0b10011111,           // 73     
    0x5C, 0b01101001,           // 74     
    0x5D, 0b01000010,           // 75     
    0x24, 0b01111000,           // 76     
    0x25, 0b01101000,           // 77     
    0x26, 0b10110011,           // 78     
    0xA3, 0b00001011,           // 79     
    0xA4, 0b00010101,           // 80     
    0xA5, 0b00101001,           // 81     
    0xA6, 0b01001010,           // 82     
    0xA7, 0b01011000,           // 83         
    0xA8, 0b01100101,           // 84     
    0xA9, 0b01110000,           // 85     
    0xAA, 0b01111011,           // 86     
    0xAB, 0b10000101,           // 87     
    0xAC, 0b10001110,           // 88     
    0xAD, 0b10100000,           // 89     
    0xAE, 0b10110000,           // 90     
    0xAF, 0b11001011,           // 91     
    0xB0, 0b11100001,           // 92     
    0xB1, 0b11110001,           // 93     
    0xB2, 0b00010100,           // 94     
    0x8E, 0b10010010,           // 95     
    0x96, 0b11111111,           // 96     
    0x97, 0b00000000,           // 97     
    0x14, REG14_DEFAULT,        // 98 
    0x0E, REG0E_DEFAULT,        // 99     
    0x28, REG28_DEFAULT,        // 100     
    0x0C, REG0C_DEFAULT,        // 101     
    0x13, REG13_DEFAULT,        // 102     
    0xD3, REGD3_DEFAULT,        // 103
    0xD8, 16,                   // 104
    0xD9, 16,                   // 105    
    0xD2, REGD2_DEFAULT,        // 106  
    0x0D, 0b01110001,           // 107
    0xC3, 0b10000000,           // 108
    0xD3, 0x30,                 // 109      Contrast adjustment +2
    0xD4, 0x28,                 // 110      Contrast adjustment +2
    0xD5, 0x20,                 // 111    
    0xDC, 0x00,                 // 112  
    0xB4, 0x10,                 // 113      De-noise
    0xB5, 0x00,                 // 114      +6
//    0x61, REG61_DEFAULT,        // 115    Show test pattern - Debug only.
};

#define DRV_REGISTER_COUNT           114
#define SYS_DEBUG(x,y)
// *****************************************************************************
// *****************************************************************************
// Section: Local prototypes
// *****************************************************************************
// *****************************************************************************

volatile DRV_CAMERA_FRAME __attribute__(( coherent, aligned(32))) buffer_data[DRV_CAMERA_FRAME_BUFFERS];

//volatile uint16_t __attribute__( (coherent, address(0x88000000))) buffer_data[DRV_CAMERA_FRAME_BUFFERS][DRV_CAMERA_FRAME_HEIGHT*DRV_CAMERA_FRAME_WIDTH];

// *****************************************************************************
// *****************************************************************************
// Section: Camera OVM7692 Driver Interface Implementations
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
     SYS_MODULE_OBJ DRV_CAMERA_OVM7692_Initialize
     (
        const SYS_MODULE_INDEX index,
        const SYS_MODULE_INIT * const init 
     )

  Summary:
    Initializes the Camera OVM7692 instance for the specified driver index.

  Description:
    This routine initializes the Camera OVM7692 driver instance for the 
    specified driver index, making it ready for clients to open and use it. The 
    initialization data is specified by the init parameter. The initialization 
    may fail if the number of driver objects allocated are insufficient or if 
    the specified driver instance is already initialized. The driver instance 
    index is independent of the Camera OVM7692 module ID. Refer to
    the description of the DRV_CAMERA_OVM7692_INIT data structure for more 
    details on which members on this data structure are overridden.

  Precondition:
    None.

  Parameters:
    index  - Identifier for the instance to be initialized
    
    init   - Pointer to a data structure containing any data necessary to
             initialize the driver.

  Returns:
    If successful, returns a valid handle to a driver instance object.  
    Otherwise, returns SYS_MODULE_OBJ_INVALID.

  Example:
    <code>
    // The following code snippet shows an example OVM7692 driver initialization.
    
    DRV_CAMERA_OVM7692_INIT     cameraInit;
    SYS_MODULE_OBJ              objectHandle;

    cameraInit.cameraID                = CAMERA_MODULE_OVM7692;
    cameraInit.sourcePort              = (void *)&PORTK,
    cameraInit.hsyncInterruptSource    = INT_SOURCE_CHANGE_NOTICE_A,
    cameraInit.vsyncInterruptSource    = INT_SOURCE_CHANGE_NOTICE_J,
    cameraInit.dmaChannel              = DRV_CAMERA_OVM7692_DMA_CHANNEL_INDEX,
    cameraInit.dmaTriggerSource        = DMA_TRIGGER_EXTERNAL_2,
    cameraInit.bpp                     = GFX_CONFIG_COLOR_DEPTH,

    objectHandle = DRV_CAMERA_OVM7692_Initialize( DRV_CAMERA_OVM7692_INDEX_0, 
                                                (SYS_MODULE_INIT*)&cameraInit);
    if (SYS_MODULE_OBJ_INVALID == objectHandle)
    {
        // Handle error
    }
    </code>

  Remarks:
    This routine must be called before any other OVM7692 routine is called.

    This routine should only be called once during system initialization
    unless DRV_CAMERA_OVM7692_Deinitialize is called to deinitialize the driver 
    instance. This routine will NEVER block for hardware access.
 */

SYS_MODULE_OBJ DRV_CAMERA_OVM7692_Initialize
(
    const SYS_MODULE_INDEX drvIndex,
    const SYS_MODULE_INIT * const init
)
{
    DRV_CAMERA_OVM7692_OBJ  *dObj       = (DRV_CAMERA_OVM7692_OBJ*)NULL;
    DRV_CAMERA_OVM7692_INIT *cameraInit = NULL ;

    /* Check if the specified driver index is in valid range */
    if(drvIndex >= DRV_CAMERA_OVM7692_INSTANCES_NUMBER)
    {
        SYS_DEBUG(0, "Invalid driver index");
        return SYS_MODULE_OBJ_INVALID;
    }

    /* Check if this hardware instance was already initialized */
    if(gDrvCameraOVM7692Obj[drvIndex].inUse != false)
    {
        SYS_DEBUG(0, "Instance already in use");
        return SYS_MODULE_OBJ_INVALID;
    }

    /* Assign to the local pointer the init data passed */
    cameraInit = ( DRV_CAMERA_OVM7692_INIT * ) init ;
    
    /* Allocate the driver object and set the operation flag to be in use */
    dObj                        = &gDrvCameraOVM7692Obj[drvIndex];
    dObj->inUse                 = true;
    dObj->nClients              = 0;
    dObj->frameBufferIndex      = 0;
    dObj->lastFrameBufferIndex  = 0;
    dObj->frameComplete         = 0;
    dObj->isExclusive           = false;
    dObj->moduleId              = cameraInit->cameraID;
    dObj->dmaChannel1           = cameraInit->dmaChannel1; 
    dObj->dmaChannel2           = cameraInit->dmaChannel2;
    dObj->dmaChannel3           = cameraInit->dmaChannel3;
    dObj->dmaChannel4           = cameraInit->dmaChannel4;    
    dObj->hsyncInterruptSource  = cameraInit->hsyncInterruptSource;
    dObj->vsyncInterruptSource  = cameraInit->vsyncInterruptSource;
    dObj->pclkInterruptSource   = cameraInit->pclkInterruptSource;
    dObj->sourcePort            = cameraInit->sourcePort;
    dObj->pwdnPin               = cameraInit->pwdnPin;
    dObj->shdnPin               = cameraInit->shdnPin;    
    dObj->sysDelayHandle        = SYS_TIME_HANDLE_INVALID;
    
    dObj->frameHorizontalSize   = cameraInit->frameHorizontalSize;
    dObj->frameVerticalSize     = cameraInit->frameVerticalSize;
    dObj->bytesPerPixel         = cameraInit->bytesPerPixel;
    
    dObj->paused                = false;
    dObj->lastFrame             = NULL;
    
   uint32_t i = 0;

    for( i = 0; i < DRV_CAMERA_FRAME_BUFFERS; i++ )
    {
        dObj->frameBuffer[i].header.type = GFXU_ASSET_TYPE_IMAGE;

        #ifdef DRV_USE_DDR   
        dObj->frameBuffer[i].header.dataLocation = GFXU_ASSET_LOCATION_ID_INTERNAL;        
        if(i == 0)
            dObj->frameBuffer[i].header.dataAddress = (void*)DRV_FRAME_BUFFER_1;
        else if(i == 1)
            dObj->frameBuffer[i].header.dataAddress = (void*)DRV_FRAME_BUFFER_2;
        #else
        dObj->frameBuffer[i].header.dataLocation = GFXU_ASSET_LOCATION_ID_INTERNAL;
        dObj->frameBuffer[i].header.dataAddress = (void*)buffer_data[i].Pixels;
        #endif   
        dObj->frameBuffer[i].header.dataSize = DRV_CAMERA_FRAME_WIDTH * DRV_CAMERA_FRAME_HEIGHT * DRV_CAMERA_COLOUR_DEPTH;

        dObj->frameBuffer[i].format = GFXU_IMAGE_FORMAT_RAW;            // image format type
        dObj->frameBuffer[i].width = DRV_CAMERA_FRAME_WIDTH;            // image width
        dObj->frameBuffer[i].height = DRV_CAMERA_FRAME_HEIGHT;          // image height
        dObj->frameBuffer[i].bufferWidth = DRV_CAMERA_FRAME_WIDTH;      // buffer width
        dObj->frameBuffer[i].bufferHeight = DRV_CAMERA_FRAME_HEIGHT;    // buffer height
        dObj->frameBuffer[i].colorMode = GFX_COLOR_MODE_RGB_565;        // image color mode
        dObj->frameBuffer[i].compType = GFXU_IMAGE_COMPRESSION_NONE;    // image compression type (raw only)
        dObj->frameBuffer[i].flags = GFXU_IMAGE_DIRECT_BLIT;            // image flags               
        dObj->frameBuffer[i].mask = 0x0;                                // image mask color
        dObj->frameBuffer[i].palette = GFX_NULL;                        // no palette
              
        dObj->dmaPtr[i][0] = (uint32_t)dObj->frameBuffer[i].header.dataAddress;
        dObj->dmaPtr[i][1] = dObj->dmaPtr[i][0] + ( dObj->frameBuffer[i].header.dataSize / DRV_DMA_TRANSFERS_PER_BUFFER );      
    }    
   
    /* Update the status */
    dObj->status = SYS_STATUS_READY;
    dObj->state = DRV_CAMERA_STATE_WAIT_FOR_OPEN; 
    
    /* Return the object structure */
    return ( (SYS_MODULE_OBJ)drvIndex );
}
// *****************************************************************************
/* Function:
    void DRV_CAMERA_OVM7692_Deinitialize( SYS_MODULE_OBJ object )

  Summary:
    Deinitializes the specified instance of the Camera OVM7692 driver module.

  Description:
    Deinitializes the specified instance of the Camera OVM7692 driver module, 
    disabling its operation (and any hardware). Invalidates all the internal 
    data.

  Precondition:
    Function DRV_CAMERA_OVM7692_Initialize should have been called before 
    calling this function.

  Parameters:
    object          - Driver object handle, returned from the 
                      DRV_CAMERA_OVM7692_Initialize routine

  Returns:
    None.

  Example:
    <code>
    SYS_MODULE_OBJ      object; //  Returned from DRV_CAMERA_OVM7692_Initialize
    SYS_STATUS          status;

    DRV_CAMERA_OVM7692_Deinitialize(object);

    status = DRV_CAMERA_OVM7692_Status(object);
    if (SYS_MODULE_DEINITIALIZED != status)
    {
        // Check again later if you need to know 
        // when the driver is deinitialized.
    }
    </code>

  Remarks:
    Once the Initialize operation has been called, the Deinitialize operation
    must be called before the Initialize operation can be called again. This 
    routine will NEVER block waiting for hardware.
 */
    
void DRV_CAMERA_OVM7692_DeInitialize(SYS_MODULE_OBJ object)
{
    DRV_CAMERA_OVM7692_OBJ * dObj;

    /* Check that the object is valid */

    if(object == SYS_MODULE_OBJ_INVALID)
    {
        SYS_DEBUG(0, "Invalid system object handle" );
        return;
    }

    if(object >= DRV_CAMERA_OVM7692_INSTANCES_NUMBER)
    {
        SYS_DEBUG(0, "Invalid system object handle" );
        return;
    }

    dObj = (DRV_CAMERA_OVM7692_OBJ*) &gDrvCameraOVM7692Obj[object];

    if(!dObj->inUse)
    {
        SYS_DEBUG(0, "Invalid system object handle");
        return;
    }

    /* The driver will not have clients when it is
       being deinitialized. So the order in which
       we do the following steps is not that important */

    /* Indicate that this object is not is use */
    dObj->inUse = false;

    /* Deinitialize the Camera status */
    dObj->status =  SYS_STATUS_UNINITIALIZED;

    /* Disable the interrupt */
    SYS_INT_SourceDisable(dObj->hsyncInterruptSource);
    SYS_INT_SourceDisable(dObj->vsyncInterruptSource);
}

// *****************************************************************************
/* Function:
    DRV_HANDLE DRV_CAMERA_OVM7692_Open
    (
        const SYS_MODULE_INDEX index,
        const DRV_IO_INTENT ioIntent
    )

  Summary:
    Opens the specified Camera OVM7692 driver instance and returns a handle to 
    it.

  Description:
    This routine opens the specified Camera OVM7692 driver instance and provides
    a handle that must be provided to all other client-level operations to
    identify the caller and the instance of the driver. The ioIntent 
    parameter defines how the client interacts with this driver instance.

  Precondition:
    Function DRV_CAMERA_OVM7692_Initialize must have been called before calling 
    this function.

  Parameters:
    index   - Identifier for the object instance to be opened
    
    intent  - Zero or more of the values from the enumeration
              DRV_IO_INTENT "ORed" together to indicate the intended use
              of the driver. See function description for details.

  Returns:
    If successful, the routine returns a valid open-instance handle (a number
    identifying both the caller and the module instance).
    
    If an error occurs, the return value is DRV_HANDLE_INVALID. Error can occur
    - if the number of client objects allocated via DRV_CAMERA_OVM7692_CLIENTS_NUMBER 
      is insufficient.
    - if the client is trying to open the driver but driver has been opened
      exclusively by another client.
    - if the driver hardware instance being opened is not initialized or is
      invalid.
    - if the client is trying to open the driver exclusively, but has already
      been opened in a non exclusive mode by another client.
    - if the driver is not ready to be opened, typically when the initialize
      routine has not completed execution.

  Example:
    <code>
    DRV_HANDLE handle;

    handle = DRV_CAMERA_OVM7692_Open(DRV_CAMERA_OVM7692_INDEX_0, DRV_IO_INTENT_EXCLUSIVE);
    if (DRV_HANDLE_INVALID == handle)
    {
        // Unable to open the driver
        // May be the driver is not initialized or the initialization
        // is not complete.
    }
    </code>

  Remarks:
    The handle returned is valid until the DRV_CAMERA_OVM7692_Close routine is 
    called. This routine will NEVER block waiting for hardware.If the requested 
    intent flags are not supported, the routine will return DRV_HANDLE_INVALID. 
    This function is thread safe in a RTOS application.

 */

DRV_HANDLE DRV_CAMERA_OVM7692_Open
(
    const SYS_MODULE_INDEX drvIndex,
    const DRV_IO_INTENT ioIntent
)
{
    DRV_CAMERA_OVM7692_CLIENT_OBJ *clientObj;
    DRV_CAMERA_OVM7692_OBJ *dObj;
    unsigned int iClient = 0;

    if (drvIndex >= DRV_CAMERA_OVM7692_INSTANCES_NUMBER)
    {
        /* Invalid driver index */
        SYS_DEBUG(0, "Invalid Driver Instance");
        return (DRV_HANDLE_INVALID);
    }

    dObj = &gDrvCameraOVM7692Obj[drvIndex];

    if((dObj->status != SYS_STATUS_READY) || (dObj->inUse == false))
    {
        /* The Camera module should be ready */

        SYS_DEBUG(0, "Was the driver initialized?");
        return DRV_HANDLE_INVALID;
    }

    if(dObj->isExclusive)
    {
        /* This means the another client has opened the driver in exclusive
           mode. The driver cannot be opened again */

        SYS_DEBUG(0, "Driver already opened exclusively");
        return ( DRV_HANDLE_INVALID ) ;
    }

    if((dObj->nClients > 0) && (ioIntent & DRV_IO_INTENT_EXCLUSIVE))
    {
        /* This means the driver was already opened and another driver was
           trying to open it exclusively.  We cannot give exclusive access in
           this case */

        SYS_DEBUG(0, "Driver already opened. Cannot be opened exclusively");
        return(DRV_HANDLE_INVALID);
    }
        
    clientObj               = &gDrvCameraOVM7692ClientObj[iClient];
    clientObj->inUse        = true;
    clientObj->hDriver      = dObj;
    dObj->nClients++;
    
    /* Update the client status */
    clientObj->status = DRV_CAMERA_OVM7692_CLIENT_STATUS_READY;
    dObj->state = DRV_CAMERA_STATE_INIT_PERIPHERALS;
    return ((DRV_HANDLE) clientObj );
}

// *****************************************************************************
/* Function:
    void DRV_CAMERA_OVM7692_Close( DRV_Handle handle )

  Summary:
    Closes an opened-instance of the Camera OVM7692 driver.

  Description:
    This routine closes an opened-instance of the Camera OVM7692 driver, 
    invalidating the handle. Any buffers in the driver queue that were submitted
    by this client will be removed. After calling this routine, the handle 
    passed in "handle" must not be used with any of the remaining driver 
    routines (with one possible exception described in the "Remarks" section).
    A new handle must be obtained by calling DRV_CAMERA_OVM7692_Open before the 
    caller may use the driver again

  Precondition:
    The DRV_CAMERA_OVM7692_Initialize routine must have been called for the 
    specified Camera OVM7692 driver instance.

    DRV_CAMERA_OVM7692_Open must have been called to obtain a valid opened 
    device handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    None.
                
  Example:
    <code>
    DRV_HANDLE handle;  // Returned from DRV_USART_Open

    DRV_CAMERA_OVM7692_Close(handle);
    
    </code>

  Remarks:
    Usually there is no need for the client to verify that the Close operation
    has completed.  The driver will abort any ongoing operations when this
    routine is called.
 */

void DRV_CAMERA_OVM7692_close ( DRV_HANDLE handle )
{
    /* This function closes the client, The client
       object is deallocated and returned to the
       pool. */

    DRV_CAMERA_OVM7692_CLIENT_OBJ * clientObj;
    DRV_CAMERA_OVM7692_OBJ * dObj;

    clientObj = (DRV_CAMERA_OVM7692_CLIENT_OBJ *) handle;
    
    if(clientObj == NULL)
    {
        /* Driver handle is not valid */
        SYS_DEBUG(0, "Invalid Driver Handle");
        return;
    }

    dObj = (DRV_CAMERA_OVM7692_OBJ *)clientObj->hDriver;

    /* Reduce the number of clients */
    dObj->nClients--;

    /* De-allocate the object */
    clientObj->status = DRV_CAMERA_OVM7692_CLIENT_STATUS_CLOSED;
    clientObj->inUse = false;

    return;
}

// *****************************************************************************

void _DRV_CAMERA_OVM7692_Start
(
    SYS_MODULE_OBJ object
)
{
    DRV_CAMERA_OVM7692_OBJ *dObj = &gDrvCameraOVM7692Obj[object];
     
    dObj->frameCount = 0;
    dObj->frameComplete = 0;
    dObj->frameBufferIndex = 0;    

    /* Clear the interrupts */  
    SYS_INT_SourceStatusClear(dObj->vsyncInterruptSource);    
    SYS_INT_SourceEnable(dObj->vsyncInterruptSource);
    
    dObj->state = DRV_CAMERA_STATE_RUNNING;
    dObj->substate = DRV_CAMERA_SUB_STATE_IDLE;
}

// *****************************************************************************
/* Function:
    DRV_CAMERA_OVM7692_ERROR DRV_CAMERA_OVM7692_Stop
    ( 
        DRV_HANDLE handle
    );
 
  Summary:
    Stops rendering the camera Pixel data.

  Description:
    This routine starts the camera rendering to the display by writing the pixel
    data to the frame buffer. Frame buffer is shared between camera OVM7692 and
    display controller.

  Precondition:
    The DRV_CAMERA_OVM7692_Initialize routine must have been called for the 
    specified Camera OVM7692 driver instance.

    DRV_CAMERA_OVM7692_Open must have been called to obtain a valid opened 
    device handle.

  Parameters:
    handle  - A valid open-instance handle, returned from the driver's
            open routine.

  Returns:
    DRV_CAMERA_OVM7692_ERROR_INVALID_HANDLE - Invalid driver Handle.
    DRV_CAMERA_OVM7692_ERROR_NONE - No error.
 
  Example:
    <code>

        DRV_HANDLE handle;

        handle = DRV_CAMERA_OVM7692_Open(DRV_CAMERA_OVM7692_INDEX_0, DRV_IO_INTENT_EXCLUSIVE);
        if (DRV_HANDLE_INVALID == handle)
        {
            //error
            return;    
        }

        if ( DRV_CAMERA_OVM7692_Stop( handle ) != 
                                            DRV_CAMERA_OVM7692_ERROR_NONE )
        {
            //error
            return;
        }

    </code>

  Remarks:
    This routine only disables the interrupt for hsync and vsync. To stop the 
    camera the power down pin need to be toggled to active high value. This will
    stop the camera internal clock and will maintain the register values.
 */

DRV_CAMERA_OVM7692_ERROR DRV_CAMERA_OVM7692_Stop
( 
    DRV_HANDLE handle
)
{
    DRV_CAMERA_OVM7692_CLIENT_OBJ * clientObj;
    DRV_CAMERA_OVM7692_OBJ * dObj;
    DRV_CAMERA_OVM7692_ERROR returnValue = DRV_CAMERA_OVM7692_ERROR_NONE;

    clientObj = (DRV_CAMERA_OVM7692_CLIENT_OBJ *) handle;
    
    if(clientObj == NULL)
    {
        /* Driver handle is not valid */
        SYS_DEBUG(0, "Invalid Driver Handle");
        returnValue = DRV_CAMERA_OVM7692_ERROR_INVALID_HANDLE;
    }
    else
    {
        dObj = (DRV_CAMERA_OVM7692_OBJ *)clientObj->hDriver;    
    
        SYS_INT_SourceDisable(dObj->vsyncInterruptSource);
        SYS_INT_SourceStatusClear(dObj->vsyncInterruptSource);
    }

    return returnValue;
}

// *****************************************************************************
/* Function:
    DRV_CAMERA_OVM7692_ERROR DRV_CAMERA_OVM7692_RegisterSet 
    ( 
        DRV_CAMERA_OVM7692_REGISTER_ADDRESS regIndex, 
        uint8_t regValue 
    )

  Summary:
    Sets the camera OVM7692 configuration registers

  Description:
    This routine sets the Camera OVM7692 configuration registers using SCCB
    interface. 

  Precondition:
    The DRV_CAMERA_OVM7692_Initialize routine must have been called for the 
    specified Camera OVM7692 driver instance.

    DRV_CAMERA_OVM7692_Open must have been called to obtain a valid opened 
    device handle.

    The SCCB interface also must have been initialized to configure the Camera
    OVM7692.

  Parameters:
    regIndex - Defines the configuration register addresses for OVM7692.
    regValue - Defines the register value to be set.

  Returns:
    DRV_CAMERA_OVM7692_ERROR_INVALID_HANDLE - Invalid driver Handle.
    DRV_CAMERA_OVM7692_ERROR_NONE - No error.

  Example:
    <code>

       DRV_HANDLE handle;
       uint8_t reg12 = DRV_CAMERA_OVM7692_REG12_SOFT_RESET;

        handle = DRV_CAMERA_OVM7692_Open(DRV_CAMERA_OVM7692_INDEX_0, DRV_IO_INTENT_EXCLUSIVE);
        if (DRV_HANDLE_INVALID == handle)
        {
            //error
            return;    
        }

        if ( DRV_CAMERA_OVM7692_RegisterSet( object, DRV_CAMERA_OVM7692_REG12_REG_ADDR,
                                             reg12 ) != 
                                             DRV_CAMERA_OVM7692_ERROR_NONE )
        {
            //error
            return;
        }

    </code>

  Remarks:
    This routine can be used separately or within a interface.
 */

SCCB_STATUS DRV_CAMERA_OVM7692_RegisterSet 
( 
    SYS_MODULE_OBJ object,
    DRV_CAMERA_OVM7692_REGISTER_ADDRESS regIndex, 
    uint8_t regValue 
)
{
    uint8_t frame[3] = {0, 0, 0};
    
    frame[0] = DRV_CAMERA_OVM7692_SCCB_ID;
    frame[1] = regIndex;
    frame[2] = regValue;
    
    return SCCB_Write( frame[0], frame[1], frame[2] );
}// *****************************************************************************
/* Function:
    DRV_CAMERA_OVM7692_ERROR DRV_CAMERA_OVM7692_RegisterSet 
    ( 
        DRV_CAMERA_OVM7692_REGISTER_ADDRESS regIndex, 
        uint8_t regValue 
    )

  Summary:
    Sets the camera OVM7692 configuration registers

  Description:
    This routine sets the Camera OVM7692 configuration registers using SCCB
    interface. 

  Precondition:
    The DRV_CAMERA_OVM7692_Initialize routine must have been called for the 
    specified Camera OVM7692 driver instance.

    DRV_CAMERA_OVM7692_Open must have been called to obtain a valid opened 
    device handle.

    The SCCB interface also must have been initialized to configure the Camera
    OVM7692.

  Parameters:
    regIndex - Defines the configuration register addresses for OVM7692.
    regValue - Defines the register value to be set.

  Returns:
    DRV_CAMERA_OVM7692_ERROR_INVALID_HANDLE - Invalid driver Handle.
    DRV_CAMERA_OVM7692_ERROR_NONE - No error.

  Example:
    <code>

       DRV_HANDLE handle;
       uint8_t reg12 = DRV_CAMERA_OVM7692_REG12_SOFT_RESET;

        handle = DRV_CAMERA_OVM7692_Open(DRV_CAMERA_OVM7692_INDEX_0, DRV_IO_INTENT_EXCLUSIVE);
        if (DRV_HANDLE_INVALID == handle)
        {
            //error
            return;    
        }

        if ( DRV_CAMERA_OVM7692_RegisterSet( object, DRV_CAMERA_OVM7692_REG12_REG_ADDR,
                                             reg12 ) != 
                                             DRV_CAMERA_OVM7692_ERROR_NONE )
        {
            //error
            return;
        }

    </code>

  Remarks:
    This routine can be used separately or within a interface.
 */

SCCB_STATUS DRV_CAMERA_OVM7692_RegisterGet 
( 
    SYS_MODULE_OBJ object,
    DRV_CAMERA_OVM7692_REGISTER_ADDRESS regIndex, 
    uint8_t* regValue 
)
{  
    uint8_t frame[2] = { 0, 0 };
    
    frame[0] = DRV_CAMERA_OVM7692_SCCB_ID;
    frame[1] = regIndex;
 
    return SCCB_Read( frame[0], frame[1], regValue );
}
// *****************************************************************************
/* Function:
    void _DRV_CAMERA_OVM7692_UpdateSubstate( DRV_CAMERA_OVM7692_OBJ *dObj )

  Summary:
    Update SM substate

  Description:
    This routine to update SM substate for tracking I2C configuration

  Precondition:

  Parameters:


  Returns:
    None.

  Example:
    <code>

    </code>

  Remarks:
    This routine must be used within the interface.
 */

void _DRV_CAMERA_OVM7692_UpdateSubstate( DRV_CAMERA_OVM7692_OBJ *dObj, bool wait )
{
    if( wait )
    {
        dObj->nextsubstate = dObj->substate + 1U;
        dObj->prevsubstate = dObj->substate;        
        dObj->substate = DRV_CAMERA_CONFIG_STATE_WAIT;   
    }
    else
    {
        dObj->prevsubstate = dObj->substate;
        dObj->substate = dObj->prevsubstate + 1U;
        dObj->nextsubstate = DRV_CAMERA_CONFIG_STATE_NONE;          
    }
}

// ***************************************************************************//
void DRV_CAMERA_OVM7692_PeripheralSetup( SYS_MODULE_OBJ object )
{
    DRV_CAMERA_OVM7692_OBJ *dObj = &gDrvCameraOVM7692Obj[object];
    
    if( dObj == NULL )
    {
        /* Driver object is not valid */
        SYS_DEBUG(0, "Invalid Driver Handle");
    }
    else
    {
        /* Disable interrupts */
        SYS_INT_SourceDisable(dObj->pclkInterruptSource);
        SYS_INT_SourceDisable(dObj->hsyncInterruptSource);
        SYS_INT_SourceDisable(dObj->vsyncInterruptSource);
        
        /* Clear the interrupts */
        SYS_INT_SourceStatusClear(dObj->hsyncInterruptSource);
        SYS_INT_SourceStatusClear(dObj->vsyncInterruptSource);   
        SYS_INT_SourceStatusClear(dObj->pclkInterruptSource);        
           
        /* Turn on camera power */
        SYS_PORT_PinOutputEnable( dObj->shdnPin );
        SYS_PORT_PinSet( dObj->shdnPin );        
        
        /* Clear Power Down Pin*/
        SYS_PORT_PinOutputEnable( dObj->pwdnPin );
        SYS_PORT_PinSet( dObj->pwdnPin );       
                
        /* Initialize DMA transfers  */ 
        SYS_DMA_AddressingModeSetup( dObj->dmaChannel1, SYS_DMA_SOURCE_ADDRESSING_MODE_FIXED, SYS_DMA_DESTINATION_ADDRESSING_MODE_INCREMENTED );  
        SYS_DMA_DataWidthSetup( dObj->dmaChannel1, SYS_DMA_WIDTH_8_BIT);       
        SYS_DMA_ChannelCallbackRegister( dObj->dmaChannel1, _DRV_CAMERA_OVM7692_DMAEventHandler, (uintptr_t)dObj );
        
        SYS_DMA_AddressingModeSetup( dObj->dmaChannel2, SYS_DMA_SOURCE_ADDRESSING_MODE_FIXED, SYS_DMA_DESTINATION_ADDRESSING_MODE_INCREMENTED );  
        SYS_DMA_DataWidthSetup( dObj->dmaChannel2, SYS_DMA_WIDTH_8_BIT);   
        SYS_DMA_ChannelCallbackRegister( dObj->dmaChannel2, _DRV_CAMERA_OVM7692_DMAEventHandler, (uintptr_t)dObj );   
        
        DCH0SSA = (uint32_t)KVA_TO_PA((void *)dObj->sourcePort);  
        DCH1SSA = (uint32_t)KVA_TO_PA((void *)dObj->sourcePort);        
        
        /* Enable camera */
        SYS_PORT_PinClear( dObj->pwdnPin );   
        
        dObj->state = DRV_CAMERA_STATE_CONFIGURE;
    }
}
// ***************************************************************************//
void DRV_CAMERA_OVM7692_HsyncEventHandler(SYS_MODULE_OBJ object)
{
}
// ***************************************************************************//
GFXU_ImageAsset* DRV_CAMERA_OVM7692_VsyncEventHandler(SYS_MODULE_OBJ object)
{
    GFXU_ImageAsset* gfxptr = NULL;
    
    DRV_CAMERA_OVM7692_OBJ *dObj = &gDrvCameraOVM7692Obj[object];
    
    if( dObj->inUse )
    {    
        if( dObj->frameComplete == true )
        {
           gfxptr = &dObj->frameBuffer[dObj->frameBufferIndex]; 
           dObj->lastFrameBufferIndex = dObj->frameBufferIndex;
           dObj->frameComplete = false;
           dObj->frameCount++;  
           
            if( ++dObj->frameBufferIndex >= DRV_CAMERA_FRAME_BUFFERS )
                dObj->frameBufferIndex = 0;            
        }
 
        DCH0DSA = (uint32_t)KVA_TO_PA((void *)dObj->dmaPtr[dObj->frameBufferIndex][0]);        
        DCH1DSA = (uint32_t)KVA_TO_PA((void *)dObj->dmaPtr[dObj->frameBufferIndex][1]);         
        
        DCH0INTCLR = _DCH0INT_CHBCIF_MASK;
        DCH0INTbits.CHBCIE = 1;
        DCH1INTCLR = _DCH1INT_CHBCIF_MASK;
        DCH1INTbits.CHBCIE = 0;
        DCH0CONbits.CHEN = 1;
        DCH1CONbits.CHEN = 0;
        IFS4CLR = 0x40;    
        
        if( dObj->substate == DRV_CAMERA_SUB_STATE_PAUSE )
        {
            CAMERA_PWDN_Set();
            dObj->paused = true;
            dObj->lastFrame = gfxptr;
            dObj->substate = DRV_CAMERA_SUB_STATE_IDLE;            
            gfxptr = NULL;
        }
        else if( dObj->substate == DRV_CAMERA_SUB_STATE_RESUME )
        {
            dObj->substate = DRV_CAMERA_SUB_STATE_IDLE;     
            dObj->paused = false;
            dObj->lastFrame = NULL;            
            gfxptr = NULL;            
        }
    }

    return gfxptr;
}
// ***************************************************************************//
// Function: void DRV_CAMERA_OVM7692_DMAEventHandler( SYS_DMA_TRANSFER_EVENT event, SYS_DMA_CHANNEL channel, uintptr_t contextHandle )

void _DRV_CAMERA_OVM7692_DMAEventHandler( SYS_DMA_TRANSFER_EVENT event,
                                          uintptr_t contextHandle )
{
    DRV_CAMERA_OVM7692_OBJ *dObj = NULL;
          
    if ( event == SYS_DMA_TRANSFER_COMPLETE )
    {
        dObj = (DRV_CAMERA_OVM7692_OBJ *)contextHandle;    
        #ifdef DEBUG_IP
        dprintf_colour("[BROWN]Frame acquired.[WHITE]\r\n" );  
        #endif        
        dObj->frameComplete = true;
    }
    
    return;    
}
// ***************************************************************************//
uint8_t DRV_CAMERA_OVM7692_getFrameIndex( DRV_HANDLE handle )
{
    DRV_CAMERA_OVM7692_CLIENT_OBJ * clientObj;
    DRV_CAMERA_OVM7692_OBJ * dObj;

    clientObj = (DRV_CAMERA_OVM7692_CLIENT_OBJ *) handle;
    
    if(clientObj == NULL)
    {
        /* Driver handle is not valid */
        SYS_DEBUG(0, "Invalid Driver Handle");
        return DRV_CAMERA_OVM7692_ERROR_INVALID_HANDLE;
    }
    else
    {
        dObj = (DRV_CAMERA_OVM7692_OBJ *)clientObj->hDriver;  
        return dObj->lastFrameBufferIndex;
    }
}
// ***************************************************************************//
bool DRV_CAMERA_OVM7692_isFrameComplete( DRV_HANDLE handle )
{
    bool complete = false;
    
    DRV_CAMERA_OVM7692_CLIENT_OBJ * clientObj;
    DRV_CAMERA_OVM7692_OBJ * dObj;

    clientObj = (DRV_CAMERA_OVM7692_CLIENT_OBJ *) handle;
    
    if(clientObj == NULL)
    {
        /* Driver handle is not valid */
        SYS_DEBUG(0, "Invalid Driver Handle");
        return DRV_CAMERA_OVM7692_ERROR_INVALID_HANDLE;
    }
    else
    {
        dObj = (DRV_CAMERA_OVM7692_OBJ *)clientObj->hDriver;  
        complete = dObj->frameComplete;
        dObj->frameComplete = false;
    }
    
    return complete;
}

uint32_t _DRV_CAMERA_OVM7692_isFrameComplete( SYS_MODULE_OBJ object )
{
    uint32_t index = false;
    
    DRV_CAMERA_OVM7692_OBJ *dObj = &gDrvCameraOVM7692Obj[object];
    
    if( dObj->inUse )  
    {
        if( dObj->frameComplete )
            index = ( dObj->lastFrameBufferIndex + 1);
        
        dObj->frameComplete = false;
    }
    
    return index;
}
// ***************************************************************************//
uint16_t DRV_CAMERA_OVM7692_GetCameraParameter( char* str, DRV_CAMERA_PARAMETERS param, DRV_HANDLE handle )
{
    uint32_t value = 0;
    uint16_t len = 0;
    
    DRV_CAMERA_OVM7692_CLIENT_OBJ * clientObj;
    DRV_CAMERA_OVM7692_OBJ * dObj;

    clientObj = (DRV_CAMERA_OVM7692_CLIENT_OBJ *) handle;
    
    if(clientObj == NULL)
    {
        /* Driver handle is not valid */
        SYS_DEBUG(0, "Invalid Driver Handle");
        return DRV_CAMERA_OVM7692_ERROR_INVALID_HANDLE;
    }
    else
    {
        dObj = (DRV_CAMERA_OVM7692_OBJ *)clientObj->hDriver;
        
        switch(param)
        {       
            case DRV_CAMERA_MID:
                value = ( (uint32_t)dObj->manufacturerID[1] << 8 ) + dObj->manufacturerID[0];
                len = sprintf(str, "0x%x", value );
                break;
                
            case DRV_CAMERA_PID:
                value = ( (uint32_t)dObj->productID[1] << 8 ) + dObj->productID[0]; 
                len = sprintf(str, "0x%x", value );
                break;
               
            case DRV_CAMERA_FRAME_COUNT:
                value = dObj->frameCount;
                len = sprintf(str, "%d", value );
                break;
        }
    }
 
    return len;
}
// ***************************************************************************//
void DRV_CAMERA_OVM7692_Tasks(SYS_MODULE_OBJ object)
{ 
    DRV_CAMERA_OVM7692_OBJ *dObj = &gDrvCameraOVM7692Obj[object];
    
    switch ( dObj->status )
    {
        case SYS_STATUS_UNINITIALIZED:
            break;
        
        case SYS_STATUS_READY:
            
            switch( dObj->state )   
            {                
                case  DRV_CAMERA_STATE_WAIT_FOR_OPEN:                   
                    break;                 
                
                case  DRV_CAMERA_STATE_INIT_PERIPHERALS: 
                    /* Setup the Hardware Peripherals*/
                    DRV_CAMERA_OVM7692_PeripheralSetup( object );
                    break;                                     
                    
                case  DRV_CAMERA_STATE_CONFIGURE:
                    /* Configure the OVM7692 Internal Registers */
                    DRV_CAMERA_OVM7692_Configure( object );  
                    break;     
                    
                case  DRV_CAMERA_STATE_START:
                    /* Start the Interface */
                    _DRV_CAMERA_OVM7692_Start( object );
                    break;
                    
                case  DRV_CAMERA_STATE_RUNNING: 
       
                    DRV_CAMERA_OVM7692_SubTasks( object );
                        
                    break;              

                case  DRV_CAMERA_STATE_ERROR: 
                    break;
                    
                default:
                    break;
            }
                     
            break;
            
        case SYS_STATUS_ERROR:        
            break;
            
        default:
            break;
    }
}
// ***************************************************************************//
void DRV_CAMERA_OVM7692_SubTasks(SYS_MODULE_OBJ object)
{
    DRV_CAMERA_OVM7692_OBJ *dObj = &gDrvCameraOVM7692Obj[object];    
    
    switch( dObj->substate )
    {              
        case  DRV_CAMERA_SUB_STATE_PAUSE: 

            break;       

        case  DRV_CAMERA_SUB_STATE_RESUME: 

            CAMERA_PWDN_Clear();

            break; 

       case  DRV_CAMERA_SUB_STATE_IDLE: 

            break;                             
    } 
}
// ***************************************************************************//
void DRV_CAMERA_OVM7692_Pause(SYS_MODULE_OBJ object)
{ 
    DRV_CAMERA_OVM7692_OBJ *dObj = &gDrvCameraOVM7692Obj[object]; 
    
    if( dObj->state == DRV_CAMERA_STATE_RUNNING )
    {
        if( !dObj->paused )
        {
            if( dObj->substate == DRV_CAMERA_SUB_STATE_IDLE )
            {
               dObj->substate = DRV_CAMERA_SUB_STATE_PAUSE;
            }     
        }
    } 
}
// ***************************************************************************//
void DRV_CAMERA_OVM7692_Resume(SYS_MODULE_OBJ object)
{ 
    DRV_CAMERA_OVM7692_OBJ *dObj = &gDrvCameraOVM7692Obj[object]; 
    
    if( dObj->state == DRV_CAMERA_STATE_RUNNING )
    {
        if( dObj->paused )
        {
            if( dObj->substate == DRV_CAMERA_SUB_STATE_IDLE )
            {
                dObj->substate = DRV_CAMERA_SUB_STATE_RESUME;
            }
        }
    }    
}
// ***************************************************************************//
bool DRV_CAMERA_OVM7692_InitRegisters(SYS_MODULE_OBJ object)
{
    uint16_t regindex = 0;
    uint16_t regcount = DRV_REGISTER_COUNT * 2;

    for( regindex = 0; regindex < regcount; regindex += 2 )
    {
        if( DRV_CAMERA_OVM7692_RegisterSet( object, drvRegisters[regindex], drvRegisters[regindex + 1] ) != SCCB_WRITE_COMPLETE )
        {
            return false;
        }
    }

    /* update HSTART and VSTART */
    DRV_CAMERA_OVM7692_Set_Position(object, settings_get_camera_hstart(), settings_get_camera_vstart());

    return true;
}
// ***************************************************************************//
void DRV_CAMERA_OVM7692_Configure(SYS_MODULE_OBJ object)
{ 
    DRV_CAMERA_OVM7692_OBJ *dObj = &gDrvCameraOVM7692Obj[object];
         
    switch ( (DRV_CAMERA_CONFIG_STATE)dObj->substate )
    {   
        case DRV_CAMERA_CONFIG_STATE_INIT:
            
            if( DRV_CAMERA_OVM7692_InitRegisters( object ) )
            {
                _DRV_CAMERA_OVM7692_UpdateSubstate( dObj, false );  
            }
            else
            {
                dObj->prevsubstate = dObj->substate;
                dObj->substate = DRV_CAMERA_CONFIG_STATE_ERROR;
            }
                
            break;           
        
        case DRV_CAMERA_CONFIG_STATE_GET_MID:
            
            /* Read manufacturer ID MSB & LSB */
            if( DRV_CAMERA_OVM7692_RegisterGet( object, DRV_CAMERA_MIDH_REG_ADDR, &dObj->manufacturerID[1] ) > 0 )
            {
                if( DRV_CAMERA_OVM7692_RegisterGet( object, DRV_CAMERA_MIDL_REG_ADDR, &dObj->manufacturerID[0] ) > 0 ) 
                {
                   _DRV_CAMERA_OVM7692_UpdateSubstate( dObj, false ); 
                   break;
                }
            }
            
            dObj->prevsubstate = dObj->substate;
            dObj->substate = DRV_CAMERA_CONFIG_STATE_ERROR;   
            
            break;
            
        case DRV_CAMERA_CONFIG_STATE_GET_PID:
            /* Read manufacturer ID MSB & LSB */
            
            if( DRV_CAMERA_OVM7692_RegisterGet( object, DRV_CAMERA_PIDH_REG_ADDR, &dObj->productID[1] ) > 0 )
            {
                if( DRV_CAMERA_OVM7692_RegisterGet( object, DRV_CAMERA_PIDL_REG_ADDR, &dObj->productID[0] ) > 0 ) 
                {
                   _DRV_CAMERA_OVM7692_UpdateSubstate( dObj, false ); 
                   break;
                }
            }
            
            dObj->prevsubstate = dObj->substate;
            dObj->substate = DRV_CAMERA_CONFIG_STATE_ERROR;              

            break;
            
        case DRV_CAMERA_CONFIG_STATE_READY:    
            dObj->prevsubstate = dObj->substate;
            dObj->prevstate = dObj->state;
            dObj->state = DRV_CAMERA_STATE_START;
            break;  
            
        case DRV_CAMERA_CONFIG_STATE_ERROR:
            dObj->prevsubstate = dObj->substate;    
            dObj->state = DRV_CAMERA_STATE_ERROR;
            break;
            
        case DRV_CAMERA_CONFIG_STATE_WAIT:      
            
            if( dObj->sysDelayHandle == SYS_TIME_HANDLE_INVALID )
            {
                if ( SYS_TIME_DelayMS( DRV_CAMERA_REG_SET_DELAY, &dObj->sysDelayHandle ) != SYS_TIME_SUCCESS)
                {
                    dObj->substate = DRV_CAMERA_CONFIG_STATE_ERROR;
                }
            }
            else
            {
                // Check if the delay has expired.
                if ( SYS_TIME_DelayIsComplete( dObj->sysDelayHandle ) == true )
                {
                    dObj->prevsubstate = dObj->substate;
                    dObj->substate = dObj->nextsubstate;
                    dObj->nextsubstate = DRV_CAMERA_CONFIG_STATE_NONE;
                    
                    dObj->sysDelayHandle = SYS_TIME_HANDLE_INVALID;
                }                    
            }
            
            break;             
            
        default:
            break;
    }
}

void DRV_CAMERA_OVM7692_Set_Position(SYS_MODULE_OBJ object, uint8_t hstart, uint8_t vstart)
{
    DRV_CAMERA_OVM7692_RegisterSet(object, DRV_CAMERA_OVM7692_HSTART_REG_ADDR, hstart);
    DRV_CAMERA_OVM7692_RegisterSet(object, DRV_CAMERA_OVM7692_VSTART_REG_ADDR, vstart);
}

void DRV_CAMERA_OVM7692_Get_Position(SYS_MODULE_OBJ object, uint8_t * hstart, uint8_t * vstart)
{
    DRV_CAMERA_OVM7692_RegisterGet(object, DRV_CAMERA_OVM7692_HSTART_REG_ADDR, hstart);
    DRV_CAMERA_OVM7692_RegisterGet(object, DRV_CAMERA_OVM7692_VSTART_REG_ADDR, vstart);
}

bool DRV_CAMERA_OVM7692_Is_Paused(SYS_MODULE_OBJ object)
{ 
    DRV_CAMERA_OVM7692_OBJ *dObj = &gDrvCameraOVM7692Obj[object];
         
    return dObj->paused;
}

GFXU_ImageAsset* DRV_CAMERA_OVM7692_Get_Last_Frame(SYS_MODULE_OBJ object)
{
    DRV_CAMERA_OVM7692_OBJ *dObj = &gDrvCameraOVM7692Obj[object];
        
    return dObj->lastFrame;
}


APP_DATA appData;
#define ERROR_HANDSHAKE_TOLERANCE 10
bool DRV_CAMERA_test_comms(void)
{
    uint8_t value = 0;
    uint16_t regindex = 4;
    static uint16_t error_handshake = ERROR_HANDSHAKE_TOLERANCE;
    static uint16_t error_overflow = 0;
    if(DRV_CAMERA_OVM7692_Is_Paused(sysObj.drvOVM7692) == true)
    {
        return true;
    }

    if( DRV_CAMERA_OVM7692_RegisterGet( sysObj.drvOVM7692, drvRegisters[regindex], &value ) != SCCB_WRITE_COMPLETE )
    {
        if(value != 2)
        {
            DRV_CAMERA_OVM7692_InitRegisters(sysObj.drvOVM7692);
            dputs_colour("[WHITE]ERROR: camera error stage 1[WHITE]\r\n");
            error_handshake--;
            if(error_handshake == 0)
            {
                dputs_colour("[RED]ERROR: camera error stage 2[WHITE]\r\n");
                error_overflow++;
                error_handshake = ERROR_HANDSHAKE_TOLERANCE;
                if(error_overflow == ERROR_HANDSHAKE_TOLERANCE)
                {
                    dputs_colour("[RED]ERROR: camera error[WHITE]\r\n");
                    appData.prevstate = appData.state;
                    appData.state = APP_STATE_ERROR;
                    sprintf(appData.error_string, "Camera Error\n" ); 
                    return false;
                }
            }
        }
    }
    
    return true;
}
/*******************************************************************************
 End of File
*/
