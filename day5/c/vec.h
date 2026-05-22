#pragma once

#include "range_inclusive.h"
#include <stddef.h>
#include <stdint.h>

typedef struct {
  RangeInclusive *items;
  size_t len;
  size_t capacity;
} Ranges;

bool ranges_push(Ranges *self, RangeInclusive value);
RangeInclusive *ranges_pop(Ranges *self);
void ranges_free(Ranges *self);

#ifdef TEST
void vec_tests(void);
#endif
