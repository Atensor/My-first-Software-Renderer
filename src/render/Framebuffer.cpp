#include "Framebuffer.h"
#include <array>
#include <fstream>

Framebuffer::Framebuffer(int width, int height)
    : m_width{width}, m_height{height}, m_buffer(new Float4[width * height]),
      m_depth_buffer(new float[width * height]) {
    for (int i = 0; i < width * height; i++) {
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
