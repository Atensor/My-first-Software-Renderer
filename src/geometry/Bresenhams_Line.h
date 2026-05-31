#include "../math/vector/Float3.h"

#ifndef BRESENHAMS_LINE_H
#define BRESENHAMS_LINE_H

class Bresenhams_Line {
  private:
    Float3 m_color;

  public:
    Bresenhams_Line();
    Bresenhams_Line(const Float3 &color);

    void draw_line(const Float2 &a, const Float2 &b);

    void draw_line_low(const Float2 &a, const Float2 &b);
    void draw_line_high(const Float2 &a, const Float2 &b);

    void set_color(const Float3 &color);
};
#endif
