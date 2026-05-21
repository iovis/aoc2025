#pragma once

#include "range_inclusive.h"
#include <stdint.h>

typedef struct {
  RangeInclusive range;
  bool error;
  const char *rest;
} ResultParseRangeInclusive;

uint64_t parse_u64_line(const char **str_ptr);
ResultParseRangeInclusive parse_range(const char *input);

#ifdef TEST
void parser_tests(void);
#endif
