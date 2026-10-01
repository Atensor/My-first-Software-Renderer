#include "Float2.h"
#ifndef FLOAT3_H
#define FLOAT3_H

struct Float3 {
	union {
		struct {
			float x, y, z;
		};
		struct {
			float r, g, b;
		};
	};

	Float3() : x{0}, y{0}, z{0} {}

	Float3(float x, float y, float z) : x{x}, y{y}, z{z} {}

	Float3 operator+(const Float3 &a) const {
		return Float3{x + a.x, y + a.y, z + a.z};
	};

	Float3 operator-(const Float3 &a) const {
		return Float3{x - a.x, y - a.y, z - a.z};
	};

	static float dot(const Float3 &a, const Float3 &b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	Float3 operator*(const Float3 &a) const {
		return Float3{x * a.x, y * a.y, z * a.z};
	}

	static Float3 cross(const Float3 &a, const Float3 &b) {
		return Float3{a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
		              a.x * b.y - a.y * b.x};
	}

	static Float3 scale(const Float3 &a, float r) {
		return Float3{a.x * r, a.y * r, a.z * r};
	}

	float get_length() const { return std::sqrt(x * x + y * y + z * z); }

	Float3 normalize() const {
		return scale(Float3(x, y, z), 1.0f / get_length());
	}

	Float2 xy() const { return Float2{x, y}; }
};

#endif
