#include "Camera.h"

Camera::Camera(float depth, const Float2 &canvas_dim_in)
    : pos{Float3{0, 0, 0}}, canvas_dim(canvas_dim_in), rotate_x(0), rotate_y(0),
      VP_depth(depth), VP_height(1),
      VP_width(canvas_dim_in.x / canvas_dim_in.y) {}

Float2 Camera::viewport_to_canvas(const Float2 &vp_pos) const {
	// add half of the canvas dimensions to shift 0/0 to the center of the
	// canvas
	return Float2(vp_pos.x * canvas_dim.x / VP_width,
	              vp_pos.y * canvas_dim.y / VP_height) +
	       Float2::scale(canvas_dim, 1.0f / 2.0f);
}

Float2 Camera::project_pos(const Float3 &pos) const {
	return viewport_to_canvas(
	    Float2(pos.x * VP_depth / pos.z, pos.y * VP_depth / pos.z));
}

Matrix3x4 Camera::get_transform_matrix_inv() const {
	return Transform::camera_transform(pos, Float3(rotate_x, rotate_y, 0.0f));
}

Matrix3x4 Camera::get_rotation_matrix_inv() const {
	return Transform::rotate_inv(Float3(rotate_x, rotate_y, 0.0f));
}
