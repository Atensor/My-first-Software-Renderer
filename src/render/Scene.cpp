#include "Scene.h"

Scene::Scene(const Camera &camera)
    : camera(camera), use_lighting(true), use_culling(true),
      draw_normals(false) {}

void Scene::render(std::unique_ptr<Framebuffer> &buffer) const {
    for (auto &object : objects) {
        if (!object->draw) {
            continue;
        }

        // Calculating tranform Matrices as M = T * R * S
        // Seperate Rotation Matrix for normals
        Matrix4 transform = object->get_transform_matrix();
        Matrix4 rotation = object->get_rotation_matrix();

        Matrix4 camera_transform = camera.get_transform_matrix();
        Matrix4 camera_rotation = camera.get_rotation_matrix();

        for (int j = -1; auto &face : object->mesh->faces) {
            std::array<Vertex, 3> vertices;

            for (int k = -1; auto &vertex : object->get_Face_Vertices(++j)) {
                vertices[++k] =
                    Transform::transform(vertex, transform, rotation);
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
                    float light_dot(Float3::dot(
                        vertex.normal.xyz(), sky_light_dir.normalize().xyz()));
                    vertices[++l].light = std::max(light_dot, 0.1f);
                }
            }

            vertices[0].color = face_color;
            vertices[1].color = face_color;
            vertices[2].color = face_color;

            Renderer::draw_triangle(
                Triangle(camera.to_viewspace(vertices, camera_transform,
                                             camera_rotation),
                         camera.get_rotation_matrix() * rotation *
                             face.surface_normal),
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

                Renderer::draw_line(center, normal_dir, Float4(1, 0, 0, 1),
                                    camera, buffer.get());
            }
        }
    }
}
