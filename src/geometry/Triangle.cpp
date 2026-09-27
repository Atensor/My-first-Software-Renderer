#include "Triangle.h"
#include <algorithm>
#include <cmath>

Triangle::Triangle(const Vertex &a, const Vertex &b, const Vertex &c,
                   const Float4 &surface_normal)
    : vertices{a, b, c}, surface_normal{surface_normal} {}

Triangle::Triangle(const std::array<Vertex, 3> &vertices,
                   const Float4 &surface_normal)
    : vertices(vertices), surface_normal(surface_normal) {}

Float4 Triangle::get_color(const Float3 &barycentric_coordinates) const {

	// inverse of the depth at the current pixel
	float inv_z{(barycentric_coordinates.x / vertices[0].pos.z) +
	            (barycentric_coordinates.y / vertices[1].pos.z) +
	            (barycentric_coordinates.z / vertices[2].pos.z)};
	Float3 a_color{
	    Float3::scale(vertices[0].color.xyz(),
	                  barycentric_coordinates.x / vertices[0].pos.z)};
	Float3 b_color{
	    Float3::scale(vertices[1].color.xyz(),
	                  barycentric_coordinates.y / vertices[1].pos.z)};
	Float3 c_color{
	    Float3::scale(vertices[2].color.xyz(),
	                  barycentric_coordinates.z / vertices[2].pos.z)};
	Float3 color_sum{a_color + b_color + c_color};
	color_sum = Float3::scale(color_sum, 1.0f / inv_z);

	// blending light
	float a_light{(vertices[0].light / vertices[0].pos.z) *
	              barycentric_coordinates.x};
	float b_light{(vertices[1].light / vertices[1].pos.z) *
	              barycentric_coordinates.y};
	float c_light{(vertices[2].light / vertices[2].pos.z) *
	              barycentric_coordinates.z};
	float light{(a_light + b_light + c_light) / inv_z};

	// TODO: Add alpha blending
	// applying light to color
	return Float4{Float3::scale(color_sum, light), 1.0f};
}

float Triangle::get_area(const Float2 &a, const Float2 &b, const Float2 &c) {
	Float2 ab = b - a;
	Float2 ac = c - a;

	return Float2::cross(ab, ac);
}

Float3 Triangle::get_barycentric_coordinates(const Float2 &a, const Float2 &b,
                                             const Float2 &c, const Float2 &x,
                                             float area) {
	float area_bcx{Triangle::get_area(b, c, x)};
	float area_acx{Triangle::get_area(c, a, x)};
	float area_abx{Triangle::get_area(a, b, x)};

	return Float3{area_bcx / area, area_acx / area, area_abx / area};
}
