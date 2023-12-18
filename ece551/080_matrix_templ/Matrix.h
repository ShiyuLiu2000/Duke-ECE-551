#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  // default constructor
  Matrix() : numRows(0), numColumns(0), rows(0, std::vector<T>()) {}
  // overloaded consturctor
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(r, std::vector<T>(c)) {}
  // copy constructor
  Matrix(const Matrix<T> & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(rhs.numRows, std::vector<T>(rhs.numColumns)) {
    for (int row = 0; row < numRows; row++) {
      rows[row] = rhs.rows[row];  // using vector's built-in overloaded = operator
    }
  }
  // destructor
  // std::vectors can take good take of themselves
  ~Matrix(){};
  // copy assignment constructor
  Matrix<T> & operator=(const Matrix<T> & rhs) {
    if (this != &rhs) {
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      // std::vector's overloaded = operator can take good care of the memory it's using
      // so that we don't need to explicitly delete[] like other newed arrays
      rows = rhs.rows;
    }
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }
  bool operator==(const Matrix<T> & rhs) const {
    if (numRows != rhs.numRows) {
      return false;
    }
    else if (numColumns != rhs.numColumns) {
      return false;
    }
    else if (!(rows == rhs.rows)) {
      return false;
    }
    else {
      return true;
    }
  }
  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert(numRows == rhs.numRows);
    assert(numColumns == rhs.numColumns);
    Matrix<T> ans = Matrix<T>(numRows, numColumns);
    for (int row = 0; row < numRows; row++) {
      for (int column = 0; column < numColumns; column++) {
        ans.rows[row][column] = rows[row][column] + rhs.rows[row][column];
      }
    }
    return ans;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int row = 0; row < rhs.getRows(); row++) {
    for (int column = 0; column < rhs.getColumns(); column++) {
      if (column == 0) {
        s << "{";
      }
      s << rhs[row][column];
      if (column != rhs.getColumns() - 1) {
        s << ", ";
      }
      else {
        s << "}";
      }
    }
    if (row != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}

#endif
