#include "../math/Transform.h"

#ifndef CAMERA_H
#define CAMERA_H
struct Camera {
	Float3 pos;
	Float2 canvas_dim;

	float rotate_x;
	float rotate_y;

	float VP_depth;
	float VP_height;
	float VP_width;

	Camera(float depth, const Float2 &canvas_dim_in);

	Float2 project_pos(const Float3 &pos) const;
	Float2 viewport_to_canvas(const Float2 &vp_pos) const;

	Matrix3x4 get_transform_matrix_inv() const;
	Matrix3x4 get_rotation_matrix_inv() const;
};

#endif
