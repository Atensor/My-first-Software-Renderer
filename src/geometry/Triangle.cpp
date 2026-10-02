#include "Triangle.h"
#include <algorithm>
#include <cmath>

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c,
                   const Float3 &surface_normal)
    : vertices{a, b, c}, surface_normal{surface_normal} {}

Triangle::Triangle(const std::array<Vertex, 3> &vertices,
                   const Float3 &surface_normal)
    : vertices(vertices), surface_normal(surface_normal) {}

Float3 Triangle::get_color(const Float3 &barycentric_coordinates) const {

	// color contibution per Vertex
	Float3 a_color{Float3::scale(vertices[0].color, barycentric_coordinates.x /
	                                                    vertices[0].pos.z)};
	Float3 b_color{Float3::scale(vertices[1].color, barycentric_coordinates.y /
	                                                    vertices[1].pos.z)};
	Float3 c_color{Float3::scale(vertices[2].color, barycentric_coordinates.z /
	                                                    vertices[2].pos.z)};
	Float3 color_sum{a_color + b_color + c_color};

	return color_sum;
}

float Triangle::get_area(const Float2 &a, const Float2 &b, const Float2 &c) {
	Float2 ab = b - a;
	Float2 ac = c - a;

	return Float2::cross(ab, ac);
}

Float3 Triangle::get_barycentric_coordinates(std::array<Float2, 3> *screen_pos,
                                             const Float2 &x, float area) {
	float area_bcx{Triangle::get_area(screen_pos->at(1), screen_pos->at(2), x)};
	float area_acx{Triangle::get_area(screen_pos->at(2), screen_pos->at(0), x)};
	float area_abx{Triangle::get_area(screen_pos->at(0), screen_pos->at(1), x)};

	return Float3{area_bcx / area, area_acx / area, area_abx / area};
}
