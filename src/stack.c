
#include "stack.h"

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
    for (uint32_t i = 0; i < stack->item_size; ++i){
        *(stack->data+(stack->top * stack->item_size)+i) = *(((uint8_t *)item)+i);
    }

    stack->top++;
    return NL_OK;
}

NL_RESULT stack_pop(stack_t * const stack, void * const item){
    if (stack->top == 0){
        return NL_ERR_EMPTY;
    }
    stack->top--;
    for (size_t i = 0; i < stack->item_size; ++i){
        *(((uint8_t *)item)+i) = *(stack->data+(stack->top * stack->item_size) + i);
    }
    return NL_OK;
}

NL_RESULT stack_peek(const stack_t * const stack, void * const item){
        if (stack->top == 0){
        return NL_ERR_EMPTY;
    }

    // apologies for this one
    for (size_t i = 0; i < stack->item_size; ++i){
        *(((uint8_t *)item)+i) = *(stack->data+((stack->top-1) * stack->item_size) + i);
    }
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
