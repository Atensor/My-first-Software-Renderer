#include "../vector/Float4.h"
#include <array>

#ifndef MATRIX4_H
#define MATRIX4_H
struct Matrix4 {
	std::array<std::array<float, 4>, 4> values;

	Matrix4(const std::array<std::array<float, 4>, 4> &values)
	    : values{values} {}

	Matrix4()
	    : values{
	          std::array<std::array<float, 4>, 4>{{{0.0f, 0.0f, 0.0f, 0.0f},
			                                       {0.0f, 0.0f, 0.0f, 0.0f},
			                                       {0.0f, 0.0f, 0.0f, 0.0f},
			                                       {0.0f, 0.0f, 0.0f, 0.0f}}}} {
	}

	Float4 operator*(const Float4 &a) const {
		return Float4{values[0][0] * a.x + values[0][1] * a.y +
		                  values[0][2] * a.z + values[0][3] * a.w,
		              values[1][0] * a.x + values[1][1] * a.y +
		                  values[1][2] * a.z + values[1][3] * a.w,
		              values[2][0] * a.x + values[2][1] * a.y +
		                  values[2][2] * a.z + values[2][3] * a.w,
		              values[3][0] * a.x + values[3][1] * a.y +
		                  values[3][2] * a.z + values[3][3] * a.w};
	}

	// Got it from:
	// https://stackoverflow.com/questions/1674005/fast-4x4-matrix-multiplication-in-c
	Matrix4 operator*(const Matrix4 &m) const {
		Matrix4 dest;
		dest.values[0][0] =
		    values[0][0] * m.values[0][0] + values[0][1] * m.values[1][0] +
		    values[0][2] * m.values[2][0] + values[0][3] * m.values[3][0];
		dest.values[0][1] =
		    values[0][0] * m.values[0][1] + values[0][1] * m.values[1][1] +
		    values[0][2] * m.values[2][1] + values[0][3] * m.values[3][1];
		dest.values[0][2] =
		    values[0][0] * m.values[0][2] + values[0][1] * m.values[1][2] +
		    values[0][2] * m.values[2][2] + values[0][3] * m.values[3][2];
		dest.values[0][3] =
		    values[0][0] * m.values[0][3] + values[0][1] * m.values[1][3] +
		    values[0][2] * m.values[2][3] + values[0][3] * m.values[3][3];
		dest.values[1][0] =
		    values[1][0] * m.values[0][0] + values[1][1] * m.values[1][0] +
		    values[1][2] * m.values[2][0] + values[1][3] * m.values[3][0];
		dest.values[1][1] =
		    values[1][0] * m.values[0][1] + values[1][1] * m.values[1][1] +
		    values[1][2] * m.values[2][1] + values[1][3] * m.values[3][1];
		dest.values[1][2] =
		    values[1][0] * m.values[0][2] + values[1][1] * m.values[1][2] +
		    values[1][2] * m.values[2][2] + values[1][3] * m.values[3][2];
		dest.values[1][3] =
		    values[1][0] * m.values[0][3] + values[1][1] * m.values[1][3] +
		    values[1][2] * m.values[2][3] + values[1][3] * m.values[3][3];
		dest.values[2][0] =
		    values[2][0] * m.values[0][0] + values[2][1] * m.values[1][0] +
		    values[2][2] * m.values[2][0] + values[2][3] * m.values[3][0];
		dest.values[2][1] =
		    values[2][0] * m.values[0][1] + values[2][1] * m.values[1][1] +
		    values[2][2] * m.values[2][1] + values[2][3] * m.values[3][1];
		dest.values[2][2] =
		    values[2][0] * m.values[0][2] + values[2][1] * m.values[1][2] +
		    values[2][2] * m.values[2][2] + values[2][3] * m.values[3][2];
		dest.values[2][3] =
		    values[2][0] * m.values[0][3] + values[2][1] * m.values[1][3] +
		    values[2][2] * m.values[2][3] + values[2][3] * m.values[3][3];
		dest.values[3][0] =
		    values[3][0] * m.values[0][0] + values[3][1] * m.values[1][0] +
		    values[3][2] * m.values[2][0] + values[3][3] * m.values[3][0];
		dest.values[3][1] =
		    values[3][0] * m.values[0][1] + values[3][1] * m.values[1][1] +
		    values[3][2] * m.values[2][1] + values[3][3] * m.values[3][1];
		dest.values[3][2] =
		    values[3][0] * m.values[0][2] + values[3][1] * m.values[1][2] +
		    values[3][2] * m.values[2][2] + values[3][3] * m.values[3][2];
		dest.values[3][3] =
		    values[3][0] * m.values[0][3] + values[3][1] * m.values[1][3] +
		    values[3][2] * m.values[2][3] + values[3][3] * m.values[3][3];

		return dest;
	}
};

#endif
