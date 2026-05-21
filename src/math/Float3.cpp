#include "Float3.h"
#include <iostream>

Float3::Float3() : x{0}, y{0}, z{0} {}

Float3::Float3(float x, float y, float z) : x{x}, y{y}, z{z} {}

Float3 Float3::add(const Float3 &a, const Float3 &b) {
    return Float3{a.x + b.x, a.y + b.y, a.z + b.z};
};

Float3 Float3::subtract(const Float3 &a, const Float3 &b) {
    return Float3{a.x - b.x, a.y - b.y, a.z - b.z};
};

float Float3::dot(const Float3 &a, const Float3, Float3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Float3 Float3::cross(const Float3 &a, const Float3, Float3 b) {
    return Float3{a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                  a.x * b.y - a.y * b.x};
}

void Float3::print() { std::cout << "(" << x << "|" << y << "|" << z << ")"; }
