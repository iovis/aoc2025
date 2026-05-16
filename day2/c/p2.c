#include "p2.h"
#include "base.h"
#include "parser.h"
#include "range.h"
#include "u64str.h"
#include <string.h>

static bool p2_is_valid_id_string(u64 value) {
  U64Str id = u64str_from(value);
  const char *text = u64str_cstr(&id);

  for (usize window_size = id.len / 2; window_size > 0; window_size--) {
    // if not divisible, it can't be validated
    if (id.len % window_size != 0) continue;

    usize windows = id.len / window_size;
    bool invalid = true;
    for (usize i = 1; i < windows; i++) {
      if (strncmp(&text[0], &text[i * window_size], window_size) != 0) {
        // if a window is not equal to the previous ones, it's not invalid
        invalid = false;
        break;
      }
    }

    if (invalid) return false;
  }

  return true;
}

#ifdef TEST
static void p2_is_valid_id_string_test(void) {
  assert(p2_is_valid_id_string(101) == true);
  assert(p2_is_valid_id_string(123123) == false);
  assert(p2_is_valid_id_string(1188511880) == true);
  assert(p2_is_valid_id_string(12341234) == false);
  assert(p2_is_valid_id_string(123123123) == false);
  assert(p2_is_valid_id_string(1212121212) == false);
  assert(p2_is_valid_id_string(1111111111) == false);
}
#endif

u64 p2(const char *input) {
  const char *line = input;
  ParseResult result;
  u64 total = 0;

  while (true) {
    result = parse(line);
    if (result.error) break;
    line = result.rest;

    RangeInclusive range = result.range;
    for (u64 id = range.start; id <= range.end; id++) {
      if (!p2_is_valid_id_string(id)) total += id;
    }
  }

  return total;
}

#ifdef TEST
static void p2_test(void) {
  const char *input = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,"
                      "38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124\n";

  // dbg("p2(input) = %lu", p2(input));
  assert(p2(input) == 4174379265);
}

void p2_tests(void) {
  p2_is_valid_id_string_test();
  p2_test();
}
#endif
