#ifndef __POINT_H__
#define __POINT_H__

class Point {
 private:
  double x;
  double y;

 public:
  Point(void) : x(0), y(0){};
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};

#endif
