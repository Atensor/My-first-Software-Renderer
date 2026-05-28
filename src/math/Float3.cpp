#include "Float3.h"
#include <cmath>
#include <iostream>

Float3::Float3() : x{0}, y{0}, z{0} {}

Float3::Float3(float x, float y, float z) : x{x}, y{y}, z{z} {}

Float3 Float3::operator+(const Float3 &a) const {
    return Float3{x + a.x, y + a.y, z + a.z};
};

Float3 Float3::operator-(const Float3 &a) const {
    return Float3{x - a.x, y - a.y, z - a.z};
};

float Float3::dot(const Float3 &a, const Float3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Float3 Float3::operator*(const Float3 &a) const {
    return Float3{x * a.x, y * a.y, z * a.z};
}

Float3 Float3::cross(const Float3 &a, const Float3 &b) {
    return Float3{a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                  a.x * b.y - a.y * b.x};
}

Float3 Float3::scale(const Float3 &a, float r) {
    return Float3{a.x * r, a.y * r, a.z * r};
}

float Float3::get_length() const { return std::sqrt(x * x + y * y + z * z); }

Float3 Float3::normalize() const {
    return Float3::scale(Float3(x, y, z), 1.0f / get_length());
}

Float2 Float3::xy() const { return Float2{x, y}; }

void Float3::print() { std::cout << "(" << x << "|" << y << "|" << z << ")"; }
