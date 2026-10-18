/*
 * ring_buffer.h
 *
 *  Created on: Oct 14, 2026
 *      Author: deivideich
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include <stdint.h>
#include <stdbool.h>

enum {
    RING_BUFFER_SIZE = 64U,
    RING_BUFFER_MASK = 63U
};


typedef struct {
    uint8_t buffer[RING_BUFFER_SIZE];
    uint16_t head;
    uint16_t tail;
} RingBuffer_t;

void RingBuffer_Init(RingBuffer_t *rb);
bool RingBuffer_Put(RingBuffer_t *rb, uint8_t byte);
bool RingBuffer_Get(RingBuffer_t *rb, uint8_t *byte);

#endif /* INC_RING_BUFFER_H_ */
