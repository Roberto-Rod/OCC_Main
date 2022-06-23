/* EEPROM N95256
 * SPI 
 */

#include "drv_N95256.h"
#include <stdint.h>
#include "definitions.h"
#include "scan_processing.h"


/* Globals */
extern DEVICE_SETTINGS_t device_settings;
extern float cal_data[PDAB_SCAN_LENGTH_16];
extern PDAB_DATA pdabData;
extern DEVICE_STATISTICS_t device_statistics;

/*         */

/* function prototypes */
static inline void EEPROM_CS_off(void);
static void debug_settings(void);
static void Delay(uint32_t cycles);
static inline void EEPROM_CS_on(void);
static inline void EEPROM_CS_off(void);
static inline void EEPROM_SDI(int value);
static inline void EEPROM_SCK(int value);
static inline void EEPROM_WP(int value);
static inline uint8_t EEPROM_SDO(void);
static uint8_t SPI_transmit_byte(uint8_t byte);
static void EEPROM_enable_writing(void);
static void EEPROM_disable_writing(void);
static uint8_t checksum(uint8_t * data, uint16_t offset, uint16_t count);
static uint8_t EEPROM_write_page(uint8_t * data, uint16_t page);
void EEPROM_write_page_raw(uint8_t * data, uint16_t page);
static bool EEPROM_read_page(uint8_t * data, uint16_t page);
void EEPROM_read_page_raw(uint8_t * data, uint16_t page);
static inline bool compare_two_pages(uint8_t * data1, uint8_t * data2);
static bool EEPROM_write_page_FT(uint8_t * data, uint16_t page);
static void fill_in_eeprom(void);
static void debug_settings(void);

/*  */

/* SPI BITBANG DRIVER - START */
#define SPI_DELAY       5

static void Delay(uint32_t cycles) {
    volatile uint32_t i = 0;
    while (i++ < cycles) {
        Nop();
    }
}

void SPI_eeprom_init(void) {
    CFGCONbits.TROEN = 0;
    SQI1CFGbits.SQIEN = 0;

    TRISDbits.TRISD4 = 0;
    TRISAbits.TRISA7 = 0;
    TRISAbits.TRISA6 = 0;
    TRISGbits.TRISG12 = 1;
    TRISGbits.TRISG13 = 0;
    TRISGbits.TRISG14 = 0;

    LATAbits.LATA7 = 1;
    LATGbits.LATG14 = 1;
    LATGbits.LATG13 = 1;

    EEPROM_CS_off();

    
    EEPROM_read_settings();
    EEPROM_read_calibration();
    EEPROM_read_statistics();
}

static inline void EEPROM_CS_on(void) {
    LATDbits.LATD4 = 0;
}

static inline void EEPROM_CS_off(void) {
    LATDbits.LATD4 = 1;
}

static inline void EEPROM_SDI(int value) {
    LATGbits.LATG13 = value;
}

static inline void EEPROM_SCK(int value) {
    LATAbits.LATA6 = value;
}

static inline void EEPROM_WP(int value) {
    LATGbits.LATG14 = value;
}

static inline uint8_t EEPROM_SDO(void) {
    return PORTGbits.RG12;
}

static uint8_t SPI_transmit_byte(uint8_t byte) {
    uint8_t bit;
    uint8_t result = 0;

    for (bit = 0; bit < 8; bit++) {
        if ((byte & 0x80) != 0) {
            EEPROM_SDI(1);
        } else {
            EEPROM_SDI(0);
        }
        byte <<= 1;
        result <<= 1;

        EEPROM_SCK(0);
        Delay(SPI_DELAY);
        EEPROM_SCK(1);

        //read MISO on rising edge
        if (EEPROM_SDO() == 1) {
            result++;
        }

        Delay(SPI_DELAY);
    }

    return result;
}
/* SPI BITBANG DRIVER - END*/

/* N95160 EEPROM DRIVER - START */
#define EEPROM_PAGE_SIZE 64
#define EEPROM_PAGE_SIZE_FLOATS EEPROM_PAGE_SIZE / sizeof(float)
#define EEPROM_TEST_VALUE 0x10

#define EEPROM_settings_page 1
#define EEPROM_statistics_page 3
#define CALIBRATION_START_PAGE 10


static void EEPROM_enable_writing(void) {
    EEPROM_CS_on();
    EEPROM_WP(1);
    SPI_transmit_byte(0x06);
    EEPROM_CS_off();
}

static void EEPROM_disable_writing(void) {
    EEPROM_CS_on();
    SPI_transmit_byte(0x05);
    EEPROM_WP(0);
    EEPROM_CS_off();

}

static uint8_t checksum(uint8_t * data, uint16_t offset, uint16_t count) {
    uint32_t sum = 0;
    uint16_t counter;
    for (counter = offset; counter < count+offset; counter++) {
        sum += data[counter];
    }
    return (uint8_t) (~sum);
}

static uint8_t EEPROM_write_page(uint8_t * data, uint16_t page) {
    uint16_t address = page * EEPROM_PAGE_SIZE;
    uint8_t counter;

    data[0] = checksum(data, 1, EEPROM_PAGE_SIZE-1);

    EEPROM_enable_writing();
    EEPROM_CS_on();

    SPI_transmit_byte(0x02);
    SPI_transmit_byte((uint8_t) (address >> 8));
    SPI_transmit_byte((uint8_t) (address));

    for (counter = 0; counter < EEPROM_PAGE_SIZE; counter++) {
        SPI_transmit_byte(data[counter]);
    }

    EEPROM_CS_off();
    EEPROM_disable_writing();

    return data[0];
}

void EEPROM_write_page_raw(uint8_t * data, uint16_t page) {
    uint16_t address = page * EEPROM_PAGE_SIZE;
    uint8_t counter;

    EEPROM_enable_writing();
    EEPROM_CS_on();

    SPI_transmit_byte(0x02);
    SPI_transmit_byte((uint8_t) (address >> 8));
    SPI_transmit_byte((uint8_t) (address));

    for (counter = 0; counter < EEPROM_PAGE_SIZE; counter++) {
        SPI_transmit_byte(data[counter]);
    }

    EEPROM_CS_off();
    EEPROM_disable_writing();
}

static bool EEPROM_read_page(uint8_t * data, uint16_t page) {
    uint16_t address = page * EEPROM_PAGE_SIZE;
    uint8_t counter;

    EEPROM_CS_on();

    SPI_transmit_byte(0x03);
    SPI_transmit_byte((uint8_t) (address >> 8));
    SPI_transmit_byte((uint8_t) (address));

    for (counter = 0; counter < EEPROM_PAGE_SIZE; counter++) {
        data[counter] = SPI_transmit_byte(0x00);
    }

    EEPROM_CS_off();

    bool checksum_ok = false;
    if (data[0] == checksum(data, 1, EEPROM_PAGE_SIZE - 1))
    {
        checksum_ok = true;
    }
    return checksum_ok;
}

void EEPROM_read_page_raw(uint8_t * data, uint16_t page) {
    uint16_t address = page * EEPROM_PAGE_SIZE;
    uint8_t counter;

    EEPROM_CS_on();

    SPI_transmit_byte(0x03);
    SPI_transmit_byte((uint8_t) (address >> 8));
    SPI_transmit_byte((uint8_t) (address));

    for (counter = 0; counter < EEPROM_PAGE_SIZE; counter++) {
        data[counter] = SPI_transmit_byte(0x00);
    }

    EEPROM_CS_off();
}

static inline bool compare_two_pages(uint8_t * data1, uint8_t * data2) {
    uint8_t counter;
    for (counter = 0; counter < EEPROM_PAGE_SIZE; counter++) {
        //dprintf("%d <=> %d\r\n", data1[counter], data2[counter]);
        if (data1[counter] != data2[counter]) {
            return false;
        }
    }
    return true;
}

/* write page Fully-Tested (read and compared) */
static bool EEPROM_write_page_FT(uint8_t * data, uint16_t page) {
    EEPROM_write_page(data, page);
    blocking_delay(5);
    uint8_t data_read[EEPROM_PAGE_SIZE];
    EEPROM_read_page(data_read, page);
    return compare_two_pages(data, data_read);
}

bool EEPROM_save_settings(void){
    debug_settings();
    
    uint8_t data_to_write[EEPROM_PAGE_SIZE];
    uint8_t checksum_offset = 1;
    memcpy(&data_to_write[checksum_offset], &device_settings, sizeof (DEVICE_SETTINGS_t));
    if (EEPROM_write_page_FT(data_to_write, EEPROM_settings_page) == false) {
        dprintf_colour("[RED]ERROR: EEPROM - settings saving[WHITE]\r\n");
        //throw error
    }
    else{
        dprintf_colour("[GREEN]EEPROM - settings saved OK[WHITE]\r\n");
        //TODO - save backup as well
    }
    return false;
}

bool EEPROM_read_settings(void) {
    uint8_t data_to_read[EEPROM_PAGE_SIZE];
    uint8_t checksum_offset = 1;
    if (EEPROM_read_page(data_to_read, EEPROM_settings_page) == false) {
        
        int i=0,j=0;
        //test if eeprom page is full of 0xFF so it is new chip
        for(i=0;i<EEPROM_PAGE_SIZE;i++){
            if(data_to_read[i] == 255){
                j++;
            }
        }
        
        dprintf_colour("[RED]ERROR: NEW EEPROM detected - [WHITE]\r\n" + j);
        
        if(j == 64){
            dprintf_colour("[RED]ERROR: NEW EEPROM detected - filling in with defaults[WHITE]\r\n");
            fill_in_eeprom();
            PDAB_Error_Status(3, 35);
        }
        else
        {
            dprintf_colour("[RED]ERROR: EEPROM - settings checksum[WHITE]\r\n");
            PDAB_Error_Status(3, 40);
        }
        return false;
        //TODO - read backup
    }
    else
    {
        memcpy(&device_settings,&data_to_read[checksum_offset], sizeof(DEVICE_SETTINGS_t));
        dprintf_colour("[GREEN]EEPROM - settings checksum OK[WHITE]\r\n");
        return true;
    }
    return false;
}

bool EEPROM_save_statistics(void){
    uint8_t data_to_write[EEPROM_PAGE_SIZE];
    uint8_t checksum_offset = 1;
    dprintf_colour("[YELLOW]EEPROM - total scans: %d[WHITE]\r\n", (uint16_t)device_statistics.scans_counter);
    memcpy(&data_to_write[checksum_offset], &device_statistics, sizeof (DEVICE_STATISTICS_t));
    if (EEPROM_write_page_FT(data_to_write, EEPROM_statistics_page) == false) {
        dprintf_colour("[RED]ERROR: EEPROM - statistics saving[WHITE]\r\n");
        //throw error
    }
    else{
        dprintf_colour("[GREEN]EEPROM - statistics saved OK[WHITE]\r\n");
    }
    return false;
}

bool EEPROM_read_statistics(void){
    uint8_t data_to_read[EEPROM_PAGE_SIZE];
    uint8_t checksum_offset = 1;
    if (EEPROM_read_page(data_to_read, EEPROM_statistics_page) == false) {
        if(data_to_read[0] != 255)
        {
            dprintf_colour("[RED]ERROR: EEPROM - statistics checksum[WHITE]\r\n");
            PDAB_Error_Status(3, 50);
            return false;
        }
        if(data_to_read[1] == 255)
        {
            dprintf_colour("[RED]EEPROM - statistics empty - checksum = 0xFF[WHITE]\r\n");
            pdabData.eeprom_stats_read_correct = false;
        }
    }
    else
    {
        memcpy(&device_statistics,&data_to_read[checksum_offset], sizeof(DEVICE_STATISTICS_t));
        pdabData.eeprom_stats_read_correct = true;
        
        dprintf_colour("[GREEN]EEPROM - statistics checksum OK[WHITE]\r\n");
        dprintf_colour("[YELLOW]EEPROM - total scans: %d[WHITE]\r\n", (uint16_t)device_statistics.scans_counter);
        return true;
    }
    return false;
}

bool EEPROM_read_calibration(void) {
    int page_pos = 0;
    uint8_t header_page[EEPROM_PAGE_SIZE];
    if( EEPROM_read_page(header_page, 9) == false){
        dprintf_colour("[RED]ERROR:EEPROM - cal. header checksum[WHITE]\r\n");
        PDAB_Error_Status(3, 20);
    }
    else
    {
        dprintf_colour("[GREEN]EEPROM - cal. header checksum OK[WHITE]\r\n");
    }
    #define DEVICE_NAME_LENGTH 16
    union calibration_header_t {
        uint8_t bytes[EEPROM_PAGE_SIZE];
        struct {
            uint8_t this_checksum;
            uint8_t calibration_checksum;
            uint8_t d2;
            uint8_t d3;
            uint32_t calibration_id;
            uint32_t device_id;
            char device_name[DEVICE_NAME_LENGTH];
        };
    };
    static union calibration_header_t calibration_header;
    memcpy((void *) &calibration_header, header_page, EEPROM_PAGE_SIZE);
    
    device_id = calibration_header.device_id;
    pdabData.device_id = calibration_header.device_id;
    pdabData.calibration_id = calibration_header.device_id;
    memcpy(&pdabData.device_name, &calibration_header.device_name,DEVICE_NAME_LENGTH);
    
    dprintf_colour("[YELLOW]EEPROM - Device name: %s[WHITE]\r\n", pdabData.device_name);
    dprintf_colour("[YELLOW]EEPROM - Calibration id: %d[WHITE]\r\n", pdabData.calibration_id);
    dprintf_colour("[YELLOW]EEPROM - Device id: %d[WHITE]\r\n", device_id);
    //dprintf("EEPROM - calibration_header - d2 %d, d3 %d, ci %d, di %d\r\n",calibration_header.d2, calibration_header.d3, calibration_header.calibration_id, calibration_header.device_id);
    
    uint8_t temp_page[EEPROM_PAGE_SIZE];
    int number_of_pages = ((PDAB_SCAN_LENGTH_16 * sizeof (float)) / EEPROM_PAGE_SIZE) + 1;

    for (page_pos = 0; page_pos < number_of_pages; page_pos++) {
        int page_pos_cycle = (page_pos + CALIBRATION_START_PAGE);
        int array_pos_cycle = (EEPROM_PAGE_SIZE_FLOATS) * page_pos;

        EEPROM_read_page_raw(temp_page, page_pos_cycle);

        if (page_pos == number_of_pages - 1) {
            /* last page has only half of the size of data */
            memcpy(&cal_data[array_pos_cycle], temp_page, EEPROM_PAGE_SIZE / 2);
        } else {
            memcpy(&cal_data[array_pos_cycle], temp_page, EEPROM_PAGE_SIZE);
        }

//#define DEBUG_EEPROM
#ifdef DEBUG_EEPROM
        float temp_page_float_test[EEPROM_PAGE_SIZE_FLOATS];
        memcpy(temp_page_float_test, temp_page, EEPROM_PAGE_SIZE);
        dprintf("EEPROM - page_pos %d, cal_data read %f \r\n", page_pos_cycle, temp_page_float_test[0]);
#endif
    }
    
    if (calibration_header.calibration_checksum != checksum((void *)&cal_data, 0, (PDAB_SCAN_LENGTH_16 * sizeof (float)))) {
        dprintf_colour("[RED]ERROR:EEPROM - calibration checksum[WHITE]\r\n");
        PDAB_Error_Status(3, 25);
    } else {
        dprintf_colour("[GREEN]EEPROM - calibration checksum OK[WHITE]\r\n");
    }
    return false;
}

typedef struct {
union {
        uint8_t bytes[64+10];
        struct{
            uint8_t cmd;
            uint8_t key1;
            uint8_t key2;
            uint8_t len;
            uint8_t checksum;
            uint16_t page;
            uint8_t page_data[64];
        };
    };
}eeprom_page_t;

void EEPROM_read_to_USB(const uint8_t * data)
{
    static uint8_t counter = 0;
    eeprom_page_t eeprom_page;
    static eeprom_page_t MAKE_BUFFER_DMA_READY eeprom_page_to_send;
    uint16_t eeprom_page_t_size = sizeof(eeprom_page_t);
    
    eeprom_page.page = ((uint16_t)data[4]<<8) + data[3];
    eeprom_page.cmd = 'R';
    eeprom_page.key1 = 0x25;
    eeprom_page.key2 = 0x68;
    
    dprintf_colour("[YELLOW]USB: page %d sent.[WHITE]\r\n", eeprom_page.page);

    EEPROM_read_page_raw(eeprom_page.page_data, eeprom_page.page);
    
    eeprom_page.checksum = 68;
    eeprom_page.len = 67;
    eeprom_page.bytes[5] = counter;
    counter++;
    
    //assign last two bytes with page bytes for pack consistency check in software
    eeprom_page.bytes[eeprom_page_t_size - 2] = data[3];
    eeprom_page.bytes[eeprom_page_t_size - 1] = data[4];

    int state = USB_DEVICE_RESULT_ERROR;
    if(USB_is_device_attached())
    {
        memcpy(&eeprom_page_to_send,&eeprom_page,sizeof(eeprom_page_to_send));

        state = USB_Return_Data((const void *) &eeprom_page_to_send.bytes, sizeof(eeprom_page_to_send), USB_DEVICE_TRANSFER_FLAGS_MORE_DATA_PENDING);
    }
    if( USB_DEVICE_RESULT_ERROR_TRANSFER_QUEUE_FULL == state )
    {
        //too much data
    }
    else
    {  
        USB_Clear_Endpoints();
    }
}

void EEPROM_save_from_USB(const uint8_t * data)
{
    eeprom_page_t eeprom_page;
    eeprom_page.page = ((uint16_t)data[4]<<8) + data[3];
    memcpy(&eeprom_page.page_data,&data[5],64);
    
    dprintf_colour("[YELLOW]USB: eeprom page %d - saved[WHITE]\r\n", eeprom_page.page);

    EEPROM_write_page_raw(eeprom_page.page_data, eeprom_page.page);
}

static inline void verbal(const char * string, uint8_t d1, uint8_t d2) {
    dprintf(string, d1, d2);
}

static inline void assign_device_settings(void){
    device_settings.LCD_BRIGHTNESS = 101;
    device_settings.LED_BRIGHTNESS = 102;
    device_settings.LED_FADE_RATE = 200;
    device_settings.VOLTAGE_TRESHOLD = 13;
    device_settings.P1_TRESHOLD = 26214;
    device_settings.P2_TRESHOLD = 786;
    device_settings.MIN_SEPARATION = 300;
    device_settings.MAX_SEPARATION = 800;
    device_settings.MIN_FWHM = 35;
    device_settings.MAX_FWHM = 75;
    device_settings.CAMERA_HSTART = 177;
    device_settings.CAMERA_VSTART = 35;
}

static void fill_in_eeprom(void) {


    dprintf_colour("[RED]ERROR: EEPROM FILLING[WHITE]\r\n");
    
    verbal("EEPROM - test routine - START\r\n", 0, 0);
    
    uint8_t paged[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    uint8_t page1[] = {
        0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    
        verbal("------- CYCLE - %d\r\n", 0, 0);
        verbal("EEPROM - test routine - write page 1 -run\r\n", 0, 0);
        EEPROM_write_page(page1, 0);
        verbal("EEPROM - test routine - write page 1 ok\r\n", 0, 0);
        blocking_delay(5);

        assign_device_settings();

        uint8_t data_to_write[EEPROM_PAGE_SIZE];
        uint8_t checksum_offset = 1;
        uint8_t settings_page = 1;
        uint8_t settings_page_backup = 2;


        verbal("EEPROM - test routine - write page 2 - settings \r\n", 0, 0);

        memcpy(&data_to_write[checksum_offset], &device_settings, sizeof (DEVICE_SETTINGS_t));
        if (EEPROM_write_page_FT(data_to_write, settings_page) == false) {
            verbal("EEPROM - settings save error\r\n", 0, 0);
            PDAB_Error_Status(3, 30);
        }





        verbal("EEPROM - settings saved ok\r\n", 0, 0);
        memcpy(&data_to_write[checksum_offset], &device_settings, sizeof (DEVICE_SETTINGS_t));
        if (EEPROM_write_page_FT(data_to_write, settings_page_backup) == false) {
            verbal("EEPROM - settings backup save error\r\n", 0, 0);
            PDAB_Error_Status(3, 31);
        }
        verbal("EEPROM - settings backup saved ok\r\n", 0, 0);


        uint8_t page2[] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        };
        uint8_t stats_page = 2;



        if (EEPROM_write_page_FT(page2, stats_page) == false) {
            verbal("EEPROM - stats_page save error\r\n", 0, 0);
            PDAB_Error_Status(3, 32);
        }
        verbal("EEPROM - stats_page saved ok\r\n", 0, 0);

    

    uint8_t temp_page[EEPROM_PAGE_SIZE];
    float temp_page_float_test[EEPROM_PAGE_SIZE_FLOATS];

#define calibration_header_page 9
#define calibration_start_page 10
#define eeprom_size 16
#define statistics_page 7
#define device_name_page 8

    int page_pos = 0;
    int number_of_pages = ((5000 * 4) / EEPROM_PAGE_SIZE) + 1;
    int page_pos_cycle = 0;
    int array_pos_cycle = 0;
    
    
        
        union calibration_header_t{
            uint8_t bytes[EEPROM_PAGE_SIZE];
            struct {
                uint8_t this_checksum;
                uint8_t calibration_checksum;
                uint8_t d2;
                uint8_t d3;
                uint32_t calibration_id;
                uint32_t device_id;
                char device_name[16];
            };
        };
        union calibration_header_t calibration_header;
        
        // clean the struct
        int i;
        for(i=0;i<EEPROM_PAGE_SIZE;i++)
        {
            calibration_header.bytes[i]=0;
        }
        
        calibration_header.calibration_id = 0;
        calibration_header.device_id = 0;
        calibration_header.d2 = 3;
        calibration_header.d3 = 4;
        calibration_header.calibration_checksum = checksum((void *)&cal_data,0,(PDAB_SCAN_LENGTH_16 * sizeof(float)));
        strcpy(calibration_header.device_name, "I'm brand new!!!");
        calibration_header.this_checksum  = checksum(calibration_header.bytes,0,EEPROM_PAGE_SIZE);
        

        memcpy(temp_page, (void *)&calibration_header, EEPROM_PAGE_SIZE);
        if (EEPROM_write_page_FT(temp_page, calibration_header_page) == false) {
            verbal("EEPROM - calibration_header_page save error\r\n", 0, 0);
            PDAB_Error_Status(3, 33);
        }
        verbal("EEPROM - calibration_header_page saved ok\r\n", 0, 0);


        for (page_pos = 0; page_pos < number_of_pages; page_pos++) {
            page_pos_cycle = (page_pos + calibration_start_page);
            array_pos_cycle = (EEPROM_PAGE_SIZE_FLOATS) * page_pos;
            
            void * ptr = (void *) &cal_data[array_pos_cycle];
            memcpy((void *) &temp_page, ptr, EEPROM_PAGE_SIZE);

            EEPROM_write_page_raw(temp_page, page_pos_cycle);
            blocking_delay(7);

            memcpy(temp_page_float_test, temp_page, EEPROM_PAGE_SIZE);
        }

        float cal_read[PDAB_SCAN_LENGTH_16];
        for (page_pos = 0; page_pos < number_of_pages; page_pos++) {
            page_pos_cycle = (page_pos + calibration_start_page);
            array_pos_cycle = (EEPROM_PAGE_SIZE_FLOATS) * page_pos;

            EEPROM_read_page_raw(paged, page_pos_cycle);
            blocking_delay(5);

            memcpy(temp_page_float_test, paged, EEPROM_PAGE_SIZE);
            memcpy(&cal_read[array_pos_cycle], paged, EEPROM_PAGE_SIZE);
        }
        
        if(checksum((void *)&cal_data,0,(PDAB_SCAN_LENGTH_16 * sizeof(float))) != calibration_header.calibration_checksum)
        {
            verbal("EEPROM - calibration save/read/checksum error\r\n", 0, 0);
            PDAB_Error_Status(3, 40);
        }
        else
        {
            verbal("EEPROM - calibration save/read/checksum OK\r\n", 0, 0);
        }
        
        
    
    verbal("\r\nEEPROM - test routine - END\r\n", 0, 0);

    PDAB_Error_Status(3, 35);//throw error on PI/LCD
}

static void debug_settings(void)
{
//    device_settings.LCD_BRIGHTNESS = 64;
//    device_settings.LED_BRIGHTNESS = 64;
//    device_settings.LED_FADE_RATE = 0;
//    device_settings.VOLTAGE_TRESHOLD = 13;
//    device_settings.P1_TRESHOLD = 26214;
//    device_settings.P2_TRESHOLD = 1311;
//    device_settings.MIN_SEPARATION = 300;
//    device_settings.MAX_SEPARATION = 700;
//    device_settings.MIN_FWHM = 35;
//    device_settings.MAX_FWHM = 75;
//    device_settings.CAMERA_HSTART = 177;
//    device_settings.CAMERA_VSTART = 28;
    
    dprintf("device_settings - LCD_BRIGHTNESS %d\r\n",device_settings.LCD_BRIGHTNESS);
    dprintf("device_settings - LED_BRIGHTNESS %d\r\n",device_settings.LED_BRIGHTNESS);
    dprintf("device_settings - LED_FADE_RATE %d\r\n",device_settings.LED_FADE_RATE);
    dprintf("device_settings - VOLTAGE_TRESHOLD %d\r\n",device_settings.VOLTAGE_TRESHOLD);
    dprintf("device_settings - P1_TRESHOLD %d\r\n",device_settings.P1_TRESHOLD);
    dprintf("device_settings - P2_TRESHOLD %d\r\n",device_settings.P2_TRESHOLD);
    dprintf("device_settings - MIN_SEPARATION %d\r\n",device_settings.MIN_SEPARATION);
    dprintf("device_settings - MAX_SEPARATION %d\r\n",device_settings.MAX_SEPARATION);
    dprintf("device_settings - MIN_FWHM %d\r\n",device_settings.MIN_FWHM);
    dprintf("device_settings - MAX_FWHM %d\r\n",device_settings.MAX_FWHM);
    dprintf("device_settings - CAMERA_HSTART %d\r\n",device_settings.CAMERA_HSTART);
    dprintf("device_settings - CAMERA_VSTART %d\r\n",device_settings.CAMERA_VSTART);
}