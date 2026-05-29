cmake_minimum_required(VERSION 3.16)
project(software_renderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -O0")

#adding libraries
add_library(math_lib
    src/math/Float2.cpp
    src/math/Float3.cpp
    src/math/Float4.cpp
    src/math/Matrix4.cpp
    src/math/Transform.cpp
)

target_include_directories(math_lib PUBLIC src)

add_library(render_lib
    src/draw/Triangle.cpp
    src/draw/Bresenhams_Line.cpp
    src/draw/Camera.cpp
    src/draw/Framebuffer.cpp
    src/draw/Renderer.cpp
)

target_include_directories(render_lib PUBLIC src)

add_library(obj_lib
    src/obj/Obj.cpp
)

target_include_directories(obj_lib PUBLIC src)


# linking libraries
target_link_libraries(render_lib PUBLIC math_lib)

target_link_libraries(obj_lib PUBLIC math_lib)

add_executable(ppm 
    src/ppm.cpp
)

target_link_libraries(ppm PRIVATE render_lib obj_lib)

# adding executables
add_executable(testing 
    src/Testing/matrix.cpp
)

target_link_libraries(testing PRIVATE math_lib)
