#include "p1.h"

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
    exit(EXIT_FAILURE);
  }

  long file_size = get_file_size(file);
  if (file_size == -1) {
    perror("failed to read file size");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  size_t buffer_size = file_size + 1;
  char *buffer = malloc(buffer_size * sizeof(char));
  if (!buffer) {
    perror("failed to allocate memory");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  size_t bytes_read = fread(buffer, sizeof(*buffer), buffer_size - 1, file);
  buffer[bytes_read] = '\0';

  if (bytes_read != buffer_size - 1) {
    fprintf(stderr, "fread() failed: %zu (bytes read) != %zu (buffer size)\n", bytes_read, buffer_size);
    fclose(file);
    exit(EXIT_FAILURE);
  }

  fclose(file);
  return buffer;
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    char *input = read_file(argv[1]);
    printf("p1 = %lu\n", p1(input));
    free(input);
  } else {
    printf("p1 = %lu\n", p1(input));
  }

  return 0;
}
