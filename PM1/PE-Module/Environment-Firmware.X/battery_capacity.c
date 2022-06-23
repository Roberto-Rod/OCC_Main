/* ************************************************************************** */
/** @file battery_capacity.c
 *
 *  @brief Battery capacity file.
 *
 *  @copyright Occuity Limited (c) 2020
 */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include <xc.h>
#include "mcc_generated_files/pin_manager.h"
#include "battery_capacity.h"
#include "debug.h"
#include "mcc_generated_files/adc1.h"
#include "power_switch_interrupt.h"
#include "app.h"

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/** @brief define macro 12-bit adc voltage reference */
#define ADC_VOLTAGE_REFERENCE                             3.3
/** @brief define macro 12-bit adc number of steps */
#define ADC_NUMBER_OF_CONV_STEPS                          4095
/** @brief define macro connected to VBAT VOL pin voltage divider inverted ratio */
#define INVERT_VOLTAGE_DIVIDER_RATIO                      2.5
/** @brief define macro adc VBAT VOL pin voltage input to battery voltage conversion ratio */
#define ADC_INPUT_TO_BATTERY_VOLTAGE_CONV_RATIO           (ADC_VOLTAGE_REFERENCE*INVERT_VOLTAGE_DIVIDER_RATIO/ADC_NUMBER_OF_CONV_STEPS) 
/** @brief define macro moving average buffer length */
#define MOVING_AVERAGE_BUFFER_LENGTH                      20
/** @brief define macro battery state of charge data not valid */
#define BATTERY_SOC_NOT_VALID                              255
/** @brief define macro battery state of charge turn of device lower threshold */
#define BATTERY_SOC_TURN_OF_DEVICE_LOWER_THRESHOLD         0 
/** @brief define macro battery state of charge turn of device higher threshold */
#define BATTERY_SOC_TURN_OF_DEVICE_HIGHER_THRESHOLD        5
/** @brief define macro battery state of charge low battery notification lower threshold */
#define BATTERY_SOC_LOW_BATTERY_NOTIFY_LOWER_THRESHOLD     (BATTERY_SOC_TURN_OF_DEVICE_HIGHER_THRESHOLD +1)
/** @brief define macro battery state of charge low battery notification lower threshold */
#define BATTERY_SOC_LOW_BATTERY_NOTIFY_HIGHER_THRESHOL     20
/** @brief define macro battery state of charge normal operation lower threshold */
#define BATTERY_SOC_NORMAL_OPERATION_LOWER_THRESHOLD       (BATTERY_SOC_LOW_BATTERY_NOTIFY_HIGHER_THRESHOL +1) 
/** @brief define macro battery state of charge normal operation higher threshold */
#define BATTERY_SOC_NORMAL_OPERATION_HIGHER_THRESHOLD      100

#define BATTERY_TURN_ON_THRESHOLD_VOLTS                   (battery_percentage.battery_voltage_lookup_table[BATTERY_SOC_TURN_OF_DEVICE_HIGHER_THRESHOLD])  



/** @brief average data flag enum defining if taking average of the samples can be began */
typedef enum
{
    /** @brief  the flag is set on  */
    AVERAGE_DATA_FLAG_SET,
    /** @brief the flag is cleaned  */
    AVERAGE_DATA_FLAG_NOT_SET,
}AVERAGE_DATA_FLAG;

/** @brief battery percentage object defining parameters required for calculation battery voltage */
typedef struct
{
    /** @brief sample battery voltage */
   float voltage_battery; 
   /** @brief moving average buffer with battery voltage samples */
   float moving_avg_buffer[MOVING_AVERAGE_BUFFER_LENGTH];
   /** @brief position of the last sample in the buffer */
   uint8_t position_of_number_in_buffer;
   /** @brief new average of battery voltage */
   float new_avg;
   /** @brief sum of battery voltage samples */
   float sum; 
   /** @brief start takin average of the data flag */
   AVERAGE_DATA_FLAG start_avg_data_flag;
   
   /** @brief battery voltage charge lookup table */
   const float  battery_voltage_lookup_table[101];
   /** @brief battery state of charge lookup table */
   uint8_t battery_state_of_charge_percentage_lookup_table[101];
} BATTERY_OBJ;

/* ************************************************************************** */
/* Section: Global Variables                                                  */
/* ************************************************************************** */

/** @brief battery percentage object defining current parameters required for calculation battery voltage  */
static BATTERY_OBJ battery_percentage= 
{
    .voltage_battery = 0,
    .moving_avg_buffer = {0},
    .position_of_number_in_buffer = 0,
    .new_avg = 0,
    .sum = 0, 
    .start_avg_data_flag = AVERAGE_DATA_FLAG_NOT_SET,
    
    .battery_voltage_lookup_table =
    {
        6.39,
        6.4203,
        6.4484,
        6.4746,
        6.499,
        6.5221,
        6.544,
        6.5649,
        6.5853,
        6.605,
        6.624,
        6.6424,
        6.6599,
        6.6767,
        6.6925,
        6.7074,
        6.7215,
        6.735,
        6.7484,
        6.762,
        6.7758,
        6.7897,
        6.8036,
        6.8174,
        6.8312,
        6.845,
        6.8588,
        6.8726,
        6.8865,
        6.9002,
        6.9139,
        6.9275,
        6.9413,
        6.9553,
        6.9696,
        6.9842,
        6.9991,
        7.0142,
        7.0296,
        7.0451,
        7.0608,
        7.0767,
        7.0926,
        7.1086,
        7.1248,
        7.141,
        7.1575,
        7.174,
        7.1907,
        7.2076,
        7.2246,
        7.2416,
        7.2585,
        7.2752,
        7.2916,
        7.3076,
        7.3231,
        7.338,
        7.3524,
        7.3664,
        7.38,
        7.3933,
        7.4065,
        7.4194,
        7.4324,
        7.4453,
        7.4585,
        7.472,
        7.4859,
        7.5003,
        7.5155,
        7.5314,
        7.5481,
        7.5655,
        7.5834,
        7.6018,
        7.6206,
        7.6397,
        7.6589,
        7.6782,
        7.6974,
        7.7161,
        7.7343,
        7.7516,
        7.768,
        7.7832,
        7.7971,
        7.81,
        7.8222,
        7.8339,
        7.8456,
        7.8574,
        7.8696,
        7.8827,
        7.8968,
        7.9122,
        7.9293,
        7.9483,
        7.9696,
        7.9934,
        8.02
    },
};

/* Old table
    6,
    6.099460222,
    6.388328904,
    6.635558858,
    6.838547662,
    6.953054167,
    7.049343728,
    7.127416344,
    7.195079279,
    7.24452527,
    7.278356737,
    7.304380943,
    7.319995466,
    7.330405148,
    7.33560999,
    7.340814831,
    7.340814831,
    7.340814831,
    7.340814831,
    7.340814831,
    7.340814831,
    7.340814831,
    7.343417251,
    7.346019672,
    7.351224513,
    7.353826933,
    7.359031775,
    7.361634195,
    7.366839036,
    7.372043877,
    7.377248719,
    7.379851139,
    7.38505598,
    7.392863242,
    7.395465663,
    7.400670504,
    7.405875345,
    7.413682606,
    7.416285027,
    7.424092289,
    7.42929713,
    7.434501971,
    7.439706812,
    7.444911653,
    7.452718915,
    7.457923756,
    7.465731018,
    7.470935859,
    7.4761407,
    7.483947962,
    7.491755223,
    7.496960064,
    7.502164906,
    7.512574588,
    7.517779429,
    7.528189111,
    7.538598793,
    7.549008476,
    7.556815737,
    7.56982784,
    7.580237523,
    7.590647205,
    7.606261728,
    7.61667141,
    7.632285934,
    7.647900457,
    7.663514981,
    7.679129504,
    7.694744027,
    7.710358551,
    7.725973074,
    7.744190018,
    7.762406962,
    7.778021485,
    7.796238429,
    7.809250532,
    7.827467476,
    7.84568442,
    7.861298943,
    7.876913467,
    7.89252799,
    7.913347355,
    7.928961878,
    7.944576401,
    7.960190925,
    7.975805448,
    7.98621513,
    8.001829654,
    8.012239336,
    8.017444177,
    8.025251439,
    8.033058701,
    8.048673224,
    8.069492588,
    8.092914374,
    8.121541,
    8.152770046,
    8.194408775,
    8.236047505,
    8.272481392,
    8.311517701
*/


/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */

static void access_ADC_data(uint16_t *convertedValue_adc_input);
static void get_input_voltage(void);
static void moving_average(size_t moving_avg_length);
static void find_best_fit(size_t battery_voltage_lookup_table_length, size_t *battery_state_of_charge_lookup_table_id);
static void get_battery_voltage_sample(void);
static void get_battery_voltage_average(void);
static void get_battery_percentage(uint8_t *current_battery_state_of_charge);
static void notify_low_battery_voltage(void);

/* ************************************************************************** */
/** 
 * @brief            Access ADC data taken from VBAT_VOL pin
 *
 * @note             Called by static void get_input_voltage(void) when new sample 
 *                   of the battery voltage is wanted to be collected. 
 *
 * @param[in/out]    uint16_t *convertedValue_adc_input
 * 
 * @return           None.
 */
/* ************************************************************************** */
static void access_ADC_data(uint16_t *convertedValue_adc_input)
{
    static uint16_t i;
    ADC1_Enable();
    ADC1_ChannelSelect(VBAT_VOL);
    ADC1_SoftwareTriggerEnable();
    for (i = 0; i < 1000; i++)
    {
        asm("nop");
    } 
    ADC1_SoftwareTriggerDisable();    
    while(!ADC1_IsConversionComplete(VBAT_VOL));
    *convertedValue_adc_input = ADC1_ConversionResultGet(VBAT_VOL);        
    ADC1_Disable();  
}

/* ************************************************************************** */
/** 
 * @brief            Get input voltage on VBAT_VOL pin
 *
 * @note             Called by static void get_battery_sample_voltage(void) when 
 *                   new sample of the battery voltage is wanted to be collected.
 *                   Recalculate the battery voltage based on the ADC_INPUT_TO_BATTERY_VOLTAGE_CONV_RATIO
 * 
 * @return           None.
 */
/* ************************************************************************** */
static void get_input_voltage(void)
{
    uint16_t convertedValue_adc_input  = 0;
    access_ADC_data(&convertedValue_adc_input);   
    battery_percentage.voltage_battery = convertedValue_adc_input*ADC_INPUT_TO_BATTERY_VOLTAGE_CONV_RATIO;
}
/* ************************************************************************** */
/** 
 * @brief            Get one battery voltage sample
 *
 * @note             Called by static void get_battery_voltage_average(void) when 
 *                   new sample of the battery voltage is wanted to be collected.
 * 
 * @return           None.
 */
/* ************************************************************************** */
static void get_battery_voltage_sample(void)
{ 
   if (battery_percentage.start_avg_data_flag == AVERAGE_DATA_FLAG_NOT_SET && battery_percentage.position_of_number_in_buffer == MOVING_AVERAGE_BUFFER_LENGTH)
   {
     battery_percentage.start_avg_data_flag = AVERAGE_DATA_FLAG_SET;  
   }
   
   if(battery_percentage.position_of_number_in_buffer >= MOVING_AVERAGE_BUFFER_LENGTH)
   {
       battery_percentage.position_of_number_in_buffer = 0;
   }
   get_input_voltage();
}
/* ************************************************************************** */
/** 
 * @brief            Moving average filter 
 *
 * @note             Called by static void get_battery_voltage_average(void).
 *                   Filters battery voltage samples. 
 * 
 * @param[in/out]    size_t moving_avg_length
 * 
 * @return           None.
 */
/* ************************************************************************** */
static void moving_average(size_t moving_avg_length)
{
  /** @brief Subtracting the oldest number from the previous sum and adding the new value */
  battery_percentage.sum = battery_percentage.sum - battery_percentage.moving_avg_buffer[battery_percentage.position_of_number_in_buffer] + battery_percentage.voltage_battery;
  /** @brief Assigning the new value to the removed sample position in the buffer */
  battery_percentage.moving_avg_buffer[battery_percentage.position_of_number_in_buffer] = battery_percentage.voltage_battery;
   /** @brief Calculating the new average */
  battery_percentage.new_avg = battery_percentage.sum/ moving_avg_length;
}

/* ************************************************************************** */
/** 
 * @brief            Reset Moving average filter variables
 *
 * @note             Called after waking, to reset battery voltage averaging variables to ensure battery monitoring starts with fresh samples
 * 
 * 
 * @return           None.
 */
/* ************************************************************************** */

void battery_capacity_reset_avg(void){

    battery_percentage.position_of_number_in_buffer = 0;
    battery_percentage.new_avg = 0;
    battery_percentage.sum = 0; 
    battery_percentage.start_avg_data_flag = AVERAGE_DATA_FLAG_NOT_SET;
    uint8_t i  = 0; 
    for (i = 0; i < MOVING_AVERAGE_BUFFER_LENGTH ; i++){
        
        battery_percentage.moving_avg_buffer[i] = 0 ; 
    }
}

/* ************************************************************************** */
/** 
 * @brief            Calculate battery voltage average
 *
 * @note             Called by void get_battery_percentage(void)
 * 
 * @return           None.
 */
/* ************************************************************************** */
static void get_battery_voltage_average(void)
{
   size_t moving_avg_length = sizeof(battery_percentage.moving_avg_buffer) / sizeof(float);
   get_battery_voltage_sample();
   moving_average(moving_avg_length);
   if (battery_percentage.start_avg_data_flag != AVERAGE_DATA_FLAG_SET)
   {
     battery_percentage.new_avg =  battery_percentage.voltage_battery;
   }
   battery_percentage.position_of_number_in_buffer++; 
}
/* ************************************************************************** */
/** 
 * @brief            Maps current voltage data onto lookup table and find best position fit
 *
 * @note             Called by static void get_battery_percentage(uint8_t *current_battery_state_of_charge)
 *                   
 * @param[in/out]    size_t battery_voltage_lookup_table_length, size_t *battery_state_of_charge_lookup_table_id
 * 
 * @return           None.
 */
/* ************************************************************************** */

static void find_best_fit(size_t battery_voltage_lookup_table_length, size_t *battery_state_of_charge_lookup_table_id)
{
    float lookup_value_now = 0;
    float lookup_value_above = 0;
    float lookup_midpoint_between_above_now = 0;
    
    while(*battery_state_of_charge_lookup_table_id != battery_voltage_lookup_table_length)
    {
      lookup_value_now = battery_percentage.battery_voltage_lookup_table[*battery_state_of_charge_lookup_table_id];
      lookup_value_above = battery_percentage.battery_voltage_lookup_table[*battery_state_of_charge_lookup_table_id +1];
      lookup_midpoint_between_above_now = (lookup_value_above - lookup_value_now)/2 + lookup_value_now;
     
      if( battery_percentage.new_avg >= lookup_midpoint_between_above_now)
      {
          *battery_state_of_charge_lookup_table_id = *battery_state_of_charge_lookup_table_id + 1;
      }
      
      else 
      {
          break; 
      }
    }
}
/* ************************************************************************** */
/** 
 * @brief            Calculation battery state of discharge based on on VBAT_VOL pin 
 *                   input voltage
 *
 * @note             Called by void battery_capacity_task(void)
 * 
 * @return           None.
 */
/* ************************************************************************** */
static void get_battery_percentage(uint8_t *current_battery_state_of_charge)
{         
   size_t battery_voltage_lookup_table_length = sizeof(battery_percentage.battery_voltage_lookup_table) / sizeof(float);
   size_t battery_state_of_charge_lookup_table_id = 0;
   get_battery_voltage_average();  
   find_best_fit(battery_voltage_lookup_table_length, &battery_state_of_charge_lookup_table_id);
   if (battery_percentage.start_avg_data_flag == AVERAGE_DATA_FLAG_SET)
   {
        *current_battery_state_of_charge = battery_percentage.battery_state_of_charge_percentage_lookup_table[battery_state_of_charge_lookup_table_id];
   }
}
/* ************************************************************************** */
/** 
 * @brief            Notify battery is low
 *
 * @note             Called by void battery_capacity_task(void) when battery is low
 * //TODO:          How do we want to notify the user?
 * @return           None.
 */
/* ************************************************************************** */
static void notify_low_battery_voltage(void)
{
    //send to DAR?
    //dprintf_colour("[YELLOW]Battery is low![WHITE]\r\n");
}

/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */

void charger_stat_check(void){
    
    
     if( false == CHARGE_STAT_GetValue() )
    {
        app_set_flag(FLAG_DEVICE_CHARGING);
    }       
    else
    {
        app_clear_flag(FLAG_DEVICE_CHARGING);
    }
    
}

/* ************************************************************************** */
/** 
 * @brief            Initialisation of battery capacity module 
 *
 * @note             Called by void SYSTEM_Initialize(void)
 * 
 * @return           None.
 */
/* ************************************************************************** */
void BATTERY_CAPACITY_Initialize(void)
{
    static uint16_t i;
    size_t battery_soc_lookup_table_length = sizeof(battery_percentage.battery_state_of_charge_percentage_lookup_table) / sizeof(uint8_t);
    for(i = 0; i <=battery_soc_lookup_table_length ; i ++)
    {
        battery_percentage.battery_state_of_charge_percentage_lookup_table[i] = i;
    }    
    
    CHARGE_STAT_SetDigitalInput();
    
    CHARGE_STAT_SetInterruptHandler( &charger_stat_check); 
}




/* ************************************************************************** */
/** 
 * @brief            Checking battery state of charge task 
 *
 * @note             Called in while loop by main. Check battery state o charge
 * 
 * @return           None.
 */
/* ************************************************************************** */
uint8_t battery_capacity_task(void)
{
    charger_stat_check();
    
    if(app_check_flag(FLAG_DEVICE_CHARGING)){
        
        dputs("Charger active\r\n");
    }
    
    uint8_t current_battery_state_of_charge = BATTERY_SOC_NOT_VALID;
    get_battery_percentage(&current_battery_state_of_charge);    
    
    if(current_battery_state_of_charge != BATTERY_SOC_NOT_VALID)
    {
        app_update_battery_charge(current_battery_state_of_charge);
    }

    switch (current_battery_state_of_charge) {

        case BATTERY_SOC_NOT_VALID:
            break;

        case BATTERY_SOC_TURN_OF_DEVICE_LOWER_THRESHOLD ... BATTERY_SOC_TURN_OF_DEVICE_HIGHER_THRESHOLD:
            delayed_turn_off(); // start delayed turn off
            break;

        case BATTERY_SOC_LOW_BATTERY_NOTIFY_LOWER_THRESHOLD ... BATTERY_SOC_LOW_BATTERY_NOTIFY_HIGHER_THRESHOL:
            app_set_flag(WARNING_FLAG_BATTERY_LOW);
            notify_low_battery_voltage();
            break;

        case BATTERY_SOC_NORMAL_OPERATION_LOWER_THRESHOLD ... BATTERY_SOC_NORMAL_OPERATION_HIGHER_THRESHOLD:
            app_clear_flag(WARNING_FLAG_BATTERY_LOW);
            //dprintf_colour("[YELLOW]State of charge = %d %[WHITE]\r\n", current_battery_state_of_charge);
            break;

        default:
            //dprintf_colour("[YELLOW]Error! Not calculated correctly Battery State of Charge[WHITE]\r\n");
            break;
    }

        
    
    
    
    return current_battery_state_of_charge; 
}

/* ************************************************************************** */
/** 
 * @brief            Checking battery voltage at device turn on 
 *
 * @note             Called in while loop by main in device init state
 * 
 * @return           None.
 */
/* ************************************************************************** */
void turn_on_battery_capacity_task(void){
    
    get_battery_voltage_average();
    if(battery_percentage.start_avg_data_flag == AVERAGE_DATA_FLAG_SET){
        
        if(battery_percentage.new_avg > BATTERY_TURN_ON_THRESHOLD_VOLTS){
#ifdef DEBUG_POWER_SW
                dputs("Turn on Battery Check: Pass\r\n");
#endif 
                turn_on_device(); 
        }else{
#ifdef DEBUG_POWER_SW
            dputs("Turn on Battery Check: Fail\r\n");
#endif 
            turn_off_device();
        }

    }

}

/* ************************************************************************** */
/** 
 * @brief            Get latest battery voltage average
 *
 * @note             
 * 
 * @return           Current calculated battery average value
 */
/* ************************************************************************** */
float get_battery_average_value(void){
    
    return battery_percentage.new_avg; 
}



