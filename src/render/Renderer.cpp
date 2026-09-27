#include "Renderer.h"
#include "../geometry/Bresenhams_Line.h"
#include "../structs/Edge.h"
#include <cmath>
#include <vector>

#define ENDLINE '\n'

void swap(std::array<Float2, 3> *arr, int index_1, int index_2) {
	Float2 temp{arr->at(index_1)};
	arr->at(index_1) = arr->at(index_2);
	arr->at(index_2) = temp;
}

std::array<Float2, 3> sort_by_y(const Float2 &a, const Float2 &b,
                                const Float2 &c) {
	std::array<Float2, 3> out{a, b, c};
	if (out.at(1).y < out.at(0).y) {
		swap(&out, 1, 0);
	}
	if (out.at(2).y < out.at(0).y) {
		swap(&out, 2, 0);
	}
	if (out.at(2).y < out.at(1).y) {
		swap(&out, 2, 1);
	}

	return out;
}

void Renderer::draw_triangle(const Triangle &tri, const Camera &camera,
                             std::unique_ptr<Framebuffer> &buffer,
                             bool use_culling) {

	if (Float4::dot(tri.surface_normal,
	                Float4::scale(tri.vertices.at(0).pos, -1.0f)) < 0 &&
	    use_culling)
		return;

	Float2 a = camera.project_Vertex(tri.vertices[0]);
	Float2 b = camera.project_Vertex(tri.vertices[1]);
	Float2 c = camera.project_Vertex(tri.vertices[2]);

	float area = Triangle::get_area(a, b, c);

	// Get screenspace Cooridinates
	std::array<Float2, 3> sorted_vertices{sort_by_y(a, b, c)};

	// used this book for scanline rasterization, but removed the vectors with a
	// struct:
	// https://gabrielgambetta.com/computer-graphics-from-scratch/07-filled-triangles.html
	Edge edge_long = Edge(sorted_vertices.at(0).x, sorted_vertices.at(0).y,
	                      sorted_vertices.at(2).x, sorted_vertices.at(2).y);

	Edge edge_short = Edge(sorted_vertices.at(0).x, sorted_vertices.at(0).y,
	                       sorted_vertices.at(1).x, sorted_vertices.at(1).y);

	// TODO: Fix Cut off for Triangles partily off screen
	int y_start{
	    std::max(static_cast<int>(std::ceil(sorted_vertices.at(0).y)), 0)};
	int y_end{std::min(static_cast<int>(std::ceil(sorted_vertices.at(2).y)),
	                   buffer->get_height() - 1)};

	int y = y_start;
	while (y < y_end) {
		if (y == edge_short.y_end) {
			edge_short = Edge(sorted_vertices.at(1).x, sorted_vertices.at(1).y,
			                  sorted_vertices.at(2).x, sorted_vertices.at(2).y);
		}

		float x_short = edge_short.x;
		float x_long = edge_long.x;

		edge_short.step_x();
		edge_long.step_x();

		float x_left = std::min(x_short, x_long);
		float x_right = std::max(x_short, x_long);

		int x_start{std::max(static_cast<int>(std::floor(x_left)), 0)};
		int x_end{std::min(static_cast<int>(std::ceil(x_right)),
		                   buffer->get_width() - 1)};
		for (int x = x_start; x < x_end; x++) {

			Float3 barycentric_coordinates =
			    tri.get_barycentric_coordinates(a, b, c, Float2(x, y), area);
			// if a point is outside the Triangle (barycentric
			// coordinate negetive) skip this point
			/*
			if (barycentric_coordinates.x < -epsilon ||
			    barycentric_coordinates.y < -epsilon ||
			    barycentric_coordinates.z < -epsilon) {
			    continue;
			}
			*/

			// interpolating the depth
			float z{
			    Float3::dot(barycentric_coordinates,
			                Float3{tri.vertices[0].pos.z, tri.vertices[1].pos.z,
			                       tri.vertices[2].pos.z})};

			if (z < camera.VP_depth ||
			    z > buffer->depth_buffer[x + y * buffer->get_width()]) {
				continue;
			}

			Float4 color(tri.get_color(barycentric_coordinates));

			buffer->write_pixel(x, y, color, z);
		}
		y++;
	}
}

void Renderer::draw_line(const Float4 &a, const Float4 &b, const Float4 &color,
                         const Camera &camera, Framebuffer *buffer) {
	Float2 a_screen{
	    camera.project_Vertex(Vertex{a, Float4(0, 0, 0, 0), color, 1.0f})};
	Float2 b_screen{
	    camera.project_Vertex(Vertex{b, Float4(0, 0, 0, 0), color, 1.0f})};

	Bresenhams_Line::draw_line(a_screen, b_screen, color, buffer);
}
