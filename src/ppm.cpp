#include "geometry/SceneObject.h"
#include "math/Transform.h"
#include "obj/Obj.h"
#include "render/Renderer.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>

#define ENDLINE "\n"

float clamp_between(float x, float min, float max) {
    return std::max(std::min(x, max), min);
}

int main() {
    int width{1920};
    int height{1080};

    std::unique_ptr<Framebuffer> buffer =
        std::make_unique<Framebuffer>(width, height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            buffer->write_pixel(x, y, Float4{0, 0, 0, 1},
                                std::numeric_limits<float>::infinity());
        }
    }

    Mesh monkey_mesh = Obj::parse_obj("monkey.obj");
    Mesh cube_mesh = Obj::parse_obj("Cube.obj");

    Camera camera(1, Float2(buffer->get_width(), buffer->get_height()));

    Renderer renderer;

    Float4 monkey_v{0.5f, 0, 3, 0};
    Matrix4 monkey_translate{Transform::translate(monkey_v)};

    Matrix4 monkey_rotate_x{Transform::rotate_x(180)};
    Matrix4 monkey_rotate_y{Transform::rotate_y(0)};

    Matrix4 monkey_transform =
        monkey_rotate_y * monkey_rotate_x * monkey_translate;

    SceneObject monkey = SceneObject(&monkey_mesh);
    for (int i = 0; i < monkey.mesh->faces.size(); i++) {
        std::array<Vertex, 3> vertices = monkey.get_Face_Vertices(i);

        for (int j = 0; j < vertices.size(); j++) {
            vertices[j] = Transform::transform(vertices[j], monkey_transform);
        }
        Triangle triangle(vertices[0], vertices[1], vertices[2]);

        Float4 face_color = Float4{
            Float3::scale(triangle.surface_normal.xyz() + Float3{1, 1, 1},
                          1.0f / 2.0f),
            1.0f};

        triangle.vertices[0].color = face_color;
        triangle.vertices[1].color = face_color;
        triangle.vertices[2].color = face_color;

        renderer.draw_triangle(triangle, camera, buffer);
    }

    Float4 cube_v{-2, 0, 5, 0};
    Matrix4 cube_translate{Transform::translate(cube_v)};

    Matrix4 cube_rotate_x{Transform::rotate_x(45)};
    Matrix4 cube_rotate_y{Transform::rotate_y(-35)};

    SceneObject cube = SceneObject(&cube_mesh);
    Matrix4 cube_m = cube_rotate_y * cube_rotate_x * cube_translate;
    for (int i = 0; i < cube.mesh->faces.size(); i++) {
        std::array<Vertex, 3> vertices = cube.get_Face_Vertices(i);

        for (int j = 0; j < vertices.size(); j++) {
            vertices[j] = Transform::transform(vertices[j], cube_m);
        }
        Triangle triangle(vertices[0], vertices[1], vertices[2]);

        Float4 face_color = Float4{
            Float3::scale(triangle.surface_normal.xyz() + Float3{1, 1, 1},
                          1.0f / 2.0f),
            1.0f};

        triangle.vertices[0].color = face_color;
        triangle.vertices[1].color = face_color;
        triangle.vertices[2].color = face_color;

        renderer.draw_triangle(triangle, camera, buffer);
    }

    buffer->write_ppm("out.ppm");

    return 0;
}
