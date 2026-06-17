#include "../math/vector/Float4.h"
#include <stdint.h>
#include <string>
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

struct Framebuffer {
  private:
    int m_width{};
    int m_height{};

  public:
    uint32_t *buffer;
    float *depth_buffer;

    Framebuffer(int width, int height);
    ~Framebuffer();

    void write_pixel(int x, int y, Float4 color, float depth);
    float get_depth(int x, int y) const;

    void write_ppm(std::string filename) const;

    void convert_to_uint32_buffer(uint32_t *framebuffer) const;

    void clear();

    int get_width() const;
    int get_height() const;
};

#endif
