/**
\mainpage Software Architecture Documentation
\section arch_overview_sec Architecture overview
\startuml{architecture.png} "Software Architecture Diagram" width=10cm
package "External libraries" {
component [p32mz1024efh100 library\nPDA-CI-031] as PDACI031 #Chocolate
component [stdint library\nPDA-CI-032] as PDACI032 #Chocolate
component [stdbool library\nPDA-CI-033] as PDACI033 #Chocolate
component [xc library\nPDA-CI-034] as PDACI034 #Chocolate
component [string library\nPDA-CI-035] as PDACI035 #Chocolate
component [limits library\nPDA-CI-036] as PDACI036 #Chocolate
component [stddef library\nPDA-CI-037] as PDACI037 #Chocolate
component [attribs library\nPDA-CI-038] as PDACI038 #Chocolate
component [p32xxxx library\nPDA-CI-039] as PDACI039 #Chocolate
component [types library\nPDA-CI-040] as PDACI040 #Chocolate
component [math library\nPDA-CI-041] as PDACI041 #Chocolate
component [float library\nPDA-CI-042] as PDACI042 #Chocolate
component [stdlib library\nPDA-CI-043] as PDACI043 #Chocolate
component [stdarg library\nPDA-CI-044] as PDACI044 #Chocolate
component [stdio library\nPDA-CI-045] as PDACI045 #Chocolate
component [cp0defs library\nPDA-CI-046] as PDACI046 #Chocolate
component [kmem library\nPDA-CI-047] as PDACI047 #Chocolate
component [assert library\nPDA-CI-048] as PDACI048 #Chocolate
}
package "Application layer" {
component [PDA-LSC state machine module\nPDA-CI-007] as PDACI007 #Orange
component [Main application module\nPDA-CI-010] as PDACI010 #CornflowerBlue
component [Maths module\nPDA-CI-011] as PDACI011 #CornflowerBlue
component [Message exchange module\nPDA-CI-012] as PDACI012 #CornflowerBlue
component [NPDA module\nPDA-CI-013] as PDACI013 #CornflowerBlue
component [Scanning logic module\nPDA-CI-014] as PDACI014 #CornflowerBlue
component [USB module\nPDA-CI-015] as PDACI015 #CornflowerBlue
component [System initialisation module\nPDA-CI-020] as PDACI020 #Orange
}
package "Driver layer" {
component [Debugging communication module\nPDA-CI-001] as PDACI001 #Orange
component [Digital to Analog Converter module\nPDA-CI-002] as PDACI002 #CornflowerBlue
component [Digital Potentiometer module\nPDA-CI-003] as PDACI003 #CornflowerBlue
component [ADC LTC2203 module\nPDA-CI-004] as PDACI004 #CornflowerBlue
component [I2C module\nPDA-CI-005] as PDACI005 #CornflowerBlue
component [Laser driver module\nPDA-CI-006] as PDACI006 #CornflowerBlue
component [EEPROM module\nPDA-CI-008] as PDACI008 #CornflowerBlue
component [PDA-LSC communication module\nPDA-CI-009] as PDACI009 #CornflowerBlue
component [PDA-PI communication module\nPDA-CI-016] as PDACI016 #CornflowerBlue
component [Scanning module\nPDA-CI-017] as PDACI017 #CornflowerBlue
component [USB module\nPDA-CI-018] as PDACI018 #Orange
component [System module\nPDA-CI-019] as PDACI019 #Orange
component [Exceptions module\nPDA-CI-021] as PDACI021 #Orange
component [ADC module\nPDA-CI-022] as PDACI022 #Orange
component [Clock module\nPDA-CI-023] as PDACI023 #Orange
component [Comparator module\nPDA-CI-024] as PDACI024 #Orange
component [DMA module\nPDA-CI-025] as PDACI025 #Orange
component [Interrupt manager module\nPDA-CI-026] as PDACI026 #Orange
component [GPIO module\nPDA-CI-027] as PDACI027 #Orange
component [Parallel port module\nPDA-CI-028] as PDACI028 #Orange
component [Timer module\nPDA-CI-029] as PDACI029 #Orange
component [UART module\nPDA-CI-030] as PDACI030 #Orange
}
package "Hardware" {
component [Master clock 25MHz\n] as HW001 #LimeGreen
component [ADC LTC2203\n] as HW002 #LimeGreen
component [DAC\n] as HW003 #LimeGreen
component [PGA & Filter\n] as HW004 #LimeGreen
component [Differential Amplifier\n] as HW005 #LimeGreen
component [Laser Driver\n] as HW006 #LimeGreen
component [PI\n] as HW007 #LimeGreen
component [LSC\n] as HW008 #LimeGreen
component [USB\n] as HW009 #LimeGreen
}
[HW001] -right- [PDACI023]
[HW002] -right- [PDACI028]
[HW003] -right- [PDACI005]
[HW004] -right- [PDACI005]
[HW005] -right- [PDACI027]
[HW006] -right- [PDACI027]
[HW007] -right- [PDACI030]
[HW008] -right- [PDACI030]
[HW008] -right- [PDACI027]
[HW009] -right- [PDACI018]
[PDACI007] -[hidden]down-> [PDACI010]
[PDACI010] -[hidden]down-> [PDACI011]
[PDACI011] -[hidden]down-> [PDACI012]
[PDACI012] -[hidden]down-> [PDACI013]
[PDACI013] -[hidden]down-> [PDACI014]
[PDACI014] -[hidden]down-> [PDACI015]
[PDACI015] -[hidden]down-> [PDACI020]
[PDACI001] -[hidden]down-> [PDACI002]
[PDACI002] -[hidden]down-> [PDACI003]
[PDACI003] -[hidden]down-> [PDACI004]
[PDACI004] -[hidden]down-> [PDACI005]
[PDACI005] -[hidden]down-> [PDACI006]
[PDACI006] -[hidden]down-> [PDACI008]
[PDACI008] -[hidden]down-> [PDACI009]
[PDACI009] -[hidden]down-> [PDACI016]
[PDACI016] -[hidden]down-> [PDACI017]
[PDACI017] -[hidden]down-> [PDACI018]
[PDACI018] -[hidden]down-> [PDACI019]
[PDACI019] -[hidden]down-> [PDACI021]
[PDACI021] -[hidden]down-> [PDACI022]
[PDACI022] -[hidden]down-> [PDACI023]
[PDACI023] -[hidden]down-> [PDACI024]
[PDACI024] -[hidden]down-> [PDACI025]
[PDACI025] -[hidden]down-> [PDACI026]
[PDACI026] -[hidden]down-> [PDACI027]
[PDACI027] -[hidden]down-> [PDACI028]
[PDACI028] -[hidden]down-> [PDACI029]
[PDACI029] -[hidden]down-> [PDACI030]
[HW001] -[hidden]down-> [HW002]
[HW002] -[hidden]down-> [HW003]
[HW003] -[hidden]down-> [HW004]
[HW004] -[hidden]down-> [HW005]
[HW005] -[hidden]down-> [HW006]
[HW006] -[hidden]down-> [HW007]
[HW007] -[hidden]down-> [HW008]
[HW008] -[hidden]down-> [HW009]
[PDACI031] -[hidden]down-> [PDACI032]
[PDACI032] -[hidden]down-> [PDACI033]
[PDACI033] -[hidden]down-> [PDACI034]
[PDACI034] -[hidden]down-> [PDACI035]
[PDACI035] -[hidden]down-> [PDACI036]
[PDACI036] -[hidden]down-> [PDACI037]
[PDACI037] -[hidden]down-> [PDACI038]
[PDACI038] -[hidden]down-> [PDACI039]
[PDACI039] -[hidden]down-> [PDACI040]
[PDACI040] -[hidden]down-> [PDACI041]
[PDACI041] -[hidden]down-> [PDACI042]
[PDACI042] -[hidden]down-> [PDACI043]
[PDACI043] -[hidden]down-> [PDACI044]
[PDACI044] -[hidden]down-> [PDACI045]
[PDACI045] -[hidden]down-> [PDACI046]
[PDACI046] -[hidden]down-> [PDACI047]
[PDACI047] -[hidden]down-> [PDACI048]
[PDACI001] -right-> [PDACI019]
[PDACI001] <-right-> [PDACI016]
[PDACI001] <-right-> [PDACI007]
[PDACI002] -right-> [PDACI001]
[PDACI002] -right-> [PDACI005]
[PDACI003] -right-> [PDACI001]
[PDACI003] -right-> [PDACI005]
[PDACI004] -right-> [PDACI001]
[PDACI004] -right-> [PDACI019]
[PDACI004] -right-> [PDACI025]
[PDACI004] -right-> [PDACI002]
[PDACI004] -right-> [PDACI006]
[PDACI006] -right-> [PDACI001]
[PDACI006] <-right-> [PDACI014]
[PDACI006] -right-> [PDACI019]
[PDACI006] <-right-> [PDACI010]
[PDACI006] -right-> [PDACI016]
[PDACI007] <-right-> [PDACI012]
[PDACI007] -right-> [PDACI026]
[PDACI007] -right-> [PDACI019]
[PDACI008] -right-> [PDACI001]
[PDACI008] <-right-> [PDACI010]
[PDACI008] -right-> [PDACI015]
[PDACI009] <-right-> [PDACI016]
[PDACI009] -right-> [PDACI001]
[PDACI009] <-right-> [PDACI012]
[PDACI009] -right-> [PDACI008]
[PDACI010] -right-> [PDACI022]
[PDACI010] -right-> [PDACI023]
[PDACI010] -right-> [PDACI024]
[PDACI010] -right-> [PDACI001]
[PDACI010] -right-> [PDACI025]
[PDACI010] -right-> [PDACI005]
[PDACI010] -right-> [PDACI018]
[PDACI010] -right-> [PDACI009]
[PDACI010] -right-> [PDACI026]
[PDACI010] -right-> [PDACI027]
[PDACI010] <-right-> [PDACI016]
[PDACI010] -right-> [PDACI028]
[PDACI010] <-right-> [PDACI019]
[PDACI010] -right-> [PDACI029]
[PDACI010] <-right-> [PDACI020]
[PDACI010] -right-> [PDACI007]
[PDACI010] -right-> [PDACI002]
[PDACI010] <-right-> [PDACI014]
[PDACI010] <-right-> [PDACI015]
[PDACI010] -right-> [PDACI003]
[PDACI010] -right-> [PDACI004]
[PDACI012] -right-> [PDACI001]
[PDACI012] <-right-> [PDACI016]
[PDACI014] -right-> [PDACI001]
[PDACI014] -right-> [PDACI026]
[PDACI014] -right-> [PDACI019]
[PDACI014] -right-> [PDACI029]
[PDACI014] -right-> [PDACI025]
[PDACI014] -right-> [PDACI024]
[PDACI014] -right-> [PDACI004]
[PDACI014] -right-> [PDACI007]
[PDACI014] -right-> [PDACI002]
[PDACI014] -right-> [PDACI003]
[PDACI014] -right-> [PDACI015]
[PDACI014] -right-> [PDACI017]
[PDACI014] -right-> [PDACI013]
[PDACI014] -right-> [PDACI016]
[PDACI014] -right-> [PDACI027]
[PDACI015] -right-> [PDACI018]
[PDACI015] -right-> [PDACI001]
[PDACI016] -right-> [PDACI008]
[PDACI017] -right-> [PDACI001]
[PDACI019] -right-> [PDACI025]
[PDACI019] -right-> [PDACI026]
[PDACI019] -right-> [PDACI027]
[PDACI019] -right-> [PDACI018]
[PDACI020] -right-> [PDACI022]
[PDACI020] -right-> [PDACI023]
[PDACI020] -right-> [PDACI024]
[PDACI020] -right-> [PDACI001]
[PDACI020] -right-> [PDACI025]
[PDACI020] -right-> [PDACI005]
[PDACI020] -right-> [PDACI018]
[PDACI020] -right-> [PDACI009]
[PDACI020] -right-> [PDACI026]
[PDACI020] -right-> [PDACI027]
[PDACI020] -right-> [PDACI016]
[PDACI020] -right-> [PDACI028]
[PDACI020] -right-> [PDACI019]
[PDACI020] -right-> [PDACI029]
[PDACI021] -right-> [PDACI001]
[PDACI026] -right-> [PDACI001]
[PDACI026] -right-> [PDACI018]
[PDACI026] -right-> [PDACI009]
[PDACI026] -right-> [PDACI016]
[PDACI026] -right-> [PDACI029]
\enduml
The Figure Software Architecture Diagram shows a diagram describing interconnections between the modules.
In the Figure, blocks indicated in orange correspond to SOUP modules, blocks indicated in brown correspond to SOUP module external to the main repository (and under configuration management by other means), and blue correspond to all other software modules. Directions of arrows determine inputs and outputs to/from the modules.
\section elem_descr_sec Element Descriptions and Interfaces
\subsection sec_PDA-CI-001 PDA-CI-001 - Debugging communication module
The module consists of the following constituents:
- debug.c
- debug.h


Functionality: Provides functionality related to debugging communication.


The module provides the following interfaces:
- dputs_colour(),
- dprintf_colour(),
- log_elapsed_time(),
- logging_start_timer(),
- dputs(),
- dprintf(),
- buffer_empty(),
- debug_initialise(),
- debug_millisecond_timer_interrupt(),
- debug_busy(),
- byte_buffer_add(),


The module is called by the following modules:
- PDA-CI-002 - Digital to Analog Converter module,
- PDA-CI-003 - Digital Potentiometer module,
- PDA-CI-004 - ADC LTC2203 module,
- PDA-CI-006 - Laser driver module,
- PDA-CI-007 - PDA-LSC state machine module,
- PDA-CI-008 - EEPROM module,
- PDA-CI-009 - PDA-LSC communication module,
- PDA-CI-010 - Main application module,
- PDA-CI-012 - Message exchange module,
- PDA-CI-014 - Scanning logic module,
- PDA-CI-015 - USB module,
- PDA-CI-016 - PDA-PI communication module,
- PDA-CI-017 - Scanning module,
- PDA-CI-020 - System initialisation module,
- PDA-CI-021 - Exceptions module,
- PDA-CI-026 - Interrupt manager module,

The module calls the following modules:
- PDA-CI-044 - stdarg library
- PDA-CI-035 - string library
- PDA-CI-032 - stdint library
- PDA-CI-033 - stdbool library
- PDA-CI-037 - stddef library
- PDA-CI-043 - stdlib library
- PDA-CI-019 - System module
- PDA-CI-016 - PDA-PI communication module
- PDA-CI-007 - PDA-LSC state machine module
\subsection sec_PDA-CI-002 PDA-CI-002 - Digital to Analog Converter module
The module consists of the following constituents:
- drv_dac_ad5667r.c
- drv_dac_ad5667r.h


Functionality: Driver-level module providing functionality related to the Digital to Analog Converter AD5667.


The module provides the following interfaces:
- drv_dac_set_ldac(),
- drv_dac_set_power_mode(),
- drv_dac_set_reference(),
- drv_dac_set_value(),
- drv_dac_get_value(),
- drv_dac_clear_error(),
- drv_dac_get_last_error(),
- drv_dac_ad5667r_controller_task(),
- drv_dac_busy(),


The module is called by the following modules:
- PDA-CI-004 - ADC LTC2203 module,
- PDA-CI-010 - Main application module,
- PDA-CI-014 - Scanning logic module,

The module calls the following modules:
- PDA-CI-001 - Debugging communication module
- PDA-CI-005 - I2C module
\subsection sec_PDA-CI-003 PDA-CI-003 - Digital Potentiometer module
The module consists of the following constituents:
- drv_dpot_ad5247.c
- drv_dpot_ad5247.h


Functionality: Driver-level module porividing functionality related to the Digital Potentiometer AD5247.


The module provides the following interfaces:
- drv_dpot_ad5247_controller_task(),
- drv_dpot_busy(),
- drv_dpot_idling(),
- drv_dpot_set_resistance(),
- drv_dpot_get_resistance(),


The module is called by the following modules:
- PDA-CI-010 - Main application module,
- PDA-CI-014 - Scanning logic module,

The module calls the following modules:
- PDA-CI-001 - Debugging communication module
- PDA-CI-005 - I2C module
\subsection sec_PDA-CI-004 PDA-CI-004 - ADC LTC2203 module
The module consists of the following constituents:
- drv_ext_adc.c
- drv_ext_adc.h


Functionality: Driver-level module providing functionality related to the Analogue to Digital Converter. Responsible for zero-offset operations


The module provides the following interfaces:
- drv_ext_adc_tasks(),
- drv_ext_adc_set_channel(),
- calculate_digipot_setting(),
- drv_ext_adc_busy(),
- drv_ext_adc_zero(),
- drv_ext_adc_zero_busy(),
- drv_ext_adc_get_offset(),
- drv_ext_adc_get_value(),
- drv_ext_adc_start(),
- drv_ext_adc_stop(),
- drv_ext_adc_get_zero(),
- drv_ext_adc_get_buffer(),


The module is called by the following modules:
- PDA-CI-010 - Main application module,
- PDA-CI-014 - Scanning logic module,

The module calls the following modules:
- PDA-CI-001 - Debugging communication module
- PDA-CI-019 - System module
- PDA-CI-025 - DMA module
- PDA-CI-002 - Digital to Analog Converter module
- PDA-CI-006 - Laser driver module
\subsection sec_PDA-CI-005 PDA-CI-005 - I2C module
The module consists of the following constituents:
- drv_i2c4.c
- drv_i2c4.h


Functionality: Provides driver-level functionality related to I2C communication.


The module provides the following interfaces:
- DRV_I2C4_Write_Bytes(),
- DRV_I2C4_Read_Single_Byte(),
- DRV_I2C4_Write_Single_Byte(),
- DRV_I2C4_Initialize(),


The module is called by the following modules:
- PDA-CI-002 - Digital to Analog Converter module,
- PDA-CI-003 - Digital Potentiometer module,
- PDA-CI-010 - Main application module,
- PDA-CI-020 - System initialisation module,

The module calls the following modules:
- PDA-CI-032 - stdint library
- PDA-CI-033 - stdbool library
- PDA-CI-037 - stddef library
- PDA-CI-043 - stdlib library
\subsection sec_PDA-CI-006 PDA-CI-006 - Laser driver module
The module consists of the following constituents:
- drv_laser.c
- drv_laser.h


Functionality: Provides driver-level functionality related to turning the laser on and off.


The module provides the following interfaces:
- drv_laser_off(),
- drv_laser_on(),
- drv_laser_timer(),
- drv_laser_get_error(),
- drv_laser_init(),


The module is called by the following modules:
- PDA-CI-004 - ADC LTC2203 module,
- PDA-CI-010 - Main application module,
- PDA-CI-014 - Scanning logic module,

The module calls the following modules:
- PDA-CI-001 - Debugging communication module
- PDA-CI-014 - Scanning logic module
- PDA-CI-019 - System module
- PDA-CI-010 - Main application module
- PDA-CI-016 - PDA-PI communication module
\subsection sec_PDA-CI-007 PDA-CI-007 - PDA-LSC state machine module
The module consists of the following constituents:
- drv_lsc.c
- drv_lsc.h


Functionality: Provides state machine for the communication with the LSC PESS.


The module provides the following interfaces:
- drv_lsc_define_limits(),
- drv_lsc_start_scanning(),
- drv_lsc_stop_scanning(),
- drv_lsc_millisecond_tick(),
- drv_lsc_get_error(),
- drv_lsc_is_initialised(),
- drv_lsc_controller_task(),
- drv_lsc_call_get_status(),
- drv_lsc_get_last_status(),
- drv_lsc_is_busy(),
- drv_lsc_is_shutdown_safe(),
- read_lsc_status(),


The module is called by the following modules:
- PDA-CI-001 - Debugging communication module,
- PDA-CI-010 - Main application module,
- PDA-CI-012 - Message exchange module,
- PDA-CI-014 - Scanning logic module,

The module calls the following modules:
- PDA-CI-001 - Debugging communication module
- PDA-CI-012 - Message exchange module
- PDA-CI-026 - Interrupt manager module
- PDA-CI-019 - System module
\subsection sec_PDA-CI-008 PDA-CI-008 - EEPROM module
The module consists of the following constituents:
- drv_N95256.c
- drv_N95256.h


Functionality: Provides driver-level functionality related to EEPROM N95256.


The module provides the following interfaces:
- checksum(),
- EEPROM_save_settings(),
- SPI_eeprom_init(),
- EEPROM_read_to_USB(),
- EEPROM_save_from_USB(),


The module is called by the following modules:
- PDA-CI-009 - PDA-LSC communication module,
- PDA-CI-010 - Main application module,
- PDA-CI-016 - PDA-PI communication module,

The module calls the following modules:
- PDA-CI-032 - stdint library
- PDA-CI-033 - stdbool library
- PDA-CI-001 - Debugging communication module
- PDA-CI-010 - Main application module
- PDA-CI-015 - USB module
\subsection sec_PDA-CI-009 PDA-CI-009 - PDA-LSC communication module
The module consists of the following constituents:
- dspic_comms.c
- dspic_comms.h


Functionality: Provides driver-level functionality related to the communication with the LSC PESS.


The module provides the following interfaces:
- dspic_pic_communications_init(),
- dspic_transmit_timer(),
- dspic_pic_comms_task(),
- dspic_pic_comms_queue_message(),
- crc32(),
- UART2_ErrorClear(),


The module is called by the following modules:
- PDA-CI-010 - Main application module,
- PDA-CI-012 - Message exchange module,
- PDA-CI-016 - PDA-PI communication module,
- PDA-CI-020 - System initialisation module,
- PDA-CI-026 - Interrupt manager module,

The module calls the following modules:
- PDA-CI-033 - stdbool library
- PDA-CI-037 - stddef library
- PDA-CI-032 - stdint library
- PDA-CI-035 - string library
- PDA-CI-043 - stdlib library
- PDA-CI-016 - PDA-PI communication module
- PDA-CI-001 - Debugging communication module
- PDA-CI-012 - Message exchange module
- PDA-CI-008 - EEPROM module
\subsection sec_PDA-CI-010 PDA-CI-010 - Main application module
The module consists of the following constituents:
- main.c
- pdab.c
- pdab.h
- pdab_types.h
- configuration.h
- definitions.h
- user.h


Functionality: Provides main application framework.


The module provides the following interfaces:
- blocking_delay(),
- PDAB_Error_Status(),
- PDAB_Set_Gain(),
- PDAB_Set_Power(),
- PDAB_Command_Received(),
- PDAB_Tasks(),
- PDAB_Initialize(),


The module is called by the following modules:
- PDA-CI-006 - Laser driver module,
- PDA-CI-008 - EEPROM module,
- PDA-CI-014 - Scanning logic module,
- PDA-CI-015 - USB module,
- PDA-CI-016 - PDA-PI communication module,
- PDA-CI-019 - System module,
- PDA-CI-020 - System initialisation module,

The module calls the following modules:
- PDA-CI-032 - stdint library
- PDA-CI-037 - stddef library
- PDA-CI-033 - stdbool library
- PDA-CI-043 - stdlib library
- PDA-CI-022 - ADC module
- PDA-CI-023 - Clock module
- PDA-CI-024 - Comparator module
- PDA-CI-001 - Debugging communication module
- PDA-CI-025 - DMA module
- PDA-CI-005 - I2C module
- PDA-CI-018 - USB module
- PDA-CI-009 - PDA-LSC communication module
- PDA-CI-026 - Interrupt manager module
- PDA-CI-027 - GPIO module
- PDA-CI-016 - PDA-PI communication module
- PDA-CI-028 - Parallel port module
- PDA-CI-019 - System module
- PDA-CI-029 - Timer module
- PDA-CI-020 - System initialisation module
- PDA-CI-006 - Laser driver module
- PDA-CI-007 - PDA-LSC state machine module
- PDA-CI-008 - EEPROM module
- PDA-CI-002 - Digital to Analog Converter module
- PDA-CI-014 - Scanning logic module
- PDA-CI-015 - USB module
- PDA-CI-003 - Digital Potentiometer module
- PDA-CI-004 - ADC LTC2203 module
\subsection sec_PDA-CI-011 PDA-CI-011 - Maths module
The module consists of the following constituents:
- maths_library.c
- maths_library.h


Functionality: Provides amthematical functions.

The module does not provides any interfaces.


The module is called by the following modules:
- None

The module calls the following modules:
- PDA-CI-032 - stdint library
- PDA-CI-041 - math library
\subsection sec_PDA-CI-012 PDA-CI-012 - Message exchange module
The module consists of the following constituents:
- message_exchange.c
- message_exchange.h


Functionality: Provides application-level functionality related to communication with LSC and PI PESS.


The module provides the following interfaces:
- send_command_LSC_is_shutdown_safe_message(),
- send_get_LSC_status_message(),
- send_get_LSC_version_message(),
- send_request_LSC_define_limits_message(),
- send_request_LSC_start_scanning_message(),
- send_request_LSC_stop_scanning_message(),
- send_request_reset_message(),
- process_lsc_request_shutdown_message(),
- process_lsc_status_message(),
- process_lsc_version_message(),
- process_pdab_is_safe_to_shutdown_message(),


The module is called by the following modules:
- PDA-CI-007 - PDA-LSC state machine module,
- PDA-CI-009 - PDA-LSC communication module,
- PDA-CI-016 - PDA-PI communication module,

The module calls the following modules:
- PDA-CI-035 - string library
- PDA-CI-001 - Debugging communication module
- PDA-CI-016 - PDA-PI communication module
- PDA-CI-007 - PDA-LSC state machine module
- PDA-CI-009 - PDA-LSC communication module
\subsection sec_PDA-CI-013 PDA-CI-013 - NPDA module
The module consists of the following constituents:
- npda.c
- npda.h
- npda_tools.c
- npda_tools.h


Functionality: Provides functionality related to NPDA algorithm that calculates corneal thickness from scan data.


The module provides the following interfaces:
- median_uint16_t(),
- run_npda(),


The module is called by the following modules:
- PDA-CI-014 - Scanning logic module,

The module calls the following modules:
- PDA-CI-043 - stdlib library
- PDA-CI-045 - stdio library
- PDA-CI-041 - math library
- PDA-CI-032 - stdint library
- PDA-CI-033 - stdbool library
- PDA-CI-037 - stddef library
- PDA-CI-035 - string library
- PDA-CI-042 - float library
\subsection sec_PDA-CI-014 PDA-CI-014 - Scanning logic module
The module consists of the following constituents:
- pdab_scan_functions.c
- pdab_scan_functions.h


Functionality: Provides functionality related to logic controlling the scanning process.


The module provides the following interfaces:
- Stop_Scanning(),
- get_npda_buffer_ptr(),
- Start_Scanning(),
- update_scan_settings(),
- Scan_Busy(),
- Scan_Tasks(),
- Scan_Idx_To_Gain(),
- Scan_Set_Dac_Zero_For_Gain(),


The module is called by the following modules:
- PDA-CI-006 - Laser driver module,
- PDA-CI-010 - Main application module,

The module calls the following modules:
- PDA-CI-043 - stdlib library
- PDA-CI-035 - string library
- PDA-CI-041 - math library
- PDA-CI-001 - Debugging communication module
- PDA-CI-026 - Interrupt manager module
- PDA-CI-019 - System module
- PDA-CI-029 - Timer module
- PDA-CI-025 - DMA module
- PDA-CI-024 - Comparator module
- PDA-CI-004 - ADC LTC2203 module
- PDA-CI-006 - Laser driver module
- PDA-CI-007 - PDA-LSC state machine module
- PDA-CI-002 - Digital to Analog Converter module
- PDA-CI-003 - Digital Potentiometer module
- PDA-CI-015 - USB module
- PDA-CI-010 - Main application module
- PDA-CI-017 - Scanning module
- PDA-CI-013 - NPDA module
- PDA-CI-016 - PDA-PI communication module
- PDA-CI-027 - GPIO module
\subsection sec_PDA-CI-015 PDA-CI-015 - USB module
The module consists of the following constituents:
- pdab_usb_functions.c
- pdab_usb_functions.h


Functionality: Provides application-level functionality related to USB processing.


The module provides the following interfaces:
- USB_Clear_Endpoints(),
- USB_is_device_attached(),
- USB_Return_Data(),
- USB_Tasks(),
- USB_is_buffer_overrun(),


The module is called by the following modules:
- PDA-CI-008 - EEPROM module,
- PDA-CI-010 - Main application module,
- PDA-CI-014 - Scanning logic module,

The module calls the following modules:
- PDA-CI-010 - Main application module
- PDA-CI-018 - USB module
- PDA-CI-001 - Debugging communication module
\subsection sec_PDA-CI-016 PDA-CI-016 - PDA-PI communication module
The module consists of the following constituents:
- pic_comms.c
- pic_comms.h


Functionality: Provides driver-level functionality related to the communication with the PI PESS.


The module provides the following interfaces:
- rx_buffer_add(),
- rx_buffer_full(),
- cancel_timeout(),
- tx_buffer_full(),
- tx_buffer_add(),
- tx_buffer_empty(),
- calculate_header_checksum(),
- send_bytes(),
- start_timeout(),
- tx_buffer_free_space(),
- crc32(),
- rx_buffer_empty(),
- get_received_data(),
- get_timer_value(),
- message_acknowledged(),
- resend_message(),
- rx_buffer_data_length(),
- send_ack_message(),
- pic_communications_init(),
- pic_transmit_timer(),
- pic_communications_send_message(),
- pic_comms_task(),
- UART3_ErrorClear(),


The module is called by the following modules:
- PDA-CI-001 - Debugging communication module,
- PDA-CI-006 - Laser driver module,
- PDA-CI-009 - PDA-LSC communication module,
- PDA-CI-010 - Main application module,
- PDA-CI-012 - Message exchange module,
- PDA-CI-014 - Scanning logic module,
- PDA-CI-020 - System initialisation module,
- PDA-CI-026 - Interrupt manager module,

The module calls the following modules:
- PDA-CI-035 - string library
- PDA-CI-001 - Debugging communication module
- PDA-CI-010 - Main application module
- PDA-CI-012 - Message exchange module
- PDA-CI-009 - PDA-LSC communication module
- PDA-CI-008 - EEPROM module
\subsection sec_PDA-CI-017 PDA-CI-017 - Scanning module
The module consists of the following constituents:
- scan_processing.c
- scan_processing.h


Functionality: Provides functionality related to scan processing and scan pre-selection.


The module provides the following interfaces:
- Find_Peaks_NPDA(),
- Scan_Selection(),
- Truncate_Data(),


The module is called by the following modules:
- PDA-CI-014 - Scanning logic module,

The module calls the following modules:
- PDA-CI-041 - math library
- PDA-CI-001 - Debugging communication module
\subsection sec_PDA-CI-018 PDA-CI-018 - USB module
The module consists of the following constituents:
- driver.h
- driver_common.h
- drv_usb.h
- drv_usb_external_dependencies.h
- drv_usbhs.h
- drv_usbhs_local.h
- drv_usbhs_variant_mapping.h
- plib_usbhs.h
- plib_usbhs_header.h
- usbhs_ClockResetControl_Default.h
- usbhs_ClockResetControl_Unsupported.h
- usbhs_EndpointFIFO_Default.h
- usbhs_EndpointFIFO_Unsupported.h
- usbhs_EndpointOperations_Default.h
- usbhs_EndpointOperations_Unsupported.h
- usbhs_EP0Status_Default.h
- usbhs_EP0Status_Unsupported.h
- usbhs_HighSpeedSupport_Default.h
- usbhs_HighSpeedSupport_Unsupported.h
- usbhs_Interrupts_Default.h
- usbhs_Interrupts_Unsupported.h
- usbhs_ModuleControl_Default.h
- usbhs_ModuleControl_Unsupported.h
- usbhs_registers.h
- usbhs_RxEPStatus_Default.h
- usbhs_RxEPStatus_Unsupported.h
- usbhs_SoftReset_Default.h
- usbhs_SoftReset_Unsupported.h
- usbhs_TxEPStatus_Default.h
- usbhs_TxEPStatus_Unsupported.h
- usbhs_USBIDControl_Default.h
- usbhs_USBIDControl_Unsupported.h
- usbhs_registers.h
- usb_device_function_driver.h
- usb_device_local.h
- usb_device_mapping.h
- usb_external_dependencies.h
- usb_chapter_9.h
- usb_common.h
- usb_device.h
- usb_host.h
- usb_host_client_driver.h
- usb_host_hub_interface.h
- usb_hub.h
- drv_usbhs.c
- drv_usbhs_device.c
- usb_device.c
- usb_device_endpoint_functions.c
- usb_device_init_data.c


Functionality: Provides driver-level functionality related to USB.


The module provides the following interfaces:
- DRV_USBHS_Initialize(),
- USB_DEVICE_Initialize(),
- DRV_USBHS_Tasks(),
- USB_DEVICE_Tasks(),
- USB_DEVICE_ActiveSpeedGet(),
- USB_DEVICE_EndpointDisable(),
- USB_DEVICE_EndpointEnable(),
- USB_DEVICE_EndpointIsEnabled(),
- USB_DEVICE_EndpointRead(),
- USB_DEVICE_EventHandlerSet(),
- USB_DEVICE_Open(),
- USB_DEVICE_Attach(),
- USB_DEVICE_ControlSend(),
- USB_DEVICE_ControlStatus(),
- USB_DEVICE_Detach(),
- USB_DEVICE_EndpointWrite(),
- USB_DEVICE_EndpointTransferCancel(),
- DRV_USBHS_Tasks_ISR(),
- DRV_USBHS_Tasks_ISR_USBDMA(),


The module is called by the following modules:
- PDA-CI-010 - Main application module,
- PDA-CI-015 - USB module,
- PDA-CI-019 - System module,
- PDA-CI-020 - System initialisation module,
- PDA-CI-026 - Interrupt manager module,

The module calls the following modules:
- PDA-CI-032 - stdint library
- PDA-CI-033 - stdbool library
- PDA-CI-035 - string library
- PDA-CI-037 - stddef library
- PDA-CI-034 - xc library
- PDA-CI-036 - limits library
- PDA-CI-043 - stdlib library
- PDA-CI-047 - kmem library
- PDA-CI-039 - p32xxxx library
\subsection sec_PDA-CI-019 PDA-CI-019 - System module
The module consists of the following constituents:
- sys_debug.h
- sys_dma.c
- sys_dma.h
- sys_dma_mapping.h
- sys_int.c
- sys_int.h
- sys_int_mapping.h
- sys_ports.h
- sys_ports_mapping.h
- system.h
- system_common.h
- system_module.h
- sys_time.c
- sys_time.h
- sys_time_definitions.h
- sys_time_local.h
- toolchain_specifics.h
- tasks.c
- xc32_monitor.c


Functionality: Provides functionality related to various system functions including: Dynamic Memory Access/interrupts/system time/stdio.


The module provides the following interfaces:
- SYS_INT_Disable(),
- SYS_INT_Restore(),
- SYS_INT_SourceDisable(),
- SYS_INT_SourceStatusClear(),
- SYS_PORT_PinClear(),
- SYS_PORT_PinOutputEnable(),
- SYS_PORT_PinSet(),
- SYS_PORT_PinInputEnable(),
- SYS_PORT_PinLatchRead(),
- SYS_PORT_PinRead(),
- SYS_PORT_PinWrite(),
- SYS_TIME_Initialize(),
- SYS_Tasks(),


The module is called by the following modules:
- PDA-CI-001 - Debugging communication module,
- PDA-CI-004 - ADC LTC2203 module,
- PDA-CI-006 - Laser driver module,
- PDA-CI-007 - PDA-LSC state machine module,
- PDA-CI-010 - Main application module,
- PDA-CI-014 - Scanning logic module,
- PDA-CI-020 - System initialisation module,

The module calls the following modules:
- PDA-CI-033 - stdbool library
- PDA-CI-037 - stddef library
- PDA-CI-032 - stdint library
- PDA-CI-035 - string library
- PDA-CI-048 - assert library
- PDA-CI-040 - types library
- PDA-CI-025 - DMA module
- PDA-CI-026 - Interrupt manager module
- PDA-CI-027 - GPIO module
- PDA-CI-018 - USB module
- PDA-CI-010 - Main application module
\subsection sec_PDA-CI-020 PDA-CI-020 - System initialisation module
The module consists of the following constituents:
- initialization.c


Functionality: Provides system initialisation functionality.


The module provides the following interfaces:
- SYS_Initialize(),


The module is called by the following modules:
- PDA-CI-010 - Main application module,

The module calls the following modules:
- PDA-CI-022 - ADC module
- PDA-CI-023 - Clock module
- PDA-CI-024 - Comparator module
- PDA-CI-001 - Debugging communication module
- PDA-CI-025 - DMA module
- PDA-CI-005 - I2C module
- PDA-CI-018 - USB module
- PDA-CI-009 - PDA-LSC communication module
- PDA-CI-026 - Interrupt manager module
- PDA-CI-027 - GPIO module
- PDA-CI-010 - Main application module
- PDA-CI-016 - PDA-PI communication module
- PDA-CI-028 - Parallel port module
- PDA-CI-019 - System module
- PDA-CI-029 - Timer module
\subsection sec_PDA-CI-021 PDA-CI-021 - Exceptions module
The module consists of the following constituents:
- exceptions.c


Functionality: Provides functionality related to exceptions.

The module does not provides any interfaces.


The module is called by the following modules:
- None

The module calls the following modules:
- PDA-CI-045 - stdio library
- PDA-CI-001 - Debugging communication module
\subsection sec_PDA-CI-022 PDA-CI-022 - ADC module
The module consists of the following constituents:
- plib_adchs.c
- plib_adchs.h
- plib_adchs_common.h


Functionality: Provides functionality related to high speed Analogue to Digital Converter.


The module provides the following interfaces:
- ADCHS_Initialize(),


The module is called by the following modules:
- PDA-CI-010 - Main application module,
- PDA-CI-020 - System initialisation module,

The module calls the following modules:
- PDA-CI-037 - stddef library
- PDA-CI-033 - stdbool library
\subsection sec_PDA-CI-023 PDA-CI-023 - Clock module
The module consists of the following constituents:
- plib_clk.c
- plib_clk.h


Functionality: Provides functionality related to clock.


The module provides the following interfaces:
- CLK_Initialize(),


The module is called by the following modules:
- PDA-CI-010 - Main application module,
- PDA-CI-020 - System initialisation module,

The module calls the following modules:
- PDA-CI-037 - stddef library
- PDA-CI-033 - stdbool library
\subsection sec_PDA-CI-024 PDA-CI-024 - Comparator module
The module consists of the following constituents:
- plib_cmp.c
- plib_cmp.h
- plib_cvr.c
- plib_cvr.h


Functionality: Provides functionality related to comparator.


The module provides the following interfaces:
- CMP_Initialize(),
- CVR_Initialize(),
- CMP_1_CompareEnable(),
- CVR_Start(),
- CVR_Stop(),
- CVR_UpdateValue(),
- CMP_1_CompareDisable(),
- CMP_1_CallbackRegister(),


The module is called by the following modules:
- PDA-CI-010 - Main application module,
- PDA-CI-014 - Scanning logic module,
- PDA-CI-020 - System initialisation module,

The module calls the following modules:
- PDA-CI-037 - stddef library
- PDA-CI-033 - stdbool library
- PDA-CI-032 - stdint library
\subsection sec_PDA-CI-025 PDA-CI-025 - DMA module
The module consists of the following constituents:
- plib_dmac.c
- plib_dmac.h


Functionality: Provides functionality related to the Dynamic Memory Access.


The module provides the following interfaces:
- DMAC_ChannelIsBusy(),
- DMAC_ChannelTransfer(),
- DMAC_ChannelCallbackRegister(),
- DMAC_ChannelDisable(),
- DMAC_Initialize(),
- DMAC_SetupChannelTransfer(),


The module is called by the following modules:
- PDA-CI-004 - ADC LTC2203 module,
- PDA-CI-010 - Main application module,
- PDA-CI-014 - Scanning logic module,
- PDA-CI-019 - System module,
- PDA-CI-020 - System initialisation module,

The module calls the following modules:
- PDA-CI-031 - p32mz1024efh100 library
- PDA-CI-035 - string library
- PDA-CI-033 - stdbool library
- PDA-CI-047 - kmem library
\subsection sec_PDA-CI-026 PDA-CI-026 - Interrupt manager module
The module consists of the following constituents:
- plib_evic.c
- plib_evic.h
- interrupts.c


Functionality: Provides functionality related to interrupt management.


The module provides the following interfaces:
- EVIC_SourceDisable(),
- EVIC_SourceStatusClear(),
- EVIC_Initialize(),
- EVIC_SourceEnable(),


The module is called by the following modules:
- PDA-CI-007 - PDA-LSC state machine module,
- PDA-CI-010 - Main application module,
- PDA-CI-014 - Scanning logic module,
- PDA-CI-019 - System module,
- PDA-CI-020 - System initialisation module,

The module calls the following modules:
- PDA-CI-031 - p32mz1024efh100 library
- PDA-CI-037 - stddef library
- PDA-CI-033 - stdbool library
- PDA-CI-001 - Debugging communication module
- PDA-CI-018 - USB module
- PDA-CI-009 - PDA-LSC communication module
- PDA-CI-016 - PDA-PI communication module
- PDA-CI-029 - Timer module
\subsection sec_PDA-CI-027 PDA-CI-027 - GPIO module
The module consists of the following constituents:
- plib_gpio.c
- plib_gpio.h


Functionality: Provides GPIO peripheral functionality.


The module provides the following interfaces:
- GPIO_Initialize(),
- GPIO_PinInterruptCallbackRegister(),
- GPIO_PortInterruptEnable(),
- GPIO_PinWrite(),
- GPIO_PinRead(),
- GPIO_PinLatchRead(),
- GPIO_PinToggle(),
- GPIO_PinSet(),
- GPIO_PinClear(),
- GPIO_PinInputEnable(),
- GPIO_PinOutputEnable(),


The module is called by the following modules:
- PDA-CI-010 - Main application module,
- PDA-CI-014 - Scanning logic module,
- PDA-CI-019 - System module,
- PDA-CI-020 - System initialisation module,

The module calls the following modules:
- PDA-CI-031 - p32mz1024efh100 library
- PDA-CI-032 - stdint library
- PDA-CI-033 - stdbool library
- PDA-CI-037 - stddef library
\subsection sec_PDA-CI-028 PDA-CI-028 - Parallel port module
The module consists of the following constituents:
- plib_pmp.c
- plib_pmp.h


Functionality: Provides functionality related to the parallel port.


The module provides the following interfaces:
- PMP_Initialize(),


The module is called by the following modules:
- PDA-CI-010 - Main application module,
- PDA-CI-020 - System initialisation module,

The module calls the following modules:
- PDA-CI-033 - stdbool library
- PDA-CI-037 - stddef library
\subsection sec_PDA-CI-029 PDA-CI-029 - Timer module
The module consists of the following constituents:
- plib_tmr2.c
- plib_tmr2.h
- plib_tmr3.c
- plib_tmr3.h
- plib_tmr4.c
- plib_tmr4.h
- plib_tmr1.c
- plib_tmr1.h


Functionality: Provides functionality related to the Timer peripherals.


The module provides the following interfaces:
- TMR1_Initialize(),
- TMR2_Initialize(),
- TMR3_Initialize(),
- TMR4_Initialize(),
- TMR2_CallbackRegister(),
- TMR2_InterruptEnable(),
- TMR2_Start(),
- TMR4_PeriodSet(),
- TMR4_CounterGet(),
- TMR4_Start(),
- TMR4_Stop(),
- TIMER_1_InterruptHandler(),
- TIMER_2_InterruptHandler(),
- TIMER_3_InterruptHandler(),


The module is called by the following modules:
- PDA-CI-010 - Main application module,
- PDA-CI-014 - Scanning logic module,
- PDA-CI-020 - System initialisation module,
- PDA-CI-026 - Interrupt manager module,

The module calls the following modules:
- PDA-CI-037 - stddef library
- PDA-CI-032 - stdint library
\subsection sec_PDA-CI-030 PDA-CI-030 - UART module
The module consists of the following constituents:
- plib_uart1.c
- plib_uart1.h
- plib_uart3.c
- plib_uart3.h
- plib_uart4.c
- plib_uart4.h
- plib_uart_common.h


Functionality: Provides functionality related to the UART peripherals.

The module does not provides any interfaces.


The module is called by the following modules:
- None

The module calls the following modules:
- PDA-CI-037 - stddef library
- PDA-CI-033 - stdbool library
- PDA-CI-032 - stdint library
\subsection sec_PDA-CI-031 PDA-CI-031 - p32mz1024efh100 library
The module consists of the following constituents:
- p32mz1024efh100.h
- device.h


Functionality: Generic utility functions for PIC32MZ1024EFH100.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-025 - DMA module,
- PDA-CI-026 - Interrupt manager module,
- PDA-CI-027 - GPIO module,

The module calls the following modules:
- PDA-CI-034 - xc library
- PDA-CI-038 - attribs library
\subsection sec_PDA-CI-032 PDA-CI-032 - stdint library
The module consists of the following constituents:
- stdint.h


Functionality: Standard integer types library.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-001 - Debugging communication module,
- PDA-CI-005 - I2C module,
- PDA-CI-008 - EEPROM module,
- PDA-CI-009 - PDA-LSC communication module,
- PDA-CI-010 - Main application module,
- PDA-CI-011 - Maths module,
- PDA-CI-013 - NPDA module,
- PDA-CI-018 - USB module,
- PDA-CI-019 - System module,
- PDA-CI-024 - Comparator module,
- PDA-CI-027 - GPIO module,
- PDA-CI-029 - Timer module,
- PDA-CI-030 - UART module,

The module calls the following modules:
- None
\subsection sec_PDA-CI-033 PDA-CI-033 - stdbool library
The module consists of the following constituents:
- stdbool.h


Functionality: Standard boolean types library.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-001 - Debugging communication module,
- PDA-CI-005 - I2C module,
- PDA-CI-008 - EEPROM module,
- PDA-CI-009 - PDA-LSC communication module,
- PDA-CI-010 - Main application module,
- PDA-CI-013 - NPDA module,
- PDA-CI-018 - USB module,
- PDA-CI-019 - System module,
- PDA-CI-022 - ADC module,
- PDA-CI-023 - Clock module,
- PDA-CI-024 - Comparator module,
- PDA-CI-025 - DMA module,
- PDA-CI-026 - Interrupt manager module,
- PDA-CI-027 - GPIO module,
- PDA-CI-028 - Parallel port module,
- PDA-CI-030 - UART module,

The module calls the following modules:
- None
\subsection sec_PDA-CI-034 PDA-CI-034 - xc library
The module consists of the following constituents:
- xc.h


Functionality: Library providing support for the specific PESS device.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-018 - USB module,
- PDA-CI-031 - p32mz1024efh100 library,

The module calls the following modules:
- None
\subsection sec_PDA-CI-035 PDA-CI-035 - string library
The module consists of the following constituents:
- string.h


Functionality: Library providing string support functions.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-001 - Debugging communication module,
- PDA-CI-009 - PDA-LSC communication module,
- PDA-CI-012 - Message exchange module,
- PDA-CI-013 - NPDA module,
- PDA-CI-014 - Scanning logic module,
- PDA-CI-016 - PDA-PI communication module,
- PDA-CI-018 - USB module,
- PDA-CI-019 - System module,
- PDA-CI-025 - DMA module,

The module calls the following modules:
- None
\subsection sec_PDA-CI-036 PDA-CI-036 - limits library
The module consists of the following constituents:
- limits.h


Functionality: Library providing limits for common variable types.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-018 - USB module,

The module calls the following modules:
- None
\subsection sec_PDA-CI-037 PDA-CI-037 - stddef library
The module consists of the following constituents:
- stddef.h


Functionality: Library providing standard definitions.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-001 - Debugging communication module,
- PDA-CI-005 - I2C module,
- PDA-CI-009 - PDA-LSC communication module,
- PDA-CI-010 - Main application module,
- PDA-CI-013 - NPDA module,
- PDA-CI-018 - USB module,
- PDA-CI-019 - System module,
- PDA-CI-022 - ADC module,
- PDA-CI-023 - Clock module,
- PDA-CI-024 - Comparator module,
- PDA-CI-026 - Interrupt manager module,
- PDA-CI-027 - GPIO module,
- PDA-CI-028 - Parallel port module,
- PDA-CI-029 - Timer module,
- PDA-CI-030 - UART module,

The module calls the following modules:
- None
\subsection sec_PDA-CI-038 PDA-CI-038 - attribs library
The module consists of the following constituents:
- attribs.h


Functionality: Library providing macros for function and variable attributes.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-031 - p32mz1024efh100 library,

The module calls the following modules:
- None
\subsection sec_PDA-CI-039 PDA-CI-039 - p32xxxx library
The module consists of the following constituents:
- p32xxxx.h


Functionality: Library providing backwards compatibility for __C32_UART macro.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-018 - USB module,

The module calls the following modules:
- None
\subsection sec_PDA-CI-040 PDA-CI-040 - types library
The module consists of the following constituents:
- types.h


Functionality: Library providing system type functions.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-019 - System module,

The module calls the following modules:
- None
\subsection sec_PDA-CI-041 PDA-CI-041 - math library
The module consists of the following constituents:
- math.h


Functionality: Library providing maths functions.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-011 - Maths module,
- PDA-CI-013 - NPDA module,
- PDA-CI-014 - Scanning logic module,
- PDA-CI-017 - Scanning module,

The module calls the following modules:
- None
\subsection sec_PDA-CI-042 PDA-CI-042 - float library
The module consists of the following constituents:
- float.h


Functionality: Library providing characteristics of floating types.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-013 - NPDA module,

The module calls the following modules:
- None
\subsection sec_PDA-CI-043 PDA-CI-043 - stdlib library
The module consists of the following constituents:
- stdlib.h


Functionality: Standard utility functions library.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-001 - Debugging communication module,
- PDA-CI-005 - I2C module,
- PDA-CI-009 - PDA-LSC communication module,
- PDA-CI-010 - Main application module,
- PDA-CI-013 - NPDA module,
- PDA-CI-014 - Scanning logic module,
- PDA-CI-018 - USB module,

The module calls the following modules:
- None
\subsection sec_PDA-CI-044 PDA-CI-044 - stdarg library
The module consists of the following constituents:
- stdarg.h


Functionality: Library providing functionality related to accepting indefinite number of arguments.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-001 - Debugging communication module,

The module calls the following modules:
- None
\subsection sec_PDA-CI-045 PDA-CI-045 - stdio library
The module consists of the following constituents:
- stdio.h


Functionality: Library providing standard I/O support functions.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-013 - NPDA module,
- PDA-CI-021 - Exceptions module,

The module calls the following modules:
- None
\subsection sec_PDA-CI-046 PDA-CI-046 - cp0defs library
The module consists of the following constituents:
- cp0defs.h


Functionality: Contains register definitions for the CP0 registers.

The module does not provides any interfaces.


The module is called by the following modules:
- None

The module calls the following modules:
- None
\subsection sec_PDA-CI-047 PDA-CI-047 - kmem library
The module consists of the following constituents:
- kmem.h


Functionality: Macros for kseg address translation.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-018 - USB module,
- PDA-CI-025 - DMA module,

The module calls the following modules:
- None
\subsection sec_PDA-CI-048 PDA-CI-048 - assert library
The module consists of the following constituents:
- assert.h


Functionality: Library providing standard assertions.

The module does not provides any interfaces.


The module is called by the following modules:
- PDA-CI-019 - System module,

The module calls the following modules:
- None
\section trace_mat_sec Architecture and software requirements
The following table shows how the software requirements map onto the software architecture, and therefore how the architecture implements these requirements.
<table>
<caption id='multi_row'>Requirements traceability matrix</caption>
<tr><th>Software module <th>Requirement ID
<tr><td>PDA-CI-001 - Debugging communication module<td>
<tr><td>PDA-CI-002 - Digital to Analog Converter module<td>
<tr><td>PDA-CI-003 - Digital Potentiometer module<td>
<tr><td>PDA-CI-004 - ADC LTC2203 module<td>
<tr><td>PDA-CI-005 - I2C module<td>
<tr><td>PDA-CI-006 - Laser driver module<td>
<tr><td>PDA-CI-007 - PDA-LSC state machine module<td>
<tr><td>PDA-CI-008 - EEPROM module<td>
<tr><td>PDA-CI-009 - PDA-LSC communication module<td>
<tr><td>PDA-CI-010 - Main application module<td>
<tr><td>PDA-CI-011 - Maths module<td>
<tr><td>PDA-CI-012 - Message exchange module<td>
<tr><td>PDA-CI-013 - NPDA module<td>
<tr><td>PDA-CI-014 - Scanning logic module<td>
<tr><td>PDA-CI-015 - USB module<td>
<tr><td>PDA-CI-016 - PDA-PI communication module<td>
<tr><td>PDA-CI-017 - Scanning module<td>
<tr><td>PDA-CI-018 - USB module<td>
<tr><td>PDA-CI-019 - System module<td>
<tr><td>PDA-CI-020 - System initialisation module<td>
<tr><td>PDA-CI-021 - Exceptions module<td>
<tr><td>PDA-CI-022 - ADC module<td>
<tr><td>PDA-CI-023 - Clock module<td>
<tr><td>PDA-CI-024 - Comparator module<td>
<tr><td>PDA-CI-025 - DMA module<td>
<tr><td>PDA-CI-026 - Interrupt manager module<td>
<tr><td>PDA-CI-027 - GPIO module<td>
<tr><td>PDA-CI-028 - Parallel port module<td>
<tr><td>PDA-CI-029 - Timer module<td>
<tr><td>PDA-CI-030 - UART module<td>
<tr><td>PDA-CI-031 - p32mz1024efh100 library<td>
<tr><td>PDA-CI-032 - stdint library<td>
<tr><td>PDA-CI-033 - stdbool library<td>
<tr><td>PDA-CI-034 - xc library<td>
<tr><td>PDA-CI-035 - string library<td>
<tr><td>PDA-CI-036 - limits library<td>
<tr><td>PDA-CI-037 - stddef library<td>
<tr><td>PDA-CI-038 - attribs library<td>
<tr><td>PDA-CI-039 - p32xxxx library<td>
<tr><td>PDA-CI-040 - types library<td>
<tr><td>PDA-CI-041 - math library<td>
<tr><td>PDA-CI-042 - float library<td>
<tr><td>PDA-CI-043 - stdlib library<td>
<tr><td>PDA-CI-044 - stdarg library<td>
<tr><td>PDA-CI-045 - stdio library<td>
<tr><td>PDA-CI-046 - cp0defs library<td>
<tr><td>PDA-CI-047 - kmem library<td>
<tr><td>PDA-CI-048 - assert library<td>
</table>
*/
