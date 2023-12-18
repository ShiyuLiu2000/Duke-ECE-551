#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }

  size_t ans = 1;
  size_t cur = 1;

  for (int i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      cur += 1;
      if (cur > ans) {
        ans = cur;
      }
    }
    else {
      cur = 1;
    }
  }

  return ans;
}
