#include "Bresenhams_Line.h"
#include <algorithm>

void Bresenhams_Line::draw_line_low(const Float2 &a, const Float2 &b,
                                    const Float4 &color, Framebuffer *buffer) {
    int dx{int(b.x - a.x)};
    int dy{int(b.y - a.y)};

    // y step
    int yi{1};
    // if line is sinking reverse the step and the y change
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }

    // Desicion variable (D) whether to step y (the error to the
    // actual line) Initialized to distance from the
    // stepping line at the starting point a
    int D{2 * dy - dx};
    int y{(int)a.y};

    // ervery move steps x and decides if y needs to move
    for (int x{(int)a.x}; x <= (int)b.x; x++) {
        if (x < 0 || x >= buffer->get_width() || y < 0 ||
            y >= buffer->get_height()) {
            return;
        }
        // TODO: Adapt depth
        buffer->write_pixel(x, y, color, 1.0f);
        // moved far enough to be over the stepping line
        if (D > 0) {
            y = y + yi;
            // consume error because of y step
            D = D + 2 * (dy - dx);
        } else {
            // add to error
            D = D + 2 * dy;
        }
    }
}

void Bresenhams_Line::draw_line_high(const Float2 &a, const Float2 &b,
                                     const Float4 &color, Framebuffer *buffer) {
    int dx{int(b.x - a.x)};
    int dy{int(b.y - a.y)};
    int xi{1};
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int D{2 * dx - dy};
    int x{(int)a.x};

    for (int y{(int)a.y}; y <= (int)b.y; y++) {
        if (x < 0 || x >= buffer->get_width() || y < 0 ||
            y >= buffer->get_height()) {
            return;
        }
        buffer->write_pixel(x, y, color, 1.0f);
        if (D > 0) {
            x = x + xi;
            D = D + 2 * (dx - dy);
        } else {
            D = D + 2 * dx;
        }
    }
}

void Bresenhams_Line::draw_line(const Float2 &a, const Float2 &b,
                                const Float4 &color, Framebuffer *buffer) {
    if (std::abs(b.y - a.y) < std::abs(b.x - a.x)) {
        if (a.x > b.x) {
            draw_line_low(b, a, color, buffer);
        } else {
            draw_line_low(a, b, color, buffer);
        }
    } else {
        if (a.y > b.y) {
            draw_line_high(b, a, color, buffer);
        } else {
            draw_line_high(a, b, color, buffer);
        }
    }
}
