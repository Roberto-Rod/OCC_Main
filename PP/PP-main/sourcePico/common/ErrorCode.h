/*****************************************************************************
 *   File        : ErrorCode.h
 *
 *   Description : Global definition of Error codes
 *
 *****************************************************************************/
/* ***************************************************************************
 * This file is copyrighted by and the property of Smith & Nephew Medical Ltd.
 * It contains confidential and proprietary information. It must not be copied
 * (in whole or in part) or otherwise disclosed without prior written consent 
 * of the company. Any copies of this file (in whole or in part), made by any
 * method must also include a copy of this legend. 
 * 
 * (c) 2018, 2019, 2020 Smith & Nephew Medical Ltd.
 * 
 *************************************************************************** */

#ifndef PICOONBOARD_ERRORCODE_H
#define PICOONBOARD_ERRORCODE_H

/**
 * Global error return code.
 */
typedef enum {
    EC_OK_E,      //generic no error
    EC_FAILED_E,  //generic fail
    EC_OPS_NOT_EXECUTED_E, //not fail, but not executed
    EC_NOT_INITIALISED_E,    //the module has not been initialised
    EC_ADC_BUSY_E,    //ADC is busy converting
    EC_PUMP_OFF,
    EC_EEPROM_CHECKS_FAILED_E, //data read from eeprom fails check
    EC_OUT_OF_BOUND_E,  //input data is out of bound
    EC_TIME_UP_E,   //time up executing an operation
    EC_INVALID_INPUT_PARAMETER_E, //SW error where an API has been used with the wrong input parameter(s)
    EC_UNKNOWN_STATE_E, // detected an unknown state
    EC_TIMER_COUNT_UNAVAILABLE_E,
    EC_TIMER_COUNT_NOT_ACTIVE_E,
    EC_TIMER_COUNT_ACTIVE_E,
    EC_INT_PRESSURE_SENSOR_NOT_READY_E,
    EC_EXT_PRESSURE_SENSOR_NOT_READY_E,
    EC_INT_PRESSURE_SENSOR_READ_FAILED_E,
    EC_EXT_PRESSURE_SENSOR_READ_FAILED_E,
    EC_INT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E,
    EC_EXT_PRESSURE_SENSOR_FAILED_TO_INITIALISE_E,
    EC_INT_PRESSURE_SENSOR_FAILED_TO_START_E,
    EC_EXT_PRESSURE_SENSOR_FAILED_TO_START_E,
    EC_PRESSURE_DIFF_FAULT_CODE_E,
    EC_POWER_TRACKER_FREQUENCY_OUT_OF_RANGE_E,
    EC_VOLTAGE_OUT_OF_RANGE_E,
    EC_BATTERY_END_OF_LIFE_E,
    EC_LOGGING_POSTPONE_E,    //logging postpone due to device busy
    EC_EEPROM_BUFFER_FULL_EOL, // Reached the end of the log buffer 
    EC_INT_TEMPERATURE_HIGH,
    EC_EXT_TEMPERATURE_HIGH,
    EC_MAX_E    //size of the error code
} ErrorCode_t;

#endif //PICOONBOARD_ERRORCODE_H
