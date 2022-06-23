void PIN_MANAGER_Initialize (void);

void PIN_MANAGER_IOC(void);

void IOCAF4_ISR(void);

void IOCAF4_SetInterruptHandler(void (* InterruptHandler)(void));

extern void (*IOCAF4_InterruptHandler)(void);

void IOCAF4_DefaultInterruptHandler(void);

void IOCAF5_ISR(void);

void IOCAF5_SetInterruptHandler(void (* InterruptHandler)(void));

extern void (*IOCAF5_InterruptHandler)(void);

void IOCAF5_DefaultInterruptHandler(void);
