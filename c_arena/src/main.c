#include "lib.h"

typedef struct {
  int x;
  double y;
} Point;

int main(void) {
  Arena arena = arena_create(1024);
  defer arena_free(&arena);

  Point *point = arena_new(&arena, Point);
  expect(point);

  *point = (Point){
      .x = 3,
      .y = 4.5,
  };

  const char *label = "arena demo";

  printf("%s: point = (%d, %.1f)\n", label, point->x, point->y);

  return 0;
}
