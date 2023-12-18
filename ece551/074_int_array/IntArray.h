#ifndef __INT_ARRAY__H__
#define __INT_ARRAY__H__
#include <cstdlib>
#include <ostream>

class IntArray {
 private:
  int * data;
  int numElements;

 public:
  IntArray() : data(NULL), numElements(0){};               // done
  IntArray(int n) : data(new int[n]()), numElements(n){};  // done
  IntArray(const IntArray & rhs);                          // done
  IntArray & operator=(const IntArray & rhs);              // done
  int & operator[](int index);                             // done
  const int & operator[](int index) const;                 // done
  int size() const { return numElements; };                // done
  bool operator==(const IntArray & rhs) const;             // done
  bool operator!=(const IntArray & rhs) const;             // done
  ~IntArray();                                             // done
};

std::ostream & operator<<(std::ostream & s, const IntArray & rhs);  // done

#endif
