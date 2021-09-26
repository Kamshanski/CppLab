#pragma once

#include "includeAll.h"
const int FIELD_SIZE = 8;

const std::array<Point, 8> POSSIBLE_DIRECTIONS = {
       Point(+1, +1),  Point(+1, 0), Point(+1, -1),
       Point( 0, +1),                      Point( 0, -1),
       Point(-1, +1),  Point(-1, 0), Point(-1, -1),
};

