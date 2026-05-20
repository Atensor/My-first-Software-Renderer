#include "draw/Bresenhams_Line.h"
#include <algorithm>
#include <iostream>

float clamp_between(float x, float min, float max) {
    return std::max(std::min(x, max), min);
}

void get_line_from_user(Framebuffer *buffer, Bresenhams_Line *line) {
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

    line->draw_line(va, vb);
}

int main() {
    int width{1920};
    int height{1080};

    Framebuffer *buffer = new Framebuffer(width, height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            buffer->write_pixel(
                x, y, Float3{(float)x / (float)width, 0, y / (float)height});
        }
    }

    int line_count{0};
    std::cout << "How many lines to Draw: ";
    std::cin >> line_count;
    std::cout << '\n';

    // get color
    int r, g, b;
    std::cout << "\nEnter color for the lines as r g b: ";
    std::cin >> r >> g >> b;
    std::cout << "\n";

    Float3 color(clamp_between(r, 0, 255) / 255, clamp_between(g, 0, 255) / 255,
                 clamp_between(b, 0, 255) / 255);

    Bresenhams_Line *line = new Bresenhams_Line(buffer, color);

    for (int i = 0; i < line_count; i++) {
        get_line_from_user(buffer, line);
    }

    buffer->write_ppm("out.ppm");

    delete line;
    delete buffer;
}
