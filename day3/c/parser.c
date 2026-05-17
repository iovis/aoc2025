#include "parser.h"

static bool is_end_of_str(const char *ptr) {
  return *ptr == '\0' || *ptr == EOF;
}

Line get_line(const char *text) {
  const char *ptr = text;
  const char *rest = nullptr;

  if (!ptr || is_end_of_str(ptr)) return (Line){.buffer = text};

  while (*ptr != '\n' && *ptr != '\0' && *ptr != EOF) {
    ptr++;
  }

  if (!is_end_of_str(ptr)) rest = ptr + 1;

  return (Line){
      .buffer = text,
      .len = (ptr - text),
      .rest = rest,
  };
}

void line_print(const Line *self) {
  printf("%.*s", (int)self->len, self->buffer);
  if (self->buffer[self->len] != '\n') printf("\n");
}

void line_debug(const Line *self) {
  fprintf(
      stderr,
      "Line { buffer = \"%.*s\", len = %lu, rest = \"%s\" }\n",
      (int)self->len,
      self->buffer,
      self->len,
      self->rest ? self->rest : "(null)"
  );
}

#ifdef TEST
static void get_line_invalid_test(void) {
  Line line;
  line = get_line("");
  assert(line.buffer[0] == '\0');
  assert(line.len == 0);
  assert(line.rest == nullptr);
}

static void get_line_without_trailing_newline_test(void) {
  Line line = get_line("987654321111111");

  assert(*line.buffer == '9');
  assert(line.len == 15);
  assert(line.buffer[line.len] == '\0');
  assert(line.rest == nullptr);
}

static void get_line_test(void) {
  Line line;
  const char *input = "987654321111111\n"
                      "811111111111119\n"
                      "234234234234278\n";

  line = get_line(input);
  assert(*line.buffer == '9');
  assert(line.len == 15);
  assert(line.buffer[line.len] == '\n');
  assert(*line.rest == '8');

  line = get_line(line.rest);
  assert(*line.buffer == '8');
  assert(line.len == 15);
  assert(line.buffer[line.len] == '\n');
  assert(*line.rest == '2');

  line = get_line(line.rest);
  assert(*line.buffer == '2');
  assert(line.len == 15);
  assert(line.buffer[line.len] == '\n');
  assert(*line.rest == '\0');

  line = get_line(line.rest);
  assert(line.len == 0);
  assert(*line.buffer == '\0');
  assert(line.rest == nullptr);
}

void parser_tests(void) {
  get_line_test();
  get_line_invalid_test();
  get_line_without_trailing_newline_test();
}
#endif
