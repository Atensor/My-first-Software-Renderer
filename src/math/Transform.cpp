#include "Transform.h"
#include <cmath>

Matrix4 Transform::rotate_x(float a) {
    return Matrix4{std::array<std::array<float, 4>, 4>{
        {{1.0f, 0.0f, 0.0f, 0.0f},
         {0.0f, (float)cos(a), (float)sin(a), 0.0f},
         {0.0f, (float)-sin(a), (float)cos(a), 0.0f},
         {0.0f, 0.0f, 0.0f, 1.0f}}}};
}

Matrix4 Transform::rotate_y(float a) {
    return Matrix4{std::array<std::array<float, 4>, 4>{
        {{(float)cos(a), 0.0f, (float)-sin(a), 0.0f},
         {0.0f, 1.0f, 0.0f, 0.0f},
         {(float)sin(a), 0.0f, (float)cos(a), 0.0f},
         {0.0f, 0.0f, 0.0f, 1.0f}}}};
}

Matrix4 Transform::translate(const Float4 &a) {
    return Matrix4{
        std::array<std::array<float, 4>, 4>{{{1.0f, 0.0f, 0.0f, a.x},
                                             {0.0f, 1.0f, 0.0f, a.y},
                                             {0.0f, 0.0f, 1.0f, a.z},
                                             {0.0f, 0.0f, 0.0f, 1.0f}}}};
}

Vertex Transform::transform(const Vertex &v, const Matrix4 &m) {
    Vertex out{v};
    out.pos = m * v.pos;
    return out;
}
