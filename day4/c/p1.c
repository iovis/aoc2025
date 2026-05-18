#include "p1.h"
#include "base.h"
#include "grid.h"
#include <stddef.h>

static bool can_be_accessed(const Grid *grid, size_t i, size_t j) {
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

uint64_t p1(const char *input) {
  Grid grid = grid_from(input);
  defer grid_free(&grid);

  uint64_t total = 0;

  for (size_t i = 0; i < grid.rows; i++) {
    for (size_t j = 0; j < grid.cols; j++) {
      if (*grid_get(&grid, i, j) == '@' && can_be_accessed(&grid, i, j)) {
        total++;
      }
    }
  }

  return total;
}

#ifdef TEST
void p1_tests(void) {
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

  assert(p1(input) == 13);
}
#endif
