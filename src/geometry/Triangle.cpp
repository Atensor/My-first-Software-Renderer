#include "Triangle.h"
#include <algorithm>
#include <cmath>

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c,
                   const Float4 &surface_normal)
    : vertices{a, b, c}, surface_normal{surface_normal} {}

Float4 Triangle::get_color(const Float2 &a, const Float2 &b, const Float2 &c,
                           const Float2 &x,
                           const Float3 &barycentric_coordinates) const {

    // inverse of the depth at the current pixel
    float inv_z{(barycentric_coordinates.x / vertices[0].pos.z) +
                (barycentric_coordinates.y / vertices[1].pos.z) +
                (barycentric_coordinates.z / vertices[2].pos.z)};

    // blending colors
    Float4 color{
        Float3::scale(
            Float3::scale(vertices[0].color.xyz(),
                          barycentric_coordinates.x / vertices[0].pos.z) +
                Float3::scale(vertices[1].color.xyz(),
                              barycentric_coordinates.y / vertices[1].pos.z) +
                Float3::scale(vertices[2].color.xyz(),
                              barycentric_coordinates.z / vertices[2].pos.z),
            1.0f / inv_z),
        ((vertices[0].color.a / vertices[0].pos.z) * barycentric_coordinates.x +
         (vertices[1].color.a / vertices[1].pos.z) * barycentric_coordinates.y +
         (vertices[2].color.a / vertices[2].pos.z) *
             barycentric_coordinates.z) /
            inv_z};

    // blending light
    float light{
        ((vertices[0].light / vertices[0].pos.z) * barycentric_coordinates.x +
         (vertices[1].light / vertices[1].pos.z) * barycentric_coordinates.y +
         (vertices[2].light / vertices[2].pos.z) * barycentric_coordinates.z) /
        inv_z};

    // applying light to color
    return Float4{Float3::scale(color.xyz(), light), color.a};
}

float Triangle::get_area(const Float2 &a, const Float2 &b, const Float2 &c) {
    Float2 ab = b - a;
    Float2 ac = c - a;

    return Float2::cross(ab, ac);
}

Float3 Triangle::get_barycentric_coordinates(const Float2 &a, const Float2 &b,
                                             const Float2 &c, const Float2 &x) {
    float area{Triangle::get_area(a, b, c)};

    float area_bcx{Triangle::get_area(b, c, x)};
    float area_acx{Triangle::get_area(c, a, x)};
    float area_abx{Triangle::get_area(a, b, x)};

    return Float3{area_bcx / area, area_acx / area, area_abx / area};
}

float get_side(const Float2 &a, const Float2 &b, int x, int y) {
    return Float2::cross(b - a, Float2(x, y) - a);
}

bool Triangle::is_inside(int x, int y,
                         const std::array<Float2, 3> &vertices) const {
    bool has_pos{false};
    bool has_neg{false};
    for (int i = 0; i < vertices.size(); i++) {
        float cross(
            get_side(vertices[i], vertices[(i + 1) % vertices.size()], x, y));
        has_pos |= (cross >= 0);
        has_neg |= (cross < 0);
        if (has_pos && has_neg) {
            return false;
        }
    }
    return true;
}
