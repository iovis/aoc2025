#pragma once

#include "base.h"
#include <stdalign.h>

typedef struct {
  unsigned char *data;
  size_t capacity;
  size_t offset;
} Arena;

Arena arena_create(size_t capacity);
void arena_free(Arena *arena);
void arena_reset(Arena *arena);

size_t arena_capacity(const Arena *arena);
size_t arena_used(const Arena *arena);
size_t arena_remaining(const Arena *arena);

void *arena_alloc(Arena *arena, size_t size, size_t alignment);
void *arena_alloc_array(Arena *arena, size_t count, size_t item_size, size_t alignment);
void *arena_calloc(Arena *arena, size_t count, size_t item_size, size_t alignment);

#define arena_new(arena, Type) ((Type *)arena_alloc((arena), sizeof(Type), alignof(Type)))
#define arena_new_zeroed(arena, Type) ((Type *)arena_calloc((arena), 1, sizeof(Type), alignof(Type)))
#define arena_array(arena, Type, count) ((Type *)arena_alloc_array((arena), (count), sizeof(Type), alignof(Type)))
#define arena_carray(arena, Type, count) ((Type *)arena_calloc((arena), (count), sizeof(Type), alignof(Type)))

#ifdef TEST
void arena_tests(void);
#endif
