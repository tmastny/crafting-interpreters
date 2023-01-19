#include <stdlib.h>

#include "object.h"
#include "memory.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  void* result = realloc(pointer, newSize);
  if (result == NULL) exit(1);
  return result;
}

void freeObjects() {
  Obj* object;
  Obj* next = vm.objects;
  if (next == NULL) return;

  do {
    object = next;
    next = object->next;

    ObjString* string = (ObjString*)object;
    free(string->chars);
    free(string);

  } while (next != NULL);
}
