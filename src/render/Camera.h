#include "../math/Transform.h"

#ifndef CAMERA_H
#define CAMERA_H
struct Camera {
    Float4 pos;

    float rotate_x;
    float rotate_y;

    Float2 canvas_dim;
    float VP_depth;
    float VP_height;
    float VP_width;

    Camera(float depth, const Float2 &canvas_dim_in);

    Float2 project_Vertex(const Vertex &v) const;
    Float2 viewport_to_canvas(const Float2 &vp_pos) const;

    Vertex to_viewspace(const Vertex &v) const;

    Matrix4 get_transform_matrix() const;
    Matrix4 get_rotation_matrix() const;
};

#endif
