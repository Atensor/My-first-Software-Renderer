#include "Camera.h"

Camera::Camera(float depth, const Float2 &canvas_dim_in)
    : pos{Float4{0, 0, 0, 0}}, rotate_x(0), rotate_y(0), VP_depth(depth),
      VP_height(1), VP_width(canvas_dim_in.x / canvas_dim_in.y),
      canvas_dim(canvas_dim_in) {}

Float2 Camera::viewport_to_canvas(const Float2 &vp_pos) const {
    // add halve of the canvas dimensions to shift 0/0 to the center of the
    // canvas
    return Float2(vp_pos.x * canvas_dim.x / VP_width,
                  vp_pos.y * canvas_dim.y / VP_height) +
           Float2::scale(canvas_dim, 1.0f / 2.0f);
}

Float2 Camera::project_Vertex(const Vertex &v) const {
    return viewport_to_canvas(
        Float2(v.pos.x * VP_depth / v.pos.z, v.pos.y * VP_depth / v.pos.z));
}

Vertex Camera::to_viewspace(const Vertex &v) const {
    return Transform::transform(v, get_transform_matrix(),
                                get_rotation_matrix());
}

Matrix4 Camera::get_transform_matrix() const {
    return Transform::translate(pos).inv();
}

Matrix4 Camera::get_rotation_matrix() const {
    return (Transform::rotate_y(rotate_y) * Transform::rotate_x(rotate_x))
        .inv();
}
