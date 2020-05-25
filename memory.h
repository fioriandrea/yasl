#ifndef memory_h
#define memory_h

#include <stdlib.h>

#include "./commontypes.h"
#include "./datastructs/value.h"
#include "./datastructs/hash_map.h"

struct sCollector {
    HashMap* interned;
    Obj* objects;
    size_t allocated;
};

#define compute_capacity(oldcap) \
    ((oldcap) < 8 ? 8 : (oldcap) * 2)

#define grow_array(collector, type, array, oldcap, newcap) \
    ((type*) reallocate(collector, array, (oldcap) * sizeof(type), (newcap) * sizeof(type)))

#define free_array(collector, type, array, oldcap) \
    reallocate(collector, array, (oldcap) * sizeof(type), 0)

#define allocate_block(collector, type, ncells) \
    ((type*) reallocate(collector, NULL, 0, sizeof(type) * (ncells)))

#define free_block(collector, type, block, ncells) \
    reallocate(collector, block, sizeof(type) * ncells, 0)

#define allocate_pointer(collector, type, size) \
    ((type*) reallocate(collector, NULL, 0, size))

#define free_pointer(collector, pointer, size) \
    reallocate(collector, pointer, size, 0) 

void* reallocate(struct sCollector* collector, void* pointer, size_t oldsize, size_t newsize); 
void initCollector(struct sCollector* collector, HashMap* map); 
void freeCollector(struct sCollector* collector); 

#endif
