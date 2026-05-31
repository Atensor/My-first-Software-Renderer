#include "Renderer.h"
#include <iostream>

#define ENDLINE '\n'

void Renderer::draw_triangle(const Triangle &tri, const Camera &camera,
                             Framebuffer *buffer) {
    // Get screenspace Cooridinates
    Float2 a{camera.project_Vertex(tri.vertices[0])},
        b{camera.project_Vertex(tri.vertices[1])},
        c{camera.project_Vertex(tri.vertices[2])};

    // Calculating Bounds to reduce pixel checks
    float x_min{std::min(std::min(a.x, b.x), c.x)};
    float x_max{std::max(std::max(a.x, b.x), c.x)};

    float y_min{std::min(std::min(a.y, b.y), c.y)};
    float y_max{std::max(std::max(a.y, b.y), c.y)};

    Float2 bound_min{std::max(x_min, 0.0f), std::max(y_min, 0.0f)};
    Float2 bound_max{std::min(x_max, (float)buffer->get_width()),
                     std::min(y_max, (float)buffer->get_height())};

    for (int x = bound_min.x; x <= bound_max.x; x++) {
        for (int y = bound_min.y; y <= bound_max.y; y++) {
            Float3 barycentric_coordinates =
                tri.get_barycentric_coordinates(a, b, c, Float2(x, y));
            float z{
                Float3::dot(barycentric_coordinates,
                            Float3{tri.vertices[0].pos.z, tri.vertices[1].pos.z,
                                   tri.vertices[2].pos.z})};
            if (tri.is_inside(x, y, std::array<Float2, 3>{a, b, c})) {
                if (z < camera.VP_depth) {
                    continue;
                }
                Float4 color(tri.get_color(a, b, c, Float2((float)x, (float)y),
                                           barycentric_coordinates));
                buffer->write_pixel(x, y, color, z);
            }
        }
    }
}

// TODO: implement
void Renderer::draw_line(const Float3 &a, const Float3 &b, const Float3 &color,
                         const Camera &camera, Framebuffer *buffer) {}
