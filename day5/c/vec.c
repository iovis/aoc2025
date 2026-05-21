#include "vec.h"
#include "range_inclusive.h"

#include <stdlib.h>

bool range_vec_push(RangeVec *self, RangeInclusive value) {
  if (self->len >= self->capacity) {
    size_t new_capacity = (self->capacity == 0) ? 16 : 2 * self->capacity;
    auto new_items = realloc(self->items, new_capacity * sizeof(*self->items));
    if (!new_items) return false;
    self->items = new_items;
    self->capacity = new_capacity;
  }

  self->items[self->len] = value;
  self->len++;

  return true;
}

void range_vec_free(RangeVec *self) {
  free(self->items);
  *self = (RangeVec){0};
}

#ifdef TEST
#include <assert.h>
#include <stddefer.h>

void vec_tests(void) {
  RangeVec ranges = {0};
  defer range_vec_free(&ranges);

  for (size_t i = 0; i < 20; i++) {
    assert(range_vec_push(&ranges, range_new(i, 2 * i)));
  }

  assert(ranges.len == 20);
  assert(ranges.capacity == 32);
  assert(ranges.items[1].start == 1);
  assert(ranges.items[19].start == 19);
}
#endif
