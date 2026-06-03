#include "../structs/Vertex.h"
#include "matrix/Matrix4.h"

#ifndef TRANSFORM_H
#define TRANSFORM_H

struct Transform {

    static Matrix4 rotate_x(float alpha);

    static Matrix4 rotate_y(float alpha);

    static Matrix4 translate(const Float4 &a);

    static Matrix4 scale(float scalar);

    static Vertex transform(const Vertex &v, const Matrix4 &translate,
                            const Matrix4 &rotation, const Matrix4 &scale);

    static Vertex transform(const Vertex &v, const Matrix4 &translate,
                            const Matrix4 &rotation);
};

#endif
