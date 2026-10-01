#include "../math/vector/Float3.h"
#include <array>

#ifndef FACE_H
#define FACE_H
struct Face {
	std::array<int, 3> pos_index;
	std::array<int, 3> normal_index;
	// std::array<int, 3> texture_coordinate_index;

	Float3 surface_normal;
};

#endif
