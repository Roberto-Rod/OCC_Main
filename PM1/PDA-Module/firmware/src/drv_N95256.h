#ifndef DRV_N95160_H    /* Guard against multiple inclusion */
#define DRV_N95160_H

#include <stdbool.h>
#include <stdint.h>


void SPI_eeprom_init(void);

bool EEPROM_save_settings(void);
bool EEPROM_read_settings(void);
bool EEPROM_read_statistics(void);
bool EEPROM_save_statistics(void);
bool EEPROM_read_calibration(void);

void EEPROM_read_to_USB(const uint8_t * data);
void EEPROM_save_from_USB(const uint8_t * data);
void EEPROM_read_page_raw(uint8_t * data, uint16_t page);
void EEPROM_write_page_raw(uint8_t * data, uint16_t page);


#endif /* _EXAMPLE_FILE_NAME_H */