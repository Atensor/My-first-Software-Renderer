#include "Triangle.h"
#include <algorithm>
#include <cmath>

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c)
    : m_vertices{a, b, c} {}

const Vertex &Triangle::get_a() const { return m_vertices[0]; }

const Vertex &Triangle::get_b() const { return m_vertices[1]; }

const Vertex &Triangle::get_c() const { return m_vertices[2]; }

// TODO: Adapt for 3D space to View plane projection
Float3 Triangle::get_color(const Float2 &x) const {
    Float2 a(m_vertices[0].pos.x, m_vertices[0].pos.y);
    Float2 b(m_vertices[1].pos.x, m_vertices[1].pos.y);
    Float2 c(m_vertices[2].pos.x, m_vertices[2].pos.y);

    Float3 barycentric_coordinates{
        get_barycentric_coordinates(Float3{x.x, x.y, 0})};
    // blending colors
    Float3 color{Float3::scale(m_vertices[0].color, barycentric_coordinates.x) +
                 Float3::scale(m_vertices[1].color, barycentric_coordinates.y) +
                 Float3::scale(m_vertices[2].color, barycentric_coordinates.z)};

    // applying shadows to the triangle
    return Float3{
        Float3::scale(color, m_vertices[0].light * barycentric_coordinates.x) +
        Float3::scale(color, m_vertices[1].light * barycentric_coordinates.y) +
        Float3::scale(color, m_vertices[2].light * barycentric_coordinates.z)};

    return color;
}

float Triangle::get_area() const {
    Float3 ab = m_vertices[1].pos - m_vertices[0].pos;
    Float3 ac = m_vertices[2].pos - m_vertices[0].pos;

    return Float3::cross(ab, ac).get_length();
}

float Triangle::get_area(int i_vertex_a, int i_vertex_b,
                         const Float3 &c) const {
    Float3 ab = m_vertices[i_vertex_b].pos - m_vertices[i_vertex_a].pos;
    Float3 ac = c - m_vertices[i_vertex_a].pos;

    return Float3::cross(ab, ac).get_length();
}

Float3 Triangle::get_barycentric_coordinates(const Float3 &x) const {
    float area{get_area()};
    return Float3{get_area(1, 2, x) / area, get_area(0, 2, x) / area,
                  get_area(0, 1, x) / area};
}

float get_side(const Float2 &a, const Float2 &b, int x, int y) {
    return Float2::cross(b - a, Float2(x, y) - a);
}

bool Triangle::is_inside(int x, int y) const {
    bool has_pos{false};
    bool has_neg{false};
    for (int i = 0; i < m_vertices.size(); i++) {
        float cross(
            get_side(Float2{m_vertices[i].pos.x, m_vertices[i].pos.y},
                     Float2{m_vertices[(i + 1) % m_vertices.size()].pos.x,
                            m_vertices[(i + 1) % m_vertices.size()].pos.y},
                     x, y));
        has_pos |= (cross >= 0);
        has_neg |= (cross < 0);
        if (has_pos && has_neg) {
            return false;
        }
    }
    return true;
}

void Triangle::draw_triangle(Framebuffer *buffer) const {

    float x_min{std::min(std::min(m_vertices[0].pos.x, m_vertices[1].pos.x),
                         m_vertices[2].pos.x)};
    float x_max{std::max(std::max(m_vertices[0].pos.x, m_vertices[1].pos.x),
                         m_vertices[2].pos.x)};

    float y_min{std::min(std::min(m_vertices[0].pos.y, m_vertices[1].pos.y),
                         m_vertices[2].pos.y)};
    float y_max{std::max(std::max(m_vertices[0].pos.y, m_vertices[1].pos.y),
                         m_vertices[2].pos.y)};

    Float2 bound_min{x_min, y_min};
    Float2 bound_max{x_max, y_max};
    for (int x = bound_min.x; x <= bound_max.x; x++) {
        for (int y = bound_min.y; y <= bound_max.y; y++) {
            if (is_inside(x, y)) {
                buffer->write_pixel(x, y, get_color(Float2(x, y)));
            }
        }
    }
}
