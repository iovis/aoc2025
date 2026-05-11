#include "parser.h"
#include <stdio.h>

static bool is_digit(const char c) {
  return c >= '0' && c <= '9';
}

ParseResult parse(const char *input) {
  const char *ptr = input;
  int64_t sign = 1;
  int64_t number = 0;
  bool error = true;

  if (*ptr == 'L') {
    sign = -1;
    ptr++;
  } else if (*ptr == 'R') {
    sign = 1;
    ptr++;
  } else {
    return (ParseResult){.error = true};
  }

  while (is_digit(*ptr)) {
    int64_t digit = *ptr - '0';
    number = 10 * number + digit;

    error = false;
    ptr++;
  }

  // Consume newline character
  if (*ptr == '\n') ptr++;

  return (ParseResult){
      .number = sign * number,
      .error = error,
      .rest = ptr,
  };
}

void parse_debug(const ParseResult *self) {
  const char *error = self->error ? "true" : "false";
  fprintf(stderr, "ParseResult { number = %ld, error = %s, rest = %p }\n", self->number, error, self->rest);
}

#ifdef TEST
#include <assert.h>

static void successful_parse_test(void) {
  const char *input = "L68\nL99\nR5\nR14\n\n";

  ParseResult result = parse(input);
  assert(result.number == -68);

  result = parse(result.rest);
  assert(result.number == -99);

  result = parse(result.rest);
  assert(result.number == 5);

  result = parse(result.rest);
  assert(result.number == 14);
}

static void failed_parse_test(void) {
  assert(parse("").error == true);
  assert(parse("\n").error == true);
  assert(parse("L\n").error == true);
  assert(parse("Rabc\n").error == true);
  assert(parse("X12\n").error == true);
}

void parse_tests(void) {
  successful_parse_test();
  failed_parse_test();
}

#endif
