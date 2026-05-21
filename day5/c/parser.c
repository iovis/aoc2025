#include "parser.h"

#include "range_inclusive.h"
#include <stdint.h>

static bool is_digit(const char digit) {
  return digit >= '0' && digit <= '9';
}

static bool consume_char(const char **ptr, char expected) {
  if (**ptr != expected) return false;
  (*ptr)++;
  return true;
}

// Advances the passed pointer to the first non-digit
static uint64_t parse_u64(const char **str_ptr) {
  const char *ptr = *str_ptr;
  uint64_t number = 0;

  while (true) {
    if (!is_digit(*ptr)) break;
    number = 10 * number + (*ptr - '0');
    ptr++;
  }

  *str_ptr = ptr;

  return number;
}

uint64_t parse_u64_line(const char **str_ptr) {
  uint64_t result = parse_u64(str_ptr);
  consume_char(str_ptr, '\n');
  return result;
}

// Parses "123-456\n"
ResultParseRangeInclusive parse_range(const char *input) {
  ResultParseRangeInclusive result = {.error = true, .rest = input};
  const char *ptr = input;

  result.range.start = parse_u64(&ptr);
  if (!consume_char(&ptr, '-')) return result;
  result.range.end = parse_u64(&ptr);

  consume_char(&ptr, '\n');

  result.rest = ptr;
  result.error = false;

  return result;
}

#ifdef TEST
#include <assert.h>

static void parse_u64_test(void) {
  const char *input = "123-456\n";
  const char *ptr = input;

  assert(parse_u64(&ptr) == 123);
  ptr++;
  assert(parse_u64_line(&ptr) == 456);

  assert(*ptr == '\0');
  assert(*input == '1');
}

static void parse_range_test(void) {
  char *input;
  ResultParseRangeInclusive result;

  input = "123-451";
  result = parse_range(input);
  assert(result.range.start == 123);
  assert(result.range.end == 451);
  assert(result.error == false);

  input = "3-5\n"
          "10-14\n";
  result = parse_range(input);
  assert(result.range.start == 3);
  assert(result.range.end == 5);
  assert(result.error == false);

  result = parse_range(result.rest);
  assert(result.range.start == 10);
  assert(result.range.end == 14);
  assert(result.error == false);

  result = parse_range(result.rest);
  assert(result.error == true);
}

void parser_tests(void) {
  parse_u64_test();
  parse_range_test();
}
#endif
