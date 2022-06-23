/**
 * @file npda_tools.c
 * @author rzeller, voccoto Ltd
 * @brief Core NPDA processing functions. Median, Polygon regression, Peak detection, ...
 * @version 0.3
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "npda_tools.h"

/**
 * @brief Find the maximum value and its position in a vector v
 * 
 * @param[in] v Vector
 * @param[in] vsize Vector size
 * @param[out] max_pos Index of maximum value
 * @return fptype Maximum value
 */
inline fptype vmax(fptype *v, int vsize, int *max_pos) {
    int i;
    fptype maxval = -FPTYPE_MAX;
    *max_pos = -1;
    for (i=0; i<vsize; i++) {
        if (maxval < v[i]) {
            maxval = v[i];
            *max_pos = i;
        }
    }
    return maxval;
}

/** @brief Swapping two values. Used in median() */
#define ELEM_SWAP(a,b) { register fptype t=(a);(a)=(b);(b)=t; }
/**
 * @brief Returns the median of the specified vector of size n.
 * 
 * @param[in] vector Input vector
 * @param[in] n Vector size
 * @return fptype Median of vector
 * 
 * @note Based on "Numerical recipes in C", Second Edition, Cambridge University Press, 1992, Section 8.5, ISBN 0-521-43108-5
 * 
 */
fptype median(fptype *vector, int n) {
    int low, high ;
    int median;
    int middle, ll, hh;

    /* Copy vector into temporary buffer */
    memcpy(__npda_median, vector, n * sizeof(fptype));

    low = 0 ; high = n-1 ; median = (low + high) / 2;
    for (;;) {
        if (high <= low) { /* One element only */
            return __npda_median[median] ;
        }

        if (high == low + 1) {  /* Two elements only */
            if (__npda_median[low] > __npda_median[high]) ELEM_SWAP(__npda_median[low], __npda_median[high]) ;
            return __npda_median[median] ;
        }

        /* Find median of low, middle and high items; swap into position low */
        middle = (low + high) / 2;
        if (__npda_median[middle] > __npda_median[high])    ELEM_SWAP(__npda_median[middle], __npda_median[high]) ;
        if (__npda_median[low] > __npda_median[high])       ELEM_SWAP(__npda_median[low], __npda_median[high]) ;
        if (__npda_median[middle] > __npda_median[low])     ELEM_SWAP(__npda_median[middle], __npda_median[low]) ;

        /* Swap low item (now in position middle) into position (low+1) */
        ELEM_SWAP(__npda_median[middle], __npda_median[low+1]) ;

        /* Nibble from each end towards middle, swapping items when stuck */
        ll = low + 1;
        hh = high;
        for (;;) {
            do ll++; while (__npda_median[low] > __npda_median[ll]) ;
            do hh--; while (__npda_median[hh]  > __npda_median[low]) ;

            if (hh < ll) break;

            ELEM_SWAP(__npda_median[ll], __npda_median[hh]) ;
        }

        /* Swap middle item (in position low) back into correct position */
        ELEM_SWAP(__npda_median[low], __npda_median[hh]) ;

        /* Re-set active partition */
        if (hh <= median) low = ll;
        if (hh >= median) high = hh - 1;
    }
}
#undef ELEM_SWAP

/**
 * @brief Convolution. c = a*b. 
 * 
 * @param[out] c Return vector
 * @param[in] a vector a
 * @param[in] b vector b
 * @param[in] lena a's length
 * @param[in] lenb b's length
 * @param[out] cvmax Max value in c
 * @param[out] cvmax_idx Max value index in c
 * @return void
 * 
 * @note Length of c vector asumed to be MIN(MAX_WINDOW_SIZE, lena + lenb - 1)
 * 
 */
inline void conv(fptype *c, fptype *a, fptype *b, int lena, int lenb, fptype *cvmax, int *cvmax_idx) {
	int i, j, i1;
	fptype tmp;
    int lenc = MIN(MAX_WINDOW_SIZE, lena + lenb - 1);

    *cvmax = -FPTYPE_MAX;
    *cvmax_idx = -1;

	for (i=0; i<lenc; i++) {
		i1 = i;
		tmp = 0.0;
		for (j=0; j<lenb; j++) {
			if (i1>=0 && i1<lena) {
				tmp = tmp + (a[i1]*b[j]);
            }
			i1 = i1-1;
			c[i] = tmp;
		}
        if (*cvmax < c[i]) {
            *cvmax = c[i];
            *cvmax_idx = i;
        }
	}
	return ;
}

#if USE_INTERPOLATED_POS_BUFFER
/**
 * @brief Fitting a quadratic polygon to the active member points (wscanx, wscany)
 * 
 * @param[in] wscanx x coord
 * @param[in] wscany y coord
 * @param[in] wsize size of wscanx and y
 * @param[in] active_members Number of active (wscanx, wscany) points in __npda_hhw[]
 * @param[out] coeffs returns the polygon's 3 parameters. Assumed to be at least double[3]
 * @return int 0 if ok
 * 
 * @note The returned polygon: coeff[2]*x^2 + coeff[1]*x + coeff[0]
 * 
 */
int polyfit2(   fptype *wscanx,
                fptype *wscany,
                int wsize,
                int active_members,
			    double *coeffs)
{
    double B[3] = {0.0, 0.0, 0.0};
    double P[7] = {active_members, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double A[18] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double x, y, powx;
    unsigned int ii, jj, kk;

    if (active_members <= 2) {
        /* polyfit2() failed on window size! Not enough data! */
        return 1; 
    }

    /* Identify the column vector */
    for (ii = 0; ii < wsize; ii++) {
        if (__npda_hhw[ii]) {
            for (jj=0, powx=1; jj<3; jj++) {
                B[jj] = B[jj] + (wscany[ii] * powx);
                powx  = powx * wscanx[ii];
            }
        }
    }

    /* Compute the sum of the Powers of X */
    for (ii = 0; ii < wsize; ii++) {
        if (__npda_hhw[ii]) {
            for (jj=1, powx=wscanx[ii]; jj < 7; jj++) {
                P[jj] = P[jj] + powx;
                powx  = powx * wscanx[ii];
            }
        }
    }

    /* Initialize the reduction matrix */
    for (ii = 0; ii < 3; ii++) {
        for (jj = 0; jj < 3; jj++) {
            A[ii*6 + jj] = P[ii + jj];
        }
        A[ii*6 + (ii + 3)] = 1.0;
    }

    /*
     Move the Identity matrix portion of the redux matrix
     to the left side (find the inverse of the left side
     of the redux matrix
    */
    for (ii = 0; ii < 3; ii++) {
        x = A[ii*6 + ii];
        if (fabs(x) > PRACTICAL_ZERO) { /* if (x != 0.0) { */
            for (kk = 0; kk < 6; kk++) {
                A[ii*6 + kk] /= x;
            }

            for (jj = 0; jj < 3; jj++) {
                if (jj != ii) {
                    y = A[jj*6 + ii];
                    for (kk = 0; kk < 6; kk++) {
                        A[jj*6 + kk] -= y * A[ii*6 + kk];
                    }
                }
            }
        } else {
            /* Cannot work with singular matrices */
            return 2;
        }
    }

    /* Calculate and Identify the coefficients */
    for (ii = 0; ii < 3; ii++) {
        for (jj = 0; jj < 3; jj++) {
            x = 0.0;
            for (kk = 0; kk < 3; kk++) {
                x += A[ii*6 + kk + 3]*B[kk];
            }
            coeffs[ii] = x;
        }
    }

    return 0;
}
#else
/**
 * @brief Fitting a quadratic polygon to the active member points starting at (__npda_x + offset, __npda_y + offset)
 * 
 * @param[in] wsize size of data set after offset
 * @param[in] active_members Number of active points in the data set represented in __npda_hhw[]
 * @param[out] coeffs returns the polygon's 3 parameters. Assumed to be at least double[3]
 * @return int
 * @return 0 - Success
 * @return 1 - Not enough active members in data!
 * @return 2 - Cannot work with singular matrices
 * 
 * @note The returned polygon: coeff[2]*x^2 + coeff[1]*x + coeff[0]
 * 
 */
int polyfit2(   int offset,
                int wsize,
                int active_members,
			    double *coeffs)
{
    double B[3] = {0.0, 0.0, 0.0};
    double P[7] = {active_members, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double A[18] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double x, y, powx;
    unsigned int ii, iio, jj, kk;
    fptype *wscany = __npda_y + offset;

    if (active_members <= 2) {
        /* polyfit2() failed on window size! Not enough data! */
        return 1; 
    }

    /* Identify the column vector */
    for (ii = 0, iio = offset; ii < wsize; ii++, iio++) {
        if (__npda_hhw[ii]) {
            for (jj=0, powx=1; jj<3; jj++) {
                B[jj] = B[jj] + (wscany[ii] * powx);
                powx  = powx * NPDA_X(iio);
            }
        }
    }

    /* Compute the sum of the Powers of X */
    for (ii = 0, iio = offset; ii < wsize; ii++, iio++) {
        if (__npda_hhw[ii]) {
            for (jj=1, powx=NPDA_X(iio); jj < 7; jj++) {
                P[jj] = P[jj] + powx;
                powx  = powx * NPDA_X(iio);
            }
        }
    }

    /* Initialize the reduction matrix */
    for (ii = 0; ii < 3; ii++) {
        for (jj = 0; jj < 3; jj++) {
            A[ii*6 + jj] = P[ii + jj];
        }
        A[ii*6 + (ii + 3)] = 1.0;
    }

    /*
     Move the Identity matrix portion of the redux matrix
     to the left side (find the inverse of the left side
     of the redux matrix
    */
    for (ii = 0; ii < 3; ii++) {
        x = A[ii*6 + ii];
        if (fabs(x) > PRACTICAL_ZERO) { /* if (x != 0.0) { */
            for (kk = 0; kk < 6; kk++) {
                A[ii*6 + kk] /= x;
            }

            for (jj = 0; jj < 3; jj++) {
                if (jj != ii) {
                    y = A[jj*6 + ii];
                    for (kk = 0; kk < 6; kk++) {
                        A[jj*6 + kk] -= y * A[ii*6 + kk];
                    }
                }
            }
        } else {
            /* Cannot work with singular matrices */
            return 2;
        }
    }

    /* Calculate and Identify the coefficients */
    for (ii = 0; ii < 3; ii++) {
        for (jj = 0; jj < 3; jj++) {
            x = 0.0;
            for (kk = 0; kk < 3; kk++) {
                x += A[ii*6 + kk + 3]*B[kk];
            }
            coeffs[ii] = x;
        }
    }

    return 0;
}
#endif

/**
 * @brief Returns the highest index of the element in array[] that is smaller
 *        than value, starting searching from the specified position start_idx
 * 
 * @param[in] value - value to look for
 * @param[in] start_idx - start searching from this position, this is the previously
 *            returned position.
 * @return    index in array[]. Return -1 if value is smaller than the first
 *            element in the array[] or larger than the last element in the array
 * 
 * @pre array must be monotonous for this function to return the nearest neighbour.
 *      array element array[MAX_WINDOW_SIZE] must be accessible
 */
#ifdef DEBUG
int nearest_neighbour(fptype value, int start_idx) {
#else
STATIC inline int nearest_neighbour(fptype value, int start_idx, fptype * array) { 
#endif
    fptype dist = FPTYPE_MAX;
    int idx = -1;
    int i;

    for (i=start_idx; i<MAX_WINDOW_SIZE; i++) { //i must vary up to MAX_WINDOW_SIZE - 1
        fptype newDist = value - array[i];
        if (newDist >= 0) {
            if (newDist < dist) {
                dist = newDist;
                idx = i;
            }
        }
        else {
            return idx;
        }
    }

    return -1; //If the code reaches this point, entire array within the MAX_WINDOW_SIZE has been checked, and even array[MAX_WINDOW_SIZE-1] > value
}

/**
 * @brief Interpolating scan data in __npda_y0 into __npda_y
 * 
 */
void interpolate_scan(void) {
    fptype dx, dy;
    int i, idx;

    /* calculating slope and intercept buffers */
    for (i=0; i<MAX_WINDOW_SIZE; i++) { //TODO: MAX_WINDOW_SIZE or __interpolated_size?
        if (i<MAX_WINDOW_SIZE-1) {
            dx = NPDA_X0(i + 1) - NPDA_X0(i);
            dy = (fptype)(__npda_y0[i + 1]) - (fptype)(__npda_y0[i]);
            
            if( dx != 0.000f ) // What if dx == 0? If dx is 0, then it is the same as previous point, and slope should be 0; right now it could be anything.
            {
                __npda_slope[i] = dy / dx;
            }
            __npda_intercept[i] = (fptype)(__npda_y0[i]) - NPDA_X0(i) * __npda_slope[i];
        } else {
            __npda_slope[i] = __npda_slope[i-1];
            __npda_intercept[i] = __npda_intercept[i-1];
        }
    }

    for (i=0, idx=0; i<__interpolated_size; i++) {
        idx = nearest_neighbour(NPDA_X(i), (unsigned int)idx, __npda_offsetted_x0); //finds index in calibration space nearest to the NPDA_X(i)
        if (idx != -1) {
            __npda_y[i] = __npda_slope[idx] * NPDA_X(i) + __npda_intercept[idx];
        } else {
            __npda_y[i] = FPTYPE_MAX;
            idx = 0;
        }
    }
    return ;
}

void interpolate_scan2(void) {
    fptype dx, dy;
    int i, idx;
    fptype slope;

    for (i=0, idx=0; i<__interpolated_size; i++)
    {
        idx = nearest_neighbour(NPDA_X(i), idx, __npda_offsetted_x0);
        if( idx != -1) //finds index in calibration space (NPDA_X0) nearest to the NPDA_X(i) //TODO: make sure that idx returned is < //TODO: this only works with x0 is monotonous
        {
            if(idx == MAX_WINDOW_SIZE - 1)
            {
                idx--;
            }
            dx = NPDA_X0(idx + 1) - NPDA_X0(idx); //is it not possible for idx + 1 to exceed the table size limit, as ensured in nearest_neighbour()
            if ( i < MAX_WINDOW_SIZE - 1 )
            {
                dy = (fptype)(__npda_y0[idx + 1]) - (fptype)(__npda_y0[idx]);
            }
            else
            {
                dy = (fptype)(__npda_y0[idx]) - (fptype)(__npda_y0[idx - 1]);
            }

            if( dx != 0 ) //TODO: ensure this cannot happen in practice, i.e. that calibration data is strongly monotonous
            {
                dy = (fptype)(__npda_y0[idx + 1]) - (fptype)(__npda_y0[idx]);
                slope = dy/dx;
                __npda_y[i] = __npda_y0[idx] + slope * (NPDA_X(i) - NPDA_X0(idx));
            }
            else
            {
                __npda_y[i] = __npda_y0[idx];
            }
        }
        else
        {
            __npda_y[i] = FPTYPE_MAX;
            idx = 0;
        }
    }
}

/**
 * @brief Adding a new interpolated scan from __npda_y to the average vector in __npda_avg, adjusting data by offset
 * 
 * @param[in] offset Based on the AC position in __npda_y, used to shift __npda_y so all averaged data has AC peak at AC_REFERENCE_INDEX
 */
void average_incremental(int offset) {
    int i, j;

    if (__valid_scans == 0) {
        /* Initialise average buffer for first scan */
        if (offset > 0) memset(__npda_avg, 0, offset*sizeof(fptype));
        if (offset < 0) memset(__npda_avg + (__interpolated_size + offset), 0, -offset*sizeof(fptype));
        memcpy(__npda_avg + (offset>0 ? offset : 0), __npda_y + (offset<0 ? abs(offset) : 0), (__interpolated_size - abs(offset))*sizeof(fptype));
    }
    else {
        /* Incremental average for subsequent scans */
        for (i=(offset<0 ? abs(offset) : 0), j=(offset>0 ? offset : 0); (i<__interpolated_size) && (j<__interpolated_size); i++, j++) {
            __npda_avg[j] += (__npda_y[i] - __npda_avg[j]) / (__valid_scans + 1.0);
        }
    }
}

/**
 * @brief Adding a new interpolated scan from __npda_y to the average vector in __npda_avg, adjusting data by offset and returning maximum average value and index. Called as the last scan of the block is added to the average.
 * 
 * @param[in] offset Based on the AC position in __npda_y, used to shift __npda_y so all averaged data has AC peak at AC_REFERENCE_INDEX
 * @param[out] avg_maxval Max average value
 * @param[out] avg_maxpos Index for avg_maxval
 */
void average_incremental_end(int offset, fptype *avg_maxval, int *avg_maxpos) {
    int i, j;

    *avg_maxval = -FPTYPE_MAX;
    *avg_maxpos = -1;
    for (i=(offset<0 ? abs(offset) : 0), j=(offset>0 ? offset : 0); (i<__interpolated_size) && (j<__interpolated_size); i++, j++) {
        __npda_avg[j] += (__npda_y[i] - __npda_avg[j]) / (__valid_scans + 1.0);
        /* update max value and index */
        if (*avg_maxval < __npda_avg[j]) {
            *avg_maxval = __npda_avg[j];
            *avg_maxpos = j;
        }
    }
}

/**
 * @brief Returning a data window (q1, q2) in scany containing the points above half height around the specified max value position
 * 
 * @param[in] scany Input vector
 * @param[in] maxval Max(scany)
 * @param[in] maxpos Index of maxval in scany
 * @param[out] q1 Left index of the returned "window"
 * @param[out] q2 Right index of the returned "window"
 */
void find_ac_peak(fptype *scany, fptype maxval, int maxpos, int *q1, int *q2) {
	/* Zero level of the data */
	fptype m = median(scany, __interpolated_size);
	fptype half_height = (maxval + m) / 2.0;

    /* looking for half_height on the left of maxpos */
	int i = maxpos;
	while (i > 0 && scany[i] > half_height) {
		i --;
	}
	*q1 = i;

    /* looking for half_height on the right of maxpos */
	i = maxpos;
	while (i < __interpolated_size && scany[i] > half_height) {
		i ++;
	}
	*q2 = i;

    return ;
}

/**
 * @brief Fitting a parabola on the half height window points around the AC peak based on the max value
 * 
 * @param[in] q1 Half height window left index from @find_ac_peak
 * @param[in] q2 Half height window right index from @find_ac_peak
 * @param[in] wmax Max value within [q1, q2]
 * @param[out] peak_value Interpolated peak value
 * @param[out] peak_idx Index for interpolated peak value
 * @return int
 * @return 0 - Success
 * @return 1 - Not enough active members for polyfit2()!
 * @return 2 - polyfit2() cannot work with singular matrices
 */
int find_ac_quad(int q1, int q2, fptype wmax, fptype *peak_value, int *peak_idx) {
    fptype range_bound_min = 0.5 * wmax;
    fptype range_bound_max = 0.95 * wmax;
    size_t max_range_set_size = q2 - q1 + 1;
    int q, i, active_cnt;
    int q1s = 0, q2e = 0;

    for (q=q1, i=0, active_cnt=0; q<=q2; q++, i++) {
        if (__npda_y[q] >= range_bound_min && __npda_y[q] <= range_bound_max) {
            __npda_hhw[i] = 1;
            if (active_cnt) {
                q2e = q; /* Active range end */
            } else {
                q1s = q; /* Active range beginning */
            }
            active_cnt ++;
        }
        else {
            __npda_hhw[i] = 0;
        }
    }

    double coeffs[3];
#if USE_INTERPOLATED_POS_BUFFER
    int iret = polyfit2(__npda_x + q1, __npda_y + q1, max_range_set_size, active_cnt, coeffs);
#else
    int iret = polyfit2(q1, max_range_set_size, active_cnt, coeffs);
#endif
    if (!iret) {
        /* Find max for the fitted function between q1 and 2 */
        *peak_value = -FPTYPE_MAX;
        *peak_idx = -1;
        for (q=q1s; q<=q2e; q++) {
            double v = NPDA_X(q)*(coeffs[2]*NPDA_X(q) + coeffs[1]) + coeffs[0];
            if (v > (*peak_value)) {
                *peak_value = v;
                *peak_idx = q;
            }
        }
    }

    return iret;
}

/**
 * @brief Find AC peak in interpolated data in __npda_y, use it as an offset to merge to current average data set in __npda_avg
 * 
 * @param[in] med Median of the __npda_y
 * @param[out] avg_maxval Maximum value in __npda_avg. Optional, can be NULL
 * @param[out] avg_maxpos Maximum value index in __npda_avg. Optional, can be NULL if avg_maxval is NULL!
 * @return int
 * @return 0 - Success
 * @return 1 - Invalid scan, cannot find max position
 * @return 21 - Not enough active members for polyfit2()!
 * @return 22 - polyfit2() cannot work with singular matrices
 */
int update_average(fptype med, fptype *avg_maxval, int *avg_maxpos) {
    int i;
    fptype maxval = -FPTYPE_MAX; /* max(__npda_y) and its index */
    int maxpos = -1;
    int q1, q2; /* Peak data left-right */
    int iret;

    /* Adjust __npda_y to median and calculate max */
    for (i=0; i<__interpolated_size; i++) {
        __npda_y[i] -= med;
        if (__npda_y[i] > maxval) {
            maxval = __npda_y[i];
            maxpos = i;
        }
    }
    if (maxpos == -1) {
        /* Invalid scan! */
        return 1;
    }
    
    /* Find half max height window (q1, q2) */
    find_ac_peak(__npda_y, maxval, maxpos, &q1, &q2);

    fptype peak_value; /* Scan value at peak and its index */
    int peak_idx;
    /* Find peak position with interpolation */
    iret = find_ac_quad(q1, q2, maxval, &peak_value, &peak_idx);
    if (iret) {
        /* find_ac_quad() failed! */
        return 20 + iret;
    }

    /* updating average incrementally */
    if (avg_maxval) {
        /* Final update. Get max value and decrement vector with median */
        average_incremental_end(AC_REFERENCE_INDEX - peak_idx, avg_maxval, avg_maxpos);
        fptype avg_median = median(__npda_avg, __interpolated_size);
        for (i=0; i<__interpolated_size; i++) {
            __npda_avg[i] -= avg_median;
        }
        /* Also adjust maximum value */
        *avg_maxval -= avg_median;
    }
    else {
        /* Add to average */
        average_incremental(AC_REFERENCE_INDEX - peak_idx);
    }

    return 0;
}

/**
 * @brief Saving all PC peak candidates to __npda_pcpc following the AC peak index
 * 
 * @param[in] AC_idx AC peak index
 * @param[out] pc_peak_cnt Number of candidates saved in __npda_pcpc
 */
void find_pc_peak_candidates(int AC_idx, int *pc_peak_cnt) {
    /*
     DEFINE WINDOW (A human cornea can't be less than 0.4 or greater than 0.7)
     Reduce the range where to look for PC pos based in AC pos
    */
    int leftbound = AC_idx + floor(MIN_CENT_CORNEAL_THICK / (INTERPOLATION_DISTANCE * CORNEA_REFRACTIVE_IDX));
    int rightbound = AC_idx + floor(MAX_CENT_CORNEAL_THICK / (INTERPOLATION_DISTANCE * CORNEA_REFRACTIVE_IDX));

    /* Finding peaks within the bounds */
    *pc_peak_cnt = 0;
    int i;
    for (i=leftbound+1; i<rightbound-1 && *pc_peak_cnt<MAX_PCPC; i++) {
        if (__npda_conv[i] > 0.0 && __npda_conv[i] > __npda_conv[i - 1] && __npda_conv[i] > __npda_conv[i + 1]) {
            /* peak at i */
            __npda_pcpc[(*pc_peak_cnt) ++] = i;
        }
    }

    return ;
}

/**
 * @brief Select PC from the list of candidates returned by find_pc_peak_candidates() in __npda_pcpc.
 *          Calculate the weighting factor for each peak located
 *          Weighting factor is based on empirical limit on the height of ripples as
 *          a function of PC position and has a logarithmic amplitude variation.
 *          Anything over a threshold height is very likely to be a real PC peak, do
 *          not need much change in weighting above threshold. Below threshold peak
 *          may still be a real PC peak, so cannot be eliminated completely.
 * 
 * @param[in] AC AC peak value
 * @param[in] AC_idx AC peak position
 * @param[in] pc_peak_cnt Number of PC peak candidates in __npda_pcpc
 * @param[out] PC_height Returning PC height
 * @param[out] PC_idx Returning PC index
 * @param[out] PC_weight Returning PC weight
 */
void find_pc_peak(fptype AC, int AC_idx, int pc_peak_cnt, fptype *PC_height, int *PC_idx, fptype *PC_weight) {
    *PC_weight = -FPTYPE_MAX;
    int i;
    
    if( AC > PRACTICAL_ZERO )
    {
        for (i=0; i<pc_peak_cnt; i++) {
            fptype t = CORNEA_REFRACTIVE_IDX * fabs(NPDA_X(__npda_pcpc[i]) - NPDA_X(AC_idx)); /* Estimate of corneal thickness */
            fptype pch = __npda_conv[__npda_pcpc[i]] / AC; /* PC peak height normalised to AC peak height */
            fptype wt = 1.0 - exp((-2.303 * pch) / (0.035 - (0.045*t) + (0.012*t*t)));
            if (*PC_weight < wt) {
                *PC_weight = wt;
                *PC_height = pch;
                *PC_idx = __npda_pcpc[i];
            }
        }
    }

    return ;
}
