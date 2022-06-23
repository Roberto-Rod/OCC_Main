/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Occuity Limited

  @File Name
    pic_comms.c

  @Summary
    Message communications between PICs.

  @Description
    Message communications between PICs.
 */
/* ************************************************************************** */

#ifndef _PIC_COMMS_H    /* Guard against multiple inclusion */
#define _PIC_COMMS_H


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */


// *****************************************************************************
// Section: Data Types
// *****************************************************************************


// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************

void pic_communications_init(void);
void pic_communications_test(void);

bool pic_comms_queue_message(const uint8_t *data, uint32_t length, bool acknowledgement_required);
void pic_comms_task(void);
uint32_t crc32(uint32_t crc, const uint8_t *data, uint32_t length);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _PIC_COMMS_H */
