#include "sumfactors.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  assert(sumPrimeFactors(42) == 12);
  assert(sumPrimeFactors(10) == 7);
  assert(sumPrimeFactors(12) == 7);
  assert(sumPrimeFactors(1) == 0);
  assert(sumPrimeFactors(0) == 0);
  return EXIT_SUCCESS;
}
