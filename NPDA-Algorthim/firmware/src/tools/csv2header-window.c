/**
 * @file csv2header-window.c
 * @author rz
 * @brief Converting csv file data into a header file. gcc -o csv2header-window csv2header-window.c -lm -Ofast
 * @version 0.1
 * @date 2020-09-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

typedef unsigned char   byte;
typedef unsigned short  word;
typedef unsigned int    dword;

#define USE_DOUBLE_PRECISION    0       /* 1-double, 0-float (mostly) */
#define PADDING                 1       /* 0-Zero padding, 1-Use min(sy0) */

#define CALIB_SIZE              5000     // Like MAX_POSITIONS
#define INTERPOLATION_DISTANCE  0.001   // Used if RAW_LINES < CALIB_SIZE
#define RAW_SCANS               300      // Number of scans in a block. Should be 300 for production. For testing in range [1...300]
#define RAW_LINES               5000    // Size of one scan
#define WINDOW_SIZE             1000//1000//!!3200    // Size of data window
#define THRESHOLD               25000   // Peak threshold
#define WINDOW_HEADER           200//!!1100     // Number of points before threshold, might be padding if WINDOW_SIZE > RAW_LINES
#if USE_DOUBLE_PRECISION
    typedef double fptype;                  /* Floating point type used. Can be float or double, also change FPTYPE_MAX if this changes! */
    #define FPTYPE_MAX              DBL_MAX /* Maximum value of the current floating point type fptype. FLT_MAX or DBL_MAX from float.h */
#else
    typedef float fptype;                   /* Floating point type used. Can be float or double, also change FPTYPE_MAX if this changes! */
    #define FPTYPE_MAX              FLT_MAX /* Maximum value of the current floating point type fptype. FLT_MAX or DBL_MAX from float.h */
#endif

#include "csv.h"

#define MIN(a,b)    ((a)<(b)?(a):(b))
#define MAX(a,b)    ((a)>(b)?(a):(b))

#define FCSV    "JR-2020-08-20-02-21-29-15-300-Raw.csv"
#define FWCSV   "windowed-scan.csv"
#define FHEADER "test_data10.h"

int median_cmp(const void *a, const void *b) {
    return (*(word*)a - *(word*)b);
}
word median_vanilla(word *vector, int vector_size) {
    // I would love to loose these two lines, will loose the calloc() and use a pre-allocated worker buffer, but still hate to use memcpy()
    word *v = (word*)calloc(vector_size, sizeof(word));
    memcpy(v, vector, vector_size * sizeof(word));

    qsort(v, vector_size, sizeof(word), median_cmp);
    
    int n = vector_size >> 1;
    word m = ((vector_size & 0x1) ? v[n] : (v[n] + v[n - 1]) / 2.0);
    
    free(v);

    return m;
}

int main() {
    fptype *sx0 = (fptype*)calloc(RAW_LINES, sizeof(fptype));
    if (!sx0) {
        printf("Failed allocating sx0!\n");
        return 100;
    }
    word *sy0 = (word*)calloc(RAW_SCANS * RAW_LINES, sizeof(word));
    if (!sy0) {
        printf("Failed allocating sy0!\n");
        free(sx0);
        return 101;
    }
    int iret = load_raw(FCSV, sx0, sy0, 1, RAW_SCANS);
    if (iret) {
        printf("Failed to load data csv!\n");
        return 1;
    }

    fptype y0_min = FPTYPE_MAX;
    fptype y0_max = -FPTYPE_MAX;
    for (int i=0; i<RAW_LINES*RAW_SCANS; i++) {
        if (sy0[i] < y0_min) y0_min = sy0[i];
        if (sy0[i] > y0_max) y0_max = sy0[i];
    }
#if PADDING==0
    fptype padding_value = 0.0;
#elif PADDING==1
    fptype padding_value = y0_min;
#endif

    FILE *f = fopen(FHEADER, "wt");
    fprintf(f, "/**\n * @file %s\n * @author tools/csv2header-window.c\n * @brief Restricted test data file for main.c\n * @version 1\n * @note SCAN SIZE: %d\n * @note NUMBER OF SCANS: %d\n * @note OFFSETS: WINDOW SIZE %d\n * @note THRESHOLD %u\n * @note WINDOW HEADER %d\n * @note BASED ON: %s\n*/\n\n\n", FHEADER, RAW_LINES, RAW_SCANS, WINDOW_SIZE, THRESHOLD, WINDOW_HEADER, FCSV);

    fprintf(f, "static const float tst_x0[%d] = {", CALIB_SIZE);
    for (int i=0; i<CALIB_SIZE; i++) {
        if (RAW_LINES < CALIB_SIZE) {
            fprintf(f, (i ? ", %g" : "%g"), (float)i*INTERPOLATION_DISTANCE); 
        }
        else {
            fprintf(f, (i ? ", %g" : "%g"), sx0[i]); 
        }
        if (i%500 == 499) fprintf(f, "\n");
    }
    fprintf(f, "};\n\n");

    int y0cnt = 0;
    word *offsets = calloc(RAW_SCANS, sizeof(word));
    word *medians = calloc(RAW_SCANS, sizeof(word));
    fprintf(f, "static const word tst_y0[%d] = {", RAW_SCANS * WINDOW_SIZE);
    for (int s=0; s<RAW_SCANS; s++) {
        char padding_before = 0;
        word *y0 = sy0 + s*RAW_LINES;

        medians[s] = median_vanilla(y0, RAW_LINES);
        if (RAW_LINES > WINDOW_SIZE) {
            // find threshold point
            int thridx = 0;
            for (thridx=0; thridx<RAW_LINES && y0[thridx] < THRESHOLD; thridx++) ;
            offsets[s] = (thridx<RAW_LINES ? MAX(thridx-WINDOW_HEADER, 0) : 0);
        }
        else {
            // No windowing needed
            offsets[s] = 0;
            if (RAW_LINES < WINDOW_SIZE && WINDOW_HEADER > 0) {
                // Padding before with min value
                padding_before = 1;
                if (!s) printf("Padding before = %d with %g\n", MIN(WINDOW_SIZE - RAW_LINES, WINDOW_HEADER), padding_value);
                for (int i=0; i<MIN(WINDOW_SIZE - RAW_LINES, WINDOW_HEADER); i++) {
                    fprintf(f, (i!=0 || s!=0 ? ", %g" : "%g"), padding_value); 
                    y0cnt ++;
                }
            }
        }
        for (int i=0; i<(WINDOW_SIZE <= RAW_LINES ? WINDOW_SIZE : RAW_LINES); i++) {
            fprintf(f, (i!=0 || s!=0 || padding_before ? ", %u" : "%u"), (unsigned)y0[offsets[s] + i]); 
            y0cnt ++;
        }

        if (RAW_LINES + WINDOW_HEADER < WINDOW_SIZE) {
            // Padding after with min value
            if (!s) printf("Padding after = %d with %g\n", WINDOW_SIZE - RAW_LINES - MIN(WINDOW_SIZE - RAW_LINES, WINDOW_HEADER), padding_value);
            for (int i=0; i<WINDOW_SIZE - RAW_LINES - MIN(WINDOW_SIZE - RAW_LINES, WINDOW_HEADER); i++) {
                fprintf(f, ", %g", padding_value); 
                y0cnt ++;
            }
        }

        fprintf(f, "\n");
    }
    fprintf(f, "};\n\n");

    printf("y0cnt = %d\n", y0cnt);

    fprintf(f, "static const word tst_offsets[%d] = {", RAW_SCANS);
    for (int i=0; i<RAW_SCANS; i++) {
        fprintf(f, (i ? ", %d" : "%d"), offsets[i]); 
    }
    fprintf(f, "};\n\n");

    fprintf(f, "static const word tst_medians[%d] = {", RAW_SCANS);
    for (int i=0; i<RAW_SCANS; i++) {
        fprintf(f, (i ? ", %u" : "%u"), (unsigned)medians[i]); 
    }
    fprintf(f, "};\n\n");

    fclose(f);

    FILE *fw = fopen(FWCSV, "wt");
    for (int i=0; i<WINDOW_SIZE; i++) {
        for (int s=0; s<RAW_SCANS; s++) {
            fprintf(fw, "%s%d", (s?", ":""), (unsigned)((sy0 + s*RAW_LINES + offsets[s])[i]));
        }
        fprintf(fw, "\n");
    }
    fclose(fw);

    return 0;
}