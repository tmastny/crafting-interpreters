#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"
#include "table.h"
#include "object.h"

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

static void printStats(float* time, int n) {
  float mean = 0, var = 0;
  for (int i = 0; i < n; i++) {
    mean += time[i];
  }

  mean /= n;

  for (int i = 0; i < n; i++) {
    var += pow(time[i] - mean, 2);
  }

  var /= (n - 1);
  printf("         - mean: %f\n", mean);
  printf("         - var:  %f\n", var);
}

static void benchmark(const char* path, char* by) {
  Table table;
  initTable(&table);

  int n = 0;
  float time[120000];
  ObjString* strings[120000];
  float start, end;

  char* input = readFile(path);
  char* token;
  while ((token = strsep(&input, by)) != NULL) {
    ObjString* string = copyString(token, strlen(token));
    strings[n] = string;

    start = (float)clock()/CLOCKS_PER_SEC;
    tableSet(&table, string, NIV_VAL);
    end = (float)clock()/CLOCKS_PER_SEC;

    time[n++] = end - start;
  }

  printf("bench: tableSet\n");
  printStats(time, n);

  Value value;
  for (int i = 0; i < n; i++) {

    start = (float)clock()/CLOCKS_PER_SEC;
    //strings[i]->hash;
    if (!tableGet(&table, strings[i], &value)) {
      printf("%s\n", strings[i]->chars);
      return;
    }
    end = (float)clock()/CLOCKS_PER_SEC;

    time[i] = end - start;
  }

  printf("bench: tableGet\n");
  printStats(time, n);
}

int main(int argc, const char* argv[]) {
  initVM();

  if (argc == 1) {
    repl();
  } else if (argc == 2) {
    runFile(argv[1]);
  } else if (argc == 4 && memcmp(argv[1], "bench", 5) == 0) {
    char by = ' ';
    if (memcmp(argv[2], "token", 5) == 0) {
      by = ' ';
    } else if (memcmp(argv[3], "token", 5) == 0) {
      by = '\n';
    }

    benchmark(argv[3], &by);
  } else {
    fprintf(stderr, "Usage: clox [path]\n");
    exit(64);
  }

  freeVM();
  return 0;
}
