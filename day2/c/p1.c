#include "p1.h"
#include "base.h"
#include "parser.h"
#include "range.h"
#include "u64str.h"

static bool is_valid_id_string(u64 value) {
  U64Str id = u64str_from(value);

  if (id.len % 2 != 0) return true;

  const char *text = u64str_cstr(&id);
  usize half = id.len / 2;

  for (usize i = 0; i < half; i++) {
    if (text[i] != text[i + half]) return true;
  }

  return false;
}

#ifdef TEST
static void is_valid_id_string_test(void) {
  assert(is_valid_id_string(101) == true);
  assert(is_valid_id_string(123123) == false);
  assert(is_valid_id_string(1188511880) == true);
}
#endif

u64 p1(const char *input) {
  const char *line = input;
  ParseResult result;
  u64 total = 0;

  while (true) {
    result = parse(line);
    if (result.error) break;
    line = result.rest;

    RangeInclusive range = result.range;
    for (u64 id = range.start; id <= range.end; id++) {
      if (!is_valid_id_string(id)) total += id;
    }
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
  is_valid_id_string_test();
  p1_test();
}
#endif
