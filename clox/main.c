#include <stdio.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
  Chunk chunk;
  initChunk(&chunk);

  // test 1
  // int constant = addConstant(&chunk, 1.2);
  // writeChunk(&chunk, OP_CONSTANT, 123);
  // writeChunk(&chunk, constant, 123);

  // writeChunk(&chunk, OP_RETURN, 123);

  // disassembleChunk(&chunk, "test chunk");
  // freeChunk(&chunk);

  for (int i = 0; i < 300; i++) {
    if (i == 256) {
      printf("debug here\n");
    }

    writeConstant(&chunk, i + 1000, 23);
  }

  disassembleChunk(&chunk, "test 2 chunk");
  freeChunk(&chunk);

  return 0;
}
