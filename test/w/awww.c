#include <stdio.h>
#include <stdlib.h>

int * do_stuff(int ** r, int a, int b) {
  **(r + a) = **(r + a + 1);
  *r[b] = *r[b - 1];
  r[a] = NULL;
  r[b + 1] = NULL;
  return r[a + 1];
}
int main(void) {
  int * x = malloc(2 * sizeof(*x));
  *x = 0;
  *(x + 1) = 1;
  int arr[] = {2, 3};
  int ** q = malloc(4 * sizeof(*q));
  for (int i = 0; i < 4; i++) {
    if (i % 2 == 0) {
      q[i] = &arr[i / 2];
    }
    else {
      q[i] = x + i / 2;
    }
    printf("*q[%d] is %d\n", i, *q[i]);
  }
  do_stuff(q, 0, 2);
  for (int i = 0; i < 4; i++) {
    if (q[i] == NULL) {
      printf("q[%d] is NULL\n", i);
    }
    else {
      printf("q[%d] is %d\n", i, *q[i]);
    }
  }
  free(x);
  free(q);
  return EXIT_SUCCESS;
}
