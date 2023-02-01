#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

// the names no longer make sense, but I didn't want to change the API that much.
// `takeString` allocates ObjString to a certain length and returns the object,
// useful for concatenation when you want an empty allocated car array.
// `copyString` calls `takeString` and then fills in the char array.
ObjString* takeString(int length) {
  ObjString* string = (ObjString*)malloc(sizeof(ObjString) + sizeof(char) * (length + 1));
  string->obj.type = OBJ_STRING;
  string->obj.next = vm.objects;
  string->length = length;

  vm.objects = (Obj*)string;
  return string;
}

ObjString* copyString(const char* chars, int length) {
  ObjString* string = takeString(length);

  memcpy(string->chars, chars, length);
  string->chars[length] = '\0';

  return string;
}

void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
    case OBJ_STRING:
      printf("%s", AS_CSTRING(value));
      break;
  }
}
