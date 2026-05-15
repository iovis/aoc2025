#include "p1.h"

u64 p1(const char *input) {
  (void)input;
  return 69;
}

#ifdef TEST
void p1_tests(void) {
  const char *input = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,"
                      "38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124\n";

  dbg("p1(input) = %lu", p1(input));
  assert(p1(input) == 1227775554);
}
#endif
