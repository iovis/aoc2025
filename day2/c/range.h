#pragma once

#include "base.h"

typedef struct {
  u64 start;
  u64 end;
} RangeInclusive;

RangeInclusive range_from(const char *str);
void range_print(const RangeInclusive *self);
