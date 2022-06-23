/**
\mainpage Software Architecture Documentation
\section arch_overview_sec Architecture overview
\startuml{architecture.png} "Software Architecture Diagram" width=10cm
package "External libraries" {
component [p32mz2064dar169 library\nPI-CI-028] as PICI028 #Chocolate
component [stdint library\nPI-CI-029] as PICI029 #Chocolate
component [stdbool library\nPI-CI-030] as PICI030 #Chocolate
component [xc library\nPI-CI-031] as PICI031 #Chocolate
component [string library\nPI-CI-032] as PICI032 #Chocolate
component [limits library\nPI-CI-033] as PICI033 #Chocolate
component [stddef library\nPI-CI-034] as PICI034 #Chocolate
component [attribs library\nPI-CI-035] as PICI035 #Chocolate
component [types library\nPI-CI-036] as PICI036 #Chocolate
component [math library\nPI-CI-037] as PICI037 #Chocolate
component [stdlib library\nPI-CI-038] as PICI038 #Chocolate
component [stdarg library\nPI-CI-039] as PICI039 #Chocolate
component [stdio library\nPI-CI-040] as PICI040 #Chocolate
component [cp0defs library\nPI-CI-041] as PICI041 #Chocolate
component [kmem library\nPI-CI-042] as PICI042 #Chocolate
component [assert library\nPI-CI-043] as PICI043 #Chocolate
}
package "Application layer" {
component [Main application module\nPI-CI-001] as PICI001 #CornflowerBlue
component [User Interface module\nPI-CI-002] as PICI002 #CornflowerBlue
component [Settings module\nPI-CI-003] as PICI003 #CornflowerBlue
component [Maths module\nPI-CI-013] as PICI013 #CornflowerBlue
component [Message exchange module\nPI-CI-014] as PICI014 #CornflowerBlue
}
package "Driver layer" {
component [Debugging communication module\nPI-CI-004] as PICI004 #CornflowerBlue
component [Delay module\nPI-CI-005] as PICI005 #CornflowerBlue
component [Camera module\nPI-CI-006] as PICI006 #CornflowerBlue
component [SCCB module\nPI-CI-007] as PICI007 #CornflowerBlue
component [Display module\nPI-CI-008] as PICI008 #CornflowerBlue
component [I2C module\nPI-CI-009] as PICI009 #CornflowerBlue
component [LED controller module\nPI-CI-010] as PICI010 #CornflowerBlue
component [Piezo module\nPI-CI-011] as PICI011 #CornflowerBlue
component [Touch controller module\nPI-CI-012] as PICI012 #CornflowerBlue
component [PI-PE communication module\nPI-CI-015] as PICI015 #CornflowerBlue
component [Power management module\nPI-CI-016] as PICI016 #CornflowerBlue
component [Graphics module\nPI-CI-017] as PICI017 #Orange
component [System module\nPI-CI-018] as PICI018 #Orange
component [Exceptions module\nPI-CI-019] as PICI019 #Orange
component [Clock module\nPI-CI-020] as PICI020 #Orange
component [DDR module\nPI-CI-021] as PICI021 #Orange
component [DMA module\nPI-CI-022] as PICI022 #Orange
component [Interrupt manager module\nPI-CI-023] as PICI023 #Orange
component [GPIO module\nPI-CI-024] as PICI024 #Orange
component [Output compare module\nPI-CI-025] as PICI025 #Orange
component [Timer module\nPI-CI-026] as PICI026 #Orange
component [UART module\nPI-CI-027] as PICI027 #Orange
component [PI-PDA communication module\nPI-CI-044] as PICI044 #CornflowerBlue
}
package "Hardware" {
component [Master clock 25MHz\n] as HW001 #LimeGreen
component [Touchscreen controller\n] as HW002 #LimeGreen
component [Backlight module\n] as HW003 #LimeGreen
component [Camera module\n] as HW004 #LimeGreen
component [PDA\n] as HW005 #LimeGreen
component [LCD Module\n] as HW006 #LimeGreen
component [PE\n] as HW007 #LimeGreen
component [Buzzer\n] as HW008 #LimeGreen
component [LED controller\n] as HW009 #LimeGreen
}
[HW001] -right- [PICI019]
[HW002] -right- [PICI011]
[HW003] -right- [PICI024]
[HW004] -right- [PICI021]
[HW005] -right- [PICI026]
[HW006] -right- [PICI016]
[HW007] -right- [PICI026]
[HW008] -right- [PICI024]
[HW009] -right- [PICI008]
[PICI001] -[hidden]down-> [PICI002]
[PICI002] -[hidden]down-> [PICI003]
[PICI003] -[hidden]down-> [PICI013]
[PICI013] -[hidden]down-> [PICI014]
[PICI004] -[hidden]down-> [PICI005]
[PICI005] -[hidden]down-> [PICI006]
[PICI006] -[hidden]down-> [PICI007]
[PICI007] -[hidden]down-> [PICI008]
[PICI008] -[hidden]down-> [PICI009]
[PICI009] -[hidden]down-> [PICI010]
[PICI010] -[hidden]down-> [PICI011]
[PICI011] -[hidden]down-> [PICI012]
[PICI012] -[hidden]down-> [PICI015]
[PICI015] -[hidden]down-> [PICI016]
[PICI016] -[hidden]down-> [PICI017]
[PICI017] -[hidden]down-> [PICI018]
[PICI018] -[hidden]down-> [PICI019]
[PICI019] -[hidden]down-> [PICI020]
[PICI020] -[hidden]down-> [PICI021]
[PICI021] -[hidden]down-> [PICI022]
[PICI022] -[hidden]down-> [PICI023]
[PICI023] -[hidden]down-> [PICI024]
[PICI024] -[hidden]down-> [PICI025]
[PICI025] -[hidden]down-> [PICI026]
[PICI026] -[hidden]down-> [PICI027]
[PICI027] -[hidden]down-> [PICI044]
[HW001] -[hidden]down-> [HW002]
[HW002] -[hidden]down-> [HW003]
[HW003] -[hidden]down-> [HW004]
[HW004] -[hidden]down-> [HW005]
[HW005] -[hidden]down-> [HW006]
[HW006] -[hidden]down-> [HW007]
[HW007] -[hidden]down-> [HW008]
[HW008] -[hidden]down-> [HW009]
[PICI028] -[hidden]down-> [PICI029]
[PICI029] -[hidden]down-> [PICI030]
[PICI030] -[hidden]down-> [PICI031]
[PICI031] -[hidden]down-> [PICI032]
[PICI032] -[hidden]down-> [PICI033]
[PICI033] -[hidden]down-> [PICI034]
[PICI034] -[hidden]down-> [PICI035]
[PICI035] -[hidden]down-> [PICI036]
[PICI036] -[hidden]down-> [PICI037]
[PICI037] -[hidden]down-> [PICI038]
[PICI038] -[hidden]down-> [PICI039]
[PICI039] -[hidden]down-> [PICI040]
[PICI040] -[hidden]down-> [PICI041]
[PICI041] -[hidden]down-> [PICI042]
[PICI042] -[hidden]down-> [PICI043]
[PICI001] <-right-> [PICI018]
[PICI001] -right-> [PICI004]
[PICI001] <-right-> [PICI002]
[PICI001] <-right-> [PICI017]
[PICI001] -right-> [PICI011]
[PICI001] <-right-> [PICI016]
[PICI001] -right-> [PICI006]
[PICI001] <-right-> [PICI014]
[PICI001] <-right-> [PICI012]
[PICI001] -right-> [PICI008]
[PICI001] -right-> [PICI003]
[PICI001] -right-> [PICI010]
[PICI001] -right-> [PICI025]
[PICI001] -right-> [PICI026]
[PICI001] -right-> [PICI020]
[PICI001] -right-> [PICI021]
[PICI001] -right-> [PICI022]
[PICI001] -right-> [PICI009]
[PICI001] <-right-> [PICI023]
[PICI001] -right-> [PICI024]
[PICI001] -right-> [PICI044]
[PICI001] -right-> [PICI015]
[PICI001] -right-> [PICI007]
[PICI001] -right-> [PICI013]
[PICI002] <-right-> [PICI017]
[PICI002] -right-> [PICI004]
[PICI002] -right-> [PICI011]
[PICI002] -right-> [PICI006]
[PICI002] -right-> [PICI003]
[PICI002] -right-> [PICI016]
[PICI002] -right-> [PICI010]
[PICI002] <-right-> [PICI018]
[PICI003] <-right-> [PICI006]
[PICI003] -right-> [PICI004]
[PICI003] <-right-> [PICI014]
[PICI004] -right-> [PICI018]
[PICI006] <-right-> [PICI018]
[PICI006] -right-> [PICI007]
[PICI006] -right-> [PICI004]
[PICI008] -right-> [PICI005]
[PICI010] -right-> [PICI009]
[PICI011] -right-> [PICI026]
[PICI011] <-right-> [PICI017]
[PICI012] -right-> [PICI004]
[PICI012] -right-> [PICI016]
[PICI012] -right-> [PICI017]
[PICI012] -right-> [PICI005]
[PICI012] -right-> [PICI009]
[PICI014] -right-> [PICI004]
[PICI014] -right-> [PICI011]
[PICI014] <-right-> [PICI015]
[PICI014] <-right-> [PICI016]
[PICI015] -right-> [PICI004]
[PICI015] <-right-> [PICI018]
[PICI016] -right-> [PICI004]
[PICI016] -right-> [PICI022]
[PICI016] -right-> [PICI011]
[PICI017] <-right-> [PICI023]
[PICI018] -right-> [PICI022]
[PICI018] <-right-> [PICI023]
[PICI018] -right-> [PICI024]
[PICI018] -right-> [PICI012]
[PICI018] -right-> [PICI010]
[PICI018] -right-> [PICI017]
[PICI018] -right-> [PICI014]
[PICI018] -right-> [PICI011]
[PICI018] -right-> [PICI016]
[PICI023] -right-> [PICI011]
[PICI023] -right-> [PICI004]
[PICI023] -right-> [PICI027]
[PICI023] -right-> [PICI015]
[PICI023] -right-> [PICI006]
[PICI023] -right-> [PICI026]
[PICI044] -right-> [PICI004]
[PICI044] -right-> [PICI024]
\enduml
The Figure Software Architecture Diagram shows a diagram describing interconnections between the modules.
In the Figure, blocks indicated in orange correspond to SOUP modules, blocks indicated in brown correspond to SOUP module external to the main repository (and under configuration management by other means), and blue correspond to all other software modules. Directions of arrows determine inputs and outputs to/from the modules.
\section elem_descr_sec Element Descriptions and Interfaces
\subsection sec_PI-CI-001 PI-CI-001 - Main application module
The module consists of the following constituents:
- app.c
- app.h
- app_function.c
- app_function.h
- main.c
- scan.c
- scan.h
- configuration.h
- definitions.h
- user.h


Functionality: Provides main application framework and functionality.


The module provides the following interfaces:
- scan_reset(),
- scan_get_progress(),
- scan_get_remaining_time_percentage(),
- scan_get_z_position(),
- scan_get_measurement_index(),
- app_exit_configure(),
- app_set_led_brightness(),
- app_set_lcd_brightness(),
- app_send_laser_check_command(),
- app_begin_configure(),
- app_send_zero_offset_command(),
- app_set_time(),
- app_touch_callback(),
- app_update_status(),
- scan_header_received(),
- app_time_callback(),
- app_update_system_clock(),
- app_power_up_callback(),
- app_power_down_callback(),
- app_power_off_callback(),
- app_zero_offset(),
- app_get_time(),
- APP_Tasks(),
- app_frame_received(),


The module is called by the following modules:
- PI-CI-002 - User Interface module,
- PI-CI-012 - Touch controller module,
- PI-CI-014 - Message exchange module,
- PI-CI-016 - Power management module,
- PI-CI-017 - Graphics module,
- PI-CI-018 - System module,
- PI-CI-023 - Interrupt manager module,

The module calls the following modules:
- PI-CI-029 - stdint library
- PI-CI-030 - stdbool library
- PI-CI-034 - stddef library
- PI-CI-038 - stdlib library
- PI-CI-018 - System module
- PI-CI-004 - Debugging communication module
- PI-CI-002 - User Interface module
- PI-CI-017 - Graphics module
- PI-CI-011 - Piezo module
- PI-CI-016 - Power management module
- PI-CI-006 - Camera module
- PI-CI-014 - Message exchange module
- PI-CI-012 - Touch controller module
- PI-CI-008 - Display module
- PI-CI-003 - Settings module
- PI-CI-010 - LED controller module
- PI-CI-025 - Output compare module
- PI-CI-026 - Timer module
- PI-CI-020 - Clock module
- PI-CI-021 - DDR module
- PI-CI-022 - DMA module
- PI-CI-009 - I2C module
- PI-CI-023 - Interrupt manager module
- PI-CI-024 - GPIO module
- PI-CI-044 - PI-PDA communication module
- PI-CI-015 - PI-PE communication module
- PI-CI-007 - SCCB module
- PI-CI-013 - Maths module
\subsection sec_PI-CI-002 PI-CI-002 - User Interface module
The module consists of the following constituents:
- app_ui_state.c
- app_ui_state.h
- camera_settings_screen.c
- camera_settings_screen.h
- device_settings_screen.c
- device_settings_screen.h
- display_settings_screen.c
- display_settings_screen.h
- main_menu.c
- main_menu.h
- scan_settings_screen.c
- scan_settings_screen.h
- time_settings_screen.c
- time_settings_screen.h


Functionality: Provides functionality related to some UI elements - in particular camera settings/device settings/display settings/main menu/scan settings/time settings.


The module provides the following interfaces:
- app_show_main_screen_buttons(),
- show_camera_settings_dialog(),
- app_update_frame(),
- app_update_gui_measurements(),
- app_update_status_bar(),
- app_logo_animation(),
- app_update_error_state(),
- app_set_scan_state(),
- app_update_measurement_value(),
- App_ScanButtonWidget_PressedEvent(),
- App_DeviceSettingsLaserCheckButtonWidget_PressedEvent(),
- App_ScanSettingsCancelButtonWidget_PressedEvent(),
- App_ScanSettingsApplyButtonWidget_PressedEvent(),
- App_ScanSettingsButtonWidget_PressedEvent(),
- App_DisplaySettings_ShowEvent(),
- App_DisplaySettingsMenuButtonWidget_PressedEvent(),
- App_CameraLeftButtonWidget_PressedEvent(),
- App_CameraLeftButtonWidget_ReleasedEvent(),
- App_CameraUpButtonWidget_PressedEvent(),
- App_CameraUpButtonWidget_ReleasedEvent(),
- App_CameraRightButtonWidget_PressedEvent(),
- App_CameraRightButtonWidget_ReleasedEvent(),
- App_CameraDownButtonWidget_PressedEvent(),
- App_CameraDownButtonWidget_ReleasedEvent(),
- App_CameraCancelButtonWidget_PressedEvent(),
- App_CameraApplyButtonWidget_PressedEvent(),
- App_MenuButtonWidget_PressedEvent(),
- App_ZeroOffsetMenuButtonWidget_PressedEvent(),
- App_DeviceSettingsMenuButtonWidget_PressedEvent(),
- App_ScanSettingsMenuButtonWidget_PressedEvent(),
- App_TimeSettingsMenuButtonWidget_PressedEvent(),
- App_CameraSettingsMenuButtonWidget_PressedEvent(),
- App_TimeSettingsupdate_gui(),
- App_TimeSettingsKeyPadWidget_KeyClickEvent(),
- App_TimeSettingsHourTextFieldWidget_TextChangedEvent(),
- App_TimeSettingsMinuteTextFieldWidget_TextChangedEvent(),
- App_TimeSettingsSecondTextFieldWidget_TextChangedEvent(),
- App_TimeSettingsCancelButtonWidget_PressedEvent(),
- App_TimeSettingsSetButtonWidget_PressedEvent(),
- App_TimeSettingsDayTextFieldWidget_TextChangedEvent(),
- App_TimeSettingsMonthTextFieldWidget_TextChangedEvent(),
- App_TimeSettingsYearTextFieldWidget_TextChangedEvent(),
- App_DeviceSettingsLEDSliderWidget_ValueChangedEvent(),
- App_DeviceSettingsLcdSliderWidget_ValueChangedEvent(),
- App_DeviceSettingsCancelButtonWidget_PressedEvent(),
- App_DeviceSettingsApplyButtonWidget_PressedEvent(),
- App_DeviceSettingsIllu50PercentCheckbox_CheckedEvent(),
- App_DeviceSettingsIllu100PercentCheckbox_CheckedEvent(),
- App_DeviceSettings_ShowEvent(),
- App_DeviceSettingsLaserPowerSliderWidget_ValueChangedEvent(),
- App_DeviceSettingsPeak2AmplitudeSliderWidget_ValueChangedEvent(),
- App_ScanSettings_ShowEvent(),
- App_ComparatorRefSliderWidget_ValueChangedEvent(),
- App_Peak1ThresholdSliderWidget_ValueChangedEvent(),
- App_Peak2ThresholdSliderWidget_ValueChangedEvent(),
- App_MinSeparationSliderWidget_ValueChangedEvent(),
- App_MaxSeparationSliderWidget_ValueChangedEvent(),
- App_ShowSummaryButtonWidget_PressedEvent(),
- App_ShowSummaryButtonWidget_ReleasedEvent(),
- App_IPScanSelectionButtonWidget_PressedEvent(),
- App_IPScanSelectionButtonWidget_ReleasedEvent(),
- App_DSPScanSelectionButtonWidget_PressedEvent(),
- App_DSPScanSelectionButtonWidget_ReleasedEvent(),
- App_TotalScansSliderWidget_ValueChangedEvent(),
- App_BoostGainSliderWidget_ValueChangedEvent(),
- App_MinFwhmSliderWidget_ValueChangedEvent(),
- App_MaxFwhmSliderWidget_ValueChangedEvent(),
- App_PupilFindingButtonWidget_PressedEvent(),
- App_PupilFindingButtonWidget_ReleasedEvent(),
- App_DisplaySettingsCancelButtonWidget_PressedEvent(),
- App_DisplaySettingsApplyButtonWidget_PressedEvent(),
- App_PK1TargetRadiusSliderWidget_ValueChangedEvent(),
- App_ShowGraphButtonWidget_PressedEvent(),
- App_ShowGraphButtonWidget_ReleasedEvent(),
- App_ShowAlignmentUiButtonWidget_PressedEvent(),
- App_ShowAlignmentUiButtonWidget_ReleasedEvent(),
- App_PK1RadiusToleranceSliderWidget_ValueChangedEvent(),
- App_RefractiveIndexSliderWidget_ValueChangedEvent(),
- App_PupilGradientThresholdSliderWidget_ValueChangedEvent(),
- App_PK1AlignmentToleranceSliderWidget_ValueChangedEvent(),
- main_menu_task(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-017 - Graphics module,
- PI-CI-018 - System module,

The module calls the following modules:
- PI-CI-017 - Graphics module
- PI-CI-004 - Debugging communication module
- PI-CI-011 - Piezo module
- PI-CI-006 - Camera module
- PI-CI-001 - Main application module
- PI-CI-003 - Settings module
- PI-CI-016 - Power management module
- PI-CI-010 - LED controller module
- PI-CI-018 - System module
\subsection sec_PI-CI-003 PI-CI-003 - Settings module
The module consists of the following constituents:
- settings.c
- settings.h


Functionality: Provides functionality related to settings.


The module provides the following interfaces:
- set_default_settings(),
- settings_get_lcd_brightness(),
- settings_get_led_brightness(),
- settings_get_amplifier_gain(),
- settings_get_comparator_reference_voltage(),
- settings_get_laser_power(),
- settings_get_maximum_fwhm(),
- settings_get_maximum_separation(),
- settings_get_minimum_fwhm(),
- settings_get_minimum_separation(),
- settings_get_peak_1_threshold_voltage(),
- settings_get_peak_2_threshold_voltage(),
- settings_get_total_scans(),
- settings_get_refractive_index(),
- settings_get_pk1_alignment_tolerance(),
- settings_get_pk1_radius_tolerance(),
- settings_get_pk1_target_radius(),
- settings_get_pupil_gradient_threshold(),
- settings_get_wait_for_alignment(),
- save_settings(),
- settings_set_camera_hstart(),
- settings_set_camera_vstart(),
- settings_get_illumination_max(),
- settings_set_bluetooth_enabled(),
- settings_set_laser_power(),
- settings_set_lcd_brightness(),
- settings_set_led_brightness(),
- settings_set_peak_2_threshold_voltage(),
- settings_set_wait_for_alignment(),
- settings_set_illumination_max(),
- settings_get_bluetooth_enabled(),
- settings_get_show_alignment_ui(),
- settings_get_show_scan_graph(),
- settings_get_show_scan_summary(),
- settings_set_pk1_alignment_tolerance(),
- settings_set_pk1_radius_tolerance(),
- settings_set_pk1_target_radius(),
- settings_set_show_alignment_ui(),
- settings_set_show_scan_graph(),
- settings_set_show_scan_summary(),
- settings_get_dsp_scan_selection(),
- settings_get_pupil_finding(),
- settings_set_comparator_reference_voltage(),
- settings_set_dsp_scan_selection(),
- settings_set_maximum_fwhm(),
- settings_set_maximum_separation(),
- settings_set_minimum_fwhm(),
- settings_set_minimum_separation(),
- settings_set_peak_1_threshold_voltage(),
- settings_set_pupil_finding(),
- settings_set_total_scans(),
- settings_get_camera_hstart(),
- settings_get_camera_vstart(),
- update_settings_from_PDAB(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-002 - User Interface module,
- PI-CI-006 - Camera module,
- PI-CI-014 - Message exchange module,

The module calls the following modules:
- PI-CI-006 - Camera module
- PI-CI-004 - Debugging communication module
- PI-CI-014 - Message exchange module
\subsection sec_PI-CI-004 PI-CI-004 - Debugging communication module
The module consists of the following constituents:
- debug.c
- debug.h


Functionality: Provides functionality related to debugging communication.


The module provides the following interfaces:
- dputs_colour(),
- dprintf_colour(),
- dprintf(),
- debug_initialise(),
- log_elapsed_time(),
- logging_start_timer(),
- dputs(),
- buffer_empty(),
- debug_millisecond_timer_interrupt(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-002 - User Interface module,
- PI-CI-003 - Settings module,
- PI-CI-006 - Camera module,
- PI-CI-012 - Touch controller module,
- PI-CI-014 - Message exchange module,
- PI-CI-015 - PI-PE communication module,
- PI-CI-016 - Power management module,
- PI-CI-023 - Interrupt manager module,
- PI-CI-044 - PI-PDA communication module,

The module calls the following modules:
- PI-CI-040 - stdio library
- PI-CI-018 - System module
\subsection sec_PI-CI-005 PI-CI-005 - Delay module
The module consists of the following constituents:
- delay.c
- delay.h


Functionality: Provides functionality related to generating delays.


The module provides the following interfaces:
- DelayNs(),
- DelayMs(),


The module is called by the following modules:
- PI-CI-008 - Display module,
- PI-CI-012 - Touch controller module,

The module calls the following modules:
- None
\subsection sec_PI-CI-006 PI-CI-006 - Camera module
The module consists of the following constituents:
- drv_camera_ovm7692.c
- drv_camera_ovm7692.h
- drv_camera.h


Functionality: Provides driver-level functionality related to camera.


The module provides the following interfaces:
- DRV_CAMERA_OVM7692_Is_Paused(),
- DRV_CAMERA_OVM7692_Resume(),
- DRV_CAMERA_OVM7692_Open(),
- DRV_CAMERA_OVM7692_Pause(),
- DRV_CAMERA_OVM7692_Initialize(),
- DRV_CAMERA_OVM7692_Set_Position(),
- DRV_CAMERA_OVM7692_Get_Position(),
- DRV_CAMERA_OVM7692_Tasks(),
- DRV_CAMERA_OVM7692_VsyncEventHandler(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-002 - User Interface module,
- PI-CI-003 - Settings module,
- PI-CI-018 - System module,
- PI-CI-023 - Interrupt manager module,

The module calls the following modules:
- PI-CI-029 - stdint library
- PI-CI-030 - stdbool library
- PI-CI-042 - kmem library
- PI-CI-018 - System module
- PI-CI-007 - SCCB module
- PI-CI-004 - Debugging communication module
- PI-CI-003 - Settings module
\subsection sec_PI-CI-007 PI-CI-007 - SCCB module
The module consists of the following constituents:
- drv_camera_sccb.c
- drv_camera_sccb.h


Functionality: Provides HAL-level functionality related to SCCB communication with the camera module.


The module provides the following interfaces:
- SCCB_Initialize(),
- SCCB_Write(),
- SCCB_Read(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-006 - Camera module,

The module calls the following modules:
- PI-CI-029 - stdint library
- PI-CI-030 - stdbool library
- PI-CI-034 - stddef library
- PI-CI-038 - stdlib library
\subsection sec_PI-CI-008 PI-CI-008 - Display module
The module consists of the following constituents:
- drv_display_ST7701S.c
- drv_display_ST7701S.h


Functionality: Provides functionality related to LCD controller ST7701S.


The module provides the following interfaces:
- drv_display_set_enable(),
- ST7701S_Init(),


The module is called by the following modules:
- PI-CI-001 - Main application module,

The module calls the following modules:
- PI-CI-005 - Delay module
\subsection sec_PI-CI-009 PI-CI-009 - I2C module
The module consists of the following constituents:
- drv_i2c2.c
- drv_i2c2.h
- drv_i2c3.c
- drv_i2c3.h


Functionality: Provides driver-level functionality related to I2C communication.


The module provides the following interfaces:
- DRV_I2C2_Initialize(),
- DRV_I2C3_Initialize(),
- DRV_I2C2_Write_Bytes(),
- DRV_I2C3_Read_Bytes_Word_Register(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-010 - LED controller module,
- PI-CI-012 - Touch controller module,

The module calls the following modules:
- None
\subsection sec_PI-CI-010 PI-CI-010 - LED controller module
The module consists of the following constituents:
- drv_led_pca9530.c
- drv_led_pca9530.h


Functionality: Provides driver-level functionality related to the LED controller PCA9530.


The module provides the following interfaces:
- set_pca9530_led_pwm0_rate(),
- set_pca9530_led_pwm1_rate(),
- set_pca9530_led0_off(),
- set_pca9530_led0_pwm1(),
- set_pca9530_led1_off(),
- set_pca9530_led1_pwm1(),
- set_pca9530_led0_on(),
- set_pca9530_led1_on(),
- drv_pca9530_led_controller_task(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-002 - User Interface module,
- PI-CI-018 - System module,

The module calls the following modules:
- PI-CI-009 - I2C module
\subsection sec_PI-CI-011 PI-CI-011 - Piezo module
The module consists of the following constituents:
- drv_piezo.c
- drv_piezo.h


Functionality: Provides functionality related to the piezo buzzer.


The module provides the following interfaces:
- piezo_two_tone(),
- play_notification(),
- piezo_pulse(),
- notification_tasks(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-002 - User Interface module,
- PI-CI-014 - Message exchange module,
- PI-CI-016 - Power management module,
- PI-CI-017 - Graphics module,
- PI-CI-018 - System module,
- PI-CI-023 - Interrupt manager module,

The module calls the following modules:
- PI-CI-026 - Timer module
- PI-CI-017 - Graphics module
\subsection sec_PI-CI-012 PI-CI-012 - Touch controller module
The module consists of the following constituents:
- drv_touch_cst130.c
- drv_touch_cst130.h


Functionality: Provides functionality related to the touch controller CST130.


The module provides the following interfaces:
- drv_cst130_touch_callback_set(),
- drv_cst130_touch_controller_task(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-018 - System module,

The module calls the following modules:
- PI-CI-029 - stdint library
- PI-CI-034 - stddef library
- PI-CI-030 - stdbool library
- PI-CI-004 - Debugging communication module
- PI-CI-016 - Power management module
- PI-CI-017 - Graphics module
- PI-CI-001 - Main application module
- PI-CI-005 - Delay module
- PI-CI-009 - I2C module
\subsection sec_PI-CI-013 PI-CI-013 - Maths module
The module consists of the following constituents:
- maths_library.c
- maths_library.h
- npda.h


Functionality: Provides mathematical functions.


The module provides the following interfaces:
- calculate_mean(),
- calculate_stdev(),
- find_circle_points(),
- fit_circle_float(),
- find_rectangle(),


The module is called by the following modules:
- PI-CI-001 - Main application module,

The module calls the following modules:
- PI-CI-029 - stdint library
- PI-CI-030 - stdbool library
- PI-CI-034 - stddef library
- PI-CI-038 - stdlib library
- PI-CI-037 - math library
\subsection sec_PI-CI-014 PI-CI-014 - Message exchange module
The module consists of the following constituents:
- message_exchange.c
- message_exchange.h


Functionality: Provides application-level functionality related to communication with PDA PESS.


The module provides the following interfaces:
- pic24_send_command(),
- send_command_to_PDAB(),
- process_PDAB_status_message(),
- process_request_settings_message(),
- process_request_shutdown_message(),
- process_scan_data_message(),
- process_scan_status_message(),
- process_pic24_is_safe_to_shutdown_message(),
- process_pic24_status_message(),
- process_pic24_version_message(),
- process_pic24_wakeup_message(),
- message_exchange_task(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-003 - Settings module,
- PI-CI-015 - PI-PE communication module,
- PI-CI-016 - Power management module,
- PI-CI-018 - System module,

The module calls the following modules:
- PI-CI-032 - string library
- PI-CI-004 - Debugging communication module
- PI-CI-001 - Main application module
- PI-CI-011 - Piezo module
- PI-CI-003 - Settings module
- PI-CI-015 - PI-PE communication module
- PI-CI-016 - Power management module
\subsection sec_PI-CI-015 PI-CI-015 - PI-PE communication module
The module consists of the following constituents:
- pic24_comms.c
- pic24_comms.h


Functionality: Provides driver-level functionality related to the communication with the PE PESS.


The module provides the following interfaces:
- pic24_communications_init(),
- pic24_comms_task(),
- pic24_comms_queue_message(),
- rx_buffer_add(),
- rx_buffer_full(),
- UART5_ErrorClear(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-014 - Message exchange module,
- PI-CI-018 - System module,
- PI-CI-023 - Interrupt manager module,

The module calls the following modules:
- PI-CI-004 - Debugging communication module
- PI-CI-014 - Message exchange module
- PI-CI-018 - System module
\subsection sec_PI-CI-016 PI-CI-016 - Power management module
The module consists of the following constituents:
- power_management.c
- power_management.h


Functionality: Provides functionality related to the power management.


The module provides the following interfaces:
- check_if_pwr_coms_quiet_window(),
- power_management_suspend(),
- power_down_callback_set(),
- power_off_callback_set(),
- power_up_callback_set(),
- reset_sleep_counter(),
- power_management_activity_trigger(),
- app_send_power_down_request(),
- power_management_task(),
- get_millisecond_timer_value(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-002 - User Interface module,
- PI-CI-012 - Touch controller module,
- PI-CI-014 - Message exchange module,
- PI-CI-018 - System module,

The module calls the following modules:
- PI-CI-001 - Main application module
- PI-CI-004 - Debugging communication module
- PI-CI-022 - DMA module
- PI-CI-011 - Piezo module
- PI-CI-014 - Message exchange module
\subsection sec_PI-CI-017 PI-CI-017 - Graphics module
The module consists of the following constituents:
- libnano2D_hal.c
- drv_gfx_glcd.c
- plib_glcd.c
- gfx_assets.c
- gfx.c
- gfx_color.c
- gfx_color_blend.c
- gfx_color_convert.c
- gfx_color_lerp.c
- gfx_color_value.c
- gfx_context.c
- gfx_default_impl.c
- gfx_display.c
- gfx_display_def.c
- gfx_draw_arc.c
- gfx_draw_blit.c
- gfx_draw_circle.c
- gfx_draw_ellipse.c
- gfx_draw_line.c
- gfx_draw_pixel.c
- gfx_draw_rect.c
- gfx_draw_stretchblit.c
- gfx_driver_def.c
- gfx_driver_interface.c
- gfx_get.c
- gfx_interface.c
- gfx_layer.c
- gfx_math.c
- gfx_pixel_buffer.c
- gfx_processor_def.c
- gfx_processor_interface.c
- gfx_rect.c
- gfx_set.c
- gfx_util.c
- libaria.c
- libaria_array.c
- libaria_context.c
- libaria_context_paint.c
- libaria_draw.c
- libaria_editwidget.c
- libaria_event.c
- libaria_events.c
- libaria_harmony.c
- libaria_init.c
- libaria_input.c
- libaria_layer.c
- libaria_list.c
- libaria_macros.c
- libaria_radiobutton_group.c
- libaria_rectarray.c
- libaria_scheme.c
- libaria_screen.c
- libaria_string.c
- libaria_utils.c
- libaria_widget.c
- libaria_widget_arc.c
- libaria_widget_arc_skin_classic.c
- libaria_widget_bar_graph.c
- libaria_widget_bar_graph_skin_classic.c
- libaria_widget_button.c
- libaria_widget_button_skin_classic.c
- libaria_widget_checkbox.c
- libaria_widget_checkbox_skin_classic.c
- libaria_widget_circle.c
- libaria_widget_circle_skin_classic.c
- libaria_widget_circular_gauge.c
- libaria_widget_circular_gauge_skin_classic.c
- libaria_widget_circular_slider.c
- libaria_widget_circular_slider_skin_classic.c
- libaria_widget_drawsurface.c
- libaria_widget_drawsurface_skin_classic.c
- libaria_widget_gradient.c
- libaria_widget_gradient_skin_classic.c
- libaria_widget_groupbox.c
- libaria_widget_groupbox_skin_classic.c
- libaria_widget_image.c
- libaria_widget_image_skin_classic.c
- libaria_widget_imageplus.c
- libaria_widget_imageplus_skin_classic.c
- libaria_widget_imagesequence.c
- libaria_widget_imagesequence_skin_classic.c
- libaria_widget_keypad.c
- libaria_widget_keypad_skin_classic.c
- libaria_widget_label.c
- libaria_widget_label_skin_classic.c
- libaria_widget_line.c
- libaria_widget_line_graph.c
- libaria_widget_line_graph_skin_classic.c
- libaria_widget_line_skin_classic.c
- libaria_widget_list.c
- libaria_widget_list_skin_classic.c
- libaria_widget_listwheel.c
- libaria_widget_listwheel_skin_classic.c
- libaria_widget_pie_chart.c
- libaria_widget_pie_chart_skin_classic.c
- libaria_widget_progressbar.c
- libaria_widget_progressbar_skin_classic.c
- libaria_widget_radial_menu.c
- libaria_widget_radial_menu_skin_classic.c
- libaria_widget_radiobutton.c
- libaria_widget_radiobutton_skin_classic.c
- libaria_widget_rectangle.c
- libaria_widget_rectangle_skin_classic.c
- libaria_widget_scrollbar.c
- libaria_widget_scrollbar_skin_classic.c
- libaria_widget_skin_classic.c
- libaria_widget_skin_classic_common.c
- libaria_widget_slider.c
- libaria_widget_slider_skin_classic.c
- libaria_widget_textfield.c
- libaria_widget_textfield_skin_classic.c
- libaria_widget_touchtest.c
- libaria_widget_touchtest_skin_classic.c
- libaria_widget_window.c
- libaria_widget_window_skin_classic.c
- lodepng.c
- gfxu_image.c
- gfxu_image_raw_external.c
- gfxu_image_raw_internal.c
- gfxu_image_rle_external.c
- gfxu_image_rle_internal.c
- gfxu_image_utils.c
- gfxu_palette.c
- gfxu_string.c
- gfxu_string_external.c
- gfxu_string_internal.c
- gfxu_string_query.c
- gfxu_string_utils.c
- gfxu_stringbuffer_external.c
- gfxu_image_png_external.c
- gfxu_image_png_internal.c
- libnano2D.h
- drv_gfx_glcd.h
- plib_glcd.h
- gfx_assets.h
- gfx.h
- gfx_color.h
- gfx_common.h
- gfx_config.h
- gfx_context.h
- gfx_default_impl.h
- gfx_display.h
- gfx_draw.h
- gfx_draw_arc.h
- gfx_draw_blit.h
- gfx_draw_circle.h
- gfx_draw_ellipse.h
- gfx_draw_line.h
- gfx_draw_pixel.h
- gfx_draw_rect.h
- gfx_draw_stretchblit.h
- gfx_driver_interface.h
- gfx_hal.h
- gfx_interface.h
- gfx_layer.h
- gfx_math.h
- gfx_pixel_buffer.h
- gfx_processor_interface.h
- gfx_rect.h
- gfx_util.h
- libaria.h
- libaria_array.h
- libaria_common.h
- libaria_config.h
- libaria_context.h
- libaria_draw.h
- libaria_editwidget.h
- libaria_event.h
- libaria_events.h
- libaria_global.h
- libaria_harmony.h
- libaria_init.h
- libaria_input.h
- libaria_layer.h
- libaria_list.h
- libaria_macros.h
- libaria_math.h
- libaria_radiobutton_group.h
- libaria_rectarray.h
- libaria_scheme.h
- libaria_screen.h
- libaria_string.h
- libaria_utils.h
- libaria_widget.h
- libaria_widget_arc.h
- libaria_widget_bar_graph.h
- libaria_widget_button.h
- libaria_widget_checkbox.h
- libaria_widget_circle.h
- libaria_widget_circular_gauge.h
- libaria_widget_circular_slider.h
- libaria_widget_drawsurface.h
- libaria_widget_gradient.h
- libaria_widget_groupbox.h
- libaria_widget_image.h
- libaria_widget_imageplus.h
- libaria_widget_imagesequence.h
- libaria_widget_keypad.h
- libaria_widget_label.h
- libaria_widget_line.h
- libaria_widget_line_graph.h
- libaria_widget_list.h
- libaria_widget_listwheel.h
- libaria_widget_pie_chart.h
- libaria_widget_progressbar.h
- libaria_widget_radial_menu.h
- libaria_widget_radiobutton.h
- libaria_widget_rectangle.h
- libaria_widget_scrollbar.h
- libaria_widget_skin_classic_common.h
- libaria_widget_slider.h
- libaria_widget_textfield.h
- libaria_widget_touchtest.h
- libaria_widget_window.h
- lodepng.h
- gfx_utils.h
- gfxu_config.h
- gfxu_binary.h
- gfxu_font.h
- gfxu_global.h
- gfxu_image.h
- gfxu_image_utils.h
- gfxu_palette.h
- gfxu_string.h
- gfxu_string_utils.h


Functionality: Provides functionality related to the graphics.


The module provides the following interfaces:
- laWidget_SetEnabled(),
- laString_CreateFromCharBuffer(),
- laString_Destroy(),
- laWidget_SetVisible(),
- laContext_GetActiveScreenIndex(),
- laContext_SetActiveScreen(),
- GFX_Initialize(),
- LibAria_Initialize(),
- laWidget_Translate(),
- laWidget_Invalidate(),
- laWidget_SetScheme(),
- laWidget_SetY(),
- laWidget_SetAlphaAmount(),
- laString_Length(),
- laString_ReduceLength(),
- laWidget_SetFocus(),
- laString_ToCharBuffer(),
- update(),
- GFX_Update(),
- LibAria_Tasks(),
- GFX_ActiveContext(),
- GFX_LayerSwap(),
- PLIB_GLCD_LayerGlobalAlphaSet(),
- PLIB_GLCD_VSyncInterruptDisable(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-002 - User Interface module,
- PI-CI-011 - Piezo module,
- PI-CI-012 - Touch controller module,
- PI-CI-018 - System module,
- PI-CI-023 - Interrupt manager module,

The module calls the following modules:
- PI-CI-029 - stdint library
- PI-CI-030 - stdbool library
- PI-CI-038 - stdlib library
- PI-CI-032 - string library
- PI-CI-034 - stddef library
- PI-CI-039 - stdarg library
- PI-CI-037 - math library
- PI-CI-028 - p32mz2064dar169 library
- PI-CI-031 - xc library
- PI-CI-035 - attribs library
- PI-CI-042 - kmem library
- PI-CI-033 - limits library
- PI-CI-040 - stdio library
- PI-CI-023 - Interrupt manager module
- PI-CI-011 - Piezo module
- PI-CI-001 - Main application module
- PI-CI-002 - User Interface module
\subsection sec_PI-CI-018 PI-CI-018 - System module
The module consists of the following constituents:
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
- SYS_TIME_DelayMS(),
- SYS_TIME_DelayIsComplete(),
- SYS_INT_Disable(),
- SYS_INT_Restore(),
- SYS_TIME_Initialize(),
- loop_1ms(),
- SYS_Tasks(),
- SYS_TIME_CallbackRegisterMS(),
- SYS_TIME_TimerDestroy(),
- SYS_TIME_CountToMS(),
- SYS_TIME_TimerCounterGet(),
- SYS_TIME_TimerPeriodHasExpired(),
- SYS_PORT_PinWrite(),
- SYS_INT_SourceDisable(),
- SYS_INT_SourceEnable(),
- SYS_INT_SourceStatusClear(),
- SYS_DMA_AddressingModeSetup(),
- SYS_DMA_ChannelCallbackRegister(),
- SYS_DMA_DataWidthSetup(),
- SYS_PORT_PinClear(),
- SYS_PORT_PinOutputEnable(),
- SYS_PORT_PinSet(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-002 - User Interface module,
- PI-CI-004 - Debugging communication module,
- PI-CI-006 - Camera module,
- PI-CI-015 - PI-PE communication module,
- PI-CI-023 - Interrupt manager module,

The module calls the following modules:
- PI-CI-034 - stddef library
- PI-CI-029 - stdint library
- PI-CI-030 - stdbool library
- PI-CI-032 - string library
- PI-CI-043 - assert library
- PI-CI-036 - types library
- PI-CI-022 - DMA module
- PI-CI-023 - Interrupt manager module
- PI-CI-024 - GPIO module
- PI-CI-001 - Main application module
- PI-CI-006 - Camera module
- PI-CI-012 - Touch controller module
- PI-CI-010 - LED controller module
- PI-CI-017 - Graphics module
- PI-CI-002 - User Interface module
- PI-CI-014 - Message exchange module
- PI-CI-011 - Piezo module
- PI-CI-015 - PI-PE communication module
- PI-CI-016 - Power management module
\subsection sec_PI-CI-019 PI-CI-019 - Exceptions module
The module consists of the following constituents:
- exceptions.c


Functionality: Provides functionality related to exceptions.

The module does not provides any interfaces.


The module is called by the following modules:
- None

The module calls the following modules:
- PI-CI-040 - stdio library
\subsection sec_PI-CI-020 PI-CI-020 - Clock module
The module consists of the following constituents:
- plib_clk.c
- plib_clk.h


Functionality: Provides functionality related to clock.


The module provides the following interfaces:
- CLK_Initialize(),


The module is called by the following modules:
- PI-CI-001 - Main application module,

The module calls the following modules:
- PI-CI-034 - stddef library
- PI-CI-030 - stdbool library
\subsection sec_PI-CI-021 PI-CI-021 - DDR module
The module consists of the following constituents:
- plib_ddr.c
- plib_ddr.h


Functionality: Provides functionality related to DDR memory.


The module provides the following interfaces:
- DDR_Initialize(),


The module is called by the following modules:
- PI-CI-001 - Main application module,

The module calls the following modules:
- PI-CI-034 - stddef library
- PI-CI-030 - stdbool library
- PI-CI-029 - stdint library
\subsection sec_PI-CI-022 PI-CI-022 - DMA module
The module consists of the following constituents:
- plib_dmac.c
- plib_dmac.h


Functionality: Provides functionality related to the Dynamic Memory Access.


The module provides the following interfaces:
- DMAC_Initialize(),
- DMAC_ChannelDisable(),
- DMAC_ChannelTransfer(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-016 - Power management module,
- PI-CI-018 - System module,

The module calls the following modules:
- PI-CI-028 - p32mz2064dar169 library
- PI-CI-032 - string library
- PI-CI-030 - stdbool library
- PI-CI-042 - kmem library
\subsection sec_PI-CI-023 PI-CI-023 - Interrupt manager module
The module consists of the following constituents:
- plib_evic.c
- plib_evic.h
- interrupts.c


Functionality: Provides functionality related to interrupt management.


The module provides the following interfaces:
- EVIC_Initialize(),
- EVIC_SourceEnable(),
- EVIC_SourceStatusClear(),
- EVIC_SourceDisable(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-017 - Graphics module,
- PI-CI-018 - System module,

The module calls the following modules:
- PI-CI-028 - p32mz2064dar169 library
- PI-CI-034 - stddef library
- PI-CI-030 - stdbool library
- PI-CI-011 - Piezo module
- PI-CI-004 - Debugging communication module
- PI-CI-027 - UART module
- PI-CI-015 - PI-PE communication module
- PI-CI-017 - Graphics module
- PI-CI-018 - System module
- PI-CI-001 - Main application module
- PI-CI-006 - Camera module
- PI-CI-026 - Timer module
\subsection sec_PI-CI-024 PI-CI-024 - GPIO module
The module consists of the following constituents:
- plib_gpio.c
- plib_gpio.h


Functionality: Provides GPIO peripheral functionality.


The module provides the following interfaces:
- GPIO_Initialize(),
- GPIO_PinWrite(),
- GPIO_PinRead(),
- GPIO_PinLatchRead(),
- GPIO_PinToggle(),
- GPIO_PinSet(),
- GPIO_PinClear(),
- GPIO_PinInputEnable(),
- GPIO_PinOutputEnable(),
- GPIO_PinInterruptCallbackRegister(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-018 - System module,
- PI-CI-044 - PI-PDA communication module,

The module calls the following modules:
- PI-CI-028 - p32mz2064dar169 library
- PI-CI-029 - stdint library
- PI-CI-030 - stdbool library
- PI-CI-034 - stddef library
\subsection sec_PI-CI-025 PI-CI-025 - Output compare module
The module consists of the following constituents:
- plib_ocmp1.c
- plib_ocmp1.h
- plib_ocmp3.c
- plib_ocmp3.h


Functionality: Provides functionality related to PWM.


The module provides the following interfaces:
- OCMP3_CompareSecondaryValueSet(),
- OCMP3_Disable(),
- OCMP3_Enable(),
- OCMP1_Initialize(),
- OCMP3_Initialize(),


The module is called by the following modules:
- PI-CI-001 - Main application module,

The module calls the following modules:
- PI-CI-034 - stddef library
- PI-CI-030 - stdbool library
- PI-CI-029 - stdint library
\subsection sec_PI-CI-026 PI-CI-026 - Timer module
The module consists of the following constituents:
- plib_tmr2.c
- plib_tmr2.h
- plib_tmr3.c
- plib_tmr3.h
- plib_tmr4.c
- plib_tmr4.h


Functionality: Provides functionality related to the Timer peripherals.


The module provides the following interfaces:
- TMR2_Start(),
- TMR2_Stop(),
- TMR2_Initialize(),
- TMR3_Initialize(),
- TMR4_Initialize(),
- TMR4_InterruptEnable(),
- TMR4_PeriodSet(),
- TMR4_Start(),
- TMR4_Stop(),
- TIMER_4_InterruptHandler(),


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-011 - Piezo module,
- PI-CI-023 - Interrupt manager module,

The module calls the following modules:
- PI-CI-034 - stddef library
- PI-CI-029 - stdint library
\subsection sec_PI-CI-027 PI-CI-027 - UART module
The module consists of the following constituents:
- plib_uart1.c
- plib_uart1.h
- plib_uart3.c
- plib_uart3.h
- plib_uart4.c
- plib_uart4.h
- plib_uart_common.h


Functionality: Provides functionality related to the UART peripherals.


The module provides the following interfaces:
- UART3_ErrorClear(),


The module is called by the following modules:
- PI-CI-023 - Interrupt manager module,

The module calls the following modules:
- PI-CI-034 - stddef library
- PI-CI-030 - stdbool library
- PI-CI-029 - stdint library
\subsection sec_PI-CI-028 PI-CI-028 - p32mz2064dar169 library
The module consists of the following constituents:
- p32mz2064dar169.h
- device.h


Functionality: Generic utility functions for PIC32MZ2064DAR169.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-017 - Graphics module,
- PI-CI-022 - DMA module,
- PI-CI-023 - Interrupt manager module,
- PI-CI-024 - GPIO module,

The module calls the following modules:
- PI-CI-031 - xc library
- PI-CI-035 - attribs library
\subsection sec_PI-CI-029 PI-CI-029 - stdint library
The module consists of the following constituents:
- stdint.h


Functionality: Standard integer types library.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-006 - Camera module,
- PI-CI-007 - SCCB module,
- PI-CI-012 - Touch controller module,
- PI-CI-013 - Maths module,
- PI-CI-017 - Graphics module,
- PI-CI-018 - System module,
- PI-CI-021 - DDR module,
- PI-CI-024 - GPIO module,
- PI-CI-025 - Output compare module,
- PI-CI-026 - Timer module,
- PI-CI-027 - UART module,

The module calls the following modules:
- None
\subsection sec_PI-CI-030 PI-CI-030 - stdbool library
The module consists of the following constituents:
- stdbool.h


Functionality: Standard boolean types library.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-006 - Camera module,
- PI-CI-007 - SCCB module,
- PI-CI-012 - Touch controller module,
- PI-CI-013 - Maths module,
- PI-CI-017 - Graphics module,
- PI-CI-018 - System module,
- PI-CI-020 - Clock module,
- PI-CI-021 - DDR module,
- PI-CI-022 - DMA module,
- PI-CI-023 - Interrupt manager module,
- PI-CI-024 - GPIO module,
- PI-CI-025 - Output compare module,
- PI-CI-027 - UART module,

The module calls the following modules:
- None
\subsection sec_PI-CI-031 PI-CI-031 - xc library
The module consists of the following constituents:
- xc.h


Functionality: Library providing support for the specific PESS device.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-017 - Graphics module,
- PI-CI-028 - p32mz2064dar169 library,

The module calls the following modules:
- None
\subsection sec_PI-CI-032 PI-CI-032 - string library
The module consists of the following constituents:
- string.h


Functionality: Library providing string support functions.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-014 - Message exchange module,
- PI-CI-017 - Graphics module,
- PI-CI-018 - System module,
- PI-CI-022 - DMA module,

The module calls the following modules:
- None
\subsection sec_PI-CI-033 PI-CI-033 - limits library
The module consists of the following constituents:
- limits.h


Functionality: Library providing limits for common variable types.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-017 - Graphics module,

The module calls the following modules:
- None
\subsection sec_PI-CI-034 PI-CI-034 - stddef library
The module consists of the following constituents:
- stddef.h


Functionality: Library providing standard definitions.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-007 - SCCB module,
- PI-CI-012 - Touch controller module,
- PI-CI-013 - Maths module,
- PI-CI-017 - Graphics module,
- PI-CI-018 - System module,
- PI-CI-020 - Clock module,
- PI-CI-021 - DDR module,
- PI-CI-023 - Interrupt manager module,
- PI-CI-024 - GPIO module,
- PI-CI-025 - Output compare module,
- PI-CI-026 - Timer module,
- PI-CI-027 - UART module,

The module calls the following modules:
- None
\subsection sec_PI-CI-035 PI-CI-035 - attribs library
The module consists of the following constituents:
- attribs.h


Functionality: Library providing macros for function and variable attributes.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-017 - Graphics module,
- PI-CI-028 - p32mz2064dar169 library,

The module calls the following modules:
- None
\subsection sec_PI-CI-036 PI-CI-036 - types library
The module consists of the following constituents:
- types.h


Functionality: Library providing system type functions.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-018 - System module,

The module calls the following modules:
- None
\subsection sec_PI-CI-037 PI-CI-037 - math library
The module consists of the following constituents:
- math.h


Functionality: Library providing maths functions.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-013 - Maths module,
- PI-CI-017 - Graphics module,

The module calls the following modules:
- None
\subsection sec_PI-CI-038 PI-CI-038 - stdlib library
The module consists of the following constituents:
- stdlib.h


Functionality: Standard utility functions library.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-001 - Main application module,
- PI-CI-007 - SCCB module,
- PI-CI-013 - Maths module,
- PI-CI-017 - Graphics module,

The module calls the following modules:
- None
\subsection sec_PI-CI-039 PI-CI-039 - stdarg library
The module consists of the following constituents:
- stdarg.h


Functionality: Library providing functionality related to accepting indefinite number of arguments.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-017 - Graphics module,

The module calls the following modules:
- None
\subsection sec_PI-CI-040 PI-CI-040 - stdio library
The module consists of the following constituents:
- stdio.h


Functionality: Library providing standard I/O support functions.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-004 - Debugging communication module,
- PI-CI-017 - Graphics module,
- PI-CI-019 - Exceptions module,

The module calls the following modules:
- None
\subsection sec_PI-CI-041 PI-CI-041 - cp0defs library
The module consists of the following constituents:
- cp0defs.h


Functionality: Contains register definitions for the CP0 registers.

The module does not provides any interfaces.


The module is called by the following modules:
- None

The module calls the following modules:
- None
\subsection sec_PI-CI-042 PI-CI-042 - kmem library
The module consists of the following constituents:
- kmem.h


Functionality: Macros for kseg address translation.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-006 - Camera module,
- PI-CI-017 - Graphics module,
- PI-CI-022 - DMA module,

The module calls the following modules:
- None
\subsection sec_PI-CI-043 PI-CI-043 - assert library
The module consists of the following constituents:
- assert.h


Functionality: Library providing standard assertions.

The module does not provides any interfaces.


The module is called by the following modules:
- PI-CI-018 - System module,

The module calls the following modules:
- None
\subsection sec_PI-CI-044 PI-CI-044 - PI-PDA communication module
The module consists of the following constituents:
- inter_pic_comms.c
- inter_pic_comms.h


Functionality: Provides driver-level functionality related to the communication with the PDA PESS.


The module provides the following interfaces:
- inter_pic_comms_init(),


The module is called by the following modules:
- PI-CI-001 - Main application module,

The module calls the following modules:
- PI-CI-004 - Debugging communication module
- PI-CI-024 - GPIO module
\section trace_mat_sec Architecture and software requirements
The following table shows how the software requirements map onto the software architecture, and therefore how the architecture implements these requirements.
<table>
<caption id='multi_row'>Requirements traceability matrix</caption>
<tr><th>Software module <th>Requirement ID
<tr><td>PI-CI-001 - Main application module<td>
<tr><td>PI-CI-002 - User Interface module<td>
<tr><td>PI-CI-003 - Settings module<td>
<tr><td>PI-CI-004 - Debugging communication module<td>
<tr><td>PI-CI-005 - Delay module<td>
<tr><td>PI-CI-006 - Camera module<td>
<tr><td>PI-CI-007 - SCCB module<td>
<tr><td>PI-CI-008 - Display module<td>
<tr><td>PI-CI-009 - I2C module<td>
<tr><td>PI-CI-010 - LED controller module<td>
<tr><td>PI-CI-011 - Piezo module<td>
<tr><td>PI-CI-012 - Touch controller module<td>
<tr><td>PI-CI-013 - Maths module<td>
<tr><td>PI-CI-014 - Message exchange module<td>
<tr><td>PI-CI-015 - PI-PE communication module<td>
<tr><td>PI-CI-016 - Power management module<td>
<tr><td>PI-CI-017 - Graphics module<td>
<tr><td>PI-CI-018 - System module<td>
<tr><td>PI-CI-019 - Exceptions module<td>
<tr><td>PI-CI-020 - Clock module<td>
<tr><td>PI-CI-021 - DDR module<td>
<tr><td>PI-CI-022 - DMA module<td>
<tr><td>PI-CI-023 - Interrupt manager module<td>
<tr><td>PI-CI-024 - GPIO module<td>
<tr><td>PI-CI-025 - Output compare module<td>
<tr><td>PI-CI-026 - Timer module<td>
<tr><td>PI-CI-027 - UART module<td>
<tr><td>PI-CI-028 - p32mz2064dar169 library<td>
<tr><td>PI-CI-029 - stdint library<td>
<tr><td>PI-CI-030 - stdbool library<td>
<tr><td>PI-CI-031 - xc library<td>
<tr><td>PI-CI-032 - string library<td>
<tr><td>PI-CI-033 - limits library<td>
<tr><td>PI-CI-034 - stddef library<td>
<tr><td>PI-CI-035 - attribs library<td>
<tr><td>PI-CI-036 - types library<td>
<tr><td>PI-CI-037 - math library<td>
<tr><td>PI-CI-038 - stdlib library<td>
<tr><td>PI-CI-039 - stdarg library<td>
<tr><td>PI-CI-040 - stdio library<td>
<tr><td>PI-CI-041 - cp0defs library<td>
<tr><td>PI-CI-042 - kmem library<td>
<tr><td>PI-CI-043 - assert library<td>
<tr><td>PI-CI-044 - PI-PDA communication module<td>
</table>
*/
