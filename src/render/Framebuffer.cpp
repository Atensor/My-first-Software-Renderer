#include "Framebuffer.h"
#include <algorithm>
#include <array>
#include <fstream>

Framebuffer::Framebuffer(int width, int height)
    : m_width{width}, m_height{height}, buffer(new uint32_t[width * height]),
      depth_buffer(new float[width * height]) {
    for (int i = 0; i < width * height; i++) {
        buffer[i] = 0;
        depth_buffer[i] = 1.0f / 0.0f;
    }
}

Framebuffer::~Framebuffer() {
    delete[] buffer;
    delete[] depth_buffer;
}

uint32_t float4_to_uint32_color(const Float4 &color) {
    auto to_u_8 = [](float v) {
        v = std::clamp(v, 0.0f, 1.0f);
        return static_cast<uint8_t>(v * 255);
    };
    uint8_t a = to_u_8(color.a);
    uint8_t r = to_u_8(color.r);
    uint8_t g = to_u_8(color.g);
    uint8_t b = to_u_8(color.b);

    return (a << 24) | (r << 16) | (g << 8) | b;
}

void Framebuffer::write_pixel(int x, int y, Float4 color, float depth) {
    int index{x + y * m_width};
    if (depth_buffer[index] >= depth) {
        buffer[index] = float4_to_uint32_color(color);
        depth_buffer[index] = depth;
    }
}

void Framebuffer::clear() {
    Float4 black(0, 0, 0, 0);
    for (int i = 0; i < m_width * m_height; ++i) {
        buffer[i] = 0;
        depth_buffer[i] = 1.0f / 0.0f;
    }
}

float Framebuffer::get_depth(int x, int y) const {
    return depth_buffer[x + y * m_width];
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
            file << (int)((buffer[current_index] >> 16) & 0xFF) << " "
                 << (int)((buffer[current_index] >> 8) & 0xFF) << " "
                 << (int)(buffer[current_index] & 0xFF) << "  ";
        }
        file << "\n";
    }

    file.close();
}

int Framebuffer::get_width() const { return m_width; }

int Framebuffer::get_height() const { return m_height; }
