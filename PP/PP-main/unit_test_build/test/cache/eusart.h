#include "xc.h"
    

   void EUSART_Initialize(void);



_Bool 

    EUSART_is_tx_ready(void);



_Bool 

    EUSART_is_rx_ready(void);



_Bool 

    EUSART_is_tx_done(void);

    uint8_t EUSART_Read(void);

    void EUSART_Write(uint8_t txData);
