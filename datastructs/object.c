#include <string.h>
#include <stdio.h>

#include "object.h"
#include "../util.h"
#include "../services/memory.h"

Obj* objList = NULL;

#define allocate_obj(type, typeenum) \
    ((type*) allocateObj(typeenum, sizeof(type)))

Obj* allocateObj(ObjType type, size_t size) {
    Obj* obj = allocate_pointer(Obj, size);
    obj->type = type;
    obj->next = objList;
    obj->hash = hash_pointer(obj);
    objList = obj;
    return obj;
}

ObjString* copyString(char* chars, int length) {
    char* copied = allocate_block(char, length + 1);
    memcpy(copied, chars, length);
    copied[length] = '\0';
    return takeString(copied, length);
}

ObjString* takeString(char* chars, int length) {
    ObjString* string = allocate_obj(ObjString, OBJ_STRING);
    string->chars = chars;
    string->length = length;
    return string;
}

void freeObject(Obj* object) {
    switch (object->type) {                                 
        case OBJ_STRING: 
            {                                    
                ObjString* string = (ObjString*) object;             
                free_array(char, string->chars, string->length + 1);
                free_pointer(object, sizeof(ObjString));                            
                break;                                              
            }                                                     
    }
}

void freeObjList() {
    while (objList != NULL) {
        Obj* next = objList->next;
        freeObject(objList);
        objList = next;
    }    
}

void printObj(Obj* obj) {
    switch (obj->type) {
        case OBJ_STRING:
            printf("%s", ((ObjString*) obj)->chars);
            break;
    }
}
