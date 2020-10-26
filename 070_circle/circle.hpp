#include <cstdio>
#include <cstdlib>
#include "point.hpp"

class Circle {
private:
    Point center;
    const double radius;
public:
    Circle() : center(Point()), radius(0) {}
    Circle(Point x, const double r) : center(x), radius(r) {}
    void move (double dx, double dy);
    double intersectionArea(const Circle & otherCircle);
    ~Circle() {}
};
