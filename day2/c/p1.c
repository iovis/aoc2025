#include "p1.h"
#include "parser.h"
#include "range.h"
#include <string.h>

static bool is_valid_id(u64 value) {
  char *id = nullptr;
  int id_len = asprintf(&id, "%lu", value);
  assert(id_len != -1);
  defer free(id);

  if (id_len % 2 != 0) return true;

  char *first_half = id;
  char *second_half = &id[id_len / 2];

  bool equal = strncmp(first_half, second_half, id_len / 2) == 0;

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

static void invalid_ids(void *ctx, u64 value) {
  u64 *total = ctx;
  if (!is_valid_id(value)) *total += value;
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
  is_valid_id_test();
  p1_test();
}
#endif
