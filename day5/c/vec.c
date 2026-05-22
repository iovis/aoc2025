#include "vec.h"
#include "range_inclusive.h"

#include <stdlib.h>

bool ranges_push(Ranges *self, RangeInclusive value) {
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

RangeInclusive *ranges_pop(Ranges *self) {
  if (self->len == 0) return nullptr;

  self->len--;
  return &self->items[self->len];
}

void ranges_free(Ranges *self) {
  free(self->items);
  *self = (Ranges){0};
}

#ifdef TEST
#include <assert.h>
#include <stddefer.h>

void vec_tests(void) {
  Ranges ranges = {0};
  defer ranges_free(&ranges);

  for (size_t i = 0; i < 20; i++) {
    assert(ranges_push(&ranges, range_new(i, 2 * i)));
  }

  assert(ranges.len == 20);
  assert(ranges.capacity == 32);
  assert(ranges.items[1].start == 1);
  assert(ranges.items[19].start == 19);

  auto range = ranges_pop(&ranges);
  assert(range->start == 19);
  assert(range->end == 38);
}
#endif
