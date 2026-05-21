#include "draw/Triangle.h"
#include <algorithm>
#include <iostream>

float clamp_between(float x, float min, float max) {
    return std::max(std::min(x, max), min);
}

int main() {
    int width{255};
    int height{255};

    Framebuffer *buffer = new Framebuffer(width, height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            buffer->write_pixel(x, y, Float3{0, 0, 0});
        }
    }

    Vertex a{Float3{75, 200, 0}, Float3{0, 0, 0},
             Float3{184.0f / 255, 51.0f / 255, 106.0f / 255}, 0.75f};
    Vertex b{Float3{200, 120, 0}, Float3{0, 0, 0},
             Float3{147.0f / 255, 163.0f / 255, 177.0f / 255}, 0.5f};
    Vertex c{Float3{125, 45, 0}, Float3{0, 0, 0},
             Float3{49.0f / 255, 76.0f / 255, 182.0f / 255}, 1.0f};

    Triangle triangle(a, b, c);

    triangle.draw_triangle(buffer);

    buffer->write_ppm("out.ppm");

    delete buffer;
}
