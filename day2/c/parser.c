#include "parser.h"

ParseResult parse(const char *input) {
  const char *start = input;
  const char *end = input;

  if (*start < '0' || *start > '9') return (ParseResult){.error = true};

  while ((*end >= '0' && *end <= '9') || *end == '-') {
    end++;
  }

  // dbg("line = %.*s", (int)(end - start), start);

  const char *rest = (*end != '\0') ? end + 1 : "";

  return (ParseResult){
      .range = range_from(start),
      .error = false,
      .rest = rest,
  };
}

void parse_print(const ParseResult *self) {
  fprintf(
      stderr,
      "ParseResult { range = { start = %ld, end = %ld }, error = %s, rest = \"%s\" }\n",
      self->range.start,
      self->range.end,
      self->error ? "true" : "false",
      self->rest
  );
}

#ifdef TEST
#include <string.h>

static void parse_test(void) {
  const char *line = "11-22,95-115,998-1012";

  ParseResult result = parse(line);
  parse_print(&result);

  assert(result.error == false);
  assert(result.range.start == 11);
  assert(result.range.end == 22);
  assert(strcmp(result.rest, "95-115,998-1012") == 0);

  result = parse(result.rest);
  parse_print(&result);

  assert(result.error == false);
  assert(result.range.start == 95);
  assert(result.range.end == 115);
  assert(strcmp(result.rest, "998-1012") == 0);

  result = parse(result.rest);
  parse_print(&result);

  assert(result.error == false);
  assert(result.range.start == 998);
  assert(result.range.end == 1012);
  assert(strcmp(result.rest, "") == 0);
}

void parser_tests(void) {
  parse_test();
}
#endif
