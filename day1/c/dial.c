#include "dial.h"
#include <stdint.h>
#include <stdio.h>

Dial dial_new(int64_t number) {
  return (Dial){
      .number = number,
  };
}

int64_t dial_rotate(Dial *self, int64_t amount) {
  self->number += amount;
  self->number %= 100;

  if (self->number < 0) self->number += 100;

  return self->number;
}

void dial_debug(const Dial *self) {
  fprintf(stderr, "Dial { number = %ld }\n", self->number);
}

#ifdef TEST
#include <assert.h>

static void dial_rotate_test(void) {
  Dial dial = dial_new(52);

  assert(dial_rotate(&dial, 18) == 70);
  assert(dial_rotate(&dial, 30) == 0);
  assert(dial_rotate(&dial, 95) == 95);
  assert(dial_rotate(&dial, 99) == 94);
  assert(dial_rotate(&dial, 60) == 54);
  assert(dial_rotate(&dial, -54) == 0);
  assert(dial_rotate(&dial, -5) == 95);

  dial = dial_new(52);
  assert(dial_rotate(&dial, 218) == 70);

  dial = dial_new(52);
  assert(dial_rotate(&dial, -218) == 34);
}

void dial_tests(void) {
  dial_rotate_test();
}
#endif
