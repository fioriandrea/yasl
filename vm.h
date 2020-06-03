#ifndef vm_h
#define vm_h

#include "./datastructs/chunk.h"
#include "./commontypes.h"
#include "./datastructs/value.h"
#include "./datastructs/hash_map.h"

#define MAX_FRAMES 256                       
#define MAX_STACK (MAX_FRAMES * UINT8_MAX)

typedef struct {
    ObjClosure* closure;
    uint8_t* pc;
    Value* localStack;
} CallFrame;

typedef struct {
    CallFrame frames[MAX_FRAMES];
    int fp;
    Value stack[MAX_STACK];
    Value* sp;
    Collector* collector;
    HashMap globals;
    ObjUpvalue* openUpvalues;
} VM;

void initVM(VM* vm);
int vmExecute(VM* vm, Collector* collector, ObjFunction* function);  
void freeVM(VM* vm);

#endif
