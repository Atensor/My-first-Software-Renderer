#include "../math/Float4.h"
#include <string>
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class Framebuffer {
  private:
    int m_width{};
    int m_height{};
    Float4 *m_buffer;
    float *m_depth_buffer;

  public:
    Framebuffer(int width, int height);
    ~Framebuffer();

    void write_pixel(int x, int y, Float4 color, float depth);
    float get_depth(int x, int y) const;

    void write_ppm(std::string filename) const;

    int get_width() const;
    int get_height() const;
};

#endif
