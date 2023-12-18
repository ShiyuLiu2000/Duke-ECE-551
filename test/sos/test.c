#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  FILE * f = fopen(argv[1], "r");
  ssize_t len = 0;
  size_t sz = 0;
  char * line = NULL;

  while ((len = getline(&line, &sz, f)) >= 0) {
    printf("%s", line);
    printf("sz is %d, len is %d\n", sz, len);
    line = NULL;
  }

  free(line);

  return EXIT_SUCCESS;
}
