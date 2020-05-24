#include <stdlib.h>

#include "memory.h"

void* reallocate(void* pointer, size_t oldsize, size_t newsize) {
    if (newsize == 0) {
        free(pointer);
        return NULL;
    }
    return realloc(pointer, newsize);
}