#include "hello.h"

const char *hello_message(void) { return "hello from day1 C"; }

#ifdef TEST
#include <assert.h>
#include <string.h>

void hello_tests(void) {
  assert(strcmp(hello_message(), "hello from day1 C") == 0);
}
#endif
