#include "../geometry/Mesh.h"
#include <string_view>
#include <vector>

#ifndef OBJ_H
#define OBJ_H
struct Obj {
    static Mesh parse_obj(std::string_view path);
};
#endif
