#include "Float4.h"
#include <array>

#ifndef MATRIX4_H
#define MATRIX4_H
struct Matrix4 {
    Matrix4();
    Matrix4(const std::array<std::array<float, 4>, 4> &values);

    std::array<std::array<float, 4>, 4> values;

    Float4 operator*(const Float4 &a) const;

    Matrix4 inv() const;
};

#endif
