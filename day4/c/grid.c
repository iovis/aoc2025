#include "grid.h"

#include "base.h"

#include <stddef.h>
#include <stddefer.h>
#include <stdlib.h>

Grid grid_from(const char *input) {
  Grid grid = (Grid){0};

  // Get size of cols
  const char *ptr = input;
  while (true) {
    if (*ptr == '\0') return grid;

    if (*ptr == '\n') {
      grid.cols = ptr - input;
      break;
    }

    ptr++;
  }

  ptr = input;
  while (*ptr) {
    if (*ptr != '\n') grid_push(&grid, *ptr);
    ptr++;
  }

  return grid;
}

void grid_push(Grid *self, char value) {
  expect(self->cols != 0, "Grid needs a number of columns");

  if (self->len == 0) { // init if unitialized
    if (self->capacity == 0) self->capacity = self->cols * self->cols;
    char *data = malloc(self->capacity * sizeof(char));
    expect(data, "failed to allocate memory");
    self->data = data;
  } else if (self->capacity <= self->len) { // grow if needed
    self->capacity *= 2;
    char *data = realloc(self->data, self->capacity * sizeof(char));
    expect(data, "failed to allocate memory");
    self->data = data;
  }

  self->data[self->len] = value;

  if (self->len == self->rows * self->cols) self->rows++;
  self->len++;
}

char *grid_get(const Grid *self, size_t i, size_t j) {
  if (i >= self->rows) return nullptr;
  if (j >= self->cols) return nullptr;

  size_t idx = i * self->cols + j;
  if (idx >= self->len) return nullptr;

  return &self->data[idx];
}

void grid_print(const Grid *self) {
  size_t filled_rows = self->len / self->cols;
  size_t rest = self->len % self->cols;

  for (size_t i = 0; i < filled_rows; i++) {
    printf("%.*s\n", (int)self->cols, &self->data[i * self->cols]);
  }

  if (rest) printf("%.*s\n", (int)rest, &self->data[filled_rows * self->cols]);
}

void grid_free(Grid *self) {
  free(self->data);
  *self = (Grid){0};
}

#ifdef TEST
#include <assert.h>
#include <string.h>

static void grid_push_test(void) {
  const char *grid_data = "123"
                          "456"
                          "789";

  Grid grid = (Grid){.len = 9, .capacity = 9, .rows = 3, .cols = 3};
  grid.data = malloc(grid.capacity * sizeof(char));
  memcpy(grid.data, grid_data, grid.len);
  defer grid_free(&grid);

  grid_push(&grid, '1');
  assert(grid.len == 10);
  assert(grid.capacity == 18);
  assert(grid.rows == 4);
  assert(grid.cols == 3);
  assert(*grid_get(&grid, 3, 0) == '1');

  grid_push(&grid, '2');
  assert(grid.len == 11);
  assert(grid.capacity == 18);
  assert(grid.rows == 4);
  assert(grid.cols == 3);
  assert(*grid_get(&grid, 3, 1) == '2');

  grid_push(&grid, '3');
  assert(grid.len == 12);
  assert(grid.capacity == 18);
  assert(grid.rows == 4);
  assert(grid.cols == 3);
  assert(*grid_get(&grid, 3, 2) == '3');

  grid_push(&grid, '4');
  assert(grid.len == 13);
  assert(grid.capacity == 18);
  assert(grid.rows == 5);
  assert(grid.cols == 3);
  assert(*grid_get(&grid, 4, 0) == '4');
}

static void grid_from_test(void) {
  const char input[] = "..@@.@@@@.\n"
                       "@@@.@.@.@@\n"
                       "@@@@@.@.@@\n"
                       "@.@@@@..@.\n"
                       "@@.@@@@.@@\n"
                       ".@@@@@@@.@\n"
                       ".@.@.@.@@@\n"
                       "@.@@@.@@@@\n"
                       ".@@@@@@@@.\n"
                       "@.@.@@@.@.\n";

  Grid grid = grid_from(input);
  defer grid_free(&grid);

  assert(grid.cols == 10);
  assert(grid.rows == 10);
  assert(grid.len == 100);
}

void grid_tests(void) {
  grid_push_test();
  grid_from_test();
}
#endif
