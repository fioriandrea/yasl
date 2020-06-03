#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "./debug/debug_switches.h"

static void collectGarbage(struct sCollector* collector) {
#ifdef TRACE_GC
    printf("START GC\n");
#endif

    // mark safeValue
    if (collector->safeObj != NULL)
        markObject(collector, collector->safeObj);

    // mark stack
    for (Value* stackValue = collector->vm->stack; stackValue < collector->vm->sp; stackValue++) {
        markValue(collector, *stackValue);
    }

    // mark globals

    markMap(collector, &collector->vm->globals);

    // todo: mark frames (mark main script function)
    
    // mark open upvalues

    for (ObjUpvalue* upvalue = collector->vm->openUpvalues; upvalue != NULL; upvalue = upvalue->next) {
        markObject(collector, (Obj*) upvalue);
    }

    // blacken
    
    for (int i = 0; i < collector->worklistCount; i++) {
        blackenObject(collector, collector->worklist[i]);
    }
    collector->worklistCount = 0;

    // sweep

    /*Obj* prev = NULL;
      Obj* current = collector->objects;
      while (current != NULL) {
      if (!current->marked) {
      Obj* toFree = current;
      if (prev != NULL) {
      prev->next = current->next;
      }
      prev = current;
      current = current->next;
      freeObject(NULL, toFree);
      } else {
      current->marked = 0;
      prev = current;
      current = current->next;
      }
      }*/
    Obj* previous = NULL;         
    Obj* object = collector->objects;     
    while (object != NULL) {      
        if (object->marked) {     
            object->marked = 0;
            previous = object;        
            object = object->next;    
        } else {                    
            Obj* unreached = object;

            object = object->next;    
            if (previous != NULL) {   
                previous->next = object;
            } else {                  
                collector->objects = object;    
            }                         

            freeObject(NULL, unreached);    
        }                           
    }           
#ifdef TRACE_GC
    printf("END GC\n");
#endif 
}

void* reallocate(Collector* collector, void* pointer, size_t oldsize, size_t newsize) {
    if (collector != NULL && collector->vm != NULL && oldsize < newsize) {
#ifdef STRESS_GC
        collectGarbage(collector);
#endif
    }
    if (newsize == 0) {
        free(pointer);
        return NULL;
    }
    return realloc(pointer, newsize);
}

void initCollector(Collector* collector) {
    collector->allocated = 0;
    collector->objects = NULL;
    collector->vm = NULL;
    collector->worklist = NULL;
    collector->worklistCount = 0;
    collector->worklistCapacity = 0;
    collector->safeObj = NULL;
    initMap(&collector->interned);
}

void freeCollector(Collector* collector) {
    // todo: be sure that map is garbage collected
    freeMap(NULL, &collector->interned);
    while (collector->objects != NULL) {
        Obj* next = collector->objects->next;
        freeObject(NULL, collector->objects);
        collector->objects = next;
    }
    if (collector->worklist != NULL)
        free(collector->worklist);
}
