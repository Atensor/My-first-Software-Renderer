#include "../structs/Vertex.h"
#include <array>
#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Triangle {
	std::array<Vertex, 3> vertices;

	Float3 surface_normal;

	Triangle(const Vertex &a, const Vertex &b, const Vertex &c,
	         const Float3 &surface_normal);

	Triangle(const std::array<Vertex, 3> &vertices,
	         const Float3 &surface_normal);

	Float3 get_color(const Float3 &barycentric_coordinates) const;

	static float get_area(const Float2 &a, const Float2 &b, const Float2 &c);
	static Float3 get_barycentric_coordinates(std::array<Float2, 3> *screen_pos,
	                                          const Float2 &x, float area);
};
#endif
