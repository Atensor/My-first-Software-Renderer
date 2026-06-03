#include "../render/Framebuffer.h"

#ifndef BRESENHAMS_LINE_H
#define BRESENHAMS_LINE_H

struct Bresenhams_Line {
    static void draw_line(const Float2 &a, const Float2 &b, const Float4 &color,
                          Framebuffer *buffer);

    static void draw_line_low(const Float2 &a, const Float2 &b,
                              const Float4 &color, Framebuffer *buffer);
    static void draw_line_high(const Float2 &a, const Float2 &b,
                               const Float4 &color, Framebuffer *buffer);
};
#endif
