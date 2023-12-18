/*
  Below is the code written by myself
*/

/*
#include "circle.hpp"

#include <cmath>

using std::sqrt;

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.distanceFrom(otherCircle.center);
  const double & r1 = radius;
  const double & r2 = otherCircle.radius;
  double d1 = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
  double d2 = (r2 * r2 - r1 * r1 + d * d) / (2 * d);
  double ans = r1 * r1 * acos(d1 / r1) - d1 * sqrt(r1 * r1 - d1 * d1) +
               r2 * r2 * acos(d2 / r2) - d2 * sqrt(2 * r2 - d2 * d2);
  return ans;
}
*/

/* 
   Below is the code written by ChatGPT 
*/
#include <algorithm>
#include <cmath>

#include "circle.hpp"

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.distanceFrom(otherCircle.center);
  double r1 = radius;
  double r2 = otherCircle.radius;

  if (d >= r1 + r2) {
    // circles are separate
    return 0.0;
  }
  else if (d <= std::abs(r1 - r2)) {
    // one circle is inside the other
    return M_PI * std::min(r1, r2) * std::min(r1, r2);
  }
  else {
    // partial overlap
    double a1 = r1 * r1 * std::acos((d * d + r1 * r1 - r2 * r2) / (2 * d * r1));
    double a2 = r2 * r2 * std::acos((d * d + r2 * r2 - r1 * r1) / (2 * d * r2));
    double a3 =
        0.5 * std::sqrt((-d + r1 - r2) * (-d - r1 + r2) * (-d + r1 + r2) * (d + r1 + r2));
    return a1 + a2 - a3;
  }
}
