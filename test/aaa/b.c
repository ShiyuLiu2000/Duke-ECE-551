#include <stdio.h>
#include <stdlib.h>

char * g(char * p, char ** q) {
  q++;
  char * temp = *q;
  *p = *(temp + 1);
  *q = p;
  return temp;
}

int main(void) {
  char c1[] = "red";
  char c2[] = "green";
  char c3[] = "blue";
  char * carr[] = {c1, c2, c3};
  char ** q = carr + 1;
  *(q - 1) = g(carr[0], q);
  printf("%s\n", carr[0]);
  printf("%s\n", carr[1]);
  printf("%s\n", carr[2]);
  return EXIT_SUCCESS;
}
