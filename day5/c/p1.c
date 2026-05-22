#include "p1.h"

#include "parser.h"
#include "range_inclusive.h"
#include "stb_ds.h"

#include <stddefer.h>
#include <stdint.h>

static bool is_ingredient_fresh(const RangeInclusive *ranges, uint64_t ingredient_id) {
  for (int i = 0; i < arrlen(ranges); i++) {
    if (range_includes(&ranges[i], ingredient_id)) return true;
  }

  return false;
}

uint64_t p1(const char *input) {
  const char *line = input;
  ResultParseRangeInclusive result;
  uint64_t total = 0;

  RangeInclusive *ranges = nullptr;
  defer arrfree(ranges);

  // Parse and store ranges
  while (true) {
    result = parse_range(line);
    if (result.error) break;
    arrput(ranges, result.range);
    line = result.rest;
  }

  // Skip newline
  line++;

  while (*line) {
    uint64_t ingredient_id = parse_u64_line(&line);
    if (is_ingredient_fresh(ranges, ingredient_id)) total++;
  }

  return total;
}

#ifdef TEST
#include <assert.h>

void p1_tests(void) {
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

  // dbg("p1(input) = %lu", p1(input));
  assert(p1(input) == 3);
}
#endif
