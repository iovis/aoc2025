#include "p1.h"
#include "parser.h"

// return the index of the local maximum
static size_t max_in(const char *line, const char *end) {
  char max = '0';
  size_t idx = 0;

  for (size_t i = 0; &line[i] < end; i++) {
    if (line[i] > max) {
      max = line[i];
      idx = i;
    }
  }

  return idx;
}

static uint64_t max_joltage(const Line *line) {
  expect(line->len >= 2);

  // Max till the second to last item
  const char *start1 = line->buffer;
  size_t idx1 = max_in(start1, &line->buffer[line->len - 1]);

  // Max after the first digit till the end
  const char *start2 = &line->buffer[idx1 + 1];
  size_t idx2 = max_in(start2, &line->buffer[line->len]);

  // 10 * digit1 + digit2
  return 10 * (start1[idx1] - '0') + (start2[idx2] - '0');
}

#ifdef TEST
static void max_joltage_test(void) {
  Line line;

  line = get_line("987654321111111");
  assert(max_joltage(&line) == 98);

  line = get_line("811111111111119");
  assert(max_joltage(&line) == 89);

  line = get_line("234234234234278");
  assert(max_joltage(&line) == 78);

  line = get_line("818181911112111");
  assert(max_joltage(&line) == 92);
}
#endif

uint64_t p1(const char *input) {
  uint64_t total = 0;
  Line line;

  while (true) {
    line = get_line(input);
    if (line.len == 0) break;

    total += max_joltage(&line);

    if (!line.rest) break;
    input = line.rest;
  }

  return total;
}

#ifdef TEST
static void p1_test(void) {
  const char *input = "987654321111111\n"
                      "811111111111119\n"
                      "234234234234278\n"
                      "818181911112111\n";

  assert(p1(input) == 357);

  const char *input_no_trailing_newline = "987654321111111";
  assert(p1(input_no_trailing_newline) == 98);
}

void p1_tests(void) {
  max_joltage_test();
  p1_test();
}
#endif
