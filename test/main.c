
#include "ring_buffer.h"
#include "stdio.h"
#include "assert.h"

#define RB_DEBUG_DUMP 1

void rb_dump(ring_buffer_t *buffer)
{
    #if RB_DEBUG_DUMP
    printf(
        "====== Ring Buffer Block ======\r\n"
        "Data pointer:      0x%08x\r\n"
        "Capacity:          %i\r\n"
        "Item Size (bytes): %i\r\n"
        "Size (curr items): %i\r\n"
        "Read head:         %i\r\n"
        "Write head:        %i\r\n"
        "===============================\r\n\r\n",
        buffer->data,
        buffer->capacity,
        buffer->item_size,
        buffer->size,
        buffer->read,
        buffer->write);
    #endif
}

int main(int argc, char *argv[])
{
    printf("%-60s", "Creating buffer with no-overwrite");
    ring_buffer_t rb;
    ring_buffer_init(&rb, 10, sizeof(int), false);
    printf("OK\r\n");
    rb_dump(&rb);

    printf("%-60s", "Checking buffer is empty");
    assert(ring_buffer_is_empty(&rb) == true);
    assert(ring_buffer_is_full(&rb) == false);
    printf("OK\r\n");
  rb_dump(&rb);

    printf("%-60s", "Filling buffer to capacity");
    for (int i = 0; i < 10; ++i)
    {
        printf("[%i] ",i);
        assert(ring_buffer_enqueue(&rb, &i) == RING_BUFFER_OK);
        rb_dump(&rb);
    }
    printf("OK\r\n");
  rb_dump(&rb);

    printf("%-60s", "Checking buffer after filling to capacity");
    assert(ring_buffer_is_full(&rb) == true);
    assert(ring_buffer_is_empty(&rb) == false);
    printf("OK\r\n");
      rb_dump(&rb);

    printf("%-60s", "Enqueue on full buffer should return error");
    int i = 1;
    assert(ring_buffer_enqueue(&rb, &i) == RING_BUFFER_ERR_FULL);
    assert(ring_buffer_is_full(&rb) == true);
    assert(ring_buffer_is_empty(&rb) == false);
    printf("OK\r\n");
  rb_dump(&rb);

    printf("%-60s", "Emptying buffer");
    for (int i = 0; i < 10; ++i){
        int j;
        assert(ring_buffer_dequeue(&rb, &j) == RING_BUFFER_OK);
    }
    printf("OK\r\n");
  rb_dump(&rb);

    printf("%-60s", "Checking buffer is empty after removing all items");
    assert(ring_buffer_is_empty(&rb) == true);
    assert(ring_buffer_is_full(&rb) == false);
    printf("OK\r\n");



    return 0;
}