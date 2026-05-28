#include "../math/Float2.h"

struct Vertex;

#ifndef CAMERA_H
#define CAMERA_H
struct Camera {
    float VP_depth;
    float VP_height{1};
    float VP_width;
    Float2 canvas_dim;

    Float2 project_Vertex(const Vertex &v) const;
    Float2 viewport_to_canvas(const Float2 &vp_pos) const;
};

#endif
