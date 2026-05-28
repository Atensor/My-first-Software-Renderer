#include "Obj.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#define ENDLINE "\n"

// TODO: Add support for only Vertex Objects and Texture coordinates
Obj::Obj(std::string_view path) {
    std::fstream file(path.data());
    std::string str;

    while (std::getline(file, str)) {
        std::string temp("");
        if (str[0] == 'v' && str[1] == ' ') {
            float x{0}, y{0}, z{0};
            int coord_index = 0;
            for (int i = 2; i < str.length(); i++) {
                if (str[i] != ' ') {
                    temp.append(1, str[i]);
                } else {
                    switch (coord_index++) {
                    case 0:
                        x = std::stof(temp);
                        break;
                    case 1:
                        y = std::stof(temp);
                        break;
                    }
                    temp.clear();
                }
            }
            z = std::stof(temp);
            temp.clear();

            vertices.push_back(Float4(x, y, z, 1.0f));
        } else if (str[0] == 'v' && str[1] == 'n') {
            float x{0}, y{0}, z{0};
            int coord_index = 0;
            for (int i = 3; i < str.length(); i++) {
                if (str[i] != ' ') {
                    temp.append(1, str[i]);
                } else {
                    switch (coord_index++) {
                    case 0:
                        x = std::stof(temp);
                        break;
                    case 1:
                        y = std::stof(temp);
                        break;
                    }
                    temp.clear();
                }
            }
            z = std::stof(temp);
            temp.clear();
            normals.push_back(Float4(x, y, z, 0.0f));
        } else if (str[0] == 'f' && str[1] == ' ') {
            Face face;
            int vert_index{0};
            int part_index{0};
            std::string temp = "";
            for (int i = 2; i < str.length(); i++) {
                char current_char = str[i];
                if (current_char == ' ') {
                    face.normal_index[vert_index++] = std::stoi(temp);
                    temp.clear();
                    part_index = 0;
                } else if (std::isdigit(current_char)) {
                    temp.append(1, current_char);
                } else if (current_char == '/') {
                    if (part_index == 0) {
                        face.vertex_index[vert_index] = std::stoi(temp);
                    }
                    temp.clear();
                    part_index++;
                }
            }
            face.normal_index[vert_index] = std::stoi(temp);
            temp.clear();
            faces.push_back(face);
        }
    }
}

std::array<Vertex, 3> Obj::get_Face(int i) const {
    return std::array<Vertex, 3>{
        Vertex{vertices[faces[i].vertex_index[0] - 1],
               normals[faces[i].normal_index[0] - 1], Float4(0, 0, 0, 1), 1.0f},
        Vertex{vertices[faces[i].vertex_index[1] - 1],
               normals[faces[i].normal_index[1] - 1], Float4(0, 0, 0, 1), 1.0f},
        Vertex{vertices[faces[i].vertex_index[2] - 1],
               normals[faces[i].normal_index[2] - 1], Float4(0, 0, 0, 1),
               1.0f}};
}

int Obj::get_face_count() const { return faces.size(); }
