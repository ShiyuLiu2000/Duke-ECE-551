#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (high <= low) {
    return low;
  }
  int mid = (high + low) / 2;
  if (mid == low) {
    return low;
  }
  int ans = f->invoke(mid);
  if (ans == 0) {
    return mid;
  }
  else if (ans > 0) {
    high = mid;
  }
  else {
    low = mid;
  }
  return binarySearchForZero(f, low, high);
}
