/**
 * @file ringBuffer.c
 * @brief Ring buffer implementation in C.
 * @author ERS
 *
 * This implementation provides a framework for a ring buffer in C. It allows for the storage and retrieval of elements in a circular manner, making it suitable for scenarios where a fixed-size buffer is needed.
 * There are two main functions for adding elements to the buffer: rb_push and rb_rotate. The rb_push function adds a new element to the buffer and will fail when the buffer is full, while the rb_rotate function
 * discards the oldest element when the buffer is full ensuring that the buffer always contains the most recent elements.
 */

 /** =======================================================================
 *  Routine Defines
 *  =======================================================================
 */
#include <stdint.h>
#include <string.h>
#include "ringBuffer.h"



#ifdef __cplusplus
    extern "C" 
        {
#endif
/** =======================================================================
 *  Public API
 *  =======================================================================
 * see ringBuffer.h for more details.
 */
uint8_t rb_init(ring_buffer_t * buff, void* storage, uint32_t capacity, uint32_t elementSize)
{
    if (buff == NULL || storage == NULL || capacity == 0 || elementSize == 0)
    {
        return 1; // Error: Invalid parameters
    }
    if (buff->storage != NULL)
    {
        return 3; // Error: Buffer already initialized
    }
    

    buff->capacity = capacity;
    buff->storage = storage;
    buff->elementSize = elementSize;
    buff->head = 0;
    buff->tail = 0;
    buff->count = 0;
    return 0;
}



uint8_t rb_push(ring_buffer_t * buff, void * data)
{
    if (buff == NULL || data == NULL)
    {
        return 1; // Error: Invalid parameters
    }
    if (buff->count >= buff->capacity)
    {
        return 2; // Error: Buffer is full
    }
    if (buff->storage == NULL)
    {
        return 3; // Error: Buffer not initialized
    }


    // Find the index of new element which is the tail index, if the index is greater than capacity,
    // wrap around to the beginning of the buffer. This I believe, is faster than using the modulus opertator, 
    // escpecially in non optimised situations when the capacity is not a power of 2.
    uint32_t index = buff->tail;
    if (index >= buff->capacity)
    {
        index = 0;
    }

    uint8_t * ret = memcpy((uint8_t*)buff->storage + (index * buff->elementSize), data, buff->elementSize);

    if (ret != (uint8_t*)buff->storage + (index * buff->elementSize))
    {
        return 4; // Error: Memory copy failed
    }
    buff->tail = index+1;
    buff->count++;
    return 0; // Success
}



uint8_t rb_rotate(ring_buffer_t * buff, void * data)
{

    if (buff == NULL || data == NULL)
    {
        return 1; // Error: Invalid parameters
    }
    if (buff->storage == NULL)
    {
        return 3; // Error: Buffer not initialized
    }


    // In the situation where the buffer is not full, the element can be added identically to the push implementation.
    if (buff->count < buff->capacity)
    {
        return rb_push(buff, data);
    }


    // In the situation where the buffer is full, the oldest element (head) is discarded and the new element is added at the tail.
    // There is probably a good way to write the two situations in a single function but I know the rb_push should work for its use.
    
    if (buff->count == buff->capacity)
    {
        uint32_t index = buff->head;
        if (index >= buff->capacity)
        {
            index = 0;
        }
        uint8_t * ret = memcpy((uint8_t*)buff->storage + (index * buff->elementSize), data, buff->elementSize);
        if (ret != (uint8_t*)buff->storage + (index * buff->elementSize))
        {
            return 4; // Error: Memory copy failed
        }
        buff->head = index + 1;
        buff->tail = index;
        return 0; // Success
    }


    return 5; // Error: Unknown error
}



uint8_t rb_at(ring_buffer_t * buff, int32_t index, void * data)
{
    if (buff == NULL || data == NULL)
    {
        return 1; // Error: Invalid parameters
    }
    if (buff->count == 0)
    {
        return 2; // Error: Buffer is empty
    }
    // If the index is negative, convert it to a positive index where -1 is the newest element.
    if (index < 0)
    {
        index = (int32_t)buff->count + index;
    }

    if (index < 0 || (uint32_t)index >= buff->count)
    {
        return 3; // Error: Index out of bounds
    }

    // Calculate the actual index in the storage array
    uint32_t actualIndex = (buff->head + (uint32_t)index);
    if (actualIndex >= buff->capacity)
    {
        actualIndex -= buff->capacity;
    }

    uint8_t * ret = memcpy(data, (uint8_t*)buff->storage + (actualIndex * buff->elementSize), buff->elementSize);
    if (ret != data)
    {
        return 4; // Error: Memory copy failed
    }
    return 0; // Success

}



uint8_t rb_newest(ring_buffer_t * buff, void * data)
{
    if (buff == NULL || data == NULL)
    {
        return 1; // Error: Invalid parameters
    }
    if (buff->count == 0)
    {
        return 2; // Error: Buffer is empty
    }

    uint32_t index = buff->tail;
    if (index == 0)
    {
        index = buff->capacity - 1;
    }
    else
    {
        index--;
    }

    uint8_t * ret = memcpy(data, (uint8_t*)buff->storage + (index * buff->elementSize), buff->elementSize);
    if (ret != data)
    {
        return 4; // Error: Memory copy failed
    }

    buff->tail = index;
    buff->count--;
    return 0; // Success

}

uint8_t rb_oldest(ring_buffer_t * buff, void * data)
{
    if (buff == NULL || data == NULL)
    {
        return 1; // Error: Invalid parameters
    }
    if (buff->count == 0)
    {
        return 2; // Error: Buffer is empty
    }

    uint32_t index = buff->head;
    uint8_t * ret = memcpy(data, (uint8_t*)buff->storage + (index * buff->elementSize), buff->elementSize);
    if (ret != data)
    {
        return 4; // Error: Memory copy failed
    }

    // Update the head index to point to the next oldest element
    buff->head++;
    if (buff->head >= buff->capacity)
    {
        buff->head = 0;
    }
    buff->count--;
    return 0; // Success

}

int32_t rb_count(ring_buffer_t * buff)
{
    if (buff == NULL)
    {
        return -1; // Error: Invalid parameters
    }
    return (int32_t)buff->count;
}


#ifdef __cplusplus
    }
#endif