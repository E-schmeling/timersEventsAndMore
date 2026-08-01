#include <stddef.h>



typedef struct {
    size_t capacity;
    size_t count;
    size_t head;
    size_t tail;

    size_t elementSize;
    void* storage;
} ring_buffer_t;

