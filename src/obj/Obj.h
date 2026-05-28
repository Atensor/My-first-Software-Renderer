#include "../structs/Vertex.h"
#include <array>
#include <string_view>
#include <vector>
struct Face {
    std::array<int, 3> vertex_index;
    std::array<int, 3> normal_index;
};

#ifndef OBJ_H
#define OBJ_H
struct Obj {
    std::vector<Float4> vertices;
    std::vector<Float4> normals;

    std::vector<Face> faces;

    Obj(std::string_view path);

    std::array<Vertex, 3> get_Face(int i) const;

    int get_face_count() const;
};
#endif
