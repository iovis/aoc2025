#pragma once

#include <stdint.h>

typedef struct {
  int64_t number;
} Dial;

Dial dial_new(int64_t number);
int64_t dial_rotate(Dial *self, int64_t amount);
uint64_t dial_rotate_with_count(Dial *self, int64_t amount);
void dial_debug(const Dial *self);

#ifdef TEST
void dial_tests(void);
#endif
