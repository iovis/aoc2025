#include "range.h"
#include "base.h"

RangeInclusive range_from(const char *str) {
  u64 start = 0;
  u64 end = 0;

  sscanf(str, "%lu-%lu", &start, &end);

  return (RangeInclusive){
      .start = start,
      .end = end,
  };
}

void range_each(const RangeInclusive *self, void (*each_fn)(void *ctx, u64 value), void *ctx) {
  for (usize i = self->start; i <= self->end; i++) {
    each_fn(ctx, i);
  }
}

void range_print(const RangeInclusive *self) {
  printf("RangeInclusive { start = %lu, end = %lu }\n", self->start, self->end);
}

#ifdef TEST
static void range_from_test(void) {
  RangeInclusive range = range_from("11-22");

  assert(range.start == 11);
  assert(range.end == 22);

  range = range_from("1188511880-1188511890,");

  assert(range.start == 1188511880);
  assert(range.end == 1188511890);
}

void range_tests(void) {
  range_from_test();
}
#endif
