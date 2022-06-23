#include "LEDType.h"
#include "PaTypes.h"
void UI_SetLED(LED_Colour_t Colour, uint32_t FlashTOn, uint32_t FlashTOff);

bool_t UI_UpdateLEDs(void);

bool_t UI_IsPushButtonPressed(void);

uint32_t UI_GetPeriodCount(LED_Colour_t Colour);
