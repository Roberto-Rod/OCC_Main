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

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */

#include "definitions.h"
#include "settings.h"

//#define DEBUG_SETTINGS

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */

typedef struct
{
    /* device settings */
    uint8_t lcd_brightness;                     /* 0 - 100% */
    uint8_t illumination_max;                   /* 127 (50%) or 255 (100%) */
    uint8_t led_brightness;                     /* 0 - 100% */
    bool bluetooth_enabled;                     /* true or false */
    uint8_t laser_power;                        /* 0 - 127 */
    uint8_t amplifier_gain;                     /* 0 - 127 */

    /* scan settings */
    uint8_t comparator_reference_voltage;       /* 0 - 16 */
    uint16_t peak_thresholds[4];                /* 0 - 5V */
    uint16_t separation_limits[2];              /* 300um - 1000um*/
    uint16_t fwhm_limits[2];                    /* 25um - 75um */   
    
    /* UI settings */
    bool show_scan_summary;                     /* true or false */
    bool show_scan_graph;                       /* true or false */
    bool show_alignment_ui;                     /* true or false */
    bool wait_for_alignment;                    /* true or false */
    
    /* Scan post-process settings */
    bool enable_dsp_scan_selection;             /* true or false */
    bool enable_ip_scan_selection;              /* true or false */
    bool enable_pupil_finding;                  /* true or false */
    
    /* camera settings */
    uint8_t camera_hstart;                      /* 0 - 0xff */
    uint8_t camera_vstart;                      /* 0 - 0xff */
    

    uint8_t pk1_target_radius;                  /* 5 - 32 */
    uint8_t pk1_radius_tolerance;               /* 1 - 10 */
    uint8_t pk1_alignment_tolerance;            /* 1 - 10 */
    
    uint8_t pupil_gradient_threshold;           /* 0 - 255 */

    uint8_t total_scans;                        /* 1 - 250 */
} device_settings_old;

typedef struct
{
    device_settings_old settings;
    uint32_t crc;
} pachymeter_device_settings;

static pachymeter_device_settings config __attribute__((aligned(32)));

DEVICE_SETTINGS_t device_settings;
DEVICE_SETTINGS_FOR_PI_t device_settings_for_PI;
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
void update_settings_from_PDAB(void)
{
    //dputs_colour("[GREEN]Settings updated on PI[WHITE]\r\n");
    
    dprintf_colour("[YELLOW]EEPROM - Device name: %s[WHITE]\r\n", device_settings_for_PI.device_name);
    
    config.settings.lcd_brightness = device_settings.LCD_BRIGHTNESS;
    config.settings.led_brightness = device_settings.LED_BRIGHTNESS;
    config.settings.comparator_reference_voltage = device_settings.VOLTAGE_TRESHOLD;      
    config.settings.peak_thresholds[0] = device_settings.P1_TRESHOLD;    
    config.settings.peak_thresholds[1] = device_settings.P2_TRESHOLD;
    config.settings.separation_limits[0] = device_settings.MIN_SEPARATION;
    config.settings.separation_limits[1] = device_settings.MAX_SEPARATION;
    config.settings.fwhm_limits[0] = device_settings.MIN_FWHM;
    config.settings.fwhm_limits[1] = device_settings.MAX_FWHM; 
    config.settings.camera_hstart = device_settings.CAMERA_HSTART;
    config.settings.camera_vstart = device_settings.CAMERA_VSTART;
    
    
    DRV_CAMERA_OVM7692_Set_Position(sysObj.drvOVM7692, config.settings.camera_hstart, config.settings.camera_vstart);
}

void set_default_settings(void)
{
    /* TODO receive settings from PDAB else assign defaults */
    device_settings.LCD_BRIGHTNESS = 101U;
    device_settings.LED_BRIGHTNESS = 200U;
    device_settings.VOLTAGE_TRESHOLD = 12U;
    device_settings.P1_TRESHOLD = 26214U;
    device_settings.P2_TRESHOLD = 786U;
    device_settings.MIN_SEPARATION = 300U;
    device_settings.MAX_SEPARATION = 800U;
    device_settings.MIN_FWHM = 35U;
    device_settings.MAX_FWHM = 75U;
    device_settings.CAMERA_HSTART = 169U;
    device_settings.CAMERA_VSTART = 25U;
    
    config.settings.lcd_brightness = device_settings.LCD_BRIGHTNESS;
    config.settings.illumination_max = 128;                     /* 50% */
    config.settings.led_brightness = device_settings.LED_BRIGHTNESS;
    config.settings.bluetooth_enabled = false;                  /* Bluetooth disabled */
    config.settings.laser_power = 64;                           /* 50% power */
    config.settings.amplifier_gain = 0;                

    config.settings.comparator_reference_voltage = device_settings.VOLTAGE_TRESHOLD;      
    config.settings.peak_thresholds[0] = device_settings.P1_TRESHOLD;    
    config.settings.peak_thresholds[1] = device_settings.P2_TRESHOLD;
    config.settings.peak_thresholds[2] = 300U;                  /* 0.2V */
    config.settings.peak_thresholds[3] = 300U;                  /* 0.2V */    
    config.settings.separation_limits[0] = device_settings.MIN_SEPARATION;
    config.settings.separation_limits[1] = device_settings.MAX_SEPARATION;
    config.settings.fwhm_limits[0] = device_settings.MIN_FWHM;
    config.settings.fwhm_limits[1] = device_settings.MAX_FWHM; 
    config.settings.show_scan_summary = false;                  /* scan summary disabled */
    config.settings.show_scan_graph = false;                    /* scan graph disabled */
    config.settings.show_alignment_ui = true;                   /* show alignment UI enabled */
    config.settings.enable_dsp_scan_selection = true;           /* DSP scan selection enabled */
    config.settings.enable_ip_scan_selection = false;           /* IP scan selection enabled */
    config.settings.enable_pupil_finding = false;               /* Pupil Finding enabled */
    
    config.settings.camera_hstart = device_settings.CAMERA_HSTART;
    config.settings.camera_vstart = device_settings.CAMERA_VSTART;
    
    config.settings.pk1_target_radius = DEFAULT_PK_RADIUS;              
    config.settings.pk1_radius_tolerance = DEFAULT_PK_RADIUS_TOL;         
    config.settings.pk1_alignment_tolerance = DEFAULT_PK_ALIGN_TOL;       
    config.settings.pupil_gradient_threshold = DEFAULT_GRAD_THRESHOLD;   
    config.settings.wait_for_alignment = true;               /* wait for alignment enabled */

    config.settings.total_scans = 100U;
    
    dputs_colour("[GREEN]Settings set to default values[WHITE]\r\n");
}

void log_settings(void)
{
    #ifdef DEBUG_SETTINGS
    dprintf_colour("[BLUE]lcd_brightness = %d[WHITE]\r\n", config.settings.lcd_brightness);
    dprintf_colour("[BLUE]illumination_max = %d[WHITE]\r\n", config.settings.illumination_max);
    dprintf_colour("[BLUE]led_brightness = %d[WHITE]\r\n", config.settings.led_brightness);
    dprintf_colour("[BLUE]bluetooth_enabled = %d[WHITE]\r\n", config.settings.bluetooth_enabled);
    dprintf_colour("[BLUE]total scans = %d[WHITE]\r\n", config.settings.total_scans);
    dprintf_colour("[BLUE]laser_power = %d[WHITE]\r\n", config.settings.laser_power);
    dprintf_colour("[BLUE]amplifier_gain = %d[WHITE]\r\n", config.settings.amplifier_gain);
    dprintf_colour("[BLUE]comparator_reference_voltage = %d[WHITE]\r\n", config.settings.comparator_reference_voltage);
    dprintf_colour("[BLUE]peak_1_threshold_voltage = %d[WHITE]\r\n", config.settings.peak_thresholds[0]);
    dprintf_colour("[BLUE]peak_2_threshold_voltage = %d[WHITE]\r\n", config.settings.peak_thresholds[1]);
    dprintf_colour("[BLUE]peak_3_threshold_voltage = %d[WHITE]\r\n", config.settings.peak_thresholds[2]);
    dprintf_colour("[BLUE]peak_4_threshold_voltage = %d[WHITE]\r\n", config.settings.peak_thresholds[3]);
    dprintf_colour("[BLUE]minimum_fwhm = %d[WHITE]\r\n", config.settings.fwhm_limits[0]);
    dprintf_colour("[BLUE]maximum_fwhm = %d[WHITE]\r\n", config.settings.fwhm_limits[1]);    
    dprintf_colour("[BLUE]minimum_separation = %d[WHITE]\r\n", config.settings.separation_limits[0]);
    dprintf_colour("[BLUE]maximum_separation = %d[WHITE]\r\n", config.settings.separation_limits[1]);
    dprintf_colour("[BLUE]show_scan_summary = %d[WHITE]\r\n", config.settings.show_scan_summary);
    dprintf_colour("[BLUE]show_scan_graph = %d[WHITE]\r\n", config.settings.show_scan_graph);
    dprintf_colour("[BLUE]show_alignment_ui = %d[WHITE]\r\n", config.settings.show_alignment_ui);    
    dprintf_colour("[BLUE]camera_hstart = 0x%02x[WHITE]\r\n", config.settings.camera_hstart);
    dprintf_colour("[BLUE]camera_vstart = 0x%02x[WHITE]\r\n", config.settings.camera_vstart);
    dprintf_colour("[BLUE]refractive_index = %1.3f[WHITE]\r\n", config.settings.refractive_index);
    dprintf_colour("[BLUE]pk1_target_radius = %d[WHITE]\r\n", config.settings.pk1_target_radius);
    dprintf_colour("[BLUE]pk1_radius_tolerance = %d[WHITE]\r\n", config.settings.pk1_radius_tolerance);
    dprintf_colour("[BLUE]pk1_alignment_tolerance = %d[WHITE]\r\n", config.settings.pk1_alignment_tolerance);
    dprintf_colour("[BLUE]pupil_gradient_threshold = %d[WHITE]\r\n", config.settings.pupil_gradient_threshold);   
    dprintf_colour("[BLUE]wait_for_alignment = %d[WHITE]\r\n", config.settings.wait_for_alignment);
    dprintf_colour("[BLUE]enable_dsp_scan_selection = %d[WHITE]\r\n", config.settings.enable_dsp_scan_selection);
    dprintf_colour("[BLUE]enable_ip_scan_selection = %d[WHITE]\r\n", config.settings.enable_ip_scan_selection);
    dprintf_colour("[BLUE]enable_pupil_finding = %d[WHITE]\r\n", config.settings.enable_pupil_finding);
#endif
}

void save_settings(void)
{
    //save_config(&config);
    //update settings on PDAB
    
    device_settings.LCD_BRIGHTNESS = config.settings.lcd_brightness;
    device_settings.LED_BRIGHTNESS = config.settings.led_brightness;
    device_settings.VOLTAGE_TRESHOLD = config.settings.comparator_reference_voltage;      
    device_settings.P1_TRESHOLD = config.settings.peak_thresholds[0];    
    device_settings.P2_TRESHOLD = config.settings.peak_thresholds[1];
    device_settings.MIN_SEPARATION = config.settings.separation_limits[0];
    device_settings.MAX_SEPARATION = config.settings.separation_limits[1];
    device_settings.MIN_FWHM = config.settings.fwhm_limits[0];
    device_settings.MAX_FWHM = config.settings.fwhm_limits[1]; 
    device_settings.CAMERA_HSTART = config.settings.camera_hstart;
    device_settings.CAMERA_VSTART = config.settings.camera_vstart;
    
    
    send_command_to_PDAB(COMMAND_UPDATE_SETTINGS,(uint8_t *)&device_settings,sizeof(DEVICE_SETTINGS_t));
}

/* getters and setters */

uint8_t settings_get_lcd_brightness(void)
{
    return (config.settings.lcd_brightness);
}

void settings_set_lcd_brightness(uint8_t lcd_brightness)
{
    config.settings.lcd_brightness = lcd_brightness;
}

uint8_t settings_get_led_brightness(void)
{
    return (config.settings.led_brightness);
}

void settings_set_led_brightness(uint8_t led_brightness)
{
    config.settings.led_brightness = led_brightness;
}

bool settings_get_bluetooth_enabled(void)
{
    return (config.settings.bluetooth_enabled);
}

void settings_set_bluetooth_enabled(bool bluetooth_enabled)
{
    config.settings.bluetooth_enabled = bluetooth_enabled;    
}

uint8_t settings_get_laser_power(void)
{
    return (config.settings.laser_power);
}

void settings_set_laser_power(uint8_t laser_power)
{
    config.settings.laser_power = laser_power;
}

uint8_t settings_get_amplifier_gain(void)
{
    return (config.settings.amplifier_gain);
}

void settings_set_amplifier_gain(uint8_t amplifier_gain)
{
    config.settings.amplifier_gain = amplifier_gain;
}

uint16_t settings_get_comparator_reference_voltage(void)
{
    return (config.settings.comparator_reference_voltage);
}

void settings_set_comparator_reference_voltage(uint8_t comparator_reference_voltage)
{
    config.settings.comparator_reference_voltage = comparator_reference_voltage;
}

uint16_t* settings_get_peak_thresholds(void)
{
    return (config.settings.peak_thresholds);
}

uint16_t settings_get_peak_1_threshold_voltage(void)
{
    return (config.settings.peak_thresholds[0]);
}

void settings_set_peak_1_threshold_voltage(uint16_t peak_1_threshold_voltage)
{
    config.settings.peak_thresholds[0] = peak_1_threshold_voltage;
}

uint16_t  settings_get_peak_2_threshold_voltage(void)
{
    return (config.settings.peak_thresholds[1]);
}

void settings_set_peak_2_threshold_voltage(uint16_t peak_2_threshold_voltage)
{
    config.settings.peak_thresholds[1] = peak_2_threshold_voltage;
    device_settings.P2_TRESHOLD = peak_2_threshold_voltage;
}

uint16_t settings_get_peak_3_threshold_voltage(void)
{
    return (config.settings.peak_thresholds[2]);
}

void settings_set_peak_3_threshold_voltage(uint16_t peak_3_threshold_voltage)
{
    config.settings.peak_thresholds[2] = peak_3_threshold_voltage;
}

uint16_t settings_get_peak_4_threshold_voltage(void)
{
    return (config.settings.peak_thresholds[3]);
}

void settings_set_peak_4_threshold_voltage(uint16_t peak_4_threshold_voltage)
{
    config.settings.peak_thresholds[3] = peak_4_threshold_voltage;
}

uint16_t settings_get_minimum_separation(void)
{
    return (config.settings.separation_limits[0]);
}

void settings_set_minimum_separation(uint16_t  minimum_separation)
{
    config.settings.separation_limits[0] = minimum_separation;
}

uint16_t settings_get_maximum_separation(void)
{
    return (config.settings.separation_limits[1]);
}

void settings_set_maximum_separation(uint16_t maximum_separation)
{
    config.settings.separation_limits[1] = maximum_separation;
}

uint16_t settings_get_minimum_fwhm(void)
{
    return (config.settings.fwhm_limits[0]);
}

void settings_set_minimum_fwhm(uint16_t  minimum_fwhm)
{
    config.settings.fwhm_limits[0] = minimum_fwhm;
}

uint16_t settings_get_maximum_fwhm(void)
{
    return (config.settings.fwhm_limits[1]);
}

void settings_set_maximum_fwhm(uint16_t maximum_fwhm)
{
    config.settings.fwhm_limits[1] = maximum_fwhm;
}

bool settings_get_show_scan_summary(void)
{
    return (config.settings.show_scan_summary);
}

void settings_set_show_scan_summary(bool show_scan_summary)
{
    config.settings.show_scan_summary = show_scan_summary;
}

bool settings_get_show_scan_graph(void)
{
    return (config.settings.show_scan_graph);
}

void settings_set_show_scan_graph(bool show_scan_graph)
{
    config.settings.show_scan_graph = show_scan_graph;
}

bool settings_get_show_alignment_ui(void)
{
    return (config.settings.show_alignment_ui);
}

void settings_set_show_alignment_ui(bool show_alignment_ui)
{
    config.settings.show_alignment_ui = show_alignment_ui;
}

bool settings_get_dsp_scan_selection(void)
{
    return (config.settings.enable_dsp_scan_selection);
}

void settings_set_dsp_scan_selection(bool enable_dsp_scan_selection)
{
    config.settings.enable_dsp_scan_selection = enable_dsp_scan_selection;
}

bool settings_get_pupil_finding(void)
{
    return (config.settings.enable_pupil_finding);
}

void settings_set_pupil_finding(bool enable_pupil_finding)
{
    config.settings.enable_pupil_finding = enable_pupil_finding;
}

uint16_t settings_get_camera_hstart(void)
{
    return (config.settings.camera_hstart);
}

void settings_set_camera_hstart(uint16_t camera_hstart)
{
    config.settings.camera_hstart = camera_hstart;
}

uint16_t settings_get_camera_vstart(void)
{
    return (config.settings.camera_vstart);
}

void settings_set_camera_vstart(uint16_t camera_vstart)
{
    config.settings.camera_vstart = camera_vstart;
}

uint8_t settings_get_pk1_target_radius(void)
{
    return (config.settings.pk1_target_radius);
}

void settings_set_pk1_target_radius(uint8_t pk1_target_radius)
{
    config.settings.pk1_target_radius = pk1_target_radius;
}

uint8_t settings_get_pk1_radius_tolerance(void)
{
    return (config.settings.pk1_radius_tolerance);
}

void settings_set_pk1_radius_tolerance(uint8_t pk1_radius_tolerance)
{
    config.settings.pk1_radius_tolerance = pk1_radius_tolerance;
}

uint8_t settings_get_pk1_alignment_tolerance(void)
{
    return (config.settings.pk1_alignment_tolerance);
}

void settings_set_pk1_alignment_tolerance(uint8_t pk1_alignment_tolerance)
{
    config.settings.pk1_alignment_tolerance = pk1_alignment_tolerance;
}

uint8_t settings_get_pupil_gradient_threshold(void)
{
    return (config.settings.pupil_gradient_threshold);
}

void settings_set_pupil_gradient_threshold(uint8_t pupil_gradient_threshold)
{
    config.settings.pupil_gradient_threshold = pupil_gradient_threshold;
}

bool settings_get_wait_for_alignment(void)
{
    return (config.settings.wait_for_alignment);
}

void settings_set_wait_for_alignment(bool wait_for_alignment)
{
    config.settings.wait_for_alignment = wait_for_alignment;
}

uint16_t settings_get_total_scans(void)
{
    return ((uint16_t) config.settings.total_scans);
}

void settings_set_total_scans(uint16_t total_scans)
{
    config.settings.total_scans = (uint8_t) total_scans;
}
