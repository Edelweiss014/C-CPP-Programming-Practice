#include <cstdio>
#include <cstdlib>

class Point {
private:
    double x;
    double y;
public:
    Point() : x(0.0), y(0.0) {}
    ~Point() {}
    void move(double dx, double dy);
    double distanceFrom(const Point & p);
};
