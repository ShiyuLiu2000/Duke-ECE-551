#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char * line = malloc(5 * sizeof(*line));
  line[0] = 'a';
  line[1] = 'b';
  line[2] = '\0';
  line[3] = 'c';
  line[4] = '\0';
  printf("%s\n", line);
  printf("length is %ld\n", strlen(line));
  free(line);
  return EXIT_SUCCESS;
}
