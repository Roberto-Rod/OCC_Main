/* ************************************************************************** */
/** @file app.c
 *
 *  @brief App module.
 *
 *  @copyright Occuity Limited (c) 2020
 */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "app.h"
#include "drv_STTS75.h"
#include "mcc_generated_files/adc1.h"

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* @brief holds major version of the firmware running on PIC24 */
#define MAJOR_VERSION 1
/* @brief holds minor version of the firmware running on PIC24 */
#define MINOR_VERSION 3

#define BUILD                       ((uint16_t)(000u))

/* ************************************************************************** */
/* Section: Global Variables                                                  */
/* ************************************************************************** */
/* @brief structure to hold the firmware running on PIC24 */
static _SW_VERSION swVersion;
/* @brief structure to hold the status of the PIC24 */
static _APP_STATUS appStatus;

/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */

/* ************************************************************************** */
/**
 * @brief            Converts version structure to uint16_t
 *
 * @param[in]        version Software version _SW_VERSION structure
 *
 * @note             None.
 *
 * @return           uint16_t Version converted to word.
 */
/* ************************************************************************** */
static uint16_t version_to_word(_SW_VERSION * version)
{
    uint8_t major = version->major;
    uint8_t minor = version->minor;
    if(minor > 99)
    {
        minor = 99;
    }
    return (uint16_t)(minor + ((uint16_t)major)*100);
}

/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */

/* ************************************************************************** */
/**
 * @brief            Returns copy of status struct
 *
 * @note             None.
 *
 * @return           _APP_STATUS Current status copy
 */
/* ************************************************************************** */
_APP_STATUS app_get_status(void)
{
    return appStatus;
}

/* ************************************************************************** */
/**
 * @brief            Returns software version in uint16_t format
 *
 * @note             None.
 *
 * @return           uint16_t Version converted to word.
 */
/* ************************************************************************** */
uint16_t SYS_version()
{
    return version_to_word(&swVersion);
}

_SW_VERSION SYS_full_version(){


    return swVersion;
}

/* ************************************************************************** */
/**
 * @brief            Initialise appStatus.
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void app_initialize(uint16_t rcon)
{
    //TODO add read of battery state
    appStatus.battery_soc_per = 100;

    app_reset_temperature_flags(true);
    _FLAG flg = NO_FLAGS;
    appStatus.flags = flg;

    app_update_date_time();

    swVersion.major = MAJOR_VERSION;
    swVersion.minor = MINOR_VERSION;

    swVersion.build = BUILD; 

}

void app_update_temperature(int16_t val){

     appStatus.temp_cur_degC_Q8 = val;

    if(val > appStatus.temp_max_degC_Q8){

        appStatus.temp_max_degC_Q8 = val;
    }

    if(val < appStatus.temp_min_degC_Q8){

        appStatus.temp_min_degC_Q8 = val;
    }

}

void app_reset_temperature_flags(bool and_values){

    if (and_values == true){
        appStatus.temp_max_degC_Q8 = INT16_MIN;
        appStatus.temp_min_degC_Q8 = INT16_MAX;
        appStatus.temp_cur_degC_Q8 = 0;
    }

    app_clear_flag(WARNING_FLAG_OVERTEMPERATURE);
    app_clear_flag(WARNING_FLAG_UNDERTEMPERATURE);
}

#define TEMP_NUM_VALS 3

void app_get_temperature(int16_t* out, uint8_t length){

    if(length > TEMP_NUM_VALS){

        return;
    }

    switch(length){

        case 3:

            *(out + 2) = appStatus.temp_max_degC_Q8;

        case 2:

            *(out + 1) = appStatus.temp_min_degC_Q8;

        default:

            *out = appStatus.temp_cur_degC_Q8;
            break;
    }

}

/* ************************************************************************** */
/**
 * @brief            Updates appStatus variable with battery state.
 *
 * @param[in]        current_battery_state_of_charge Current battery state of
 *                   charge.
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void app_update_battery_charge(uint8_t current_battery_state_of_charge)
{
    appStatus.battery_soc_per = current_battery_state_of_charge;
}

/* ************************************************************************** */
/**
 * @brief            Updates appStatus variable with current time and date.
 *
 * @param            None.
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void app_update_date_time(void)
{
    get_time(&appStatus.rtc_data);
}

/* ************************************************************************** */
/**
 * @brief            Updates appStatus variable setting appropriate flag.
 *
 * @param            None.
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void app_set_flag(_FLAG flg)
{
    appStatus.flags = appStatus.flags | flg;
}

/* ************************************************************************** */
/**
 * @brief            Updates appStatus variable removing appropriate flag.
 *
 * @param            flg flag mask
 *
 * @note             None.
 *
 * @return           None.
 */
/* ************************************************************************** */
void app_clear_flag(_FLAG flg)
{
    appStatus.flags = appStatus.flags & (~flg);
}

/* ************************************************************************** */
/**
 * @brief            Checks if particular appState flag is set
 *
 * @param            flg flag mask
 *
 * @note             None.
 *
 * @return           setiing of flag.
 */
/* ************************************************************************** */
bool app_check_flag(_FLAG flg)
{
    return ((appStatus.flags & (flg)) > 0 ? true: false);
}
