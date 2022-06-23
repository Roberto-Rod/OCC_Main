/**
 * @file csv2header.c
 * @author rz
 * @brief Converting csv file data into a header file without window restrictions. gcc -o csv2header csv2header.c -lm -Ofast
 * @version 0.1
 * @date 2020-09-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char   byte;
typedef unsigned short  word;
typedef unsigned int    dword;

#define USE_DOUBLE_PRECISION    0       /* 1-double, 0-float (mostly) */
#define RAW_SCANS               300      // Number of scans in a block. Should be 300 for production. For testing in range [1...300]
#define RAW_LINES               5000    // Size of one scan
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
#define FHEADER "test_data1.h"

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

    FILE *f = fopen(FHEADER, "wt");
    fprintf(f, "/**\n * @file %s\n * @author tools/csv2header.c\n * @brief Test data file for main.c\n * @version 1\n * @note SCAN SIZE: %d\n * @note NUMBER OF SCANS: %d\n * @note BASED ON: %s\n*/\n\n\n", FHEADER, RAW_LINES, RAW_SCANS, FCSV);

    fprintf(f, "static const float tst_x0[%d] = {", RAW_LINES);
    for (int i=0; i<RAW_LINES; i++) {
        fprintf(f, (i ? ", %g" : "%g"), sx0[i]); 
        if (i%500 == 499) fprintf(f, "\n");
    }
    fprintf(f, "};\n\n");

    fprintf(f, "static const word tst_y0[%d] = {", RAW_SCANS * RAW_LINES);
    for (int i=0; i<RAW_SCANS * RAW_LINES; i++) {
        fprintf(f, (i ? ", %u" : "%u"), (unsigned)sy0[i]); 
        if (i%500 == 499) fprintf(f, "\n");
    }
    fprintf(f, "};\n\n");

    fclose(f);

    return 0;
}
