#include "dial.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DIAL_RANGE 100

Dial dial_new(int64_t number) {
  return (Dial){
      .number = number,
  };
}

int64_t dial_rotate(Dial *self, int64_t amount) {
  self->number += amount;
  self->number %= DIAL_RANGE;

  if (self->number < 0) self->number += DIAL_RANGE;

  return self->number;
}

// Returns how many times the dial hit zero
uint64_t dial_rotate_with_count(Dial *self, int64_t amount) {
  int64_t zeroes = 0;

  if (self->number == 0 && amount < 0) zeroes = -1;

  self->number += amount;
  zeroes += labs(self->number / DIAL_RANGE);
  self->number %= DIAL_RANGE;

  if (self->number < 0) {
    self->number += DIAL_RANGE;
    zeroes++;
  }

  if (self->number == 0 && amount < 0) zeroes++;

  return zeroes;
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

static void dial_rotate_with_count_test(void) {
  Dial dial = dial_new(50);
  assert(dial_rotate_with_count(&dial, 50) == 1);
  assert(dial.number == 0);

  dial = dial_new(50);
  assert(dial_rotate_with_count(&dial, -50) == 1);
  assert(dial.number == 0);

  dial = dial_new(0);
  assert(dial_rotate_with_count(&dial, 1) == 0);

  dial = dial_new(0);
  assert(dial_rotate_with_count(&dial, -1) == 0);

  dial = dial_new(50);
  assert(dial_rotate_with_count(&dial, 203) == 2);
  assert(dial.number == 53);

  dial = dial_new(50);
  assert(dial_rotate_with_count(&dial, -203) == 2);
  assert(dial.number == 47);

  dial = dial_new(0);
  assert(dial_rotate_with_count(&dial, 100) == 1);

  dial = dial_new(0);
  assert(dial_rotate_with_count(&dial, -100) == 1);

  dial = dial_new(1);
  assert(dial_rotate_with_count(&dial, -1) == 1);

  dial = dial_new(99);
  assert(dial_rotate_with_count(&dial, 1) == 1);
}

void dial_tests(void) {
  dial_rotate_test();
  dial_rotate_with_count_test();
}
#endif
