cmake_minimum_required(VERSION 3.16)
project(software_renderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -O0")

set(SOURCES
    src/ppm.cpp
    src/draw/Triangle.cpp
    src/draw/Bresenhams_Line.cpp
    src/draw/Camera.cpp
    src/draw/Framebuffer.cpp
    src/draw/Renderer.cpp
    src/math/Float2.cpp
    src/math/Float3.cpp
    src/math/Float4.cpp
    src/math/Matrix4.cpp
    src/math/Transform.cpp
    src/obj/Obj.cpp
)

add_executable(ppm ${SOURCES})
