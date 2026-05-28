#include "../structs/Vertex.h"
#include "Matrix4.h"

#ifndef TRANSFORM_H
#define TRANSFORM_H

struct Transform {

    static Matrix4 rotate_x(float alpha);

    static Matrix4 rotate_y(float alpha);

    static Matrix4 translate(const Float4 &a);

    static Vertex transform(const Vertex &v, const Matrix4 &m);
};

#endif
