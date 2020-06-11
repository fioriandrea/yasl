#ifndef value_operations
#define value_operations

#include "value.h"

void indexGetObject(Collector* collector, Obj* array, Value* index, Value* result);
void indexSetObject(Collector* collector, Obj* array, Value* index, Value* value, Value* result);
ObjString* concatenateCharArrays(Collector* collector, char* first, ...);
ObjString* concatenateArraysToString(Collector* collector, ObjString* str, ...);
ObjString* vconcatenateMultipleStrings(Collector* collector, ObjString* first, va_list rest);
ObjString* concatenateStringAndCharArray(Collector* collector, ObjString* str, char* carr);
ObjString* vconcatenateCharArrays(Collector* collector, char* first, va_list rest);
ObjString* objectToString(Collector* collector, Obj* obj);
Obj* concatenateObjects(Collector* collector, Obj* a, Obj* b);
void arrayPush(Collector* collector, ObjArray* array, Value* value);
int dictPut(Collector* collector, ObjDict* dict, Value* key, Value* value);
int dictGet(ObjDict* dict, Value* key, Value* result);


Value indexGetValue(Collector* collector, Value arrayLike, Value index);
Value indexSetValue(Collector* collector, Value arrayLike, Value index, Value value);
ObjString* valueToString(Collector* collector, Value value);
char* valueToCharArray(Collector* collector, Value value);
void printValue(Collector* collector, Value val);
int isTruthy(Value val); 
int valueInteger(Value value);
int valuesIntegers(Value a, Value b); 
int valuesEqual(Value a, Value b); 
int valuesConcatenable(Value a, Value b); 
int valuesNumbers(Value a, Value b); 
Value concatenate(Collector* collector, Value a, Value b); 

#endif