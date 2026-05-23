#include "parser.h"

#include "base.h"
#include "cc.h"
#include <stdint.h>
#include <sys/types.h>

vec(str_t) parse_into_lines(const char *input) {
  vec(str_t) lines = initialized(&lines);
  const char *ptr = input;

  while (*ptr) {
    const char *start = ptr;

    while (*ptr && *ptr != '\n')
      ptr++;

    str_t line = (str_t){.buf = start, .len = ptr - start};
    expect(push(&lines, line));
    if (*ptr != '\0') ptr++;
  }

  return lines;
}

vec(str_t) parse_operators(const str_t *line) {
  vec(str_t) operators = initialized(&operators);
  const char *ptr = line->buf;
  const char *end = line->buf + line->len;

  while (ptr < end && *ptr != '\n') {
    const char *start = ptr;
    ptr++;

    while (ptr < end && *ptr == ' ')
      ptr++;

    size_t len = ptr - start;
    if (ptr < end && *ptr != '\n') len--; // remove separator

    str_t operator = (str_t){.buf = start, .len = len};
    expect(push(&operators, operator));
  }

  return operators;
}

uint64_t parse_number(const str_t *line) {
  uint64_t number = 0;

  for (size_t i = 0; i < line->len; i++) {
    char c = line->buf[i];
    if (c < '0' || c > '9') continue;
    number = 10 * number + c - '0';
  }

  return number;
}

#ifdef TEST
#include <assert.h>
#include <string.h>

static void parse_number_test(void) {
  assert(parse_number(&(str_t){.buf = "123", .len = 3}) == 123);
  assert(parse_number(&(str_t){.buf = " 45", .len = 3}) == 45);
  assert(parse_number(&(str_t){.buf = "  6", .len = 3}) == 6);
  assert(parse_number(&(str_t){.buf = "64 ", .len = 3}) == 64);
}

static void parse_into_lines_test(void) {
  const char *input = "123 328  51 64 \n"
                      " 45 64  387 23 \n"
                      "  6 98  215 314\n"
                      "*   +   *   +  \n";

  vec(str_t) lines = parse_into_lines(input);

  assert(memcmp(get(&lines, 0)->buf, "123 328  51 64 ", get(&lines, 0)->len) == 0);
  assert(memcmp(get(&lines, 1)->buf, " 45 64  387 23 ", get(&lines, 1)->len) == 0);
  assert(memcmp(get(&lines, 2)->buf, "  6 98  215 314", get(&lines, 2)->len) == 0);
  assert(memcmp(get(&lines, 3)->buf, "*   +   *   +  ", get(&lines, 3)->len) == 0);
  assert(size(&lines) == 4);

  cleanup(&lines);
}

static void parse_operators_test(void) {
  str_t line = {
      .buf = "*   +   *   +  \n",
      .len = 15,
  };

  vec(str_t) operators = parse_operators(&line);

  assert(*get(&operators, 0)->buf == '*');
  assert(get(&operators, 0)->len == 3);
  assert(*get(&operators, 1)->buf == '+');
  assert(get(&operators, 1)->len == 3);
  assert(*get(&operators, 2)->buf == '*');
  assert(get(&operators, 2)->len == 3);
  assert(*get(&operators, 3)->buf == '+');
  assert(get(&operators, 3)->len == 3);
  assert(size(&operators) == 4);

  cleanup(&operators);
}

void parser_tests(void) {
  parse_into_lines_test();
  parse_operators_test();
  parse_number_test();
}
#endif
