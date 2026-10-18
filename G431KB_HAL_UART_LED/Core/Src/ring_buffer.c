/*
 * ring_buffer.c
 *
 *  Created on: Oct 16, 2026
 *      Author: deivideich
 */


#include "ring_buffer.h"

void RingBuffer_Init(RingBuffer_t *rb){
	rb->head = 0;
	rb->tail = 0;
}

bool RingBuffer_Put(RingBuffer_t *rb, uint8_t byte) {
    uint16_t next_head = (rb->head + 1) & RING_BUFFER_MASK;

    if (next_head == rb->tail) {
        return false;
    }

    rb->buffer[rb->head] = byte;
    rb->head = next_head;

    return true;
}

bool RingBuffer_Get(RingBuffer_t *rb, uint8_t *byte) {
    if (rb->head == rb->tail) {
        return false;
    }

    *byte = rb->buffer[rb->tail];

    rb->tail = (rb->tail + 1) & RING_BUFFER_MASK;
    return true;
}
