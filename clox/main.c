#include <stdio.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  // #1
  printf("#1: 4 - 3 * 2\n - without using OP_NEGATE\n");

  int constant = addConstant(&chunk, 4);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  constant = addConstant(&chunk, 3);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  constant = addConstant(&chunk, 0);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  constant = addConstant(&chunk, 2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_SUBTRACT, 123);
  writeChunk(&chunk, OP_MULTIPLY, 123);
  writeChunk(&chunk, OP_SUBTRACT, 123);
  writeChunk(&chunk, OP_RETURN, 123);
  interpret(&chunk);
  freeChunk(&chunk);
  initChunk(&chunk);

    // #2
  printf("#2: 4 - 3 * 2\n - without using OP_SUBTRACT\n");

  constant = addConstant(&chunk, 4);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  constant = addConstant(&chunk, 3);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_NEGATE, 123);

  constant = addConstant(&chunk, 2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_NEGATE, 123);

  writeChunk(&chunk, OP_MULTIPLY, 123);
  writeChunk(&chunk, OP_ADD, 123);
  writeChunk(&chunk, OP_RETURN, 123);
  interpret(&chunk);
  freeChunk(&chunk);

  freeVM();
  return 0;
}
