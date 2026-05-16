#pragma once

#include "base.h"

// UINT64_MAX = 18446744073709551615 => 20 digits + '\0'
#define U64_STRING_SIZE 21

typedef struct {
  char buffer[U64_STRING_SIZE];
  usize offset;
  usize len;
} U64Str;

U64Str u64str_from(u64 value);

static inline const char *u64str_cstr(const U64Str *self) {
  return &self->buffer[self->offset];
}
