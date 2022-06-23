#include "xc.h"


typedef enum

{

        I2C_MESSAGE_COMPLETE,

        I2C_MESSAGE_FAIL,

        I2C_MESSAGE_PENDING,

        I2C_STUCK_START,

        I2C_MESSAGE_ADDRESS_NO_ACK,

        I2C_DATA_NO_ACK,

        I2C_LOST_STATE

    } I2C_MESSAGE_STATUS;

typedef struct

{

    uint16_t address;





    uint8_t length;

    uint8_t *pbuffer;

    } I2C_TRANSACTION_REQUEST_BLOCK;

    void I2C_Initialize(void);

    void I2C_MasterWrite(

            uint8_t *pdata,

            uint8_t length,

            uint16_t address,

            I2C_MESSAGE_STATUS *pstatus);

    void I2C_MasterRead(

            uint8_t *pdata,

            uint8_t length,

            uint16_t address,

            I2C_MESSAGE_STATUS *pstatus);

    void I2C_MasterTRBInsert(

            uint8_t count,

            I2C_TRANSACTION_REQUEST_BLOCK *ptrb_list,

            I2C_MESSAGE_STATUS *pflag);

    void I2C_MasterReadTRBBuild(

            I2C_TRANSACTION_REQUEST_BLOCK *ptrb,

            uint8_t *pdata,

            uint8_t length,

            uint16_t address);

    void I2C_MasterWriteTRBBuild(

            I2C_TRANSACTION_REQUEST_BLOCK *ptrb,

            uint8_t *pdata,

            uint8_t length,

            uint16_t address);

    

   _Bool 

        I2C_MasterQueueIsEmpty(void);

    

   _Bool 

        I2C_MasterQueueIsFull(void);



void I2C_BusCollisionISR( void );

void I2C_ISR ( void );
