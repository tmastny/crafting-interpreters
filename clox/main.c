#include <stdio.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  printf("(1.2 + 3.4) / 5.6\n");
  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  constant = addConstant(&chunk, 3.4);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_ADD, 123);

  constant = addConstant(&chunk, 5.6);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_DIVIDE, 123);
  writeChunk(&chunk, OP_NEGATE, 123);

  writeChunk(&chunk, OP_RETURN, 123);
  interpret(&chunk);
  freeChunk(&chunk);
  initChunk(&chunk);

  // #2
  freeChunk(&chunk);
  initChunk(&chunk);

  printf("1 * 2 + 3\n");
  constant = addConstant(&chunk, 1);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  constant = addConstant(&chunk, 2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_MULTIPLY, 123);

  constant = addConstant(&chunk, 3);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_MULTIPLY, 123);
  writeChunk(&chunk, OP_RETURN, 123);
  interpret(&chunk);
  freeChunk(&chunk);
  initChunk(&chunk);

  // #3
  printf("1 + 2 * 3\n");
  constant = addConstant(&chunk, 1);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  constant = addConstant(&chunk, 2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  constant = addConstant(&chunk, 3);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_MULTIPLY, 123);
  writeChunk(&chunk, OP_ADD, 123);

  writeChunk(&chunk, OP_RETURN, 123);
  interpret(&chunk);
  freeChunk(&chunk);
  initChunk(&chunk);

  // #4
  printf("3 - 2 - 1\n");
  constant = addConstant(&chunk, 3);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  constant = addConstant(&chunk, 2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_SUBTRACT, 123);

  constant = addConstant(&chunk, 1);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_SUBTRACT, 123);
  writeChunk(&chunk, OP_RETURN, 123);
  interpret(&chunk);
  freeChunk(&chunk);
  initChunk(&chunk);

  // #5
  printf("1 + 2 * 3 - 4 / -5\n");
  constant = addConstant(&chunk, 1);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  constant = addConstant(&chunk, 2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  constant = addConstant(&chunk, 3);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_MULTIPLY, 123);
  writeChunk(&chunk, OP_ADD, 123);

  constant = addConstant(&chunk, 4);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  constant = addConstant(&chunk, 5);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_NEGATE, 123);
  writeChunk(&chunk, OP_DIVIDE, 123);
  writeChunk(&chunk, OP_SUBTRACT, 123);
  writeChunk(&chunk, OP_RETURN, 123);
  interpret(&chunk);
  freeChunk(&chunk);
  initChunk(&chunk);


  freeVM();
  freeChunk(&chunk);
  return 0;
}
