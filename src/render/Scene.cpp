#include "Scene.h"
#include <map>

Scene::Scene(const Camera &camera)
    : camera(camera), use_lighting(true), use_culling(true),
      draw_normals(false) {}

void transform_vec_Float3(const std::vector<Float3> &vec,
                          std::vector<Float3> *out,
                          const std::vector<bool> &vec_transformed,
                          const Matrix3x4 &transform) {
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec_transformed.at(i))
			out->at(i) = transform * vec.at(i);
	}
}

void Scene::render(std::unique_ptr<Framebuffer> &buffer) const {
	Float3 sky_light_dir_normalized =
	    use_lighting ? sky_light_dir.normalize() : sky_light_dir;

	for (auto &object : objects) {
		if (!object->draw) {
			continue;
		}

		// Pre Calculated Matrices as M = T * R * S
		// Seperate Rotation Matrix for normals
		//
		// World Space
		Matrix3x4 transform = object->get_transform_matrix();
		Matrix3x4 rotation = object->get_rotation_matrix();

		// Camera Space
		Matrix3x4 camera_transform = camera.get_transform_matrix_inv();
		Matrix3x4 camera_rotation = camera.get_rotation_matrix_inv();

		Matrix3x4 view_model_transform = camera_transform * transform;
		Matrix3x4 view_model_rotation = camera_rotation * rotation;

		std::vector<Float3> transformed_pos(object->mesh->positions.size());
		std::vector<Float3> transformed_norm(object->mesh->normals.size());

		std::vector<bool> pos_transformed(object->mesh->positions.size());
		std::vector<bool> norm_transformed(object->mesh->normals.size());
		std::vector<bool> culled_faces(object->mesh->faces.size());

		// First Iteration over Faces for Backface culling
		for (size_t i = 0; i < object->mesh->faces.size(); i++) {
			Float3 *p_surface_normal =
			    &(object->mesh->faces.at(i).surface_normal);

			float transformed_surface_normal_z =
			    view_model_rotation.values[8] * p_surface_normal->x +
			    view_model_rotation.values[9] * p_surface_normal->y +
			    view_model_rotation.values[10] * p_surface_normal->z +
			    view_model_rotation.values[11];

			if (transformed_surface_normal_z > 0 && use_culling) {
				culled_faces.at(i) = true;
			} else {
				for (size_t j = 0; j < 3; j++) {
					pos_transformed.at(
					    object->mesh->faces.at(i).pos_index.at(j)) = true;
					norm_transformed.at(
					    object->mesh->faces.at(i).normal_index.at(j)) = true;
				}
			}
		}

		// Lazy Transform non culled Vertex positions and normals
		transform_vec_Float3(object->mesh->positions, &transformed_pos,
		                     pos_transformed, view_model_transform);
		transform_vec_Float3(object->mesh->normals, &transformed_norm,
		                     norm_transformed, view_model_rotation);

		// Second Iteration over Faces for setting up Rasterization
		for (size_t i = 0; auto &face : object->mesh->faces) {
			if (culled_faces.at(i++))
				continue;

			std::array<Vertex, 3> vertices;

			for (size_t j = 0; j < vertices.size(); j++) {
				int pos_index = face.pos_index.at(j);
				int normal_index = face.normal_index.at(j);
				vertices.at(j) = Vertex{transformed_pos.at(pos_index),
				                        transformed_norm.at(normal_index),
				                        Float3(0, 0, 0), 1.0f};
			}

			Float3 face_color =
			    object->normals_as_color
			        ? Float3::scale(face.surface_normal + Float3{1, 1, 1},
			                        1.0f / 2.0f)
			        : object->color;

			if (use_lighting) {
				for (int l = -1; auto &vertex : vertices) {
					float light_dot(
					    Float3::dot(vertex.normal, sky_light_dir_normalized));
					vertices[++l].light = std::max(light_dot, 0.1f);
				}
			}

			vertices[0].color = face_color;
			vertices[1].color = face_color;
			vertices[2].color = face_color;

			std::array<Float2, 3> screen_pos_out = {
			    camera.project_pos(vertices[0].pos),
			    camera.project_pos(vertices[1].pos),
			    camera.project_pos(vertices[2].pos)};

			Float3 transformed_surface_normal =
			    view_model_rotation * face.surface_normal;

			Renderer::draw_triangle(
			    Triangle(vertices, transformed_surface_normal), &screen_pos_out,
			    camera, buffer);

			// Drawing normals of the triangles for Debug
			if (draw_normals) {
				Float3 center(0.0f, 0.0f, 0.0f);

				for (Vertex v : vertices) {
					center = center + v.pos;
				}

				center = Float3::scale(center, 1.0f / 3.0f);

				Float3 normal_dir(
				    center +
				    Float3::scale((rotation * face.surface_normal), 0.1f));

				Renderer::draw_line(center, normal_dir, Float3(1, 0, 0), camera,
				                    buffer.get());
			}
		}
	}
}
