#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType)

static Obj* allocateObject(size_t size, ObjType type) {
  Obj* object = (Obj*)reallocate(NULL, 0, size);
  object->type = type;
  object->next = vm.objects;
  vm.objects = object;

  return object;
}

static ObjString* allocateString(char* chars, int length, bool freeable) {
  ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
  string->length = length;
  string->chars = chars;
  string->freeable = freeable;
  return string;
}

// no longer a good name. Now should be named freeableString
ObjString* takeString(char* chars, int length) {
  return allocateString(chars, length, true);
}

// no longer a good name. Now should be named constantString
ObjString* copyString(const char* chars, int length) {
  // this is a little tricky, because now it is not a null-terminated string.
  return allocateString(chars, length, false);
}

void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
    case OBJ_STRING:
      printf("%.*s", AS_STRING(value)->length, AS_CSTRING(value));
      break;
  }
}
