#include <stddef.h>




/**
 * @brief Represents a ring buffer.
 * 
 * - 'capacity'        is the maximum number of elements the buffer can hold, this should be storage size divided by element size
 * - 'count'           is the current number of elements in the buffer
 * - 'head'            is the index of the next element to be read
 * - 'tail'            is the index where the next element will be written
 * - 'elementSize'     is the size of each element in bytes
 * - 'storage'         is a pointer to the memory block used for storing elements
 */
typedef struct {
    size_t capacity;
    size_t count;
    size_t head;
    size_t tail;
    
    size_t elementSize;
    void* storage;
} ring_buffer_t;



/**
 * @brief Initializes a ring buffer.
 * 
 * @param buff Pointer to the ring buffer structure to be initialized
 * @param storage Pointer to the memory block used for storing elements
 * @param capacity The maximum number of elements the buffer can hold
 * @param elementSize The size of each element in bytes
 * 
 * @return return errors:
 *              0 - Success
 *              1 - Error: Invalid parameters
 *              2 - Error: Capacity must be a multiple of element size
 *              3 - Error: Buffer already initialized
 */
uint8_t rb_init(ring_buffer_t * buff, void* storage, size_t capacity, size_t elementSize); 



/**
 * @brief Pushes a new element into the ring buffer.
 *
 * @param buff Pointer to the ring buffer
 * @param data Pointer to the new element to be added
 * 
 * @return return errors:
 *              0 - Success
 *              1 - Error: Invalid parameters
 *              2 - Error: Buffer is full
 */
uint8_t rb_push(ring_buffer_t * buff, void * data);



/**
 * @brief Discards the oldest element in the ring buffer and adds the new *data element
 *
 * This is used to maintain the last N elements of a stream of data. 
 * 
 * @param buff Pointer to the ring buffer
 * @param data Pointer to the new element to be added
 * 
 * @return return errors:
 *              0 - Success
 *              1 - Error: Invalid parameters
 */
uint8_t rb_rotate(ring_buffer_t * buff, void * data);


/**
 * @brief Peeks at an index of the ring buffer without removing it.
 *
 * @param buff  Pointer to the ring buffer
 * @param index Index of the element to peek at (0 is the oldest element, count-1 or -1 is the newest)
 * @param[out] data  Pointer to the buffer where the element will be copied
 * 
 * @return return errors:
 *              0 - Success
 *              1 - Error: Invalid parameters
 */
uint8_t rb_at(ring_buffer_t * buff, size_t index, void * data);



/**
 * @brief Destructively retrieves the newest element from the ring buffer.
 * 
 * @param buff Pointer to the ring buffer
 * @param data Pointer to the buffer where the removed element will be copied
 * 
 * @return return errors:
 */
uint8_t rb_newest(ring_buffer_t * buff, void * data);



/**
 * @brief Destructively retrieves the oldest element from the ring buffer.
 * 
 * @param buff Pointer to the ring buffer
 * @param data Pointer to the buffer where the removed element will be copied
 * 
 * @return return errors:
 *              0 - Success
 *              1 - Error: Invalid parameters
 *              2 - Error: Buffer is empty
 */
uint8_t rb_oldest(ring_buffer_t * buff, void * data);