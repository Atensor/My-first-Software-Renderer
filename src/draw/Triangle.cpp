#include "Triangle.h"
#include <algorithm>

Triangle::Triangle(const Float2 &a, const Float2 &b, const Float2 &c,
                   const Float3 &color)
    : m_points{a, b, c}, m_color{color} {
    float x_min{std::min(std::min(a.x, b.x), c.x)};
    float x_max{std::max(std::max(a.x, b.x), c.x)};

    float y_min{std::min(std::min(a.y, b.y), c.y)};
    float y_max{std::max(std::max(a.y, b.y), c.y)};

    m_width = (int)x_max - (int)x_min;
    m_height = (int)y_max - (int)y_min;

    m_bound_min = Float2{x_min, y_min};
    m_bound_max = Float2{x_max, y_max};
}

int Triangle::get_width() const { return m_width; }

int Triangle::get_height() const { return m_height; }

Float2 Triangle::get_bound_min() const { return m_bound_min; }

Float2 Triangle::get_bound_max() const { return m_bound_max; }

Float2 Triangle::get_a() const { return m_points[0]; }

Float2 Triangle::get_b() const { return m_points[1]; }

Float2 Triangle::get_c() const { return m_points[2]; }

Float3 Triangle::get_color() const { return m_color; }

float get_side(const Float2 &a, const Float2 &b, int x, int y) {
    return Float2::cross(Float2::subtract(b, a),
                         Float2::subtract(Float2(x, y), a));
}

bool Triangle::is_inside(int x, int y) const {
    bool has_pos{false};
    bool has_neg{false};
    for (int i = 0; i < m_points.size(); i++) {
        float cross(
            get_side(m_points[i], m_points[(i + 1) % m_points.size()], x, y));
        has_pos |= (cross >= 0);
        has_neg |= (cross < 0);
        if (has_pos && has_neg) {
            return false;
        }
    }
    return true;
}

void Triangle::draw_triangle(Framebuffer *buffer) const {
    for (int x = m_bound_min.x; x <= m_bound_max.x; x++) {
        for (int y = m_bound_min.y; y <= m_bound_max.y; y++) {
            if (is_inside(x, y)) {
                buffer->write_pixel(x, y, get_color());
            }
        }
    }
}
