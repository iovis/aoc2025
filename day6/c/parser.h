#pragma once

#include "cc.h"

#include <stddef.h>
#include <stdint.h>

typedef struct {
  const char *buf;
  size_t len;
} str_t;

vec(str_t) parse_into_lines(const char *input);
vec(str_t) parse_operators(const str_t *line);
uint64_t parse_number(const str_t *line);

#ifdef TEST
void parser_tests(void);
#endif
