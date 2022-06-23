/**
\mainpage Software Architecture Documentation
\section arch_overview_sec Architecture overview
\startuml{architecture.png} "Software Architecture Diagram" width=10cm
package "External libraries" {
component [libpic30 library\nLSC-SM-016] as LSCSM016 #Chocolate
component [stdint library\nLSC-SM-017] as LSCSM017 #Chocolate
component [stdbool library\nLSC-SM-018] as LSCSM018 #Chocolate
component [xc library\nLSC-SM-019] as LSCSM019 #Chocolate
component [string library\nLSC-SM-020] as LSCSM020 #Chocolate
component [stdio library\nLSC-SM-021] as LSCSM021 #Chocolate
component [stddef library\nLSC-SM-022] as LSCSM022 #Chocolate
}
package "Application layer" {
component [Main application module\nLSC-SM-001] as LSCSM001 #CornflowerBlue
component [Message exchange module\nLSC-SM-002] as LSCSM002 #CornflowerBlue
component [System initialisation module\nLSC-SM-010] as LSCSM010 #Orange
component [System module\nLSC-SM-013] as LSCSM013 #Orange
component [LRS tuning module\nLSC-SM-029] as LSCSM029 #CornflowerBlue
}
package "Driver layer" {
component [LSC-PDA communication module\nLSC-SM-003] as LSCSM003 #CornflowerBlue
component [GPIO module\nLSC-SM-004] as LSCSM004 #Orange
component [UART module\nLSC-SM-005] as LSCSM005 #Orange
component [Timer module\nLSC-SM-006] as LSCSM006 #Orange
component [External interrupt module\nLSC-SM-007] as LSCSM007 #Orange
component [Dynamic Momery Access module\nLSC-SM-008] as LSCSM008 #Orange
component [Comparator HAL module\nLSC-SM-009] as LSCSM009 #Orange
component [Interrupt manager module\nLSC-SM-011] as LSCSM011 #Orange
component [Reset module\nLSC-SM-012] as LSCSM012 #Orange
component [Clock module\nLSC-SM-014] as LSCSM014 #Orange
component [Configurable Logic Cell HAL module\nLSC-SM-015] as LSCSM015 #Orange
component [Debugging comms module\nLSC-SM-023] as LSCSM023 #Orange
component [Delay module\nLSC-SM-024] as LSCSM024 #Orange
component [Flash module\nLSC-SM-025] as LSCSM025 #Orange
component [SCCP module\nLSC-SM-026] as LSCSM026 #Orange
component [Bootloader module\nLSC-SM-027] as LSCSM027 #Orange
component [Encoder driver module\nLSC-SM-028] as LSCSM028 #CornflowerBlue
component [Motor driver module\nLSC-SM-030] as LSCSM030 #CornflowerBlue
}
package "Hardware" {
component [Master clock 25MHz\n] as HW001 #LimeGreen
component [Power amplifier\n] as HW002 #LimeGreen
component [H-Bridge\n] as HW003 #LimeGreen
component [Linear encoder\n] as HW004 #LimeGreen
component [PDA\n] as HW005 #LimeGreen
}
[HW001] -right- [LSCSM014]
[HW002] -right- [LSCSM009]
[HW003] -right- [LSCSM004]
[HW004] -right- [LSCSM007]
[HW004] -right- [LSCSM015]
[HW005] -right- [LSCSM005]
[HW005] -right- [LSCSM015]
[LSCSM001] -[hidden]down-> [LSCSM002]
[LSCSM002] -[hidden]down-> [LSCSM010]
[LSCSM010] -[hidden]down-> [LSCSM013]
[LSCSM013] -[hidden]down-> [LSCSM029]
[LSCSM003] -[hidden]down-> [LSCSM004]
[LSCSM004] -[hidden]down-> [LSCSM005]
[LSCSM005] -[hidden]down-> [LSCSM006]
[LSCSM006] -[hidden]down-> [LSCSM007]
[LSCSM007] -[hidden]down-> [LSCSM008]
[LSCSM008] -[hidden]down-> [LSCSM009]
[LSCSM009] -[hidden]down-> [LSCSM011]
[LSCSM011] -[hidden]down-> [LSCSM012]
[LSCSM012] -[hidden]down-> [LSCSM014]
[LSCSM014] -[hidden]down-> [LSCSM015]
[LSCSM015] -[hidden]down-> [LSCSM023]
[LSCSM023] -[hidden]down-> [LSCSM024]
[LSCSM024] -[hidden]down-> [LSCSM025]
[LSCSM025] -[hidden]down-> [LSCSM026]
[LSCSM026] -[hidden]down-> [LSCSM027]
[LSCSM027] -[hidden]down-> [LSCSM028]
[LSCSM028] -[hidden]down-> [LSCSM030]
[HW001] -[hidden]down-> [HW002]
[HW002] -[hidden]down-> [HW003]
[HW003] -[hidden]down-> [HW004]
[HW004] -[hidden]down-> [HW005]
[LSCSM016] -[hidden]down-> [LSCSM017]
[LSCSM017] -[hidden]down-> [LSCSM018]
[LSCSM018] -[hidden]down-> [LSCSM019]
[LSCSM019] -[hidden]down-> [LSCSM020]
[LSCSM020] -[hidden]down-> [LSCSM021]
[LSCSM021] -[hidden]down-> [LSCSM022]
[LSCSM001] -right-> [LSCSM023]
[LSCSM001] -right-> [LSCSM003]
[LSCSM001] -right-> [LSCSM009]
[LSCSM001] <-right-> [LSCSM028]
[LSCSM001] <-right-> [LSCSM002]
[LSCSM001] <-right-> [LSCSM029]
[LSCSM001] -right-> [LSCSM030]
[LSCSM001] -right-> [LSCSM006]
[LSCSM001] -right-> [LSCSM005]
[LSCSM001] -right-> [LSCSM024]
[LSCSM001] -right-> [LSCSM013]
[LSCSM002] -right-> [LSCSM023]
[LSCSM002] <-right-> [LSCSM003]
[LSCSM003] -right-> [LSCSM023]
[LSCSM006] -right-> [LSCSM023]
[LSCSM006] -right-> [LSCSM028]
[LSCSM006] -right-> [LSCSM002]
[LSCSM006] -right-> [LSCSM003]
[LSCSM006] -right-> [LSCSM029]
[LSCSM007] -right-> [LSCSM001]
[LSCSM008] <-right-> [LSCSM030]
[LSCSM010] -right-> [LSCSM014]
[LSCSM010] -right-> [LSCSM012]
[LSCSM013] -right-> [LSCSM015]
[LSCSM013] -right-> [LSCSM014]
[LSCSM013] -right-> [LSCSM009]
[LSCSM013] -right-> [LSCSM008]
[LSCSM013] -right-> [LSCSM007]
[LSCSM013] -right-> [LSCSM011]
[LSCSM013] -right-> [LSCSM003]
[LSCSM013] -right-> [LSCSM004]
[LSCSM013] -right-> [LSCSM026]
[LSCSM013] -right-> [LSCSM006]
[LSCSM013] -right-> [LSCSM005]
[LSCSM023] -right-> [LSCSM005]
[LSCSM023] -right-> [LSCSM011]
[LSCSM026] -right-> [LSCSM009]
[LSCSM029] -right-> [LSCSM023]
[LSCSM029] -right-> [LSCSM030]
[LSCSM029] -right-> [LSCSM008]
[LSCSM029] -right-> [LSCSM026]
[LSCSM030] -right-> [LSCSM009]
[LSCSM030] -right-> [LSCSM026]
[LSCSM030] -right-> [LSCSM023]
[LSCSM030] -right-> [LSCSM028]
\enduml
The Figure Software Architecture Diagram shows a diagram describing interconnections between the modules.
In the Figure, blocks indicated in orange correspond to SOUP modules, blocks indicated in brown correspond to SOUP module external to the main repository (and under configuration management by other means), and blue correspond to all other software modules. Directions of arrows determine inputs and outputs to/from the modules.
\section elem_descr_sec Element Descriptions and Interfaces
\subsection sec_LSC-SM-001 LSC-SM-001 - Main application module
The module consists of the following constituents:
- main.c
- main.h


Functionality: Provides main application logic.


The module provides the following interfaces:
- update_lsc_status_data(),
- GetPosition(),


The module is called by the following modules:
- LSC-SM-002 - Message exchange module,
- LSC-SM-007 - External interrupt module,
- LSC-SM-028 - Encoder driver module,
- LSC-SM-029 - LRS tuning module,

The module calls the following modules:
- LSC-SM-019 - xc library
- LSC-SM-018 - stdbool library
- LSC-SM-017 - stdint library
- LSC-SM-023 - Debugging comms module
- LSC-SM-003 - LSC-PDA communication module
- LSC-SM-009 - Comparator HAL module
- LSC-SM-028 - Encoder driver module
- LSC-SM-002 - Message exchange module
- LSC-SM-029 - LRS tuning module
- LSC-SM-030 - Motor driver module
- LSC-SM-006 - Timer module
- LSC-SM-005 - UART module
- LSC-SM-024 - Delay module
- LSC-SM-013 - System module
\subsection sec_LSC-SM-002 LSC-SM-002 - Message exchange module
The module consists of the following constituents:
- message_exchange.c
- message_exchange.h


Functionality: Provides application-level functionality related to communication with PDA PESS.


The module provides the following interfaces:
- message_exchange_millisecond_timer_interrupt(),
- process_PDAB_is_safe_to_shutdown_message(),
- process_pdab_request_reset_message(),
- process_request_define_limits_message(),
- process_request_start_scanning_message(),
- process_request_status_message(),
- process_request_stop_scanning_message(),
- process_request_version_message(),


The module is called by the following modules:
- LSC-SM-001 - Main application module,
- LSC-SM-003 - LSC-PDA communication module,
- LSC-SM-006 - Timer module,

The module calls the following modules:
- LSC-SM-020 - string library
- LSC-SM-023 - Debugging comms module
- LSC-SM-003 - LSC-PDA communication module
- LSC-SM-001 - Main application module
\subsection sec_LSC-SM-003 LSC-SM-003 - LSC-PDA communication module
The module consists of the following constituents:
- pdab_comms.c
- pdab_comms.h


Functionality: Provides driver-level functionality related to communication with PDA PESS.


The module provides the following interfaces:
- pic_communications_init(),
- transmit_timer(),
- pic_comms_task(),
- pic_comms_queue_message(),


The module is called by the following modules:
- LSC-SM-001 - Main application module,
- LSC-SM-002 - Message exchange module,
- LSC-SM-006 - Timer module,
- LSC-SM-013 - System module,

The module calls the following modules:
- LSC-SM-018 - stdbool library
- LSC-SM-022 - stddef library
- LSC-SM-017 - stdint library
- LSC-SM-020 - string library
- LSC-SM-019 - xc library
- LSC-SM-023 - Debugging comms module
- LSC-SM-002 - Message exchange module
\subsection sec_LSC-SM-004 LSC-SM-004 - GPIO module
The module consists of the following constituents:
- pin_manager.c
- pin_manager.h


Functionality: Provides GPIO peripheral functionality. This module permits the LSC software subsystem support interface with hardware - controls GPIO pins.


The module provides the following interfaces:
- PIN_MANAGER_Initialize(),


The module is called by the following modules:
- LSC-SM-013 - System module,

The module calls the following modules:
- LSC-SM-019 - xc library
\subsection sec_LSC-SM-005 LSC-SM-005 - UART module
The module consists of the following constituents:
- uart2.c
- uart2.h
- uart1.c
- uart1.h


Functionality: Provides UART peripheral functionality. This module permits the LSC software subsystem support interface with hardware - controls UART peripheral.


The module provides the following interfaces:
- UART1_TransferStatusGet(),
- UART1_Initialize(),
- UART1_Write(),


The module is called by the following modules:
- LSC-SM-001 - Main application module,
- LSC-SM-013 - System module,
- LSC-SM-023 - Debugging comms module,

The module calls the following modules:
- LSC-SM-019 - xc library
- LSC-SM-018 - stdbool library
- LSC-SM-017 - stdint library
- LSC-SM-021 - stdio library
\subsection sec_LSC-SM-006 LSC-SM-006 - Timer module
The module consists of the following constituents:
- tmr1.c
- tmr1.h


Functionality: Provides functionality related to Timer 1 peripheral.


The module provides the following interfaces:
- TMR1_Counter16BitSet(),
- TMR1_Period16BitSet(),
- TMR1_Start(),
- TMR1_Stop(),
- TMR1_Initialize(),


The module is called by the following modules:
- LSC-SM-001 - Main application module,
- LSC-SM-013 - System module,

The module calls the following modules:
- LSC-SM-019 - xc library
- LSC-SM-017 - stdint library
- LSC-SM-018 - stdbool library
- LSC-SM-023 - Debugging comms module
- LSC-SM-028 - Encoder driver module
- LSC-SM-002 - Message exchange module
- LSC-SM-003 - LSC-PDA communication module
- LSC-SM-029 - LRS tuning module
\subsection sec_LSC-SM-007 LSC-SM-007 - External interrupt module
The module consists of the following constituents:
- ext_int.c
- ext_int.h


Functionality: Provides functionality related to External Interrupt peripheral.


The module provides the following interfaces:
- EXT_INT_Initialize(),


The module is called by the following modules:
- LSC-SM-013 - System module,

The module calls the following modules:
- LSC-SM-019 - xc library
- LSC-SM-001 - Main application module
\subsection sec_LSC-SM-008 LSC-SM-008 - Dynamic Momery Access module
The module consists of the following constituents:
- dma.c
- dma.h


Functionality: Provides functionality related to Dynamic Memory Access peripheral.


The module provides the following interfaces:
- DMA_Initialize(),
- DMA_ChannelDisable(),
- DMA_ChannelEnable(),
- DMA_DestinationAddressSet(),
- DMA_SourceAddressSet(),
- DMA_TransferCountSet(),


The module is called by the following modules:
- LSC-SM-013 - System module,
- LSC-SM-029 - LRS tuning module,
- LSC-SM-030 - Motor driver module,

The module calls the following modules:
- LSC-SM-019 - xc library
- LSC-SM-018 - stdbool library
- LSC-SM-017 - stdint library
- LSC-SM-030 - Motor driver module
\subsection sec_LSC-SM-009 LSC-SM-009 - Comparator HAL module
The module consists of the following constituents:
- cmp1.c
- cmp1.h


Functionality: Provides functionality related to comparator peripheral.


The module provides the following interfaces:
- CMP1_SetDACDataHighValue(),
- CMP1_Initialize(),
- CMP1_Enable(),
- CMP1_EnableDACOutput(),
- CMP1_DisableDACOutput(),


The module is called by the following modules:
- LSC-SM-001 - Main application module,
- LSC-SM-013 - System module,
- LSC-SM-026 - SCCP module,
- LSC-SM-030 - Motor driver module,

The module calls the following modules:
- LSC-SM-019 - xc library
- LSC-SM-017 - stdint library
- LSC-SM-018 - stdbool library
\subsection sec_LSC-SM-010 LSC-SM-010 - System initialisation module
The module consists of the following constituents:
- mcc.c
- mcc.h


Functionality: Provides system initialisation functionality.

The module does not provides any interfaces.


The module is called by the following modules:
- None

The module calls the following modules:
- LSC-SM-019 - xc library
- LSC-SM-017 - stdint library
- LSC-SM-018 - stdbool library
- LSC-SM-014 - Clock module
- LSC-SM-012 - Reset module
\subsection sec_LSC-SM-011 LSC-SM-011 - Interrupt manager module
The module consists of the following constituents:
- interrupt_manager.c
- interrupt_manager.h


Functionality: Provides functionality related to interrupt management.


The module provides the following interfaces:
- INTERRUPT_GlobalEnable(),
- INTERRUPT_Initialize(),
- INTERRUPT_GlobalDisable(),


The module is called by the following modules:
- LSC-SM-013 - System module,
- LSC-SM-023 - Debugging comms module,

The module calls the following modules:
- LSC-SM-019 - xc library
\subsection sec_LSC-SM-012 LSC-SM-012 - Reset module
The module consists of the following constituents:
- reset.c
- reset.h
- reset_types.h


Functionality: Provides functionality related to software reset.


The module provides the following interfaces:
- RESET_CauseClearAll(),


The module is called by the following modules:
- LSC-SM-010 - System initialisation module,

The module calls the following modules:
- LSC-SM-018 - stdbool library
- LSC-SM-017 - stdint library
\subsection sec_LSC-SM-013 LSC-SM-013 - System module
The module consists of the following constituents:
- system.c
- system.h
- system_types.h


Functionality: Provides system initialisation functionality.


The module provides the following interfaces:
- SYSTEM_Initialize(),


The module is called by the following modules:
- LSC-SM-001 - Main application module,

The module calls the following modules:
- LSC-SM-015 - Configurable Logic Cell HAL module
- LSC-SM-014 - Clock module
- LSC-SM-009 - Comparator HAL module
- LSC-SM-008 - Dynamic Momery Access module
- LSC-SM-007 - External interrupt module
- LSC-SM-011 - Interrupt manager module
- LSC-SM-003 - LSC-PDA communication module
- LSC-SM-004 - GPIO module
- LSC-SM-026 - SCCP module
- LSC-SM-006 - Timer module
- LSC-SM-005 - UART module
\subsection sec_LSC-SM-014 LSC-SM-014 - Clock module
The module consists of the following constituents:
- clock.c
- clock.h


Functionality: Provides functionality related to system clock.


The module provides the following interfaces:
- CLOCK_Initialize(),


The module is called by the following modules:
- LSC-SM-010 - System initialisation module,
- LSC-SM-013 - System module,

The module calls the following modules:
- LSC-SM-017 - stdint library
\subsection sec_LSC-SM-015 LSC-SM-015 - Configurable Logic Cell HAL module
The module consists of the following constituents:
- clc1.c
- clc1.h
- clc2.c
- clc2.h
- clc3.c
- clc3.h
- clc4.c
- clc4.h


Functionality: Provides functionality related to Configurable Logic Cell peripheral.


The module provides the following interfaces:
- CLC1_Initialize(),
- CLC2_Initialize(),
- CLC3_Initialize(),
- CLC4_Initialize(),


The module is called by the following modules:
- LSC-SM-013 - System module,

The module calls the following modules:
- LSC-SM-019 - xc library
- LSC-SM-017 - stdint library
- LSC-SM-018 - stdbool library
\subsection sec_LSC-SM-016 LSC-SM-016 - libpic30 library
The module consists of the following constituents:
- libpic30.h


Functionality: Generic utility functions for PIC30.

The module does not provides any interfaces.


The module is called by the following modules:
- LSC-SM-024 - Delay module,
- LSC-SM-025 - Flash module,

The module calls the following modules:
- None
\subsection sec_LSC-SM-017 LSC-SM-017 - stdint library
The module consists of the following constituents:
- stdint.h


Functionality: Standard integer types library.

The module does not provides any interfaces.


The module is called by the following modules:
- LSC-SM-001 - Main application module,
- LSC-SM-003 - LSC-PDA communication module,
- LSC-SM-005 - UART module,
- LSC-SM-006 - Timer module,
- LSC-SM-008 - Dynamic Momery Access module,
- LSC-SM-009 - Comparator HAL module,
- LSC-SM-010 - System initialisation module,
- LSC-SM-012 - Reset module,
- LSC-SM-014 - Clock module,
- LSC-SM-015 - Configurable Logic Cell HAL module,
- LSC-SM-023 - Debugging comms module,
- LSC-SM-024 - Delay module,
- LSC-SM-025 - Flash module,
- LSC-SM-026 - SCCP module,

The module calls the following modules:
- None
\subsection sec_LSC-SM-018 LSC-SM-018 - stdbool library
The module consists of the following constituents:
- stdbool.h


Functionality: Standard boolean types library.

The module does not provides any interfaces.


The module is called by the following modules:
- LSC-SM-001 - Main application module,
- LSC-SM-003 - LSC-PDA communication module,
- LSC-SM-005 - UART module,
- LSC-SM-006 - Timer module,
- LSC-SM-008 - Dynamic Momery Access module,
- LSC-SM-009 - Comparator HAL module,
- LSC-SM-010 - System initialisation module,
- LSC-SM-012 - Reset module,
- LSC-SM-015 - Configurable Logic Cell HAL module,
- LSC-SM-023 - Debugging comms module,
- LSC-SM-025 - Flash module,
- LSC-SM-026 - SCCP module,
- LSC-SM-028 - Encoder driver module,

The module calls the following modules:
- None
\subsection sec_LSC-SM-019 LSC-SM-019 - xc library
The module consists of the following constituents:
- xc.h


Functionality: Library providing support for the specific PESS device.

The module does not provides any interfaces.


The module is called by the following modules:
- LSC-SM-001 - Main application module,
- LSC-SM-003 - LSC-PDA communication module,
- LSC-SM-004 - GPIO module,
- LSC-SM-005 - UART module,
- LSC-SM-006 - Timer module,
- LSC-SM-007 - External interrupt module,
- LSC-SM-008 - Dynamic Momery Access module,
- LSC-SM-009 - Comparator HAL module,
- LSC-SM-010 - System initialisation module,
- LSC-SM-011 - Interrupt manager module,
- LSC-SM-015 - Configurable Logic Cell HAL module,
- LSC-SM-025 - Flash module,
- LSC-SM-026 - SCCP module,
- LSC-SM-028 - Encoder driver module,
- LSC-SM-029 - LRS tuning module,
- LSC-SM-030 - Motor driver module,

The module calls the following modules:
- None
\subsection sec_LSC-SM-020 LSC-SM-020 - string library
The module consists of the following constituents:
- string.h


Functionality: Library providing string support functions.

The module does not provides any interfaces.


The module is called by the following modules:
- LSC-SM-002 - Message exchange module,
- LSC-SM-003 - LSC-PDA communication module,
- LSC-SM-023 - Debugging comms module,
- LSC-SM-025 - Flash module,

The module calls the following modules:
- None
\subsection sec_LSC-SM-021 LSC-SM-021 - stdio library
The module consists of the following constituents:
- stdio.h


Functionality: Library providing standard I/O support functions.

The module does not provides any interfaces.


The module is called by the following modules:
- LSC-SM-005 - UART module,

The module calls the following modules:
- None
\subsection sec_LSC-SM-022 LSC-SM-022 - stddef library
The module consists of the following constituents:
- stddef.h


Functionality: Library providing standard definitions.

The module does not provides any interfaces.


The module is called by the following modules:
- LSC-SM-003 - LSC-PDA communication module,
- LSC-SM-023 - Debugging comms module,

The module calls the following modules:
- None
\subsection sec_LSC-SM-023 LSC-SM-023 - Debugging comms module
The module consists of the following constituents:
- debug.c
- debug.h


Functionality: Provides functionality related to debugging communication.


The module provides the following interfaces:
- dprintf(),
- dprintf_colour(),
- dputs_colour(),
- debug_millisecond_timer_interrupt(),
- debug_initialise(),
- initialisation_debug(),
- dputs(),
- debug_output_pulse(),


The module is called by the following modules:
- LSC-SM-001 - Main application module,
- LSC-SM-002 - Message exchange module,
- LSC-SM-003 - LSC-PDA communication module,
- LSC-SM-006 - Timer module,
- LSC-SM-029 - LRS tuning module,
- LSC-SM-030 - Motor driver module,

The module calls the following modules:
- LSC-SM-020 - string library
- LSC-SM-017 - stdint library
- LSC-SM-018 - stdbool library
- LSC-SM-022 - stddef library
- LSC-SM-005 - UART module
- LSC-SM-011 - Interrupt manager module
\subsection sec_LSC-SM-024 LSC-SM-024 - Delay module
The module consists of the following constituents:
- delay.c
- delay.h


Functionality: Provides functionality related to delays.


The module provides the following interfaces:
- DELAY_microseconds(),


The module is called by the following modules:
- LSC-SM-001 - Main application module,

The module calls the following modules:
- LSC-SM-016 - libpic30 library
- LSC-SM-017 - stdint library
\subsection sec_LSC-SM-025 LSC-SM-025 - Flash module
The module consists of the following constituents:
- NVM_Driver.c
- NVM_Driver.h
- flash.h


Functionality: Provides functionality related to writing to flash programming.

The module does not provides any interfaces.


The module is called by the following modules:
- None

The module calls the following modules:
- LSC-SM-017 - stdint library
- LSC-SM-018 - stdbool library
- LSC-SM-019 - xc library
- LSC-SM-016 - libpic30 library
- LSC-SM-020 - string library
\subsection sec_LSC-SM-026 LSC-SM-026 - SCCP module
The module consists of the following constituents:
- sccp2_tmr.c
- sccp2_tmr.h
- sccp7_tmr.c
- sccp7_tmr.h


Functionality: Provides functionality related to Single Capture Compare and PWM module.


The module provides the following interfaces:
- SCCP2_TMR_Initialize(),
- SCCP7_TMR_Initialize(),
- SCCP7_TMR_Counter16BitPrimarySet(),
- SCCP7_TMR_Period16BitSecondarySet(),
- SCCP7_TMR_Start(),
- SCCP7_TMR_Stop(),


The module is called by the following modules:
- LSC-SM-013 - System module,
- LSC-SM-029 - LRS tuning module,
- LSC-SM-030 - Motor driver module,

The module calls the following modules:
- LSC-SM-019 - xc library
- LSC-SM-017 - stdint library
- LSC-SM-018 - stdbool library
- LSC-SM-009 - Comparator HAL module
\subsection sec_LSC-SM-027 LSC-SM-027 - Bootloader module
The module consists of the following constituents:
- boot_config.h


Functionality: Provides functionality related to bootloader.

The module does not provides any interfaces.


The module is called by the following modules:
- None

The module calls the following modules:
- None
\subsection sec_LSC-SM-028 LSC-SM-028 - Encoder driver module
The module consists of the following constituents:
- encoder_drv.c
- encoder_drv.h


Functionality: Provides driver-level functionality related to encoder.


The module provides the following interfaces:
- encoder_interrupt(),
- enc_move_wdt_check_clear(),
- enc_move_wdt_start(),
- enc_move_wdt_stop(),


The module is called by the following modules:
- LSC-SM-001 - Main application module,
- LSC-SM-006 - Timer module,
- LSC-SM-030 - Motor driver module,

The module calls the following modules:
- LSC-SM-019 - xc library
- LSC-SM-018 - stdbool library
- LSC-SM-001 - Main application module
\subsection sec_LSC-SM-029 LSC-SM-029 - LRS tuning module
The module consists of the following constituents:
- LRS_tuning.c
- LRS_tuning.h


Functionality: Provides functionality related to LRS tuning.


The module provides the following interfaces:
- Tuning_tick(),
- DefineLimits_task(),


The module is called by the following modules:
- LSC-SM-001 - Main application module,
- LSC-SM-006 - Timer module,

The module calls the following modules:
- LSC-SM-019 - xc library
- LSC-SM-023 - Debugging comms module
- LSC-SM-030 - Motor driver module
- LSC-SM-001 - Main application module
- LSC-SM-008 - Dynamic Momery Access module
- LSC-SM-026 - SCCP module
\subsection sec_LSC-SM-030 LSC-SM-030 - Motor driver module
The module consists of the following constituents:
- motor_drv.c
- motor_drv.h


Functionality: Provides driver-level functionality related to driving LRS coil.


The module provides the following interfaces:
- StartMotion(),
- StopMotion(),
- GenerateDACProfile(),
- StartDACOutput(),


The module is called by the following modules:
- LSC-SM-001 - Main application module,
- LSC-SM-008 - Dynamic Momery Access module,
- LSC-SM-029 - LRS tuning module,

The module calls the following modules:
- LSC-SM-019 - xc library
- LSC-SM-009 - Comparator HAL module
- LSC-SM-008 - Dynamic Momery Access module
- LSC-SM-026 - SCCP module
- LSC-SM-023 - Debugging comms module
- LSC-SM-028 - Encoder driver module
\section trace_mat_sec Architecture and software requirements
The following table shows how the software requirements map onto the software architecture, and therefore how the architecture implements these requirements.
<table>
<caption id='multi_row'>Requirements traceability matrix</caption>
<tr><th>Software module <th>Requirement ID
<tr><td>LSC-SM-001 - Main application module<td>
<tr><td>LSC-SM-002 - Message exchange module<td>
<tr><td>LSC-SM-003 - LSC-PDA communication module<td>
<tr><td>LSC-SM-004 - GPIO module<td>
<tr><td>LSC-SM-005 - UART module<td>
<tr><td>LSC-SM-006 - Timer module<td>
<tr><td>LSC-SM-007 - External interrupt module<td>
<tr><td>LSC-SM-008 - Dynamic Momery Access module<td>
<tr><td>LSC-SM-009 - Comparator HAL module<td>
<tr><td>LSC-SM-010 - System initialisation module<td>
<tr><td>LSC-SM-011 - Interrupt manager module<td>
<tr><td>LSC-SM-012 - Reset module<td>
<tr><td>LSC-SM-013 - System module<td>
<tr><td>LSC-SM-014 - Clock module<td>
<tr><td>LSC-SM-015 - Configurable Logic Cell HAL module<td>
<tr><td>LSC-SM-016 - libpic30 library<td>
<tr><td>LSC-SM-017 - stdint library<td>
<tr><td>LSC-SM-018 - stdbool library<td>
<tr><td>LSC-SM-019 - xc library<td>
<tr><td>LSC-SM-020 - string library<td>
<tr><td>LSC-SM-021 - stdio library<td>
<tr><td>LSC-SM-022 - stddef library<td>
<tr><td>LSC-SM-023 - Debugging comms module<td>
<tr><td>LSC-SM-024 - Delay module<td>
<tr><td>LSC-SM-025 - Flash module<td>
<tr><td>LSC-SM-026 - SCCP module<td>
<tr><td>LSC-SM-027 - Bootloader module<td>
<tr><td>LSC-SM-028 - Encoder driver module<td>
<tr><td>LSC-SM-029 - LRS tuning module<td>
<tr><td>LSC-SM-030 - Motor driver module<td>
</table>
*/
