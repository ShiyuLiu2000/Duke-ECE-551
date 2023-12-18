#include "IntArray.h"

#include <assert.h>

#include <ostream>

// deep copy (copy constructor does not return anything!!)
IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]()), numElements(rhs.numElements) {
  for (int i = 0; i < rhs.numElements; i++) {
    data[i] = rhs.data[i];
  }
}

// destructor
IntArray::~IntArray() {
  delete[] data;
}

// deep copy (operator = does things in an already existed class!! We should free the memory taken by the old existed left-hand side fields)
IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    delete[] data;
    numElements = rhs.numElements;
    data = new int[numElements]();
    for (int i = 0; i < numElements; i++) {
      data[i] = rhs.data[i];
    }
  }
  return *this;
}

// index operator
const int & IntArray::operator[](int index) const {
  assert(index >= 0 && index < numElements);  // important!! Learn to use assert
  return data[index];
}
int & IntArray::operator[](int index) {
  assert(index >= 0 && index < numElements);
  return data[index];
}

// checks if 2 arrays are the same
bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < numElements; i++) {
    if ((*this)[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

// checks if 2 arrays are NOT the same
bool IntArray::operator!=(const IntArray & rhs) const {
  if (*this == rhs) {
    return false;
  }
  else {
    return true;
  }
}

// overload string insertion to print IntArray
std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.size(); i++) {
    s << rhs[i];
    if (i != rhs.size() - 1) {
      s << ", ";
    }
  }
  s << "}";
  return s;
}
