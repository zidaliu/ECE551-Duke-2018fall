#include "circle.h"

#include <stdio.h>

#include <cmath>
using namespace std;

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double distance = center.distanceFrom(otherCircle.center);
  printf("distance = %f", distance);
  double r1 = this->radius;
  double r2 = otherCircle.radius;
  if (r1 + r2 <= distance) {
    return 0.0;
  }

  if (r1 < r2) {
    double temp = r1;
    r1 = r2;
    r2 = temp;
  }

  if (distance <= r1 - r2) {
    return r2 * r2 * M_PI;
  }

  double sector_r1 = 0;
  double sector_r2 = 0;
  double p = (r1 + r2 + distance) / 2;
  double trangle_S = sqrt(p * (p - r1) * (p - r2) * (p - distance));
  printf("trangle_s = %f", trangle_S);
  double heigh = 2 * trangle_S / distance;

  if (distance >= r1 && distance >= r2) {
    sector_r1 = M_PI * r1 * heigh / 2;
    printf("sector_r1 = %f", sector_r1);
    sector_r2 = M_PI * r2 * heigh / 2;
    printf("sector_r2 = %f", sector_r2);
    printf("field = %f\n", sector_r1 + sector_r2 - 2 * trangle_S);
    return sector_r1 + sector_r2 - 2 * trangle_S;
  }

  if (distance < r1 && (distance > r2)) {
    sector_r1 = M_PI * r1 * heigh / 2;
    printf("sector_r1 = %f", sector_r1);
    sector_r2 = r2 * r2 * M_PI - M_PI * r2 * heigh / 2;
    printf("sector_r2 = %f", sector_r2);
    printf("field = %f\n", sector_r1 + sector_r2 - 2 * trangle_S);
    return sector_r1 + sector_r2 - 2 * trangle_S;
  }

  if (distance < r2) {
    sector_r1 = r1 * r1 * M_PI - M_PI * r1 * heigh / 2;
    printf("sector_r1 = %f", sector_r1);
    sector_r2 = r2 * r2 * M_PI - M_PI * r2 * heigh / 2;
    printf("sector_r2 = %f", sector_r2);
    printf("field = %f\n", sector_r1 + sector_r2 - 2 * trangle_S);
    return sector_r1 + sector_r2 - 2 * trangle_S;
  }
  return 0;
}
