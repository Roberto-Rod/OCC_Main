/*****************************************************************************
 *   File        : Pressure_Part2.c
 *
 *   Description : Source for implementation of pressure measurements
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

#include "Pressure_Part2.h"
#include "Pressure_Part3.h"
#include "PerformanceLogger.h"

/****************************************************************************
Function Name  :  TryToGetSingleVacuumMeasurement

Parameters     :  pInternal - Pointer to the internal pressure 
                  pExternal - Pointer to the external pressure  
                  pDiff - Pointer to the difference between the pressures

Return Value   :  EC_OK_E if the pressures are read OK and the temperatures are below
                  the thresholds, or errors otherwise.

Description    :  Reads the external and internal pressure sensors and
                  calculate their difference. 
                  Additionally read the internal and external sensor temperatures
                  and check against thresholds for over-heating.
*****************************************************************************/

/*lint -e{613} Suppress: Possible use of null pointer 'pInternal', 'pExternal', 'pDiff' in argument to operator 'unary *'. */
ErrorCode_t TryToGetSingleVacuumMeasurement(uint16_t* pInternal, uint16_t* pExternal, uint16_t* pDiff)
{
    ErrorCode_t result      = EC_OK_E;
    uint16_t    ExtPressure = 0;
    uint16_t    IntPressure = 0;
    uint16_t    ExtTemperature = 0;
    uint16_t    IntTemperature = 0;
    
    if ((NULL == pInternal) || (NULL == pExternal) || (NULL == pDiff))
    {
        result = EC_INVALID_INPUT_PARAMETER_E;
    }

    if (EC_OK_E == result)
    {
        if (TRUE == isPressureSensorReady(PS_EXTERNAL_PRESSURE_E))
        {
            result = PM_GetPressure(PS_EXTERNAL_PRESSURE_E, &ExtPressure, &ExtTemperature);
            PerformanceLogger_SetExternalPressure(ExtPressure);
            PerformanceLogger_SetExternalTemperature(ExtTemperature);
        }
        else
        {
            result = EC_EXT_PRESSURE_SENSOR_NOT_READY_E;
        }
    }

    if (EC_OK_E == result)
    {
        if (TRUE == isPressureSensorReady(PS_INTERNAL_PRESSURE_E))
        {
            result = PM_GetPressure(PS_INTERNAL_PRESSURE_E, &IntPressure, &IntTemperature);
            PerformanceLogger_SetInternalTemperature(IntTemperature);
        }
        else
        {
            result = EC_INT_PRESSURE_SENSOR_NOT_READY_E;
        }
    }

    if (EC_OK_E == result)
    {
        result = PM_CalcDiffPressure(ExtPressure, IntPressure, pDiff);
        PerformanceLogger_SetDifferentialPressure(*pDiff);

        *pInternal = IntPressure;
        *pExternal = ExtPressure;

        // Check temperature readings for overheating
        if ((int16_t)IntTemperature > INT_TEMPERATURE_THRESHOLD)
        {
            result = EC_INT_TEMPERATURE_HIGH;
        }
        
        else if ((int16_t)ExtTemperature > EXT_TEMPERATURE_THRESHOLD)
        {
            result = EC_EXT_TEMPERATURE_HIGH;
        }
    }

    return result;
}


