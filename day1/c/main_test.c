#include <stdio.h>

#include "dial.h"
#include "p1.h"
#include "parser.h"

int main(void) {
  dial_tests();
  parse_tests();
  p1_test();
  puts("ok");
  return 0;
}
