#include "Float2.h"
#include <cmath>
#include <iostream>

Float2::Float2() : x{0}, y{0} {}

Float2::Float2(float x, float y) : x{x}, y{y} {}

Float2 Float2::operator+(const Float2 &a) const {
    return Float2{x + a.x, y + a.y};
}

Float2 Float2::operator-(const Float2 &a) const {
    return Float2{x - a.x, y - a.y};
}

Float2 Float2::operator*(const Float2 &a) const {
    return Float2{x * a.x, y * a.y};
}

float Float2::dot(const Float2 &a, const Float2 &b) {
    return a.x * b.x + a.y * b.y;
}

float Float2::cross(const Float2 &a, const Float2 &b) {
    return a.x * b.y - a.y * b.x;
}

Float2 Float2::scale(const Float2 &a, float r) {
    return Float2{a.x * r, a.y * r};
}

float Float2::get_length() const { return std::sqrt(x * x + y * y); }

Float2 Float2::normalize() const {
    return Float2::scale(Float2{x, y}, 1.0f / get_length());
}

void Float2::print() const { std::cout << "(" << x << "|" << y << ")"; }
