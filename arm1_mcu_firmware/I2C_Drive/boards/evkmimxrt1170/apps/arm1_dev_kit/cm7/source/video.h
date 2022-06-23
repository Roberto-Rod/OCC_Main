/*****************************************************************************/
/**
 * @file 
 *   video.h
 * @brief 
 *   Top level layer for camera/display image buffering and processing
 *
 *****************************************************************************/

/*
 * Copyright (c) 2022 Occuity Ltd. All rights reserved.
 */

#if !defined(VIDEO_H)
#define VIDEO_H

/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Public (external) variables                                               */
/*****************************************************************************/

/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/

void VIDEO_reset(void);
void VIDEO_initialise(void);
void VIDEO_frame_handler(void);
void VIDEO_compliance_test(void);

#endif // defined(VIDEO_H)


/*** end of file ***/