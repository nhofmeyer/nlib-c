
#include "ringbuffer.h"
#include "stdlib.h"
#include "string.h"

/**
 * @brief Round up a number to the next power of 2
 * 
 * @param x number to round up
 * @return nearest power of 2 >= x
 */
static uint32_t pow2_roundup(uint32_t x){
    if (x == 0){
        return 1; // 1 is 2^0
    }
    x -=1;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x += 1;
    return x;
}


bool ring_buffer_is_full(const ring_buffer_t * const rb){
    return ((rb->write == rb->read) && (rb->size > 0));
}

bool ring_buffer_is_empty(const ring_buffer_t * const rb){
    return ((rb->write == rb->read) && (rb->size == 0));
}

RING_BUFFER_ERR ring_buffer_init(ring_buffer_t * const rb, const uint32_t capacity, const uint32_t item_size, const bool overwrite){
    if (capacity == 0 || item_size == 0){
        return RING_BUFFER_ERR_NOT_INITIALIZED;
    }
    
    uint32_t capacity_rounded = pow2_roundup(capacity);
    rb->data = malloc(capacity_rounded * item_size);
    if (rb->data == NULL){
        return RING_BUFFER_ERR_NOT_INITIALIZED;
    }

    rb->capacity = capacity_rounded;
    rb->item_size = item_size;
    rb->size = 0;
    rb->read = 0;
    rb->write = 0;
    rb->overwrite_on_full = overwrite;
    return RING_BUFFER_OK;
}

RING_BUFFER_ERR ring_buffer_init_static(ring_buffer_t * const rb, const uint32_t capacity, const uint32_t item_size, const bool overwrite, uint8_t * const buffer){
    if (buffer == NULL){
        return RING_BUFFER_ERR_NOT_INITIALIZED;
    }
    rb->data = buffer;
    rb->capacity = capacity; // extra slot due to implementation detail
    rb->item_size = item_size;
    rb->size = 0;
    rb->read = 0;
    rb->write = 0;
    rb->overwrite_on_full = overwrite;
    return RING_BUFFER_OK;
}

RING_BUFFER_ERR ring_buffer_deinit(ring_buffer_t * const rb){
    if(rb->data){
        free(rb->data); // no real way to catch this if there's an error
        rb->data = NULL;
    }
    rb->capacity = 0;
    rb->read = 0;
    rb->write = 0;
    rb->size = 0;
    return RING_BUFFER_OK;
}

RING_BUFFER_ERR ring_buffer_enqueue(ring_buffer_t * const rb, const void * const item){
    if(rb->data == NULL){
        return RING_BUFFER_ERR_NOT_INITIALIZED;
    }
    bool overwritten = false;

    if (ring_buffer_is_full(rb)){
        if (rb->overwrite_on_full == true){
            // advancing read index 'overwrites' last element which is under write pointer
            rb->read++;
            rb->read &= ~(rb->capacity);
            overwritten = true;
        } else {
            return RING_BUFFER_ERR_FULL;
        }
    }

    (void) memcpy(rb->data+(rb->write * rb->item_size), item, rb->item_size);

    // rollover
    rb->write++;
    rb->write &= ~(rb->capacity);

    if (overwritten == false){
        rb->size++;
    }

    return RING_BUFFER_OK;
}

RING_BUFFER_ERR ring_buffer_dequeue(ring_buffer_t * const rb, void * const item){
    if(rb->data == NULL){
        return RING_BUFFER_ERR_NOT_INITIALIZED;
    }
    
    if (ring_buffer_is_empty(rb)){
        return RING_BUFFER_ERR_EMPTY;
    }

    (void) memcpy(rb->data+(rb->read * rb->item_size), item, rb->item_size);
    rb->read++;
    rb->read &= ~(rb->capacity); // rollover
    rb->size--;

    return RING_BUFFER_OK;
}

RING_BUFFER_ERR ring_buffer_reset(ring_buffer_t * const rb){
    if (rb->data == NULL){
        return RING_BUFFER_ERR_NOT_INITIALIZED;
    }
    rb->read = 0;
    rb->write = 0;
    rb->size = 0;
    return RING_BUFFER_OK;
}

uint32_t ring_buffer_size(const ring_buffer_t * const rb){
    return rb->size;
}