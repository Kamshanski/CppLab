#include "includeAll.h"
Point::Point(const int x, const int y) : x(x), y(y) {}

bool Point::operator==(const Point &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Point::operator!=(const Point &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os <<'(' << point.x << ", " << point.y << ')';
    return os;
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

bool Point::operator<(const Point &rhs) const {
    if (x < rhs.x)
        return true;
    if (rhs.x < x)
        return false;
    return y < rhs.y;
}

bool Point::operator>(const Point &rhs) const {
    return rhs < *this;
}

bool Point::operator<=(const Point &rhs) const {
    return !(rhs < *this);
}

bool Point::operator>=(const Point &rhs) const {
    return !(*this < rhs);
}
