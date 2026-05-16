#include "lib.h"

int main(void) {
  parser_tests();
  range_tests();
  u64str_tests();
  p1_tests();
  p2_tests();

  puts("ok");
  return 0;
}
