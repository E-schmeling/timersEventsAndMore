#include <stdint.h> 

#include "ringBuffer.h"

uint8_t rb_init(ring_buffer_t * buff, void* storage, size_t capacity, size_t elementSize)
{
    if (buff == NULL || storage == NULL || capacity == 0 || elementSize == 0)
    {
        return 1; // Error: Invalid parameters
    }
    if (capacity % elementSize != 0)
    {
        return 2; // Error: Capacity must be a multiple of element size
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

