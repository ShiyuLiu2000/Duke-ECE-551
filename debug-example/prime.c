#include "prime.h"

#include <stdio.h>
#include <stdlib.h>

int isPrime(unsigned n) {
  if (n <= 1) {
    return 0;
  }
  for (unsigned i = 2; i < n; i++) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}
