#include "Face.h"
#include <vector>

#ifndef MESH_H
#define MESH_H

struct Mesh {
    std::vector<Float4> vertices;
    std::vector<Float4> normals;
    std::vector<Float2> texture_coordinates;

    std::vector<Face> faces;
};

#endif
