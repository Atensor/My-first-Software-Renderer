#include "Float3.h"
#ifndef FLOAT4_H
#define FLOAT4_H

struct Float4 {
	union {
		struct {
			float x, y, z, w;
		};
		struct {
			float r, g, b, a;
		};
	};

	Float4() : x{0}, y{0}, z{0}, w{0} {}

	Float4(float x, float y, float z, float w) : x{x}, y{y}, z{z}, w{w} {}

	Float4(const Float3 &a, float w) : x{a.x}, y{a.y}, z{a.z}, w{w} {}

	Float4 operator+(const Float4 &a) const {
		return Float4{x + a.x, y + a.y, z + a.z, a.w};
	};

	Float4 operator-(const Float4 &a) const {
		return Float4{x - a.x, y - a.y, z - a.z, w + a.w};
	};

	static float dot(const Float4 &a, const Float4 &b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	Float4 operator*(const Float4 &a) const {
		return Float4{x * a.x, y * a.y, z * a.z, w * a.w};
	}

	static Float4 scale(const Float4 &a, float r) {
		return Float4{a.x * r, a.y * r, a.z * r, a.w};
	}

	float get_length() const { return std::sqrt(x * x + y * y + z * z); }

	Float4 normalize() const {
		return scale(Float4(x, y, z, w), 1.0f / get_length());
	}

	Float2 xy() const { return Float2{x, y}; }

	Float3 xyz() const { return Float3{x, y, z}; }
};

#endif
