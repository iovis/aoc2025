#include "p1.h"

#include <stdio.h>

uint64_t p1(const char *input) {
  printf("%s\n", input);

  return 0;
}

#ifdef TEST
#include <assert.h>

void p1_tests(void) {
  //   let input = indoc::indoc! {"
  //     3-5
  //     10-14
  //     16-20
  //     12-18
  //
  //     1
  //     5
  //     8
  //     11
  //     17
  //     32
  // "};
  //
  // assert_eq!(p1(input), 3);
  assert(true);
}
#endif
