#include "Scene.h"

Scene::Scene(const Camera &camera)
    : camera(camera), use_lighting(true), use_culling(true),
      draw_normals(false) {}

void Scene::render(std::unique_ptr<Framebuffer> &buffer) const {
    for (auto &object : objects) {
        if (!object->draw) {
            continue;
        }

        Matrix4 translate = object->get_translation_matrix();
        Matrix4 rotation = object->get_rotation_matrix();
        Matrix4 scale = object->get_scalar_matrix();

        for (int j = -1; auto &face : object->mesh->faces) {
            std::array<Vertex, 3> vertices = object->get_Face_Vertices(++j);

            for (int k = -1; auto &vertex : vertices) {
                vertices[++k] =
                    Transform::transform(vertex, translate, rotation, scale);
            }
            Triangle triangle(vertices[0], vertices[1], vertices[2],
                              rotation * face.surface_normal);

            Float4 face_color =
                object->normals_as_color
                    ? Float4{Float3::scale(
                                 (rotation.inv() * triangle.surface_normal)
                                         .xyz() +
                                     Float3{1, 1, 1},
                                 1.0f / 2.0f),
                             1.0f}
                    : object->color;

            // TODO: make a proper light interpolation
            if (use_lighting) {
                for (int l = -1; auto &vertex : triangle.vertices) {
                    float light_dot(Float3::dot(
                        vertex.normal.xyz(), sky_light_dir.normalize().xyz()));
                    triangle.vertices[++l].light = std::max(light_dot, 0.1f);
                }
            }

            triangle.vertices[0].color = face_color;
            triangle.vertices[1].color = face_color;
            triangle.vertices[2].color = face_color;

            Renderer::draw_triangle(
                Triangle(camera.to_viewspace(triangle.vertices[0]),
                         camera.to_viewspace(triangle.vertices[1]),
                         camera.to_viewspace(triangle.vertices[2]),
                         camera.get_rotation_matrix() *
                             triangle.surface_normal),
                camera, buffer, use_culling);

            if (draw_normals) {
                Float4 center(Float4::scale(
                    camera.to_viewspace(triangle.vertices[0]).pos +
                        camera.to_viewspace(triangle.vertices[1]).pos +
                        camera.to_viewspace(triangle.vertices[2]).pos,
                    1.0f / 3.0f));
                Float4 normal_dir(center +
                                  Float4::scale(triangle.surface_normal, 0.1f));

                Renderer::draw_line(center, normal_dir, Float4(1, 0, 0, 1),
                                    camera, buffer.get());
            }
        }
    }
}
