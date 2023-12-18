#include "sumfactors.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/** This computes the sum
 * of the prime factorization of n.
 * For example, 
 * 42 = 2 * 3 * 7, so sumPrimeFactors(42) = 2 + 3 + 7 = 12.
 * 10 = 2 * 5 , so sumPrimeFactors(10)=  2 + 5 = 7.
 * 12 = 2 * 2 * 3, so sumPrimeFactors(12)= 2 + 2 +3 = 7.
 */
unsigned sumPrimeFactors(unsigned n) {
  unsigned ans = 0;
  unsigned div = 2;
  while (n > 1) {
    if (n % div == 0) {
      ans = ans + div;
      n = n / div;
    }
    div = div + 1;
  }
  return ans;
}
