#include "p1.h"
#include "p2.h"

#include <stddefer.h>
#include <stdio.h>
#include <stdlib.h>

static const char input[] = {
#embed "../input.txt"
    ,
    '\0'
};

// NOTE: rewinds to beginning of file
static long get_file_size(FILE *file) {
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file);

  return file_size;
}

static char *read_file(const char *restrict filename) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    perror("failed to read file");
    return nullptr;
  }

  defer fclose(file);

  long file_size = get_file_size(file);
  if (file_size == -1) {
    perror("failed to read file size");
    return nullptr;
  }

  size_t buffer_size = file_size + 1;
  char *buffer = malloc(buffer_size * sizeof(char));
  if (!buffer) {
    perror("failed to allocate memory");
    return nullptr;
  }

  size_t bytes_read = fread(buffer, sizeof(*buffer), buffer_size - 1, file);
  buffer[bytes_read] = '\0';

  if (bytes_read != buffer_size - 1) {
    fprintf(stderr, "fread() failed: %zu (bytes read) != %zu (buffer size)\n", bytes_read, buffer_size);
    free(buffer);
    return nullptr;
  }

  return buffer;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("p1 = %lu\n", p1(input));
    printf("p2 = %lu\n", p2(input));
    return EXIT_SUCCESS;
  }

  char *input = read_file(argv[1]);
  if (!input) return EXIT_FAILURE;
  defer free(input);

  printf("p1 = %lu\n", p1(input));
  printf("p2 = %lu\n", p2(input));

  return EXIT_SUCCESS;
}
