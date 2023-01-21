#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"
#include "table.h"
#include "value.h"

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
  initVM();

  Table table;
  initTable(&table);
  Value d1 = NUMBER_VAL(1.1);
  Value d2 = NUMBER_VAL(1);
  Value t = BOOL_VAL(true);
  Value f = BOOL_VAL(false);
  Value n = NIV_VAL;

  tableSet(&table, valueKey(d1), NUMBER_VAL(1));
  tableSet(&table, valueKey(d2), NUMBER_VAL(2));
  tableSet(&table, valueKey(t), NUMBER_VAL(3));
  tableSet(&table, valueKey(f), NUMBER_VAL(4));
  tableSet(&table, valueKey(n), NUMBER_VAL(5));

  Value value;
  tableGet(&table, valueKey(d1), &value);
  printValue(value);
  printf("\n");
  tableGet(&table, valueKey(d2), &value);
  printValue(value);
  printf("\n");
  tableGet(&table, valueKey(t),  &value);
  printValue(value);
  printf("\n");
  tableGet(&table, valueKey(f),  &value);
  printValue(value);
  printf("\n");
  tableGet(&table, valueKey(n),  &value);
  printValue(value);
  printf("\n");




  if (argc == 1) {
    repl();
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    fprintf(stderr, "Uage: clox [path]\n");
    exit(64);
  }

  freeVM();
  return 0;
}
