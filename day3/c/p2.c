#include "p2.h"
#include "base.h"
#include "parser.h"
#include <stdint.h>

// return the index of the local maximum
static size_t p2_max_in(const char *start, const char *end) {
  const char *max = start;

  for (const char *p = start; p < end; p++) {
    if (*p > *max) max = p;
  }

  return (size_t)(max - start);
}

static uint64_t p2_max_joltage(const Line *line, size_t number_of_digits) {
  expect(line->len >= number_of_digits);

  uint64_t joltage = 0;
  size_t digits_left = number_of_digits;
  const char *start = line->buffer;

  while (digits_left > 0) {
    const char *end = &line->buffer[line->len - digits_left + 1];
    size_t next_digit_idx = p2_max_in(start, end);
    uint64_t next_digit = start[next_digit_idx] - '0';

    joltage = 10 * joltage + next_digit;

    digits_left--;
    start = start + next_digit_idx + 1;
  }

  return joltage;
}

#ifdef TEST
static void p2_max_joltage_test(void) {
  Line line;

  line = get_line("987654321111111");
  assert(p2_max_joltage(&line, 12) == 987654321111);

  line = get_line("811111111111119");
  assert(p2_max_joltage(&line, 12) == 811111111119);

  line = get_line("234234234234278");
  assert(p2_max_joltage(&line, 12) == 434234234278);

  line = get_line("818181911112111");
  assert(p2_max_joltage(&line, 12) == 888911112111);
}
#endif

uint64_t p2(const char *input) {
  uint64_t total = 0;
  Line line;

  while (true) {
    line = get_line(input);
    if (line.len == 0) break;

    total += p2_max_joltage(&line, 12);

    if (!line.rest) break;
    input = line.rest;
  }

  return total;
}

#ifdef TEST
static void p2_test(void) {
  const char *input = "987654321111111\n"
                      "811111111111119\n"
                      "234234234234278\n"
                      "818181911112111\n";

  assert(p2(input) == 3121910778619);

  const char *input_no_trailing_newline = "987654321111111";
  assert(p2(input_no_trailing_newline) == 987654321111);
}

void p2_tests(void) {
  p2_max_joltage_test();
  p2_test();
}
#endif
