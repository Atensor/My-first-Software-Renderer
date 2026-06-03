#include "../geometry/Triangle.h"
#include "Camera.h"
#include "Framebuffer.h"
#include <memory>

#ifndef RENDERER_H
#define RENDERER_H

struct Renderer {
    static void draw_triangle(const Triangle &tri, const Camera &camera,
                              std::unique_ptr<Framebuffer> &buffer,
                              bool use_culling);

    static void draw_line(const Float4 &a, const Float4 &b, const Float4 &color,
                          const Camera &camera, Framebuffer *buffer);
};
#endif
