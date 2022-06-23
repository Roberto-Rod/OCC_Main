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
 * @brief Function that checks whether an array increases strictly monotonically
 *
 * @param[in] array - Array to check.
 * @param[in] array_len - Length of the array.
 * @return bool
 * @return true - calibration is strictly monotonically increasing
 * @return false - calibration is NOT strictly monotonically increasing
 */
bool is_increasing_monotonically(const fptype* calibration, int array_len)
{
    uint16_t i = 0;
    for(i=0; i<array_len-1; i++)
    {
        if(calibration[i+1] <= calibration[i])
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Function to transform non-linear vector to uniformly distributed space. Note that the
 *
 * @param[in] x - Pointer to array to input array. This array will form a basis for the transformation.
 * @param[in] x_len - Length of the input array.
 * @param[in] resolution - Length of individual increments in the uniformly-distributed space.
 * @param[out] transformed_start_x - X value of the first element of the transformed space.
 * @param[out] transformed_len - Length of the transformed space.
 *
 * @return 0 - Success
 * @return 1 - Failed due to wrong resolution or x_len
 * @return 2 - Failed due to transformed_length being too short
 *
 * @pre x is monotonically increasing, so first point is min(x) and last point is max(x)
 */
int inline transform_to_uniform_distribution(fptype * x, int x_len, fptype resolution, fptype * transformed_start_x, int * transformed_len)
{
    if(resolution <= 0 || x_len <= 1)
    {
        return 1;
    }

    *transformed_start_x = resolution * ceil(x[0] / resolution); //WARNING: if x[0] is divisible by resolution, then due to float rounding it may be that *transformed_start_x < x[0]!!!
    if(*transformed_start_x < x[0])
    {
        *transformed_start_x = x[0];
    }
    fptype transformed_end_x = resolution * floor( x[x_len-1] / resolution);
    *transformed_len = MIN(((int)rint((transformed_end_x - *transformed_start_x) / resolution) + 1), x_len); //WARNING: if x[x_len] is divisible by resolution, then due to float rounding it may be that *transformed_start_x + < x[0]!!!
    if(*transformed_start_x + ((*transformed_len)-1)*resolution > x[x_len-1])
    {
        (*transformed_len)--;
    }
    if(*transformed_len <= 1)
    {
        return 2;
    }
    return 0;
}

/**
 * @brief Find the maximum value and its position in a vector v
 *
 * @param[in] v Vector
 * @param[in] vsize Vector size
 * @param[out] max_pos Index of maximum value
 * @return fptype Maximum value
 *
 * @note The function returns leftmost peak in case two peaks are present.
 */
fptype inline vmax(fptype *v, int vsize, int *max_pos) 
{
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

/**
 * @brief Find the minimum value and its position in a vector v
 *
 * @param[in] v Vector
 * @param[in] vsize Vector size
 * @param[out] min_pos Index of maximum value
 * @return fptype Minimum value
 *
 * @note The function returns leftmost peak in case two peaks are present.
 */
STATIC fptype inline vmin(fptype *v, int vsize, int *min_pos) {
    int i;
    fptype minval = FPTYPE_MAX;
    *min_pos = -1;
    for (i=0; i<vsize; i++) {
        if (minval > v[i]) {
            minval = v[i];
            *min_pos = i;
        }
    }
    return minval;
}

/** @brief Swapping two values. Used in select_kth_largest() */
#define ELEM_SWAP(a,b) { register fptype t=(a);(a)=(b);(b)=t; }
/**
 * @brief Returns the k-th largest element in specified vector of size n.
 *
 * @param[in] vector Input vector
 * @param[in] n Vector size
 * @param[in] k Number of the element to return
 * @param[in] helper Helper vector where data is stored temporarily
 * @return fptype k-th largest element in the array
 *
 * @note Based on "Numerical recipes in C", Second Edition, Cambridge University Press, 1992, Section 8.5, ISBN 0-521-43108-5
 *
 */
static fptype select_kth_largest(fptype *vector, int n, int k, fptype *helper) {
    int low, high ;
    int middle, ll, hh;

    /* Copy vector into temporary buffer */
    memcpy(helper, vector, n * sizeof(fptype));

    low = 0 ; high = n-1 ;
    for (;;) {
        if (high <= low) { /* One element only */
            return helper[k] ;
        }

        if (high == low + 1) {  /* Two elements only */
            if (helper[low] > helper[high]) ELEM_SWAP(helper[low], helper[high]) ;
            return helper[k] ;
        }

        /* Find median of low, middle and high items; swap into position low */
        middle = (low + high) / 2;
        if (helper[middle] > helper[high])    ELEM_SWAP(helper[middle], helper[high]) ;
        if (helper[low] > helper[high])       ELEM_SWAP(helper[low], helper[high]) ;
        if (helper[middle] > helper[low])     ELEM_SWAP(helper[middle], helper[low]) ;

        /* Swap low item (now in position middle) into position (low+1) */
        ELEM_SWAP(helper[middle], helper[low+1]) ;

        /* Nibble from each end towards middle, swapping items when stuck */
        ll = low + 1;
        hh = high;
        for (;;) {
            do ll++; while (helper[low] > helper[ll]) ;
            do hh--; while (helper[hh]  > helper[low]) ;

            if (hh < ll) break;

            ELEM_SWAP(helper[ll], helper[hh]) ;
        }

        /* Swap middle item (in position low) back into correct position */
        ELEM_SWAP(helper[low], helper[hh]) ;

        /* Re-set active partition */
        if (hh <= k) low = ll;
        if (hh >= k) high = hh - 1;
    }
}
#undef ELEM_SWAP

#define UINT16_SWAP(a,b) { register uint16_t t=(a);(a)=(b);(b)=t; }
#define S 2
/**
 * @brief Returns the median of the vector of uint16_t s.
 *
 * @param[in] vector Input vector
 * @param[in] n Vector size
 * @return uint16_t median element in the array
 *
 * @note Based on "Numerical recipes in C", Second Edition, Cambridge University Press, 1992, Section 8.5, ISBN 0-521-43108-5
 * @note In case of vectors with even length n, it will return n/2-1 largest element (not true median).
 * @note Warning: the vector is 'recycled' for the purpose of the median calculation.
 *
 */
uint16_t median_uint16_t(uint16_t *arr, int n)
{

    unsigned int i, ir, j, k, l, m, mid;
    uint16_t a;

    l = 0;
    ir = n-1-((n-1)%S);
    m = (ir-l)/(2*S);
    k = l+S*m;
    for (;;) {
        if (ir <= l+S) {
            if (ir == l+S && arr[ir] < arr[l]) {
                UINT16_SWAP(arr[l], arr[ir])
            }
            return arr[k] ;
        } else {
            m=(ir-l)/(2*S);
            mid=l+S*m;
            UINT16_SWAP(arr[mid], arr[l+S]);
            if (arr[l] > arr[ir]) {
                UINT16_SWAP(arr[l], arr[ir]);
            }
            if (arr[l+S] > arr[ir]) {
                UINT16_SWAP(arr[l+S], arr[ir]);
            }
            if (arr[l] > arr[l+S]) {
                UINT16_SWAP(arr[l], arr[l+S]);
            }

            i=l+S;
            j=ir;
            a=arr[l+S];
            for (;;) {
                do i+=S; while (arr[i] < a);
                do j-=S; while (arr[j] > a);
                if (j < i) break;
                UINT16_SWAP(arr[i], arr[j]) ;
            }
            arr[l+S]=arr[j];
            arr[j]=a;
            if (j >= k) ir=j-S;
            if (j <= k) l=i;
        }
    }

}
#undef UINT16_SWAP
#undef S

/**
 * @brief Returns the median of the specified vector of size n.
 *
 * @param[in] vector Input vector
 * @param[in] n Vector size
 * @param[in] helper Helper vector where data is stored temporarily
 * @return fptype Median of vector
 *
 * @note For vectors longer than 100 elements, we accept that in case of even number of elements the returned value will be the lower of the two middle elements.
 * @note For vectors shorter or equal to 100 elements, median is calculated accurately for vectors with odd and even number of elements.
 *
 */
fptype median(fptype *vector, int n, fptype *helper) {
    int median_idx = ( n - 1 ) / 2;
    if( n <= 100 && !(n & 1) ) //Special case for short vectors with even number of elements
    {
        return (select_kth_largest(vector, n, median_idx, helper) + select_kth_largest(vector, n, median_idx+1, helper))/2;
    }

    return select_kth_largest(vector, n, median_idx, helper);
}

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
 * @note Length of c vector assumed to be lenb, as MATLAB algorithm uses parameter 'same' (i.e. conv(a, b, 'same')) see https://uk.mathworks.com/help/matlab/ref/conv.html
 *
 */
inline void conv(fptype *c, fptype *a, fptype *b, int lena, int lenb, fptype *cvmax, int *cvmax_idx) {
	int i, j;
	fptype tmp;
    int first_idx = (int)((fptype)lenb / 2.0);


    *cvmax = -FPTYPE_MAX;
    *cvmax_idx = -1;

	for (i=first_idx; i<lena+first_idx; i++) {
		tmp = 0.0;
		for (j=0; j<lenb; j++) {
			if (i-j>=0 && i-j<lena) {
				tmp = tmp + (a[i-j]*b[j]);
            }
		}
    	c[i-first_idx] = tmp;
        if (*cvmax < c[i-first_idx]) {
            *cvmax = c[i-first_idx];
            *cvmax_idx = i-first_idx;
        }
	}

	return ;
}

/**
 * @brief Fitting a quadratic polygon to the active member points starting at (__npda_x + offset, __npda_y + offset)
 *
 * @param[in] scany - Data to fit the parabola to
 * @param[in] offset - Offset to be applied to NPDA_X, so that NPDA_X(i) and scany(i) match
 * @param[in] active_members_buffer - Buffer of active points in the data set (i.e. points to fit to)
 * @param[in] wsize - size of active_members_buffer
 * @param[out] coeffs - returns the polygon's 3 parameters. Assumed to be at least double[3]
 *
 * @return int
 * @return 0 - Success
 * @return 1 - Not enough active members in data!
 * @return 2 - Cannot work with singular matrices
 * @return 3 - Offset negative
 *
 * @note The returned polynomial: coeff[2]*x^2 + coeff[1]*x + coeff[0]
 * @note The polynomial is fitted to x with no shift, i.e.
 *
 * @pre active_member_cnt must equal sum(active_member_buffer)
 */
STATIC int polyfit2(fptype * scany, int offset, byte * active_members_buffer, int wsize, double *coeffs)
{
    int i;
    int active_members_cnt=0;
    for (i=0; i<wsize; i++)
    {
        if(active_members_buffer[i] == 1)
        {
            active_members_cnt++;
        }
    }
    /* condition NPDA_X so that it starts at 0, this avoid ill-conditioned matrices */
//    fptype matrix_conditioning = __npda_offsetted_x_start;
//    __npda_offsetted_x_start = 0;

    double B[3] = {0.0, 0.0, 0.0};
    double P[7] = {active_members_cnt, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double A[18] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double x, y, powx;
    unsigned int ii, iio, jj, kk;

    if( offset < 0)
    {
        return 3;
    }

    if (active_members_cnt <= 2) {
        /* polyfit2() failed on window size! Not enough data! */
        return 1;
    }

    /* Identify the column vector */
    for (ii = 0, iio = offset; ii < wsize; ii++, iio++) {
        if (active_members_buffer[ii]) {
            for (jj=0, powx=1; jj<3; jj++) {
                B[jj] = B[jj] + (scany[ii] * powx);
                powx  = powx * NPDA_X(iio);
            }
        }
    }

    /* Compute the sum of the Powers of X */
    for (ii = 0, iio = offset; ii < wsize; ii++, iio++) {
        if (active_members_buffer[ii]) {
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
     of the redux matrix)
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
        x = 0.0;
        for (kk = 0; kk < 3; kk++) {
            x += A[ii*6 + kk + 3]*B[kk];
        }
        coeffs[ii] = x;
    }

    /* revert NPDA_X back to where it was */
//    __npda_offsetted_x_start = matrix_conditioning;
    /* correct coefficients for the translation */
//    coeffs[1] = coeffs[1] - 2*matrix_conditioning*coeffs[2];
//    coeffs[0] = coeffs[0] + coeffs[0]*matrix_conditioning*matrix_conditioning - coeffs[1]*matrix_conditioning;

    return 0;
}

/**
 * @brief Returns the highest index of the element in array[] that is smaller
 *        than value, starting searching from the specified position start_idx
 *
 * @param[in] value - value to look for
 * @param[in] start_idx - start searching from this position, this is the previously
 *            returned position.
 * @param[in] array - array to be searched.
 * @param[in] len - length of the array to be searched.
 *
 * @return    index in array[].
 * @return    -1 if value is smaller than the first element in the array[] or
 *            larger than the last element in the array or if start_idx < 0 or
 *            start_idx > len-1 (i.e. this could signify that len is too short.
 *
 * @pre array must be monotonous for this function to return the nearest neighbour.
 *      This is ensured through is_increasing_monotonically() check.
 *      array element array[len] must be accessible.
 */
#if defined(DEBUG) || defined(TEST)
int nearest_neighbour(fptype value, int start_idx, fptype * array, int len)
#else
static inline int nearest_neighbour(fptype value, int start_idx, fptype * array, int len)
#endif
{
    fptype dist = FPTYPE_MAX;
    int idx = -1;
    int i;

    if(start_idx < 0 || start_idx > len-1)
    {
        return -1;
    }
    if(value == array[len-1])
    {
        return len-2;
    }

    for (i=start_idx; i<len; i++) { //i must vary up to len
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
 * @brief Interpolating scan data in y0 into y_inter
 *
 * @param[in] x0 - pointer to array containing x data before interpolation
 * @param[in] y0 - pointer to array containing y data before interpolation
 * @param[in] x0_y0_len - length of the arrays before interpolation
 * @param[out] y_inter - pointer to array containing y data after interpolation
 * @param[in] x_y_inter_len - length of the array after interpolation
 *
 * @return 0 - Success
 *         1 - Error - could not find nearest neighbour
 *         2 - Nearest neighbour returned too high index
 *         3 - Data is not increasing strictly monotonically
 *         4 - Too short x0_y0_len
 */

int interpolate_scan(fptype * x0, uint16_t * y0, int x0_y0_len, fptype * y_inter, int x_y_inter_len ) {
    fptype dx, dy;
    int i, idx;
    fptype slope;
    if(x_y_inter_len < 1)
    {
        return 4;
    }

    for (i=0, idx=0; i<x_y_inter_len; i++)
    {
        if( (idx = nearest_neighbour(NPDA_X(i), idx, x0, x0_y0_len)) == -1) //Finds index (idx) in x0 nearest to the x(i)=NPDA_X(i)
        {
            return 1;
        }
        if(idx >= x0_y0_len - 1) //This should be ensured by design of nearest_neighbour(), but worth checking
        {
            return 2;
        }
        dx = x0[idx + 1] - x0[idx];
        dy = (fptype)(y0[idx + 1]) - (fptype)(y0[idx]);

        if( fabs(dx) <= PRACTICAL_ZERO ) //This is ensured through is_increasing_monotonically() check on cal data.
        {
            return 3;
        }
        slope = dy/dx;
        y_inter[i] = y0[idx] + slope * (NPDA_X(i) - x0[idx]);
    }
    return 0;
}

/**
 * @brief Adding a new interpolated scan from __npda_y to the average vector in __npda_avg, adjusting data by offset
 *
 * @param[in] scany - Pointer to scan data
 * @param[in] scany_len - Length of the scan data
 * @param[in] valid_scan_cnt - Count of valid scans
 * @param[in] offset - Based on the AC position in __npda_y, used to shift __npda_y so all averaged data has AC peak at AC_REFERENCE_INDEX
 * @param[out] npda_avg_len - Length of valid data in npda_avg
 */
#if defined(DEBUG) || defined(TEST)
void average_incremental(fptype * scany, int scany_len, int valid_scan_cnt, int offset, uint16_t * npda_avg_len)
#else
static inline void average_incremental(fptype * scany, int scany_len, int valid_scan_cnt, int offset, uint16_t * npda_avg_len)
#endif
{
    int i, j;

    if (valid_scan_cnt == 0) {
        /* Initialise average buffer for first scan */
        int mem_start = (offset>0 ? offset : 0); //idx in __npda_avg where the first elem of scany shall be copied
        int mem_end = mem_start + scany_len + (offset<0 ? (offset) : 0); //one idx after the idx in __npda_avg where the last elem of scany shall be copied
        if(mem_end > MAX_WINDOW_SIZE) mem_end = MAX_WINDOW_SIZE;
        if(mem_start > 0) memset(__npda_avg, 0, mem_start*sizeof(fptype));
        if(mem_end < MAX_WINDOW_SIZE) memset(__npda_avg + mem_end, 0, (MAX_WINDOW_SIZE - mem_end)*sizeof(fptype));
        memcpy(__npda_avg + mem_start, scany + (offset<0 ? (-offset) : 0), (mem_end - mem_start)*sizeof(fptype));
        *npda_avg_len = mem_end;
    }
    else {
        /* Incremental average for subsequent scans */
        for (i=(offset<0 ? (-offset) : 0), j=(offset>0 ? offset : 0); (i<scany_len) && (j<MAX_WINDOW_SIZE); i++, j++) {
            __npda_avg[j] += (scany[i] - __npda_avg[j]) / ((fptype)valid_scan_cnt + 1.0);
        }
        if(j < (*npda_avg_len)) {
            *npda_avg_len = j;
        }
    }
}


/**
 * @brief Returning a data window (q1, q2) in scany containing the points above half height around the specified max value position
 *
 * @param[in] scany - input vector
 * @param[in] scany_len - length of the input vector
 * @param[in] maxval - max(scany)
 * @param[in] maxpos - index of maxval in scany
 * @param[out] q1 - index of the left end of FWHM "window"
 * @param[out] q2 - index of the right end of FWHM "window"
 *
 * @return 0 - Success
 * @return 1 - Error: maxpos is less than 1 or higher than scany_len-1
 * @return 2 - Error: q2 is larger than last idx in scany
 */
int find_ac_peak(fptype *scany, int scany_len, fptype maxval, int maxpos, int *q1, int *q2) {
	/* Calculate half height of the data */
	fptype half_height = maxval / 2.0;
	/* This is just to get rid of the compiler warning */
    *q1 = maxpos;
    *q2 = maxpos;

    if(maxpos < 1 || maxpos >= scany_len - 1)
    {
        return 1;
    }

    /* looking for half_height on the left of maxpos */
	int i = maxpos;
	while (i > 0 && scany[i] > half_height) { //TODO: discuss with James if when i=0 this should be wrong
		i --;
	}
	*q1 = i;

    /* looking for half_height on the right of maxpos */
	i = maxpos;
	while (scany[i] > half_height) {
		i ++;
        if( i >= scany_len )
        {
            return 2;
        }
	}
	*q2 = i;

    return 0;
}

/**
 * @brief Finds points that will be later used for fitting a parabola
 *
 * @param[in] scany - Scan data starting at the idx of the q1 of FWHM
 * @param[in] scany_len - Distance between q1 and q2
 * @param[in] wmax - Max yscan value within [q1, q2]
 * @param[out] active_points_buffer - Buffer containing 1 is the value is to be taken into account in fitting or 0 if not
 * @return int
 * @return 0 - Success
 * @return 1 - Error: scany_len less than 3
 */
STATIC int find_active_points(fptype * scany, int scany_len, fptype wmax, byte * active_points_buffer) {
    fptype range_bound_min = 0.5 * wmax;
    fptype range_bound_max = 0.95 * wmax;
    int i;
    if(scany_len <= 2)
    {
        return 1;
    }
    for (i=0; i<scany_len; i++) {
        if (scany[i] >= range_bound_min && scany[i] <= range_bound_max) {
            active_points_buffer[i] = 1;
        }
        else {
            active_points_buffer[i] = 0;
        }
    }
    return 0;
}

/**
 * @brief Calculating idx at which the parabola reaches its maximum (and returning the value at that idx).
 *
 * @param[in] coeffs - Parabola coefficients, with y=coeff[2]*x^2 + coeff[1]*x + coeff[0]
 * @param[out] peak_idx -  Idx at which the parabola achieves its maximum
 *
 * @return int
 * @return 0 - Success
 * @return 1 - Error: Parabola has minimum, but no maximum
 * @return 2 - Error: Parabola is a straight line and hence no maximum
 */
STATIC int calc_parabola_max(double * coeffs, int *peak_idx)
{
    if(coeffs[2] > 0) /* The parabola has minimum, but no maximum */
    {
        return 1;
    }
    if(fabs(coeffs[2]) <= PRACTICAL_ZERO) /* The parabola is actually a straight line, and maximum cannot be determined*/
    {
        return 2;
    }

    *peak_idx = (int) rint( (-coeffs[1] / ( 2 * coeffs[2] ) - __npda_offsetted_x_start) / INTERPOLATION_DISTANCE);
    /* *peak_value = NPDA_X(*peak_idx)*(coeffs[2]*NPDA_X(*peak_idx) + coeffs[1]) + coeffs[0]; */

    return 0;
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
 * @return 1 - Error: q1 and q2 are too far away, therefore not all
 *             active_members can fit into allocated array. Consider increasing
 *             MAX_AC_HHW.
 * @return 11 - Error: q1 and q2 are too close to each other
 * @return 21 - Error: Not enough active members in data - q1 and q2 are too
 *              close or a lot of data falls out of the acceptable limits for
 *              data to be considered in the interpolation.
 * @return 22 - Error: Polyfit failed - singular matrix encountered
 * @return 23 - Error: Q1 is negative
 * @return 31 - Error: Parabola has a minimum, but no maximum
 * @return 32 - Error: Parabola is a straight line and hence no maximum
 * @return 41 - Error: The peak of the parabola is outside [q1, q2] window
 *
 * @pre scany must be accessible at idx q2, i.e. scany[q2] must be valid
 */
STATIC int find_ac_quad(fptype *scany, int q1, int q2, fptype wmax, int *peak_idx) {
    size_t max_range_set_size = q2 - q1 + 1;
    if(max_range_set_size > MAX_AC_HHW)
    {
        return 1;
    }
    int iret;
    fptype *scany_offset_by_q1 = scany + q1;

    if((iret = find_active_points(scany_offset_by_q1, max_range_set_size, wmax, __npda_hhw)) != 0)
    {
        return 10 + iret;
    }

    double coeffs[3];
    if((iret = polyfit2(scany_offset_by_q1, q1, __npda_hhw, max_range_set_size, coeffs)) != 0)
    {
        return 20 + iret;
    }

    if((iret = calc_parabola_max(coeffs, peak_idx)) != 0)
    {
        return 30 + iret;
    }
    if((*peak_idx) < q1 || (*peak_idx) > q2) /* Parabola peak outside the [q1, q2] window */
    {
        return 41;
    }

    return 0;
}

/**
 * @brief Find AC peak in interpolated data in __npda_y, use it as an offset to merge to current average data set in __npda_avg
 *
 * @param[in] scany - Pointer to the scan data
 * @param[in] scany_len - Length of the scan data
 * @param[in] med - Median of the __npda_y
 * @param[in] valid_scan_cnt - Count of valid scans within the block
 * @param[out] npda_avg_len - Length of valid data in __npda_avg.
 * @return int
 * @return 0 - Success
 * @return 1 - Error: invalid scan, cannot find max position
 * @return 11 - Error: maxpos is less than 1 or higher than scany_len-1
 * @return 12 - Error: q2 is larger than last idx in scany
 * @return 21 - Error: q1 and q2 are too far away, therefore not all
 *             active_members can fit into allocated array. Consider increasing
 *             MAX_AC_HHW.
 * @return 31 - Error: q1 and q2 are too close to each other
 * @return 41 - Error: Not enough active members in data - q1 and q2 are too
 *              close or a lot of data falls out of the acceptable limits for
 *              data to be considered in the interpolation.
 * @return 42 - Error: Polyfit failed - singular matrix encountered
 * @return 43 - Error: Q1 is negative
 * @return 51 - Error: Parabola has a minimum, but no maximum
 * @return 52 - Error: Parabola is a straight line and hence no maximum
 * @return 61 - Error: The peak of the parabola is outside [q1, q2] window
 */
int update_average(fptype *scany, int scany_len, fptype med, int valid_scan_cnt, uint16_t *npda_avg_len) {
    int i;
    fptype maxval = -FPTYPE_MAX; /* max(__npda_y) and its index */
    int maxpos = -1;
    int q1, q2; /* Peak data left-right */
    int iret;

    /* Adjust __npda_y to median and calculate max */
    for (i=0; i<scany_len; i++) {
        scany[i] -= med;
        if (scany[i] > maxval) {
            maxval = scany[i];
            maxpos = i;
        }
    }
    if (maxpos <= 0 || maxpos >= scany_len - 1) {
        /* Invalid scan! */
        return 1;
    }

    /* Find half max height window (q1, q2) */
    if((iret = find_ac_peak(scany, scany_len, maxval, maxpos, &q1, &q2)) != 0) //WARNING: q1 may equal q2
    {
        return 10 + iret;
    }
    int peak_idx;
    /* Find peak position with interpolation */
    if((iret = find_ac_quad(scany, q1, q2, maxval, &peak_idx)) != 0)
    {
        /* find_ac_quad() failed! */
        return 20 + iret;
    }

    /* Add to average */
    average_incremental(scany, scany_len, valid_scan_cnt, AC_REFERENCE_INDEX - peak_idx, npda_avg_len);

    return 0;
}

/**
 * @brief Saving all PC peak candidates to __npda_pcpc following the AC peak index
 *
 * @param[in] searchdata Data in which the peak is searched
 * @param[in] searchdata_len Length of the data in which the peak is searched
 * @param[in] AC_idx AC peak index
 * @param[out] pc_peak_cnt Number of candidates saved in __npda_pcpc
 */
void find_pc_peak_candidates(fptype* searchdata, uint16_t searchdata_len, int AC_idx, int *pc_peak_cnt) {
    /*
     DEFINE WINDOW (A human cornea can't be less than 0.4 or greater than 0.7)
     Reduce the range where to look for PC pos based in AC pos
    */
    int leftbound = AC_idx + floor(MIN_CENT_CORNEAL_THICK / (INTERPOLATION_DISTANCE * CORNEA_REFRACTIVE_IDX));
    int rightbound = MIN(AC_idx + floor(MAX_CENT_CORNEAL_THICK / (INTERPOLATION_DISTANCE * CORNEA_REFRACTIVE_IDX)), searchdata_len);

    /* Finding peaks within the bounds */
    *pc_peak_cnt = 0;
    int i;
    for (i=leftbound+1; i<rightbound-1 && *pc_peak_cnt<MAX_PCPC; i++) {
        if (searchdata[i] > 0.0 && searchdata[i] > searchdata[i - 1] && searchdata[i] > searchdata[i + 1]) {
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
 * @param[in] searchdata Convolved average signal for the block
 * @param[in] searchdata_len Length of searchdata
 * @param[in] AC_height AC peak height
 * @param[in] AC_idx AC peak position
 * @param[in] pc_peak_cnt Number of PC peak candidates in __npda_pcpc
 * @param[out] PC_idx Returning PC index
 * @param[out] PC_weight Returning PC weight
 * @param[out] thickness Returning corneal thickness for the block
 *
 */
int find_pc_peak(fptype* searchdata, uint16_t searchdata_len, fptype AC_height, int AC_idx, int pc_peak_cnt, int *PC_idx, fptype *PC_weight, fptype *thickness) {
    *PC_weight = -FPTYPE_MAX;
    int i;
    *PC_idx = -1;
    fptype t, pch, wt;
    #ifdef PC_PEAK_CORRECTION
    fptype_t LHminval, RHminval, slope, maxval, corrected_peak_val;
    #endif
    if( AC_height <= PRACTICAL_ZERO )
    {
        return 1;
    }
    int PClidx;
    int PCridx;
    fptype PClhgt;
    fptype PCrhgt;
    fptype a_coeff;
    fptype b_coeff;
    for (i=0; i<pc_peak_cnt; i++) {
        t = CORNEA_REFRACTIVE_IDX * (NPDA_X(__npda_pcpc[i]) - NPDA_X(AC_idx)); /* Estimate of corneal thickness */
        if(t > 0.0)
        {
#ifdef RELATIVE_PC_PEAK_CALC
            PClidx = __npda_pcpc[i] - (int)rint(HALF_WIDTH / INTERPOLATION_DISTANCE);
            if(PClidx < 0)
            {
                PClidx = 0;
            }
            PCridx = __npda_pcpc[i] + (int)rint(HALF_WIDTH / INTERPOLATION_DISTANCE);
            if( PCridx >= searchdata_len)
            {
                PCridx = searchdata_len-1;
            }

            PClhgt = searchdata[PClidx];
            PCrhgt = searchdata[PCridx];
            if(PCridx-PClidx == 0)
            {
                return 1;
            }
            a_coeff = (PCrhgt-PClhgt)/((fptype)(PCridx-PClidx));
            b_coeff = PClhgt - a_coeff * ((fptype)PClidx);
            pch = (searchdata[__npda_pcpc[i]]-(a_coeff*__npda_pcpc[i]+b_coeff)) / AC_height;
            if(pch < 0)
            {
                pch = 0;
            }
            wt = 1.0 - exp( -230.3 * pch );
#else
            pch = searchdata[__npda_pcpc[i]] / AC_height;
            wt = 1.0 - exp((-2.303 * pch) / (0.035 - (0.045*t) + (0.012*t*t)));
#endif
            if (*PC_weight < wt) {
                *PC_weight = wt;
                *PC_idx = __npda_pcpc[i];
            }
        }
    }

    if(*PC_idx == -1)
    {
        return 2;
    }

#ifdef PC_PEAK_CORRECTION
    int PCleftindex = *PC_idx - (int)rint(HALF_WIDTH / INTERPOLATION_DISTANCE);
    if(PCleftindex < 0)
    {
        PCleftindex = 0;
    }
    int LHminindex;

    LHminval = vmin(searchdata + PCleftindex, *PC_idx - PCleftindex, &LHminindex);

    LHminindex += (PCleftindex + 1);

    int RHminindex = 2 * (*PC_idx) - LHminindex;
    if( RHminindex >= searchdata_len)
    {
        RHminindex = searchdata_len-1;
    }

    RHminval = searchdata[RHminindex];
    slope = (RHminval - LHminval) / (RHminindex - LHminindex);

    maxval = -FPTYPE_MAX;
    *PC_idx = -1;

    for(i=LHminindex; i<RHminindex; i++)
    {
        corrected_peak_val = searchdata[i] - (LHminval + slope * (i - LHminindex));
        if(corrected_peak_val > maxval)
        {
            *PC_idx = i;
            maxval = corrected_peak_val;
        }
    }
#endif

    *thickness = CORNEA_REFRACTIVE_IDX * (NPDA_X(*PC_idx) - NPDA_X(AC_idx)); /* Estimate of corneal thickness */

    return 0;
}
