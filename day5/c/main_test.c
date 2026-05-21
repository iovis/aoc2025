#include "lib.h"

#include <stdio.h>

int main(void) {
  parser_tests();
  vec_tests();
  range_inclusive_tests();
  p1_tests();

  puts("ok");
  return 0;
}
