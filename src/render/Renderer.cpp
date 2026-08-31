#include "Renderer.h"
#include "../geometry/Bresenhams_Line.h"
#include <cmath>
#include <vector>

#define ENDLINE '\n'

void swap(std::array<Float2, 3> *arr, int index_1, int index_2) {
	Float2 temp{arr->at(index_1)};
	arr->at(index_1) = arr->at(index_2);
	arr->at(index_2) = temp;
}

std::array<Float2, 3> sort_by_y(const Float2 a, const Float2 b,
                                const Float2 c) {
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

std::vector<float> interpolate(float x0, float y0, float x1, float y1) {
	std::vector<float> out;

	if (y0 == y1) {
		return out;
	}

	int y_start{static_cast<int>(std::ceil(y0))};
	int y_end{static_cast<int>(std::ceil(y1))};

	out.reserve(y_end - y_start);

	float a = (x1 - x0) / (float)(y1 - y0);
	float x = x0 + (y_start - y0) * a;

	for (int y = y_start; y < y_end; ++y) {
		out.push_back(x);
		x += a;
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
	// Get screenspace Cooridinates
	std::array<Float2, 3> sorted_vertices{
	    sort_by_y(Float2{camera.project_Vertex(tri.vertices[0])},
	              Float2{camera.project_Vertex(tri.vertices[1])},
	              Float2{camera.project_Vertex(tri.vertices[2])})};

	// used this book for scanline rasterization:
	// https://gabrielgambetta.com/computer-graphics-from-scratch/07-filled-triangles.html
	std::vector<float> x_02{
	    interpolate(sorted_vertices.at(0).x, sorted_vertices.at(0).y,
	                sorted_vertices.at(2).x, sorted_vertices.at(2).y)};

	if (x_02.empty()) {
		return;
	}

	std::vector<float> x_01{
	    interpolate(sorted_vertices.at(0).x, sorted_vertices.at(0).y,
	                sorted_vertices.at(1).x, sorted_vertices.at(1).y)};
	x_01.reserve(x_02.size());
	std::vector<float> x_12{
	    interpolate(sorted_vertices.at(1).x, sorted_vertices.at(1).y,
	                sorted_vertices.at(2).x, sorted_vertices.at(2).y)};

	x_01.insert(x_01.end(), x_12.begin(), x_12.end());
	if (x_01.empty()) {
		return;
	}

	std::vector<float> *x_left, *x_right;
	int m{(int)floor(x_02.size() / 2.0f)};

	if (x_02.size() <= 2) {
		m = 0;
	}
	if (x_01.at(m) < x_02.at(m)) {
		x_left = &x_01;
		x_right = &x_02;
	} else {
		x_left = &x_02;
		x_right = &x_01;
	}

	// TODO: Fix Cut off for Triangles partily off screen
	int y_start{std::max((int)std::ceil(sorted_vertices.at(0).y), 0)};
	int y_end{std::min((int)std::ceil(sorted_vertices.at(2).y),
	                   buffer->get_height() - 1)};
	int y_step{0};
	for (int y = y_start; y < y_end; ++y) {
		int x_start{
		    std::max(static_cast<int>(std::floor(x_left->at(y_step))), 0)};
		int x_end{std::min(static_cast<int>(std::ceil(x_right->at(y_step))),
		                   buffer->get_width() - 1)};
		for (int x = x_start; x < x_end; x++) {

			Float3 barycentric_coordinates = tri.get_barycentric_coordinates(
			    Float2{camera.project_Vertex(tri.vertices[0])},
			    Float2{camera.project_Vertex(tri.vertices[1])},
			    Float2{camera.project_Vertex(tri.vertices[2])}, Float2(x, y));
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
		y_step++;
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
