#include "IntMatrix.h"

// constructor overloading
// IMPORTANT: when `new` a list of object we can only use default constructor!!
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int row = 0; row < numRows; row++) {
    rows[row] = new IntArray(numColumns);
  }
}

// deep copy, copy constructor
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns), rows(new IntArray *[rhs.numRows]) {
  for (int row = 0; row < numRows; row++) {
    rows[row] = new IntArray(numColumns);
    for (int column = 0; column < numColumns; column++) {
      (*rows[row])[column] = (*rhs.rows[row])[column];
    }
  }
}

// destructor
IntMatrix::~IntMatrix() {
  for (int row = 0; row < numRows; row++) {
    delete rows[row];
  }
  delete[] rows;
}

// deep copy, copy assignment operator
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    // delete the old rows
    for (int row = 0; row < numRows; row++) {
      delete rows[row];
    }
    delete[] rows;
    // assign fields to new value
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new IntArray *[numRows];
    for (int row = 0; row < numRows; row++) {
      rows[row] = new IntArray(numColumns);
      for (int column = 0; column < numColumns; column++) {
        (*rows[row])[column] = (*rhs.rows[row])[column];
      }
    }
  }
  return *this;
}

// read-only index operator
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

// read and write index operator
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

// compare two matrices for equality
bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
    return false;
  }
  for (int row = 0; row < numRows; row++) {
    for (int column = 0; column < numColumns; column++) {
      if ((*rows[row])[column] != (*rhs.rows[row])[column]) {
        return false;
      }
    }
  }
  return true;
}

// matrix addition
IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows);
  assert(numColumns == rhs.numColumns);
  IntMatrix ans = IntMatrix(numRows, numColumns);
  for (int row = 0; row < numRows; row++) {
    for (int column = 0; column < numColumns; column++) {
      (*ans.rows[row])[column] = (*rows[row])[column] + (*rhs.rows[row])[column];
    }
  }
  return ans;
}

// print the 2D matrix
std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int row = 0; row < rhs.getRows(); row++) {
    s << rhs[row];
    if (row != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
