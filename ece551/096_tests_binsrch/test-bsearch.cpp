#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

// the prototype function we bring to test
// just declare it as existing. The implementations is not my concern for now
int binarySearchForZero(Function<int, int> * f, int low, int high);

// helper class to check the right number of invocations
class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

// tester function 1: f(x) = sin(x)
class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

// tester function 2: f(x) = 3x-8
class LinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 3 * arg - 8; }
};

// tester function 3: f(x) = -1
class NegConst : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg * 0 - 1; }
};

// tester function 4: f(x) = 1
class PosConst : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg * 0 + 1; }
};

// tester function 5: f(x) = x-1
class TrickyLinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg - 1; }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int remaining;
  if (high > low) {
    remaining = log(high - low) / log(2) + 1;
  }
  else {
    remaining = 1;
  }
  // we wrap f into counter, and pass counter to binarySearchForZero to do calculation while checking times of invocations
  CountedIntFn counter(remaining, f, mesg);
  int ans = binarySearchForZero(&counter, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "Expected %d but got %d while calling %s\n", expected_ans, ans, mesg);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  SinFunction sinFunction;
  LinFunction linFunction;
  NegConst negConst;
  PosConst posConst;
  TrickyLinFunction trickyFunction;

  // testing sin function f(x) = sin(x)
  check(&sinFunction, 0, 150000, 52359, "f(x) = sin(x)");

  // testing linear function f(x) = 3x-8
  check(&linFunction, 0, 0, 0, "Linear func [0, 0)");
  check(&linFunction, 0, 2, 1, "Linear func [0, 2)");
  check(&linFunction, 0, 3, 2, "Linear func [0, 3)");
  check(&linFunction, 2, 3, 2, "Linear func [2, 3)");
  check(&linFunction, 0, 4, 2, "Linear func [0, 4)");
  check(&linFunction, 3, 5, 3, "Linear func [3, 5)");

  // testing negative constant function f(x) = -1
  check(&negConst, 0, 0, 0, "Neg constant func [0, 0)");
  check(&negConst, 0, 2, 1, "Neg constant func [0, 2)");

  // testing positive constant function f(x) = 1
  check(&posConst, 0, 0, 0, "Pos conatant func [0, 0)");
  check(&posConst, 0, 2, 0, "Pos constant func [0, 2)");

  // testing off-by-one linear function f(x) = x-1
  check(&trickyFunction, 0, 4, 1, "Tricky linear func [0, 4)");

  return EXIT_SUCCESS;
}
