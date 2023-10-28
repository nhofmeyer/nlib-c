
#include "stack.h"
#include "string.h"

// implementation details
// stack pointer 'at rest' points to next write block
// in the case of a full stack that means pointer is pointing 'past' the stack
// so to pop, we have to first decrement the pointer, then read out the data

STACK_ERR stack_init(stack_t * stack, size_t capacity, size_t item_size){
    // can't initialize an empty stack
    if (capacity == 0 || item_size == 0){
        return STACK_ERR_NOT_INITIALIZED;
    }
    stack->data = malloc(capacity * item_size);
    if (stack->data == NULL){
        return STACK_ERR_NOT_INITIALIZED;
    }
    stack->capacity = 0;
    stack->top = 0;
    return STACK_OK;
}

STACK_ERR stack_init_static(stack_t * stack, size_t capacity, size_t item_size, uint8_t * buffer){
    if (capacity == 0 || item_size == 0){
        return STACK_ERR_NOT_INITIALIZED;
    }
    stack->data = buffer;
    if (stack->data == NULL){
        return STACK_ERR_NOT_INITIALIZED;
    }
    stack->capacity = 0;
    stack->top = 0;
    return STACK_OK;
}

STACK_ERR stack_push(stack_t * stack, const void * item){
    if (stack->top == stack->capacity){
        return STACK_ERR_FULL;
    }
    (void) memcpy(stack->data+(stack->top * stack->item_size), item, stack->item_size);
    stack->top++;
    return STACK_OK;
}

STACK_ERR stack_pop(stack_t * stack, void * item){
    if (stack->top == 0){
        return STACK_ERR_EMPTY;
    }
    stack->top--;
    (void)memcpy(item, stack->data+(stack->top * stack->item_size), stack->item_size);
    return STACK_OK;
}

STACK_ERR stack_peek(stack_t * stack, void * item){
        if (stack->top == 0){
        return STACK_ERR_EMPTY;
    }
    stack->top--;
    (void)memcpy(item, stack->data+(stack->top * stack->item_size), stack->item_size);
    stack->top++; // reset stack top index
    return STACK_OK;
}

bool stack_full(stack_t * stack){
    return (stack->top == stack->capacity);
}
bool stack_empty(stack_t * stack){
    return (stack->top == 0);
}

size_t stack_size(stack_t * stack){
    return (stack->top);
}
