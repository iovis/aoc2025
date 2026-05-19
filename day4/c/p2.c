#include "p2.h"
#include "grid.h"

#include <stddef.h>
#include <stddefer.h>
#include <stdint.h>

static bool can_be_accessed_p2(const Grid *grid, size_t i, size_t j) {
  // clang-format off
  int directions[8][2] = {
    {-1, -1}, {-1,  0}, {-1,  1},
    { 0, -1},           { 0,  1},
    { 1, -1}, { 1,  0}, { 1,  1},
  };
  // clang-format on

  size_t count = 0;

  for (size_t d = 0; d < 8; d++) {
    int ii = (int)i + directions[d][0];
    int jj = (int)j + directions[d][1];

    if (ii < 0 || jj < 0) continue;

    char *item = grid_get(grid, ii, jj);

    if (item && *item == '@') count++;
  }

  return count < 4;
}

static uint64_t remove_accessible_rolls(Grid *grid) {
  uint64_t total = 0;

  for (size_t i = 0; i < grid->rows; i++) {
    for (size_t j = 0; j < grid->cols; j++) {
      char *cell = grid_get(grid, i, j);
      if (*cell == '@' && can_be_accessed_p2(grid, i, j)) {
        *cell = '.';
        total++;
      }
    }
  }

  return total;
}

uint64_t p2(const char *input) {
  Grid grid = grid_from(input);
  defer grid_free(&grid);

  uint64_t total = 0;
  uint64_t removed = 0;

  do {
    removed = remove_accessible_rolls(&grid);
    total += removed;
  } while (removed != 0);

  return total;
}

#ifdef TEST
#include <assert.h>

void p2_tests(void) {
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

  assert(p2(input) == 43);
}
#endif
