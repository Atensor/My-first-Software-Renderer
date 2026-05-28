#include "draw/Renderer.h"
#include "math/Transform.h"
#include "obj/Obj.h"
#include <algorithm>
#include <iostream>
#include <limits>
#define _USE_MATH_DEFINES
#include <cmath>

#define ENDLINE "\n"

float clamp_between(float x, float min, float max) {
    return std::max(std::min(x, max), min);
}

int main() {
    int width{1920};
    int height{1080};

    Framebuffer *buffer = new Framebuffer(width, height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            buffer->write_pixel(x, y, Float4{0, 0, 0, 1},
                                std::numeric_limits<float>::infinity());
        }
    }

    Obj monkey("monkey.obj");

    Camera camera;
    camera.VP_depth = 1;
    camera.VP_height = 1;
    camera.VP_width = (float)buffer->get_width() / (float)buffer->get_height();
    camera.canvas_dim = Float2(buffer->get_width(), buffer->get_height());

    Renderer renderer;

    for (int i = 0; i < monkey.get_face_count(); i++) {
        std::array<Vertex, 3> vertices = monkey.get_Face(i);

        Float4 face_color =
            Float4{Float3::scale(vertices[1].normal.xyz() + Float3{1, 1, 1},
                                 1.0f / 2.0f),
                   1.0f};

        vertices[0].color = face_color;
        vertices[1].color = face_color;
        vertices[2].color = face_color;

        Float4 v{0, 0, 3, 0};
        Matrix4 translate{Transform::translate(v)};

        Matrix4 rotate_x{Transform::rotate_x(M_PI)};
        Matrix4 rotate_y{Transform::rotate_y(0)};

        for (int j = 0; j < vertices.size(); j++) {
            vertices[j] = Transform::transform(vertices[j], rotate_y);
            vertices[j] = Transform::transform(vertices[j], rotate_x);
            vertices[j] = Transform::transform(vertices[j], translate);
        }
        Triangle triangle(vertices[0], vertices[1], vertices[2]);

        renderer.draw_triangle(triangle, camera, buffer);
    }

    buffer->write_ppm("out.ppm");

    delete buffer;
}
