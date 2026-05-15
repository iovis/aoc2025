#include "p2.h"
#include "dial.h"
#include "parser.h"

#include <stdint.h>

uint64_t p2(const char *input) {
  Dial dial = dial_new(50);
  ParseResult result;
  uint64_t total = 0;

  while (true) {
    result = parse(input);
    if (result.error) break;

    total += dial_rotate_with_count(&dial, result.number);

    input = result.rest;
  }

  return total;
}

#ifdef TEST
#include <assert.h>

void p2_tests(void) {
  const char *input = "L68\n"
                      "L30\n"
                      "R48\n"
                      "L5\n"
                      "R60\n"
                      "L55\n"
                      "L1\n"
                      "L99\n"
                      "R14\n"
                      "L82\n";

  assert(p2(input) == 6);
}
#endif
