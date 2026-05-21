#include "draw/Triangle.h"
#include <iostream>

int main() {
    int width{255};
    int height{255};

    Framebuffer *buffer = new Framebuffer(width, height);

    Float3 color(28, 183, 189);

    Float2 a(75, 200);
    Float2 b(200, 120);
    Float2 c(125, 45);

    Triangle triangle(a, b, c, color);

    triangle.is_inside(130, 120, true);
    buffer->write_ppm("out.ppm");

    delete buffer;
}
