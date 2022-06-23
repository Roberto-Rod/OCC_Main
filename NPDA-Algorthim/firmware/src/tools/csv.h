/*
  Very simple CSV read
*/

#ifndef __CSV_H__
#define __CSV_H__

#define RAW_LINE_BUFF_SIZE      2048

// Load a (sub)set of the raw data file [start_scan_idx ... end_scan_idx]
// start_scan_idx = {1...300}
// end_scan_idx = {1...300}
// All 300: start_scan_idx=1, end_scan_idx=300
// ret 0 if ok
// ignore additional columns and lines!
int load_raw(const char *raw_fn, fptype *sx0, word *sy0, int start_scan_idx, int end_scan_idx) {
    char buff[RAW_LINE_BUFF_SIZE];
    FILE *fp = fopen(raw_fn, "r"); 
    if (!fp) return 100;
    int ln = 0;

    while (fgets(buff, sizeof(buff), fp) && ln < RAW_LINES) { 
        int fld = 0; 
        char *token = strtok(buff, ","); 
        while (token != NULL && fld <= RAW_SCANS) { 
            if (fld == 0) {
                sx0[ln] = atof(token);
            } else if (fld >= start_scan_idx && fld <= end_scan_idx) {
                sy0[(fld - start_scan_idx)*RAW_LINES + ln] = (word)atoi(token);
            }
            token = strtok(NULL, ",");
            fld ++;
        }
        if (fld != RAW_SCANS+1) {
            fclose(fp);
            return 1; // Invalid data, missing column!
        }
        ln ++; 
    }
    if (ln != RAW_LINES) {
        fclose(fp);
        return 2; // Invalid data, number of measurements!
    }
// printf("X[] = {%g, ..., %g, %g}\n", sx0[0], sx0[RAW_LINES-2], sx0[RAW_LINES-1]);
// printf("Y[0] = {%d, ..., %d, %d}\n", (int)sy0[0], (int)sy0[RAW_LINES-2], (int)sy0[RAW_LINES-1]);
// printf("...\n");
// printf("Y[%d] = {%d, ..., %d, %d}\n", RAW_SCANS-2, (int)sy0[(RAW_SCANS-2)*RAW_LINES + 0], (int)sy0[(RAW_SCANS-2)*RAW_LINES + RAW_LINES-2], (int)sy0[(RAW_SCANS-2)*RAW_LINES + RAW_LINES-1]);
// printf("Y[%d] = {%d, ..., %d, %d}\n", RAW_SCANS-1, (int)sy0[(RAW_SCANS-1)*RAW_LINES + 0], (int)sy0[(RAW_SCANS-1)*RAW_LINES + RAW_LINES-2], (int)sy0[(RAW_SCANS-1)*RAW_LINES + RAW_LINES-1]);
    
    fclose(fp);
    return 0; 
}

int load_raw_fpy(const char *raw_fn, fptype *sx0, fptype *sy0, int start_scan_idx, int end_scan_idx) {
    char buff[RAW_LINE_BUFF_SIZE];
    FILE *fp = fopen(raw_fn, "r"); 
    if (!fp) return 100;
    int ln = 0;

    while (fgets(buff, sizeof(buff), fp) && ln < RAW_LINES) { 
        int fld = 0; 
        char *token = strtok(buff, ","); 
        while (token != NULL && fld <= RAW_SCANS) { 
            if (fld == 0) {
                sx0[ln] = atof(token);
            } else if (fld >= start_scan_idx && fld <= end_scan_idx) {
                sy0[(fld - start_scan_idx)*RAW_LINES + ln] = (fptype)atof(token);
            }
            token = strtok(NULL, ",");
            fld ++;
        }
        if (fld != RAW_SCANS+1) {
            fclose(fp);
            return 1; // Invalid data, missing column!
        }
        ln ++; 
    }
    if (ln != RAW_LINES) {
        fclose(fp);
        return 2; // Invalid data, number of measurements!
    }
    
    fclose(fp);
    return 0; 
}

#endif
