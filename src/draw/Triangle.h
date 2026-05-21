#include "../math/Float2.h"
#include "../structs/Vertex.h"
#include "Framebuffer.h"
#include <array>
#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle {
  private:
    std::array<Vertex, 3> m_vertices;

  public:
    Triangle(const Vertex &a, const Vertex &b, const Vertex &c);

    const Vertex &get_a() const;
    const Vertex &get_b() const;
    const Vertex &get_c() const;

    Float3 get_color(const Float2 &x) const;

    float get_area() const;
    float get_area(int i_vertex_a, int i_vertex_b, const Float3 &c) const;
    Float3 get_barycentric_coordinates(const Float3 &x) const;

    bool is_inside(int x, int y) const;
    void draw_triangle(Framebuffer *buffer) const;
};
#endif
