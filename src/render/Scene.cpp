#include "Scene.h"

Scene::Scene(const Camera &camera) : camera(camera) {}

void Scene::render(std::unique_ptr<Framebuffer> &buffer) const {
    for (int i = 0; i < objects.size(); ++i) {

        Matrix4 transform = camera.get_transform_matrix() *
                            objects.at(i)->get_transform_matrix();

        for (int j = 0; j < objects.at(i)->mesh->faces.size(); ++j) {
            std::array<Vertex, 3> vertices =
                objects.at(i)->get_Face_Vertices(j);

            for (int k = 0; k < vertices.size(); k++) {
                vertices[k] = Transform::transform(vertices[k], transform);
            }
            Triangle triangle(vertices[0], vertices[1], vertices[2]);

            if (Float4::dot(triangle.surface_normal, Float4(0, 0, 1, 0)) > 0)
                continue;

            Float4 face_color =
                objects.at(i)->normals_as_color
                    ? Float4{Float3::scale(triangle.surface_normal.xyz() +
                                               Float3{1, 1, 1},
                                           1.0f / 2.0f),
                             1.0f}
                    : objects.at(i)->color;

            // TODO: make a proper light interpolation
            // float light_dot =
            //     Float3::dot(triangle.surface_normal.xyz(),
            //     sky_light_dir.xyz());

            triangle.vertices[0].color = face_color;
            //  triangle.vertices[0].light = std::max(light_dot, 0.01f);
            triangle.vertices[1].color = face_color;
            //  triangle.vertices[1].light = std::max(light_dot, 0.01f);
            triangle.vertices[2].color = face_color;
            //  triangle.vertices[2].light = std::max(light_dot, 0.01f);

            Renderer::draw_triangle(triangle, camera, buffer);
        }
    }
}
