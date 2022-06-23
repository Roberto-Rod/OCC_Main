/**
 * @file main2.c
 * @author rzeller, voccoto Ltd
 * @brief Occuity NDPA test application.
 * @version 0.1
 * @date 2020-10-26
 * 
 * @copyright Copyright (c) 2020
 * 
 * @note Loading an interpolated data set from a csv and processing it further. PC only
 * @note To compile optimised version on the pc use "gcc -o main2 main2.c ndpa.c ndpa_tools.c -Dx86 -lm -Ofast [-std=c89]"
 * @note To compile with debug info on the pc use "gcc -o main2 main2.c ndpa.c ndpa_tools.c -Dx86 -lm -g -O0 -fno-inline -DDEBUG [-std=c89]"
 * 
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

void __sleep() {struct timespec tim, tim2; tim.tv_sec = 0; tim.tv_nsec = 100,000,000; nanosleep(&tim , &tim2); }
#include <string.h>
#include <stdio.h>

#include "ndpa_tools.h"
#include "ndpa.h"

#define RAW_SCANS   (MAX_BLOCKS * MAX_SCANS)
#define RAW_LINES   MAX_POSITIONS
#include "tools/csv.h"

typedef clock_t    tick_t;

tick_t GetTick(void) {
    return clock();
}
float ElapsedMs(tick_t startCnt, tick_t endCnt) {
    return 1000.0*((double)(endCnt - startCnt)/CLOCKS_PER_SEC);
}

// Try to enable core dumps
void core_init(void) {
    struct rlimit core_limit;
    core_limit.rlim_cur = RLIM_INFINITY;
    core_limit.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &core_limit);
}

int main (void) {
    int iret = 0;
    bool fOk = true;

    core_init();

    printf("\r\nNDPA Speed Test...\r\n\r\n");
    printf("\tBlock-count: %d\r\n", MAX_BLOCKS);
    printf("\tScans-per-count: %d\r\n", MAX_SCANS);
#if USE_RESTRICTED_SCANS
    printf("\tRestricted-window-size: %d\r\n", MAX_WINDOW_SIZE);
#endif
    printf("\tRaw-scan-size: %d\r\n\r\n", MAX_POSITIONS);

    printf("Initialising memory buffers...\r\n");
    ndpa_initialise();

    printf("Allocating buffers for csv data...\r\n");
    fptype *tst_y = (fptype*)calloc(MAX_BLOCKS * MAX_SCANS * MAX_POSITIONS, sizeof(fptype));
    if (!tst_y) {
        printf("Failed allocating tst_y!\n");
        return 101;
    }

    printf("Loading interpolated data set from csv...\r\n");
    iret = load_raw_fpy("NPDA-Scan 17a.csv", __ndpa_x, tst_y, 1, MAX_BLOCKS * MAX_SCANS);
    if (iret) {
        printf("ERROR: Failed to load data csv!\n");
        return 1;
    }

    // Dumping input data into a csv, PC only
    FILE *f = fopen("intrpd-calib-input-dump.csv", "wt");
    for (int i=0; i<MAX_POSITIONS; i++) fprintf(f, "%g\n", __ndpa_x[i]);
    fclose(f);
    f = fopen("intrpd-scan-input-dump.csv", "wt");
    for (int i=0; i<MAX_WINDOW_SIZE; i++) {
        for (int s=0; s<MAX_BLOCKS*MAX_SCANS; s++) {
            fprintf(f, "%s%u", (s?", ":""), (unsigned)tst_y[s*MAX_WINDOW_SIZE + i]);
        }
        fprintf(f, "\n");
    }
    fclose(f);

    tick_t startCnt = GetTick();
    ndpa_measurement_start();
    fptype *ty = (fptype*)tst_y;
    __interpolated_size = MAX_POSITIONS;
    do {
        printf("\tProcessing block %d...\r\n", __block_cnt);
        if (!(iret = ndpa_block_start())) {
            printf("\t\tProcessing %d scans of the file as one block...\r\n", MAX_SCANS);
            do {
                // already have the interpolated data
                memcpy(__ndpa_y, ty, MAX_POSITIONS*sizeof(fptype));
                ty += MAX_WINDOW_SIZE;
                
                // Process scan but do not interpolate
                if ((iret = update_average(NULL, NULL))) {
                    printf("\t\t~~~~~~ ERROR: update_average() = %d\r\n", iret);
                }
                __scan_cnt ++;
                if (!iret) {
                    /* All scans are valid unless there was an error */
                    __valid_scans ++;
                }
            } while (__scan_cnt < MAX_SCANS);

            // Dumping block averaged and/or convolved data into a csv 
            char sfn[32];
            sprintf(sfn, "avg-data-%d.csv", __block_cnt);
            FILE *favg = fopen(sfn, "wt");
            for (int i=0; i<__interpolated_size; i++) fprintf(favg, "%g\n", __ndpa_avg[i]);
            fclose(favg);

            sprintf(sfn, "conv-data-%d.csv", __block_cnt);
            FILE *fconv = fopen(sfn, "wt");
            for (int i=0; i<__interpolated_size; i++) fprintf(favg, "%g\n", __ndpa_conv[i]);
            fclose(favg);

            if ((iret = ndpa_block_end())) {
                printf("\t\t~~~~~~ ERROR: ndpa_block_end() = %d\r\n", iret);
            }
            printf("\t\tNumber of valid scans used %d vs %d\r\n", __valid_scans, __scan_cnt);
        }
        else {
            printf("ERROR: ndpa_block_start() = %d\r\n", iret);
        }
    } while (__block_cnt < MAX_BLOCKS);
    ndpa_measurement_end();

    printf("\r\nDone.\r\n");
    printf("Elapsed time %f msec\r\n", ElapsedMs(startCnt, GetTick()));

    free(tst_y);

    return ( 0 );
}


/*******************************************************************************
 End of File
*/
