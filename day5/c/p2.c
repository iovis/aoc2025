#include "p2.h"

#include "base.h"
#include "parser.h"
#include "range_inclusive.h"
#include "vec.h"

#include <stddefer.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t p2(const char *input) {
  const char *line = input;
  ResultParseRangeInclusive result;

  Ranges ranges = {0};
  defer ranges_free(&ranges);

  // Parse and merge ranges
  while (true) {
    result = parse_range(line);
    if (result.error) break;
    expect(ranges_push(&ranges, result.range));
    line = result.rest;
  }

  expect(ranges.len > 0);

  // Sort by start
  qsort(ranges.items, ranges.len, sizeof(ranges.items[0]), ranges_cmp);

  // Consolidate ranges using in-place compaction
  size_t write_idx = 0;
  for (size_t read_idx = 1; read_idx < ranges.len; read_idx++) {
    if (ranges_can_be_merged(&ranges.items[write_idx], &ranges.items[read_idx])) {
      // if ranges can be merged, write it in-place
      ranges.items[write_idx] = ranges_merge(&ranges.items[write_idx], &ranges.items[read_idx]);
    } else {
      // if they can't, copy the current range over the last discarded range
      write_idx++;
      ranges.items[write_idx] = ranges.items[read_idx];
    }
  }

  ranges.len = write_idx + 1; // (+1 because 0-based)

  // Count ranges
  uint64_t total = 0;
  for (size_t i = 0; i < ranges.len; i++) {
    total += range_count(&ranges.items[i]);
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
