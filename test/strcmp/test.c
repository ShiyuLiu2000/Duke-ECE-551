#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char * s1 = NULL;
  char * s2 = "fxxku";
  int res = strcmp(s1, s2);
  printf("res is %d\n", res);
  return EXIT_SUCCESS;
}
