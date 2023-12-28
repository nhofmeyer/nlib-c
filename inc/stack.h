
#ifndef INC_STACK_H
#define INC_STACK_H

#include "nlib_defs.h"

// control block for stack
typedef struct stack_t {
    uint8_t * data;
    size_t capacity;
    size_t item_size;
    size_t top;
} stack_t;

/**
 * @brief Initialize stack with user-supplied memory block
 * 
 * @param stack object to init
 * @param capacity max number of elements storable on stack
 * @param item_size size of a single element in bytes
 * @param buffer user-provided buffer, must be (capacity * item_size) bytes
 * @return STACK_OK on successful init, STACK_ERR_NOT_INITIALIZED on failure
 */
NL_RESULT stack_init(stack_t * const stack, size_t capacity, size_t item_size, uint8_t * const buffer);

/**
 * @brief Push an element onto the stack
 * 
 * @param stack stack to add the element to
 * @param item pointer to item to add
 * @return NL_OK on successful push, NL_ERR_FULL if stack has no space
 */
NL_RESULT stack_push(stack_t * const stack, const void * const item);

/**
 * @brief Pop item from the stack
 * 
 * @param stack stack to pull item from
 * @param item  pointer to item to retreive (will be overwritten)
 * @return NL_OK on success, NL_ERR_EMPTY if no item to pop
 * @note   pop removes top item
 */
NL_RESULT stack_pop(stack_t * const stack, void * const item);

/**
 * @brief Peek at top of stack
 * 
 * @param stack stack to check
 * @param item  pointer to item to retreive (will be overwritten)
 * @return STACK_OK on success, STACK_EMPTY if there aren't any items.
 * @note   Functionally the same as stack_pop but doesn't remove top item
 */
NL_RESULT stack_peek(const stack_t * const stack, void * const item);

/**
 * @brief Check if stack is full
 * 
 * @param stack to check
 * @return true if stack is full (cannot push any additional items)
 * @return false if stack is not full
 */
bool stack_full(const stack_t * const stack);

/**
 * @brief Check if stack is empty
 * 
 * @param stack to check
 * @return true if stack is empty (cannot pop or peek any additional items)
 * @return false if stack is not empty
 */
bool stack_empty(const stack_t * const stack);

/**
 * @brief Check how many items are currently held in stack
 * 
 * @param stack to check
 * @return number of items on stack
 */
size_t stack_size(const stack_t * const stack);

/**
 * @brief Check capacity (maximum size) of stack in elements
 * 
 * @param stack to check
 * @return capacity of stack
*/
size_t stack_capacity(const stack_t * const stack);

#endif // INC_STACK_H
