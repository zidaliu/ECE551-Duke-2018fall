#include "point.h"

#include <cmath>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double distance_x = x - p.x;

  double distance_y = y - p.y;

  double temp_x = distance_x * distance_x;
  double temp_y = distance_y * distance_y;
  double distance = sqrt(temp_x + temp_y);
  return distance;
}
