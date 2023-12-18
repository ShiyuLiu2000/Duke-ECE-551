#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */

using std::sqrt;

double Vector2D::getMagnitude() const {
  return sqrt(x * x + y * y);
}  // we use const because we don't want the function to modify object members

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D ans;
  ans.x = x + rhs.x;
  ans.y = y + rhs.y;
  return ans;
}  // use const because + does not mess up with original lvalue and rvalue

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  return x * rhs.x + y * rhs.y;
}

void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}
