#include "../structs/Vertex.h"
#include <array>
#include <string_view>
#include <vector>
struct Face {
    std::array<int, 3> vertex_index;
    std::array<int, 3> normal_index;
    std::array<int, 3> texture_coordinate_index;
};

#ifndef OBJ_H
#define OBJ_H
struct Obj {
    std::vector<Float4> vertices;
    std::vector<Float4> normals;
    std::vector<Float2> texture_coordinates;

    bool has_normals;
    bool has_texture_coordinates;

    std::vector<Face> faces;

    Obj(std::string_view path);

    std::array<Vertex, 3> get_Face_Vertices(int i) const;
    std::array<Float2, 3> get_Face_Texture_Coordinates(int i) const;

    int get_face_count() const;
};
#endif
