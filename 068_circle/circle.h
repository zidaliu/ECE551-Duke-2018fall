#include "point.h"

class Circle
{
 private:
  Point center;
  const double radius;

 public:
  Circle(Point center_in, double radius_in) : center(center_in), radius(radius_in) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
