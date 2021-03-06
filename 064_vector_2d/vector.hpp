#include <cstdio>
#include <cstdlib>
#include <cmath>

class Vector2D {
    private:
        double x;
        double y;
    public:
        void initVector(double init_x, double init_y) {
            x = init_x;
            y = init_y;
        }
        double getMagnitude() const {
            return std::sqrt(x * x + y * y);
        }
        Vector2D operator+ (const Vector2D & rhs) const {
            Vector2D result;
            result.x = this->x + rhs.x;
            result.y = this->y + rhs.y;
            return result;
        }
        Vector2D & operator+=(const Vector2D & rhs) {
            this->x += rhs.x; 
            this->y += rhs.y;
            return *this;
        }
        double dot(const Vector2D & rhs) const {
            return this->x * rhs.x + this->y * rhs.y;
        }
        void print() const {
            printf("<%.2f, %.2f>", this->x, this->y);
        }
};