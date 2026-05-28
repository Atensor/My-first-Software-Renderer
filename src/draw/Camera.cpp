#include "Camera.h"
#include "../structs/Vertex.h"

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
