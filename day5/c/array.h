#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// ({ ... }) is a GNU statement expression (gcc, clang) and the last line behaves like a `return`
#define arr_push(arr, value)                                                                                           \
  ({                                                                                                                   \
    auto arr__ptr = (arr);                                                                                             \
    auto arr__value = (value);                                                                                         \
    bool arr__result = true;                                                                                           \
                                                                                                                       \
    if (arr__ptr->len >= arr__ptr->capacity) {                                                                         \
      size_t arr__capacity = (arr__ptr->capacity == 0) ? 16 : 2 * arr__ptr->capacity;                                  \
      auto arr__items = realloc(arr__ptr->items, arr__capacity * sizeof(*arr__ptr->items));                            \
                                                                                                                       \
      if (arr__items) {                                                                                                \
        arr__ptr->items = arr__items;                                                                                  \
        arr__ptr->capacity = arr__capacity;                                                                            \
      } else {                                                                                                         \
        arr__result = false;                                                                                           \
      }                                                                                                                \
    }                                                                                                                  \
                                                                                                                       \
    if (arr__result) {                                                                                                 \
      arr__ptr->items[arr__ptr->len] = arr__value;                                                                     \
      arr__ptr->len++;                                                                                                 \
    }                                                                                                                  \
                                                                                                                       \
    arr__result;                                                                                                       \
  })

#define arr_pop(arr)                                                                                                   \
  ({                                                                                                                   \
    auto arr__ptr = (arr);                                                                                             \
    (arr__ptr->len == 0) ? nullptr : &arr__ptr->items[--arr__ptr->len];                                                \
  })

#define arr_free(arr)                                                                                                  \
  do {                                                                                                                 \
    auto arr__ptr = (arr);                                                                                             \
    free(arr__ptr->items);                                                                                             \
    *arr__ptr = (typeof(*arr__ptr)){0};                                                                                \
  } while (0)

#ifdef TEST
#include <assert.h>

typedef struct {
  int *items;
  size_t len;
  size_t capacity;
} ArrayTest;

static inline void array_tests(void) {
  ArrayTest array = {0};

  for (int i = 0; i < 20; i++) {
    assert(arr_push(&array, i));
  }

  assert(array.len == 20);
  assert(array.capacity == 32);
  assert(array.items[1] == 1);
  assert(array.items[19] == 19);

  int *item = arr_pop(&array);
  assert(array.len == 19);
  assert(*item == 19);

  ArrayTest empty = {0};
  assert(empty.len == 0);
  assert(arr_pop(&empty) == nullptr);

  arr_free(&array);
  assert(array.items == nullptr);
  assert(array.len == 0);
  assert(array.capacity == 0);
}
#endif
