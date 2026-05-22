#pragma once

#include <stdint.h>

typedef struct {
  uint64_t start;
  uint64_t end;
} RangeInclusive;

RangeInclusive range_new(const uint64_t start, const uint64_t end);

bool range_includes(const RangeInclusive *self, uint64_t value);
uint64_t range_count(const RangeInclusive *range);
void range_print(const RangeInclusive *self);

bool ranges_can_be_merged(const RangeInclusive *a, const RangeInclusive *b);
RangeInclusive ranges_merge(const RangeInclusive *a, const RangeInclusive *b);
int ranges_cmp(const void *a, const void *b);

#ifdef TEST
void range_inclusive_tests(void);
#endif
