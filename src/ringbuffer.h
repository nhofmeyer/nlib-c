#ifndef INC_RING_BUFFER_H
#define INC_RING_BUFFER_H

#include "stdint.h"
#include "stdbool.h"

typedef struct ring_buffer_t {
    void * data;            // data rb
    uint32_t capacity;      // maximum capacity in element count (not bytes)
    uint32_t item_size;     // size of contained items in bytes
    uint32_t size;          // current number of elements stored in ring rb
    uint32_t read;          // read index of data array
    uint32_t write;         // write index of data array
    bool overwrite_on_full; // option for behavior on full enqueue 
} ring_buffer_t;

typedef enum RING_BUFFER_ERR {
    RING_BUFFER_OK = 0,
    RING_BUFFER_ERR_FULL = 1,
    RING_BUFFER_ERR_EMPTY = 2,
    RING_BUFFER_ERR_NOT_INITIALIZED = 3,
} RING_BUFFER_ERR;

/**
 * @brief Initialize ring rb structure
 * 
 * @param rb rb struct to initialize (will be modified)
 * @param capacity max number of items to store in rb
 * @param overwrite_when_full if true, queue will overwrite oldest data when user enqueues a value on a full queue rather than fail.
 * @return RING_BUFFER_OK on successful creation, RING_BUFFER_ERR_NOT_INITIALIZED on failure
 */
RING_BUFFER_ERR ring_buffer_init(ring_buffer_t * const rb,  const uint32_t capacity, const uint32_t item_size, const bool overwrite);

/**
 * @brief Initialize ring buffer with user-provided memory
 * 
 * @param rb ring buffer to init
 * @param capacity max number of elements to store
 * @param item_size length of element in bytes
 * @param overwrite whether enqueue should overwrite old data when buffer is full
 * @param buffer    user-provided data block, user must provide (item_size * capacity) bytes of memory
 * @return RING_BUFFER_ERR 
 */
RING_BUFFER_ERR ring_buffer_init_static(ring_buffer_t * const rb, const uint32_t capacity, const uint32_t item_size, const bool overwrite, uint8_t * const buffer);

/**
 * @brief Uninitialize ring rb which has been dynamically allocated
 * 
 * @param rb rb to clean up
 * @return RING_BUFFER_OK on successful cleanup
 * @warning Do not call on rb initialized with ring_buffer_init_static(),
 *          cleanup of static ring rb to be handled manually by user
 */
RING_BUFFER_ERR ring_buffer_deinit(ring_buffer_t * const rb);

/**
 * @brief Enqueue object in the rb
 * 
 * @param rb rb to add object
 * @param item item to enqueue (copy into rb)
 * @return RING_BUFFER_OK on successful add, RING_BUFFER_ERR_FULL if ring rb is full (unless ring rb is configured with over-write)
 *         IN this case you should dequeue an item and try again
 */
RING_BUFFER_ERR ring_buffer_enqueue(ring_buffer_t * const rb, const void * const item);

/**
 * @brief Get item from the queue
 * 
 * @param rb to get item from
 * @param item pointer which is filled by call
 * @return RING_BUFFER_OK if item dequeued successfully, RING_BUFFER_ERR_EMPTY if queue is empty
 */
RING_BUFFER_ERR ring_buffer_dequeue(ring_buffer_t * const rb, void * const item);

/**
 * @brief reset a ring rb without destroying it
 * 
 * @param rb to reset
 * @return RING_BUFFER_OK if ring rb reset, RING_BUFFER_ERR_NOT_INITIALIZED if not set up 
 */
RING_BUFFER_ERR ring_buffer_reset(ring_buffer_t * const rb);


bool ring_buffer_is_full(const ring_buffer_t * const rb);
bool ring_buffer_is_empty(const ring_buffer_t * const rb);

/**
 * @brief Returns the size (current elements in ring buffer)
 * 
 * @param rb buffer to check size
 * @return number of elements held
 */
uint32_t ring_buffer_size(const ring_buffer_t * const rb);



#endif // INC_RING_BUFFER_H