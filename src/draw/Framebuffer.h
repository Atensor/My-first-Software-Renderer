#include "../math/Float3.h"
#include <string>
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class Framebuffer {
  private:
    int m_width{};
    int m_height{};
    Float3 *m_buffer;

  public:
    Framebuffer(int width, int height);
    ~Framebuffer();

    void write_pixel(int x, int y, Float3 color);

    void write_ppm(std::string filename) const;

    int get_width() const;
    int get_height() const;
};

#endif
