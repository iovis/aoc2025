#include "range_inclusive.h"

#include <stdio.h>

RangeInclusive range_new(const uint64_t start, const uint64_t end) {
  return (RangeInclusive){.start = start, .end = end};
}

bool range_includes(const RangeInclusive *self, uint64_t value) {
  return self->start <= value && self->end >= value;
}

void range_print(const RangeInclusive *self) {
  printf("RangeInclusive { start = %lu, end = %lu }\n", self->start, self->end);
}

#ifdef TEST
#include <assert.h>

void range_inclusive_tests(void) {
  RangeInclusive range = range_new(1, 10);
  assert(range.start == 1);
  assert(range.end == 10);

  assert(range_includes(&range, 1) == true);
  assert(range_includes(&range, 5) == true);
  assert(range_includes(&range, 10) == true);
  assert(range_includes(&range, 15) == false);
}
#endif
