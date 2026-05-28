#include "Triangle.h"
#include <algorithm>
#include <cmath>

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c)
    : vertices{a, b, c},
      surface_normal{Float4::scale(a.normal + b.normal + c.normal, 1.0f / 3.0f)
                         .normalize()} {}

Float4 Triangle::get_color(const Float2 &a, const Float2 &b, const Float2 &c,
                           const Float3 &x) const {
    Float3 barycentric_coordinates{
        Triangle::get_barycentric_coordinates(a, b, c, x.xy())};
    // blending colors
    Float4 color{
        Float3::scale(vertices[0].color.xyz(), barycentric_coordinates.x) +
            Float3::scale(vertices[1].color.xyz(), barycentric_coordinates.y) +
            Float3::scale(vertices[2].color.xyz(), barycentric_coordinates.z),
        vertices[0].color.a * barycentric_coordinates.x +
            vertices[1].color.a * barycentric_coordinates.y +
            vertices[2].color.a * barycentric_coordinates.z};

    float light{vertices[0].light * barycentric_coordinates.x +
                vertices[1].light * barycentric_coordinates.y +
                vertices[2].light * barycentric_coordinates.z};

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
