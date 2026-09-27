#include "Transform.h"
#define _USE_MATH_DEFINES
#include <cmath>

float deg_to_rad(float a) { return a * ((float)M_PI / 180.0f); }

Matrix4 Transform::rotate(const Float3 &rotate) {
	float a = deg_to_rad(rotate.x);
	float b = deg_to_rad(rotate.y);
	float c = deg_to_rad(rotate.z);
	return Matrix4{std::array<std::array<float, 4>, 4>{
	    {{(float)cos(b) * (float)cos(c), (float)-cos(b) * (float)sin(c),
	      (float)-sin(b), 0.0f},
	     {(float)(cos(a) * sin(c) - sin(a) * sin(b) * cos(c)),
	      (float)(cos(a) * cos(c) + sin(a) * sin(b) * sin(c)),
	      (float)(-sin(a) * cos(b)), 0.0f},
	     {(float)(cos(a) * sin(b) * cos(c) + sin(a) * sin(c)),
	      (float)(sin(a) * cos(c) - cos(a) * sin(b) * sin(c)),
	      (float)(cos(a) * cos(b)), 0.0f},
	     {0.0f, 0.0f, 0.0f, 1.0f}}}};
}

Matrix4 Transform::rotate_inv(const Float3 &rotate) {
	float a = deg_to_rad(rotate.x);
	float b = deg_to_rad(rotate.y);
	float c = deg_to_rad(rotate.z);
	return Matrix4{std::array<std::array<float, 4>, 4>{
	    {{(float)(cos(b) * cos(c)),
	      (float)(cos(a) * sin(c) - sin(a) * sin(b) * cos(c)),
	      (float)(cos(a) * sin(b) * cos(c) + sin(a) * sin(c)), 0.0f},
	     {(float)(-cos(b) * sin(c)),
	      (float)(cos(a) * cos(c) + sin(a) * sin(b) * sin(c)),
	      (float)(sin(a) * cos(c) - cos(a) * sin(b) * sin(c)), 0.0f},
	     {(float)(-sin(b)), (float)(-sin(a) * cos(b)), (float)(cos(a) * cos(b)),
	      0.0f},
	     {0.0f, 0.0f, 0.0f, 1.0f}}}};
}

Matrix4 Transform::camera_transform(const Float4 &translate,
                                    const Float3 &rotate) {
	float a = deg_to_rad(rotate.x);
	float b = deg_to_rad(rotate.y);
	float c = deg_to_rad(rotate.z);
	return Matrix4{std::array<std::array<float, 4>, 4>{
	    {{(float)(cos(b) * cos(c)),
	      (float)(cos(a) * sin(c) - sin(a) * sin(b) * cos(c)),
	      (float)(cos(a) * sin(b) * cos(c) + sin(a) * sin(c)),
	      (float)(-cos(b) * cos(c) * translate.x -
	              (cos(a) * sin(c) - sin(a) * sin(b) * cos(c)) * translate.y -
	              (cos(a) * sin(b) * cos(c) + sin(a) * sin(c)) * translate.z)},
	     {(float)(-cos(b) * sin(c)),
	      (float)(cos(a) * cos(c) + sin(a) * sin(b) * sin(c)),
	      (float)(sin(a) * cos(c) - cos(a) * sin(b) * sin(c)),
	      (float)(cos(b) * sin(c) * translate.x -
	              (cos(a) * cos(c) + sin(a) * sin(b) * sin(c)) * translate.y +
	              (cos(a) * sin(b) * sin(c) - sin(a) * cos(c)) * translate.z)},
	     {(float)(-sin(b)), (float)(-sin(a) * cos(b)), (float)(cos(a) * cos(b)),
	      (float)(sin(b) * translate.x + sin(a) * cos(b) * translate.y -
	              cos(a) * cos(b) * translate.z)},
	     {0.0f, 0.0f, 0.0f, 1.0f}}}};
}

Matrix4 Transform::object_transform(const Float4 &translate,
                                    const Float3 &rotate, const float scalar) {
	float a = deg_to_rad(rotate.x);
	float b = deg_to_rad(rotate.y);
	float c = deg_to_rad(rotate.z);
	return Matrix4{std::array<std::array<float, 4>, 4>{
	    {{(float)cos(b) * (float)cos(c) * scalar,
	      (float)-cos(b) * (float)sin(c) * scalar, (float)-sin(b) * scalar,
	      translate.x},
	     {(float)((cos(a) * sin(c) - sin(a) * sin(b) * cos(c)) * scalar),
	      (float)((cos(a) * cos(c) + sin(a) * sin(b) * sin(c)) * scalar),
	      (float)((-sin(a) * cos(b)) * scalar), translate.y},
	     {(float)((cos(a) * sin(b) * cos(c) + sin(a) * sin(c)) * scalar),
	      (float)((sin(a) * cos(c) - cos(a) * sin(b) * sin(c)) * scalar),
	      (float)((cos(a) * cos(b)) * scalar), translate.z},
	     {0.0f, 0.0f, 0.0f, 1.0f}}}};
}

Matrix4 Transform::translate(const Float4 &a) {
	return Matrix4{
	    std::array<std::array<float, 4>, 4>{{{1.0f, 0.0f, 0.0f, a.x},
	                                         {0.0f, 1.0f, 0.0f, a.y},
	                                         {0.0f, 0.0f, 1.0f, a.z},
	                                         {0.0f, 0.0f, 0.0f, 1.0f}}}};
}

Matrix4 Transform::translate_inv(const Float4 &a) {
	return Matrix4{
	    std::array<std::array<float, 4>, 4>{{{1.0f, 0.0f, 0.0f, -a.x},
	                                         {0.0f, 1.0f, 0.0f, -a.y},
	                                         {0.0f, 0.0f, 1.0f, -a.z},
	                                         {0.0f, 0.0f, 0.0f, 1.0f}}}};
}

Matrix4 Transform::scale(float s) {
	return Matrix4{
	    std::array<std::array<float, 4>, 4>{{{s, 0.0f, 0.0f, 0.0f},
	                                         {0.0f, s, 0.0f, 0.0f},
	                                         {0.0f, 0.0f, s, 0.0f},
	                                         {0.0f, 0.0f, 0.0f, 1.0f}}}};
}

Vertex Transform::transform(const Vertex &v, const Matrix4 &tranform,
                            const Matrix4 &rotation) {
	Vertex out{v};
	out.pos = tranform * v.pos;
	out.normal = (rotation * v.normal);
	return out;
}
