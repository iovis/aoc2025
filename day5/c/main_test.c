#include "lib.h"

#include <stdio.h>

int main(void) {
  parser_tests();
  // array_tests();
  range_inclusive_tests();
  p1_tests();
  p2_tests();

  puts("ok");
  return 0;
}
