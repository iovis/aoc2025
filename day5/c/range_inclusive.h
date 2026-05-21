#pragma once

#include <stdint.h>

typedef struct {
  uint64_t start;
  uint64_t end;
} RangeInclusive;

RangeInclusive range_new(const uint64_t start, const uint64_t end);
bool range_includes(const RangeInclusive *self, uint64_t value);
void range_print(const RangeInclusive *self);

#ifdef TEST
void range_inclusive_tests(void);
#endif
