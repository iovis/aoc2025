#include "u64str.h"
#include "base.h"

static const char decimal_pairs[] = "0001020304050607080910111213141516171819"
                                    "2021222324252627282930313233343536373839"
                                    "4041424344454647484950515253545556575859"
                                    "6061626364656667686970717273747576777879"
                                    "8081828384858687888990919293949596979899";

static void write_pair(char *dst, u64 value) {
  assert(value < 100);

  usize pair = (usize)value * 2;
  dst[0] = decimal_pairs[pair];
  dst[1] = decimal_pairs[pair + 1];
}

U64Str u64str_from(u64 value) {
  U64Str result;
  char *end = &result.buffer[U64_STRING_SIZE - 1];
  char *cursor = end;

  *end = '\0';

  while (value > 9999) {
    u64 chunk = value % 10000;
    value /= 10000;

    cursor -= 4;
    write_pair(cursor, chunk / 100);     // left two digits
    write_pair(cursor + 2, chunk % 100); // right two digits
  }

  if (value > 999) {
    cursor -= 4;
    write_pair(cursor, value / 100);
    write_pair(cursor + 2, value % 100);
  } else if (value > 99) {
    cursor -= 3;
    cursor[0] = (char)('0' + value / 100);
    write_pair(cursor + 1, value % 100);
  } else if (value > 9) {
    cursor -= 2;
    write_pair(cursor, value);
  } else {
    cursor -= 1;
    cursor[0] = (char)('0' + value);
  }

  result.offset = (usize)(cursor - result.buffer);
  result.len = (usize)(end - cursor);

  return result;
}

#ifdef TEST
#include <string.h>

static void u64str_from_test(void) {
  U64Str result = u64str_from(0);
  assert(strcmp(u64str_cstr(&result), "0") == 0);
  assert(result.len == 1);

  result = u64str_from(9);
  assert(strcmp(u64str_cstr(&result), "9") == 0);
  assert(result.len == 1);

  result = u64str_from(10);
  assert(strcmp(u64str_cstr(&result), "10") == 0);
  assert(result.len == 2);

  result = u64str_from(101);
  assert(strcmp(u64str_cstr(&result), "101") == 0);
  assert(result.len == 3);

  result = u64str_from(1234);
  assert(strcmp(u64str_cstr(&result), "1234") == 0);
  assert(result.len == 4);

  result = u64str_from(1188511880);
  assert(strcmp(u64str_cstr(&result), "1188511880") == 0);
  assert(result.len == 10);

  result = u64str_from(UINT64_MAX);
  assert(strcmp(u64str_cstr(&result), "18446744073709551615") == 0);
  assert(result.len == 20);
}

void u64str_tests(void) {
  u64str_from_test();
}
#endif
