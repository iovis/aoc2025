#include "p1.h"

#include "base.h"
#include "parser.h"

#include <stddefer.h>
#include <stdio.h>

uint64_t p1(const char *input) {
  vec(str_t) lines = parse_into_lines(input);
  defer cleanup(&lines);
  expect(size(&lines) >= 1);

  vec(str_t) operators = parse_operators(last(&lines));
  defer cleanup(&operators);

  erase(&lines, size(&lines) - 1);

  size_t total = 0;
  size_t column = 0;
  for (size_t i = 0; i < size(&operators); i++) {
    size_t amount = 0;
    size_t width = get(&operators, i)->len;
    char operator = *get(&operators, i)->buf;

    if (operator == '*') {
      amount = 1;
      for (size_t j = 0; j < size(&lines); j++) {
        expect(column + width <= get(&lines, j)->len);
        amount *= parse_number(&(str_t){
            .buf = &get(&lines, j)->buf[column],
            .len = width,
        });
      }
    } else if (operator == '+') {
      amount = 0;
      for (size_t j = 0; j < size(&lines); j++) {
        expect(column + width <= get(&lines, j)->len);
        amount += parse_number(&(str_t){
            .buf = &get(&lines, j)->buf[column],
            .len = width,
        });
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

void p1_tests(void) {
  const char *input = "123 328  51 64 \n"
                      " 45 64  387 23 \n"
                      "  6 98  215 314\n"
                      "*   +   *   +  \n";

  assert(p1(input) == 4277556);
}
#endif
