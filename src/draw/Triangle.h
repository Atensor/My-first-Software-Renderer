#include "../math/Float2.h"
#include "Framebuffer.h"
#include <array>
#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle {
  private:
    std::array<Float2, 3> m_points;

    int m_width;
    int m_height;

    Float2 m_bound_min;
    Float2 m_bound_max;

    Float3 m_color;

  public:
    Triangle(const Float2 &a, const Float2 &b, const Float2 &c,
             const Float3 &color);

    int get_width() const;
    int get_height() const;

    Float2 get_bound_min() const;
    Float2 get_bound_max() const;

    Float2 get_a() const;
    Float2 get_b() const;
    Float2 get_c() const;

    Float3 get_color() const;

    bool is_inside(int x, int y) const;
    void draw_triangle(Framebuffer *buffer) const;
};
#endif
