#pragma once

#include <stdint.h>

typedef struct {
  int64_t number;
  bool error;
  const char *rest;
} ParseResult;

ParseResult parse(const char *input);
void parse_debug(const ParseResult *self);

#ifdef TEST
void parse_tests(void);
#endif
