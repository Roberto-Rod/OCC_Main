/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _NPDA_H    /* Guard against multiple inclusion */
#define _NPDA_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        Brief one-line summary of the constant.
    
      @Description
        Full description, explaining the purpose and usage of the constant.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
      @Remarks
        Any additional remarks
     */

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

/* NPDA errors, should be shared with PDAB */
typedef enum {
            SUCCESS = 0,
            ERROR_CAL_NOT_STR_MON_INCREASING,
            ERROR_UNEXPECTED_FAILURE,
            WARNING_FEW_VALID_BLOCKS,
            WARNING_PC_PEAKS_SMALL,
            WARNING_PC_PEAKS_SMALL_AND_FEW_VALID_BLOCKS,
            WARNING_HIGH_DATA_SPREAD,
            WARNING_HIGH_DATA_SPREAD_AND_FEW_VALID_BLOCKS,
            WARNING_HIGH_DATA_SPREAD_AND_PC_PEAKS_SMALL,
            WARNING_HIGH_DATA_SPREAD_AND_PC_PEAKS_SMALL_AND_FEW_VALID_BLOCKS,
            ERROR_TOO_FEW_BLOCKS,
            ERROR_PC_PEAKS_TOO_SMALL,
            ERROR_SPREAD_TOO_HIGH
} NPDA_RETVAL;
    
    
typedef struct
{
    float thickness;
    float std;
    uint16_t valid_blocks;
    uint16_t total_blocks;
    NPDA_RETVAL error;
} _NPDA_MEASUREMNT;

    // *****************************************************************************

    /** Descriptive Data Type Name

      @Summary
        Brief one-line summary of the data type.
    
      @Description
        Full description, explaining the purpose and usage of the data type.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

      @Remarks
        Any additional remarks
        <p>
        Describe enumeration elements and structure and union members above each 
        element or member.
     */



    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
