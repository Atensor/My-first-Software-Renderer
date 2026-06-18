#include "Camera.h"

Camera::Camera(float depth, const Float2 &canvas_dim_in)
    : pos{Float4{0, 0, 0, 0}}, canvas_dim(canvas_dim_in), rotate_x(0),
      rotate_y(0), VP_depth(depth), VP_height(1),
      VP_width(canvas_dim_in.x / canvas_dim_in.y) {}

Float2 Camera::viewport_to_canvas(const Float2 &vp_pos) const {
    // add half of the canvas dimensions to shift 0/0 to the center of the
    // canvas
    return Float2(vp_pos.x * canvas_dim.x / VP_width,
                  vp_pos.y * canvas_dim.y / VP_height) +
           Float2::scale(canvas_dim, 1.0f / 2.0f);
}

Float2 Camera::project_Vertex(const Vertex &v) const {
    return viewport_to_canvas(
        Float2(v.pos.x * VP_depth / v.pos.z, v.pos.y * VP_depth / v.pos.z));
}

std::array<Vertex, 3>
Camera::to_viewspace(const std::array<Vertex, 3> &vertices,
                     const Matrix4 &transform, const Matrix4 &rotation) const {
    std::array<Vertex, 3> out;
    for (int i = 0; i < (int)vertices.size(); i++) {
        out.at(i) = Transform::transform(vertices.at(i), transform, rotation);
    }
    return out;
}

Matrix4 Camera::get_transform_matrix() const {
    return Transform::translate(pos).inv() * get_rotation_matrix();
}

Matrix4 Camera::get_rotation_matrix() const {
    return (Transform::rotate_y(rotate_y) * Transform::rotate_x(rotate_x))
        .inv();
}
