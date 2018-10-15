#include "circle.h"

#include <cmath>
using namespace std;
void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double angle(double a, double b, double c) {
  return acos((a * a + b * b - c * c) / (2.0 * a * b));
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.distanceFrom(otherCircle.center);
  double r1 = this->radius;
  double r2 = otherCircle.radius;

  if (r1 + r2 <= d) {
    return 0.0;
  }
  if (r2 > r1) {
    double temp = r2;
    r2 = r1;
    r1 = temp;
  }

  if (d <= r1 - r2) {
    return M_PI * r2 * r2;
  }

  double theta1, theta2;
  theta1 = 2.0 * angle(r1, d, r2);
  theta2 = 2.0 * angle(r2, d, r1);
  return 0.5 * r1 * r1 * (theta1 - sin(theta1)) + 0.5 * r2 * r2 * (theta2 - sin(theta2));
}
