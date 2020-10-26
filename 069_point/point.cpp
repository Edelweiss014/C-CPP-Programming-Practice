#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "point.hpp"

void Point::move(double dx, double dy) {
    x += dx;
    y += dy;
    return;
}

double Point::distanceFrom(const Point & p) {
    double distance = std::sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    return distance;
}