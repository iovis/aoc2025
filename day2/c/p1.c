#include "p1.h"
#include "base.h"
#include "parser.h"
#include "range.h"

#include <string.h>

// UINT64_MAX = 18446744073709551615 => 20 digits + '\0'
#define U64_STRING_SIZE 21

typedef struct {
  char buffer[U64_STRING_SIZE];
  usize len;
} u64str;

static u64str u64_to_str(u64 value) {
  u64str result = {0};

  // Extract digits (in reverse order)
  while (value >= 10) {
    char digit = '0' + value % 10;
    value /= 10;

    result.buffer[result.len] = digit;
    result.len++;
  }

  // Last digit
  assert(value < 10);
  result.buffer[result.len] = '0' + value;
  result.len++;
  result.buffer[result.len] = '\0';

  assert(result.len < U64_STRING_SIZE);

  // invert the number
  for (usize i = 0; i < result.len / 2; i++) {
    char tmp = result.buffer[i];
    result.buffer[i] = result.buffer[result.len - 1 - i];
    result.buffer[result.len - 1 - i] = tmp;
  }

  return result;
}

#ifdef TEST
static void u64_to_str_test(void) {
  u64str result = u64_to_str(101);
  assert(strcmp(result.buffer, "101") == 0);

  result = u64_to_str(123);
  assert(strcmp(result.buffer, "123") == 0);

  result = u64_to_str(1234);
  assert(strcmp(result.buffer, "1234") == 0);

  result = u64_to_str(1188511880);
  assert(strcmp(result.buffer, "1188511880") == 0);
}
#endif

static bool is_valid_id(u64 value) {
  u64str id = u64_to_str(value);

  if (id.len % 2 != 0) return true;

  char *first_half = id.buffer;
  char *second_half = &id.buffer[id.len / 2];

  bool equal = strncmp(first_half, second_half, id.len / 2) == 0;

  // valid if not equal
  return !equal;
}

#ifdef TEST
static void is_valid_id_test(void) {
  assert(is_valid_id(101) == true);
  assert(is_valid_id(123123) == false);
  assert(is_valid_id(1188511880) == true);
}
#endif

// faster than `is_valid_id` because it solves it
// by calculating the number of digits
static bool is_valid_id_fast(u64 value) {
  u64 pow10 = 10;
  usize digits = 1;

  while (value >= pow10) {
    pow10 *= 10;
    digits++;
  }

  if (digits % 2 != 0) return true;

  u64 half_pow10 = 1;
  for (usize i = 0; i < digits / 2; i++) {
    half_pow10 *= 10;
  }

  // left  = value / pow10 (123123 / 10e3)
  // right = value % pow10 (123123 % 10e3)
  return value / half_pow10 != value % half_pow10;
}

#ifdef TEST
static void is_valid_id_fast_test(void) {
  assert(is_valid_id_fast(101) == true);
  assert(is_valid_id_fast(123123) == false);
  assert(is_valid_id_fast(1188511880) == true);
}
#endif

static void invalid_ids(void *ctx, u64 value) {
  u64 *total = ctx;
  if (!is_valid_id_fast(value)) *total += value;
}

u64 p1(const char *input) {
  const char *line = input;
  ParseResult result;
  u64 total = 0;

  while (true) {
    result = parse(line);
    if (result.error) break;
    line = result.rest;

    RangeInclusive range = result.range;
    range_each(&range, invalid_ids, &total);
  }

  return total;
}

#ifdef TEST
static void p1_test(void) {
  const char *input = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,"
                      "38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124\n";

  // dbg("p1(input) = %lu", p1(input));
  assert(p1(input) == 1227775554);
}

void p1_tests(void) {
  u64_to_str_test();
  is_valid_id_test();
  is_valid_id_fast_test();
  p1_test();
}
#endif
