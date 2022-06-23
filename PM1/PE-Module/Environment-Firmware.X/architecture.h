/**
\mainpage Software Architecture Documentation
\section arch_overview_sec Architecture overview
\startuml{architecture.png} "Software Architecture Diagram" width=10cm
package "External libraries" {
component [stdint library\nPE-CI-019] as PECI019 #Chocolate
component [stdbool library\nPE-CI-020] as PECI020 #Chocolate
component [xc library\nPE-CI-021] as PECI021 #Chocolate
component [string library\nPE-CI-022] as PECI022 #Chocolate
component [stdio library\nPE-CI-023] as PECI023 #Chocolate
component [stddef library\nPE-CI-024] as PECI024 #Chocolate
component [stdlib library\nPE-CI-025] as PECI025 #Chocolate
component [stdarg library\nPE-CI-026] as PECI026 #Chocolate
}
package "Application layer" {
component [Main application module\nPE-CI-001] as PECI001 #CornflowerBlue
component [Battery module\nPE-CI-002] as PECI002 #CornflowerBlue
component [Message exchange module\nPE-CI-007] as PECI007 #CornflowerBlue
component [Temperature monitor module\nPE-CI-010] as PECI010 #CornflowerBlue
component [Analog to Digital Converter module\nPE-CI-011] as PECI011 #CornflowerBlue
component [System initialisation module\nPE-CI-014] as PECI014 #Orange
component [System module\nPE-CI-016] as PECI016 #Orange
}
package "Driver layer" {
component [PE-PI communication module\nPE-CI-003] as PECI003 #CornflowerBlue
component [I2C module\nPE-CI-004] as PECI004 #CornflowerBlue
component [Accelerometer module\nPE-CI-005] as PECI005 #CornflowerBlue
component [Temperature sensor module\nPE-CI-006] as PECI006 #CornflowerBlue
component [Debugging communication module\nPE-CI-008] as PECI008 #Orange
component [Power switch module\nPE-CI-009] as PECI009 #Orange
component [Clock module\nPE-CI-012] as PECI012 #Orange
component [Interrupt manager module\nPE-CI-013] as PECI013 #Orange
component [GPIO module\nPE-CI-015] as PECI015 #Orange
component [Timer module\nPE-CI-017] as PECI017 #Orange
component [UART module\nPE-CI-018] as PECI018 #Orange
}
package "Hardware" {
component [Temperature sensor\n] as HW001 #LimeGreen
component [Accelerometer\n] as HW002 #LimeGreen
component [Push button\n] as HW003 #LimeGreen
component [PI\n] as HW004 #LimeGreen
component [Voltage regulators\n] as HW005 #LimeGreen
}
[HW001] -right- [PECI004]
[HW001] -right- [PECI015]
[HW002] -right- [PECI004]
[HW002] -right- [PECI015]
[HW003] -right- [PECI015]
[HW004] -right- [PECI018]
[HW005] -right- [PECI015]
[PECI001] -[hidden]down-> [PECI002]
[PECI002] -[hidden]down-> [PECI007]
[PECI007] -[hidden]down-> [PECI010]
[PECI010] -[hidden]down-> [PECI011]
[PECI011] -[hidden]down-> [PECI014]
[PECI014] -[hidden]down-> [PECI016]
[PECI003] -[hidden]down-> [PECI004]
[PECI004] -[hidden]down-> [PECI005]
[PECI005] -[hidden]down-> [PECI006]
[PECI006] -[hidden]down-> [PECI008]
[PECI008] -[hidden]down-> [PECI009]
[PECI009] -[hidden]down-> [PECI012]
[PECI012] -[hidden]down-> [PECI013]
[PECI013] -[hidden]down-> [PECI015]
[PECI015] -[hidden]down-> [PECI017]
[PECI017] -[hidden]down-> [PECI018]
[HW001] -[hidden]down-> [HW002]
[HW002] -[hidden]down-> [HW003]
[HW003] -[hidden]down-> [HW004]
[HW004] -[hidden]down-> [HW005]
[PECI019] -[hidden]down-> [PECI020]
[PECI020] -[hidden]down-> [PECI021]
[PECI021] -[hidden]down-> [PECI022]
[PECI022] -[hidden]down-> [PECI023]
[PECI023] -[hidden]down-> [PECI024]
[PECI024] -[hidden]down-> [PECI025]
[PECI025] -[hidden]down-> [PECI026]
[PECI001] -right-> [PECI008]
[PECI001] <-right-> [PECI002]
[PECI001] <-right-> [PECI009]
[PECI001] -right-> [PECI004]
[PECI001] -right-> [PECI003]
[PECI001] -right-> [PECI016]
[PECI001] <-right-> [PECI010]
[PECI001] -right-> [PECI017]
[PECI001] <-right-> [PECI007]
[PECI002] -right-> [PECI011]
[PECI002] -right-> [PECI015]
[PECI002] -right-> [PECI009]
[PECI002] -right-> [PECI008]
[PECI003] <-right-> [PECI007]
[PECI003] -right-> [PECI008]
[PECI005] -right-> [PECI008]
[PECI007] -right-> [PECI008]
[PECI007] <-right-> [PECI009]
[PECI008] -right-> [PECI018]
[PECI008] -right-> [PECI013]
[PECI009] -right-> [PECI003]
[PECI009] -right-> [PECI018]
[PECI009] -right-> [PECI008]
[PECI010] -right-> [PECI008]
[PECI010] -right-> [PECI006]
[PECI016] -right-> [PECI011]
[PECI016] -right-> [PECI002]
[PECI016] -right-> [PECI012]
[PECI016] -right-> [PECI013]
[PECI016] -right-> [PECI015]
[PECI016] -right-> [PECI017]
[PECI016] -right-> [PECI018]
\enduml
The Figure Software Architecture Diagram shows a diagram describing interconnections between the modules.
In the Figure, blocks indicated in orange correspond to SOUP modules, blocks indicated in brown correspond to SOUP module external to the main repository (and under configuration management by other means), and blue correspond to all other software modules. Directions of arrows determine inputs and outputs to/from the modules.
\section elem_descr_sec Element Descriptions and Interfaces
\subsection sec_PE-CI-001 PE-CI-001 - Main application module
The module consists of the following constituents:
- main.c
- app.c
- app.h
- board.h


Functionality: Provides main application logic.


The module provides the following interfaces:
- app_clear_flag(),
- app_set_flag(),
- app_check_flag(),
- app_update_battery_charge(),
- app_get_status(),
- app_update_date_time(),
- SYS_version(),
- app_reset_temperature_flags(),
- app_update_temperature(),


The module is called by the following modules:
- PE-CI-002 - Battery module,
- PE-CI-007 - Message exchange module,
- PE-CI-009 - Power switch module,
- PE-CI-010 - Temperature monitor module,

The module calls the following modules:
- PE-CI-008 - Debugging communication module
- PE-CI-002 - Battery module
- PE-CI-009 - Power switch module
- PE-CI-004 - I2C module
- PE-CI-003 - PE-PI communication module
- PE-CI-016 - System module
- PE-CI-010 - Temperature monitor module
- PE-CI-017 - Timer module
- PE-CI-007 - Message exchange module
\subsection sec_PE-CI-002 PE-CI-002 - Battery module
The module consists of the following constituents:
- battery_capacity.c
- battery_capacity.h


Functionality: Provides application-level functionality related to the battery charge status and management.


The module provides the following interfaces:
- battery_capacity_reset_avg(),
- battery_capacity_task(),
- get_battery_average_value(),
- turn_on_battery_capacity_task(),
- BATTERY_CAPACITY_Initialize(),


The module is called by the following modules:
- PE-CI-001 - Main application module,
- PE-CI-016 - System module,

The module calls the following modules:
- PE-CI-021 - xc library
- PE-CI-011 - Analog to Digital Converter module
- PE-CI-001 - Main application module
- PE-CI-015 - GPIO module
- PE-CI-009 - Power switch module
- PE-CI-008 - Debugging communication module
\subsection sec_PE-CI-003 PE-CI-003 - PE-PI communication module
The module consists of the following constituents:
- dar_comms.c
- dar_comms.h


Functionality: Provides driver-level functionality related to communication with PI PESS.


The module provides the following interfaces:
- pic_comms_task(),
- pic_communications_init(),
- pic_comms_queue_message(),


The module is called by the following modules:
- PE-CI-001 - Main application module,
- PE-CI-007 - Message exchange module,
- PE-CI-009 - Power switch module,

The module calls the following modules:
- PE-CI-020 - stdbool library
- PE-CI-024 - stddef library
- PE-CI-019 - stdint library
- PE-CI-022 - string library
- PE-CI-025 - stdlib library
- PE-CI-007 - Message exchange module
- PE-CI-008 - Debugging communication module
\subsection sec_PE-CI-004 PE-CI-004 - I2C module
The module consists of the following constituents:
- drv_i2c1.c
- drv_i2c1.h


Functionality: Provides driver-level functionality related to I2C communication.


The module provides the following interfaces:
- DRV_I2C1_Initialize(),


The module is called by the following modules:
- PE-CI-001 - Main application module,

The module calls the following modules:
- PE-CI-021 - xc library
- PE-CI-019 - stdint library
- PE-CI-020 - stdbool library
- PE-CI-025 - stdlib library
\subsection sec_PE-CI-005 PE-CI-005 - Accelerometer module
The module consists of the following constituents:
- drv_LIS2DS12.c
- drv_LIS2DS12.h


Functionality: Provides driver-level functionality related to the LIS2DS12 accelerometer.

The module does not provides any interfaces.


The module is called by the following modules:
- None

The module calls the following modules:
- PE-CI-021 - xc library
- PE-CI-008 - Debugging communication module
\subsection sec_PE-CI-006 PE-CI-006 - Temperature sensor module
The module consists of the following constituents:
- drv_STTS75.c
- drv_STTS75.h


Functionality: Provides driver-level functionality related to the STTS75 temperature sensor.


The module provides the following interfaces:
- STTS75_start_one_shot_measurement(),
- STTS75_write_configuration(),
- STTS75_write_OT_hyst_threshold(),
- STTS75_write_over_temp_threshold(),
- STTS75_read_temperature_register(),
- STTS75_valid_val(),


The module is called by the following modules:
- PE-CI-010 - Temperature monitor module,

The module calls the following modules:
- PE-CI-021 - xc library
\subsection sec_PE-CI-007 PE-CI-007 - Message exchange module
The module consists of the following constituents:
- message_exchange.c
- message_exchange.h
- pe_interface.h


Functionality: Provides application-level functionality related to communication with the PI PESS.


The module provides the following interfaces:
- wakeup_task(),
- process_get_status_message(),
- process_power_down_message(),
- process_request_version_message(),
- process_reset_error_message(),
- process_reset_message(),
- process_reset_temp_message(),
- process_set_time_date_message(),
- send_is_shutdown_safe_message(),
- wakeup_dar(),


The module is called by the following modules:
- PE-CI-001 - Main application module,
- PE-CI-003 - PE-PI communication module,
- PE-CI-009 - Power switch module,

The module calls the following modules:
- PE-CI-022 - string library
- PE-CI-019 - stdint library
- PE-CI-008 - Debugging communication module
- PE-CI-003 - PE-PI communication module
- PE-CI-001 - Main application module
- PE-CI-009 - Power switch module
\subsection sec_PE-CI-008 PE-CI-008 - Debugging communication module
The module consists of the following constituents:
- debug.c
- debug.h


Functionality: Provides functionality related to debugging communication.


The module provides the following interfaces:
- dputs(),
- dprintf(),
- dprintf_colour(),
- dputs_colour(),


The module is called by the following modules:
- PE-CI-001 - Main application module,
- PE-CI-002 - Battery module,
- PE-CI-003 - PE-PI communication module,
- PE-CI-005 - Accelerometer module,
- PE-CI-007 - Message exchange module,
- PE-CI-009 - Power switch module,
- PE-CI-010 - Temperature monitor module,

The module calls the following modules:
- PE-CI-026 - stdarg library
- PE-CI-022 - string library
- PE-CI-023 - stdio library
- PE-CI-019 - stdint library
- PE-CI-020 - stdbool library
- PE-CI-024 - stddef library
- PE-CI-025 - stdlib library
- PE-CI-018 - UART module
- PE-CI-013 - Interrupt manager module
\subsection sec_PE-CI-009 PE-CI-009 - Power switch module
The module consists of the following constituents:
- power_switch_interrupt.c
- power_switch_interrupt.h


Functionality: Provides functionality related to the power switch.


The module provides the following interfaces:
- disabling_uart_modules(),
- get_device_state(),
- is_device_on(),
- delayed_turn_off(),
- turn_off_device(),
- turn_on_device(),


The module is called by the following modules:
- PE-CI-001 - Main application module,
- PE-CI-002 - Battery module,
- PE-CI-007 - Message exchange module,

The module calls the following modules:
- PE-CI-021 - xc library
- PE-CI-003 - PE-PI communication module
- PE-CI-018 - UART module
- PE-CI-001 - Main application module
- PE-CI-008 - Debugging communication module
- PE-CI-007 - Message exchange module
\subsection sec_PE-CI-010 PE-CI-010 - Temperature monitor module
The module consists of the following constituents:
- temperature_monitor.c
- temperature_monitor.h


Functionality: Provides application-level functionality related to the temperature monitoring switch.


The module provides the following interfaces:
- temperature_mon_init(),
- temperature_monitor_min_200ms(),


The module is called by the following modules:
- PE-CI-001 - Main application module,

The module calls the following modules:
- PE-CI-001 - Main application module
- PE-CI-008 - Debugging communication module
- PE-CI-006 - Temperature sensor module
\subsection sec_PE-CI-011 PE-CI-011 - Analog to Digital Converter module
The module consists of the following constituents:
- adc1.c
- adc1.h
- adc_module_features.h


Functionality: Provides driver-level functionality related to the Analog to Digital Converter peripheral.


The module provides the following interfaces:
- ADC1_ChannelSelect(),
- ADC1_ConversionResultGet(),
- ADC1_Disable(),
- ADC1_Enable(),
- ADC1_IsConversionComplete(),
- ADC1_SoftwareTriggerDisable(),
- ADC1_SoftwareTriggerEnable(),
- ADC1_Initialize(),


The module is called by the following modules:
- PE-CI-002 - Battery module,
- PE-CI-016 - System module,

The module calls the following modules:
- PE-CI-021 - xc library
- PE-CI-020 - stdbool library
- PE-CI-019 - stdint library
- PE-CI-025 - stdlib library
\subsection sec_PE-CI-012 PE-CI-012 - Clock module
The module consists of the following constituents:
- clock.c
- clock.h


Functionality: Provides functionality related to system clock.


The module provides the following interfaces:
- CLOCK_Initialize(),


The module is called by the following modules:
- PE-CI-016 - System module,

The module calls the following modules:
- PE-CI-019 - stdint library
- PE-CI-020 - stdbool library
\subsection sec_PE-CI-013 PE-CI-013 - Interrupt manager module
The module consists of the following constituents:
- interrupt_manager.c
- interrupt_manager.h


Functionality: Provides functionality related to interrupt management.


The module provides the following interfaces:
- INTERRUPT_GlobalDisable(),
- INTERRUPT_GlobalEnable(),
- INTERRUPT_Initialize(),


The module is called by the following modules:
- PE-CI-008 - Debugging communication module,
- PE-CI-016 - System module,

The module calls the following modules:
- PE-CI-021 - xc library
\subsection sec_PE-CI-014 PE-CI-014 - System initialisation module
The module consists of the following constituents:
- mcc.c
- mcc.h


Functionality: Provides system initialisation functionality.

The module does not provides any interfaces.


The module is called by the following modules:
- None

The module calls the following modules:
- PE-CI-021 - xc library
- PE-CI-019 - stdint library
- PE-CI-020 - stdbool library
\subsection sec_PE-CI-015 PE-CI-015 - GPIO module
The module consists of the following constituents:
- pin_manager.c
- pin_manager.h


Functionality: Provides GPIO peripheral functionality. This module permits the PE software subsystem support interface with hardware - controls GPIO pins and interfaces with e.g. voltage regulators.


The module provides the following interfaces:
- CHARGE_STAT_SetInterruptHandler(),
- PIN_MANAGER_Initialize(),


The module is called by the following modules:
- PE-CI-002 - Battery module,
- PE-CI-016 - System module,

The module calls the following modules:
- PE-CI-021 - xc library
- PE-CI-023 - stdio library
\subsection sec_PE-CI-016 PE-CI-016 - System module
The module consists of the following constituents:
- system.c
- system.h


Functionality: Provides system initialisation functionality.


The module provides the following interfaces:
- SYSTEM_Initialize(),


The module is called by the following modules:
- PE-CI-001 - Main application module,

The module calls the following modules:
- PE-CI-011 - Analog to Digital Converter module
- PE-CI-002 - Battery module
- PE-CI-012 - Clock module
- PE-CI-013 - Interrupt manager module
- PE-CI-015 - GPIO module
- PE-CI-017 - Timer module
- PE-CI-018 - UART module
\subsection sec_PE-CI-017 PE-CI-017 - Timer module
The module consists of the following constituents:
- tmr1.c
- tmr1.h


Functionality: Provides functionality related to Timer 1 peripheral.


The module provides the following interfaces:
- TMR1_GetElapsedThenClear(),
- TMR1_Start(),
- TMR1_Initialize(),


The module is called by the following modules:
- PE-CI-001 - Main application module,
- PE-CI-016 - System module,

The module calls the following modules:
- PE-CI-023 - stdio library
- PE-CI-021 - xc library
- PE-CI-019 - stdint library
- PE-CI-020 - stdbool library
\subsection sec_PE-CI-018 PE-CI-018 - UART module
The module consists of the following constituents:
- uart2.c
- uart2.h
- uart1.c
- uart1.h


Functionality: Provides UART peripheral functionality. This module permits the PE software subsystem support interface with hardware - controls UART peripheral and communication with PI/debugging port.


The module provides the following interfaces:
- UART2_Write(),
- UART2_Initialize(),


The module is called by the following modules:
- PE-CI-008 - Debugging communication module,
- PE-CI-009 - Power switch module,
- PE-CI-016 - System module,

The module calls the following modules:
- PE-CI-020 - stdbool library
- PE-CI-019 - stdint library
- PE-CI-024 - stddef library
- PE-CI-021 - xc library
\subsection sec_PE-CI-019 PE-CI-019 - stdint library
The module consists of the following constituents:
- stdint.h


Functionality: Standard integer types library.

The module does not provides any interfaces.


The module is called by the following modules:
- PE-CI-003 - PE-PI communication module,
- PE-CI-004 - I2C module,
- PE-CI-007 - Message exchange module,
- PE-CI-008 - Debugging communication module,
- PE-CI-011 - Analog to Digital Converter module,
- PE-CI-012 - Clock module,
- PE-CI-014 - System initialisation module,
- PE-CI-017 - Timer module,
- PE-CI-018 - UART module,

The module calls the following modules:
- None
\subsection sec_PE-CI-020 PE-CI-020 - stdbool library
The module consists of the following constituents:
- stdbool.h


Functionality: Standard boolean types library.

The module does not provides any interfaces.


The module is called by the following modules:
- PE-CI-003 - PE-PI communication module,
- PE-CI-004 - I2C module,
- PE-CI-008 - Debugging communication module,
- PE-CI-011 - Analog to Digital Converter module,
- PE-CI-012 - Clock module,
- PE-CI-014 - System initialisation module,
- PE-CI-017 - Timer module,
- PE-CI-018 - UART module,

The module calls the following modules:
- None
\subsection sec_PE-CI-021 PE-CI-021 - xc library
The module consists of the following constituents:
- xc.h


Functionality: Library providing support for the specific PESS device.

The module does not provides any interfaces.


The module is called by the following modules:
- PE-CI-002 - Battery module,
- PE-CI-004 - I2C module,
- PE-CI-005 - Accelerometer module,
- PE-CI-006 - Temperature sensor module,
- PE-CI-009 - Power switch module,
- PE-CI-011 - Analog to Digital Converter module,
- PE-CI-013 - Interrupt manager module,
- PE-CI-014 - System initialisation module,
- PE-CI-015 - GPIO module,
- PE-CI-017 - Timer module,
- PE-CI-018 - UART module,

The module calls the following modules:
- None
\subsection sec_PE-CI-022 PE-CI-022 - string library
The module consists of the following constituents:
- string.h


Functionality: Library providing string support functions.

The module does not provides any interfaces.


The module is called by the following modules:
- PE-CI-003 - PE-PI communication module,
- PE-CI-007 - Message exchange module,
- PE-CI-008 - Debugging communication module,

The module calls the following modules:
- None
\subsection sec_PE-CI-023 PE-CI-023 - stdio library
The module consists of the following constituents:
- stdio.h


Functionality: Library providing standard I/O support functions.

The module does not provides any interfaces.


The module is called by the following modules:
- PE-CI-008 - Debugging communication module,
- PE-CI-015 - GPIO module,
- PE-CI-017 - Timer module,

The module calls the following modules:
- None
\subsection sec_PE-CI-024 PE-CI-024 - stddef library
The module consists of the following constituents:
- stddef.h


Functionality: Library providing standard definitions.

The module does not provides any interfaces.


The module is called by the following modules:
- PE-CI-003 - PE-PI communication module,
- PE-CI-008 - Debugging communication module,
- PE-CI-018 - UART module,

The module calls the following modules:
- None
\subsection sec_PE-CI-025 PE-CI-025 - stdlib library
The module consists of the following constituents:
- stdlib.h


Functionality: Standard utility functions library.

The module does not provides any interfaces.


The module is called by the following modules:
- PE-CI-003 - PE-PI communication module,
- PE-CI-004 - I2C module,
- PE-CI-008 - Debugging communication module,
- PE-CI-011 - Analog to Digital Converter module,

The module calls the following modules:
- None
\subsection sec_PE-CI-026 PE-CI-026 - stdarg library
The module consists of the following constituents:
- stdarg.h


Functionality: Library providing functionality related to accepting indefinite number of arguments.

The module does not provides any interfaces.


The module is called by the following modules:
- PE-CI-008 - Debugging communication module,

The module calls the following modules:
- None
\section trace_mat_sec Architecture and software requirements
The following table shows how the software requirements map onto the software architecture, and therefore how the architecture implements these requirements.
<table>
<caption id='multi_row'>Requirements traceability matrix</caption>
<tr><th>Software module <th>Requirement ID
<tr><td>PE-CI-001 - Main application module<td>
<tr><td>PE-CI-002 - Battery module<td>
<tr><td>PE-CI-003 - PE-PI communication module<td>
<tr><td>PE-CI-004 - I2C module<td>
<tr><td>PE-CI-005 - Accelerometer module<td>
<tr><td>PE-CI-006 - Temperature sensor module<td>
<tr><td>PE-CI-007 - Message exchange module<td>
<tr><td>PE-CI-008 - Debugging communication module<td>
<tr><td>PE-CI-009 - Power switch module<td>
<tr><td>PE-CI-010 - Temperature monitor module<td>
<tr><td>PE-CI-011 - Analog to Digital Converter module<td>
<tr><td>PE-CI-012 - Clock module<td>
<tr><td>PE-CI-013 - Interrupt manager module<td>
<tr><td>PE-CI-014 - System initialisation module<td>
<tr><td>PE-CI-015 - GPIO module<td>
<tr><td>PE-CI-016 - System module<td>
<tr><td>PE-CI-017 - Timer module<td>
<tr><td>PE-CI-018 - UART module<td>
<tr><td>PE-CI-019 - stdint library<td>
<tr><td>PE-CI-020 - stdbool library<td>
<tr><td>PE-CI-021 - xc library<td>
<tr><td>PE-CI-022 - string library<td>
<tr><td>PE-CI-023 - stdio library<td>
<tr><td>PE-CI-024 - stddef library<td>
<tr><td>PE-CI-025 - stdlib library<td>
<tr><td>PE-CI-026 - stdarg library<td>
</table>
*/
