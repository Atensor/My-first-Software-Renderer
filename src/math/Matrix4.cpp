#include "Matrix4.h"

Matrix4::Matrix4(const std::array<std::array<float, 4>, 4> &values)
    : values{values} {}

Matrix4::Matrix4()
    : values{std::array<std::array<float, 4>, 4>{{{0.0f, 0.0f, 0.0f, 0.0f},
                                                  {0.0f, 0.0f, 0.0f, 0.0f},
                                                  {0.0f, 0.0f, 0.0f, 0.0f},
                                                  {0.0f, 0.0f, 0.0f, 0.0f}}}} {}

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

float invf(int i, int j, const std::array<std::array<float, 4>, 4> &values) {

    int o = 2 + (j - i);

    i += 4 + o;
    j += 4 - o;

#define e(a, b) values[((i + a) % 4)][((j + b) % 4)]

    float inv =
        +e(+1, -1) * e(+0, +0) * e(-1, +1) + e(+1, +1) * e(+0, -1) * e(-1, +0) +
        e(-1, -1) * e(+1, +0) * e(+0, +1) - e(-1, -1) * e(+0, +0) * e(+1, +1) -
        e(-1, +1) * e(+0, -1) * e(+1, +0) - e(+1, -1) * e(-1, +0) * e(+0, +1);

    return (o % 2) ? inv : -inv;

#undef e
}

// Got the Algorithm from:
// https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
Matrix4 Matrix4::inv() const {
    Matrix4 inv;
    Matrix4 out;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            inv.values[i][j] = invf(i, j, values);

    double D = 0;

    for (int k = 0; k < 4; k++)
        D += values[k][0] * inv.values[0][k];

    if (D == 0)
        return out;

    D = 1.0 / D;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            out.values[i][j] = inv.values[i][j] * D;

    return out;
}
