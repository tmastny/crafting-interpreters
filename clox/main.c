#include <stdio.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
  Chunk chunk;
  initChunk(&chunk);

  for (int i = 0; i < 100; i++) {
    int constant = addConstant(&chunk, i + 100);
    writeChunk(&chunk, OP_CONSTANT, i / 10);
    writeChunk(&chunk, constant, i / 10);
  }
  writeChunk(&chunk, OP_RETURN, 10);

  // // test line encoding
  printf("Chunk count: %i\n", chunk.count);
  printf("Chunks per line:\n");
  for (int i = 0; i < chunk.linecap; i++) {
    printf("line: %i, num: %i\n", i, chunk.lines[i]);
  }
  printf("-----\n");

  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
  return 0;
}
