
#include "stack.h"
#include "string.h"
#include "stdio.h"

// implementation details
// stack pointer 'at rest' points to next write block
// in the case of a full stack that means pointer is pointing 'past' the stack
// so to pop, we have to first decrement the pointer, then read out the data

NL_RESULT stack_init(stack_t * const stack, size_t capacity, size_t item_size, uint8_t * const buffer){
    if (capacity == 0 || item_size == 0){
        return NL_ERR_NOT_INITIALIZED;
    }
    stack->data = buffer;
    if (stack->data == NULL){
        return NL_ERR_NOT_INITIALIZED;
    }
    stack->capacity = capacity;
    stack->item_size = item_size;
    stack->top = 0;
    return NL_OK;
}

NL_RESULT stack_push(stack_t * const stack, const void * const item){
    if (stack->top == stack->capacity){
        return NL_ERR_FULL;
    }

    // insert item into stack memory
    (void)memcpy(stack->data+(stack->top * stack->item_size), item, stack->item_size);

    stack->top++;
    return NL_OK;
}

NL_RESULT stack_pop(stack_t * const stack, void * const item){
    if (stack->top == 0){
        return NL_ERR_EMPTY;
    }
    stack->top--;
    (void)memcpy(item, stack->data+(stack->top * stack->item_size), stack->item_size);
    return NL_OK;
}

NL_RESULT stack_peek(const stack_t * const stack, void * const item){
        if (stack->top == 0){
        return NL_ERR_EMPTY;
    }
    size_t top = (stack->top - 1);

    // copy data into item (in-out param)
    (void)memcpy(item, stack->data+(top * stack->item_size), stack->item_size);

    return NL_OK;
}

bool stack_full(const stack_t * const stack){
    return (stack->top == stack->capacity);
}

bool stack_empty(const stack_t * const stack){
    return (stack->top == 0);
}

size_t stack_size(const stack_t * const stack){
    return (stack->top);
}

size_t stack_capacity(const stack_t * stack){
    return (stack->capacity);
}
