cmake_minimum_required(VERSION 3.16)
project(software_renderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -O0")

find_package(SDL3 REQUIRED)

#adding libraries
add_library(math_lib
    src/math/vector/Float2.cpp
    src/math/vector/Float3.cpp
    src/math/vector/Float4.cpp
    src/math/matrix/Matrix4.cpp
    src/math/Transform.cpp
)

target_include_directories(math_lib PUBLIC src)

add_library(render_lib
    src/render/Camera.cpp
    src/render/Framebuffer.cpp
    src/render/Renderer.cpp
)

target_include_directories(render_lib PUBLIC src)

add_library(obj_lib
    src/obj/Obj.cpp
)

target_include_directories(obj_lib PUBLIC src)

add_library(geometry_lib
    src/geometry/Triangle.cpp
)

target_include_directories(geometry_lib PUBLIC src)


# linking libraries
target_link_libraries(render_lib PRIVATE SDL3::SDL3)

target_link_libraries(render_lib PUBLIC math_lib)

target_link_libraries(render_lib PUBLIC geometry_lib)

target_link_libraries(obj_lib PUBLIC math_lib)

add_executable(main
    src/main.cpp
)

target_link_libraries(main PRIVATE render_lib obj_lib)

add_executable(ppm 
    src/ppm.cpp
)

target_link_libraries(ppm PRIVATE render_lib obj_lib)

# adding executables
add_executable(testing 
    src/Testing/matrix.cpp
)

target_link_libraries(testing PRIVATE math_lib)
