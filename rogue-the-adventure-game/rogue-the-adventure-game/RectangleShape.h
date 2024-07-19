#pragma once

#include "Coordinate.h"
#include "RandomNumberGenerator.h"

class RectangleShape
{
public:
    RectangleShape(Coordinate origin, int height, int width) : origin(origin), height(height), width(width), rng(RandomNumberGenerator()) {};
    RectangleShape() : origin(Coordinate(0, 0)), height(0), width(0), rng(RandomNumberGenerator()) {};
    Coordinate origin;
    int height;
    int width;
    Coordinate top_right_corner();
    Coordinate top_left_corner();
    Coordinate bottom_right_corner();
    Coordinate bottom_left_corner();
    Coordinate get_random_coordinate();
private:
    RandomNumberGenerator rng;
};