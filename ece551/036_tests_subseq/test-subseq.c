#include <stdio.h>
#include <stdlib.h>

// claim function prototype
size_t maxSeq(int * array, size_t n);

// helper function
void run_check(int * array, size_t n, size_t expected) {
  // test if the function meets the expected output
  if (maxSeq(array, n) != expected) {
    printf("error");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array1[1] = {1};
  int array2[3] = {1, 2, 3};
  int array3[5] = {1, 1, 2, 1, -1};
  int array4[4] = {1, -1, 1, -2};
  int array5[13] = {1, 1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 1, 2};
  int array6[2] = {3, 3};
  int array7[2] = {3, 2};
  int array8[1] = {0};
  int array9[1] = {-10};
  int array10[7] = {1, 2, 3, 1, 2, 4, 6};
  int array11[6] = {5, 4, 3, 4, 2, 1};
  int array12[5] = {-3, -2, 0, -2, -1};
  int array13[9] = {2, 3, 3, 10, 12, 13, 7, 8, 9};
  int array14[5] = {-4, -2, 0, -1, 2};

  run_check(NULL, 0, 0);
  run_check(array1, 1, 1);
  run_check(array2, 3, 3);
  run_check(array3, 5, 2);
  run_check(array4, 4, 2);
  run_check(array5, 13, 4);
  run_check(array6, 2, 1);
  run_check(array7, 2, 1);
  run_check(array8, 1, 1);
  run_check(array9, 1, 1);
  run_check(array10, 7, 4);
  run_check(array11, 6, 2);
  run_check(array12, 5, 3);
  run_check(array13, 9, 4);
  run_check(array14, 5, 3);

  return EXIT_SUCCESS;
}
