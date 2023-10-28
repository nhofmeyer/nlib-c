
#ifndef INC_STACK_H
#define INC_STACK_H

#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"

// return codes for stack
typedef enum STACK_ERR {
    STACK_OK = 0,
    STACK_ERR_FULL,
    STACK_ERR_EMPTY,
    STACK_ERR_NOT_INITIALIZED
} STACK_ERR;

// control block for stack
typedef struct stack_t {
    void * data;
    size_t capacity;
    size_t item_size;
    size_t top;
} stack_t;

/**
 * @brief Initialize stack object (dynamic allocation)
 * 
 * @param stack object to init
 * @param capacity max number of elements
 * @param item_size size of each element in bytes
 * @return STACK_OK on success, STACK_ERR_NOT_INITIALIZED on failure
 */
STACK_ERR stack_init(stack_t * stack, size_t capacity, size_t item_size);

/**
 * @brief Initialize stack with user-supplied memory block
 * 
 * @param stack object to init
 * @param capacity max number of elements storable on stack
 * @param item_size size of a single element in bytes
 * @param buffer user-provided buffer, must be (capacity * item_size) bytes
 * @return STACK_OK on successful init, STACK_ERR_NOT_INITIALIZED on failure
 */
STACK_ERR stack_init_static(stack_t * stack, size_t capacity, size_t item_size, uint8_t * buffer);

/**
 * @brief Push an element onto the stack
 * 
 * @param stack stack to add the element to
 * @param item pointer to item to add
 * @return STACK_OK on successful push, STACK_ERR_FULL if stack has no space
 */
STACK_ERR stack_push(stack_t * stack, const void * item);

/**
 * @brief Pop item from the stack
 * 
 * @param stack stack to pull item from
 * @param item  pointer to item to retreive (will be overwritten)
 * @return STACK_OK on success, STACK_ERR_EMPTY if no item to pop
 * @note   pop removes top item
 */
STACK_ERR stack_pop(stack_t * stack, void * item);

/**
 * @brief Peek at top of stack
 * 
 * @param stack stack to check
 * @param item  pointer to item to retreive (will be overwritten)
 * @return STACK_OK on success, STACK_EMPTY if there aren't any items.
 * @note   Functionally the same as stack_pop but doesn't remove top item
 */
STACK_ERR stack_peek(stack_t * stack, void * item);

/**
 * @brief Check if stack is full
 * 
 * @param stack to check
 * @return true if stack is full (cannot push any additional items)
 * @return false if stack is not full
 */
bool stack_full(stack_t * stack);

/**
 * @brief Check if stack is empty
 * 
 * @param stack to check
 * @return true if stack is empty (cannot pop or peek any additional items)
 * @return false if stack is not empty
 */
bool stack_empty(stack_t * stack);

/**
 * @brief Check how many items are currently held in stack
 * 
 * @param stack to check
 * @return number of items on stack
 */
size_t stack_size(stack_t * stack);


#endif // INC_STACK_H
