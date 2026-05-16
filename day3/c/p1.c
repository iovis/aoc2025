#include "p1.h"

u64 p1(const char *input) {
  return 123;
}

#ifdef TEST
void p1_tests(void) {
  const char *input = "987654321111111\n"
                      "811111111111119\n"
                      "234234234234278\n"
                      "818181911112111\n";

  assert(p1(input) == 357);
}
#endif
