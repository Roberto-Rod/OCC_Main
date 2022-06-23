/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    settings.c

  @Summary
    Load and save device settings in non-volatile memory.

  @Description
    Uses CY15B104 FRAM to store settings.
 */
/* ************************************************************************** */

#ifndef _SETTINGS_H    /* Guard against multiple inclusion */
#define _SETTINGS_H


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */



/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */   

#define SETTINGS_STRUCTURE_SIZE 32U
typedef struct{
    union{
        uint8_t Bytes[SETTINGS_STRUCTURE_SIZE];
        struct{
            uint16_t LCD_BRIGHTNESS;
            uint16_t LED_BRIGHTNESS;
            uint16_t LED_FADE_RATE;
            uint16_t VOLTAGE_TRESHOLD;//VREF
            uint16_t P1_TRESHOLD;
            uint16_t P2_TRESHOLD;
            uint16_t MIN_SEPARATION;
            uint16_t MAX_SEPARATION;
            uint16_t MIN_FWHM;
            uint16_t MAX_FWHM;
            uint16_t CAMERA_HSTART;
            uint16_t CAMERA_VSTART;
            uint16_t MENU_LOCKED;
        };
    };
}DEVICE_SETTINGS_t;

typedef union {
    uint8_t Bytes[128];
    struct{
        DEVICE_SETTINGS_t settings;
        uint8_t device_name[17];
        uint8_t PDAB_build;
        uint8_t LSC_build;
        uint32_t scans_counter;
    };
}DEVICE_SETTINGS_FOR_PI_t;

extern DEVICE_SETTINGS_t device_settings;
extern DEVICE_SETTINGS_FOR_PI_t device_settings_for_PI;
  
#define DEFAULT_PK_RADIUS           25U                           /* 25 */
#define DEFAULT_PK_RADIUS_TOL       4U                            /* 4 */
#define DEFAULT_PK_ALIGN_TOL        4U                            /* 4 */    
#define DEFAULT_GRAD_THRESHOLD      8U                           /* 20 */ 
    
// *****************************************************************************
// Section: Data Types
// *****************************************************************************



// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

/* load, save and set defaults */
void set_default_settings(void);
void save_settings(void);
void load_settings(void);


/* getters and setters */
uint8_t settings_get_lcd_brightness(void);
void settings_set_lcd_brightness(uint8_t lcd_brightness);
uint8_t settings_get_illumination_max(void);
void settings_set_illumination_max(uint8_t illumination_max);
uint8_t settings_get_led_brightness(void);
void settings_set_led_brightness(uint8_t led_brightness);
bool settings_get_bluetooth_enabled(void);
void settings_set_bluetooth_enabled(bool bluetooth_enabled);
uint8_t settings_get_laser_power(void);
void settings_set_laser_power(uint8_t laser_power);
uint8_t settings_get_amplifier_gain(void);
void settings_set_amplifier_gain(uint8_t amplifier_gain);
uint16_t settings_get_comparator_reference_voltage(void);
void settings_set_comparator_reference_voltage(uint8_t comparator_reference_voltage);
uint16_t* settings_get_peak_thresholds(void);
uint16_t settings_get_peak_1_threshold_voltage(void);
void settings_set_peak_1_threshold_voltage(uint16_t peak_1_threshold_voltage);
uint16_t settings_get_peak_2_threshold_voltage(void);
void settings_set_peak_2_threshold_voltage(uint16_t peak_2_threshold_voltage);
uint16_t settings_get_peak_3_threshold_voltage(void);
void settings_set_peak_3_threshold_voltage(uint16_t peak_3_threshold_voltage);
uint16_t settings_get_peak_4_threshold_voltage(void);
void settings_set_peak_4_threshold_voltage(uint16_t peak_4_threshold_voltage);
uint16_t settings_get_minimum_separation(void);
void settings_set_minimum_separation(uint16_t minimum_separation);
uint16_t settings_get_maximum_separation(void);
void settings_set_maximum_separation(uint16_t maximum_separation);
uint16_t  settings_get_minimum_fwhm(void);
void settings_set_minimum_fwhm(uint16_t  minimum_fwhm);
uint16_t  settings_get_maximum_fwhm(void);
void settings_set_maximum_fwhm(uint16_t maximum_fwhm);
bool settings_get_show_scan_summary(void);
void settings_set_show_scan_summary(bool show_scan_summary);
bool settings_get_show_scan_graph(void);
void settings_set_show_scan_graph(bool show_scan_graph);
bool settings_get_show_alignment_ui(void);
void settings_set_show_alignment_ui(bool show_alignment_ui);
bool settings_get_dsp_scan_selection(void);
void settings_set_dsp_scan_selection(bool enable_dsp_scan_selection);
bool settings_get_pupil_finding(void);
void settings_set_pupil_finding(bool enable_pupil_finding);
uint16_t settings_get_camera_hstart(void);
void settings_set_camera_hstart(uint16_t camera_hstart);
uint16_t settings_get_camera_vstart(void);
void settings_set_camera_vstart(uint16_t camera_vstart);

uint8_t settings_get_pk1_target_radius(void);
void settings_set_pk1_target_radius(uint8_t pk1_target_radius);
uint8_t settings_get_pk1_radius_tolerance(void);
void settings_set_pk1_radius_tolerance(uint8_t pk1_radius_tolerance);
uint8_t settings_get_pk1_alignment_tolerance(void);
void settings_set_pk1_alignment_tolerance(uint8_t pk1_alignment_tolerance);
uint8_t settings_get_pupil_gradient_threshold(void);
void settings_set_pupil_gradient_threshold(uint8_t pupil_gradient_threshold);

bool settings_get_wait_for_alignment(void);
void settings_set_wait_for_alignment(bool wait_for_alignment);

float settings_get_refractive_index_value(uint8_t index);
const char* settings_get_refractive_index_string(uint8_t index);

float settings_get_refractive_index(void);
uint8_t settings_get_refractive_index_index(void);
void settings_set_refractive_index(uint8_t index);
uint8_t settings_get_refractive_index_index(void);

uint16_t settings_get_total_scans(void);
void settings_set_total_scans(uint16_t total_scans);

void update_settings_from_PDAB(void);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _SETTINGS_H */
