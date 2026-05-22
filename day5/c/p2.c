#include "p2.h"

#include "base.h"
#include "parser.h"
#include "range_inclusive.h"
#include "stb_ds.h"

#include <stddefer.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t p2(const char *input) {
  const char *line = input;
  ResultParseRangeInclusive result;

  RangeInclusive *ranges = nullptr;
  defer arrfree(ranges);

  // Parse and merge ranges
  while (true) {
    result = parse_range(line);
    if (result.error) break;
    arrput(ranges, result.range);
    line = result.rest;
  }

  expect(arrlen(ranges) > 0);

  // Sort by start
  qsort(ranges, arrlen(ranges), sizeof(*ranges), ranges_cmp);

  // Consolidate ranges using in-place compaction
  int write_idx = 0;
  for (int read_idx = 1; read_idx < arrlen(ranges); read_idx++) {
    if (ranges_can_be_merged(&ranges[write_idx], &ranges[read_idx])) {
      // if ranges can be merged, write it in-place
      ranges[write_idx] = ranges_merge(&ranges[write_idx], &ranges[read_idx]);
    } else {
      // if they can't, copy the current range over the last discarded range
      write_idx++;
      ranges[write_idx] = ranges[read_idx];
    }
  }

  // Valid ranges only till `write_idx`, adjust `len` accordingly
  arrsetlen(ranges, write_idx + 1);

  // Count ranges
  uint64_t total = 0;
  for (int i = 0; i < arrlen(ranges); i++) {
    total += range_count(&ranges[i]);
  }

  return total;
}

#ifdef TEST
#include <assert.h>

void p2_tests(void) {
  const char *input = "3-5\n"
                      "10-14\n"
                      "16-20\n"
                      "12-18\n"
                      "\n"
                      "1\n"
                      "5\n"
                      "8\n"
                      "11\n"
                      "17\n"
                      "32\n";

  auto result = p2(input);
  // dbg("p2(input) = %lu", result);
  assert(result == 14);

  input = "1-1\n"
          "10-20\n"
          "12-13\n"
          "30-30\n";

  result = p2(input);
  // dbg("p2(input) = %lu", result);
  assert(result == 13);
}
#endif
