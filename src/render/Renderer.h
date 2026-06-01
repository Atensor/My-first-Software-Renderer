#include "../geometry/Triangle.h"
#include "Camera.h"
#include "Framebuffer.h"
#include <memory>

#ifndef RENDERER_H
#define RENDERER_H

struct Renderer {
    static void draw_triangle(const Triangle &tri, const Camera &camera,
                              std::unique_ptr<Framebuffer> &buffer);

    static void draw_line(const Float3 &a, const Float3 &b, const Float3 &color,
                          const Camera &camera, Framebuffer *buffer);
};
#endif
