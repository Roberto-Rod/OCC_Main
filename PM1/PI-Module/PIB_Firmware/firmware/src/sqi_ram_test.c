/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    sqi_ram_test.c

  @Summary
    Test SQI FRAM chip.

  @Description
    Test SQI FRAM chip.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "definitions.h"
#include "sqi_ram_test.h"
#include "drv_fram_cy15b104.h"

#define TEST_BUFFER_LENGTH          (64u * 1024u)

#define RW_BUFFER_SIZE              (16u * 1024u)
#define FRAM_SIZE_IN_BYTES          (512u * 1024u)

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

void monitor_cs_busy()
{
    uint32_t i;
    uint32_t d;

    for (i = 0; i < 100000; i++)
    {
        for (d = 0; d < 100; d++);

        if (!FRAM_is_fram_free_old())
        {
            dputs_colour("[GREEN]Seen a FRAM busy![WHITE]\r\n");
            break;
        }
    }
}

/* test that the entire FRAM chip can be written and the read */
void sqi_fram_write_read_test()
{
    uint32_t address;
    static uint32_t buffer[RW_BUFFER_SIZE];
    uint32_t first_failure;
    uint32_t blocks;
    uint32_t block;
    uint32_t block_size;
    uint32_t i;
    static bool upwards = true;
    uint32_t write_value;
    uint32_t good;
    uint32_t bad;

    block_size = RW_BUFFER_SIZE * sizeof(uint32_t);
    blocks = FRAM_SIZE_IN_BYTES / block_size;
    dprintf_colour("[YELLOW]Writing FRAM %d blocks, %d byte block size, direction %s ...[WHITE]\r\n", blocks, block_size, upwards ? "upwards" : "downwards");

    address = 0;
    for (block = 0; block < blocks; block++)
    {
        for (i = 0; i < RW_BUFFER_SIZE; i++)
        {
            write_value = address;

            if (!upwards)
            {
                write_value ^= 0xffffffffu;
            }

            buffer[i] = write_value;
            address++;
        }

        FRAM_write(block * block_size, (uint8_t *) buffer, RW_BUFFER_SIZE * sizeof(uint32_t));
    }

    dputs_colour("[YELLOW]Verifying FRAM ...[WHITE]\r\n");

    /* verify the contents of the FRAM */

    first_failure = 0xffffffffu;
    address = 0;
    good = 0;
    bad = 0;

    for (block = 0; block < blocks; block++)
    {
        FRAM_read(block * block_size, (uint8_t *) buffer, RW_BUFFER_SIZE * sizeof(uint32_t));

        for (i = 0; i < RW_BUFFER_SIZE; i++)
        {
            write_value = address;

            if (!upwards)
            {
                write_value ^= 0xffffffffu;
            }

            if (buffer[i] != write_value)
            {
                bad++;

                if (address < first_failure)
                {
                    dprintf_colour("[RED]Expecting 0x%08x but read 0x%08x[WHITE]\r\n", write_value, buffer[i]);            
                    first_failure = address;
                    //break;
                }
            }
            else
            {
                good++;
            }

            address++;
        }
    }

    if (first_failure == 0xffffffffu)
    {
        dputs_colour("[GREEN]FRAM test succeeded!![WHITE]\r\n");
    }
    else
    {
        dprintf_colour("[RED]FRAM test failed, first failure at address 0x%08x[WHITE]\r\n", first_failure);
        dprintf_colour("[GREEN]Good %d, [RED]bad %d[WHITE]\r\n", good, bad);
    }

    upwards = !upwards;
}

void test_sqi_fram(void)
{
    //sqi_fram_write_read_test();
    //disable_FRAM();
    //dputs_colour("[GREEN]Hello! I'm running[WHITE]\r\n");
}
