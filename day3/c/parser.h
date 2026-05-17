#pragma once

#include "base.h" // IWYU pragma: keep

// string slice (not owned)
typedef struct {
  const char *buffer;
  const char *rest;
  size_t len;
} Line;

Line get_line(const char *text);
void line_print(const Line *self);
void line_debug(const Line *self);

#ifdef TEST
void parser_tests(void);
#endif
