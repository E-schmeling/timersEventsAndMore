#include <stdio.h>
#include <stdint.h>

#include "ringBuffer.h"


uint8_t printRingBufferData(ring_buffer_t * buff);


uint8_t storage[8];
ring_buffer_t buffer;



int main()
{
    printf("Hello wolrd\n");
    uint8_t ret = rb_init(&buffer, storage, sizeof(storage) / sizeof(storage[0]), sizeof(storage[0]));

    if (ret != 0)
    {
        printf("Error initializing ring buffer: %d\n", ret);
        return 1;
    }
    printf("Ring buffer initialized successfully.\n");

    uint8_t dataToPush = 42;
    
    ret = rb_rotate(&buffer, &dataToPush);
    dataToPush++;
    ret = rb_rotate(&buffer, &dataToPush);
    dataToPush++;
    ret = rb_rotate(&buffer, &dataToPush);
    dataToPush++;
    ret = rb_rotate(&buffer, &dataToPush);
    dataToPush++;
    ret = rb_rotate(&buffer, &dataToPush);
    dataToPush++;
    ret = rb_rotate(&buffer, &dataToPush);

    if (ret != 0)
    {
        printf("Error pushing data to ring buffer: %d\n", ret);
        return 1;
    }
    printRingBufferData(&buffer);
    
    return 0; 
}




uint8_t printRingBufferData(ring_buffer_t * buff)
{
    if (buff == NULL || buff->storage == NULL)
    {
        return 1; // Error: Invalid parameters
    }

    printf("Ring Buffer Data:\n");
    for (uint32_t i = 0; i < buff->count; i++)
    {
        uint32_t index = (buff->head + i) % buff->capacity;
        uint8_t * element = (uint8_t*)buff->storage + (index * buff->elementSize);
        printf("Element %u: %d\n", i, *element);
    }
    return 0; // Success
}