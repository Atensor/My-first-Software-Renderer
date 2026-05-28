#include "Bresenhams_Line.h"
#include "Camera.h"
#include "Triangle.h"

#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
  public:
    void draw_triangle(const Triangle &tri, const Camera &camera,
                       Framebuffer *buffer);

    void draw_line(const Float3 &a, const Float3 &b, const Float3 &color,
                   const Camera &camera, Framebuffer *buffer);
};
#endif
