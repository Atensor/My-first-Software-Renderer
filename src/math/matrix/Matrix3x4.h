#include "../vector/Float3.h"
#include <array>

#ifndef MATRIX4_H
#define MATRIX4_H
struct Matrix3x4 {
	std::array<float, 12> values;

	Matrix3x4(const std::array<float, 12> &values) : values{values} {}

	Matrix3x4()
	    : values{std::array<float, 12>{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f}} {}

	Float3 operator*(const Float3 &a) const {
		return Float3{
		    values[0] * a.x + values[1] * a.y + values[2] * a.z + values[3],
		    values[4] * a.x + values[5] * a.y + values[6] * a.z + values[7],
		    values[8] * a.x + values[9] * a.y + values[10] * a.z + values[11]};
	}

	// Got it from and rewritten by AI:
	// https://stackoverflow.com/questions/1674005/fast-4x4-matrix-multiplication-in-c
	Matrix3x4 operator*(const Matrix3x4 &m) const {
		Matrix3x4 dest;
		dest.values[0] = values[0] * m.values[0] + values[1] * m.values[4] +
		                 values[2] * m.values[8];
		dest.values[1] = values[0] * m.values[1] + values[1] * m.values[5] +
		                 values[2] * m.values[9];
		dest.values[2] = values[0] * m.values[2] + values[1] * m.values[6] +
		                 values[2] * m.values[10];
		dest.values[3] = values[0] * m.values[3] + values[1] * m.values[7] +
		                 values[2] * m.values[11] + values[3];
		dest.values[4] = values[4] * m.values[0] + values[5] * m.values[4] +
		                 values[6] * m.values[8];
		dest.values[5] = values[4] * m.values[1] + values[5] * m.values[5] +
		                 values[6] * m.values[9];
		dest.values[6] = values[4] * m.values[2] + values[5] * m.values[6] +
		                 values[6] * m.values[10];
		dest.values[7] = values[4] * m.values[3] + values[5] * m.values[7] +
		                 values[6] * m.values[11] + values[7];
		dest.values[8] = values[8] * m.values[0] + values[9] * m.values[4] +
		                 values[10] * m.values[8];
		dest.values[9] = values[8] * m.values[1] + values[9] * m.values[5] +
		                 values[10] * m.values[9];
		dest.values[10] = values[8] * m.values[2] + values[9] * m.values[6] +
		                  values[10] * m.values[10];
		dest.values[11] = values[8] * m.values[3] + values[9] * m.values[7] +
		                  values[10] * m.values[11] + values[11];
		return dest;
	}
};

#endif
