#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  const char * s = "hi";
  const char * copy = strdup(s);
  printf("%s\n", copy);
  return EXIT_SUCCESS;
}
