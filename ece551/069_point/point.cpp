#include "point.hpp"

#include <cmath>

using std::sqrt;

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double x_diff = x - p.x;
  double y_diff = y - p.y;
  double ans = sqrt(x_diff * x_diff + y_diff * y_diff);
  return ans;
}
