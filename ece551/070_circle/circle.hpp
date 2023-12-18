/*
  Below is the code written by myself
*/

/*
#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(Point center, double radius) : center(center), radius(radius){};
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle) const;
};

#endif
*/

/* 
   Below is the code written by ChatGPT 
*/
#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(const Point & c, double r) : center(c), radius(r) {}

  void move(double dx, double dy) { center.move(dx, dy); }

  double intersectionArea(const Circle & otherCircle);
};

#endif  // CIRCLE_HPP
