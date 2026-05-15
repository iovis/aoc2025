#pragma once

#include <assert.h>
#include <stddef.h>
#include <stddefer.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef ptrdiff_t isize;
typedef size_t usize;

typedef float f32;
typedef double f64;

#ifdef TEST
#include <assert.h>
#endif

#ifndef NDEBUG
#define dbg(fmt, ...)                                                                                                  \
  do {                                                                                                                 \
    fprintf(stderr, "[%s:%d:%s] " fmt "\n", __FILE__, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__);                  \
  } while (0)
#else
#define dbg(...)                                                                                                       \
  do {                                                                                                                 \
  } while (0)
#endif
