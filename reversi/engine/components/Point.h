#pragma once
#include "includeAll.h"
class Point {
    int x;
    int y;
public:
    Point(int x, int y);

    int getX() const;

    int getY() const;

    bool operator<(const Point &rhs) const;

    bool operator>(const Point &rhs) const;

    bool operator<=(const Point &rhs) const;

    bool operator>=(const Point &rhs) const;

    bool operator==(const Point &rhs) const;

    bool operator!=(const Point &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};

typedef std::vector<Point*> PointsList;
