#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

typedef struct {
  ObjType type;
  struct Obj2* next;
} Obj2;


static void repl() {
  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    interpret(line);
  }
}

static char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fileSize + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  if (bytesRead < fileSize) {
    fprintf(stderr, "Could not read file \"%s\n.\n", path);
    exit(74);
  }
  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

static void runFile(const char* path) {
  char* source = readFile(path);
  InterpretResult result = interpret(source);
  free(source);

  if (result == INTERPRET_COMPILE_ERROR) exit(65);
  if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main(int argc, const char* argv[]) {
  // initVM();

  printf("Obj total:     %d\n", sizeof(Obj));
  printf("    - ObjType: %d\n", sizeof(ObjType));
  printf("    - bool:    %d\n", sizeof(bool));
  printf("    - Obj*:    %d\n", sizeof(Obj*));
  printf("\n\n\n");

  // because of object padding, the extra field `isMarked`
  // doesn't change the total size.
  Obj2* obj2;
  printf("Obj2 total:    %d\n", sizeof(Obj2));
  printf("    - ObjType: %d\n", sizeof(ObjType));
  printf("    - Obj*:    %d\n", sizeof(Obj2*));
  printf("\n");

  // We can't allocate objects into an array (which would
  // save 8 bytes and have better cache locality), because we
  // we want constant time deletion of objects in the garbage
  // collector.

  return 0;

  if (argc == 1) {
    repl();
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    fprintf(stderr, "Usage: clox [path]\n");
    exit(64);
  }

  freeVM();
  return 0;
}
