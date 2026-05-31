#include "../math/vector/Float4.h"

#ifndef VERTEX_H
#define VERTEX_H
struct Vertex {
    Float4 pos;
    Float4 normal;
    Float4 color;

    float light;
};
#endif
