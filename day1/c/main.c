#include <stdio.h>

#include "p1.h"

static const char input[] = {
#embed "../input.txt"
    ,
    '\0'
};

int main(void) {
  printf("p1 = %lu\n", p1(input));

  return 0;
}
