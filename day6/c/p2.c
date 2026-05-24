#include "p2.h"

#include "base.h"
#include "parser.h"

#include <stddefer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint64_t parse_vertical_number(const vec(str_t) lines, size_t column, char *scratch) {
  size_t len = size(&lines);

  memset(scratch, 0, len + 1);

  for (size_t i = 0; i < len; i++) {
    str_t *line = get(&lines, i);
    expect(column < line->len);
    scratch[i] = line->buf[column];
  }

  return parse_number(&(str_t){
      .buf = scratch,
      .len = len,
  });
}

uint64_t p2(const char *input) {
  vec(str_t) lines = parse_into_lines(input);
  defer cleanup(&lines);
  expect(size(&lines) >= 1);

  vec(str_t) operators = parse_operators(last(&lines));
  defer cleanup(&operators);

  erase(&lines, size(&lines) - 1);

  char *cephalod_number = malloc(size(&lines) * sizeof(char) + 1);
  expect(cephalod_number);
  defer free(cephalod_number);

  size_t total = 0;
  size_t column = 0;
  for (size_t i = 0; i < size(&operators); i++) {
    size_t amount = 0;
    size_t width = get(&operators, i)->len;
    char operator = *get(&operators, i)->buf;

    if (operator == '*') {
      amount = 1;
      for (size_t k = column; k < column + width; k++) {
        uint64_t n = parse_vertical_number(lines, k, cephalod_number);
        amount *= n;
      }
    } else if (operator == '+') {
      amount = 0;
      for (size_t k = column; k < column + width; k++) {
        uint64_t n = parse_vertical_number(lines, k, cephalod_number);
        amount += n;
      }
    } else {
      expect(false, "unknown operator %c", operator);
    }

    total += amount;
    column += get(&operators, i)->len + 1;
  }

  return total;
}

#ifdef TEST
#include <assert.h>

void p2_tests(void) {
  const char *input = "123 328  51 64 \n"
                      " 45 64  387 23 \n"
                      "  6 98  215 314\n"
                      "*   +   *   +  \n";

  assert(p2(input) == 3263827);
}
#endif
