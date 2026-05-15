#pragma once

#include "base.h"
#include "range.h"

typedef struct {
  RangeInclusive range;
  bool error;
  const char *rest;
} ParseResult;

ParseResult parse(const char *input);
void parse_print(const ParseResult *self);

#ifdef TEST
void parser_tests(void);
#endif
