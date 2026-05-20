#include "../math/Float2.h"
#include "Framebuffer.h"

#ifndef BRESENHAMS_LINE_H
#define BRESENHAMS_LINE_H

class Bresenhams_Line {
  private:
    Framebuffer *m_buffer;

    Float3 m_color;

  public:
    Bresenhams_Line(Framebuffer *buffer);
    Bresenhams_Line(Framebuffer *buffer, const Float3 &color);

    void draw_line(const Float2 &a, const Float2 &b);

    void draw_line_low(const Float2 &a, const Float2 &b);
    void draw_line_high(const Float2 &a, const Float2 &b);

    void set_color(const Float3 &color);
};
#endif
