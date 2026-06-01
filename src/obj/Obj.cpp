#include "Obj.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#define ENDLINE "\n"

Mesh Obj::parse_obj(std::string_view path) {
    std::fstream file(path.data());
    std::string str;

    Mesh out;

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

            out.vertices.emplace_back(Float4(x, y, z, 1.0f));
        } else if (str[0] == 'v' && str[1] == 't') {
            float x{0}, y{0};
            int coord_index{0};
            for (int i = 3; i < str.length(); i++) {
                if (str[i] != ' ') {
                    temp.append(1, str[i]);
                } else {
                    if (coord_index == 0) {
                        x = std::stof(temp);
                        temp.clear();
                    }
                }
            }
            y = std::stof(temp);
            temp.clear();

            out.texture_coordinates.emplace_back(Float2(x, y));
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
            out.normals.emplace_back(Float4(x, y, z, 0.0f));
        } else if (str[0] == 'f' && str[1] == ' ') {
            Face face;
            int vert_index{0};
            int part_index{0};
            std::string temp = "";
            for (int i = 2; i < str.length(); i++) {
                char current_char = str[i];
                if (current_char == ' ') {
                    switch (part_index) {
                    case 0:
                        face.vertex_index.at(vert_index++) = std::stoi(temp);
                        break;
                    case 1:
                        face.texture_coordinate_index.at(vert_index++) =
                            std::stoi(temp);
                        break;
                    case 2:
                        face.normal_index.at(vert_index++) = std::stoi(temp);
                        break;
                    }
                    temp.clear();
                    part_index = 0;
                } else if (std::isdigit(current_char)) {
                    temp.append(1, current_char);
                } else if (current_char == '/') {
                    if (temp.length() == 0) {
                        part_index++;
                        continue;
                    }
                    switch (part_index) {
                    case 0:
                        face.vertex_index.at(vert_index) = std::stoi(temp);
                        break;
                    case 1:
                        face.texture_coordinate_index.at(vert_index) =
                            std::stoi(temp);
                        break;
                    }
                    temp.clear();
                    part_index++;
                }
            }
            switch (part_index) {
            case 0:
                face.vertex_index.at(vert_index) = std::stoi(temp);
                break;
            case 1:
                face.texture_coordinate_index.at(vert_index) = std::stoi(temp);
                break;
            case 2:
                face.normal_index.at(vert_index) = std::stoi(temp);
                break;
            }
            temp.clear();
            out.faces.emplace_back(face);
        }
    }
    return out;
}
