#include "Framebuffer.h"
#include <array>
#include <fstream>

Framebuffer::Framebuffer(int width, int height)
    : m_width{width}, m_height{height}, m_buffer(new Float3[width * height]) {}

Framebuffer::~Framebuffer() { delete[] m_buffer; }
void Framebuffer::write_pixel(int x, int y, Float3 color) {
    m_buffer[x + y * m_width] = color;
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
            file << (int)(m_buffer[current_index].x * 255) << " "
                 << (int)(m_buffer[current_index].y * 255) << " "
                 << (int)(m_buffer[current_index].z * 255) << "  ";
        }
        file << "\n";
    }

    file.close();
}
int Framebuffer::get_width() const { return m_width; }
int Framebuffer::get_height() const { return m_height; }
