#include "Transform.h"
#define _USE_MATH_DEFINES
#include <cmath>

Matrix4 Transform::rotate_x(float a) {
    float alpha{a * ((float)M_PI / 180.0f)};
    return Matrix4{std::array<std::array<float, 4>, 4>{
        {{1.0f, 0.0f, 0.0f, 0.0f},
         {0.0f, (float)cos(alpha), (float)sin(alpha), 0.0f},
         {0.0f, (float)-sin(alpha), (float)cos(alpha), 0.0f},
         {0.0f, 0.0f, 0.0f, 1.0f}}}};
}

Matrix4 Transform::rotate_y(float a) {
    float alpha{a * ((float)M_PI / 180.0f)};
    return Matrix4{std::array<std::array<float, 4>, 4>{
        {{(float)cos(alpha), 0.0f, (float)-sin(alpha), 0.0f},
         {0.0f, 1.0f, 0.0f, 0.0f},
         {(float)sin(alpha), 0.0f, (float)cos(alpha), 0.0f},
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
    out.normal = m.inv() * v.normal;
    return out;
}
