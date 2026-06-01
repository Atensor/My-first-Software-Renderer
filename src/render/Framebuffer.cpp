#include "Framebuffer.h"
#include <algorithm>
#include <array>
#include <fstream>

Framebuffer::Framebuffer(int width, int height)
    : m_width{width}, m_height{height}, m_buffer(new Float4[width * height]),
      m_depth_buffer(new float[width * height]) {
    for (int i = 0; i < width * height; i++) {
        m_buffer[i] = Float4{0, 0, 0, 0};
        m_depth_buffer[i] = 1.0f / 0.0f;
    }
}

Framebuffer::~Framebuffer() {
    delete[] m_buffer;
    delete[] m_depth_buffer;
}

void Framebuffer::write_pixel(int x, int y, Float4 color, float depth) {
    int index{x + y * m_width};
    if (m_depth_buffer[index] >= depth) {
        // TODO: do proper translucency via triangle sorting
        m_buffer[index] = m_buffer[index].alpha_composite(color);
        m_depth_buffer[index] = depth;
    }
}

void Framebuffer::convert_to_uint32_buffer(uint32_t *framebuffer) const {
    auto to_u_8 = [](float v) {
        v = std::clamp(v, 0.0f, 1.0f);
        return static_cast<uint8_t>(v * 255);
    };
    for (int i = 0; i < m_width * m_height; ++i) {
        uint8_t a = to_u_8(m_buffer[i].a);
        uint8_t r = to_u_8(m_buffer[i].r);
        uint8_t g = to_u_8(m_buffer[i].g);
        uint8_t b = to_u_8(m_buffer[i].b);

        framebuffer[i] = (a << 24) | (r << 16) | (g << 8) | b;
    }
}

void Framebuffer::clear() {
    Float4 black(0, 0, 0, 0);
    for (int i = 0; i < m_width * m_height; ++i) {
        m_buffer[i] = black;
        m_depth_buffer[i] = 1.0f / 0.0f;
    }
}

float Framebuffer::get_depth(int x, int y) const {
    return m_depth_buffer[x + y * m_width];
}

void Framebuffer::write_ppm(std::string filename) const {
    std::ofstream file;
    file.open(filename);

    file << "P3\n";
    file << m_width << " " << m_height << "\n";

    file << "255\n";

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            int current_index = x + y * m_width;
            file << (int)(m_buffer[current_index].r * 255) << " "
                 << (int)(m_buffer[current_index].g * 255) << " "
                 << (int)(m_buffer[current_index].b * 255) << "  ";
        }
        file << "\n";
    }

    file.close();
}

int Framebuffer::get_width() const { return m_width; }

int Framebuffer::get_height() const { return m_height; }
