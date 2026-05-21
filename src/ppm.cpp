#include "draw/Triangle.h"
#include <algorithm>
#include <iostream>

float clamp_between(float x, float min, float max) {
    return std::max(std::min(x, max), min);
}

void get_triangle_from_user(Framebuffer *buffer, const Float3 &color) {
    // get first Vector
    int ax, ay;
    std::cout << "Enter point a as x y: ";
    std::cin >> ax >> ay;

    Float2 va(clamp_between(ax, 0, (float)buffer->get_width() - 1),
              clamp_between(ay, 0, (float)buffer->get_height() - 1));

    // get second Vector
    int bx, by;
    std::cout << "Enter point b as x y: ";
    std::cin >> bx >> by;

    Float2 vb(clamp_between(bx, 0, (float)buffer->get_width() - 1),
              clamp_between(by, 0, (float)buffer->get_height() - 1));

    // get third Vector
    int cx, cy;
    std::cout << "Enter point c as x y: ";
    std::cin >> cx >> cy;

    Float2 vc(clamp_between(cx, 0, (float)buffer->get_width() - 1),
              clamp_between(cy, 0, (float)buffer->get_height() - 1));

    Triangle triangle(va, vb, vc, color);

    triangle.draw_triangle(buffer);
}

int main() {
    int width{255};
    int height{255};

    Framebuffer *buffer = new Framebuffer(width, height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            buffer->write_pixel(
                x, y, Float3{(float)x / (float)width, 0, y / (float)height});
        }
    }

    int triangle_count{0};
    std::cout << "How many triangles to Draw: ";
    std::cin >> triangle_count;
    std::cout << '\n';

    // get color
    int r, g, b;
    std::cout << "\nEnter color for the triangles as r g b: ";
    std::cin >> r >> g >> b;
    std::cout << "\n";

    Float3 color(clamp_between(r, 0, 255) / 255, clamp_between(g, 0, 255) / 255,
                 clamp_between(b, 0, 255) / 255);

    for (int i = 0; i < triangle_count; i++) {
        get_triangle_from_user(buffer, color);
    }

    buffer->write_ppm("out.ppm");

    delete buffer;
}
