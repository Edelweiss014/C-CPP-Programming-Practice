#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "circle.hpp"

const double PI = 3.141592653589793238463;

double min_of_2 (double x, double y) {
    if (x < y) return x;
    else return y;
}

void Circle::move (double dx, double dy) {
    center.move(dx, dy);
    return;
}

double Circle::intersectionArea(const Circle & otherCircle) {
    double d = center.distanceFrom(otherCircle.center);
    if (d >= radius + otherCircle.radius) {
        return 0.0;
    }
    if (d <= std::abs(radius - otherCircle.radius)) {
        double thisR = min_of_2(radius, otherCircle.radius);
        return PI * thisR * thisR;
    }
    double area = 0.0;
    double d_1 = (radius * radius - otherCircle.radius * otherCircle.radius + d * d) / (2 * d);
    double d_2 = (otherCircle.radius * otherCircle.radius - radius * radius + d * d) / (2 * d);
    double area_1 = radius * radius * std::acos(d_1 / radius) - d_1 * std::sqrt(radius * radius - d_1 * d_1);
    double area_2 = otherCircle.radius * otherCircle.radius * std::acos(d_2 / otherCircle.radius)
         - d_2 * std::sqrt(otherCircle.radius * otherCircle.radius - d_2 * d_2);
    area = area_1 + area_2;
    return area;
}