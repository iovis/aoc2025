#pragma once

#include <stddef.h>

typedef struct {
  char *data;
  size_t len;
  size_t capacity;
  size_t rows;
  size_t cols;
} Grid;

Grid grid_from(const char *input);

void grid_push(Grid *self, char value);

char *grid_get(const Grid *self, size_t i, size_t j);

void grid_print(const Grid *self);

void grid_free(Grid *self);

#ifdef TEST
void grid_tests(void);
#endif
