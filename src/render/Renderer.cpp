#include "Renderer.h"
#include "../geometry/Bresenhams_Line.h"
#include "../structs/Edge.h"
#include <cmath>
#include <vector>

#define ENDLINE '\n'

inline void swap(std::array<Float2, 3> *arr, int index_1, int index_2) {
	Float2 temp{arr->at(index_1)};
	arr->at(index_1) = arr->at(index_2);
	arr->at(index_2) = temp;
}

// Sorting Vertex positions with Bubble Sort
inline void sort_by_y(std::array<Float2, 3> *in) {
	if (in->at(1).y < in->at(0).y) {
		swap(in, 1, 0);
	}
	if (in->at(2).y < in->at(0).y) {
		swap(in, 2, 0);
	}
	if (in->at(2).y < in->at(1).y) {
		swap(in, 2, 1);
	}
}

void Renderer::draw_triangle(const Triangle &tri,
                             std::array<Float2, 3> *screen_pos,
                             const Camera &camera,
                             std::unique_ptr<Framebuffer> &buffer) {

	std::array<Float2, 3> sorted_vertices = *screen_pos;
	sort_by_y(&sorted_vertices);

	// used this book for scanline rasterization, but removed the vectors with a
	// struct:
	// https://gabrielgambetta.com/computer-graphics-from-scratch/07-filled-triangles.html
	//
	// Setting up edges
	Edge edge_long = Edge(sorted_vertices.at(0).x, sorted_vertices.at(0).y,
	                      sorted_vertices.at(2).x, sorted_vertices.at(2).y);

	Edge edge_short = Edge(sorted_vertices.at(0).x, sorted_vertices.at(0).y,
	                       sorted_vertices.at(1).x, sorted_vertices.at(1).y);

	// Setting up x-step differences
	float area = Triangle::get_area(screen_pos->at(0), screen_pos->at(1),
	                                screen_pos->at(2));

	Float3 d_barycentric_dx{(screen_pos->at(1).y - screen_pos->at(2).y) / area,
	                        (screen_pos->at(2).y - screen_pos->at(0).y) / area,
	                        (screen_pos->at(0).y - screen_pos->at(1).y) / area};

	float dz_dx = d_barycentric_dx.x * tri.vertices.at(0).pos.z +
	              d_barycentric_dx.y * tri.vertices.at(1).pos.z +
	              d_barycentric_dx.z * tri.vertices.at(2).pos.z;

	float d_inv_z_dx = d_barycentric_dx.x / tri.vertices.at(0).pos.z +
	                   d_barycentric_dx.y / tri.vertices.at(1).pos.z +
	                   d_barycentric_dx.z / tri.vertices.at(2).pos.z;

	Float3 d_color_dx{
	    Float3::scale(tri.vertices.at(0).color,
		              d_barycentric_dx.x / tri.vertices.at(0).pos.z) +
	    Float3::scale(tri.vertices.at(1).color,
		              d_barycentric_dx.y / tri.vertices.at(1).pos.z) +
	    Float3::scale(tri.vertices.at(2).color,
		              d_barycentric_dx.z / tri.vertices.at(2).pos.z)};

	float d_light_dx{(tri.vertices.at(0).light / tri.vertices.at(0).pos.z) *
	                     d_barycentric_dx.x +
	                 (tri.vertices.at(1).light / tri.vertices.at(1).pos.z) *
	                     d_barycentric_dx.y +
	                 (tri.vertices.at(2).light / tri.vertices.at(2).pos.z) *
	                     d_barycentric_dx.z};

	// step until the top of the screen
	for (int i = static_cast<int>(std::ceil(sorted_vertices.at(0).y)); i < 0;
	     i++) {
		if (i == edge_short.y_end) {
			edge_short = Edge(sorted_vertices.at(1).x, sorted_vertices.at(1).y,
			                  sorted_vertices.at(2).x, sorted_vertices.at(2).y);
		}
		edge_short.step_x();
		edge_long.step_x();
	}

	int y_start{
	    std::max(static_cast<int>(std::ceil(sorted_vertices.at(0).y)), 0)};
	int y_end{std::min(static_cast<int>(std::ceil(sorted_vertices.at(2).y)),
	                   buffer->get_height() - 1)};

	int y = y_start;
	while (y < y_end) {
		// get the next short edge when the first has ended
		if (y == edge_short.y_end) {
			edge_short = Edge(sorted_vertices.at(1).x, sorted_vertices.at(1).y,
			                  sorted_vertices.at(2).x, sorted_vertices.at(2).y);
		}

		// init Scanline start and end
		float x_short = edge_short.x;
		float x_long = edge_long.x;

		edge_short.step_x();
		edge_long.step_x();

		float x_left = std::min(x_short, x_long);
		float x_right = std::max(x_short, x_long);

		int x_start{std::max(static_cast<int>(std::floor(x_left)), 0)};
		int x_end{std::min(static_cast<int>(std::ceil(x_right)),
		                   buffer->get_width() - 1)};

		// init values at Scanline start
		Float3 barycentric_coordinates = tri.get_barycentric_coordinates(
		    screen_pos, Float2(x_start, y), area);

		float z{Float3::dot(barycentric_coordinates,
		                    Float3{tri.vertices.at(0).pos.z,
		                           tri.vertices.at(1).pos.z,
		                           tri.vertices.at(2).pos.z})};

		float inv_z{(barycentric_coordinates.x / tri.vertices.at(0).pos.z) +
		            (barycentric_coordinates.y / tri.vertices.at(1).pos.z) +
		            (barycentric_coordinates.z / tri.vertices.at(2).pos.z)};

		Float3 color_sum(tri.get_color(barycentric_coordinates));

		float light{(tri.vertices.at(0).light / tri.vertices.at(0).pos.z) *
		                barycentric_coordinates.x +
		            (tri.vertices.at(1).light / tri.vertices.at(1).pos.z) *
		                barycentric_coordinates.y +
		            (tri.vertices.at(2).light / tri.vertices.at(2).pos.z) *
		                barycentric_coordinates.z};

		for (int x = x_start; x < x_end; x++) {

			if (z < camera.VP_depth ||
			    z > buffer->depth_buffer[x + y * buffer->get_width()]) {
				continue;
			}

			// Remove z from Interpolated values
			Float3 interpolated_color{Float3::scale(color_sum, 1.0f / inv_z)};
			float interpolated_light = light / inv_z;

			// apply light
			Float3 color{Float3::scale(interpolated_color, interpolated_light)};

			buffer->write_pixel(x, y, color, z);

			// advance Values to next Pixel
			barycentric_coordinates =
			    barycentric_coordinates + d_barycentric_dx;

			z += dz_dx;
			inv_z += d_inv_z_dx;

			color_sum = color_sum + d_color_dx;
			light += d_light_dx;
		}
		y++;
	}
}

void Renderer::draw_line(const Float3 &a, const Float3 &b, const Float3 &color,
                         const Camera &camera, Framebuffer *buffer) {
	Float2 a_screen{camera.project_pos(a)};
	Float2 b_screen{camera.project_pos(b)};

	Bresenhams_Line::draw_line(a_screen, b_screen, color, buffer);
}
