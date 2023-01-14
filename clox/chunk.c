#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;
  chunk->lines[chunk->count] = line;
  chunk->count++;
}

void writeConstant(Chunk* chunk, Value value, int line) {
  int constant = addConstant(chunk, value);

  if (constant < 256) {
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, constant, line);
    return;
  }

  writeChunk(chunk, OP_CONSTANT_LONG, line);

  int mask = 0xff0000;
  uint8_t byte;
  for (int i = 0; i <= 16; i += 8) {
    byte = (constant & (mask >> i)) >> (16 - i);
    writeChunk(chunk, byte, line);
  }
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}


void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}
