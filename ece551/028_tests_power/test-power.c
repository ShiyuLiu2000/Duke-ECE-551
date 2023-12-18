#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y) {
  unsigned expected = 1;

  for (unsigned i = 0; i < y; i++) {
    expected *= x;
  }

  if (power(x, y) != expected) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  run_check(1, 1);
  run_check('a', 3);
  run_check(-1, 0);
  run_check(-2, 0);
  run_check('a', 'b');
  run_check(2, 0);
  run_check(2, 3);
  //run_check(3, -1);
  run_check(0, 2);
  //run_check(0, -1);
  //run_check(0, -2);
  run_check(4, 'a');
  run_check(0, 0);

  return EXIT_SUCCESS;
}
