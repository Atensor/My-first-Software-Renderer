#include <cmath>
#ifndef FLOAT2_H
#define FLOAT2_H

struct Float2 {
	float x;
	float y;

	Float2() : x{0}, y{0} {}

	Float2(float x, float y) : x{x}, y{y} {}

	Float2 operator+(const Float2 &a) const { return Float2{x + a.x, y + a.y}; }

	Float2 operator-(const Float2 &a) const { return Float2{x - a.x, y - a.y}; }

	Float2 operator*(const Float2 &a) const { return Float2{x * a.x, y * a.y}; }

	static float dot(const Float2 &a, const Float2 &b) {
		return a.x * b.x + a.y * b.y;
	}

	static float cross(const Float2 &a, const Float2 &b) {
		return a.x * b.y - a.y * b.x;
	}

	static Float2 scale(const Float2 &a, float r) {
		return Float2{a.x * r, a.y * r};
	}

	float get_length() const { return std::sqrt(x * x + y * y); }

	Float2 normalize() const {
		return Float2::scale(Float2{x, y}, 1.0f / get_length());
	}
};

#endif
