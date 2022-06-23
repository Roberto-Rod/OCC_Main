#include "xc.h"


typedef uint16_t adc_result_t;









typedef struct

{

    adc_result_t adcResult1;

    adc_result_t adcResult2;

} adc_sync_double_result_t;

typedef enum

{

    HBridge_Current = 0x4,

    Boost_Voltage = 0x5,

    channel_Temp = 0x1D,

    channel_DAC = 0x1E,

    channel_FVR = 0x1F

} adc_channel_t;

void ADC_Initialize(void);

void ADC_SelectChannel(adc_channel_t channel);

void ADC_StartConversion();



_Bool 

    ADC_IsConversionDone();

adc_result_t ADC_GetConversionResult(void);

adc_result_t ADC_GetConversion(adc_channel_t channel);

void ADC_TemperatureAcquisitionDelay(void);
