#include "Matrix4.h"

Matrix4::Matrix4(const std::array<std::array<float, 4>, 4> &values)
    : values{values} {}

Float4 Matrix4::operator*(const Float4 &a) const {
    return Float4{values[0][0] * a.x + values[0][1] * a.y + values[0][2] * a.z +
                      values[0][3] * a.w,
                  values[1][0] * a.x + values[1][1] * a.y + values[1][2] * a.z +
                      values[1][3] * a.w,
                  values[2][0] * a.x + values[2][1] * a.y + values[2][2] * a.z +
                      values[2][3] * a.w,
                  values[3][0] * a.x + values[3][1] * a.y + values[3][2] * a.z +
                      values[3][3] * a.w};
}
