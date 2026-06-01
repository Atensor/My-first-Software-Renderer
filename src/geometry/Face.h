#include <array>

#ifndef FACE_H
#define FACE_H
struct Face {
    std::array<int, 3> vertex_index;
    std::array<int, 3> normal_index;
    std::array<int, 3> texture_coordinate_index;
};

#endif
