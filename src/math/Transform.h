#include "matrix/Matrix3x4.h"

#ifndef TRANSFORM_H
#define TRANSFORM_H

struct Transform {

	static Matrix3x4 rotate(const Float3 &rotate);

	static Matrix3x4 rotate_inv(const Float3 &rotate);

	static Matrix3x4 camera_transform(const Float3 &translate,
	                                  const Float3 &rotate);

	static Matrix3x4 object_transform(const Float3 &translate,
	                                  const Float3 &rotate, float scalar);

	static Matrix3x4 translate(const Float3 &a);

	static Matrix3x4 translate_inv(const Float3 &a);

	static Matrix3x4 scale(float scalar);
};

#endif
