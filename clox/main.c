#include <time.h>
#include <stdio.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);


  float start1 = (float)clock() / CLOCKS_PER_SEC;
  for (int i = 0; i < 100000; i++) {
    writeChunk(&chunk, OP_NEGATE_1, 123);
  }
  writeChunk(&chunk, OP_RETURN, 123);


  interpret(&chunk);
  float end1 = (float)clock() / CLOCKS_PER_SEC;
  printf("Time elapsed for pushpop: %f\n", end1 - start1);
  freeVM();
  freeChunk(&chunk);
  initVM();
  initChunk(&chunk);


  constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);


  float start2 = (float)clock() / CLOCKS_PER_SEC;
  // tried at 1, 10_000, and 100_000
  for (int i = 0; i < 100000; i++) {
    writeChunk(&chunk, OP_NEGATE_2, 123);
  }
  writeChunk(&chunk, OP_RETURN, 123);

  interpret(&chunk);
  float end2 = (float)clock() / CLOCKS_PER_SEC;
  printf("Time elapsed for inplace: %f\n", end2 - start2);




  freeVM();
  freeChunk(&chunk);
  return 0;
}
