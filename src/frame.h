#ifndef _FRAME_H
#define _FRAME_H

#include <stdint.h>
#include <stdbool.h>

#define RX_FRAME_LENGTH 64

/**
 * Must be called before any other framing operations.
 */
void FRM_init(void);

/**
 * Use to push an array element to be framed and sent.
 * @param data a byte-aligned array pointer
 * @param length the length of the array
 */
void FRM_push(uint8_t* data, uint16_t length);

/**
 * Use to read unframed data from the receive buffer
 * 
 * @param data a byte-aligned array pointer to which the
 * unframed data will be copied
 * @return length the length of the array
 */
uint16_t FRM_pull(uint8_t* data);

void FRM_assignChannelInit(void (*functPtr)());
void FRM_assignChannelReadable(uint16_t (*functPtr)());
void FRM_assignChannelWriteable(uint16_t (*functPtr)());
void FRM_assignChannelRead(void (*functPtr)(void* data, uint32_t length));
void FRM_assignChannelWrite(void (*functPtr)(void* data, uint32_t length));

#endif