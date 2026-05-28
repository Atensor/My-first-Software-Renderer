#include "Float4.h"
#include <cmath>
#include <iostream>

Float4::Float4() : x{0}, y{0}, z{0}, w{0} {}

Float4::Float4(float x, float y, float z, float w) : x{x}, y{y}, z{z}, w{w} {}

Float4::Float4(const Float3 &a, float w) : x{a.x}, y{a.y}, z{a.z}, w{w} {}

Float4 Float4::operator+(const Float4 &a) const {
    return Float4{x + a.x, y + a.y, z + a.z, w + a.w};
};

Float4 Float4::operator-(const Float4 &a) const {
    return Float4{x - a.x, y - a.y, z - a.z, w + a.w};
};

float Float4::dot(const Float4 &a, const Float4 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Float4 Float4::operator*(const Float4 &a) const {
    return Float4{x * a.x, y * a.y, z * a.z, w * a.w};
}

Float4 Float4::scale(const Float4 &a, float r) {
    return Float4{a.x * r, a.y * r, a.z * r, a.w};
}

float Float4::get_length() const { return std::sqrt(x * x + y * y + z * z); }

Float4 Float4::normalize() const {
    return Float4::scale(Float4(x, y, z, w), 1.0f / get_length());
}

Float2 Float4::xy() const { return Float2{x, y}; }
Float3 Float4::xyz() const { return Float3{x, y, z}; }

Float4 Float4::alpha_composite(const Float4 &color) {
    return Float4{Float3::scale(color.xyz(), color.a) +
                      Float3::scale(xyz(), 1.0f - color.a),
                  color.a + a * (1.0f - color.a)};
}
void Float4::print() {
    std::cout << "(" << x << "|" << y << "|" << z << "|" << w << ")";
}
