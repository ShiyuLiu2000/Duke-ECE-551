#ifndef __INT_MATRIX_H___
#define __INT_MATRIX_H___

#include <assert.h>

#include <iostream>

#include "IntArray.h"
class IntMatrix {
 private:
  int numRows;
  int numColumns;
  IntArray ** rows;

 public:
  IntMatrix() : numRows(0), numColumns(0), rows(NULL){};  // done
  IntMatrix(int r, int c);                                // done
  IntMatrix(const IntMatrix & rhs);                       // done
  ~IntMatrix();                                           // done
  IntMatrix & operator=(const IntMatrix & rhs);           // done
  int getRows() const { return numRows; };                // done
  int getColumns() const { return numColumns; };          // done
  const IntArray & operator[](int index) const;           // done
  IntArray & operator[](int index);                       // done
  bool operator==(const IntMatrix & rhs) const;           // done
  IntMatrix operator+(const IntMatrix & rhs) const;       // done
};

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs);  // done
#endif
