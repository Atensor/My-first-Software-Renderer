#include "Scene.h"

Scene::Scene(const Camera &camera)
    : camera(camera), use_lighting(true), use_culling(true),
      draw_normals(false) {}

void transform_vec_Float4(const std::vector<Float4> &vec,
                          std::vector<Float4> *out, const Matrix4 &transform) {
	for (auto &float_4 : vec) {
		out->emplace_back(transform * float_4);
	}
}

void Scene::render(std::unique_ptr<Framebuffer> &buffer) const {
	Float4 sky_light_dir_normalized =
	    use_lighting ? sky_light_dir.normalize() : sky_light_dir;

	for (auto &object : objects) {
		if (!object->draw) {
			continue;
		}

		// Calculating tranform Matrices as M = T * R * S
		// Seperate Rotation Matrix for normals
		Matrix4 transform = object->get_transform_matrix();
		Matrix4 rotation = object->get_rotation_matrix();

		Matrix4 camera_transform = camera.get_transform_matrix_inv();
		Matrix4 camera_rotation = camera.get_rotation_matrix_inv();

		Matrix4 view_model_transform = camera_transform * transform;
		Matrix4 view_model_rotation = camera_rotation * rotation;

		std::vector<Float4> transformed_pos;
		std::vector<Float4> transformed_norm;

		transformed_pos.reserve(object->mesh->vertices.size());
		transformed_norm.reserve(object->mesh->normals.size());

		transform_vec_Float4(object->mesh->vertices, &transformed_pos,
		                     view_model_transform);
		transform_vec_Float4(object->mesh->normals, &transformed_norm,
		                     view_model_rotation);

		for (int j = -1; auto &face : object->mesh->faces) {
			std::array<Vertex, 3> vertices;

			for (size_t i = 0; i < vertices.size(); i++) {
				vertices.at(i) =
				    Vertex{transformed_pos.at(face.vertex_index.at(i) - 1),
				           transformed_norm.at(face.normal_index.at(i) - 1),
				           Float4(0, 0, 0, 1), 1.0f};
			}
			Float4 face_color =
			    object->normals_as_color
			        ? Float4{Float3::scale((face.surface_normal).xyz() +
			                                   Float3{1, 1, 1},
			                               1.0f / 2.0f),
			                 1.0f}
			        : object->color;

			if (use_lighting) {
				for (int l = -1; auto &vertex : vertices) {
					float light_dot(
					    Float4::dot(vertex.normal, sky_light_dir_normalized));
					vertices[++l].light = std::max(light_dot, 0.1f);
				}
			}

			vertices[0].color = face_color;
			vertices[1].color = face_color;
			vertices[2].color = face_color;

			Renderer::draw_triangle(
			    Triangle(vertices, view_model_rotation * face.surface_normal),
			    camera, buffer, use_culling);

			// Drawing normals of the triangles for Debug
			if (draw_normals) {
				Float4 center(0.0f, 0.0f, 0.0f, 0.0f);
				for (Vertex v : vertices) {
					center = center + v.pos;
				}
				center = Float4::scale(center, 1.0f / 3.0f);
				Float4 normal_dir(
				    center +
				    Float4::scale(rotation * face.surface_normal, 0.1f));

				Renderer::draw_line(camera_transform * center,
				                    camera_rotation * normal_dir,
				                    Float4(1, 0, 0, 1), camera, buffer.get());
			}
		}
	}
}
