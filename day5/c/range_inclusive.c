#include "range_inclusive.h"
#include "base.h"

#include <stdio.h>

RangeInclusive range_new(const uint64_t start, const uint64_t end) {
  expect(start <= end);
  return (RangeInclusive){.start = start, .end = end};
}

bool range_includes(const RangeInclusive *self, uint64_t value) {
  return self->start <= value && self->end >= value;
}

uint64_t range_count(const RangeInclusive *range) {
  return range->end - range->start + 1;
}

void range_print(const RangeInclusive *self) {
  printf("RangeInclusive { start = %lu, end = %lu }\n", self->start, self->end);
}

bool ranges_can_be_merged(const RangeInclusive *a, const RangeInclusive *b) {
  return range_includes(a, b->start) || range_includes(a, b->end) || range_includes(b, a->start)
         || range_includes(b, a->end);
}

RangeInclusive ranges_merge(const RangeInclusive *a, const RangeInclusive *b) {
  uint64_t start = (a->start < b->start) ? a->start : b->start;
  uint64_t end = (a->end > b->end) ? a->end : b->end;

  return (RangeInclusive){
      .start = start,
      .end = end,
  };
}

int ranges_cmp(const void *a, const void *b) {
  const RangeInclusive *aa = a;
  const RangeInclusive *bb = b;

  // Trick to compare unsigned integers
  return (aa->start > bb->start) - (aa->start < bb->start);
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

  RangeInclusive b = range_new(9, 11);
  assert(ranges_can_be_merged(&range, &b) == true);

  RangeInclusive c = range_new(11, 15);
  assert(ranges_can_be_merged(&b, &c) == true);

  RangeInclusive d = range_new(13, 13);
  assert(ranges_can_be_merged(&c, &d) == true);
  assert(ranges_can_be_merged(&b, &d) == false);

  auto merged = ranges_merge(&range, &b);
  assert(merged.start == 1);
  assert(merged.end == 11);

  assert(range_count(&b) == 3);
}
#endif
