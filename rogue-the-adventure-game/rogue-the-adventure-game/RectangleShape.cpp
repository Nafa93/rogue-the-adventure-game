#include "RectangleShape.h"

Coordinate RectangleShape::top_right_corner() {
	return Coordinate(origin.x + width - 1, origin.y);
}

Coordinate RectangleShape::top_left_corner() {
	return origin;
}

Coordinate RectangleShape::bottom_right_corner() {
	return Coordinate(origin.x + width - 1, origin.y + height - 1);
}

Coordinate RectangleShape::bottom_left_corner() {
	return Coordinate(origin.x, origin.y + height - 1);
}

Coordinate RectangleShape::get_random_coordinate()
{
	int random_x = rng.generate(top_left_corner().x + 1, top_right_corner().x - 1);
	int random_y = rng.generate(top_left_corner().y + 1, bottom_left_corner().y - 1);
	return Coordinate(random_x, random_y);
}
