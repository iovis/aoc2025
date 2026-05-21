#pragma once

#include "range_inclusive.h"
#include <stddef.h>
#include <stdint.h>

typedef struct {
  RangeInclusive *items;
  size_t len;
  size_t capacity;
} RangeVec;

bool range_vec_push(RangeVec *self, RangeInclusive value);
void range_vec_free(RangeVec *self);

#ifdef TEST
void vec_tests(void);
#endif
