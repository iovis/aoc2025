#include "p1.h"

uint64_t p1(const char *input) {
  return 0;
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
