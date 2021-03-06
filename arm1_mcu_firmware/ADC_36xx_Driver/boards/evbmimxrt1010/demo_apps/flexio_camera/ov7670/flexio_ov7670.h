/*
 * Copyright (c) 2015 -2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FLEXIO_OV7670_H__
#define __FLEXIO_OV7670_H__

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define OV7670_BYTES_PER_PIXEL      2u
#define OV7670_FRAME_WIDTH          160u
#define OV7670_FRAME_HEIGHT         120u
#define OV7670_FRAME_PIXELS         (OV7670_FRAME_WIDTH * OV7670_FRAME_HEIGHT)
#define OV7670_FRAME_BYTES          (OV7670_FRAME_PIXELS * OV7670_BYTES_PER_PIXEL)
#define OV7670_FRAME_BUFFER_CNT     2u

typedef uint16_t FrameBuffer_t[OV7670_FRAME_HEIGHT][OV7670_FRAME_WIDTH];
typedef uint16_t (*pFrameBuffer_t)[OV7670_FRAME_HEIGHT][OV7670_FRAME_WIDTH];

/*******************************************************************************
 * API
 ******************************************************************************/

void FLEXIO_Ov7670Init(void);
void FLEXIO_Ov7670CaptureStart(void);
void FLEXIO_Ov7670CaptureDone(void);

#endif /* __FLEXIO_OV7670_H__ */
