#include "Transform.h"
#include <cmath>

float deg_to_rad(float a) { return a * ((float)M_PI / 180.0f); }

Matrix3x4 Transform::rotate(const Float3 &rotate) {
	float a = deg_to_rad(rotate.x);
	float b = deg_to_rad(rotate.y);
	float c = deg_to_rad(rotate.z);

	float sin_a = std::sin(a);
	float sin_b = std::sin(b);
	float sin_c = std::sin(c);

	float cos_a = std::cos(a);
	float cos_b = std::cos(b);
	float cos_c = std::cos(c);

	return Matrix3x4{std::array<float, 12>{
	    cos_b * cos_c,
	    -cos_b * sin_c,
	    -sin_b,
	    0.0f,
	    cos_a * sin_c - sin_a * sin_b * cos_c,
	    cos_a * cos_c + sin_a * sin_b * sin_c,
	    -sin_a * cos_b,
	    0.0f,
	    cos_a * sin_b * cos_c + sin_a * sin_c,
	    sin_a * cos_c - cos_a * sin_b * sin_c,
	    cos_a * cos_b,
	    0.0f,
	}};
}

Matrix3x4 Transform::rotate_inv(const Float3 &rotate) {
	float a = deg_to_rad(rotate.x);
	float b = deg_to_rad(rotate.y);
	float c = deg_to_rad(rotate.z);

	float sin_a = std::sin(a);
	float sin_b = std::sin(b);
	float sin_c = std::sin(c);

	float cos_a = std::cos(a);
	float cos_b = std::cos(b);
	float cos_c = std::cos(c);

	return Matrix3x4{std::array<float, 12>{
	    cos_b * cos_c, cos_a * sin_c - sin_a * sin_b * cos_c,
	    cos_a * sin_b * cos_c + sin_a * sin_c, 0.0f, -cos_b * sin_c,
	    cos_a * cos_c + sin_a * sin_b * sin_c,
	    sin_a * cos_c - cos_a * sin_b * sin_c, 0.0f, -sin_b, -sin_a * cos_b,
	    cos_a * cos_b, 0.0f}};
}

Matrix3x4 Transform::camera_transform(const Float3 &translate,
                                      const Float3 &rotate) {
	float a = deg_to_rad(rotate.x);
	float b = deg_to_rad(rotate.y);
	float c = deg_to_rad(rotate.z);

	float sin_a = std::sin(a);
	float sin_b = std::sin(b);
	float sin_c = std::sin(c);

	float cos_a = std::cos(a);
	float cos_b = std::cos(b);
	float cos_c = std::cos(c);

	return Matrix3x4{std::array<float, 12>{
	    cos_b * cos_c, cos_a * sin_c - sin_a * sin_b * cos_c,
	    cos_a * sin_b * cos_c + sin_a * sin_c,
	    -cos_b * cos_c * translate.x -
	        (cos_a * sin_c - sin_a * sin_b * cos_c) * translate.y -
	        (cos_a * sin_b * cos_c + sin_a * sin_c) * translate.z,
	    -cos_b * sin_c, cos_a * cos_c + sin_a * sin_b * sin_c,
	    sin_a * cos_c - cos_a * sin_b * sin_c,
	    cos_b * sin_c * translate.x -
	        (cos_a * cos_c + sin_a * sin_b * sin_c) * translate.y +
	        (cos_a * sin_b * sin_c - sin_a * cos_c) * translate.z,
	    -sin_b, -sin_a * cos_b, cos_a * cos_b,
	    sin_b * translate.x + sin_a * cos_b * translate.y -
	        cos_a * cos_b * translate.z}};
}

Matrix3x4 Transform::object_transform(const Float3 &translate,
                                      const Float3 &rotate,
                                      const float scalar) {
	float a = deg_to_rad(rotate.x);
	float b = deg_to_rad(rotate.y);
	float c = deg_to_rad(rotate.z);

	float sin_a = std::sin(a);
	float sin_b = std::sin(b);
	float sin_c = std::sin(c);

	float cos_a = std::cos(a);
	float cos_b = std::cos(b);
	float cos_c = std::cos(c);

	return Matrix3x4{std::array<float, 12>{
	    cos_b * cos_c * scalar, -cos_b * sin_c * scalar, -sin_b * scalar,
	    translate.x, (cos_a * sin_c - sin_a * sin_b * cos_c) * scalar,
	    (cos_a * cos_c + sin_a * sin_b * sin_c) * scalar,
	    (-sin_a * cos_b) * scalar, translate.y,
	    (cos_a * sin_b * cos_c + sin_a * sin_c) * scalar,
	    (sin_a * cos_c - cos_a * sin_b * sin_c) * scalar,
	    (cos_a * cos_b) * scalar, translate.z}};
}

Matrix3x4 Transform::translate(const Float3 &a) {
	return Matrix3x4{std::array<float, 12>{1.0f, 0.0f, 0.0f, a.x, 0.0f, 1.0f,
	                                       0.0f, a.y, 0.0f, 0.0f, 1.0f, a.z}

	};
}

Matrix3x4 Transform::translate_inv(const Float3 &a) {
	return Matrix3x4{std::array<float, 12>{1.0f, 0.0f, 0.0f, -a.x, 0.0f, 1.0f,
	                                       0.0f, -a.y, 0.0f, 0.0f, 1.0f, -a.z}};
}

Matrix3x4 Transform::scale(float s) {
	return Matrix3x4{std::array<float, 12>{s, 0.0f, 0.0f, 0.0f, 0.0f, s, 0.0f,
	                                       0.0f, 0.0f, 0.0f, s, 0.0f}};
}
