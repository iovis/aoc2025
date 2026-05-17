#include "arena.h"

#include <stdbool.h>
#include <string.h>

static bool arena_is_live(const Arena *arena) {
  return arena && arena->data && arena->offset <= arena->capacity;
}

static bool is_power_of_two(size_t value) {
  return value != 0 && (value & (value - 1)) == 0;
}

static bool align_up_size(size_t value, size_t alignment, size_t *out) {
  if (!is_power_of_two(alignment)) return false;

  size_t mask = alignment - 1;
  if (value > SIZE_MAX - mask) return false;

  *out = (value + mask) & ~mask;
  return true;
}

Arena arena_create(size_t capacity) {
  if (capacity == 0) return (Arena){0};

  unsigned char *data = malloc(capacity);
  if (!data) return (Arena){0};

  return (Arena){
      .data = data,
      .capacity = capacity,
      .offset = 0,
  };
}

void arena_free(Arena *arena) {
  if (!arena) return;

  free(arena->data);
  *arena = (Arena){0};
}

void arena_reset(Arena *arena) {
  if (!arena_is_live(arena)) return;

  arena->offset = 0;
}

size_t arena_capacity(const Arena *arena) {
  if (!arena_is_live(arena)) return 0;

  return arena->capacity;
}

size_t arena_used(const Arena *arena) {
  if (!arena_is_live(arena)) return 0;

  return arena->offset;
}

size_t arena_remaining(const Arena *arena) {
  if (!arena_is_live(arena)) return 0;

  return arena->capacity - arena->offset;
}

void *arena_alloc(Arena *arena, size_t size, size_t alignment) {
  if (!arena_is_live(arena)) return nullptr;
  if (size == 0) return nullptr;
  if (!is_power_of_two(alignment)) return nullptr;
  if (alignment > alignof(max_align_t)) return nullptr;

  size_t start = 0;
  if (!align_up_size(arena->offset, alignment, &start)) return nullptr;
  if (start > arena->capacity || size > arena->capacity - start) return nullptr;

  void *ptr = &arena->data[start];
  arena->offset = start + size;
  return ptr;
}

void *arena_alloc_array(Arena *arena, size_t count, size_t item_size, size_t alignment) {
  if (count == 0 || item_size == 0) return nullptr;
  if (item_size > SIZE_MAX / count) return nullptr;

  return arena_alloc(arena, count * item_size, alignment);
}

void *arena_calloc(Arena *arena, size_t count, size_t item_size, size_t alignment) {
  void *ptr = arena_alloc_array(arena, count, item_size, alignment);
  if (!ptr) return nullptr;

  memset(ptr, 0, count * item_size);
  return ptr;
}

#ifdef TEST
static void arena_create_test(void) {
  Arena arena = arena_create(128);
  defer arena_free(&arena);

  assert(arena.data);
  assert(arena_capacity(&arena) == 128);
  assert(arena_used(&arena) == 0);
  assert(arena_remaining(&arena) == 128);
}

static void arena_create_zero_capacity_test(void) {
  Arena arena = arena_create(0);
  defer arena_free(&arena);

  assert(arena.data == nullptr);
  assert(arena_capacity(&arena) == 0);
  assert(arena_used(&arena) == 0);
  assert(arena_remaining(&arena) == 0);
}

static void arena_alloc_test(void) {
  Arena arena = arena_create(128);
  defer arena_free(&arena);

  int *number = arena_new(&arena, int);
  double *fraction = arena_new(&arena, double);

  assert(number);
  assert(fraction);

  *number = 42;
  *fraction = 3.5;

  assert(*number == 42);
  assert(*fraction == 3.5);
  assert(arena_used(&arena) <= arena_capacity(&arena));
}

static void arena_alignment_test(void) {
  Arena arena = arena_create(128);
  defer arena_free(&arena);

  char *byte = arena_new(&arena, char);
  uint64_t *number = arena_new(&arena, uint64_t);
  double *fraction = arena_new(&arena, double);

  assert(byte);
  assert(number);
  assert(fraction);
  assert((uintptr_t)byte % alignof(char) == 0);
  assert((uintptr_t)number % alignof(uint64_t) == 0);
  assert((uintptr_t)fraction % alignof(double) == 0);
}

static void arena_reset_test(void) {
  Arena arena = arena_create(128);
  defer arena_free(&arena);

  int *first = arena_array(&arena, int, 4);
  assert(first);
  assert(arena_used(&arena) > 0);

  arena_reset(&arena);

  assert(arena_used(&arena) == 0);

  int *second = arena_array(&arena, int, 4);
  assert(second);
  assert(second == first);
}

static void arena_calloc_test(void) {
  Arena arena = arena_create(128);
  defer arena_free(&arena);

  int *items = arena_carray(&arena, int, 4);

  assert(items);

  for (size_t i = 0; i < 4; i++) {
    assert(items[i] == 0);
  }
}

static void arena_oom_returns_null_test(void) {
  Arena arena = arena_create(8);
  defer arena_free(&arena);

  void *ptr = arena_alloc(&arena, 9, alignof(char));

  assert(ptr == nullptr);
  assert(arena_used(&arena) == 0);
}

static void arena_invalid_request_returns_null_test(void) {
  Arena arena = arena_create(128);
  defer arena_free(&arena);

  assert(arena_alloc(&arena, 0, alignof(char)) == nullptr);
  assert(arena_alloc(&arena, sizeof(int), 3) == nullptr);
  assert(arena_alloc_array(&arena, SIZE_MAX, 2, alignof(char)) == nullptr);
  assert(arena_alloc(nullptr, sizeof(int), alignof(int)) == nullptr);
  assert(arena_used(&arena) == 0);
}

static void arena_alloc_after_free_returns_null_test(void) {
  Arena arena = arena_create(128);
  arena_free(&arena);

  assert(arena_alloc(&arena, sizeof(int), alignof(int)) == nullptr);
  assert(arena_capacity(&arena) == 0);
}

void arena_tests(void) {
  arena_create_test();
  arena_create_zero_capacity_test();
  arena_alloc_test();
  arena_alignment_test();
  arena_reset_test();
  arena_calloc_test();
  arena_oom_returns_null_test();
  arena_invalid_request_returns_null_test();
  arena_alloc_after_free_returns_null_test();
}
#endif
