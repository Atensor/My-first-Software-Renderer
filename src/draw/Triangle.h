#include "../structs/Vertex.h"
#include <array>
#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Triangle {
    std::array<Vertex, 3> vertices;

    Float4 surface_normal;

    Triangle(const Vertex &a, const Vertex &b, const Vertex &c);

    Float4 get_color(const Float2 &a, const Float2 &b, const Float2 &c,
                     const Float3 &x) const;

    static float get_area(const Float2 &a, const Float2 &b, const Float2 &c);
    static Float3 get_barycentric_coordinates(const Float2 &a, const Float2 &b,
                                              const Float2 &c, const Float2 &x);

    bool is_inside(int x, int y, const std::array<Float2, 3> &vertices) const;
};
#endif
