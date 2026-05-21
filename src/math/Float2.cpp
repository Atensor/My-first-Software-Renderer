#include "Float2.h"
#include <iostream>

Float2::Float2() : x{0}, y{0} {}

Float2::Float2(float x, float y) : x{x}, y{y} {}

Float2 Float2::add(const Float2 &a, const Float2 &b) {
    return Float2{a.x + b.x, a.y + b.y};
}

Float2 Float2::subtract(const Float2 &a, const Float2 &b) {
    return Float2{a.x - b.x, a.y - b.y};
}

float Float2::dot(const Float2 &a, const Float2 &b) {
    return a.x * b.x + a.y * b.y;
}

float Float2::cross(const Float2 &a, const Float2 &b) {
    return a.x * b.y - a.y * b.x;
}

void Float2::print() const { std::cout << "(" << x << "|" << y << ")"; }
