#include "../structs/Vertex.h"
#include "matrix/Matrix4.h"

#ifndef TRANSFORM_H
#define TRANSFORM_H

struct Transform {

	static Matrix4 rotate(const Float3 &rotate);

	static Matrix4 rotate_inv(const Float3 &rotate);

	static Matrix4 camera_transform(const Float4 &translate,
	                                const Float3 &rotate);

	static Matrix4 object_transform(const Float4 &translate,
	                                const Float3 &rotate, float scalar);

	static Matrix4 translate(const Float4 &a);

	static Matrix4 translate_inv(const Float4 &a);

	static Matrix4 scale(float scalar);

	static Vertex transform(const Vertex &v, const Matrix4 &translate,
	                        const Matrix4 &rotation, const Matrix4 &scale);

	static Vertex transform(const Vertex &v, const Matrix4 &translate,
	                        const Matrix4 &rotation);
};

#endif
